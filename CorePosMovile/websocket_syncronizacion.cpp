#include "websocket_syncronizacion.h"
#include "hilo_actualizador.h"
QT_USE_NAMESPACE
websocket_syncronizacion::websocket_syncronizacion(){}
void websocket_syncronizacion::init_websocket(){
    ai_ln_actual=0;
    ai_ln_max=0;
    setProgreso_actualizacion( 0);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pruebas");
    if(!db.open()){
        qDebug() << "Error syncronizacion 1: " << db.lastError();
    }
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
      QString script="CREATE TABLE Bank (ID_BN integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6),NM_BN varchar(40));CREATE TABLE BusinessDay (DC_DY_BSN timestamp,ID_STR_RT integer,AI_TRN integer,ID_WS integer,TS_BGN timestamp,TS_END timestamp,PRIMARY KEY (DC_DY_BSN, ID_STR_RT));CREATE TABLE ButtonConfig (ID_STR_RT integer,ID_BTNSET smallint,ID_BTN integer,ID_BTN_PRNT integer,TY_BTN char(2) DEFAULT 'PR',BTN_WT smallint,NM_BTN varchar(20),DE_BTN varchar(255),PIC bytea,ID_ITM integer,ICON_ADDRESS varchar(50),ID_STRGRP integer,ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer,WEBADDRESS varchar(255),WEBSERV_NAME varchar(255),PARAMS_LIST text,POSITION smallint,PRIMARY KEY (ID_STR_RT, ID_BTNSET,ID_BTN));CREATE TABLE ButtonSets (ID_STR_RT integer,ID_BTNSET smallint,DE_BTNSET varchar(40),FL_COMPOR_RET char(1) DEFAULT 'H',PRIMARY KEY (ID_STR_RT, ID_BTNSET));CREATE TABLE ConfiguracionGral (ID_INSTANCIA integer PRIMARY KEY,BTNHOME boolean,DESGLOSAIMPUESTOS boolean,HASVIRTUALWINDOW boolean,IDMERCHANT integer,IMPUESTOPORIG boolean,ISNEW boolean,LINEMAX bigint,SCALE integer,SCALETYPE varchar(6) DEFAULT 'SERIAL0',SCALEPORT varchar(10),SCALEREMLEFT varchar(10),SCALEREQUEST varchar(10),SCALEREMRIGHT varchar(10),TAXINPRICE boolean,TRAINING boolean,UPDATEPOS boolean,VERSION varchar(20),WINDOWWIDTH integer,WINDOWHIGH integer);CREATE TABLE Customer (ID_CT bigint PRIMARY KEY,CV_CT char(8),ID_PRTY integer,NM_CT varchar(40),NM_ORGN varchar(60),ID_TX_IRGN varchar(255),ID_TX_FDL varchar(40),RFC_TAXID varchar(40),DESGLOSA_IEPS char(1),ID_PRS_LST integer);CREATE TABLE CustomerAddress (ID_ADS integer PRIMARY KEY,ID_CT bigint,DC_EF timestamp,DC_EP timestamp,DOMICILIO varchar(60),COLONIA varchar(40),CIUDAD varchar(40),ESTADO varchar(50),PAIS varchar(40),CP varchar(10),DIR_FACTURA char(1),DIR_ENTREG char(1));CREATE TABLE DerivatedPrice (ID_PRC_LST integer,ID_ITM_SL_PRC integer,PRICE decimal(10,4),ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer,PRIMARY KEY (ID_PRC_LST,ID_ITM_SL_PRC,PRICE ));CREATE TABLE Descuentos (ID_DSC integer PRIMARY KEY,NM_DSC varchar(40),DE_DSC varchar(255),CD_RDN_MTH char(2),MO_RDN_AMT decimal(8,3),PR_RDN_AMT decimal(5,2),MO_NW_PRC decimal(8,3));CREATE TABLE DisbursementFundsReceiptReason (ID_RCV_DSB integer PRIMARY KEY,DE_RCV_DSB varchar(20),TY_RCV char(1));CREATE TABLE External_User (ID_EXTU integer PRIMARY KEY,USER varchar(20),PWD varchar(20),TY_USR char(1) DEFAULT 'I',TY_TND char(4),ID_ITM integer);CREATE TABLE GroupResourceAccess (ID_GP_WRK integer,ID_RS integer,PS_ACS_GP_RD char(2),PS_ACS_GP_WR char(2),PRIMARY KEY (ID_GP_WRK,ID_RS,PS_ACS_GP_RD,PS_ACS_GP_WR));CREATE TABLE HistCatalogos (DC_DY_BSN timestamp,AI_LN bigint,ID_OPR integer,ID_STR_RT integer,CAT_ACT varchar(50),DT_ACT timestamp,OPER varchar(50),XML text,APLICADO integer,PRIMARY KEY (DC_DY_BSN,AI_LN,ID_OPR,ID_STR_RT ));CREATE TABLE Item (ID_ITM integer PRIMARY KEY,ID_SPR integer,ID_ITM_SL_PRC integer,ID_MRHRC_GP integer,ID_BRN integer,NM_UOM varchar(15),LU_EXM_TX integer,NM_ITM varchar(40),DE_ITM varchar(255),TY_ITM char(6),TY_ITM_SV char(2),ID_GP_TX integer,ID_GP_TX_BUY integer,URL varchar(255),ETIQUETA_IMPORTE varchar(255),ETIQUETA_POST varchar(255),QML varchar(255),VTA_CANCEL varchar(2) DEFAULT 'SI',FOOD_STAMP_EX char(1));CREATE TABLE ItemCollection (ID_ITM integer,ID_ITM_COL integer,AI_ITM_COL smallint,QU_ITM_PR_ASMB decimal(9,3),PE_BLO decimal(5,2),PRIMARY KEY (ID_ITM,ID_ITM_COL ));CREATE TABLE ItemPictures (ID_ITM integer,ID_SEQ INTEGER, PICTURE bytea, URL varchar(150), PRIMARY KEY (ID_ITM, id_seq) );CREATE TABLE ItemSellPrice (ID_ITM_SL_PRC integer PRIMARY KEY,SELL_PRICE decimal(8,4),PRICE_LIST decimal(10,4),OFER_PRICE decimal(10,4),PE_PRICE decimal(5,2),FL_VL_PRICE char(1));CREATE TABLE ItemVolumePrice (ID_ITM_SL_PRC integer,AL_LN_PRC smallint,ID_PRC_LST integer,MIN_QTY decimal(10,4),MAX_QTY decimal(10,4),PRIMARY KEY (ID_ITM_SL_PRC,AL_LN_PRC));CREATE TABLE Languaje (ID_LNG smallint PRIMARY KEY,LANGUAJE varchar(20));CREATE TABLE Mensajes (ID_RS integer,ID_LNG smallint,ID_MSJ integer,MENSAJE varchar(255),PRIMARY KEY (ID_RS,ID_LNG,ID_MSJ));CREATE TABLE MerchandiseHierarchyGroup (ID_MRHRC_GP integer PRIMARY KEY,ID_MRHC_PRNT integer,NM_MRHRC_GP varchar(40),PE_PROFIT decimal(10,4),ID_GP_TX integer,FOOD_STAMP_EX char(1) DEFAULT 'N');CREATE TABLE Operator (ID_OPR integer,ID_STR_RT integer,ID_EM integer,NM_OPR varchar(30),PWD_ACS_OPR varchar(15),BLOQUED_TIME timestamp,PRIMARY KEY (ID_OPR,ID_STR_RT));CREATE TABLE OperatorGroup (ID_STR_RT integer,ID_GP_WRK integer,ID_OPR integer,ID_RS INTEGER,PRIMARY KEY (ID_STR_RT,ID_GP_WRK,ID_OPR));CREATE TABLE Ports (PORT varchar(10) PRIMARY KEY,BAUDRATE varchar(50),DATABITS varchar(50),FLOWCONTROL varchar(50),REMRI varchar(50),PARITY varchar(50),STOPBITS varchar(50));CREATE TABLE POSIdentity (ID_ITM_PS varchar(30),ID_ITM_PS_QFR integer DEFAULT 1,ID_ITM_SL_PRC integer,ID_ITM integer,ID_PREP_CC integer,Qu_ITM decimal(10,4),ACTIVO char(1) DEFAULT 'S',PRIMARY KEY (ID_ITM_PS,ID_ITM_PS_QFR,ID_ITM));CREATE TABLE RetailStore (ID_STR_RT integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6) DEFAULT 'SUCURS',ID_STRGRP integer,DC_OPN_RT_STR date,DC_CL_RT_STR date,NM_STR_RT varchar(40),DOMICILIO varchar(60),COLONIA  varchar(40),CIUDAD varchar(40),ESTADO varchar(40),PAIS varchar(50),CP varchar(10),ENC_PRN1 varchar(22),ENC_PRN2 varchar(22),PIE_PRN1 varchar(22),PIE_PRN2 varchar(22),ID_MERCHANT_ED integer,LOGIN_ED varchar(10),PASWORD_ED varchar(10),BANK_AUTO_ED varchar(20),POSITION1 varchar(40),POSITION2 varchar(40),POSITION3 varchar(40),POSITION4 varchar(40),POSITION5 varchar(40),POSITION6 varchar(40),LOGO1 bytea,LOGO2 bytea,permite_venta_rojo VARCHAR(1));CREATE TABLE Safety (ID_STR_RT integer,ID_SFTY bigint,DEPOSITO decimal(15,4),GARANTIZADO decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_SFTY));CREATE TABLE Safety_Log (ID_STR_RT integer,ID_SFTY bigint,ID_TRAN integer,TY_OPER char(1),DC_OPER timestamp,AMOUNT decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_SFTY,ID_TRAN));CREATE TABLE Scales (SCALE integer PRIMARY KEY,NM_SCALE varchar(40),SCALETYPE varchar(6),BAUDRATE varchar(50),DATABITS varchar(50),FLOWCONTROL varchar(50),PARITY varchar(50),REMLEFT varchar(50),REMRIGHT varchar(50),REQUEST varchar(50),STOPBITS varchar(50));CREATE TABLE ServiceItem (ID_ITM integer PRIMARY KEY,ID_SPR integer,CP_BS_SV_ITM decimal(10,4),CP_NT_SV_ITM decimal(10,4),PE_BS_SV_ITM decimal(5,2),PE_NT_SV_ITM decimal(5,2),TY_CLC_SV_ITEM char(2),DC_CST_EST_SV_ITM timestamp,TY_ITM_SV char(6),WEB_URL varchar(255),ETIQUETA_IMPORTE varchar(255),ETIQUETA_POST varchar(255),QML_FILE varchar(255),VTA_CANCEL varchar(2),CARGO_XFPAG varchar(1),FM_CLC_SV_ITEM varchar(1));CREATE TABLE Session (ID_STR_RT integer,ID_WS integer,ID_OPR integer,TS_TM_STR timestamp,AI_TRN_BGN integer,AI_TRN_END integer,DC_DY_BSN_BGN timestamp,DC_DY_BSN_END timestamp,TS_END timestamp,PRIMARY KEY (ID_STR_RT,ID_WS,ID_OPR,TS_TM_STR));CREATE TABLE StockItem (ID_ITM integer PRIMARY KEY,ID_SPR integer,NM_UOM varchar(40),LU_CNT_SLS_WT_UN char(2),CP_UN_SL_LS_RSV decimal(10,5),DC_CST_EST_LS_RCV timestamp);CREATE TABLE Supplier (ID_SPR integer PRIMARY KEY,ID_PRTY integer,TY_RO_PRTY char(6),NM_SPR varchar(40),DU_SPR char(9),FL_MF_SPR_IS char(1),PERIODICITY integer,MONEY_ORDER char(1));CREATE TABLE TaxableGroup (ID_GP_TX integer PRIMARY KEY,NM_GP_TX varchar(40),CD_RCPT_PRN varchar(2));CREATE TABLE TaxGroupRule (ID_ATHY_TX integer,ID_GP_TX integer,AI_CMPND smallint,NM_RU_TX varchar(20),ID_ACNT_LDG integer,PRIMARY KEY (ID_ATHY_TX,ID_GP_TX ));CREATE TABLE TaxRateRule (ID_ATHY_TX integer,ID_GP_TX integer,AI_TX_RT_RU smallint,TY_TX_RT_RU char(2) DEFAULT 'PE',MO_TXBM_MNM decimal(15,4),MO_TXBL_MXM decimal(15,4),MO_RT_TX decimal(15,5),PE_RT_TX decimal(10,4),PRIMARY KEY (ID_ATHY_TX,ID_GP_TX,AI_TX_RT_RU));CREATE TABLE Tender (TY_TND char(4) PRIMARY KEY,ID_ACT_LDG integer,ID_CNY integer,DE_TND varchar(255),FL_NMB_SRZ smallint,FL_AZN_RQ smallint,LU_MTH_AZN varchar(4),FL_DT_AZN_EP_RQ char(1) DEFAULT 'N',IN_WIT_AZN_MXM_ALOW smallint,FL_IDTN_RQ_CT smallint,FL_ID_PRSL_RQ smallint,FL_AVLB_LCL_CNY smallint,FL_SGNTR_CT_RQ smallint,MO_TH_TND_CHN decimal(14,3),FL_DRW_OPEN smallint,MO_APVL_TNDCE_OFF decimal(15,4),FL_ENDSM_RQ smallint,PLAZOS char(1) DEFAULT 'N',ID_ITM_PS varchar(30),BTN_ASIGNED char(4),FOOD_STAMP_EX char(1));CREATE TABLE TenderPlazo (TY_TND char(4),TY_TND_LN smallint,DIAS decimal(3),PE_MONTO decimal(5,2),PRIMARY KEY (TY_TND,TY_TND_LN));CREATE TABLE Till (ID_STR_RT integer,ID_RPSTY_TND integer,ID_WS integer,ID_OPR integer,SC_TL char(2),TS_TST_TL timestamp,CP_BLNC_DFLT_OPN decimal(14,3),LU_TND_MXM_ALW decimal(14,3),PRIMARY KEY (ID_STR_RT,ID_RPSTY_TND));CREATE TABLE TillTender (ID_STR_RT integer,ID_RPSTY_TND integer,ID_WS integer,TY_TND char(4),TOTAL_DEPOSITOS decimal(15,4),TOTAL_RETIROS decimal(15,4),TOTAL_INGRESOS decimal(15,4),TOTAL_CAMBIOS decimal(15,4),TOTAL_PAGOS decimal(15,4),TOTAL_PAGOS_MENORES decimal(15,4),TOTAL_COBROS_MENORES decimal(15,4),PRIMARY KEY (ID_STR_RT,ID_RPSTY_TND,ID_WS,TY_TND));CREATE TABLE Transactions (ID_STR_RT integer,ID_WS integer,DC_DY_BSN timestamp,AI_TRN integer,ID_OPR integer,TS_TM_STR timestamp,TY_TRN varchar(6),TS_TRN_BGN timestamp,TS_TRN_END timestamp,FL_CNCL smallint,FL_VD smallint,FL_TRG_TRN smallint,FL_KEY_OFL smallint,XML text,PRIMARY KEY (ID_STR_RT,ID_WS,DC_DY_BSN,AI_TRN));CREATE TABLE TY_ID (TY_ID char(2) PRIMARY KEY,NM_ID varchar(20));CREATE TABLE WorkStation (ID_STR_RT integer,ID_WS integer,ID_EQ integer,SERIE varchar(30),QU_TL_WS decimal(3),FL_MOD_TRG smallint,FL_KEYBOARD smallint,ID_BTNSET bigint,ID_POS_ED integer,PRIMARY KEY (ID_STR_RT,ID_WS))";
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
      QString script="INSERT INTO ButtonSets (ID_STR_RT,ID_BTNSET,DE_BTNSET,FL_COMPOR_RET) VALUES ( '1', '1', 'principal', '''H''' ); INSERT INTO Item (ID_ITM,ID_ITM_SL_PRC,ID_MRHRC_GP,ID_BRN,NM_ITM,DE_ITM,TY_ITM,ID_GP_TX,ID_GP_TX_BUY,VTA_CANCEL,FOOD_STAMP_EX) VALUES (1, 1, 319, 137, 'BISTECK DE RES LB', 'BISTECK DE RES LB', 'STOK', 1, 1, 'SI', 'S'),  (2, 2, 319, 137, 'CHORIZO CHICANO CAJA 10/4LB', 'CHORIZO CHICANO CAJA 10/4LB', 'STOK', 1, 1, 'SI', 'S'),  (3, 3, 319, 137, 'CHORIZO CHICANO 1 PZ /4LB', 'CHORIZO CHICANO 1 PZ /4LB', 'STOK', 1, 1, 'SI', 'S'),  (4, 4, 319, 137, 'EL POPULAR CHORIZO no return 12 / 15 OZ', 'EL POPULAR CHORIZO no return 12 / 15 OZ', 'STOK', 1, 1, 'SI', 'S'),  (5, 5, 319, 137, 'MILAN QUESO PUERCO GRANDE', 'MILAN QUESO PUERCO GRANDE', 'STOK', 1, 1, 'SI', 'S'),  (6, 6, 319, 137, 'VER-MEX CHORIZO PIEZA 14 OZ', 'VER-MEX CHORIZO PIEZA 14 OZ', 'STOK', 1, 1, 'SI', 'S'),  (7, 7, 319, 137, 'VER-MEX CHORIZO PIEZA 3 LB', 'VER-MEX CHORIZO PIEZA 3 LB', 'STOK', 1, 1, 'SI', 'S'),  (8, 8, 319, 137, 'VER-MEX LONGANIZA PIEZA 10 OZ', 'VER-MEX LONGANIZA PIEZA 10 OZ', 'STOK', 1, 1, 'SI', 'S'),  (9, 9, 319, 137, 'MI RANCHITO:MR CECINA LB/ GR', 'MI RANCHITO:MR CECINA LB/ GR', 'STOK', 1, 1, 'SI', 'S'),  (10, 10, 319, 137, 'MI RANCHITO:MR CHICHA  LB/GR', 'MI RANCHITO:MR CHICHA  LB/GR', 'STOK', 1, 1, 'SI', 'S'),  (11, 11, 319, 137, 'MI RANCHITO:MR CHICHA GRU', 'MI RANCHITO:MR CHICHA GRU', 'STOK', 1, 1, 'SI', 'S'),  (12, 12, 319, 137, 'MI RANCHITO:MR CHOR LB/GRA', 'MI RANCHITO:MR CHOR LB/GRA', 'STOK', 1, 1, 'SI', 'S'),  (13, 13, 319, 137, 'MI RANCHITO:MR ENCHLBS/GRA', 'MI RANCHITO:MR ENCHLBS/GRA', 'STOK', 1, 1, 'SI', 'S'),  (14, 14, 319, 137, 'Mi Ranchito Tlales pq', 'Mi Ranchito Tlales pq', 'STOK', 1, 1, 'SI', 'S'),  (15, 15, 316, 137, 'AGUACATE 40 #2', 'AGUACATE 40 #2', 'STOK', 1, 1, 'SI', 'S'),  (16, 16, 316, 137, 'CACAHUATE ENCH.(Botana), LBS', 'CACAHUATE ENCH.(Botana), LBS', 'STOK', 1, 1, 'SI', 'S'),  (17, 17, 316, 137, 'CACAHUATE JAPONES LBS', 'CACAHUATE JAPONES LBS', 'STOK', 1, 1, 'SI', 'S'),  (18, 18, 316, 137, 'Chicharrin suelto', 'Chicharrin suelto', 'STOK', 1, 1, 'SI', 'S'),  (19, 19, 316, 137, 'CHICHARRIN 4X8', 'CHICHARRIN 4X8', 'STOK', 1, 1, 'SI', 'S'),  (20, 20, 316, 137, 'CHICHARRIN LAG LB', 'CHICHARRIN LAG LB', 'STOK', 1, 1, 'SI', 'S'),  (21, 21, 316, 137, 'Chicharrin Lagrimita', 'Chicharrin Lagrimita', 'STOK', 1, 1, 'SI', 'S'),  (22, 22, 316, 137, 'CHICHARRIN RUE LB', 'CHICHARRIN RUE LB', 'STOK', 1, 1, 'SI', 'S'),  (23, 23, 316, 137, 'CHICHARRIN TOR LB', 'CHICHARRIN TOR LB', 'STOK', 1, 1, 'SI', 'S'),  (24, 24, 316, 137, 'CHILE MOLIDO C/LIMON LBS', 'CHILE MOLIDO C/LIMON LBS', 'STOK', 1, 1, 'SI', 'S'),  (25, 25, 316, 137, 'CHURRITOS PLAIN (Botana), LBS', 'CHURRITOS PLAIN (Botana), LBS', 'STOK', 1, 1, 'SI', 'S'),  (26, 26, 316, 137, 'CILANTRO FLORIDA RAIZ', 'CILANTRO FLORIDA RAIZ', 'STOK', 1, 1, 'SI', 'S'),  (27, 27, 328, 137, 'COBERTOR', 'COBERTOR', 'STOK', 1, 1, 'SI', 'N'),  (28, 28, 316, 137, 'coco rayado lbs', 'coco rayado lbs', 'STOK', 1, 1, 'SI', 'S'),  (29, 29, 316, 137, 'DORADILLA LB', 'DORADILLA LB', 'STOK', 1, 1, 'SI', 'S'),  (30, 30, 316, 137, 'DULCES Y GALLETAS:PELO ELOTE LB', 'DULCES Y GALLETAS:PELO ELOTE LB', 'STOK', 1, 1, 'SI', 'S'),  (31, 31, 316, 137, 'EPAZOTE SECO LB', 'EPAZOTE SECO LB', 'STOK', 1, 1, 'SI', 'S'),  (32, 32, 316, 137, 'ESENCIA DE NIEVE LIMON PIEZA', 'ESENCIA DE NIEVE LIMON PIEZA', 'STOK', 1, 1, 'SI', 'S'),  (33, 33, 316, 137, 'ESPECIES ENPACADAS', 'ESPECIES ENPACADAS', 'STOK', 1, 1, 'SI', 'S'),  (34, 34, 316, 137, 'CACAHUATE CASCARA 40 LIBRA..', 'CACAHUATE CASCARA 40 LIBRA..', 'STOK', 1, 1, 'SI', 'S'),  (35, 35, 328, 137, 'FLETE', 'FLETE', 'STOK', 1, 1, 'SI', 'N'),  (36, 36, 316, 137, 'Garbanzo Lb', 'Garbanzo Lb', 'STOK', 1, 1, 'SI', 'S'),  (37, 37, 316, 137, 'GENGIBRE ', 'GENGIBRE ', 'STOK', 1, 1, 'SI', 'S'),  (38, 38, 316, 137, 'Frijol Quebrado lb', 'Frijol Quebrado lb', 'STOK', 1, 1, 'SI', 'S'),  (39, 39, 316, 137, 'Limon verde', 'Limon verde', 'STOK', 1, 1, 'SI', 'S'),  (40, 40, 316, 137, 'GROCERY:LEMON GRASS', 'GROCERY:LEMON GRASS', 'STOK', 1, 1, 'SI', 'S'),  (41, 41, 316, 137, 'HABA  LB', 'HABA  LB', 'STOK', 1, 1, 'SI', 'S'),  (42, 42, 328, 137, 'LIMPIEZA:ESTROPAJO LAR', 'LIMPIEZA:ESTROPAJO LAR', 'STOK', 1, 1, 'SI', 'S'),  (43, 43, 328, 137, 'LIMPIEZA:ESTROPAJO REDON', 'LIMPIEZA:ESTROPAJO REDON', 'STOK', 1, 1, 'SI', 'S'),  (44, 44, 316, 137, 'MANGO SLICES', 'MANGO SLICES', 'STOK', 1, 1, 'SI', 'S'),  (45, 45, 319, 137, 'MILAN CHORIZO JALAPENO PIEZA', 'MILAN CHORIZO JALAPENO PIEZA', 'STOK', 1, 1, 'SI', 'S'),  (46, 46, 316, 137, 'MUITLE LB', 'MUITLE LB', 'STOK', 1, 1, 'SI', 'S'),  (47, 47, 316, 137, 'MUITLE PTS', 'MUITLE PTS', 'STOK', 1, 1, 'SI', 'S'),  (48, 48, 328, 137, 'MOLCAJETE PIEDRA PIEZA', 'MOLCAJETE PIEDRA PIEZA', 'STOK', 1, 1, 'SI', 'N'),  (49, 49, 316, 137, 'MOLE POBLANO', 'MOLE POBLANO', 'STOK', 1, 1, 'SI', 'S'),  (50, 50, 316, 137, 'MUSTARD GREEN', 'MUSTARD GREEN', 'STOK', 1, 1, 'SI', 'S'),  (51, 51, 316, 137, 'PINOLE LB', 'PINOLE LB', 'STOK', 1, 1, 'SI', 'S'),  (52, 52, 316, 137, 'PISTACHIOS (Botana), LBS', 'PISTACHIOS (Botana), LBS', 'STOK', 1, 1, 'SI', 'S'),  (53, 53, 328, 137, 'OTROS:CAZO COBRE', 'OTROS:CAZO COBRE', 'STOK', 1, 1, 'SI', 'N'),  (54, 54, 328, 137, 'OTROS:COMAL L/ DEL', 'OTROS:COMAL L/ DEL', 'STOK', 1, 1, 'SI', 'N'),  (55, 55, 328, 137, 'OTROS:COMAL RED/DEL', 'OTROS:COMAL RED/DEL', 'STOK', 1, 1, 'SI', 'N'),  (56, 56, 328, 137, 'OTROS:EXPRIMIDOR LIMON', 'OTROS:EXPRIMIDOR LIMON', 'STOK', 1, 1, 'SI', 'N'),  (57, 57, 328, 137, 'OTROS:FAJAS PUDIN', 'OTROS:FAJAS PUDIN', 'STOK', 1, 1, 'SI', 'N'),  (58, 58, 328, 137, 'OTROS:JUEGO DE MESA', 'OTROS:JUEGO DE MESA', 'STOK', 1, 1, 'SI', 'N'),  (59, 59, 316, 137, 'PALO ENCINO LB', 'PALO ENCINO LB', 'STOK', 1, 1, 'SI', 'S'),  (60, 60, 316, 137, 'PALO MAD P/ ELO', 'PALO MAD P/ ELO', 'STOK', 1, 1, 'SI', 'S'),  (61, 61, 316, 137, 'PERSIMMON', 'PERSIMMON', 'STOK', 1, 1, 'SI', 'S'),  (62, 62, 316, 137, 'AGUACATE  FLORIDA  CT 18/1', 'AGUACATE  FLORIDA  CT 18/1', 'STOK', 1, 1, 'SI', 'S'),  (63, 63, 316, 137, 'AGUACATE FLORIDA 12CT', 'AGUACATE FLORIDA 12CT', 'STOK', 1, 1, 'SI', 'S'),  (64, 64, 316, 137, 'AJO PELADO-PEELED GARLIC 20/1LB', 'AJO PELADO-PEELED GARLIC 20/1LB', 'STOK', 1, 1, 'SI', 'S'),  (65, 65, 316, 137, 'ALBACAR SUELTA- LOOSE BASIL', 'ALBACAR SUELTA- LOOSE BASIL', 'STOK', 1, 1, 'SI', 'S'),  (66, 66, 316, 137, 'ALFALBA', 'ALFALBA', 'STOK', 1, 1, 'SI', 'S'),  (67, 67, 316, 137, 'APIO RAIZ', 'APIO RAIZ', 'STOK', 1, 1, 'SI', 'S'),  (68, 68, 316, 137, 'APIO- CELERY CELLO  30PZ / BOLSA', 'APIO- CELERY CELLO  30PZ / BOLSA', 'STOK', 1, 1, 'SI', 'S'),  (69, 69, 316, 137, 'APRICOT', 'APRICOT', 'STOK', 1, 1, 'SI', 'S'),  (70, 70, 316, 137, 'ARTICHOKE-ALCACHOFA', 'ARTICHOKE-ALCACHOFA', 'STOK', 1, 1, 'SI', 'S'),  (71, 71, 316, 137, 'ARUGULA', 'ARUGULA', 'STOK', 1, 1, 'SI', 'S'),  (72, 72, 316, 137, 'BANANA MANZANO 15LB', 'BANANA MANZANO 15LB', 'STOK', 1, 1, 'SI', 'S'),  (73, 73, 316, 137, 'BABY BELLA', 'BABY BELLA', 'STOK', 1, 1, 'SI', 'S'),  (74, 74, 316, 137, 'BABY SPINACH', 'BABY SPINACH', 'STOK', 1, 1, 'SI', 'S'),  (75, 75, 316, 137, 'BANANA MADURA ', 'BANANA MADURA ', 'STOK', 1, 1, 'SI', 'S'),  (76, 76, 316, 137, 'BANANA AMARILLA-BANACOL', 'BANANA AMARILLA-BANACOL', 'STOK', 1, 1, 'SI', 'S'),  (77, 77, 316, 137, 'BANANANA  AMARILLA DEL MONTE', 'BANANANA  AMARILLA DEL MONTE', 'STOK', 1, 1, 'SI', 'S'),  (78, 78, 316, 137, 'BANANA BABY MADURA 15LB', 'BANANA BABY MADURA 15LB', 'STOK', 1, 1, 'SI', 'S'),  (79, 79, 316, 137, 'BANANA  AMARILLA  CHIQUITA', 'BANANA  AMARILLA  CHIQUITA', 'STOK', 1, 1, 'SI', 'S'),  (80, 80, 316, 137, 'BANANA MANZANO 20LBS', 'BANANA MANZANO 20LBS', 'STOK', 1, 1, 'SI', 'S'),  (81, 81, 316, 137, 'BANANA AMARILLA SELVATICA', 'BANANA AMARILLA SELVATICA', 'STOK', 1, 1, 'SI', 'S'),  (82, 82, 316, 137, 'BANANA  AMARILLA TURBANA', 'BANANA  AMARILLA TURBANA', 'STOK', 1, 1, 'SI', 'S'),  (83, 83, 316, 137, 'BATATA FLORIDA  BONIATO 40LB', 'BATATA FLORIDA  BONIATO 40LB', 'STOK', 1, 1, 'SI', 'S'),  (84, 84, 316, 137, 'BATATA ORIENTALJUMBO CALIF 50LB', 'BATATA ORIENTALJUMBO CALIF 50LB', 'STOK', 1, 1, 'SI', 'S'),  (85, 85, 316, 137, 'BEAN SPROUTS', 'BEAN SPROUTS', 'STOK', 1, 1, 'SI', 'S'),  (86, 86, 316, 137, 'BERENJENA DOMINICANA-EGGPLANT DR.', 'BERENJENA DOMINICANA-EGGPLANT DR.', 'STOK', 1, 1, 'SI', 'S'),  (87, 87, 316, 137, 'BERENJENA negra', 'BERENJENA negra', 'STOK', 1, 1, 'SI', 'S'),  (88, 88, 316, 137, 'BERRO ', 'BERRO ', 'STOK', 1, 1, 'SI', 'S'),  (89, 89, 316, 137, 'BETABEL- BEETS TX', 'BETABEL- BEETS TX', 'STOK', 1, 1, 'SI', 'S'),  (90, 90, 316, 137, 'BETABEL EN MANOJO-BEETS  BUNCH', 'BETABEL EN MANOJO-BEETS  BUNCH', 'STOK', 1, 1, 'SI', 'S'),  (91, 91, 316, 137, 'BETABEL SUELTO- LOOSE BEET 25LB', 'BETABEL SUELTO- LOOSE BEET 25LB', 'STOK', 1, 1, 'SI', 'S'),  (92, 92, 316, 137, 'BLACK BERRY', 'BLACK BERRY', 'STOK', 1, 1, 'SI', 'S'),  (93, 93, 316, 137, 'BLUEBERRY', 'BLUEBERRY', 'STOK', 1, 1, 'SI', 'S'),  (94, 94, 316, 137, 'BOK CHOY', 'BOK CHOY', 'STOK', 1, 1, 'SI', 'S'),  (95, 95, 316, 137, 'BOSTON LETTUCE', 'BOSTON LETTUCE', 'STOK', 1, 1, 'SI', 'S'),  (96, 96, 316, 137, 'BROCOLI', 'BROCOLI', 'STOK', 1, 1, 'SI', 'S'),  (97, 97, 316, 137, 'BRUSSEL SPROUT', 'BRUSSEL SPROUT', 'STOK', 1, 1, 'SI', 'S'),  (98, 98, 316, 137, 'BULB SCALLION', 'BULB SCALLION', 'STOK', 1, 1, 'SI', 'S'),  (99, 99, 316, 137, 'BUTTERNUT SQUASH', 'BUTTERNUT SQUASH', 'STOK', 1, 1, 'SI', 'S'),  (100, 100, 316, 137, 'CACAHUATE CASCARA 25  LIBRA', 'CACAHUATE CASCARA 25  LIBRA', 'STOK', 1, 1, 'SI', 'S'); INSERT INTO ItemSellPrice (ID_ITM_SL_PRC,SELL_PRICE,PRICE_LIST,OFER_PRICE) VALUES (1, 0.0000, 0.0000, 0.0000),(2, 0.0000, 0.0000, 0.0000),(3, 0.0000, 0.0000, 0.0000),(4, 0.0000, 0.0000, 0.0000),(5, 0.0000, 0.0000, 0.0000),(6, 0.0000, 0.0000, 0.0000),(7, 0.0000, 0.0000, 0.0000),(8, 0.0000, 0.0000, 0.0000),(9, 0.0000, 0.0000, 0.0000),(10, 0.0000, 0.0000, 0.0000),(11, 0.0000, 0.0000, 0.0000),(12, 0.0000, 0.0000, 0.0000),(13, 0.0000, 0.0000, 0.0000),(14, 2.2500, 2.2500, 0.0000),(15, 0.0000, 0.0000, 0.0000),(16, 0.0000, 0.0000, 0.0000),(17, 0.0000, 0.0000, 0.0000),(18, 1.1500, 1.1500, 0.0000),(19, 0.0000, 0.0000, 0.0000),(20, 1.1000, 1.1000, 0.0000),(21, 1.1000, 1.1000, 0.0000),(22, 0.0000, 0.0000, 0.0000),(23, 0.0000, 0.0000, 0.0000),(24, 0.0000, 0.0000, 0.0000),(25, 0.0000, 0.0000, 0.0000),(26, 0.0000, 0.0000, 0.0000),(27, 0.0000, 0.0000, 0.0000),(28, 0.0000, 0.0000, 0.0000),(29, 0.0000, 0.0000, 0.0000),(30, 0.0000, 0.0000, 0.0000),(31, 0.0000, 0.0000, 0.0000),(32, 0.0000, 0.0000, 0.0000),(33, 0.0000, 0.0000, 0.0000),(34, 0.0000, 0.0000, 0.0000),(35, 0.0000, 0.0000, 0.0000),(36, 0.9900, 0.9900, 0.0000),(37, 0.9900, 0.9900, 0.0000),(38, 2.9900, 2.9900, 0.0000),(39, 1.0000, 1.0000, 0.0000),(40, 0.0000, 0.0000, 0.0000),(41, 2.4900, 2.4900, 0.0000),(42, 0.0000, 0.0000, 0.0000),(43, 0.0000, 0.0000, 0.0000),(44, 0.0000, 0.0000, 0.0000),(45, 0.0000, 0.0000, 0.0000),(46, 0.0000, 0.0000, 0.0000),(47, 0.0000, 0.0000, 0.0000),(48, 0.0000, 0.0000, 0.0000),(49, 0.0000, 0.0000, 0.0000),(50, 0.0000, 0.0000, 0.0000),(51, 0.0000, 0.0000, 0.0000),(52, 0.0000, 0.0000, 0.0000),(53, 0.0000, 0.0000, 0.0000),(54, 0.0000, 0.0000, 0.0000),(55, 0.0000, 0.0000, 0.0000),(56, 0.0000, 0.0000, 0.0000),(57, 0.0000, 0.0000, 0.0000),(58, 0.0000, 0.0000, 0.0000),(59, 0.0000, 0.0000, 0.0000),(60, 0.0000, 0.0000, 0.0000),(61, 0.8900, 0.8900, 0.0000),(62, 0.0000, 0.0000, 0.0000),(63, 1.9900, 1.9900, 0.0000),(64, 0.0000, 0.0000, 0.0000),(65, 0.9900, 0.9900, 0.0000),(66, 0.0000, 0.0000, 0.0000),(67, 1.9900, 1.9900, 0.0000),(68, 0.0000, 0.0000, 0.0000),(69, 1.3900, 1.3900, 0.0000),(70, 1.8900, 1.8900, 0.0000),(71, 0.0000, 0.0000, 0.0000),(72, 0.0000, 0.0000, 0.0000),(73, 0.0000, 0.0000, 0.0000),(74, 0.0000, 0.0000, 0.0000),(75, 1.0000, 1.0000, 0.0000),(76, 0.4900, 0.4900, 0.0000),(77, 0.4900, 0.4900, 0.0000),(78, 0.0000, 0.0000, 0.0000),(79, 0.0000, 0.0000, 0.0000),(80, 0.0000, 0.0000, 0.0000),(81, 0.0000, 0.0000, 0.0000),(82, 0.4900, 0.4900, 0.0000),(83, 0.6900, 0.6900, 0.0000),(84, 0.0000, 0.0000, 0.0000),(85, 0.0000, 0.0000, 0.0000),(86, 1.4900, 1.4900, 0.0000),(87, 0.9900, 0.9900, 0.0000),(88, 1.4900, 1.4900, 0.0000),(89, 0.0000, 0.0000, 0.0000),(90, 0.0000, 0.0000, 0.0000),(91, 0.0000, 0.0000, 0.0000),(92, 0.0000, 0.0000, 0.0000),(93, 0.0000, 0.0000, 0.0000),(94, 0.0000, 0.0000, 0.0000),(95, 0.4900, 0.4900, 0.0000),(96, 1.4900, 1.4900, 0.0000),(97, 0.0000, 0.0000, 0.0000),(98, 1.0000, 1.0000, 0.0000),(99, 0.0000, 0.0000, 0.0000),(100, 0.0000, 0.0000, 0.0000); INSERT INTO MerchandiseHierarchyGroup (ID_MRHRC_GP,ID_MRHC_PRNT,NM_MRHRC_GP,PE_PROFIT,ID_GP_TX,FOOD_STAMP_EX) VALUES (316, 315, 'VERDULERIA', 0.0000, 1, 'S'), (319, 318, 'CARNICERIA', 0.0000, 1, 'S'), (328, 327, 'BAZAR', 0.0000, 2, 'N'); INSERT INTO POSIdentity (ID_ITM_PS,ID_ITM_PS_QFR,ID_ITM_SL_PRC,ID_ITM,Qu_ITM,ACTIVO) VALUES ('CACAHCAS25LB', 1, 100, 100, 1, 'S'),('BUTTERNSQ', 1, 99, 99, 1, 'S'),('SCALLBULB', 1, 98, 98, 1, 'S'),('BRUSSELSPR', 1, 97, 97, 1, 'S'),('BROCOBUNCH', 1, 96, 96, 1, 'S'),('LETTUCEBOS', 1, 95, 95, 1, 'S'),('BOKCHOY', 1, 94, 94, 1, 'S'),('BLUEBERRY', 1, 93, 93, 1, 'S'),('BLACKBERR', 1, 92, 92, 1, 'S'),('BETABELSUELT', 1, 91, 91, 1, 'S'),('BETABELMANO', 1, 90, 90, 1, 'S'),('BETABELTX', 1, 89, 89, 1, 'S'),('BERROS', 1, 88, 88, 1, 'S'),('BERENNEGRA', 1, 87, 87, 1, 'S'),('BERENDOMINIC', 1, 86, 86, 1, 'S'),('BEANSPROUTS', 1, 85, 85, 1, 'S'),('BATAORJUM50LB', 1, 84, 84, 1, 'S'),('BATABONIF40LB', 1, 83, 83, 1, 'S'),('BANATURBA', 1, 82, 82, 1, 'S'),('BANASELVA', 1, 81, 81, 1, 'S'),('BANAMAN20LB', 1, 80, 80, 1, 'S'),('BANADOLE', 1, 79, 79, 1, 'S'),('BANABABY', 1, 78, 78, 1, 'S'),('BANADELMONTE', 1, 77, 77, 1, 'S'),('BANAAMARIL', 1, 76, 76, 1, 'S'),('BANABONITA', 1, 75, 75, 1, 'S'),('BABYSPINACH', 1, 74, 74, 1, 'S'),('BABYBELLA', 1, 73, 73, 1, 'S'),('BANAMAN15LB', 1, 72, 72, 1, 'S'),('ARUGULA', 1, 71, 71, 1, 'S'),('ALCACHOF', 1, 70, 70, 1, 'S'),('APRICOT', 1, 69, 69, 1, 'S'),('APIOBOLSA', 1, 68, 68, 1, 'S'),('APIORAIZ', 1, 67, 67, 1, 'S'),('ALFANFA', 1, 66, 66, 1, 'S'),('ALBACASUELT', 1, 65, 65, 1, 'S'),('AJOPEL20.1LB', 1, 64, 64, 1, 'S'),('AGUACFLOR9CT', 1, 63, 63, 1, 'S'),('AGUACFLOR', 1, 62, 62, 1, 'S'),('PERSIMMON', 1, 61, 61, 1, 'S'),('PALOMADELO', 1, 60, 60, 1, 'S'),('PALOENCLB', 1, 59, 59, 1, 'S'),('JUEGOMESA', 1, 58, 58, 1, 'S'),('FAJAPUDIN', 1, 57, 57, 1, 'S'),('EXPRLIMON', 1, 56, 56, 1, 'S'),('COMALRED', 1, 55, 55, 1, 'S'),('COMALLARGO', 1, 54, 54, 1, 'S'),('CAZOCOBRE1', 1, 53, 53, 1, 'S'),('PISTACHLB', 1, 52, 52, 1, 'S'),('PINOLELB', 1, 51, 51, 1, 'S'),('MUSTAGREEN', 1, 50, 50, 1, 'S'),('MOLEPOB', 1, 49, 49, 1, 'S'),('MOLCAJETEPZ', 1, 48, 48, 1, 'S'),('MUITLEPTS', 1, 47, 47, 1, 'S'),('MUITLELB', 1, 46, 46, 1, 'S'),('CHORMILJAL', 1, 45, 45, 1, 'S'),('MANGOSLLB', 1, 44, 44, 1, 'S'),('ESTRREDON', 1, 43, 43, 1, 'S'),('ESTRLARGO', 1, 42, 42, 1, 'S'),('HABABOTLB', 1, 41, 41, 1, 'S'),('LEMONGRASS', 1, 40, 40, 1, 'S'),('LEMON', 1, 39, 39, 1, 'S'),('FRIJOLQUELB', 1, 38, 38, 1, 'S'),('GENGIBLB', 1, 37, 37, 1, 'S'),('GARBANZOLB', 1, 36, 36, 1, 'S'),('FLETE', 1, 35, 35, 1, 'S'),('ESPEEMCA', 1, 34, 34, 1, 'S'),('ESPEEMP', 1, 33, 33, 1, 'S'),('ESENNILIM', 1, 32, 32, 1, 'S'),('EPAZSEC', 1, 31, 31, 1, 'S'),('PELOELOTELB', 1, 30, 30, 1, 'S'),('DORADILB', 1, 29, 29, 1, 'S'),('COCORAYALB', 1, 28, 28, 1, 'S'),('COBERTOR', 1, 27, 27, 1, 'S'),('CILANTFLORZ', 1, 26, 26, 1, 'S'),('CHURRPLA', 1, 25, 25, 1, 'S'),('CHILEMOLIM', 1, 24, 24, 1, 'S'),('CHICHATOR', 1, 23, 23, 1, 'S'),('CHICHARUE', 1, 22, 22, 1, 'S'),('CHICHAMINI', 1, 21, 21, 1, 'S'),('CHICHALAG', 1, 20, 20, 1, 'S'),('CHICHACUA4X8', 1, 19, 19, 1, 'S'),('CHICHACUA4X4', 1, 18, 18, 1, 'S'),('CACAHJAPLB', 1, 17, 17, 1, 'S'),('CACAHUENCHLB', 1, 16, 16, 1, 'S'),('AGUACA40/2', 1, 15, 15, 1, 'S'),('TLALESMRLB', 1, 14, 14, 1, 'S'),('ENCHIMRGR', 1, 13, 13, 1, 'S'),('CHORMRGR', 1, 12, 12, 1, 'S'),('CHICHAMRGG', 1, 11, 11, 1, 'S'),('CHICHAMIRLB', 1, 10, 10, 1, 'S'),('CECIMIRANLB', 1, 9, 9, 1, 'S'),('CHORMEXLON', 1, 8, 8, 1, 'S'),('CHORMEX3LB', 1, 7, 7, 1, 'S'),('CHORMEX14', 1, 6, 6, 1, 'S'),('QUESMILANP', 1, 5, 5, 1, 'S'),('CHORPOPU', 1, 4, 4, 1, 'S'),('BISTECKRES', 1, 1, 1, 1, 'S'),('CHORCHICA', 1, 2, 2, 1, 'S'),('CHORCHICP', 1, 3, 3, 1, 'S'); INSERT INTO RetailStore (ID_STR_RT,ID_PRTY,TY_RO_PRTY,ID_STRGRP,NM_STR_RT,ENC_PRN1,ENC_PRN2,PIE_PRN1,PIE_PRN2,ID_MERCHANT_ED,POSITION1,POSITION2,POSITION3,POSITION4,POSITION5,POSITION6,permite_venta_rojo) VALUES ( '1', '81', '''SUCURS''', '1', 'demo', 'tienda demo', 'encabezado', 'pie 1', 'vuelva  pronto', '1', '1', '2', '3', '4', '5', '6','S' ); INSERT INTO StockItem (ID_ITM,ID_SPR,NM_UOM,LU_CNT_SLS_WT_UN,CP_UN_SL_LS_RSV) VALUES (92, 11, 'lb', 'WT', 1.00000), (93, 11, 'lb', 'WT', 1.00000), (94, 11, 'lb', 'WT', 1.00000), (95, 11, 'lb', 'WT', 1.00000), (96, 11, 'lb', 'UN', 1.00000), (97, 11, 'lb', 'WT', 1.00000), (98, 11, 'lb', 'WT', 1.00000), (99, 11, 'lb', 'WT', 1.00000), (100, 11, 'lb', 'WT', 1.00000), (2, 11, 'lb', 'WT', 1.00000), (3, 11, 'lb', 'WT', 1.00000), (4, 11, 'lb', 'WT', 1.00000), (5, 11, 'lb', 'WT', 1.00000), (6, 11, 'lb', 'WT', 1.00000), (7, 11, 'lb', 'WT', 1.00000), (8, 11, 'lb', 'WT', 1.00000), (9, 11, 'lb', 'WT', 1.00000), (10, 11, 'lb', 'WT', 1.00000), (11, 11, 'lb', 'WT', 1.00000), (12, 11, 'lb', 'WT', 1.00000), (13, 11, 'lb', 'WT', 1.00000), (14, 11, 'lb', 'UN', 1.00000), (15, 11, 'lb', 'WT', 1.00000), (16, 11, 'lb', 'WT', 1.00000), (17, 11, 'lb', 'WT', 1.00000), (18, 11, 'lb', 'WT', 1.00000), (19, 11, 'lb', 'WT', 1.00000), (20, 11, 'lb', 'WT', 1.00000), (21, 11, 'lb', 'WT', 1.00000), (22, 11, 'lb', 'WT', 1.00000), (23, 11, 'lb', 'WT', 1.00000), (24, 11, 'lb', 'WT', 1.00000), (25, 11, 'lb', 'WT', 1.00000), (26, 11, 'lb', 'WT', 1.00000), (27, 11, 'lb', 'WT', 1.00000), (28, 11, 'lb', 'WT', 1.00000), (29, 11, 'lb', 'WT', 1.00000), (30, 11, 'lb', 'WT', 1.00000), (31, 11, 'lb', 'WT', 1.00000), (32, 11, 'lb', 'WT', 1.00000), (33, 11, 'lb', 'WT', 1.00000), (34, 11, 'lb', 'WT', 1.00000), (35, 11, 'lb', 'WT', 1.00000), (1, 11, 'lb', 'WT', 1.00000), (36, 11, 'lb', 'WT', 1.00000), (37, 11, 'lb', 'WT', 1.00000), (38, 11, 'lb', 'WT', 1.00000), (39, 11, 'lb', 'UN', 1.00000), (40, 11, 'lb', 'WT', 1.00000), (41, 11, 'lb', 'WT', 1.00000), (42, 11, 'lb', 'WT', 1.00000), (43, 11, 'lb', 'WT', 1.00000), (44, 11, 'lb', 'WT', 1.00000), (45, 11, 'lb', 'WT', 1.00000), (46, 11, 'lb', 'WT', 1.00000), (47, 11, 'lb', 'WT', 1.00000), (48, 11, 'lb', 'WT', 1.00000), (49, 11, 'lb', 'WT', 1.00000), (50, 11, 'lb', 'WT', 1.00000), (51, 11, 'lb', 'WT', 1.00000), (52, 11, 'lb', 'WT', 1.00000), (53, 11, 'lb', 'WT', 1.00000), (54, 11, 'lb', 'WT', 1.00000), (55, 11, 'lb', 'WT', 1.00000), (56, 11, 'lb', 'WT', 1.00000), (57, 11, 'lb', 'WT', 1.00000), (58, 11, 'lb', 'WT', 1.00000), (59, 11, 'lb', 'WT', 1.00000), (60, 11, 'lb', 'WT', 1.00000), (61, 11, 'lb', 'WT', 1.00000), (62, 11, 'lb', 'WT', 1.00000), (63, 11, 'lb', 'WT', 1.00000), (64, 11, 'lb', 'WT', 1.00000), (65, 11, 'lb', 'UN', 1.00000), (66, 11, 'lb', 'WT', 1.00000), (67, 11, 'lb', 'WT', 1.00000), (68, 11, 'lb', 'WT', 1.00000), (69, 11, 'lb', 'WT', 1.00000), (70, 11, 'lb', 'WT', 1.00000), (71, 11, 'lb', 'WT', 1.00000), (72, 11, 'lb', 'WT', 1.00000), (73, 11, 'lb', 'WT', 1.00000), (74, 11, 'lb', 'WT', 1.00000), (75, 11, 'lb', 'UN', 1.00000), (76, 11, 'lb', 'WT', 1.00000), (77, 11, 'lb', 'WT', 1.00000), (78, 11, 'lb', 'WT', 1.00000), (79, 11, 'lb', 'WT', 1.00000), (80, 11, 'lb', 'WT', 1.00000), (81, 11, 'lb', 'WT', 1.00000), (82, 11, 'lb', 'WT', 1.00000), (83, 11, 'lb', 'WT', 1.00000), (84, 11, 'lb', 'WT', 1.00000), (85, 11, 'lb', 'WT', 1.00000), (86, 11, 'lb', 'WT', 1.00000), (87, 11, 'lb', 'WT', 1.00000), (88, 11, 'lb', 'UN', 1.00000), (89, 11, 'lb', 'WT', 1.00000), (90, 11, 'lb', 'WT', 1.00000), (91, 11, 'lb', 'WT', 1.00000); INSERT INTO TaxGroupRule (ID_ATHY_TX,ID_GP_TX,AI_CMPND,NM_RU_TX,ID_ACNT_LDG) VALUES ( '1', '1', '0', 'MEXICO', '0' ); INSERT INTO TaxGroupRule (ID_ATHY_TX,ID_GP_TX,AI_CMPND,NM_RU_TX,ID_ACNT_LDG) VALUES ( '1', '2', '0', 'MEXICO2', '0' ); INSERT INTO TaxRateRule (ID_ATHY_TX,ID_GP_TX,AI_TX_RT_RU,TY_TX_RT_RU,MO_TXBM_MNM,MO_TXBL_MXM,MO_RT_TX,PE_RT_TX) VALUES ( '1', '1', '1', '''PE''', '0.0', '9999.0', '0', '0' ); INSERT INTO TaxRateRule (ID_ATHY_TX,ID_GP_TX,AI_TX_RT_RU,TY_TX_RT_RU,MO_TXBM_MNM,MO_TXBL_MXM,MO_RT_TX,PE_RT_TX) VALUES ( '1', '2', '1', '''PE''', '0.0', '9999.0', '0', '7' ); INSERT INTO TaxableGroup (ID_GP_TX,NM_GP_TX,CD_RCPT_PRN) VALUES ( '1', '0%', 'T0' ); INSERT INTO TaxableGroup (ID_GP_TX,NM_GP_TX,CD_RCPT_PRN) VALUES ( '2', '7%', 'T7' ); INSERT INTO Tender (TY_TND,ID_ACT_LDG,ID_CNY,DE_TND,FL_NMB_SRZ,FL_AZN_RQ,LU_MTH_AZN,FL_DT_AZN_EP_RQ,IN_WIT_AZN_MXM_ALOW,FL_IDTN_RQ_CT,FL_ID_PRSL_RQ,FL_AVLB_LCL_CNY,FL_SGNTR_CT_RQ,MO_TH_TND_CHN,FL_DRW_OPEN,MO_APVL_TNDCE_OFF,FL_ENDSM_RQ,PLAZOS,BTN_ASIGNED,FOOD_STAMP_EX) VALUES ('CCAR', 1, 1, 'CARD', 0, 0, '', '', 0, 1, 0, 0, 1, 0.000, 0, 50.0000, 0, '', 'CARD', 'N'),('CASH', 1, 1, 'CASH', 0, 0, '', '', 0, 0, 0, 1, 0, 500.000, 1, 0.0000, 0, '', 'CASH', 'N'),('CHEC', 0, 1, 'CHEC', 1, 0, NULL, 'N', 0, 0, 0, 0, 0, 500.000, 1, 500.0000, 1, 'N', 'CHEC', 'N'); INSERT INTO Till (ID_STR_RT,ID_RPSTY_TND,ID_WS,ID_OPR,CP_BLNC_DFLT_OPN,LU_TND_MXM_ALW) VALUES ( '1', '1', '1', '214', '500', '500' ); INSERT INTO WorkStation (ID_STR_RT,ID_WS,SERIE,QU_TL_WS,FL_MOD_TRG,FL_KEYBOARD,ID_BTNSET,ID_POS_ED) VALUES ( '1', '1', 'POSI', '0', '0', '0', '1', '0' ); INSERT INTO Till (ID_STR_RT,ID_RPSTY_TND,ID_WS,ID_OPR,CP_BLNC_DFLT_OPN,LU_TND_MXM_ALW) VALUES (1,1,1,100,500,500); insert into operator values (100,1,NULL,'chacon','chacon',NULL), (101,1,NULL, 'maria', 'maria',NULL), (102,1,NULL,'sandra','sandra',NULL),(103,1,NULL,'mariana','mariana',NULL); insert into operatorgroup(id_str_rt, id_gp_wrk, id_opr) values (1,10,100), (1,10,101), (1,11,102), (1,11,103); INSERT INTO GroupResourceAccess (ID_GP_WRK,ID_RS,PS_ACS_GP_RD,PS_ACS_GP_WR) VALUES (10,1001, 1, 1), (10,1010, 1, 1), (10,1020, 1, 1), (10,1030, 1, 1), (10,1031,1,1), (10,1032,1,1), (10,1033,1,1), (10,1034,1,1), (10,1035,1,1), (10,1036,1,1), (10,1037,1,1), (10,1038,1,1), (10,1039,1,1), (10,1040,1,1), (10,1042,1,1), (10,1043,1,1), (10,1044,1,1), (11,1001, 1, 1), (11,1010, 0, 0), (11,1020, 1, 1), (11,1030, 0, 0), (11,1031,0,0), (11,1032,0,0), (11,1033,0,0), (11,1034,1,1), (11,1035,0,0), (11,1036,0,0), (11,1037,0,0), (11,1038,1,1), (11,1039,0,0), (11,1040,1,1), (11,1042,1,1), (11,1043,1,1), (11,1044,0,0);";
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
    query.exec("SELECT * FROM operator  ");
    qDebug() << "SELECT * FROM HistCatalogos ORDER BY ai_ln";
    while (query.next()) {

        qDebug() << "id" << query.value("nm_opr").toString()<<query.value("id_opr").toString();
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

