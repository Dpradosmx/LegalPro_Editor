#include "rt_total_tax.h"
#include <qDebug>


RT_Total_Tax::RT_Total_Tax(bool wdesglosa)
//Carga la totalidad de la estructura de impuestos
{
    bool first=true;
    QSqlQuery sqlQuery( sql.database( "Origen") );
    RT_Total_Tax *nodo1;
    query="select * from taxablegroup";
    id_gp_tax = -1;
    nm_gp_tx = "";
    cd_rcpt_prn  = "";
    if (sqlQuery.exec( query )){
        while (sqlQuery.next()){
            if(first)
            {
                id_gp_tax = sqlQuery.value("ID_GP_TX").toInt();
                nm_gp_tx = sqlQuery.value("NM_GP_TX").toString();
                //qDebug() << "rt_total_tax::rt_total_tax "<< nm_gp_tx;
                cd_rcpt_prn  = sqlQuery.value("CD_RCPT_PRN").toString();
                next = NULL;
                reglas=NULL;
                impuesto = 0;
                RT_Total_Tax_Reglas();
                first=false;
                nodo1=this;
            }
            else
            {
                nodo1->next = new RT_Total_Tax(wdesglosa, sqlQuery.value("ID_GP_TX").toInt(), sqlQuery.value("NM_GP_TX").toString(), sqlQuery.value("CD_RCPT_PRN").toString());
                nodo1=nodo1->next;
            }
        }
    }

}

RT_Total_Tax::RT_Total_Tax(bool wdesglosa, int wid_gp_tx, QString wnm_gp_tx, QString wcd_rcpt_prn )
{
    //qDebug() << "rt_total_tax::rt_total_tax (Next) "<< wnm_gp_tx;
    desglosa_impuestos = wdesglosa;
    id_gp_tax = wid_gp_tx;
    nm_gp_tx = wnm_gp_tx;
    cd_rcpt_prn  = wcd_rcpt_prn;
    impuesto=0;
    next = NULL;
    reglas = NULL;
    RT_Total_Tax_Reglas();
}


RT_Total_Tax::RT_Total_Tax(RT_Total_Tax* nodo)
//copia la totalidad de la estructura de impuestos
{

    //qDebug() << "rt_total_tax::rt_total_tax 3 "<< QString::number(nodo->id_gp_tax) << " " << nodo->nm_gp_tx;
    desglosa_impuestos = nodo->desglosa_impuestos;
    id_gp_tax = nodo->id_gp_tax;
    nm_gp_tx = nodo->nm_gp_tx;
    cd_rcpt_prn  = nodo->cd_rcpt_prn;
    next = NULL;
    reglas = NULL;
    if(nodo->next != NULL)
    {
        next = new RT_Total_Tax(nodo->next);
    }
    if(nodo->reglas != NULL)
    {
        reglas = new RT_Total_individual_Tax(nodo->reglas);
    }
}

RT_Total_Tax::RT_Total_Tax(int wid_gpo_tx, RT_Total_Tax* nodo)
//copia solo un solo elemento de una lista
{
    RT_Total_Tax* nodo1;
    //qDebug() << "rt_total_tax::rt_total_tax 1"<< nodo->nm_gp_tx;
    nodo1=nodo->find(wid_gpo_tx);
    if(nodo1 != NULL)
    {
        desglosa_impuestos = nodo1->desglosa_impuestos;
        id_gp_tax = nodo1->id_gp_tax;
        nm_gp_tx = nodo1->nm_gp_tx;
        //qDebug() << "rt_total_tax::rt_total_tax 4"<< nm_gp_tx;
        cd_rcpt_prn  = nodo1->cd_rcpt_prn;
        next = NULL;
        reglas = NULL;
        if(nodo1->reglas != NULL)
        {
            reglas = new RT_Total_individual_Tax(nodo1->reglas);
        }
    }
    else
    {
        desglosa_impuestos = true;
        id_gp_tax = -1;
        nm_gp_tx = "";
        //qDebug() << "rt_total_tax::rt_total_tax 5"<< nm_gp_tx << QString::number(wid_gpo_tx);
        cd_rcpt_prn  = "";
        next = NULL;
        reglas = NULL;
    }
}

RT_Total_Tax* RT_Total_Tax::find(int wid_gp_tax)
{
    RT_Total_Tax* nodo;
    bool continua=true;

    nodo = this;
    while(continua)
    {
        //qDebug() << "RT_Total_Tax::find(): " << QString::number(nodo->id_gp_tax) << " " << nodo->nm_gp_tx << " " << QString::number(wid_gp_tax);
        if(nodo->id_gp_tax == wid_gp_tax)
        {
            continua=false;
        }
        else
        {
            nodo = nodo->next;
            if(nodo == NULL)
            {
                continua =false;
            }
        }
    }
    return nodo;
}

void RT_Total_Tax::RT_Total_Tax_Reglas()
{

    bool first;
    int wid_athy_tx, wai_tx_rt_ru;
    QString wty_tx_rt_ru;
    double wmo_txbm_mnm, wmo_txbl_mxm, wmo_rt_tx, wpe_rt_tx;
    RT_Total_individual_Tax* nodo1;
    query="select * from taxraterule  where ID_GP_TX="+QString::number(id_gp_tax);
    if (desglosa_impuestos)
    {
        query += " order by ai_tx_rt_ru desc";
    }
    else
    {
        query+=" order by ai_tx_rt_ru";
    }
    first=true;
    QSqlQuery sqlQuery(sql.database("Origen"));
    //qDebug() << "RT_Total_Tax::RT_Total_Tax_Reglas: " << query;
    if(sqlQuery.exec( query )){
        while( sqlQuery.next()  ){
            wid_athy_tx=sqlQuery.value("id_athy_tx").toInt();
            wai_tx_rt_ru=sqlQuery.value("AI_TX_RT_RU").toInt();
            wty_tx_rt_ru=sqlQuery.value("TY_TX_RT_RU").toString();
            wmo_txbm_mnm=sqlQuery.value("MO_TXBM_MNM").toDouble();
            wmo_txbl_mxm=sqlQuery.value("MO_TXBL_MXM").toDouble();
            wmo_rt_tx=sqlQuery.value("MO_RT_TX").toDouble();
            wpe_rt_tx=sqlQuery.value("PE_RT_TX").toDouble();
            if(reglas == NULL)
            {
                //qDebug() << "RT_Total_Tax::RT_Total_Tax_Reglas: 1";
                reglas = new RT_Total_individual_Tax(wid_athy_tx, id_gp_tax, wai_tx_rt_ru, wty_tx_rt_ru, wmo_txbm_mnm, wmo_txbl_mxm, wmo_rt_tx, wpe_rt_tx);
            }
            else
            {
                nodo1 = new RT_Total_individual_Tax(wid_athy_tx, id_gp_tax, wai_tx_rt_ru, wty_tx_rt_ru, wmo_txbm_mnm, wmo_txbl_mxm, wmo_rt_tx, wpe_rt_tx);
                //qDebug() << "RT_Total_Tax::RT_Total_Tax_Reglas: 2 ";
                reglas->append(nodo1);
            }
        }
    }
}

double RT_Total_Tax::calcula_impuesto(double base){
    impuesto = 0;
    //qDebug() << "RT_Total_Tax::calcula_impuesto a";
    if(reglas != NULL)
    {
        //qDebug() << "RT_Total_Tax::calcula_impuesto 1";
        impuesto = reglas->calcula_impuesto(base);
    }
    else{
        //qDebug() << "RT_Total_Tax::calcula_impuesto nulo";
    }
    //qDebug() << "RT_Total_Tax::calcula_impuesto " << QString::number(impuesto);
    return impuesto;
}

void RT_Total_Tax::acumula_impuesto(RT_Total_Tax* nodo)
{
    RT_Total_Tax* nodo_acumulador=find(nodo->id_gp_tax);
    //qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(nodo->id_gp_tax);
    RT_Total_individual_Tax* regla_acumuladora;
    RT_Total_individual_Tax* regla;
    bool continua;
    if(nodo_acumulador != NULL)
    {
        regla=nodo->reglas;
        while(regla !=NULL)
        {
            continua=true;
            regla_acumuladora=nodo_acumulador->reglas;
            while(continua)
            {
                qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(regla->id_athy_tx) << " " << QString::number(regla->ai_tx_rt_ru);
                if(regla->id_athy_tx == regla_acumuladora->id_athy_tx && regla->ai_tx_rt_ru == regla_acumuladora->ai_tx_rt_ru)
                {
                    qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(regla->base_gravable,'f',6) << " " << QString::number(regla->impuesto,'f',6);
                    regla_acumuladora->base_gravable += regla->base_gravable;
                    regla_acumuladora->mo_txbm_mnm += regla->mo_txbm_mnm;
                    regla_acumuladora->mo_txbm_mxm += regla->mo_txbm_mxm;
                    regla_acumuladora->impuesto += regla->impuesto;
                    impuesto+=regla->impuesto;
                    continua=false;
                }
                else
                {
                    regla_acumuladora=regla_acumuladora->next;
                    if(regla_acumuladora == NULL)
                    {
                        continua=false;
                    }
                }
            }
            regla = regla->next;
        }
    }
}

void RT_Total_Tax::resta_impuesto(RT_Total_Tax* nodo)
{
    RT_Total_Tax* nodo_acumulador=find(nodo->id_gp_tax);
    //qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(nodo->id_gp_tax);
    RT_Total_individual_Tax* regla_acumuladora;
    RT_Total_individual_Tax* regla;
    bool continua;
    if(nodo_acumulador != NULL)
    {
        regla=nodo->reglas;
        while(regla !=NULL)
        {
            continua=true;
            regla_acumuladora=nodo_acumulador->reglas;
            while(continua)
            {
                qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(regla->id_athy_tx) << " " << QString::number(regla->ai_tx_rt_ru);
                if(regla->id_athy_tx == regla_acumuladora->id_athy_tx && regla->ai_tx_rt_ru == regla_acumuladora->ai_tx_rt_ru)
                {
                    qDebug() << "RT_Total_Tax::acumula_impuesto " << QString::number(regla->base_gravable,'f',6) << " " << QString::number(regla->impuesto,'f',6);
                    regla_acumuladora->base_gravable -= regla->base_gravable;
                    regla_acumuladora->impuesto -= regla->impuesto;
                    regla_acumuladora->mo_txbm_mnm -= regla->mo_txbm_mnm;
                    regla_acumuladora->mo_txbm_mxm -= regla->mo_txbm_mxm;
                    impuesto-=regla->impuesto;
                    continua=false;
                }
                else
                {
                    regla_acumuladora=regla_acumuladora->next;
                    if(regla_acumuladora == NULL)
                    {
                        continua=false;
                    }
                }
            }
            regla = regla->next;
        }
    }
}

QString RT_Total_Tax::Get_XML(){
    QString xml="";
    RT_Total_individual_Tax* nodo= reglas;
    while(nodo!=NULL)
    {
        xml+=nodo->Get_XML();
        nodo=nodo->next;
    }
    return xml;
}

QString RT_Total_Tax::Get_PrintLines(){
    QString regreso="";

    if (reglas != NULL){
        qDebug()<< "RT_Total_Tax::Get_PrintLines() 1 " << QString::number(impuesto,'f',2) << " " << nm_gp_tx;
        regreso=reglas->Get_PrintLine();
    }
    if(next !=NULL){
        regreso+=next->Get_PrintLines();
    }
    return regreso;
}


RT_Total_Tax::~RT_Total_Tax()
{
    if (reglas != NULL)
    {
        delete reglas;
    }
    if (next != NULL)
        delete next;
    reglas=NULL;
    next=NULL;
}

