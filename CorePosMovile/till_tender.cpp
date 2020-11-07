#include "till_tender.h"
#include "till.h"
//#include "loginprocess.h"
#include <QDebug>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>
#include <QEventLoop>
#include <QTimer>
#include "utilerias.h"



till_tender::till_tender(QObject *parent) :
    QObject(parent)
{
    settings.setUp();
    ty_tnd = "";
    tenderlistprepared=false;
}

bool till_tender::addTillTender(RT_LineItem* linea, QString signo){
    bool ret;
    Utilerias u;

    ret = false;
    if(linea->get_ty_ln_item() == "TE")
    {
        ret=addTillTender(linea->get_ty_tnd(),0, u.FormatoNumero(linea->get_total_pagado(),8,2),signo);
    }
    else
        if(linea->get_ty_ln_item()=="CH")
        {
            ret=addTillTender(linea->get_ty_tnd(),1,u.FormatoNumero(linea->get_total_cambio(),8,2),signo);
        }
        else
            ret = true;
    return ret;
}

bool till_tender::addTillTender(QString ty_tnd, int ty_trn,QString monto, QString signo){

    QSqlDatabase sqldatabasetill; // El acceso es a traves del driver de ODBC
    QString campo="";

    QSqlQuery sqlQueryt( sqldatabasetill.database("Origen") );
    QString Query ="select * from tilltender where id_str_rt = "+settings.getIdStore()+" and id_ws = "+settings.getIdWorkStation()+" and ty_tnd = '"+ty_tnd+"'";
    qDebug() << "till_tender::addTillTender " << Query;

    bool ok = sqlQueryt.exec( Query ) ;
    sqlQueryt.first();
    if(!sqlQueryt.isValid()){
        QSqlQuery sqlQuery( sqldatabasetill.database("Origen") );
        Query= "insert into tilltender values ("+settings.getIdStore()+",1,"+settings.getIdWorkStation()+",'"+ty_tnd+"',0,0,0,0,0,0,0)";
        qDebug() << "No existe la entrada en tilltender asi que se crea con ceros " << Query;
        ok = sqlQuery.exec( Query ) ;
        if(!ok){
            qDebug() << "addtilltender:: error al hacer el insert nuevo";
            return false;
        }
    }
    if(ty_trn==0){
        campo="total_ingresos";
    }
    if(ty_trn==1){
        campo="total_cambios";
    }
    if(ty_trn==2){
        campo="total_depositos";
    }
    if(ty_trn==3){
        campo="total_retiros";
    }
    if(ty_trn==4){
        campo="total_pagos_menores";
    }
    if(ty_trn==5){
        campo="total_cobros_menores";
    }
    if(ty_trn==6){
        campo="total_envios";
    }
    if(ty_trn==7){
        campo="total_enviosd";
    }
    if(ty_trn==8){
        campo="total_pagos";
    }

    QSqlQuery sqlQueryt2( sqldatabasetill.database("Origen") );
    if(signo=="+")
        Query = "update tilltender set "+campo+" = "+campo+"+"+monto+" where id_str_rt = "+settings.getIdStore()+" and id_ws = "+settings.getIdWorkStation()+" and ty_tnd = '"+ty_tnd+"'";
    else
        Query = "update tilltender set "+campo+" = "+campo+"-"+monto+" where id_str_rt = "+settings.getIdStore()+" and id_ws = "+settings.getIdWorkStation()+" and ty_tnd = '"+ty_tnd+"'";
    qDebug() << "till_tender::addTillTender" << Query;
    ok = sqlQueryt2.exec( Query );
    sqldatabasetill.close();
    return ok;
}

QMap<QString,QVariant> till_tender::valida_Operacion(QString ty_tnd, double monto, double monto_cobro, QMap<QString,QVariant> capturas){

    //2020 PAGO

    QMap <QString,QVariant> resultado;
    resultado["resultado"] = "";
    resultado["mensaje"] = "";
    resultado["cambio"] ="";
    QString resultado2;

    QSqlDatabase sqldatabasetillt;
    QSqlQuery sqlQuery( sqldatabasetillt.database("Origen") );
    QString query ="select * from tender where ty_tnd='"+ty_tnd+"'";
    qDebug() << "till_tender::valida_Operacion; " << query;
    bool ok = sqlQuery.exec( query ) ;
    if(ok)ok=sqlQuery.first();
    if(!ok){
        if(!altaformapago(ty_tnd))
        {
            resultado["resultado"]="false";
            resultado["mensaje"]="Error, ,no existe la forma de pago";
            return resultado;
        }
        else
        {
            ok = sqlQuery.exec( query ) ;
            if(ok)ok=sqlQuery.first();
        }
    }
        //si el cambio es mayor almonto maximo
        if(monto_cobro-monto > sqlQuery.value("mo_th_tnd_chn").toDouble()){
            resultado["resultado"]="false";
            resultado2="No se puede devolver mas de "+sqlQuery.value("mo_th_tnd_chn").toString()+"$";
            resultado["mensaje"]=resultado2;
            sqldatabasetillt.close() ;
            return resultado;
        }
        if(sqlQuery.value("fl_nmb_srz").toInt()==1){
            if(capturas.value("n_cheke").toString().compare("")==0){//si no se capturo
            resultado["mensaje"]="Necesita cobrar el numero de cheque, o un folio";
            resultado["resultado"]="false";
            sqldatabasetillt.close() ;
            return resultado;
            }
            else{
                resultado2+=" requiere el endoso del chequee";
                //resultado["mensaje"]+=" requiere el endoso del checke";
                resultado["resultado"]="true";
            }
        }

        if(sqlQuery.value("fl_azn_rq").toInt()==1){
            if(capturas.value("autorizacion").toString().compare("")==0){//si no se capturo
            resultado["mensaje"]=" se necesita un proceso de autorizacion";
            resultado["resultado"]="false";
            sqldatabasetillt.close() ;
            return resultado;
            }
            else{
                resultado2+=" ,correcto";
                //resultado["mensaje"]+=" ,correcto";
                resultado["resultado"]="true";
            }
        }

        if(sqlQuery.value("fl_dt_azn_ep_rq").toString().compare("N")==0){//0 es igual
            resultado2+=" este tipo de pago requiere que se valide la fecha de expiracion y registrarse";
            //resultado["mensaje"]+=" este tipo de pago requiere que se valide la fecha de expiracion y registrarse";
            resultado["resultado"]="false";

        }
        /*tiempo de espera permitido
        if(sqlQuery.value("in_wit_azn_mxm_alow")){//no hay comparacion aun

        }*/
        if(sqlQuery.value("fl_idtn_rq_ct").toInt()==1){
            resultado2+=" Necesita mostrar identificacion oficial";
               // resultado["mensaje"]+=" Necesita mostrar identificacion oficial";
                resultado["resultado"]="true";

        }

        if(sqlQuery.value("fl_id_prsl_rq").toInt()==1){
             resultado2+=" SE necesita introducir un pin";
                //resultado["mensaje"]+=" SE necesita introducir un pin";
                resultado["resultado"]="true";

        }
        if(sqlQuery.value("fl_sgntr_ct_rq").toInt()==1){
            resultado2+=" requier que se firme el vaucher resultante";
               // resultado["mensaje"]+=" requier que se firme el vaucher resultante";
                resultado["resultado"]="true";

        }
        if(sqlQuery.value("fl_avlb_lcl_cny").toInt()==1){
            resultado2+=" CAMBIO ";
           // resultado["mensaje"]+=" CAMBIO ";
                resultado["resultado"]="true";
                //abrir caja
                if(monto-monto_cobro<=0){
                    resultado["cambio"]=monto_cobro-monto;
                    qDebug() << "till_tender::valida_Operacion hay cambio" << monto << " - " << monto_cobro << " = " << resultado["cambio"];
                }
        }
        resultado["mensaje"]=resultado2;
        qDebug()<< "till_tender::valida_Operacion() -- TERMINA PROCESO DE PAGOS --";
        sqldatabasetillt.close() ;
        return resultado;
}

bool till_tender::altaformapago(QString wty_tnd)
{
    bool ret=true;
    QSqlDatabase sqldatabasetillt;
    QSqlQuery sqlQuery( sqldatabasetillt.database("Origen") );
    /*
    ty_tnd = tipo de forma de pago
    id_act_ldg = id de la cuenta contable
    id_cny = id de la moneda
    de_tnd = descripcion de la forma de pago
    fl_nmb_srz = la forma de pago requiere un numero de seria
    fl_azn_rq = requiere un proceso de autorización
    lu_mth_azn = método de autorizacion
    fl_dr_azn_ep_rq = requiere se valide la fecha de expiración
    in_wit_azn_mxm_alow = tiempo máximo de espera para lograr las autorizaciones
    fl_idtn_rq_ct = requiere identificacion
    fl_id_prsl_rq =requiere introducir un pin
    fl_avlb_lcl_cny = se puede dar cambio en esta forma de pago
    fl_sgntr_ct_rq = requiere firmar
    mo_th_tnd_chn = monto máximo en esta forma de pago
    fl_drw_open = abrira el cajon de dinero;
    plazos = venta a plazos
    id_itm_ps = articulo si existe un cargo en esta forma de pago
    btn_asigned = boton asignado
    food_stamp_ex = si es food stamp
     */
    QString query ="insert into tender (ty_tnd_act_ldg, id_cny, de_tnd, fl_nmb_srz, fl_azn_rq, lu_mth_azn, ";
    query+="in_wit_azn_mxm_alow, fl_idtn_rq_ct, fl_id_prsl_rq, fl_avlb_lcl_cny, fl_sgntr_ct_rq, mo_th_tnd_chn, fl_drw_open, ";
    query+="plazos, id_itm_ps, btn_asigned) values ("+wty_tnd+"NULL,1,";

    if(wty_tnd=="CASH") query+= "'Efectivo', 0, 0, '', 0, 0, 0, 0, 1, 0, 999.99, 1, '', NULL, 'CASH')";
    else
    {
        ret=false; //quitar si se quieren añadir otras formas de pago
        if(wty_tnd== "CCAR") query+= "'T. de Crédito', 0, 1, 'TC', 1, 15, 1, 1, 0, 1, 0, 0, '', NULL, 'CCAR')";
        else
        {
            if(wty_tnd == "CHEC") query += "'Cheque', 1, 0, '', 0, 0, 1, 0, 0, 1, 0, 0, '', NULL, 'CHEC')";
            else
            {
                if(wty_tnd == "VALE") query+="'Vale', 1, 0, '', 0, 0, 1, 0, 0, 1, 0, 0, '', NULL, 'vale')";
                else
                {
                    if(wty_tnd=="FDST") query+= "'Food Stamp', 0, 1, 'TC', 1, 15, 1, 1, 0, 1, 0, 0, '', NULL, 'FDST')";
                    else ret = false;
                }
            }
        }
    }
    if(ret)
    {
        sqlQuery.exec( query ) ;
    }
    return ret;
}


void till_tender::revision(QMap<QString,QVariant> capturas){//pruebas

    //Este no se para que se usa
    QSqlDatabase sqldatabasetill;
    bool okd;
    QSqlQuery sqlQueryt( sqldatabasetill.database("Origen") );
    qDebug()<<"le llegaron las capturas";
    QString query ="select * from tilltender where id_str_rt = "+settings.getIdStore() +"and id_ws = "+settings.getIdWorkStation()+" and ty_tnd = 'CASH'";
    okd=sqlQueryt.exec(query);
    sqlQueryt.first();

    qDebug()<<"la del cash regresa " << sqlQueryt.size() << sqlQueryt.isValid();

    QSqlQuery sqlQueryt2( sqldatabasetill.database("Origen") );

    QString query2 ="select * from tilltender where id_str_rt = " + settings.getIdStore()+"and id_ws = "+settings.getIdWorkStation()+" and ty_tnd = 'CASHs'";
    okd=sqlQueryt2.exec(query2);
    sqlQueryt2.first();

    qDebug()<<"till_tender:rebision() la del nocash regresa " << sqlQueryt2.size() << sqlQueryt2.isValid();

}

bool till_tender::searchTender(QString wty_tnd)
{
    if(wty_tnd == ty_tnd) return true;
    QSqlDatabase sqldatabasetillt;
    QSqlQuery sqlQuery( sqldatabasetillt.database("Origen") );
    QString query ="select * from tender where ty_tnd ='" + wty_tnd + "'";
    sqlQuery.exec(query);
    qDebug() << "till_tender::searchTender query: " << query;
    if(sqlQuery.first())
    {
        ty_tnd = wty_tnd;
        id_act_ldg = sqlQuery.value("de_tnd").toInt();
        id_cny = sqlQuery.value("de_tnd").toInt();
        id_itm = sqlQuery.value("id_itm_ps").toInt();
        de_tnd = sqlQuery.value("de_tnd").toString();
        fl_nmb_srz = sqlQuery.value("fl_nmb_srz").toBool();
        fl_azn_rq = sqlQuery.value("fl_azn_rq").toBool();
        lu_mth_azn = sqlQuery.value("lu_mth_azn").toString();
        fl_dt_azn_ep_rq = sqlQuery.value("fl_dt_azn_ep_rq").toString() == "S";
        fl_idtn_rq_ct = sqlQuery.value("fl_idtn_rq_ct").toBool();
        fl_id_prsl_rq = sqlQuery.value("fl_id_prsl_rq").toBool();
        fl_avlb_lcl_cny = sqlQuery.value("fl_avlb_lcl_cny").toBool();
        fl_sgntr_ct_rq = sqlQuery.value("fl_sgntr_ct_rq").toBool();
        mo_th_tnd_chn = sqlQuery.value("mo_th_tnd_chn").toFloat();
        fl_drw_open = sqlQuery.value("fl_drw_open").toBool();
        mo_apvl_tndce_off = sqlQuery.value("mo_apvl_tndce_off").toFloat();
        plazos = sqlQuery.value("plazos").toBool();
        btn_asigned = sqlQuery.value("btn_asigned").toBool();
        return true;
    }
    else
    {

        return false;
    }
}

QStringList till_tender::tenderlist(int modo, QString wty_tnd){

    QSqlDatabase sqldatabasetillt;
    QSqlQuery sqlQuery( sqldatabasetillt.database("Origen") );
    QString query ="select ty_tnd, de_tnd from tender;";
    QStringList res;

    res.clear();
    if(modo != 3)
    {
        sqlQuery.exec( query ) ;
        while (sqlQuery.next())
        {
            ty_tnd=sqlQuery.value("ty_tnd").toString();
            if (ty_tnd=="CASH")
                res.append("CASH Efectivo");
            else if (ty_tnd == "CCAR")
                res.append("CCAR");
            else if (ty_tnd == "CHEC T.Crédito/Deb")
                res.append("CHEC");
            else if (ty_tnd=="VALE")
                res.append("VALE Vale");
            else if (ty_tnd == "FDST")
                res.append("FDST, FoodStamp");
            else res.append(ty_tnd + " " + sqlQuery.value("de_tnd").toString());
        }
    }
    else
    {
        if(searchTender(wty_tnd)) res.append(ty_tnd + " " + de_tnd);
    }
    return res;
}

int till_tender::tenderlist_prepare(char tipo){

        //tipo 'A' = Todos
        //Cambio 'B' = solo los que pueden dar cambio.
        //Otros 'O' = otras formas de pago que no van en los botones;
        QString xml="";
        QString query="";
        QSqlDatabase sqldatabase;
        int Contador = 0;

        QSqlQuery sqlQuery( sqldatabase.database("Origen") )  ;
        query="select ty_tnd, de_tnd from tender";
        if(tipo=='O') query+=" where ty_tnd not in ('CASH', 'CCAR', 'VALE', 'CHEC')";
        else if(tipo == 'B') query+=" where MO_TH_TND_CHN > 0";
        query+=" order by TY_TND";
        qDebug() << "till_tender.cpp::tenderlist_prepare query: "<<query;
        tenderlistprepared=true;
        if (sqlQuery.exec( query ))
        {
            while(sqlQuery.next()){
                Contador++;
                xml+="<Tender><TY_TND>"+sqlQuery.value("ty_tnd").toString()+"</TY_TND><DE_TND>"+sqlQuery.value("de_tnd").toString()+"</DE_TND></Tender>";
            }
            xml="<TenderList><Oper>TenderList</Oper><resultado>1</resultado><resultadoMsg>Exito</resultadoMsg>"+xml+"</TenderList>";
            if(Contador == 0)
            {
                xml = "";
            }
            xmlResultado = xml;
        }
        else
        {
            xmlResultado = "";
        }
        return Contador;
}

QString till_tender::get_tenderlist(char tipo)
{
    if(!tenderlistprepared) tenderlist_prepare(tipo);
    qDebug() << "till_tender::tenderlist_prepare() " << xmlResultado;
    return xmlResultado;
}

QMap<QString, QVariant> till_tender::getPropertiesTender(QString wty_tnd){

    QMap<QString, QVariant> ret;
    if(searchTender(wty_tnd))
    {
        ret["ty_tnd"]= ty_tnd;
        ret["id_act_ldg"]= id_act_ldg;
        ret["id_cny"]=id_cny;
        ret["id_itm"]=id_itm;
        ret["de_tnd"]=de_tnd;
        ret["fl_nmb_srz"]=fl_nmb_srz;
        ret["fl_azn_rq"]=fl_azn_rq;
        ret["lu_mth_azn"]=lu_mth_azn;
        ret["fl_dt_azn_ep_rq"]=fl_dt_azn_ep_rq;
        ret["fl_idtn_rq_ct"]=fl_idtn_rq_ct;
        ret["fl_id_prsl_rq"]=fl_id_prsl_rq;
        ret["fl_avlb_lcl_cny"]=fl_avlb_lcl_cny;
        ret["fl_sgntr_ct_rq"]=fl_sgntr_ct_rq;
        ret["mo_th_tnd_chn"]=mo_th_tnd_chn;
        ret["fl_drw_open"]=fl_drw_open;
        ret["mo_apvl_tndce_off"]=mo_apvl_tndce_off;
        ret["plazos"]=plazos;
        ret["btn_asigned"]=btn_asigned;

    }
    else
        ret["ty_tnd"]= "";
    return ret;
}



