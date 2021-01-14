#include "principal.h"


principal::principal(int a){


}
void principal::init_principal(){
    qDebug()<<"paso 1 new retailtrasaction()";
    tiket = new retail_Transaction();
    modoventa = true;
    qDebug()<<"paso 2 inicializar settings()";
    settings.setUp();
    sqldatabasecortex =QSqlDatabase::addDatabase("QSQLITE","Origen"); // El acceso es a traves del driver de ODBC
    sqldatabasecortex.setDatabaseName("pruebas");
    if(!sqldatabasecortex.open()){
        qDebug() << "Error syncronizacion 1: "; //<< sqldatabasecortex.lastError();
    }
    qDebug()<<"paso 3 inicializar  taxs()";
    Taxes = new RT_Total_Tax(true);
    qDebug()<<"paso 4 inicializar el ticket";
    tiket->inicializar(settings.getDesglosaImpuestos()=="TRUE", Taxes);
    qDebug()<<"paso 5 inicializar los datos del ticket";

    datos_ticket.inicializar();
    //sesion_actual.setLogin("usuarion","usuarion");


}
principal::principal()
{
tiket = new retail_Transaction();
modoventa = true;
settings.setUp();
sqldatabasecortex =QSqlDatabase::addDatabase("QSQLITE","Origen"); // El acceso es a traves del driver de ODBC
sqldatabasecortex.setDatabaseName("pruebas");
if(!sqldatabasecortex.open()){
    qDebug() << "Error syncronizacion 1: "; //<< sqldatabasecortex.lastError();
}
Taxes = new RT_Total_Tax(true);
tiket->inicializar(settings.getDesglosaImpuestos()=="TRUE", Taxes);
datos_ticket.inicializar();
//sesion_actual.setLogin("usuarion","usuarion");

}

void principal::estado_Mesa(int lista, int mesa,QString modelo,int estado){
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson("{\"arreglo\":"+modelo.toUtf8()+"}");
    QStringList valores;
    QString a,b;
    if(!doc.isNull())
       {
           if(doc.isObject())
           {
               obj = doc.object();
               qDebug() << "Documento correcto";
           }
           else
           {
               qDebug() << "Document is not an object";
               return;
           }
       }
       else
       {
           qDebug() << "Invalid JSON...\n" ;
           return;
       }
    QJsonArray npcArray = obj["arreglo"].toArray();
    QVariantList listal=npcArray.toVariantList();
    //QMap Listall =listal[0].toMap();
    for(int x=0;x<listal.size();x++){
         //QJsonObject npcObject =npcArray[x].toObject();
        QMap<QString,QVariant> v=listal.at(x).toMap();
        qDebug()<<v<<" antes";
        if(v["idMesa"].toInt()==mesa){
             //npcArray[x].toObject()["status"]=estado;
             v["status"]=estado;
             listal[x]=v;
             qDebug()<<listal[x];
             //doc.setArray(npcArray);
             //qDebug() <<doc.toJson();
             actualizaMesa(lista,listal );
         }
        //qDebug() << npcObject["idMesa"] << " mesa " << lista <<" " << mesa;
    }

}

int principal::itemsearchPrepare(QVariant value)
{
    return item.itemsearchPrepare(value);
}

QVariant principal::itemsearch()
{
    return item.itemsearch();
}

QString principal::itemsearch_getPosidentity()
{
    return item.itemsearch_getPosidentity();
}

QString principal::itemsearch_getQfr(){
    return item.itemsearch_getQfr();
}

QString principal::buttonsRoot()
{
    getbuttons b;
    return b.traerBotonesRoot() ;
}

QString principal::buttonsAg(QString id_parent)
{
    getbuttons b;
    return b.traerBotonesA(id_parent) ;
}

QString principal::buttonsPr(QString id_parent)
{
    getbuttons b;
    return b.traerBotonesB(id_parent) ;
}

QString principal::buttonsParent(QString id_parent)
{
    getbuttons b;
    return b.traerPadreDePadre(id_parent) ;
}

QVariant principal::set_selected(QString posidentity, QString posidentity_qfr, double cantidad)
//2020 Esta funcion encuentra el articulo de venta
{
    Item* articulo;
    RT_LineItem* rt_lineitem;
    QMap<QString,QVariant> resultado;
    int cantidad1;
    double fracciones;
    bool fraccional;

    qDebug() << ".cpp chacon lookitem 1 " << posidentity << " " << posidentity_qfr;
    articulo = new Item();
    cantidad1 = cantidad;
    fracciones = cantidad-cantidad1;
    fraccional = (fracciones > .001);
    last_set_selected_result= 1;
    if(articulo->search_items(posidentity ,posidentity_qfr)){
        if(fraccional)
        {
            if(articulo->lu_cnt_sls_wt_un != "WT")
            {
                qDebug() << ".cpp Articulo no encontrado " << QString::number(fracciones,'f',6) << articulo->lu_cnt_sls_wt_un;
                resultado["respuesta"]=-1;
                delete articulo;
                articulo = NULL;
                last_set_selected_result=-1;
                return resultado;
            }

        }
        rt_lineitem = new RT_LineItem(articulo, cantidad, Taxes, tiket->getflDevolucion());
        resultado=tiket->add_line(rt_lineitem);
        resultado["respuesta"]=1;
    }
    else{
        last_set_selected_result=0;
        qDebug() << ".cpp Articulo no encontrado ";
        resultado["respuesta"]=0;
        delete articulo;
        articulo=NULL;
    }
    return resultado;
}

int principal::getNumeroLineas()
{
    int ret;
    if (tiket==NULL)
        ret = 0;
    else ret = tiket->getNumeroLineas();
    qDebug() << "::getNumeroLineas() "<<ret;
    return ret;
}


QVariant principal::validacion(QVariant values)
{
    //2020 esta validacion se corre en el momento del pago.
    QMap<QString,QVariant> lol;
    Utilerias u;

    lol=values.toMap();
    till_tender tender;
    qDebug() << "::validacion" <<lol.value("a_pagar").toString() << lol.value("forma_de_pago").toString() << lol.value("monto").toString() << lol.value("n_cheke").toString() << lol.value("id_cheke").toString() << lol.value("tipo_id").toString() << lol.value("banco_cheke").toString();
    QMap<QString,QVariant> resultado = tender.valida_Operacion(lol.value("forma_de_pago").toString(),lol.value("a_pagar").toDouble(),lol.value("monto").toDouble(),lol);
    lol.insert("mensaje",resultado.value("mensaje"));
    lol.insert("resultado",resultado.value("resultado"));
    lol.insert("cambio",u.FormatoNumero(resultado.value("cambio").toString(),6,2));
    return QVariant(lol);
}

QVariant principal::do_pay(QVariant value){

    //2020 hace el pago

    QMap<QString,QVariant> pay_info;
    QMap<QString,QVariant> respuesta;
    //line linea_pago;
    RT_LineItem* rt_lineitem;

    //QString titulo_linea = "Pago en "+pay_info.value("forma_de_pago").toString();
    QString tipo;
    pay_info=value.toMap();
    tipo=pay_info.value("ty_tnd").toString();
    qDebug() << "()::do_pay() " << tipo << pay_info.value("monto").toDouble();
    if(tipo.compare("CASH")==0)
    {
        rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), false);
    }
    else
    {
        if(tipo.compare("CCAR")==0){
            rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), false);
        }
        else
        {
            if(tipo.compare("CHEC")==0){
                rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), pay_info.value("tipo_id").toString(), pay_info.value("n_cheke").toString(), pay_info.value("id_cheke").toString());
            }
            else
            {
                if(tipo.compare("FDST")==0){
                    rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), false);
                }
                else
                {
                    if(tipo.compare("VALE")==0){
                        rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), false);
                    }
                    else
                    {
                        rt_lineitem = new RT_LineItem(tipo, pay_info.value("monto").toDouble(), false);
                    }
                }
            }
        }
    }
    qDebug() << "::do_pay linea insertada de pago b";
    respuesta=tiket->add_line(rt_lineitem);
    if(pay_info.value("monto").toDouble()>=pay_info.value("a_pagar").toDouble()){
        respuesta["cambio"]=pay_info.value("monto").toDouble()-pay_info.value("a_pagar").toDouble();
        respuesta["ty_tnd"]=pay_info.value("ty_tnd").toString();
        respuesta["respuesta"]=1;//termino de pagar
        respuesta["accepted"]=true;
    }
    else{respuesta["respuesta"]=0;//se pago a medias
        qDebug() << "::do_pay se pago " <<respuesta.value("a_pagar");
        respuesta["accepted"]=true;
    }
    return respuesta;
}

QVariant principal::put_change(QVariant value){
    QMap<QString,QVariant> pay_info;
    QMap<QString,QVariant> respuesta;
    RT_LineItem* rtlineitem;

        pay_info=value.toMap();
        if(pay_info.value("cambio").isValid()&&pay_info.value("cambio").toDouble()>0){
            qDebug() << "::put_change() hay cambio " <<pay_info.value("cambio").toString() << " " << pay_info.value("cambio").toDouble();
            //rtlineitem = new RT_LineItem(pay_info.value("ty_tnd").toString(),pay_info.value("cambio").toDouble(),true);
            rtlineitem = new RT_LineItem("CASH",pay_info.value("cambio").toDouble(),true);
            respuesta =tiket->add_line(rtlineitem);
            respuesta["respuesta"]=1;//termino de pagar
            respuesta["accepted"]=true;
        }
        else
        {
            if(pay_info.value("cambio").isValid()&&pay_info.value("cambio").toDouble()==0)
            {
                respuesta["respuesta"]=2;//No termino de pagar
                respuesta["accepted"]=true;}
            else
            {
                respuesta["respuesta"]=0;//No termino de pagar
                respuesta["accepted"]=true;
            }
        }
    return respuesta;
}

QVariant principal::finish_ticket(int is_cancelacion,QVariant cliente){


    QMap<QString,QVariant> clientet = cliente.toMap();
    QString xmlt2 =tiket->do_transaction();
    QString dia_trabajo = "";
    int ai_trn2=0;
    QString TS_TRN_BGN="";
    QString TS_TRN_END="";
    TS_TRN_BGN=tiket->get_ts_trn_bgn();
    TS_TRN_END=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    int training=0;
    if(settings.getTraining().compare("true")==0){
        training=1;
    }
    QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") )  ;
    QString query ="select coalesce( max(dc_dy_bsn) ,'2000-01-01 00:00:00') as dc_dy_bsn from transactions";
    bool ok = sqlQuery.exec( query ) ;
    sqlQuery.first();
    dia_trabajo=sqlQuery.value("dc_dy_bsn").toString();
    qDebug() << "finish_ticket() resultado 1 " << dia_trabajo;
    QSqlQuery sqlQuery2( sqldatabasecortex.database("Origen") );
    query ="select coalesce(max(ai_trn),0) as trn from transactions where  dc_dy_bsn = '"+dia_trabajo+"'";

        ok = sqlQuery2.exec( query ) ;
        sqlQuery2.first();
        ai_trn2 = sqlQuery2.value("trn").toInt()+1;
        qDebug() << "loginproces::finish_ticket() resultado 2 " << ai_trn2;
        qDebug() << "loginproces::finish_ticket()\n" << tiket->string_impresion ;
        impresion_dep(tiket->string_impresion,1,ai_trn2,TS_TRN_BGN,settings.getIdWorkStation().toInt());
        //xml del ticket
        QString xmlt ="<?xml version=\"1.0\"?><WriteRetailTransaction><Oper>WriteRetailTransaction</Oper>";
            xmlt+="<id_instancia>"+settings.getIdInstancia()+"</id_instancia><RetailTransaction>";
            xmlt+="<Cliente><id_ct>"+clientet.value("ID_CT").toString()+"</id_ct><CV_CT>"+clientet.value("CV_CT").toString()+"</CV_CT><NM_CT>"+clientet.value("nm_cliente").toString()+"</NM_CT><organizacion><RFC_TAXID>"+clientet.value("RFC_TAXID").toString()+"</RFC_TAXID></organizacion>";
            xmlt+="<FAddress><DOMICILIO>"+clientet.value("DOMICILIO").toString()+"</DOMICILIO><COLONIA>"+clientet.value("COLONIA").toString()+"</COLONIA><CIUDAD>"+clientet.value("CIUDAD").toString()+"</CIUDAD><ESTADO>"+clientet.value("ESTADO").toString()+"</ESTADO><PAIS>"+clientet.value("PAIS").toString()+"</PAIS><CP>"+clientet.value("CP").toString()+"</CP></FAddress></Cliente>";
            xmlt+="<Transaction><ID_STR_RT>"+settings.getIdStore()+"</ID_STR_RT><ID_WS>"+settings.getIdWorkStation()+"</ID_WS>";
            xmlt+="<DC_DY_BSN>"+dia_trabajo+"</DC_DY_BSN>";
            xmlt+="<AI_TRN>"+QString::number(ai_trn2)+"</AI_TRN>";
            xmlt+="<ID_OPR>"+sesion_actual.Get_Oper()+"</ID_OPR><TS_TM_STR>"+settings.getSessionTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TM_STR>";
            xmlt+="<TY_TRN>TIEN</TY_TRN><TS_TRN_BGN>"+tiket->get_ts_trn_bgn()+"</TS_TRN_BGN><TS_TRN_END>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TRN_END>";
            xmlt+="<FL_CNCL>"+QString::number(is_cancelacion)+"</FL_CNCL>";//0 cuando no es cancelacion, 1 cuando si
            xmlt+="<FL_VD>0</FL_VD><FL_TRG_TRN>"+QString::number(training)+"</FL_TRG_TRN><FL_KEY_OFL>1</FL_KEY_OFL></Transaction>";
            xmlt+="<IN_TND_ELPSD>0</IN_TND_ELPSD><FL_SPN>0</FL_SPN>";
            xmlt+="<QU_UN_RTL_TRN>"+QString::number(tiket->get_total_art())+"</QU_UN_RTL_TRN>";
            xmlt+="<QU_ITM_LN_SC>0</QU_ITM_LN_SC><PE_ITM_LN_SC>0</PE_ITM_LN_SC><QU_ITM_LN_KY>"+QString::number(tiket->lineas.length())+"</QU_ITM_LN_KY><ID_FACTURA>0</ID_FACTURA>";
            xmlt+=xmlt2 + "</RetailTransaction>";
            xmlt+="</WriteRetailTransaction>";
            //QString query2="insert into transactions values ("+settings.getIdStore()+","+settings.getIdWorkStation()+",'"+dia_trabajo+"',"+QString::number(ai_trn2)+","+sesion_actual.Get_Oper()+",'"+sesion_actual.Get_ts_tm_str()+"','TIEN','"+TS_TRN_BGN+"','"+TS_TRN_BGN+"',"+QString::number(is_cancelacion)+",0,"+QString::number(training)+",1,'"+xmlt+"')";
            QString query2="insert into transactions values ("+settings.getIdStore()+","+settings.getIdWorkStation()+",'"+dia_trabajo+"',"+QString::number(ai_trn2)+","+sesion_actual.Get_Oper()+",'"+sesion_actual.Get_ts_tm_str()+"','TIEN','"+TS_TRN_BGN+"','"+TS_TRN_BGN+"',"+QString::number(is_cancelacion)+",0,"+QString::number(training)+",1,'"+xmlt+"')";
            ok = sqlQuery2.exec( query2 ) ;

    qDebug() << "finish_ticket \n" << query2;
    tiket->inicializar(settings.getDesglosaImpuestos()=="TRUE", Taxes);
return "query";
}

void principal::aplicar_cambios(QString cambio, int indice){
    QMap<QString,QVariant> regreso;
    RT_LineItem* linea = tiket->get_line(indice);
    linea->set_cambios(cambio);
    qDebug()<<"Cambiada linea "<<indice;
}

QVariant principal::do_cortez(){
    QString xml_cortez="";
    QString xml="";
    QString dia_trabajo = "";
    int ai_trn2= -1;
    int ai_trn;
    tillsalessumary* corteztillsalessumary;
    tilltaxhistory* corteztilltaxhistory;
    tilltaxhistory* temp_tilltaxhistory;
    tillhistory tillhist;
    int cajon;
    int almacen;
    Utilerias u;
    tillsalessumary* temp_tillsalessum;
    QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") );
    QString query;
    bool ok;
    bool venta;
    QDomDocument xmlt;
    bool cancelado;//nodo con posibles nodos
    bool anulado;//nodo con posibles nodos
    //totales  del tilltender en base de datos.
    QDomNodeList TY_LN_ITEM;
    int FL_VD_LN_ITEM;
    QDomNodeList RetailTransactionLineItem;
    QDomNodeList SaleReturnLineItem;
    QDomNodeList ID_ITM_PS;
    QDomNodeList ID_ITM_PS_QFR;
    QDomNodeList MO_EXTND;
    QDomNodeList ID_ITM;
    QDomNodeList TY_ITM;
    QDomNodeList QTY_ITM;
    QDomNodeList QU_ITM_LM_RTN_SLS;
    QDomNodeList FOOD_STAMP;
    QDomNodeList QU_ITM;
    QDomNodeList MO_IMPORTE_BASE;
    QDomNodeList MO_IMPORTE_FULL;
    QDomNodeList SaleReturnTaxLineItem;
    QDomNodeList ID_ATHY_TX;
    QDomNodeList ID_GP_TX;
    QDomNodeList AI_TX_RT_RU;
    QDomNodeList MO_TX_RTN_SLS;
    QDomNodeList MO_TXBL_RTN_SLS;
    QString xmltilltaxhistory;

    //sqlQuery( sqldatabasecortex.database("Origen") )  ;
    corteztillsalessumary=NULL;
    corteztilltaxhistory=NULL;
    almacen=1;
    cajon=1;
    query ="select coalesce( max(dc_dy_bsn) ,'2000-01-01 00:00:00') as dc_dy_bsn from transactions";
    ok = sqlQuery.exec( query ) ;
    sqlQuery.first();
    dia_trabajo=sqlQuery.value("dc_dy_bsn").toString();
    qDebug() << "loginproces.cpp do_cortez resultado 1 " << dia_trabajo;
    query ="select coalesce(max(ai_trn),0) as trn from transactions where TY_TRN='corte' and dc_dy_bsn = '"+dia_trabajo+"' and id_str_rt="+settings.getIdStore()+" and id_ws="+settings.getIdWorkStation();
    qDebug() << "::Do_Cortez() " << query;
    ok = sqlQuery.exec( query ) ;
    if(sqlQuery.first())
        ai_trn2 = sqlQuery.value("trn").toInt();
    else
        ai_trn2 = 0;
    qDebug() << "::do_corte() primera transaccion despues del corte anterior " << ai_trn2;
    //Obtiene el folio de la transaccion del corte Z
    query="select coalesce(max(ai_trn)+1,1) as trn from transactions where dc_dy_bsn = '"+dia_trabajo+"' and id_str_rt="+settings.getIdStore()+" and id_ws="+settings.getIdWorkStation();
    ok = sqlQuery.exec( query ) ;
    if(sqlQuery.first())
        ai_trn=sqlQuery.value("trn").toInt();
    else
        ai_trn = 1;
    qDebug() << "::do_corte folio de la transaccion del corte" << ai_trn;
    query="select * from transactions where ty_trn = 'TIEN' and dc_dy_bsn = '" + dia_trabajo + "' and fl_trg_trn = 0 and (xml is not null or xml != '') and ai_trn > " + QString::number(ai_trn2) + " and ID_STR_RT = " + settings.getIdStore() + " and ID_WS = " + settings.getIdWorkStation() + " order by ai_trn";
    ok = sqlQuery.exec( query ) ;
    qDebug() << "::do_corte PASO 0" << query;
    Ticket T;
    while( sqlQuery.next()  ){//get todos las transacciones
        qDebug() << "::do_corte PASO 1";
        venta=false;
        xmlt.setContent(sqlQuery.value("xml").toByteArray());
        qDebug() << "::do_corte PASO 1.1" << sqlQuery.value("xml").toString();
        RetailTransactionLineItem=xmlt.elementsByTagName("RetailTransactionLineItem");//get todos los writetendercontroltransactions
        cancelado= xmlt.elementsByTagName("FL_CNCL").at(0).toElement().text().toInt();//es cancelado
        anulado= xmlt.elementsByTagName("FL_VD").at(0).toElement().text().toInt();//es cancelado
        qDebug() << "::do_corte PASO 1.1";
        tillhist.qu_tran++;
        qDebug() << "::do_corte PASO 1.2";
        if(cancelado){
            tillhist.qu_tran_void++;
        }
        else if(anulado)
            tillhist.qu_tran_no_sale++;
        qDebug() << "::do_corte PASO 1.3";
        for(int x=0;x<RetailTransactionLineItem.length();x++){//recorrer todos los writetendercontroltransactions
            TY_LN_ITEM = (RetailTransactionLineItem.at(x).toElement()).elementsByTagName("TY_LN_ITEM");
            FL_VD_LN_ITEM = (RetailTransactionLineItem.at(x).toElement()).elementsByTagName("FL_VD_LN_ITEM").at(0).toElement().text().toInt();
            qDebug() << "::do_corte PASO 1.4" << TY_LN_ITEM.at(0).toElement().text();
            if(TY_LN_ITEM.at(0).toElement().text().compare("VE")==0)
            {
                SaleReturnLineItem =(RetailTransactionLineItem.at(x).toElement()).elementsByTagName("SaleReturnLineItem");
                qDebug() << "::do_corte PASO 1.5 " << SaleReturnLineItem.length();
                if(SaleReturnLineItem.length() > 0){
                    ID_ITM_PS = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("ID_ITM_PS");
                    ID_ITM_PS_QFR = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("ID_ITM_PS_QFR");
                    MO_EXTND = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("MO_EXTND");
                    ID_ITM = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("ID_ITM");
                    TY_ITM = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("TY_ITM");
                    QTY_ITM = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("QTY_ITM");
                    QU_ITM_LM_RTN_SLS = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("QU_ITM_LM_RTN_SLS");
                    FOOD_STAMP = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("FOOD_STAMP");
                    QU_ITM=(SaleReturnLineItem.at(0).toElement()).elementsByTagName("QU_ITM");
                    MO_IMPORTE_BASE = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("MO_IMPORTE_BASE");
                    MO_IMPORTE_FULL = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("MO_IMPORTE_FULL");
                    qDebug() << "::do_corte PASO 2 " << cancelado << " " << anulado;
                    if(!cancelado & !anulado)
                    {
                        qDebug() << "::do_corte PASO 2.1 " << FL_VD_LN_ITEM;
                        if(FL_VD_LN_ITEM <= 0)
                        {
                            qDebug() << "::do_corte PASO 2.3 " << FL_VD_LN_ITEM;
                            xml_cortez+=T.text_lista("Imp: Ventas articulos:",u.FormatoNumero(QString::number(tillhist.cu_sls_itm),1,2),48);
                            xml_cortez+=T.text_lista("Tax: Ventas articulos:",u.FormatoNumero(QString::number(tillhist.cu_sls_tx_itm),1,2),48);
                            xml_cortez+=T.text_lista("Imp: Ventas anuladas:",u.FormatoNumero(QString::number(tillhist.cu_void_itm),1,2),48);
                            xml_cortez+=T.text_lista("Tax: Ventas anuladas:",u.FormatoNumero(QString::number(tillhist.cu_void_tx_itm),1,2),48);
                            xml_cortez+=T.text_lista("Imp: Ventas canceladas",u.FormatoNumero(QString::number(tillhist.cu_void_itm_tr),1,2),48);
                            xml_cortez+=T.text_lista("Tax: Ventas canceladas:",u.FormatoNumero(QString::number(tillhist.cu_void_tx_itm_tr),1,2),48);
                            xml_cortez+=T.text_lista("Imp: Ventas devoluciones:",u.FormatoNumero(QString::number(tillhist.cu_rtn_itm),1,2),48);
                            xml_cortez+=T.text_lista("Tax: Ventas devoluciones:",u.FormatoNumero(QString::number(tillhist.cu_rtn_tx_itm),1,2),48);
                            xml_cortez+=T.text_lista("Imp: Ventas servicios:",u.FormatoNumero(QString::number(tillhist.cu_sls_svc),1,2),48);
                            xml_cortez+=T.text_lista("Tax: Ventas servicios:",u.FormatoNumero(QString::number(tillhist.cu_sls_tx_svc),1,2),48);
                            if(corteztillsalessumary == NULL){
                                qDebug() << "::do_corte PASO 10";
                                corteztillsalessumary = new tillsalessumary(ID_ITM.at(0).toElement().text().toInt(), cajon, almacen);
                                temp_tillsalessum = corteztillsalessumary;
                                if(QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat() >= 0)
                                {
                                    if(TY_ITM.at(0).toElement().text().compare("SERV")==0)
                                    {
                                        tillhist.cu_sls_svc++;
                                        tillhist.cu_sls_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                        tillhist.cu_sls_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    }
                                    else
                                    {
                                        tillhist.qu_sls_itm++;
                                        tillhist.cu_sls_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                        tillhist.cu_sls_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    }
                                    corteztillsalessumary->add(MO_IMPORTE_BASE.at(0).toElement().text().toFloat(),
                                                           QU_ITM.at(0).toElement().text().toInt() * QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat(),
                                                           1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                                }
                                else
                                {
                                    tillhist.qu_rtn_itm++;
                                    tillhist.cu_rtn_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    tillhist.cu_rtn_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    corteztillsalessumary->add(0, 0, 0, -1 * MO_IMPORTE_BASE.at(0).toElement().text().toFloat(),
                                                          -1 *QU_ITM.at(0).toElement().text().toInt() * QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat(),
                                                           1, 0, 0, 0, 0, 0, 0);
                                 }
                            }
                            else
                            {
                                temp_tillsalessum=corteztillsalessumary->find(ID_ITM.at(0).toElement().text().toInt(),cajon, almacen);
                                if(temp_tillsalessum == NULL)
                                {
                                    temp_tillsalessum = new tillsalessumary(ID_ITM.at(0).toElement().text().toInt(),cajon, almacen);
                                    corteztillsalessumary->append(temp_tillsalessum);
                                }
                                if(QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat() >= 0)
                                {
                                    if(TY_ITM.at(0).toElement().text().compare("SERV")==0)
                                    {
                                        tillhist.cu_sls_svc++;
                                        tillhist.cu_sls_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                        tillhist.cu_sls_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    }
                                    else
                                    {
                                        tillhist.qu_sls_itm++;
                                        tillhist.cu_sls_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                        tillhist.cu_sls_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    }
                                    temp_tillsalessum->add(MO_IMPORTE_BASE.at(0).toElement().text().toFloat(),
                                                       QU_ITM.at(0).toElement().text().toInt() * QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat(),
                                                       1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                                }
                                else
                                {
                                    tillhist.qu_rtn_itm++;
                                    tillhist.cu_rtn_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    tillhist.cu_rtn_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                                    temp_tillsalessum->add(0, 0, 0, -1 * MO_IMPORTE_BASE.at(0).toElement().text().toFloat(),
                                                           -1 *QU_ITM.at(0).toElement().text().toInt() * QU_ITM_LM_RTN_SLS.at(0).toElement().text().toFloat(),
                                                           1, 0, 0, 0, 0, 0, 0);
                                }
                            }
                            SaleReturnTaxLineItem = (SaleReturnLineItem.at(0).toElement()).elementsByTagName("SaleReturnTaxLineItem");
                            for(int y=0;y<SaleReturnTaxLineItem.count();y++)
                            {
                                ID_ATHY_TX = (SaleReturnTaxLineItem.at(y).toElement()).elementsByTagName("ID_ATHY_TX");
                                ID_GP_TX = (SaleReturnTaxLineItem.at(y).toElement()).elementsByTagName("ID_GP_TX");
                                AI_TX_RT_RU = (SaleReturnTaxLineItem.at(y).toElement()).elementsByTagName("AI_TX_RT_RU");
                                MO_TX_RTN_SLS = (SaleReturnTaxLineItem.at(y).toElement()).elementsByTagName("MO_TX_RTN_SLS");
                                MO_TXBL_RTN_SLS = (SaleReturnTaxLineItem.at(y).toElement()).elementsByTagName("MO_TXBL_RTN_SLS");
                                temp_tillsalessum->add_tax(ID_GP_TX.at(0).toElement().text().toInt(), ID_ATHY_TX.at(0).toElement().text().toInt(), AI_TX_RT_RU.at(0).toElement().text().toInt(), MO_TXBL_RTN_SLS.at(0).toElement().text().toFloat(), MO_TX_RTN_SLS.at(0).toElement().text().toFloat(),
                                                           MO_TXBL_RTN_SLS.at(0).toElement().text().toFloat(), MO_TX_RTN_SLS.at(0).toElement().text().toFloat());
                                if(corteztilltaxhistory == NULL)
                                    corteztilltaxhistory = new tilltaxhistory(ID_ATHY_TX.at(0).toElement().text().toInt(),
                                                                              ID_GP_TX.at(0).toElement().text().toInt(),
                                                                              AI_TX_RT_RU.at(0).toElement().text().toInt(),
                                                                              MO_TXBL_RTN_SLS.at(0).toElement().text().toFloat(),
                                                                              MO_TX_RTN_SLS.at(0).toElement().text().toFloat());
                                else{
                                    temp_tilltaxhistory = corteztilltaxhistory->find(ID_ATHY_TX.at(0).toElement().text().toInt(),
                                                                                     ID_GP_TX.at(0).toElement().text().toInt(),
                                                                                     AI_TX_RT_RU.at(0).toElement().text().toInt());
                                    if(temp_tilltaxhistory == NULL)
                                    {
                                        temp_tilltaxhistory = new tilltaxhistory(ID_ATHY_TX.at(0).toElement().text().toInt(),
                                                                                 ID_GP_TX.at(0).toElement().text().toInt(),
                                                                                 AI_TX_RT_RU.at(0).toElement().text().toInt(),
                                                                                 MO_TXBL_RTN_SLS.at(0).toElement().text().toFloat(),
                                                                                 MO_TX_RTN_SLS.at(0).toElement().text().toFloat());
                                        corteztilltaxhistory->append(temp_tilltaxhistory);
                                    }
                                    else
                                    {
                                        temp_tilltaxhistory->add(MO_TXBL_RTN_SLS.at(0).toElement().text().toFloat(),
                                                                 MO_TX_RTN_SLS.at(0).toElement().text().toFloat());
                                    }
                                }
                                //fin de la creacion o asignacion de tillsales y tillsalestax
                            }
                        }
                        else
                        {
                            tillhist.qu_void_itm_tr++;
                        }
                    }
                    else
                    {
                        if (cancelado)
                        {
                            tillhist.cu_void_itm_tr+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                            tillhist.cu_void_tx_itm_tr+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                        }
                        else
                        {
                            tillhist.cu_void_itm+=MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                            tillhist.cu_void_tx_itm+=MO_IMPORTE_FULL.at(0).toElement().text().toFloat() - MO_IMPORTE_BASE.at(0).toElement().text().toFloat();
                        }
                    }
                } //Termina la linea de ventas
            }
        }
    }
    qDebug() << "::do_corte PASO A";
    xml_cortez+=T.text_centrado("Corte de Caja",48);
    xml_cortez+="\n\n"+T.text_centrado("Seccion de Tracciones",48)+"\n\n";
    xml_cortez+=T.text_lista("Lineas de venta en articulos:",QString::number(tillhist.qu_sls_itm),48);
    xml_cortez+=T.text_lista("Lineas de ventas anuladas:",QString::number(tillhist.qu_void_itm),48);
    xml_cortez+=T.text_lista("Lineas de ventas canceladas:",QString::number(tillhist.qu_void_itm_tr),48);
    xml_cortez+=T.text_lista("Lineas de articulos Devueltos:",QString::number(tillhist.qu_rtn_itm),48);
    xml_cortez+=T.text_lista("Lineas de articulos de Servicios:",QString::number(tillhist.cu_sls_svc),48);
    xml_cortez+=T.text_lista("Cant. de transacciones sin venta:",QString::number(tillhist.qu_tran_no_sale),48);
    xml_cortez+=T.text_lista("Cant. de transacciones canceladas:",QString::number(tillhist.qu_tran_void),48);
    xml_cortez+=T.text_lista("Cant. totales transacciones:",QString::number(tillhist.qu_tran),48)+"\n\n";
    xml_cortez+="\n\n"+T.text_centrado("Seccion Ventas",48)+"\n";
    xml_cortez+=T.text_lista("Imp: Ventas articulos:",u.FormatoNumero(QString::number(tillhist.cu_sls_itm),1,2),48);
    xml_cortez+=T.text_lista("Tax: Ventas articulos:",u.FormatoNumero(QString::number(tillhist.cu_sls_tx_itm),1,2),48);
    xml_cortez+=T.text_lista("Imp: Ventas anuladas:",u.FormatoNumero(QString::number(tillhist.cu_void_itm),1,2),48);
    xml_cortez+=T.text_lista("Tax: Ventas anuladas:",u.FormatoNumero(QString::number(tillhist.cu_void_tx_itm),1,2),48);
    xml_cortez+=T.text_lista("Imp: Ventas canceladas",u.FormatoNumero(QString::number(tillhist.cu_void_itm_tr),1,2),48);
    xml_cortez+=T.text_lista("Tax: Ventas canceladas:",u.FormatoNumero(QString::number(tillhist.cu_void_tx_itm_tr),1,2),48);
    xml_cortez+=T.text_lista("Imp: Ventas devoluciones:",u.FormatoNumero(QString::number(tillhist.cu_rtn_itm),1,2),48);
    xml_cortez+=T.text_lista("Tax: Ventas devoluciones:",u.FormatoNumero(QString::number(tillhist.cu_rtn_tx_itm),1,2),48);
    xml_cortez+=T.text_lista("Imp: Ventas servicios:",u.FormatoNumero(QString::number(tillhist.cu_sls_svc),1,2),48);
    xml_cortez+=T.text_lista("Tax: Ventas servicios:",u.FormatoNumero(QString::number(tillhist.cu_sls_tx_svc),1,2),48);
    float total_ventas = tillhist.cu_sls_itm + tillhist.cu_sls_tx_itm + tillhist.cu_sls_svc + tillhist.cu_sls_tx_svc - tillhist.cu_rtn_itm - tillhist.cu_rtn_tx_itm;
    xml_cortez+=T.text_lista("Total:",u.FormatoNumero(QString::number(total_ventas),1,2),48);
    xml_cortez+="\n\n\n\n"+T.text_centrado("Seccion de Impuesto",48)+"\n\n\n";
    xmltilltaxhistory="";
    qDebug() << "::do_corte PASO B";
    if(corteztilltaxhistory!=NULL)
    {
        xml_cortez+=corteztilltaxhistory->get_linea();
        xmltilltaxhistory=corteztilltaxhistory->get_xml();
    }
    qDebug() << "::do_corte PASO C";
    /*
    for(int x=0;x<corteztilltaxhistory.length();x++){
        xml_cortez+=T.text_centrado(corteztilltaxhistory.at(x).nm_gp_tx,48)+"\n\n";
        xml_cortez+=T.text_lista("Base Gravable",u.FormatoNumero(QString::number(corteztilltaxhistory.at(x).mo_txbl_rtn_sls),1,2),48);
        xml_cortez+=T.text_lista("Total del impuesto",u.FormatoNumero(QString::number(corteztilltaxhistory.at(x).mo_tx_rtn_sls),1,2),48)+"\n\n";
        xmltilltaxhistory+="<TillTaxHistory><ID_ATHY_TX>"+u.FormatoNumero(QString::number(corteztilltaxhistory.at(x).id_athy_tx),1,2)+"</ID_ATHY_TX><ID_GP_TX>"+QString::number(corteztilltaxhistory.at(x).id_gp_tx)+"</ID_GP_TX><NM_GP_TX>"+corteztilltaxhistory.at(x).nm_gp_tx+"</NM_GP_TX><AI_LN_TAX>"+QString::number(corteztilltaxhistory.at(x).ai_ln_tax)+"</AI_LN_TAX><MO_TXBL_RTN_SLS>"+QString::number(corteztilltaxhistory.at(x).mo_tx_rtn_sls)+"</MO_TXBL_RTN_SLS><MO_TX_RTN_SLS>"+QString::number(corteztilltaxhistory.at(x).mo_tx_rtn_sls)+"</MO_TX_RTN_SLS><MO_EXM_TXBL>"+QString::number(corteztilltaxhistory.at(x).mo_exm_tx)+"</MO_EXM_TXBL><MO_EXM_TX>"+QString::number(corteztilltaxhistory.at(x).mo_exm_tx)+"</MO_EXM_TX></TillTaxHistory>";
    }*/
    xml_cortez+=T.text_centrado("Impuesto anulado",48)+"\n\n";
    xml_cortez+=T.text_lista("Base Gravable",u.FormatoNumero(QString::number(tillhist.cu_void_itm),1,2),48);
    xml_cortez+=T.text_lista("Total del impuesto",u.FormatoNumero(QString::number(tillhist.cu_void_tx_itm),1,2),48)+"\n\n";
    qDebug() << "::do_corte PASO D";

    /*
    float totalb=0;
    float totali=0;
    xml_cortez+="\n\n\n\n"+T.text_centrado("Seccion de Impuesto Excento",48)+"\n\n\n";
    for(int x=0;x<corteztilltaxhistory.length();x++){
        totalb+=corteztilltaxhistory.at(x).mo_exm_txbl;
        totali+=corteztilltaxhistory.at(x).mo_exm_tx;
    }
    xml_cortez+=T.text_lista("Base Gravable",u.FormatoNumero(QString::number(totalb),1,2),48);
    xml_cortez+=T.text_lista("Total del impuesto",u.FormatoNumero(QString::number(totali),1,2),48)+"\n\n";
    */

    xml_cortez+="\n\n\n\n"+T.text_centrado("Seccion de dinero",48)+"\n\n\n";
    float sub_entradas=0;
    float sub_salidas=0;
    QString xmltilltender="";
    query="select tt.*, t.de_tnd from tilltender tt, tender t where tt.ty_tnd = t.ty_tnd";
    if(!sqlQuery.exec( query ))
        qDebug() << "::do_cortez() error en query" << query;
    else{
        while( sqlQuery.next()){//todos los till tender
            sub_entradas=0;
            sub_salidas=0;
            sub_entradas=sqlQuery.value("TOTAL_DEPOSITOS").toFloat()+sqlQuery.value("TOTAL_INGRESOS").toFloat()+sqlQuery.value("TOTAL_COBROS_MENORES").toFloat();
            xml_cortez+="\n\n\n\n"+T.text_centrado(sqlQuery.value("TY_TND").toString(),48)+"\n\n";
            xml_cortez+=T.text_lista("Total de depositos",u.FormatoNumero(sqlQuery.value("TOTAL_DEPOSITOS").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("Total de ingresos",u.FormatoNumero(sqlQuery.value("TOTAL_INGRESOS").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("Total de cobros menores",u.FormatoNumero(sqlQuery.value("TOTAL_COBROS_MENORES").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("subtotal de entradas",u.FormatoNumero(QString::number(sub_entradas),1,2),48)+"\n";

            sub_salidas=sqlQuery.value("TOTAL_RETIROS").toFloat()+sqlQuery.value("TOTAL_CAMBIOS").toFloat()+sqlQuery.value("TOTAL_PAGOS").toFloat()+sqlQuery.value("TOTAL_PAGOS_MENORES").toFloat();
            xml_cortez+=T.text_lista("Total de retiros",u.FormatoNumero(sqlQuery.value("TOTAL_RETIROS").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("Total de cambios",u.FormatoNumero(sqlQuery.value("TOTAL_CAMBIOS").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("Total de pagos",u.FormatoNumero(sqlQuery.value("TOTAL_PAGOS").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("Total de pagos menores",u.FormatoNumero(sqlQuery.value("TOTAL_PAGOS_MENORES").toString(),1,2),48)+"\n";
            xml_cortez+=T.text_lista("subtotal de salidas",u.FormatoNumero(QString::number(sub_salidas),1,2),48)+"\n";

            xmltilltender+="<TillTenderHistory><TY_TND>"+sqlQuery.value("TY_TND").toString()+"</TY_TND><DE_TND>"+sqlQuery.value("DE_TND").toString()+"</DE_TND><TOTAL_DEPOSITOS>"+sqlQuery.value("TOTAL_DEPOSITOS").toString()+"</TOTAL_DEPOSITOS><TOTAL_RETIROS>"+sqlQuery.value("TOTAL_RETIROS").toString();
            xmltilltender+="</TOTAL_RETIROS><TOTAL_INGRESOS>"+sqlQuery.value("TOTAL_INGRESOS").toString()+"</TOTAL_INGRESOS><TOTAL_CAMBIOS>"+sqlQuery.value("TOTAL_CAMBIOS").toString()+"</TOTAL_CAMBIOS><TOTAL_PAGOS>"+sqlQuery.value("TOTAL_PAGOS").toString()+"</TOTAL_PAGOS><TOTAL_PAGOS_MENORES>"+sqlQuery.value("TOTAL_PAGOS_MENORES").toString();
            xmltilltender+="</TOTAL_PAGOS_MENORES><TOTAL_COBROS_MENORES>"+sqlQuery.value("TOTAL_COBROS_MENORES").toString()+"</TOTAL_COBROS_MENORES></TillTenderHistory>";
        }
    }
    /*
    for(int x=0;x<corteztillsalessumary.length();x++){
        xmlCorte+="<TillSalesSummary><ID_ITM>"+QString::number(corteztillsalessumary.at(x).id_itm)+"</ID_ITM><NM_ITM></NM_ITM><MO_SLS_ITM>"+QString::number(corteztillsalessumary.at(x).mo_sls_itm)+"</MO_SLS_ITM><QU_SLS_ITM>"+QString::number(corteztillsalessumary.at(x).qu_sls_itm)+"</QU_SLS_ITM><QU_SLS_TRN>"+QString::number(corteztillsalessumary.at(x).qu_sls_trn)+"</QU_SLS_TRN><MO_RTN_ITM>"+QString::number(corteztillsalessumary.at(x).mo_rtn_itm)+"</MO_RTN_ITM><QU_RTN_ITM>"+QString::number(corteztillsalessumary.at(x).qu_rtn_itm)+"</QU_RTN_ITM><QU_RTN_TRN>"+QString::number(corteztillsalessumary.at(x).qu_rtn_trn)+"</QU_RTN_TRN><MO_XDEP_ITM>"+QString::number(corteztillsalessumary.at(x).mo_xdep_itm)+"</MO_XDEP_ITM><QU_XDEP_ITM>"+QString::number(corteztillsalessumary.at(x).qu_xdep_itm)+"</QU_XDEP_ITM><QU_XDEP_TRN>"+QString::number(corteztillsalessumary.at(x).qu_xdep_trn)+"</QU_XDEP_TRN><MO_PAG_ITM>"+QString::number(corteztillsalessumary.at(x).mo_pag_itm)+"</MO_PAG_ITM><QU_PAG_ITM>"+QString::number(corteztillsalessumary.at(x).qu_pag_itm)+"</QU_PAG_ITM><QU_PAG_TRN>"+QString::number(corteztillsalessumary.at(x).qu_pag_trn)+"</QU_PAG_TRN></TillSalesSummary>";
        xmlCorte+="<TillSalesTaxSummary><ID_ITM>"+QString::number(corteztilltaxsumary.at(x).id_itm)+"</ID_ITM><NM_ITM></NM_ITM><AI_LN_TAX>"+QString::number(corteztilltaxsumary.at(x).ai_ln_tax)+"</AI_LN_TAX><ID_GP_TX>"+QString::number(corteztilltaxsumary.at(x).id_gp_tx)+"</ID_GP_TX><AI_ATHY_TX>"+QString::number(corteztilltaxsumary.at(x).ai_athy_tx)+"</AI_ATHY_TX><MO_TXBL_RTN_SLS>"+QString::number(corteztilltaxsumary.at(x).mo_txbl_rtn_sls)+"</MO_TXBL_RTN_SLS><MO_TX_RTN_SLS>"+QString::number(corteztilltaxsumary.at(x).mo_tx_rtn_sls)+"</MO_TX_RTN_SLS><MO_EXM_TXBL_SLS>"+QString::number(corteztilltaxsumary.at(x).mo_exm_txbl_sls)+"</MO_EXM_TXBL_SLS><MO_EXM_TX>"+QString::number(corteztilltaxsumary.at(x).mo_exm_tx)+"</MO_EXM_TX></TillSalesTaxSummary>";
    }
    */
    qDebug() << "::do_corte PASO E";
    xmlCorte="";
    if(corteztillsalessumary != NULL)
        xmlCorte=corteztillsalessumary->get_xml();
    qDebug() << "::do_corte PASO F";
    xml="<Cortes><corte><WriteControlTransaction><ControlTransaction>";
    xml+="<Transaction><ID_STR_RT>"+settings.getIdStore()+"</ID_STR_RT><ID_WS>"+settings.getIdWorkStation()+"</ID_WS><DC_DY_BSN>"+dia_trabajo+"</DC_DY_BSN><AI_TRN>"+QString::number(ai_trn)+"</AI_TRN><ID_OPR>"+sesion_actual.Get_Oper()+"</ID_OPR><TS_TM_STR>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TM_STR><TY_TRN>CORTE</TY_TRN><TS_TRN_BGN>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TRN_BGN><TS_TRN_END>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TRN_END><FL_CNCL>0</FL_CNCL><FL_VD>0</FL_VD>";
    if(settings.getTraining().compare("FALSE")==0||settings.getTraining().compare("false")==0){
       xml+="<FL_TRG_TRN>0</FL_TRG_TRN>";
    }else{xml+="<FL_TRG_TRN>1</FL_TRG_TRN>";}

    xml+="<FL_KEY_OFL>1</FL_KEY_OFL></Transaction><TY_TRN_CTL /><TillSettlementTransaction><TillHistory> ";
    xml+="<ID_RPSTY_TND>"+sesion_actual.id_rpsty_tnd+"</ID_RPSTY_TND><QU_SLS_ITM>"+QString::number(tillhist.qu_sls_itm)+"</QU_SLS_ITM><QU_VOID_ITM>"+QString::number(tillhist.qu_void_itm)+"</QU_VOID_ITM><QU_VOID_ITM_TR>"+QString::number(tillhist.qu_void_itm_tr)+"</QU_VOID_ITM_TR><QU_RTN_ITM>"+QString::number(tillhist.qu_rtn_itm)+"</QU_RTN_ITM><QU_SLS_SVC>"+QString::number(tillhist.qu_sls_svc)+"</QU_SLS_SVC><QU_TRAN>"+QString::number(tillhist.qu_tran)+"</QU_TRAN><QU_TRAN_NO_SALE>"+QString::number(tillhist.qu_tran_no_sale)+"</QU_TRAN_NO_SALE><QU_TRAN_VOID>"+QString::number(tillhist.qu_tran_void)+"</QU_TRAN_VOID><CU_SLS_ITM>"+QString::number(tillhist.cu_sls_itm)+"</CU_SLS_ITM><CU_VOID_ITEM>"+QString::number(tillhist.cu_void_itm)+"</CU_VOID_ITEM><CU_RTN_ITM>"+QString::number(tillhist.cu_rtn_itm)+"</CU_RTN_ITM><CU_VOID_ITM_TR>"+QString::number(tillhist.cu_void_itm_tr)+"</CU_VOID_ITM_TR>";
    xml+="<CU_SLS_SVC>"+QString::number(tillhist.cu_sls_svc)+"</CU_SLS_SVC><CU_SLS_TX_ITM>"+QString::number(tillhist.cu_sls_tx_itm)+"</CU_SLS_TX_ITM><CU_VOID_TX_ITM>"+QString::number(tillhist.cu_void_tx_itm)+"</CU_VOID_TX_ITM><CU_RTN_TX_ITM>"+QString::number(tillhist.cu_rtn_tx_itm)+"</CU_RTN_TX_ITM><CU_VOID_TX_ITM_TR>"+QString::number(tillhist.cu_void_tx_itm_tr)+"</CU_VOID_TX_ITM_TR><CU_SLS_TX_SVC>"+QString::number(tillhist.cu_sls_tx_svc)+"</CU_SLS_TX_SVC>";
    xml+=xmlCorte;
    qDebug() << "::do_corte PASO G";
    xml+=xmltilltender;
    xml+=xmltilltaxhistory;
    qDebug() << "::do_corte PASO H";
    xml+="</TillHistory></TillSettlementTransaction></ControlTransaction></WriteControlTransaction></corte></Cortes>";
    query = "insert into transactions values("+settings.getIdStore()+","+settings.getIdWorkStation()+",'"+dia_trabajo+"',"+QString::number(ai_trn)+","+sesion_actual.Get_Oper()+",'"+sesion_actual.Get_ts_tm_str()+"','CORTE', '"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"', '"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"',0,0,0,1,'"+xml+"')";
    qDebug() << "Logout() en el insert " << query;
    ok = sqlQuery.exec( query ) ;
    if(ok){
        impresion_dep(xml_cortez,5,ai_trn,dia_trabajo,settings.getIdWorkStation().toInt());
        qDebug() << "do_corte()obtiene cajas de dinero de los workstation";
        //query = "SELECT id_rpsty_tnd FROM core_pos.till where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() + " and id_opr = " + id_opr;
        query = "SELECT id_rpsty_tnd FROM core_pos.till where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation();//  + " and id_opr = " + id_opr;
        ok = sqlQuery.exec( query ) ;
        sqlQuery.first();
        if(sqlQuery.isValid()){
            cajon=sqlQuery.value("id_rpsty_tnd").toInt();}
        qDebug() << "::do_corte() update tilltender" ;
        query = "update tilltender set total_depositos = 0,total_retiros = 0, total_ingresos = 0, total_cambios= 0, total_pagos = 0, total_pagos_menores = 0, total_cobros_menores = 0 where ";
        query+= " id_str_rt = " + settings.getIdStore() + " and id_rpsty_tnd = " + QString::number(cajon) + " and id_ws = " + settings.getIdWorkStation();
        ok = sqlQuery.exec( query ) ;
        if(!ok){qDebug() << "::do_corte() error al update el tilltender" << query;}
        qDebug() << "::do_corte() update till" ;
        query = "update till set id_opr = NULL where id_str_rt = " + settings.getIdStore() + " and id_rpsty_tnd = " + QString::number(cajon) + " and id_ws = " + settings.getIdWorkStation();
        ok = sqlQuery.exec( query ) ;
        if(!ok){qDebug() << "::do_corte() error al update el till" << query ;}
        sesion_actual.logout(ai_trn);
    }
    else
    {
        qDebug() << "";
        qDebug() << "::Logout() error en el insert " << query;
    }


    return "d";
}

void principal::impresion_dep(QString texto, int tipo,int transaction,QString fecha,int caja){
    //llega un objeto con el tipo, concepto y valor.
    //tipo: 1 ticket venta
    //2 deposito
    //3 retiro
    //4 corte z
    //5 corte x
    QString impresion="";
    QString separador="";
    Ticket T;

    qDebug() <<"::impresion_dep en la prueba";

    int ypoint=0;
    int saltos_de_linea=0;
    qDebug() <<": impresion_dep()";

    QPrinter printer(QPrinter::HighResolution);

    printer.setPageSize(QPrinter::A7);
    printer.setOrientation(QPrinter::Portrait);
    printer.setPageMargins (1,1,1,1,QPrinter::Millimeter);
    //printer.setFullPage(false);
    //printer.setFullPage(false);
    //printer.setPrinterName("PRP Thermal Printer");
    //printer.setPrinterName("PRP-188");

    QPrintDialog dialog(&printer);
            dialog.setWindowTitle(tr("Print Document"));

            if (dialog.exec() != QDialog::Accepted) {
                return;
            }
            else{

                qDebug() << "impresion en proceso";

                    if(tipo==1){//ticket
                        //titulo
                        QPainter painter(&printer); // create a painter which will paint 'on printer'.
                        painter.setFont(QFont("Tahoma",15));
                        qDebug()<<"Metrics, tamaño  de fuente"<<painter.fontMetrics().height()<<" tamaño de la hoja "<<printer.pageRect().width();

                        //width 1550.0

                        QRectF rectangle(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        painter.drawText(rectangle,Qt::AlignCenter,"bienvenidos");
                        //painter.drawRect(rectangle);
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;
                        QRectF rectangle2(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        //painter.drawRect(rectangle2);
                        painter.drawText(rectangle2,Qt::AlignCenter,"Abarrotes duero Y MAS");
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;
                        //200 widt
                        QRectF target(200.0, ypoint, 200.0, 200.0);//tamaño de la imagen
                        QPixmap pixmap("assets/default.png");
                        QRectF source(80.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara
                        //QRectF source(2000-pixmap.width()/2, 0.0,4000, pixmap.height());
                        painter.drawPixmap(target, pixmap, source);

                        ypoint=ypoint+210;

                        //fin titulo

                        painter.setFont(QFont("Tahoma",9));

                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        //550.0
                        QRectF rectangles1(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

                        //datos tiket
                        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
                        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles1x(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //separador
                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles2(15.0, ypoint, 3400, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //cuerpo  del tiket

                        impresion=texto+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles4(15.0, ypoint, 3000.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles4,Qt::AlignRight,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

                        //footer
                        painter.setFont(QFont("Tahoma",15));
                        impresion=datos_ticket.pie1+"\n"+datos_ticket.pie2;
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangle4(15.0, ypoint, 3000.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle4);
                        painter.drawText(rectangle4,Qt::AlignCenter,impresion);

                    }
                    if(tipo==2 || tipo==3){
                        //titulo
                        QPainter painter(&printer); // create a painter which will paint 'on printer'.
                        painter.setFont(QFont("Tahoma",15));
                        //550 width
                        QRectF rectangle(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        painter.drawText(rectangle,Qt::AlignCenter,datos_ticket.encabezado1);
                        //painter.drawRect(rectangle);
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;
                        QRectF rectangle2(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        //painter.drawRect(rectangle2);
                        painter.drawText(rectangle2,Qt::AlignCenter,datos_ticket.encabezado2);
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;

                        QRectF target(200.0, ypoint, 200, 200.0);//tamaño de la imagen
                        QPixmap pixmap("assets/default.png");
                        QRectF source(0.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara

                        painter.drawPixmap(target, pixmap, source);

                        ypoint=ypoint+210;

                        //fin titulo

                        painter.setFont(QFont("Tahoma",9));

                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles1(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

                        //datos tiket
                        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
                        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles1x(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //separador
                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles2(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //cuerpo  del tiket

                        impresion=texto+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles4(15.0, ypoint, 3000.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles4,Qt::AlignRight,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

                    }
                    if(tipo==4 || tipo== 5){
                        //titulo
                        QPainter painter(&printer); // create a painter which will paint 'on printer'.
                        painter.setFont(QFont("Tahoma",15));
                        //550 widht
                        QRectF rectangle(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        painter.drawText(rectangle,Qt::AlignCenter,datos_ticket.encabezado1);
                        //painter.drawRect(rectangle);
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;
                        QRectF rectangle2(15.0, ypoint, 3400.0, painter.fontMetrics().height());
                        //painter.drawRect(rectangle2);
                        painter.drawText(rectangle2,Qt::AlignCenter,datos_ticket.encabezado2);
                        ypoint=ypoint+painter.fontMetrics().height()+20;
                        //qDebug() <<ypoint;

                        QRectF target(200.0, ypoint, 200, 200.0);//tamaño de la imagen
                        QPixmap pixmap("assets/default.png");
                        QRectF source(0.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara

                        painter.drawPixmap(target, pixmap, source);

                        ypoint=ypoint+210;

                        //fin titulo

                        painter.setFont(QFont("Tahoma",9));

                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles1(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

                        //datos tiket
                        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
                        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles1x(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
                        //qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //separador
                        impresion=separador.leftJustified(48,'-')+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles2(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                        //cuerpo  del tiket

                        impresion=texto+"\n\n";
                        saltos_de_linea=impresion.count('\n')+1;
                        QRectF rectangles4(15.0, ypoint, 3400.0, painter.fontMetrics().height()*saltos_de_linea);
                        //painter.drawRect(rectangle3);
                        painter.drawText(rectangles4,Qt::AlignRight,impresion);
                        qDebug() <<saltos_de_linea << " " <<ypoint;
                        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


                    }

                qDebug() << "impresion terminó";
            }

/*
    if(tipo==1){//ticket
        //titulo
        QPainter painter(&printer); // create a painter which will paint 'on printer'.
        painter.setFont(QFont("Tahoma",15));
        QRectF rectangle(15.0, ypoint, 1550.0, painter.fontMetrics().height());
        painter.drawText(rectangle,Qt::AlignCenter,datos_ticket.encabezado1);
        //painter.drawRect(rectangle);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;
        QRectF rectangle2(15.0, ypoint, 1550.0, painter.fontMetrics().height());
        //painter.drawRect(rectangle2);
        painter.drawText(rectangle2,Qt::AlignCenter,datos_ticket.encabezado2);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;

        QRectF target(200.0, ypoint, 200, 200.0);//tamaño de la imagen
        QPixmap pixmap("C:/Users/Karlis/Downloads/mitienda.jpg");
        QRectF source(0.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara

        painter.drawPixmap(target, pixmap, source);

        ypoint=ypoint+210;

        //fin titulo

        painter.setFont(QFont("Tahoma",9));

        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

        //datos tiket
        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1x(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //separador
        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles2(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //cuerpo  del tiket

        impresion=texto+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles4(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles4,Qt::AlignRight,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

        //footer
        painter.setFont(QFont("Tahoma",15));
        impresion=datos_ticket.pie1+"\n"+datos_ticket.pie2;
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangle4(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle4);
        painter.drawText(rectangle4,Qt::AlignCenter,impresion);

    }
    if(tipo==2 || tipo==3){
        //titulo
        QPainter painter(&printer); // create a painter which will paint 'on printer'.
        painter.setFont(QFont("Tahoma",15));
        QRectF rectangle(15.0, ypoint, 550.0, painter.fontMetrics().height());
        painter.drawText(rectangle,Qt::AlignCenter,datos_ticket.encabezado1);
        //painter.drawRect(rectangle);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;
        QRectF rectangle2(15.0, ypoint, 550.0, painter.fontMetrics().height());
        //painter.drawRect(rectangle2);
        painter.drawText(rectangle2,Qt::AlignCenter,datos_ticket.encabezado2);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;

        QRectF target(200.0, ypoint, 200, 200.0);//tamaño de la imagen
        QPixmap pixmap("C:/Users/Karlis/Downloads/mitienda.jpg");
        QRectF source(0.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara

        painter.drawPixmap(target, pixmap, source);

        ypoint=ypoint+210;

        //fin titulo

        painter.setFont(QFont("Tahoma",9));

        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

        //datos tiket
        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1x(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //separador
        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles2(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //cuerpo  del tiket

        impresion=texto+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles4(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles4,Qt::AlignRight,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

    }
    if(tipo==4 || tipo== 5){
        //titulo
        QPainter painter(&printer); // create a painter which will paint 'on printer'.
        painter.setFont(QFont("Tahoma",15));
        QRectF rectangle(15.0, ypoint, 550.0, painter.fontMetrics().height());
        painter.drawText(rectangle,Qt::AlignCenter,datos_ticket.encabezado1);
        //painter.drawRect(rectangle);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;
        QRectF rectangle2(15.0, ypoint, 550.0, painter.fontMetrics().height());
        //painter.drawRect(rectangle2);
        painter.drawText(rectangle2,Qt::AlignCenter,datos_ticket.encabezado2);
        ypoint=ypoint+painter.fontMetrics().height()+20;
        //qDebug() <<ypoint;

        QRectF target(200.0, ypoint, 200, 200.0);//tamaño de la imagen
        QPixmap pixmap("C:/Users/Karlis/Downloads/mitienda.jpg");
        QRectF source(0.0, 0.0,pixmap.width(), pixmap.height());//parte de la imagen que se tomara

        painter.drawPixmap(target, pixmap, source);

        ypoint=ypoint+210;

        //fin titulo

        painter.setFont(QFont("Tahoma",9));

        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1,Qt::AlignCenter,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;

        //datos tiket
        impresion="Tran. NO. "+QString::number(transaction)+"\nFecha:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"\n"+"caja:"+QString::number(caja)+"\n";
        impresion+="cajero: "+sesion_actual.OPERADOR+"\n"+"D. de negocio: "+sesion_actual.fechaBusinessday.toString("yyyy-MM-dd hh:mm:ss")+"\n";

        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles1x(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles1x,Qt::AlignLeft,impresion);
        //qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //separador
        impresion=separador.leftJustified(48,'-')+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles2(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles2,Qt::AlignCenter,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


        //cuerpo  del tiket

        impresion=texto+"\n\n";
        saltos_de_linea=impresion.count('\n')+1;
        QRectF rectangles4(15.0, ypoint, 550.0, painter.fontMetrics().height()*saltos_de_linea);
        //painter.drawRect(rectangle3);
        painter.drawText(rectangles4,Qt::AlignRight,impresion);
        qDebug() <<saltos_de_linea << " " <<ypoint;
        ypoint+=painter.fontMetrics().height()*saltos_de_linea;


    }
*/

}

void principal::add_tilltender(QVariant values)
{
    QMap<QString,QVariant> till_info;
    till_tender tender;
    QString tipo;
    bool ok;
    till_info=values.toMap();

    ok=tender.addTillTender(till_info.value("forma_de_pago").toString(),till_info.value("operacion").toInt(),till_info.value("amount").toString(),"+");
    if(ok){
        qDebug() << "tender actualizado";
        QString dep_impresion;
        Ticket tik;
        if(till_info.value("operacion").toInt()==2)
        {
            dep_impresion="\n\n"+tik.text_centrado("Deposito",48)+"\n\n";
            tipo = "DE";
        }
        else
        {
            if (till_info.value("operacion").toInt()==3){
                dep_impresion="\n\n"+tik.text_centrado("Retiro",48)+"\n\n";
                tipo = "RE";
            }
            else if(till_info.value("operacion").toInt()==4)
            {
                dep_impresion="\n\n"+tik.text_centrado("Pago Menor",48)+"\n\n";
                tipo = "PA";
            }
            else if(till_info.value("operacion").toInt()==5){
                dep_impresion="\n\n"+tik.text_centrado("Cobro Menor",48)+"\n\n";
                tipo = "CO";
            }
        }

        dep_impresion=tik.text_lista("Concepto","Valor",48)+"\n";
        dep_impresion+=tik.text_lista(till_info.value("concepto").toString(),till_info.value("amount").toString(),48);

        impresion_dep(dep_impresion,till_info.value("operacion").toInt(),1,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),settings.getIdWorkStation().toInt());

        QString dia_trabajo = "";
        int ai_trn= 0;
        QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") )  ;
        dia_trabajo=sesion_actual.Get_BusinessDayF("yyyy_MM-dd hh:mm:ss");
        qDebug() << "loginproces dia de negocio " << dia_trabajo;
        QString query ="select coalesce(max(ai_trn),0)+1 as trn from transactions where dc_dy_bsn = '"+dia_trabajo+"'";
        ok = sqlQuery.exec( query ) ;
        if(sqlQuery.first())
            ai_trn = sqlQuery.value("trn").toInt();
        else
            ai_trn=1;
        qDebug() << "loginproces trn " << ai_trn;
        QString training="0";
        if(settings.getTraining().compare("TRUE")==0){
            training="1";
        }
        //ticket y actualizacion en tabla transactions
         QString xmlt="<?xml version=\"1.0\"?><WriteTenderControlTransaction><Oper>WriteTenderControlTransaction</Oper>";
                 xmlt+="<TendeControlTransactionTenderLineItem><ID_RPSTY_TND>"+sesion_actual.id_rpsty_tnd+"</ID_RPSTY_TND>";
                 xmlt+="<MO_TND_FN_TRN>"+till_info.value("amount").toString()+"</MO_TND_FN_TRN><TY_TND>"+till_info.value("forma_de_pago").toString()+"</TY_TND></TendeControlTransactionTenderLineItem>";
                 xmlt+="<TenderControlTransaction><RC_TND_CTL>"+till_info.value("concepto").toString()+"</RC_TND_CTL>";//descripcion del movimiento
                 xmlt+="<TY_TND_CTL>"+tipo+"</TY_TND_CTL>";//PAGO,RETI,DEPO
                 xmlt+="<Transaction><AI_TRN>1</AI_TRN><DC_DY_BSN>"+dia_trabajo+"</DC_DY_BSN><FL_CNCL>0</FL_CNCL>";
                 xmlt+="<FL_KEY_OFL>0</FL_KEY_OFL>";
                 xmlt+="<FL_TRG_TRN>"+training+"</FL_TRG_TRN><FL_VD>0</FL_VD>";
                 xmlt+="<ID_OPR>"+QString::number(settings.getIdOpr())+"</ID_OPR><ID_STR_RT>"+settings.getIdStore()+"</ID_STR_RT><ID_WS>"+settings.getIdWorkStation()+"</ID_WS>";
                 xmlt+="<TS_TM_STR>"+settings.getSessionTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TM_STR>";
                 xmlt+="<TS_TRN_BGN>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TRN_BGN>";
                 xmlt+="<TS_TRN_END>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</TS_TRN_END><TY_TRN>CTTE</TY_TRN>";
                 xmlt+="<Transaction_Auth><ID_OPR>"+sesion_actual.Get_OperSup()+"</ID_OPR></Transaction_Auth>";
                 xmlt+="</Transaction></TenderControlTransaction></WriteTenderControlTransaction>";
                 query="insert into transactions values ("+settings.getIdStore()+","+settings.getIdWorkStation()+",'"+dia_trabajo+"',"+QString::number(ai_trn)+","+QString::number(settings.getIdOpr())+",'"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"','CTTE','"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"','"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"',"+"0"+",0,"+training+",1,'"+xmlt+"')";
         if(!sqlQuery.exec( query ))
         {
             qDebug() << "add_tilltender() Error" << query;
         }
         else
             qDebug() << "add_tilltender() insert Ok: " << query;
    }else{qDebug() << "tender no actualizado";}
}

QVariant principal::do_cancel(QVariant value){

    //2020 participa en el proceso de cancelación

    QMap<QString,QVariant> respuesta;
    RT_LineItem* linea;
    bool novalida=false;

    qDebug() << "::do_cancel" << value;
    int indice=value.toInt();
    linea =tiket->get_line(indice);
    if (linea->get_cancelable()){
        respuesta=tiket->add_line_cancel(indice);
        respuesta["respuesta"]=1;//cancelacion exitosa
    }
    else novalida = true;
    if(novalida) respuesta["respuesta"] = 0;
    return respuesta;
}

QVariant principal::validaCancel(QVariant value){
    RT_LineItem* linea;
    QMap<QString,QVariant> respuesta;
    int indice=value.toInt();
    qDebug() << "::validaCancel;" << value;
    linea =tiket->get_line(indice);
    if (linea->get_cancelable()){
        qDebug() << "::validaCancel es cancelable" << value;
        respuesta["respuesta"]=1;//cancelacion exitosa
    }
    else respuesta["respuesta"] = 0;
    return respuesta;
}

QMap<QString, QVariant> principal::getlinea(int i){
    QMap<QString, QVariant> ret;
    if (tiket == NULL)
        ret["resultado"]=0;
    else{
        ret=tiket->getlinea(i);
        ret["resultado"]=1;
    }
    return ret;
}

QString principal::login(QString u, QString p, bool supervisor){
    QVariant l;

    if(supervisor){
        l=sesion_actual.login_operador(u,p);
    }
    else{
        l=sesion_actual.setLogin(u,p);
    }
    qDebug() << ".cpp resultado:" << l;
    return l.toString();
}

QString principal::logout(){
    QSqlDatabase sqlDatabasebut;
    int ai_trn=0;
    bool ok=false;
    QString query;
    QSqlQuery sqlQuery( sqlDatabasebut.database( "Origen") ) ;

    query = "select coalesce(max(ai_trn)+1,1) as ai_trn from transactions where id_str_rt = " + settings.getIdStore() + " and id_ws = " + settings.getIdWorkStation() + " and dc_dy_bsn = (select max(dc_dy_bsn) from businessday where ts_end is null or ts_end = '2000-01-01 00:00:00')";
    qDebug()<< "Session.cpp logout "<<query;
    ok = sqlQuery.exec( query ) ;
    if(sqlQuery.first())
        ai_trn =sqlQuery.value("ai_trn").toInt();
    else
        ai_trn = 1;
     query= "update till set id_opr = NULL where id_str_rt = " + settings.getIdStore() + " and id_rpsty_tnd = " + sesion_actual.id_rpsty_tnd + " and id_ws = " + settings.getIdWorkStation();
    ok = sqlQuery.exec( query ) ;
    if(!ok){qDebug() << "::do_corte() error al update el till" << query ;}
    sesion_actual.logout(ai_trn);
    return "";
}

int principal::check_permisos(QString permiso ){
for(int x=0;x<sesion_actual.permisos.size();x++){
    qDebug()<<"el permiso "<<permiso<<" el actual "<<sesion_actual.permisos.at(x)["id_rs"]<<sesion_actual.permisos.at(x)["ps_acs_gp_wr"];
    if(permiso.compare(sesion_actual.permisos.at(x)["id_rs"])==0&&sesion_actual.permisos.at(x)["ps_acs_gp_wr"].compare("1")==0){
        qDebug()<<"Se encontro el permiso "<<permiso;
        return 1;
    }
}

return 0;

}

int principal::check_permisos_supervisor(QString permiso ){
for(int x=0;x<sesion_actual.permisosadmin.size();x++){
    qDebug()<<"el permiso "<<permiso<<" el actual "<<sesion_actual.permisosadmin.at(x)["id_rs"]<<sesion_actual.permisosadmin.at(x)["ps_acs_gp_wr"];
    if(permiso.compare(sesion_actual.permisosadmin.at(x)["id_rs"])==0&&sesion_actual.permisosadmin.at(x)["ps_acs_gp_wr"].compare("1")==0){
        qDebug()<<"Se encontro el permiso "<<permiso;
        return 1;
    }
}

return 0;

}


QVariant principal::before_change_price(QVariant value){
    QMap<QString,QVariant> respuesta;

    int indice=value.toInt();
    RT_LineItem* line;
    line = tiket->get_line(indice);
    qDebug() << "::before_change_price" << QString::number(indice);
    if(line->get_cancelable()){
       if(line->get_tipo_renglon() == "VE") respuesta["respuesta"]=1;
       else {
           respuesta["respuesta"]=0;
           respuesta["mensaje"]="Esta linea no es una venta";
       }
    }
    else {
       respuesta["respuesta"]=0;
       respuesta["mensaje"]="No se pueden hacer cambios en esta linea";
    }
    return respuesta;
}

QVariant principal::do_Change_price(QVariant value, int indice){
    //2020 Participa en el cambio de precios
    QMap<QString,QVariant> regreso=value.toMap();
    QMap<QString,QVariant> respuesta;
    QString price  =regreso.value("precio_Nuevo").toString();
    QString pos    =regreso.value("id_itm_ps").toString();
    QString pos_qr =regreso.value("id_itm_ps_qfr").toString();
    bool permanente=regreso.value("permanente").toBool();
    if(sesion_actual.Get_OperSup()==0)//el usuario ya es supervisor
    {
        regreso["id_supervisor"]=sesion_actual.Get_Oper();
    }else{regreso["id_supervisor"]=sesion_actual.Get_OperSup(); }

    qDebug() << ".cpp do_Change_price(): precio nuevo " << price << " indice " << QString::number(indice);
    if(permanente){
        QSqlQuery sqlQuery( sqldatabasecortex.database( "Origen") )  ;
        QString query = "select * from posidentity where ID_ITM_PS = '"+pos+ "' and ID_ITM_PS_QFR = '"+pos_qr+"'";
        qDebug() << ".cpp do_Change_price(): precio nuevo " << query;
        sqlQuery.exec( query ) ;
        sqlQuery.first();
        if(sqlQuery.isValid()){
            QString sellprice=sqlQuery.value("ID_ITM_SL_PRC").toString();
            qDebug() << "se busco el sell price y dio  "+sellprice;
            QSqlQuery sqlQuery2( sqldatabasecortex.database( "Origen") )  ;
            QString query2 = "update itemsellprice set sell_price = "+price+"  where id_itm_sl_prc ="+sellprice;
            sqlQuery2.exec( query2 ) ;
            qDebug() << ".cpp do_Change_price() se cambio el precio "+query2;
        }
        else qDebug() << ".cpp do_Change_price(): query inválido";
    }
    else         qDebug() << ".cpp do_Change_price(): no permanente ";
    respuesta=tiket->do_cambio_precio(indice, regreso);
    respuesta["respuesta"]=1;//cancelacion exitosa
    return respuesta;
}

bool principal::toggleflDevolucion()
{
    if (tiket == NULL)
        return true;
    else
        return tiket->toggleflDevolucion();
}

bool principal::getflDevolucion(){
    if (tiket == NULL)
        return false;
    else
        return tiket->getflDevolucion();
}

void principal::resetflDevolucion(){
    if (tiket != NULL) tiket->resetflDevolucion();
}

bool principal::waitSaleSave(QVariant nombre){
    int position;
    bool ret;
    bool igual;

    ret = false;
    if (tiket->venta_activa())
    {
        position = -1;
        if (tiket_esperan.length() > 0)
        {
            position = 0;
            igual=false;
            while (position < tiket_esperan.length() && !igual)
            {
                if(tiket_esperan.at(position) == nombre)
                {
                    igual=true;
                }
                else
                    position++;
            }
            if(!igual) position = -1;
        }
        if (position < 0)
        {
            tiket_espera.append(tiket);
            tiket_esperan.append(nombre.toString());
            tiket = new (retail_Transaction);
            tiket->inicializar(settings.getDesglosaImpuestos()=="TRUE", Taxes);
            ret=true;
        }
    }
    return ret;
}

bool principal::waitSaleRecover(int position){
    bool ret;

    ret = false;
    if(!tiket->venta_activa())
    {
        delete tiket;
        tiket=NULL;
        tiket = tiket_espera.at(position);
        tiket_espera.remove(position);
        tiket_esperan.removeAt(position);
        ret=true;
    }
    return ret;
}

QVariant principal::getNombresVentaEspera()
{
    return QVariant::fromValue(tiket_esperan);
}

int principal::getNumeroVentasEspera()
{
    return tiket_espera.length();
}

bool principal::venta_activa(){
    bool ret = tiket->venta_activa();
    if (ret)
        qDebug() << "::venta_activa() true";
    else
        qDebug() << "::venta_activa() false";
    return ret;
}

bool principal::getPosibleNoVenta(){
    bool ret;

    if (tiket == NULL) ret = false;
    else ret=tiket->getPosibleNoVenta();
    return ret;
}

QString principal::get_taxs(){
    QString xml="";
    QString query="";
    qDebug() << "get_taxs() ";
    QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") )  ;
    query="select * from taxablegroup";

    qDebug() << "get_taxs() " <<query;

    sqlQuery.exec( query ) ;

    while(sqlQuery.next()){

        xml+="<impuesto><id_gp_tx>"+sqlQuery.value("id_gp_tx").toString()+"</id_gp_tx><nm_ru_tx>"+sqlQuery.value("nm_gp_tx").toString()+"</nm_ru_tx></impuesto>";
    }

        xml="<impuestos>"+xml+"</impuestos>";

return xml;
}

QString principal::get_categorias(QString valor){
    QString xml="";
    QString query="";

    QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") )  ;
    query="select m.*,t.nm_gp_tx from merchandisehierarchygroup m,taxablegroup t where m.id_gp_tx = t.id_gp_tx and m.NM_MRHRC_GP like '%"+valor+"%' order by m.nm_MRHRC_GP limit 0,25";
    qDebug() << "query "<<query;

    sqlQuery.exec( query ) ;

    while(sqlQuery.next()){

        xml+="<categoria><id_mrhrc_gp>"+sqlQuery.value("id_mrhrc_gp").toString()+"</id_mrhrc_gp><nm_mrhrc_gp>"+sqlQuery.value("nm_mrhrc_gp").toString()+"</nm_mrhrc_gp><id_gp_tx>"+sqlQuery.value("id_gp_tx").toString()+"</id_gp_tx><nm_ru_tx>"+sqlQuery.value("nm_gp_tx").toString()+"</nm_ru_tx><food_stamp>"+sqlQuery.value("food_stamp_ex").toString()+"</food_stamp></categoria>";
    }

        xml="<categorias>"+xml+"</categorias>";

    //qDebug() << "fin de itemsearch "<<xml;

return xml;
}

