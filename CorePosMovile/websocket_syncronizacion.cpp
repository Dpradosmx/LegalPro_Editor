#include "websocket_syncronizacion.h"
#include "hilo_actualizador.h"
QT_USE_NAMESPACE
websocket_syncronizacion::websocket_syncronizacion(){}
void websocket_syncronizacion::init_websocket(){
    ai_ln_actual=0;
    ai_ln_max=0;
    setProgreso_actualizacion( 0);

    settings.setUp();

}
websocket_syncronizacion::websocket_syncronizacion(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &websocket_syncronizacion::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    m_webSocket.open(QUrl(url));

    opciones<<"mensaje"<<"syncronizacionResultado"<<"loginRespuesta"<<"respuestainstalacion"<<"respuestaconfirmacion"<<"respuestaaltaitem";
    //0,1,2....,n
    //settings.setNewLineMax(0);
    //settings.setIdStore("1");
    //settings.setIdInstancia("87");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pruebas");
    if(!db.open()){
        qDebug() << "Error syncronizacion 1: " << db.lastError();
    }
}
//funcion que crea la base de datos si es una nueva instalacion,
//solo se ejecuta la primera vez que se abre la aplicacion

void websocket_syncronizacion::base_de_datos(){
    QTime myTimer;
    myTimer.start();
      db.setDatabaseName("pruebas");
      if(!db.open()){
          qDebug() << "ERROR: " << db.lastError();
          return;
      }
      QSqlQuery query(db);
      QString script="CREATE TABLE Bank (ID_BN integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6),NM_BN varchar(40));CREATE TABLE BusinessDay (DC_DY_BSN timestamp,ID_STR_RT integer,AI_TRN integer,ID_WS integer,TS_BGN timestamp,TS_END timestamp,PRIMARY KEY (DC_DY_BSN, ID_STR_RT));CREATE TABLE ButtonConfig (ID_STR_RT integer,ID_BTNSET smallint,ID_BTN integer,ID_BTN_PRNT integer,TY_BTN char(2) DEFAULT 'PR',BTN_WT smallint,NM_BTN varchar(20),DE_BTN varchar(255),PIC bytea,ID_ITM integer,ICON_ADDRESS varchar(50),ID_STRGRP integer,ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer,WEBADDRESS varchar(255),WEBSERV_NAME varchar(255),PARAMS_LIST text,POSITION smallint,PRIMARY KEY (ID_STR_RT, ID_BTNSET,ID_BTN));CREATE TABLE ButtonSets (ID_STR_RT integer,ID_BTNSET smallint,DE_BTNSET varchar(40),FL_COMPOR_RET char(1) DEFAULT 'H',PRIMARY KEY (ID_STR_RT, ID_BTNSET));CREATE TABLE ConfiguracionGral (ID_INSTANCIA integer PRIMARY KEY,BTNHOME boolean,DESGLOSAIMPUESTOS boolean,HASVIRTUALWINDOW boolean,IDMERCHANT integer,IMPUESTOPORIG boolean,ISNEW boolean,LINEMAX bigint,SCALE integer,SCALETYPE varchar(6) DEFAULT 'SERIAL0',SCALEPORT varchar(10),SCALEREMLEFT varchar(10),SCALEREQUEST varchar(10),SCALEREMRIGHT varchar(10),TAXINPRICE boolean,TRAINING boolean,UPDATEPOS boolean,VERSION varchar(20),WINDOWWIDTH integer,WINDOWHIGH integer);CREATE TABLE Customer (ID_CT bigint PRIMARY KEY,CV_CT char(8),ID_PRTY integer,NM_CT varchar(40),NM_ORGN varchar(60),ID_TX_IRGN varchar(255),ID_TX_FDL varchar(40),RFC_TAXID varchar(40),DESGLOSA_IEPS char(1),ID_PRS_LST integer);CREATE TABLE CustomerAddress (ID_ADS integer PRIMARY KEY,ID_CT bigint,DC_EF timestamp,DC_EP timestamp,DOMICILIO varchar(60),COLONIA varchar(40),CIUDAD varchar(40),ESTADO varchar(50),PAIS varchar(40),CP varchar(10),DIR_FACTURA char(1),DIR_ENTREG char(1));CREATE TABLE DerivatedPrice (ID_PRC_LST integer,ID_ITM_SL_PRC integer,PRICE decimal(10,4),ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer,PRIMARY KEY (ID_PRC_LST,ID_ITM_SL_PRC,PRICE ));CREATE TABLE Descuentos (ID_DSC integer PRIMARY KEY,NM_DSC varchar(40),DE_DSC varchar(255),CD_RDN_MTH char(2),MO_RDN_AMT decimal(8,3),PR_RDN_AMT decimal(5,2),MO_NW_PRC decimal(8,3));CREATE TABLE DisbursementFundsReceiptReason (ID_RCV_DSB integer PRIMARY KEY,DE_RCV_DSB varchar(20),TY_RCV char(1));CREATE TABLE External_User (ID_EXTU integer PRIMARY KEY,USER varchar(20),PWD varchar(20),TY_USR char(1) DEFAULT 'I',TY_TND char(4),ID_ITM integer);CREATE TABLE GroupResourceAccess (ID_GP_WRK integer,ID_RS integer,PS_ACS_GP_RD char(2),PS_ACS_GP_WR char(2),PRIMARY KEY (ID_GP_WRK,ID_RS,PS_ACS_GP_RD,PS_ACS_GP_WR));CREATE TABLE HistCatalogos (DC_DY_BSN timestamp,AI_LN bigint,ID_OPR integer,ID_STR_RT integer,CAT_ACT varchar(50),DT_ACT timestamp,OPER varchar(50),XML text,APLICADO integer,PRIMARY KEY (DC_DY_BSN,AI_LN,ID_OPR,ID_STR_RT ));CREATE TABLE Item (ID_ITM integer PRIMARY KEY,ID_SPR integer,ID_ITM_SL_PRC integer,ID_MRHRC_GP integer,ID_BRN integer,NM_UOM varchar(15),LU_EXM_TX integer,NM_ITM varchar(40),DE_ITM varchar(255),TY_ITM char(6),TY_ITM_SV char(2),ID_GP_TX integer,ID_GP_TX_BUY integer,URL varchar(255),ETIQUETA_IMPORTE varchar(255),ETIQUETA_POST varchar(255),QML varchar(255),VTA_CANCEL varchar(2) DEFAULT 'SI',FOOD_STAMP_EX char(1));CREATE TABLE ItemCollection (ID_ITM integer,ID_ITM_COL integer,AI_ITM_COL smallint,QU_ITM_PR_ASMB decimal(9,3),PE_BLO decimal(5,2),PRIMARY KEY (ID_ITM,ID_ITM_COL ));CREATE TABLE ItemPictures (ID_ITM integer,ID_SEQ INTEGER, PICTURE bytea, URL varchar(200), PRIMARY KEY (ID_ITM, id_seq) );CREATE TABLE ItemSellPrice (ID_ITM_SL_PRC integer PRIMARY KEY,SELL_PRICE decimal(8,4),PRICE_LIST decimal(10,4),OFER_PRICE decimal(10,4),PE_PRICE decimal(5,2),FL_VL_PRICE char(1));CREATE TABLE ItemVolumePrice (ID_ITM_SL_PRC integer,AL_LN_PRC smallint,ID_PRC_LST integer,MIN_QTY decimal(10,4),MAX_QTY decimal(10,4),PRIMARY KEY (ID_ITM_SL_PRC,AL_LN_PRC));CREATE TABLE Languaje (ID_LNG smallint PRIMARY KEY,LANGUAJE varchar(20));CREATE TABLE Mensajes (ID_RS integer,ID_LNG smallint,ID_MSJ integer,MENSAJE varchar(255),PRIMARY KEY (ID_RS,ID_LNG,ID_MSJ));CREATE TABLE MerchandiseHierarchyGroup (ID_MRHRC_GP integer PRIMARY KEY,ID_MRHC_PRNT integer,NM_MRHRC_GP varchar(40),PE_PROFIT decimal(10,4),ID_GP_TX integer,FOOD_STAMP_EX char(1) DEFAULT 'N');CREATE TABLE Operator (ID_OPR integer,ID_STR_RT integer,ID_EM integer,NM_OPR varchar(30),PWD_ACS_OPR varchar(15),BLOQUED_TIME timestamp,PRIMARY KEY (ID_OPR,ID_STR_RT));CREATE TABLE OperatorGroup (ID_STR_RT integer,ID_GP_WRK integer,ID_OPR integer,ID_RS INTEGER,PRIMARY KEY (ID_STR_RT,ID_GP_WRK,ID_OPR));CREATE TABLE Ports (PORT varchar(10) PRIMARY KEY,BAUDRATE varchar(50),DATABITS varchar(50),FLOWCONTROL varchar(50),REMRI varchar(50),PARITY varchar(50),STOPBITS varchar(50));CREATE TABLE POSIdentity (ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer DEFAULT 1,ID_ITM_SL_PRC integer,ID_ITM integer,ID_PREP_CC integer,Qu_ITM decimal(10,4),ACTIVO char(1) DEFAULT 'S',PRIMARY KEY (ID_ITM_PS,ID_ITM_PS_QFR,ID_ITM));CREATE TABLE RetailStore (ID_STR_RT integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6) DEFAULT 'SUCURS',ID_STRGRP integer,DC_OPN_RT_STR date,DC_CL_RT_STR date,NM_STR_RT varchar(40),DOMICILIO varchar(60),COLONIA  varchar(40),CIUDAD varchar(40),ESTADO varchar(40),PAIS varchar(50),CP varchar(10),ENC_PRN1 varchar(22),ENC_PRN2 varchar(22),PIE_PRN1 varchar(22),PIE_PRN2 varchar(22),ID_MERCHANT_ED integer,LOGIN_ED varchar(10),PASWORD_ED varchar(10),BANK_AUTO_ED varchar(20),POSITION1 varchar(40),POSITION2 varchar(40),POSITION3 varchar(40),POSITION4 varchar(40),POSITION5 varchar(40),POSITION6 varchar(40),LOGO1 bytea,LOGO2 bytea,permite_venta_rojo VARCHAR(1));CREATE TABLE Safety (ID_STR_RT integer,ID_SFTY bigint,DEPOSITO decimal(15,4),GARANTIZADO decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_SFTY));CREATE TABLE Safety_Log (ID_STR_RT integer,ID_SFTY bigint,ID_TRAN integer,TY_OPER char(1),DC_OPER timestamp,AMOUNT decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_SFTY,ID_TRAN));CREATE TABLE Scales (SCALE integer PRIMARY KEY,NM_SCALE varchar(40),SCALETYPE varchar(6),BAUDRATE varchar(50),DATABITS varchar(50),FLOWCONTROL varchar(50),PARITY varchar(50),REMLEFT varchar(50),REMRIGHT varchar(50),REQUEST varchar(50),STOPBITS varchar(50));CREATE TABLE ServiceItem (ID_ITM integer PRIMARY KEY,ID_SPR integer,CP_BS_SV_ITM decimal(10,4),CP_NT_SV_ITM decimal(10,4),PE_BS_SV_ITM decimal(5,2),PE_NT_SV_ITM decimal(5,2),TY_CLC_SV_ITEM char(2),DC_CST_EST_SV_ITM timestamp,TY_ITM_SV char(6),WEB_URL varchar(255),ETIQUETA_IMPORTE varchar(255),ETIQUETA_POST varchar(255),QML_FILE varchar(255),VTA_CANCEL varchar(2),CARGO_XFPAG varchar(1),FM_CLC_SV_ITEM varchar(1));CREATE TABLE Session (ID_STR_RT integer,ID_WS integer,ID_OPR integer,TS_TM_STR timestamp,AI_TRN_BGN integer,AI_TRN_END integer,DC_DY_BSN_BGN timestamp,DC_DY_BSN_END timestamp,TS_END timestamp,PRIMARY KEY (ID_STR_RT,ID_WS,ID_OPR,TS_TM_STR));CREATE TABLE StockItem (ID_ITM integer PRIMARY KEY,ID_SPR integer,NM_UOM varchar(40),LU_CNT_SLS_WT_UN char(2),CP_UN_SL_LS_RSV decimal(10,5),DC_CST_EST_LS_RCV timestamp);CREATE TABLE Supplier (ID_SPR integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6),NM_SPR varchar(40),DU_SPR char(9),FL_MF_SPR_IS char(1),PERIODICITY integer,MONEY_ORDER char(1));CREATE TABLE TaxableGroup (ID_GP_TX integer PRIMARY KEY,NM_GP_TX varchar(40),CD_RCPT_PRN varchar(2));CREATE TABLE TaxGroupRule (ID_ATHY_TX integer,ID_GP_TX integer,AI_CMPND smallint,NM_RU_TX varchar(20),ID_ACNT_LDG integer,PRIMARY KEY (ID_ATHY_TX,ID_GP_TX ));CREATE TABLE TaxRateRule (ID_ATHY_TX integer,ID_GP_TX integer,AI_TX_RT_RU smallint,TY_TX_RT_RU char(2) DEFAULT 'PE',MO_TXBM_MNM decimal(15,4),MO_TXBL_MXM decimal(15,4),MO_RT_TX decimal(15,5),PE_RT_TX decimal(10,4),PRIMARY KEY (ID_ATHY_TX,ID_GP_TX,AI_TX_RT_RU));CREATE TABLE Tender (TY_TND char(4) PRIMARY KEY,ID_ACT_LDG integer,ID_CNY integer,DE_TND varchar(255),FL_NMB_SRZ smallint,FL_AZN_RQ smallint,LU_MTH_AZN varchar(4),FL_DT_AZN_EP_RQ char(1) DEFAULT 'N',IN_WIT_AZN_MXM_ALOW smallint,FL_IDTN_RQ_CT smallint,FL_ID_PRSL_RQ smallint,FL_AVLB_LCL_CNY smallint,FL_SGNTR_CT_RQ smallint,MO_TH_TND_CHN decimal(14,3),FL_DRW_OPEN smallint,MO_APVL_TNDCE_OFF decimal(15,4),FL_ENDSM_RQ smallint,PLAZOS char(1) DEFAULT 'N',ID_ITM_PS varchar(30),BTN_ASIGNED char(4),FOOD_STAMP_EX char(1));CREATE TABLE TenderPlazo (TY_TND char(4),TY_TND_LN smallint,DIAS decimal(3),PE_MONTO decimal(5,2),PRIMARY KEY (TY_TND,TY_TND_LN));CREATE TABLE Till (ID_STR_RT integer,ID_RPSTY_TND integer,ID_WS integer,ID_OPR integer,SC_TL char(2),TS_TST_TL timestamp,CP_BLNC_DFLT_OPN decimal(14,3),LU_TND_MXM_ALW decimal(14,3),PRIMARY KEY (ID_STR_RT,ID_RPSTY_TND));CREATE TABLE TillTender (ID_STR_RT integer,ID_RPSTY_TND integer,ID_WS integer,TY_TND char(4),TOTAL_DEPOSITOS decimal(15,4),TOTAL_RETIROS decimal(15,4),TOTAL_INGRESOS decimal(15,4),TOTAL_CAMBIOS decimal(15,4),TOTAL_PAGOS decimal(15,4),TOTAL_PAGOS_MENORES decimal(15,4),TOTAL_COBROS_MENORES decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_RPSTY_TND,ID_WS,TY_TND));CREATE TABLE Transactions (ID_STR_RT integer,ID_WS integer,DC_DY_BSN timestamp,AI_TRN integer,ID_OPR integer,TS_TM_STR timestamp,TY_TRN varchar(6),TS_TRN_BGN timestamp,TS_TRN_END timestamp,FL_CNCL smallint,FL_VD smallint,FL_TRG_TRN smallint,FL_KEY_OFL smallint,XML text,PRIMARY KEY (ID_STR_RT,ID_WS,DC_DY_BSN,AI_TRN));CREATE TABLE TY_ID (TY_ID char(2) PRIMARY KEY,NM_ID varchar(20));CREATE TABLE WorkStation (ID_STR_RT integer,ID_WS integer,ID_EQ integer,SERIE varchar(30),QU_TL_WS decimal(3),FL_MOD_TRG smallint,FL_KEYBOARD smallint,ID_BTNSET bigint,ID_POS_ED integer,PRIMARY KEY (ID_STR_RT,ID_WS))";
      QStringList scriptQueries = script.split(";");
      foreach (QString queryTxt, scriptQueries)
          {
              if (queryTxt.trimmed().isEmpty()) {
                  continue;
              }
              if (!query.exec(queryTxt))
              {
                  qDebug() << "ERROR: " << query.lastError().text();
                  //qFatal(QString("One of the query failed to execute."
                    //          " Error detail: " + query.lastError().text()).toLocal8Bit());
              }
              query.finish();
          }
      qDebug() << "Creada bd en: " << myTimer.elapsed() << " milisegundos;";
}

void websocket_syncronizacion::insertar(){
    QTime myTimer;
    myTimer.start();
      db.setDatabaseName("pruebas");
      if(!db.open()){
          qDebug() << "ERROR: " << db.lastError();
          return;
      }
      QSqlQuery query(db);
      //inicial pruebas
      QString script="insert into itempictures (id_itm,id_seq, url) values(2,1,'https://1.bp.blogspot.com/-SgdeP7qUxaU/XjXLKoYtjkI/AAAAAAAAGuA/IbujcWYprMwtvnipeFfuA6NlIuMn6xV8ACLcBGAsYHQ/s1600/papas%2Bcon%2Bchorizo%2B01.jpg'),(2,2,'https://images-gmi-pmc.edge-generalmills.com/2a6e1f03-b10d-4251-bb3f-6f17005fe9fe.jpg'),(3,1,'https://cdn2.cocinadelirante.com/sites/default/files/styles/gallerie/public/images/2019/07/receta-de-chorizo-argentino-con-cerveza.jpg')";

      QStringList scriptQueries = script.split(";");
      foreach (QString queryTxt, scriptQueries)
          {
              if (queryTxt.trimmed().isEmpty()) {
                  continue;
              }
              if (!query.exec(queryTxt))
              {
                  qDebug() << "ERROR: " << query.lastError().text();
                  //qFatal(QString("One of the query failed to execute."
                    //          " Error detail: " + query.lastError().text()).toLocal8Bit());
              }
              query.finish();
          }
      qDebug() << "Insertada bd en: " << myTimer.elapsed() << " milisegundos;";
}

void websocket_syncronizacion::select(){
    db.setDatabaseName("pruebas");
    QString xml="";
    if(!db.open()){
        qDebug() << "ERROR: " << db.lastError();
        return;
    }
    QSqlQuery query(db);
    query.exec("SELECT * FROM item where id_itm in (2,3);");
    qDebug() << "SELECT * FROM itempictures ";
    QString resultado="vacio";
    while (query.next()) {
        resultado="";
        for(int x=0;x<query.record().count();x++){
            resultado+="| "+query.value(x).toString()+" | ";

        }
        qDebug()<< resultado;
    }

}

void websocket_syncronizacion::selectquery(QString querys){
    db.setDatabaseName("pruebas");
    QString xml="";
    if(!db.open()){
        qDebug() << "ERROR: " << db.lastError();
        return;
    }
    QSqlQuery query(db);
    query.exec(querys);
    qDebug() << "SELECT * FROM HistCatalogos ORDER BY ai_ln";
    QString resultado="vacio";
    while (query.next()) {
        resultado="";
        for(int x=0;x<query.record().count();x++){
            resultado+="| "+query.value(x).toString()+" | ";

        }
        qDebug()<< resultado;
    }

}

QString websocket_syncronizacion::get_tender(){
    db.setDatabaseName("pruebas");
    QString xml="";
    if(!db.open()){
        qDebug() << "ERROR: " << db.lastError();
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
        xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
        return xml;
    }
    QSqlQuery query(db);
    query.exec("select ty_tnd,de_tnd from tender");

    xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    while (query.next()) {
        xml+="<buttonconfig>";
        xml+="<ID_STR_RT>"+query.value("ty_tnd").toString()+"</ID_STR_RT>";
        xml+="<ID_BTNSET>"+query.value("de_tnd").toString()+"</ID_BTNSET>";
        xml+="</buttonconfig>";
        }

   xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
   qDebug() << "resultado  tender: " << xml;
   return xml;
}
//inicia parte de sockets
void websocket_syncronizacion::iniciar(const QUrl &url2){
    if (m_debug)
        qDebug() << "WebSocket server:" << url2;
    connect(&m_webSocket2, &QWebSocket::connected, this, &websocket_syncronizacion::onConnected2);
    connect(&m_webSocket2, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    connect(&m_webSocket2, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    m_webSocket2.open(QUrl(url2));
}

void websocket_syncronizacion::iniciar2(const QString &url3){

    if (m_debug)
        qDebug() << "WebSocket server:" << url3;


    connect(&m_webSocket3, &QWebSocket::connected, this, &websocket_syncronizacion::onConnected3);
    connect(&m_webSocket3, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    connect(&m_webSocket3, &QWebSocket::disconnected, this, &websocket_syncronizacion::closed);
    m_webSocket3.open(QUrl(url3));
}

void websocket_syncronizacion::cerrar_slot(){
    m_webSocket.close();

}

void websocket_syncronizacion::send_message(QString mensaje,int actual){
    actual=settings.getLineMax().toInt();
    mensaje=mensaje.replace(QString("N"),settings.getLineMax());
    if(ai_ln_actual==0){  ai_ln_actual=actual;}
    qDebug()<< "send_message "+mensaje;
    //m_webSocket.sendTextMessage(mensaje);

}
void websocket_syncronizacion::send_message_log_conf(QString mensaje){

    m_webSocket2.sendTextMessage(mensaje);
}
void websocket_syncronizacion::send_message_inst(QString mensaje){
    m_webSocket3.sendTextMessage(mensaje);
}

//! [onConnected]
void websocket_syncronizacion::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected syncronizacion";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &websocket_syncronizacion::onTextMessageReceived);
    //actual=settings.getLineMax().toInt();
    QString mensaje=settings.getLineMax()+","+settings.getIdStore()+","+settings.getIdInstancia()+",x";
    qDebug() << "Inicia gethistcatalogos "<<mensaje;
    m_webSocket.sendTextMessage(mensaje);


}
void websocket_syncronizacion::onConnected2()
{
    if (m_debug)
        qDebug() << "WebSocket connected validacion y log";
    connect(&m_webSocket2, &QWebSocket::textMessageReceived,
            this, &websocket_syncronizacion::onTextMessageReceived);
    //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));


}
void websocket_syncronizacion::onConnected3()
{
    if (m_debug)
        qDebug() << "WebSocket connected instalar";
    connect(&m_webSocket3, &QWebSocket::textMessageReceived,
            this, &websocket_syncronizacion::onTextMessageReceived);
    //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));


}
//! [onConnected]

//! [onTextMessageReceived]
void websocket_syncronizacion::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message.left(50);
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
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
               qDebug() << "Document is not an object" << endl;
               return;
           }
       }
       else
       {
           qDebug() << "Invalid JSON...\n" << message << endl;
           return;
       }

    switch (opciones.indexOf(obj["mensaje"].toString())) {
    case 0:
        qDebug()<<obj["mensaje"].toString()<<" : "<<obj["value"].toString().left(50);
        break;
    case 1:{
         QSqlQuery query(db);
         QJsonArray npcArray = obj["value"].toArray();
         ai_ln_max=npcArray[0].toObject()["ailnmax"].toInt();
         QString insert="insert into histcatalogos(AI_LN,CAT_ACT,OPER,XML,APLICADO) values ";
         qDebug()<<"size "<< npcArray.size() << "ailnmax " <<ai_ln_max;
         for(int x=0;x<npcArray.size();x++){
              QJsonObject npcObject =npcArray[x].toObject();
             if(x==npcArray.size()-1){
                 insert=insert+" ("+QString::number(npcObject["ailn"].toInt())+",'"+npcObject["catact"].toString()+"','"+npcObject["oper"].toString()+"','"+npcObject["xml"].toString()+"',0);";
             }
             else{
                 insert=insert+" ("+QString::number(npcObject["ailn"].toInt())+",'"+npcObject["catact"].toString()+"','"+npcObject["oper"].toString()+"','"+npcObject["xml"].toString()+"',0),";
             }
         }

         qDebug()<<insert;
         if(!query.exec(insert)){
           qDebug() << "ERROR3: " << query.lastError().text();
         }
         query.finish();
         ai_ln_actual=get_max();
         if(ai_ln_actual<ai_ln_max){
             settings.setNewLineMax(QString::number(ai_ln_actual));
             send_message(QString::number(ai_ln_actual)+","+settings.getIdStore()+","+settings.getIdInstancia()+",x",ai_ln_actual);
         }
         else{
            settings.setNewLineMax(QString::number(ai_ln_actual));
            qDebug()<< "terminada " <<ai_ln_actual;
            cerrar_slot();
         }
    }
        break;
    case 2:
        qDebug()<< "respuesta login" <<obj["value"].toString().split(",").at(0);

        emit loginf(obj["value"].toString().split(",").at(0).toInt(),1);
        break;
    case 3:
        qDebug()<< "respuesta instalacion" <<obj["value"].toString();
        valores=obj["value"].toString().split(",");
        a=valores.at(1);
        b= valores.at(2);
        settings.setIdStore(valores.at(2));
        settings.setIdInstancia(valores.at(1));
        emit instalacionCompleta(a.toInt(),b.toInt());
        break;
    case 4:
        qDebug()<< "respuesta confirmacion" <<obj["value"].toString();
        emit confirmado(obj["value"].toInt());
        break;
    case 5:
        qDebug()<< "respuesta a altaexpress" <<obj["value"].toString();
        valores=obj["value"].toString().split(",");
        abc_item(valores.at(1),valores.at(2),valores.at(3),valores.at(4),valores.at(5),valores.at(6),valores.at(7),
                 valores.at(8),valores.at(9),valores.at(10),valores.at(11),valores.at(12),valores.at(2),valores.at(13),
                 valores.at(14),valores.at(15),valores.at(16),valores.at(17),valores.at(18),valores.at(20),"1");
        emit altaExpress(valores.at(0));
        break;
    default:
        break;
    }
}

int websocket_syncronizacion::get_max(){
    QSqlQuery query;
    query.prepare("SELECT ai_ln FROM histcatalogos ORDER BY ai_ln DESC LIMIT 1");
    //query.addBindValue(valuer.toInt());
    if(!query.exec()){
      qDebug() << "ERROR4: " << query.lastError().text();
      return 0;
    }
    while(query.next())
    {
       qDebug() << "RESULTADOS: " << query.value("ai_ln").toString();
        return query.value("ai_ln").toInt();
    }
}
//! [onTextMessageReceived]

//termina parte de sockets

//inicia parte de actualizador

void websocket_syncronizacion::run_hilo_actualizador() {
 qDebug() << "Preparando hilo actualizador;";
 hilo_actualizador *worker = new hilo_actualizador;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        //connect(this, &Controller::operate, worker, &Worker::doWork);
        connect(worker, &hilo_actualizador::setservice, this, &websocket_syncronizacion::muestra_progreso_sincronizacion);
        workerThread.start();

}

void websocket_syncronizacion::muestra_progreso_sincronizacion(double text) {
   setProgreso_actualizacion(text);
;
}

//seters y getters

double websocket_syncronizacion::progreso_actualizacion() const{

    return m_progreso_actualizacion;
}

void websocket_syncronizacion::setProgreso_actualizacion(double value){

    if(m_progreso_actualizacion!=value)m_progreso_actualizacion=value;
    progreso_actualizacionChanged();
}

QString websocket_syncronizacion::abc_item(QString idt, QString sl_prc, QString merch, QString brand, QString exm_tx,
                  QString nombre, QString descripcion, QString ty, QString food,
                  QString spr,QString lu_cnt,QString cp_un_sl,
                  QString id_sl_prc,QString sell,QString list,QString ofer,QString fl_vl, QString itm_ps,
                  QString qfr,QString prep_cc,QString qu){//pic null

    if(prep_cc.length()<=0){
        prep_cc="null";
    }
    if(exm_tx.length()<=0){
        exm_tx="null";
    }

    if(fl_vl.length()<=0||fl_vl.compare("NULL")==0){
        fl_vl="";
    }

    QString query="insert into itemsellprice(id_itm_sl_prc,sell_price,price_list,ofer_price,fl_vl_price) values("+id_sl_prc+","+sell+","+list+","+ofer+",'"+fl_vl+"');"+
            "insert into item(id_itm,id_itm_sl_prc,id_mrhrc_gp,id_brn,lu_exm_tx,nm_itm,de_itm,ty_itm,food_stamp_ex) values("+idt+","+id_sl_prc+","+merch+","+brand+","+exm_tx+",'"+nombre+"','"+descripcion+"','"+ty+"','"+food+"');"+
            "insert into stockitem (id_itm,id_spr,lu_cnt_sls_wt_un,cp_un_sl_ls_rsv) values("+idt+","+spr+",'"+lu_cnt+"',"+cp_un_sl+");"+
            "insert into posidentity(id_itm_ps,id_itm_ps_qfr,id_itm_sl_prc,id_itm,id_prep_cc,qu_itm,activo) values('"+itm_ps+"',"+qfr+","+id_sl_prc+","+idt+","+prep_cc+","+qu+",'S');"+
            "insert into itempictures(id_itm,picture) values ("+idt+", null);";
    qDebug()<< " query "+query;
   return ejecutaQuery(query);

}

QString websocket_syncronizacion::ejecutaQuery(QString quer){
   QSqlQuery query(db);
   //separados por ; cada insert

   QStringList scriptQueries = quer.split(";");
   foreach (QString queryTxt, scriptQueries)
       {
           if (queryTxt.trimmed().isEmpty()) {
               continue;
           }
           if (!query.exec(queryTxt))
           {
               qDebug() << "ERROR: " << query.lastError().text();
               //qFatal(QString("One of the query failed to execute."
                 //          " Error detail: " + query.lastError().text()).toLocal8Bit());
           }
           query.finish();
       }
return "ok";
}

