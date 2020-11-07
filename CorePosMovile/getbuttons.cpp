#include "getbuttons.h"

#include <QDebug>
#include <QStack>

getbuttons::getbuttons()
{
    settings.setUp();
}

getbuttons::~getbuttons()
{

}

 QString getbuttons::traerBotones(){

    QString xml = "";
    QSqlDatabase sql = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sql);
    QString query ="SELECT * FROM buttonconfig order by NM_BTN;";
    bool continua;
    bool ok = sqlQuery.exec(query);
    if (!ok){
        qDebug() << "GetButtons.cpp Base de datos cerrada o con lios" << sql.lastError().text();
        return "";
    }
    qDebug() << "Getbuttons.cpp traerBotones()" << sqlQuery.isActive() << " " << sqlQuery.executedQuery() << "  " << sql.connectionNames() << " Válida " << sql.isValid() << " Abierta " << sql.isOpen();
    qDebug() << "Getbuttons.cpp traerBotones() tamaño " << sqlQuery.size();
    xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    continua = sqlQuery.first();
    if (continua)
    {
        qDebug() << "Getbuttons.cpp traerBotones() si encuentra 1" << xml;
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
        while( continua ){
            xml+="<buttonconfig>";
            xml+="<ID_STR_RT>"+sqlQuery.value("ID_STR_RT").toString()+"</ID_STR_RT>";
            xml+="<ID_BTNSET>"+sqlQuery.value("ID_BTNSET").toString()+"</ID_BTNSET>";
            xml+="<ID_BTN>"+sqlQuery.value("ID_BTN").toString()+"</ID_BTN>";
            xml+="<ID_BTN_PRNT>"+sqlQuery.value("ID_BTN_PRNT").toString()+"</ID_BTN_PRNT>";
            xml+="<TY_BTN>"+sqlQuery.value("TY_BTN").toString()+"</TY_BTN>";
            xml+="<BTN_WT>"+sqlQuery.value("BTN_WT").toString()+"</BTN_WT>";
            xml+="<NM_BTN>"+sqlQuery.value("NM_BTN").toString()+"</NM_BTN>";
            xml+="<DE_BTN>"+sqlQuery.value("DE_BTN").toString()+"</DE_BTN>";
            xml+="<PIC/>";
            //xml+="<ID_ITM>"+sqlQuery.value("ID_ITM").toString()+"</ID_ITM>";
            xml+="<ICON_ADDRESS/>";
            xml+="<ID_STRGRP>"+sqlQuery.value("ID_STRGRP").toString()+"</ID_STRGRP>";
            xml+="<ID_ITM_PS>"+sqlQuery.value("ID_ITM_PS").toString()+"</ID_ITM_PS>";
            xml+="<ID_ITM_PS_QFR>"+sqlQuery.value("ID_ITM_PS_QFR").toString()+"</ID_ITM_PS_QFR>";
            xml+="<POSITION>"+sqlQuery.value("POSITION").toString()+"</POSITION>";
            xml+="</buttonconfig>";
            continua = sqlQuery.next();
        }
    }
    else
    {
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>0</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    }
        //xml+="</return></ns2:GETButtonConfigWResponse></S:Body></S:Envelope>";
    xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
    qDebug()<<"getbuttons.cpp return de buttons " << xml;
    return xml;
}

 QString getbuttons::traerBotonesRoot(){

    QString xml = "";
    QSqlDatabase sql = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sql);
    QString query ="SELECT * FROM buttonconfig where TY_BTN='RO' order by NM_BTN ;";
    bool continua;
    bool ok = sqlQuery.exec(query);
    if (!ok){
        qDebug() << "GetButtons.cpp Base de datos cerrada o con lios" << sql.lastError().text();
        return "";
    }
    qDebug() << "Getbuttons.cpp traerBotones()" << sqlQuery.isActive() << " " << sqlQuery.executedQuery() << "  " << sql.connectionNames() << " Válida " << sql.isValid() << " Abierta " << sql.isOpen();
    qDebug() << "Getbuttons.cpp traerBotones() tamaño " << sqlQuery.size();
    xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    continua = sqlQuery.first();
    if (continua)
    {
        qDebug() << "Getbuttons.cpp traerBotones() si encuentra 1" << xml;
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
        while( continua ){
            xml+="<buttonconfig>";
            xml+="<ID_STR_RT>"+sqlQuery.value("ID_STR_RT").toString()+"</ID_STR_RT>";
            xml+="<ID_BTNSET>"+sqlQuery.value("ID_BTNSET").toString()+"</ID_BTNSET>";
            xml+="<ID_BTN>"+sqlQuery.value("ID_BTN").toString()+"</ID_BTN>";
            xml+="<ID_BTN_PRNT>"+sqlQuery.value("ID_BTN_PRNT").toString()+"</ID_BTN_PRNT>";
            xml+="<TY_BTN>"+sqlQuery.value("TY_BTN").toString()+"</TY_BTN>";
            xml+="<BTN_WT>"+sqlQuery.value("BTN_WT").toString()+"</BTN_WT>";
            xml+="<NM_BTN>"+sqlQuery.value("NM_BTN").toString()+"</NM_BTN>";
            xml+="<DE_BTN>"+sqlQuery.value("DE_BTN").toString()+"</DE_BTN>";
            xml+="<PIC/>";
            //xml+="<ID_ITM>"+sqlQuery.value("ID_ITM").toString()+"</ID_ITM>";
            xml+="<ICON_ADDRESS/>";
            xml+="<ID_STRGRP>"+sqlQuery.value("ID_STRGRP").toString()+"</ID_STRGRP>";
            xml+="<ID_ITM_PS>"+sqlQuery.value("ID_ITM_PS").toString()+"</ID_ITM_PS>";
            xml+="<ID_ITM_PS_QFR>"+sqlQuery.value("ID_ITM_PS_QFR").toString()+"</ID_ITM_PS_QFR>";
            xml+="<POSITION>"+sqlQuery.value("POSITION").toString()+"</POSITION>";
            xml+="</buttonconfig>";
            continua = sqlQuery.next();
        }
    }
    else
    {
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>0</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    }
        //xml+="</return></ns2:GETButtonConfigWResponse></S:Body></S:Envelope>";
    xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
    qDebug()<<"getbuttons.cpp return de buttons " << xml;
    return xml;
}

 QString getbuttons::traerBotonesA(QString id_prnt){

    QString xml = "";
    QSqlDatabase sql = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sql);
    QString query ="SELECT * FROM buttonconfig  where TY_BTN='AG'and ID_BTN_PRNT="+id_prnt+" order by NM_BTN;";
    bool continua;
    bool ok = sqlQuery.exec(query);
    if (!ok){
        qDebug() << "GetButtons.cpp Base de datos cerrada o con lios" << sql.lastError().text();
        return "";
    }
    qDebug() << "Getbuttons.cpp traerBotones()" << sqlQuery.isActive() << " " << sqlQuery.executedQuery() << "  " << sql.connectionNames() << " Válida " << sql.isValid() << " Abierta " << sql.isOpen();
    qDebug() << "Getbuttons.cpp traerBotones() tamaño " << sqlQuery.size();
    xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    continua = sqlQuery.first();
    if (continua)
    {
        qDebug() << "Getbuttons.cpp traerBotones() si encuentra 1" << xml;
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
        while( continua ){
            xml+="<buttonconfig>";
            xml+="<ID_STR_RT>"+sqlQuery.value("ID_STR_RT").toString()+"</ID_STR_RT>";
            xml+="<ID_BTNSET>"+sqlQuery.value("ID_BTNSET").toString()+"</ID_BTNSET>";
            xml+="<ID_BTN>"+sqlQuery.value("ID_BTN").toString()+"</ID_BTN>";
            xml+="<ID_BTN_PRNT>"+sqlQuery.value("ID_BTN_PRNT").toString()+"</ID_BTN_PRNT>";
            xml+="<TY_BTN>"+sqlQuery.value("TY_BTN").toString()+"</TY_BTN>";
            xml+="<BTN_WT>"+sqlQuery.value("BTN_WT").toString()+"</BTN_WT>";
            xml+="<NM_BTN>"+sqlQuery.value("NM_BTN").toString()+"</NM_BTN>";
            xml+="<DE_BTN>"+sqlQuery.value("DE_BTN").toString()+"</DE_BTN>";
            xml+="<PIC/>";
            //xml+="<ID_ITM>"+sqlQuery.value("ID_ITM").toString()+"</ID_ITM>";
            xml+="<ICON_ADDRESS/>";
            xml+="<ID_STRGRP>"+sqlQuery.value("ID_STRGRP").toString()+"</ID_STRGRP>";
            xml+="<ID_ITM_PS>"+sqlQuery.value("ID_ITM_PS").toString()+"</ID_ITM_PS>";
            xml+="<ID_ITM_PS_QFR>"+sqlQuery.value("ID_ITM_PS_QFR").toString()+"</ID_ITM_PS_QFR>";
            xml+="<POSITION>"+sqlQuery.value("POSITION").toString()+"</POSITION>";
            xml+="</buttonconfig>";
            continua = sqlQuery.next();
        }
    }
    else
    {
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>0</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    }
        //xml+="</return></ns2:GETButtonConfigWResponse></S:Body></S:Envelope>";
    xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
    qDebug()<<"getbuttons.cpp return de buttons " << xml;
    return xml;
}

 QString getbuttons::traerBotonesB(QString id_prnt){

    QString xml = "";
    QSqlDatabase sql = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sql);
    QString query ="SELECT * FROM buttonconfig where TY_BTN='PR' and ID_BTN_PRNT="+id_prnt+" order by NM_BTN ;";
    bool continua;
    bool ok = sqlQuery.exec(query);
    if (!ok){
        qDebug() << "GetButtons.cpp Base de datos cerrada o con lios" << sql.lastError().text();
        return "";
    }
    qDebug() << "Getbuttons.cpp traerBotones()" << sqlQuery.isActive() << " " << sqlQuery.executedQuery() << "  " << sql.connectionNames() << " Válida " << sql.isValid() << " Abierta " << sql.isOpen();
    qDebug() << "Getbuttons.cpp traerBotones() tamaño " << sqlQuery.size();
    xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    continua = sqlQuery.first();
    if (continua)
    {
        qDebug() << "Getbuttons.cpp traerBotones() si encuentra 1" << xml;
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
        while( continua ){
            xml+="<buttonconfig>";
            xml+="<ID_STR_RT>"+sqlQuery.value("ID_STR_RT").toString()+"</ID_STR_RT>";
            xml+="<ID_BTNSET>"+sqlQuery.value("ID_BTNSET").toString()+"</ID_BTNSET>";
            xml+="<ID_BTN>"+sqlQuery.value("ID_BTN").toString()+"</ID_BTN>";
            xml+="<ID_BTN_PRNT>"+sqlQuery.value("ID_BTN_PRNT").toString()+"</ID_BTN_PRNT>";
            xml+="<TY_BTN>"+sqlQuery.value("TY_BTN").toString()+"</TY_BTN>";
            xml+="<BTN_WT>"+sqlQuery.value("BTN_WT").toString()+"</BTN_WT>";
            xml+="<NM_BTN>"+sqlQuery.value("NM_BTN").toString()+"</NM_BTN>";
            xml+="<DE_BTN>"+sqlQuery.value("DE_BTN").toString()+"</DE_BTN>";
            xml+="<PIC/>";
            //xml+="<ID_ITM>"+sqlQuery.value("ID_ITM").toString()+"</ID_ITM>";
            xml+="<ICON_ADDRESS/>";
            xml+="<ID_STRGRP>"+sqlQuery.value("ID_STRGRP").toString()+"</ID_STRGRP>";
            xml+="<ID_ITM_PS>"+sqlQuery.value("ID_ITM_PS").toString()+"</ID_ITM_PS>";
            xml+="<ID_ITM_PS_QFR>"+sqlQuery.value("ID_ITM_PS_QFR").toString()+"</ID_ITM_PS_QFR>";
            xml+="<POSITION>"+sqlQuery.value("POSITION").toString()+"</POSITION>";
            xml+="</buttonconfig>";
            continua = sqlQuery.next();
        }
    }
    else
    {
        xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>0</resultado><resultadoMsg>ok</resultadoMsg></resultado>";
    }
        //xml+="</return></ns2:GETButtonConfigWResponse></S:Body></S:Envelope>";
    xml+="</return></GETButtonConfigWResponse></Body></Envelope>";
    qDebug()<<"getbuttons.cpp return de buttons " << xml;
    return xml;
}

 QString getbuttons::traerPadreDePadre(QString id_prnt){
     QString xml = "";
     QSqlDatabase sql = QSqlDatabase::database("Origen");
     QSqlQuery sqlQuery(sql);
     QString query ="select id_btn_prnt from buttonconfig where id_btn="+id_prnt+" order by NM_BTN ;";
     bool continua;
     bool ok = sqlQuery.exec(query);
     if (!ok){
         qDebug() << "GetButtons.cpp Base de datos cerrada o con lios" << sql.lastError().text();
         return "";
     }
    continua = sqlQuery.first();
     if (continua)
     {
         while( continua ){
             xml+=sqlQuery.value("ID_BTN_PRNT").toString();
             continua = sqlQuery.next();
         }
     }
     qDebug()<<"getbuttons.cpp return padre del padre " << xml;
     return xml;
 }
QList<QVariant> getbuttons::agregarBotones(QString value){

    QList<QVariant> regreso;
    QSqlDatabase sql = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sql);
    QString query = "SELECT * FROM buttonconfig where id_btn_prnt = "+value+" order by nm_btn";

    qDebug() << "getButtons.cpp: agregarbotones"<< query;


    bool ok = sqlQuery.exec( query ) ;
    if ( ok == false )
    {
        qDebug() << "GetButtons.cpp " << query ;
        qDebug() << "GetButtons.cpp Error en bd " << sqlQuery.lastError() ;
        QMap<QString,QVariant> objeto;
        objeto["mensaje"] = "false";
        return regreso;
    }
    while( sqlQuery.next()  ){
        QMap<QString,QVariant> objeto;
        objeto["ID_STR_RT"] = sqlQuery.value("ID_STR_RT").toString();
        objeto["ID_BTNSET"] = sqlQuery.value("ID_BTNSET").toString();
        objeto["ID_BTN"] = sqlQuery.value("ID_BTN").toString();
        objeto["ID_BTN_PRNT"] = sqlQuery.value("ID_BTN_PRNT").toString();
        objeto["TY_BTN"] = sqlQuery.value("TY_BTN").toString();
        objeto["BTN_WT"] = sqlQuery.value("BTN_WT").toString();
        objeto["NM_BTN"] = sqlQuery.value("NM_BTN").toString();
        objeto["DE_BTN"] = sqlQuery.value("DE_BTN").toString();
        objeto["PIC"] = "";
        //objeto["ID_ITM"] = sqlQuery.value("ID_ITM").toString();
        objeto["ICON_ADDRESS"] = "";
        objeto["ID_STRGRP"] = sqlQuery.value("ID_STRGRP").toString();
        objeto["ID_ITM_PS"] = sqlQuery.value("ID_ITM_PS").toString();
        objeto["ID_ITM_PS_QFR"] = sqlQuery.value("ID_ITM_PS_QFR").toString();
        objeto["POSITION"] = sqlQuery.value("POSITION").toString();
        regreso.append(objeto);
    }
    return regreso;
}
