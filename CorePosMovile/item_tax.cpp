#include "item_tax.h"

Item_tax::Item_tax()
{
    settings = new Settings();
    settings->setUp();
    DesglosaImp = (settings->getDesglosaImpuestos() == "TRUE");
    qDebug() << "Item_tax::Item_tax() " << settings->getDesglosaImpuestos();
    if (DesglosaImp){
        qDebug() << "Item_tax::Item_tax() Desglosa";
    }
    DesglosaImp = true;
}

void Item_tax::set_tax(QString id_gp_tx1, double cantidad){
    //2020 aqui se hace el cálculo del impuesto
    QSqlDatabase sql;
    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    QString query="select * from taxraterule inner join taxgrouprule on taxraterule.ID_GP_TX=taxgrouprule.ID_GP_TX inner join taxablegroup on taxablegroup.ID_GP_TX=taxraterule.ID_GP_TX where taxraterule.ID_GP_TX="+id_gp_tx1;
    if (settings->getDesglosaImpuestos()=="TRUE")
    {
        query += " order by ai_tx_rt_ru desc";
    }
    else
    {
        query+=" order by ai_tx_rt_ru";
    }
    qDebug() << "item_tax: set_tax " << query;
    id_gp_tx=id_gp_tx1;
    QMap<QString,QVariant> temp;
    bool ok = sqlQuery.exec( query ) ;
    if(ok){
        while( sqlQuery.next()  ){
             id_athy_tx=sqlQuery.value("ID_ATHY_TX").toString();
             ai_cmpnd=sqlQuery.value("AI_CMPND").toString();
             temp["id_athy_tx"]=id_athy_tx;
             temp["ai_cmpnd"]=ai_cmpnd;
             temp["nm_gp_tx"]=sqlQuery.value("NM_GP_TX");
             temp["ai_tx_rt_ru"]=sqlQuery.value("AI_TX_RT_RU");
             temp["ty_tx_rt_ru"]=sqlQuery.value("TY_TX_RT_RU");
             temp["mo_txbm_mnm"]=sqlQuery.value("MO_TXBM_MNM");
             temp["mo_txbl_mxm"]=sqlQuery.value("MO_TXBL_MXM");
             temp["mo_rt_tx"]=sqlQuery.value("MO_RT_TX");
             temp["pe_rt_tx"]=sqlQuery.value("PE_RT_TX");
             temp["cd_rcpt_prn"]=sqlQuery.value("CD_RCPT_PRN");
             impuestos.append(temp);
        }
    }
    qDebug() << "item_tax.cpp tamaño de impuestos: "<<impuestos.length();
    if(impuestos.length()>0) {qDebug() << "item_tax.cpp par de datos" <<impuestos.at(0).value("ty_tx_rt_ru")<< " y " << impuestos.at(0).value("ai_tx_rt_ru");} ;
}

double Item_tax::get_tax(QString id_gp_tx, double monto, QSqlDatabase sql){
    //2020
    double total = 0;
    double impuesto;
    double montonvo;
    QString query;
    QSqlQuery sqlQuery( sql.database( "Origen") )  ;
    if (true)
    {
        query="SELECT * FROM taxraterule where id_gp_tx = "+id_gp_tx+ " order by ai_tx_rt_ru desc";
    }
    else
    {
        query="SELECT * FROM taxraterule where id_gp_tx = "+id_gp_tx + " order by ai_tx_rt_ru";
    }
    qDebug() << "Item_tax::get_tax: " << query << "monto" << monto;

    bool ok = sqlQuery.exec( query ) ;
    qDebug() << "Item_tax::get_tax: " << query << "monto 1" << monto;
    if(ok){
        qDebug() << "Item_tax::get_tax: " << query << "monto 2" << monto;
        while( sqlQuery.next()  ){
            if(sqlQuery.isValid()){
                if (true) //
                {
                    qDebug() << "Item_tax::get_tax: desglosa " << query << "Tipo 2.5" << sqlQuery.value("TY_TX_RT_RU").toString();
                    if(sqlQuery.value("TY_TX_RT_RU").toString() == "PE"){
                        montonvo = monto / (1 + (sqlQuery.value("PE_RT_TX").toDouble() /100));
                        impuesto = monto - montonvo;
                        qDebug() << "gettax:: total tax es por porcentaje es " << impuesto << "del %" <<sqlQuery.value("PE_RT_TX").toString();
                    }
                    else{
                        impuesto = sqlQuery.value("MO_RT_TX").toDouble();
                        montonvo = monto - impuesto;
                        qDebug() << "gettax:: total tax es por fijo es " << total << "del " <<sqlQuery.value("MO_RT_TX").toString();
                    }
                    monto=montonvo;
                    total+=impuesto;
                }
                else
                {
                    qDebug() << "Item_tax::get_tax: añade " << query << "Tipo 2.5" << sqlQuery.value("TY_TX_RT_RU").toString();
                    if(sqlQuery.value("TY_TX_RT_RU").toString() == "PE"){
                        impuesto = monto * sqlQuery.value("PE_RT_TX").toDouble() /100;
                        qDebug() << "gettax:: total tax es por porcentaje es " << impuesto << "del %" <<sqlQuery.value("PE_RT_TX").toString();
                    }
                    else{
                        impuesto = sqlQuery.value("MO_RT_TX").toDouble();
                        qDebug() << "gettax:: total tax es por fijo es " << total << "del " <<sqlQuery.value("MO_RT_TX").toString();
                    }
                    monto+=impuesto;
                    total+=impuesto;
                }
            }

        }
        qDebug() << "Item_tax::get_tax: " << query << "monto 3" << monto;
    }
    qDebug() << "Item_tax::get_tax() &&##: " << query << "totales total" << total;
    return total;//total de dinero que se le sumara al total;
}
