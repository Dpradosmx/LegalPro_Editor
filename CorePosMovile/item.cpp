#include "item.h"
#include "utilerias.h"
#include <QDebug>
#include <QSqlError>



Item::Item()
{
}

void Item::set_item(QString ID_ITM, QString ID_ITM_PS_QFR)
{
    //asigna los valores necesarios al objeto

    QSqlDatabase sql;
    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    QString queryprecios ="select * from posidentity inner join item on posidentity.ID_ITM = item.ID_ITM where item.id_itm="+ID_ITM +" AND posidentity.ID_ITM_PS_QFR = "+ID_ITM_PS_QFR;
    qDebug() << "item::set_item " << queryprecios;

    if(!sqlQuery.exec( queryprecios )) return;
    sqlQuery.first();
    if(sqlQuery.isValid()){
         id_itm=sqlQuery.value("ID_ITM").toInt();
         id_itm_sl_prc=sqlQuery.value("ID_ITM_SL_PRC").toInt();
         id_mrhrc_gp=sqlQuery.value("ID_MRHRC_GP").toInt();
         id_brn=sqlQuery.value("ID_BRN").toInt();
         lu_exm_tx=sqlQuery.value("LU_EXM_TX").toString();
         nm_itm=sqlQuery.value("NM_ITM").toString();
         de_itm=sqlQuery.value("DE_ITM").toString();
         ty_itm=sqlQuery.value("TY_ITM").toString();
         ty_itm_sv =sqlQuery.value("TY_ITM_SV").toString();
         id_gp_tx=sqlQuery.value("ID_GP_TX").toInt();
         id_gp_tx_buy=sqlQuery.value("ID_GP_TX_BUY").toInt();
         id_itm_ps=sqlQuery.value("ID_ITM_PS").toString();
         qu_itm=sqlQuery.value("QU_ITM").toInt();
         id_itm_ps_qfr=ID_ITM_PS_QFR;
         food_stamp_ex=sqlQuery.value("FOOD_STAMP_EX").toString();
         qDebug() << nm_itm << " item sell prices = " << id_itm_sl_prc;
         getprecios();

//         impuestos.set_tax(id_gp_tx,cantidad);
//         total_tax = impuestos.get_tax(id_gp_tx,get_precio_indice(0).toDouble(),sql);//aqui hay una excepcio si es en estados unidos
    }
}


QVariant Item::get_item(){
QMap<QString,QVariant> datositem;

datositem["id_itm"] = id_itm;
datositem["id_itm_sl_prc"] = id_itm_sl_prc;
datositem["id_mrhrc_gp"] = id_mrhrc_gp; //???
datositem["id_brn"] = id_brn;//???
datositem["lu_exm_tx"] = lu_exm_tx;//excepcion de impuestos
datositem["nm_itm"] = nm_itm;
datositem["de_itm"] = de_itm;
datositem["ty_itm"] = ty_itm;
datositem["id_gp_tx"] = id_gp_tx;
datositem["id_gp_tx_buy"] = id_gp_tx_buy;
datositem["id_itm_ps"] =id_itm_ps;
datositem["id_itm_ps_qfr"]=id_itm_ps_qfr;
datositem["food_stamp_ex"] = food_stamp_ex;
datositem["precio"] = precio;
datositem["precio_volumen"] = precio_volumen;
datositem["qu_itm"] = qu_itm;
datositem["itempictures"]=itempictures;
//datositem["total_tax"] = total_tax;

return datositem;
}

void Item::getpicture(){
    QSqlDatabase sql;
    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    QString queryprecios ="select * from ItemPictures where ID_ITM="+QString::number(id_itm);
    qDebug() << "item.cpp getpictures() query?" << queryprecios;
    bool ok = sqlQuery.exec( queryprecios ) ;

    if(ok){
        while( sqlQuery.next()){
            itempictures+=sqlQuery.value("url").toString()+",";
        }
    }
}

void Item::getprecios(){

    QList<QVariant> itemsellprice;
    QList<QVariant> itemvolumeprice;

    QSqlDatabase sql;
    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    QString queryprecios ="select SELL_PRICE, PRICE_LIST, OFER_PRICE from itemsellprice where itemsellprice.ID_ITM_SL_PRC="+QString::number(id_itm_sl_prc);
    qDebug() << "item.cpp getprecios() query?" << queryprecios;
    bool ok = sqlQuery.exec( queryprecios ) ;
    if(ok){
        if( sqlQuery.first()){
            sell_price = sqlQuery.value("SELL_PRICE").toDouble()+1;
            price_list =sqlQuery.value("PRICE_LIST").toDouble();
            offer_price = sqlQuery.value("OFER_PRICE").toDouble();
            precio= sell_price;
        }
    }
    qDebug() << "item.cpp get_precios(): " << QString::number(sell_price) << " " << QString::number(price_list) << " ";
    qDebug() << "item::get precios() tamaño de los item sell prices " << itemsellprice.length();
    //valor sera necesario hacerle un itemsellprice.tolist;

    queryprecios ="select * from itemvolumeprice where ID_ITM_SL_PRC =" + QString::number(id_itm_sl_prc) + " order by AL_LN_PRC";

    qDebug() << "item.cpp  item::get precios::" << queryprecios;

    ok = sqlQuery.exec( queryprecios ) ;

    if(ok){
    while( sqlQuery.next()  ){

        QMap<QString,QVariant> temp;
        temp["id_itm_sl_prc"]=sqlQuery.value("ID_ITM_SL_PRC");
        temp["al_ln_prc"]=sqlQuery.value("AL_LN_PRC");
        temp["price"]=sqlQuery.value("PRICE");
        temp["min_qty"]=sqlQuery.value("MIN_QTY");
        temp["max_qty"]=sqlQuery.value("MAX_QTY");
        itemvolumeprice.append(temp);
    }
  }
    qDebug() << "item.cpp item::get precios:: tamaño de los item volumen price " << itemsellprice.length();
    precio_volumen = itemvolumeprice;//valor sera necesario hacerle un itemsellprice.tolist;
}

int Item::search_items(QString item, QString ps_qfr){

    QList<QVariant> items;
    QSqlDatabase sql;
    int cuantos = 0;
    QMap<QString,QVariant> temp;

    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    QString query ="select p.id_ITM_PS, p.ID_ITM_PS_QFR, P.ID_ITM_SL_PRC, I.id_ITM, I.ID_MRHRC_GP, I.ID_BRN, ";
    query+="I.LU_EXM_TX, I.NM_ITM, I.DE_ITM, I.TY_ITM, I.ID_GP_TX, I.ID_GP_tx_buy, I.fOOD_STAMP_EX, ST.LU_CNT_SLS_WT_UN, P.QU_ITM ";
    query+="from posidentity p inner join item i on i.id_itm = p.id_itm left outer join stockitem st on st.id_itm = i.id_itm where id_itm_ps = '"+item+"'";
    query+=" and id_itm_ps_qfr='"+ps_qfr+"'";
    qDebug() << "item.cpp search_items " << query;
    if(sqlQuery.exec( query )){
        while( sqlQuery.next()  ){
            cuantos++;
            id_itm=sqlQuery.value("ID_ITM").toInt();
            id_itm_sl_prc=sqlQuery.value("ID_ITM_SL_PRC").toInt();
            id_mrhrc_gp=sqlQuery.value("ID_MRHRC_GP").toInt();
            id_brn=sqlQuery.value("ID_BRN").toInt();
            lu_exm_tx=sqlQuery.value("LU_EXM_TX").toString();
            nm_itm=sqlQuery.value("NM_ITM").toString();
            de_itm=sqlQuery.value("DE_ITM").toString();
            ty_itm=sqlQuery.value("TY_ITM").toString();
            id_gp_tx=sqlQuery.value("ID_GP_TX").toInt();
            id_gp_tx_buy=sqlQuery.value("ID_GP_TX_BUY").toInt();
            id_itm_ps=sqlQuery.value("ID_ITM_PS").toString();
            id_itm_ps_qfr=sqlQuery.value("ID_ITM_PS_QFR").toString();
            food_stamp_ex=sqlQuery.value("FOOD_STAMP_EX").toString();
            lu_cnt_sls_wt_un=sqlQuery.value("LU_CNT_SLS_WT_UN").toString();
            qu_itm=sqlQuery.value("QU_ITM").toInt();
            qDebug() << "item.cpp set_item: " << nm_itm << " item sell prices = " << id_itm_sl_prc;
            getprecios();
            getpicture();
//            impuestos.set_tax(id_gp_tx,cantidad);
//            total_tax = impuestos.get_tax(id_gp_tx,get_precio_indice(0).toDouble(),sql);//aqui hay una excepcion si es en estados unidos
        }
    }
    return cuantos;
}


int Item::itemsearchPrepare(QVariant value){

    QString xml="";
    QString query="";
    int Contador=0;
    QString sContador;
    QString sNumber="";
    QSqlDatabase sqldatabasecortex;
    Utilerias u;

    posidentity="";
    qfr="";
    QSqlQuery sqlQuery( sqldatabasecortex.database("Origen") )  ;                                                                                                                                                                                       //esto fue agregado para obtener una imagen de muestra
    query="select p.id_itm,id_itm_ps,id_itm_ps_qfr,nm_itm,sell_price,qu_itm, pics.URL as url from item it left outer join posidentity p on p.id_itm = it.id_itm left outer join itemsellprice i on p.id_itm_sl_prc = i.id_itm_sl_prc left join (select id_itm,url from ItemPictures GROUP by id_itm) as pics on pics.id_itm=it.ID_ITM where lower(id_itm_ps) = lower('" + value.toString() + "');";
    qDebug() << "item.cpp::itemsearchprepare() query: "<<query;
    if(value.toString()> "")
    {
        if (sqlQuery.exec( query ))
        {
            while(sqlQuery.next()){
                Contador++;
                sNumber = u.FormatoNumero(sqlQuery.value("sell_price").toString(),7,4);
                if(Contador == 1)
                {
                    posidentity=sqlQuery.value("id_itm_ps").toString();
                    qfr = sqlQuery.value("id_itm_ps_qfr").toString();
                    qDebug() << "item.cpp::itemsearchprepare() posidentity"<< posidentity << " qufr "<<qfr;
                }
                xml+="<ItemList><ID_ITM_PS>"+sqlQuery.value("id_itm_ps").toString()+"</ID_ITM_PS><ID_ITM_PS_QFR>"+sqlQuery.value("id_itm_ps_qfr").toString()+"</ID_ITM_PS_QFR><NM_ITM>"+sqlQuery.value("nm_itm").toString()+"</NM_ITM><PRICE>"+sNumber+"</PRICE><QTY_ITM>"+sqlQuery.value("qu_itm").toString()+"</QTY_ITM><PIC>"+sqlQuery.value("url").toString()+"</PIC></ItemList>";
            }
            xml="<ItemSearch><Oper>ItemSearch</Oper><resultado>1</resultado><resultadoMsg>Exito</resultadoMsg>"+xml+"</ItemSearch>";
        }
        else
            qDebug() << "item.cpp::itemsearchprepare() error en el query 1";
    }
    if(Contador == 0)
    {
        xml="";
        query="select  p.id_itm,id_itm_ps,id_itm_ps_qfr,nm_itm,sell_price,qu_itm,pics.url as url from item it left outer join posidentity p on p.id_itm = it.id_itm left outer join itemsellprice i on p.id_itm_sl_prc = i.id_itm_sl_prc left join (select id_itm,url from ItemPictures GROUP by id_itm) as pics on pics.id_itm=it.ID_ITM where UPPER(nm_itm) like UPPER('%" + value.toString() + "%') or UPPER(de_itm) like UPPER('%" + value.toString() + "%') or UPPER(id_itm_ps) like UPPER('%" + value.toString() + "%') ORDER BY nm_itm LIMIT 25;";
        qDebug() << "item.qpp query "<<query;
        if (sqlQuery.exec( query ))
        {
            while(sqlQuery.next()){
                Contador++;
                sNumber = u.FormatoNumero(sqlQuery.value("sell_price").toString(),7,4);
                xml+="<ItemList><ID_ITM_PS>"+sqlQuery.value("id_itm_ps").toString()+"</ID_ITM_PS><ID_ITM_PS_QFR>"+sqlQuery.value("id_itm_ps_qfr").toString()+"</ID_ITM_PS_QFR><NM_ITM>"+sqlQuery.value("nm_itm").toString()+"</NM_ITM><PRICE>"+sNumber+"</PRICE><QTY_ITM>"+sqlQuery.value("qu_itm").toString()+"</QTY_ITM><PIC>"+sqlQuery.value("url").toString()+"</PIC></ItemList>";
                if(Contador == 1)
                {
                posidentity=sqlQuery.value("id_itm_ps").toString();
                qfr = sqlQuery.value("id_itm_ps_qfr").toString();
                qDebug() << "item.cpp::itemsearchprepare() posidentity"<< posidentity << " qufr "<<qfr;
                }
            }
            xml="<ItemSearch><Oper>ItemSearch</Oper><resultado>1</resultado><resultadoMsg>Exito</resultadoMsg>"+xml+"</ItemSearch>";
        }
        else
            qDebug() << "item.cpp::itemsearchprepare() error en el query 1";
    }
    if(Contador == 0)
    {
        xml = "";
    }
    xmlResultado = xml;
    return Contador;
}

QString Item::itemsearch(){
    return xmlResultado;
}

QString Item::itemsearch_getPosidentity(){
    return posidentity;
}

QString Item::itemsearch_getQfr()
{
    return qfr;
}





