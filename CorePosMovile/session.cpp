#include "session.h"

session::session()
{
    settings.setUp();
    id_str_rt=settings.getIdStore();
    id_ws = settings.getIdWorkStation();
    numero_de_intentos=settings.getNoIntentos();
}

QVariant session::setLogin(QString usuario, QString password)
{
    QMap<QString,QVariant> respuesta;
    QSqlDatabase sqlDatabasebut;
    QString xml="";
    QDateTime block;
    QString actual;
    QString query;
    QString fecha1;

    int id_opr_till;
    bool hubocorte;
    bool ok;
    int ai_trn = 0;

    respuesta["exito"]=0;
    respuesta["mensaje"]="";
    mismo_usuario = -1;
    hubocorte=false;
    permisos.clear();
    actual = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QSqlQuery sqlQuery( sqlDatabasebut.database( "Origen") ) ;


    //Valida las credenciales del usuar
    qDebug()<< "Session.cpp SetLogin usuario y password "  << usuario << password ;
    if (usuario == "")
    {
        qDebug() << "Session.cpp usuario setlogin Vacio";
        xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>usuario vacio</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
        return xml;
    }
    if (password == "")
    {
        qDebug() << "Session.cpp password setlogin Vacio" ;
        xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>password vacio</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
        return xml;
    }
    //Recuperamos el bloqueo
    fecha1=settings.getBloqued_Time();
    if (numero_de_intentos > 3)
    {
        if(fecha1.length()>0)//No es valor nulo VALOR NULO?
        {
            block = QDateTime::fromString(fecha1 ,"yyyy-MM-dd HH:mm:ss");//hora del blockeo
            fecha1=block.addSecs(180).toString("yyyy-MM-dd HH:mm:ss");
            if(QString::compare(fecha1, actual,Qt::CaseInsensitive)>0){//180 segundos son 3 min
                qDebug() << "Session.cpp Error usuario blockeado espera unos minutos " ;
                xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>Error usuario blockeado espera unos minutos</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
                return xml;
            }
            else
            {
                settings.setBloqued_Time(false);
                numero_de_intentos=0;
                settings.setNoIntentos(0);
            }
        }
    }
    query = "select id_opr from operator  where id_str_rt = " + settings.getIdStore() + " and nm_opr = '" + usuario + "' and pwd_acs_opr ='" + password + "'" ;
    ok = sqlQuery.exec( query ) ;
    if(ok)
    {
        if ( !sqlQuery.first())//No existe el usuario y el password;
        {
            numero_de_intentos++;
            settings.setNoIntentos(numero_de_intentos);
            qDebug() << "Session.cpp verificar usuario, numero de intentos " << numero_de_intentos;
            if(numero_de_intentos>3){//se blockea
                qDebug() << query ;
                qDebug() << "Session.cpp usuario blockeado" << sqlQuery.lastError() ;
                xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>usuario blockeado</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
                settings.setBloqued_Time(true);
                settings.setNoIntentos(4);
                return xml;
            }
            else{
                qDebug() << "Session.cpp Error en el usuario o contraseña" ;
                xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>Error en el usuario,contraseña</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
            }
            return xml;
        }
        else
            id_opr=sqlQuery.value("id_opr").toString();
    }
    query = "select coalesce(id_opr,-1) as id_opr,id_rpsty_tnd from till where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() ;

    ok = sqlQuery.exec( query ) ;
    if (ok){
        ok = (sqlQuery.first());
        if(ok){
            id_rpsty_tnd=sqlQuery.value("id_rpsty_tnd").toString(); //se supone que tendria que ser el cajón al que regresa los depósitos
            id_opr_till=sqlQuery.value("id_opr").toInt();
            qDebug() << "LoginProcess:setLogin() cajon " << id_rpsty_tnd << " " << id_opr_till;
        }
    }
    else{
        qDebug() << "LoginProcess:setLogin() error en " << query;
    }
    if ( !sqlQuery.isValid())
    {
        qDebug() << query;
        qDebug() << "Session.cpp Error en el till " << sqlQuery.lastError() ;
        xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>Error en el till</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
        return xml;
    }
    settings.setNoIntentos(0);
    settings.setBloqued_Time(false);

    //verificar si el usuario ya tiene sesion
    if(id_opr_till > 0)
    {
        if(id_opr.toInt()!=id_opr_till){
            qDebug() << "Session.cpp Error porque EL USUARIO DE LA SESION ANTERIOR NO ES EL MISMO " << sqlQuery.lastError() ;
            xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>Error porque EL USUARIO DE LA SESION ANTERIOR NO ES EL MISMO</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
            return xml;
        }else{
            mismo_usuario=1;
        }
    }
    else
    {
        query = "update till set id_opr = "+ id_opr + " where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() + " and id_rpsty_tnd = " + id_rpsty_tnd;
        bool ok = sqlQuery.exec( query ) ;
        if (ok){
            mismo_usuario=1;
            id_opr_till = id_opr.toInt();
            hubocorte=true;
        }
        else{
            qDebug() << "Session.cpp Error en el update del till " << query ;
            xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>-1</resultado>  <resultadoMsg>Error en el update del till</resultadoMsg>  <ID_OPR></ID_OPR>  <NM_OPER></NM_OPER>  <TS_TM_STR></TS_TM_STR>  <DC_DY_BSN></DC_DY_BSN>  <AI_TRN></AI_TRN></LogInResponse>";
            return xml;
        }
    }
    //Obtiene permisos
    query = "select g.id_rs,g.ps_acs_gp_rd,g.ps_acs_gp_wr from operator o inner join operatorgroup og on og.id_opr = o.id_opr inner join groupresourceaccess g on g.id_gp_wrk = og.id_gp_wrk where o.id_str_rt = " + settings.getIdStore() + " and o.id_opr = " + id_opr;
    ok = sqlQuery.exec( query ) ;

    while( sqlQuery.next()){
        QMap<QString,QString> map;
        if(sqlQuery.isValid())
        {
        map["id_rs"]=sqlQuery.value("id_rs").toString();
        map["ps_acs_gp_rd"]= sqlQuery.value("ps_acs_gp_rd").toString();
        map["ps_acs_gp_wr"]= sqlQuery.value("ps_acs_gp_wr").toString();
        permisos.append(map);
        }
        //acceso permisos[0].value("id_rs");
    }
    if(permisos.length()==0){
        qDebug() << "session.cpp obteniendo permisos " << query ;
        qDebug() << "session.cpp no hay permisos " << sqlQuery.lastError() ;
        //return   "Error" ;
    }
    // Caso 1: La caja fue correctamente cerrada, solo en esta caso hay cambio de fecha
        // 1.- Obtener la fecha del dia, en su caso cerrar el dia.
        // 2.- Crear la transacción
        // 3.- Crear la sesión
        // 4.- Actualizar la transacción con la fecha de session
        // 5.- Actualizar el Till
        // 6.- Cerrar todas las sesiones atrasadas.
    // Caso 2: Se hizo logout pero no se hizo corte Z o Se abandono la sesion sin Logout.
        // 1.- Obtener la fecha del dia
        // 2.- Crear la transacción.
        // 3.- Crear la sesion
        // 4.- Actualizar la transaccion con la fecha de session
        // 5.- Cerrar las sessiones atrasadas
    bool Cierre_Dia = false;
    bool NuevaInst = false;
    QDateTime fecha;
    QDateTime  fecha_actual;
    fecha_actual= QDateTime::currentDateTime();
    fecha=fecha_actual;
    qDebug() << "session.cpp buscando el ultimo cierre de dia" ;
    query = "select max(dc_dy_bsn) as dc_dy_bsn from businessday where ts_end is null or ts_end = '2000-01-01 00:00:00'";
    qDebug() << "session.cpp buscando el ultimo cierre de dia " << query;
    ok = sqlQuery.exec( query ) ;
    sqlQuery.first();
    if(sqlQuery.isValid()){
        fecha=sqlQuery.value("dc_dy_bsn").toDateTime();
        fechaBusinessday = fecha;
        if(fecha.daysTo(fecha_actual) > 0){
            Cierre_Dia = hubocorte;
            qDebug() << "session.cpp fecha actual > 0 " << fecha.daysTo(fecha_actual) <<" "<< fecha << " " << fecha_actual << " Cierre_Dia " << Cierre_Dia;
        }else{
            qDebug() << "session.cpp fecha actual <= 0 " << fecha.daysTo(fecha_actual) <<" "<< fecha << " " << fecha_actual;
            Cierre_Dia = false;
        }
    }
    else{
        Cierre_Dia = false;
        NuevaInst = true;
    }
    //Caso 1
    if(Cierre_Dia){
         qDebug() << "session.cpp  cerrando el dia ";
         query = "update businessday set ts_end = '" + fecha_actual.toString("yyyy/MM/dd HH:mm:ss") + "' where ts_end is null";
         ok = sqlQuery.exec( query ) ;
         if(ok){qDebug() << "session.cpp dia cerrado ";}
     }
     if(Cierre_Dia || NuevaInst){
         qDebug() << "session.cpp abriendo dia ";
         query = "insert into businessday(DC_DY_BSN,id_str_rt,id_ws, ts_bgn) values ('" + fecha_actual.toString("yyyy/MM/dd") + "'," + settings.getIdStore() + ", " + settings.getIdWorkStation() + ", '"+ fecha_actual.toString("yyyy/MM/dd HH:mm:ss") + "')";
         ok = sqlQuery.exec( query ) ;
         if(ok){qDebug() << "session.cpp dia abierto " << query;}
         else qDebug() << "session.cpp error de dia" << query;
         query = "select max(dc_dy_bsn) as dc_dy_bsn from businessday where ts_end is null or ts_end = '2000-01-01 00:00:00'";
         qDebug() << "session.cpp buscando el ultimo cierre de dia " << query;
         ok = sqlQuery.exec( query ) ;
         sqlQuery.first();
         if(sqlQuery.isValid()){
             fechaBusinessday=sqlQuery.value("dc_dy_bsn").toDateTime();
         }
     }
     else fechaBusinessday1 = fechaBusinessday;
    //crear la transaccion de apertura de sesion
    query = "select coalesce(max(ai_trn)+1,1) as ai_trn from transactions where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() + " and dc_dy_bsn = (select max(dc_dy_bsn) from businessday where ts_end is null or ts_end = '2000-01-01 00:00:00')";
    qDebug()<< "Session.cpp set_login "<<query;
    ok = sqlQuery.exec( query ) ;
    if(sqlQuery.first())
        ai_trn =sqlQuery.value("ai_trn").toInt();
    else
        ai_trn = 1;
    qDebug()<< "Session.cpp set_login " << ai_trn << " " << QString::number(ai_trn);
    query = "insert into transactions(id_str_rt,id_ws,dc_dy_bsn,ai_trn,ty_trn,ts_trn_bgn,fl_cncl,fl_vd,fl_trg_trn,fl_key_ofl) values(" + settings.getIdStore() + "," + settings.getIdWorkStation() + ",'" +fechaBusinessday.toString("yyyy/MM/dd HH:mm:ss") + "'," + QString::number(ai_trn) + "," +  "'TIEN', '" + fechaBusinessday.toString("yyyy/MM/dd HH:mm:ss") + "',0,0,0,0)";
    ok = sqlQuery.exec( query ) ;
    if(!ok)
        qDebug() <<"session.cpp::setLogin() error " << query;
    if (Cierre_Dia || NuevaInst)
    {
        query = "update businessday set ai_trn = "+ QString::number(ai_trn) + " where dc_dy_bsn = '"+fechaBusinessday.toString("yyyy/MM/dd HH:mm:ss")+"'";
        ok = sqlQuery.exec( query ) ;
        if(!ok)
            qDebug() <<"session.cpp::setLogin() error " << query;
    }
    if(ok){qDebug() << "se creo la transaccion " <<query;}
    //se crea la sesion
    QDateTime fsession=QDateTime::currentDateTime();
    query = "insert into session(id_str_rt,id_ws,id_opr,ts_tm_str,ai_trn_bgn,dc_dy_bsn_bgn) values(" + settings.getIdStore() + ", " + settings.getIdWorkStation() + ", " + id_opr + ",'" + fsession.toString("yyyy/MM/dd HH:mm:ss") + "'," + QString::number(ai_trn) + ",'" + fechaBusinessday.toString("yyyy/MM/dd") + "')";
    qDebug() << "session.cpp se creo la transaccion " <<query;
    ok = sqlQuery.exec( query ) ;
    if(ok){qDebug() << "session.cpp se creo la session " <<query;}
    //actualizando la transaccion de apertura
    query = "update transactions set id_opr ="+ id_opr+", ts_tm_str = '" + fsession.toString("yyyy/MM/dd HH:mm:ss") + "'" + " where id_str_rt = " + settings.getIdStore() + " and id_WS = " + settings.getIdWorkStation() + " and dc_dy_bsn = '" + fechaBusinessday.toString("yyyy/MM/dd HH:mm:ss") + "' and ai_trn = " + QString::number(ai_trn);
    qDebug() << "session.cpp se creo la transaccion " <<query;
    ok = sqlQuery.exec( query ) ;
    if(ok){qDebug() << "la transaccion de apertura hecha con exito" <<query;}
    fecha_actual = QDateTime::currentDateTime();
    //todos los datos de tienda;
    query = "select * from retailStore where id_str_rt = " + settings.getIdStore();
    qDebug() << "session.cpp se creo la transaccion " <<query;
    ok = sqlQuery.exec( query ) ;
    sqlQuery.first();
    ts_tm_str=QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss");//inicio de sesion
    ts_end ="";//fin de sesione
    trn_bgn = QString::number(ai_trn);// primera transaccion
    trn_end ="";//ultima transaccion
    bsn_bgn =fsession.toString("yyyy/MM/dd HH:mm:ss");//fecha de primera transaccion
    id_end ="";//fecha de la ultima transaccion
    //settings.setIdOpr(id_opr.toInt());
    NM_STR_RT=sqlQuery.value("nm_str_rt").toString();
    qDebug() << "session.cpp se creo la transaccion " <<NM_STR_RT;
    DOMICILIO=sqlQuery.value("DOMICILIO").toString();
    COLONIA=sqlQuery.value("COLONIA").toString();
    CIUDAD=sqlQuery.value("CIUDAD").toString();
    ESTADO=sqlQuery.value("ESTADO").toString();
    PAIS=sqlQuery.value("PAIS").toString();
    CP=sqlQuery.value("CP").toString();
    OPERADOR=usuario;
    xml="<LogInResponse>  <Oper>Login</Oper>  <resultado>1</resultado>  <resultadoMsg>Exito</resultadoMsg>  <ID_OPR>"+id_opr+"</ID_OPR>  <NM_OPER>"+usuario+"</NM_OPER>  <TS_TM_STR>"+fsession.toString("yyyy/MM/dd HH:mm:ss")+"</TS_TM_STR>  <DC_DY_BSN>"+fechaBusinessday.toString("yyyy/MM/dd")+"</DC_DY_BSN>  <AI_TRN>1</AI_TRN>  <NM_STR_RT>"+sqlQuery.value("nm_str_rt").toString()+"</NM_STR_RT>  <DOMICILIO>"+sqlQuery.value("DOMICILIO").toString()+"</DOMICILIO>  <COLONIA>"+sqlQuery.value("COLONIA").toString()+"</COLONIA>  <CIUDAD>"+sqlQuery.value("CIUDAD").toString()+"</CIUDAD>  <ESTADO>"+sqlQuery.value("ESTADO").toString()+"</ESTADO>  <PAIS>"+sqlQuery.value("PAIS").toString()+"</PAIS>  <CP>"+sqlQuery.value("CP").toString()+"</CP></LogInResponse>";
    qDebug() << "session.cpp xml exito " << xml;
    return xml;
}

QString session::login_operador(QString usuario, QString password)
{
    qDebug()<< "Session.cpp login_operador() usuario y password "  << usuario << password << " como operador";
    QSqlDatabase sql;

    QString xml="";
    if (usuario == "")
    {
        qDebug() << "usuario setlogin Vacio";
        return "error";
    }
    if (password == "")
    {
        qDebug() << "password setlogin Vacio" ;
        return "error";
    }

    sqlDatabasebut = sql;
    id_opr_sup = "";
    QSqlQuery sqlQuery( sqlDatabasebut.database( "Origen") )  ;
    QString query = "select o.id_opr from operator o,operatorgroup g  where o.id_str_rt = " + settings.getIdStore() + " and o.nm_opr = '" + usuario + "' and o.pwd_acs_opr ='" + password + "' and g.id_opr = o.id_opr and g.id_gp_wrk = 2";
    bool ok = sqlQuery.exec( query ) ;
    if (ok){
        sqlQuery.first();
        if(sqlQuery.isValid()){
            xml="<ValidateSupervisor>  <Oper>ValidateSupervisor</Oper>  <resultado>1</resultado>  <resultadoMsg>Es supervisor</resultadoMsg>  <ID_OPR>"+sqlQuery.value("id_opr").toString()+"</ID_OPR></ValidateSupervisor>";
            id_opr_sup = sqlQuery.value("id_opr").toString();     
            query = "select g.id_rs,g.ps_acs_gp_rd,g.ps_acs_gp_wr from operator o inner join operatorgroup og on og.id_opr = o.id_opr inner join groupresourceaccess g on g.id_gp_wrk = og.id_gp_wrk where o.id_str_rt = "+settings.getIdStore()+" and o.id_opr = "+id_opr_sup;
            ok = sqlQuery.exec( query ) ;
            while(sqlQuery.next()){
                QMap<QString,QString> map;
                    map["id_rs"]=sqlQuery.value("id_rs").toString();
                    map["ps_acs_gp_rd"]= sqlQuery.value("ps_acs_gp_rd").toString();
                    map["ps_acs_gp_wr"]= sqlQuery.value("ps_acs_gp_wr").toString();
                    permisosadmin.append(map);
            }
            return xml;
        }
        else{
            xml="<ValidateSupervisor>  <Oper>ValidateSupervisor</Oper>  <resultado>-1</resultado>  <resultadoMsg>No es supervisor</resultadoMsg>  <ID_OPR>0</ID_OPR></ValidateSupervisor>";
            return xml;
        }
    }
    else{
        qDebug() << "session.cpp error en la base de datos";
    }
    return "";
}

QString session::get_cortez(QSqlDatabase sql)
{
    sqlDatabasebut = sql;
    //qDebug() << "dbName = " << settings.getDbName() << " User = " << settings.getUser() << " Password = " << settings.getPassword() ;
    qDebug() << "Session.cpp, get_cortez" ;

    qDebug() << "misma maquina" ;
    QSqlQuery sqlQuery( sqlDatabasebut.database( "Origen") )  ;

    QString query = "select ai_trn, xml from transactions where ty_trn = 'CORTE' and FL_KEY_OFL = 1 LIMIT 0, 1";
    bool ok = sqlQuery.exec( query ) ;
    if(ok){
    QString tmp=sqlQuery.value("xml").toString();
    QString ai_trn =sqlQuery.value("ai_trn").toString();
    int f = tmp.indexOf("<Cortes>");
    tmp = tmp.replace(f,8, "");
    f = tmp.indexOf("</Cortes>");
    tmp = tmp.replace(f,9, "");
    f = tmp.indexOf("<AI_TRN>")+8;
    int f2 = tmp.indexOf("</AI_TRN>");
    QString ai_trnxml=tmp.mid(f,f2-f);//ai_trn del xml
    if(ai_trnxml.toInt() != ai_trn.toInt()){
           tmp = tmp.mid(0,tmp.indexOf("<AI_TRN>")+8)+ai_trn+tmp.mid(f2);
    }

    return tmp;
    }
    else{
        qDebug() << "error en la base de datos" ;
        return "error";
    }

}

void session::logout(int ultima_trn)
{
    int ai_trn_sesion = 0;
    QDateTime fechaSesion;

    QSqlQuery sqlQuery( sqlDatabasebut.database( "Origen") )  ;

    QString query =  "select * from session where id_str_rt = " + id_str_rt + " and id_ws = " + id_ws ;
    query += " and id_opr = " + id_opr + " and ts_tm_str = ";
    query+="(select max(ts_tm_str) from session where id_str_rt = " + id_str_rt + " and id_ws = " + id_ws + " and id_opr = " + id_opr + " ) ";
    bool ok = sqlQuery.exec( query ) ;
    sqlQuery.first();
    if(sqlQuery.isValid()){
        if(sqlQuery.value("ai_trn_bgn").toString()!=""){
            ai_trn_sesion=sqlQuery.value("ai_trn_bgn").toInt();
            fechaSesion=QDateTime::fromString(sqlQuery.value("ts_tm_str").toString(),"yyyy/MM/dd HH:mm:ss");
        }
        qDebug() << "session.cpp logout update session";
        QString query = "update session set ai_trn_end = " + QString::number(ultima_trn) + ",dc_dy_bsn_end = '" + QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss")  + "', ts_end = '" + QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss")  + "' where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() + " and id_opr = " + this->id_opr + " and ts_tm_str = '" + fechaSesion.toString("yyyy/MM/dd HH:mm:ss") + "'";
        qDebug() << "session.cpp::antes del logout" << query;
        ok = sqlQuery.exec( query ) ;
        qDebug() << "session.cpp::despues del logout" << query;
    }
    else{qDebug() << "session.cpp::logout() error al dar de baja al usuario" << query;}
}

void session::blockeo()
{
}

QString session::desblockeo(QString usuario, QString password, QSqlDatabase sql){
return "";
}


