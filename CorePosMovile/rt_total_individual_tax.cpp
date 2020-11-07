#include "rt_total_individual_tax.h"
#include "utilerias.h"
#include <QDebug>

RT_Total_individual_Tax::RT_Total_individual_Tax(int wid_athy_tx, int wid_gp_tx, int wai_tx_rt_ru, QString wty_tx_rt_ru, double wmo_txbm_mnm, double wmo_txbm_mxm, double wmo_rt_tx, double wpe_rt_tx)
{
    id_athy_tx = wid_athy_tx;
    id_gp_tx = wid_gp_tx;
    ai_tx_rt_ru = wai_tx_rt_ru;
    mo_txbm_mnm = wmo_txbm_mnm;
    mo_txbm_mxm = wmo_txbm_mxm;
    ty_tx_rt_ru=wty_tx_rt_ru;
    mo_rt_tx = wmo_rt_tx;
    pe_rt_tx = wpe_rt_tx;
    base_gravable = 0;
    impuesto = 0;
    next = NULL;
//    qDebug() << "RT_Total_individual_Tax::RT_Total_individual_Tax Crea nuevo "<<id_athy_tx<< " "<<id_gp_tx << " " << ai_tx_rt_ru << " " << next;
}

RT_Total_individual_Tax::RT_Total_individual_Tax(RT_Total_individual_Tax* nodo)
{
    id_athy_tx = nodo->id_athy_tx;
    ai_tx_rt_ru = nodo->ai_tx_rt_ru;
    id_gp_tx = nodo->id_gp_tx;
    ty_tx_rt_ru=nodo->ty_tx_rt_ru;
    mo_txbm_mnm = 0;
    mo_txbm_mxm = 0;
    mo_rt_tx = nodo->mo_rt_tx;
    pe_rt_tx = nodo->pe_rt_tx;
    base_gravable = 0;
    impuesto = 0;
    if(nodo->next == NULL)
    {
        //qDebug() << "RT_Total_individual_Tax::RT_Total_individual_Tax Crea COPIA "<<id_athy_tx<< " "<<id_gp_tx << " " << ai_tx_rt_ru << " NULL";
        next = NULL;
    }
    else
    {
        //qDebug() << "RT_Total_individual_Tax::RT_Total_individual_Tax Crea COPIA "<<id_athy_tx<< " "<<id_gp_tx << " " << ai_tx_rt_ru << " !NULL";
        next = new RT_Total_individual_Tax(nodo->next);
    }
    //qDebug() << "RT_Total_individual_Tax::RT_Total_individual_Tax Crea COPIA "<<id_athy_tx<< " "<<id_gp_tx << " " << ai_tx_rt_ru << " " << next;
}

void RT_Total_individual_Tax::append(RT_Total_individual_Tax* nodo)
{
    if(next == NULL)
    {
        qDebug() << "RT_Total_individual_Tax::append Asignando el nodo";
        next = nodo;
    }
    else
    {
        qDebug() << "RT_Total_individual_Tax::append Asignando el nodo rec.";
        next->append(nodo);
    }
}

void RT_Total_individual_Tax::Erase(){
    base_gravable = 0;
    impuesto=0;
}

double RT_Total_individual_Tax::Get_Base_gravable(){
    return base_gravable;
}

double RT_Total_individual_Tax::Get_impuesto(){
    return impuesto;
}

double RT_Total_individual_Tax::calcula_impuesto(double base){

    double impuesto1;
    double nuevabase;

    impuesto=0;
    base_gravable=base;
    qDebug() << "rt_total_individual_tax::calcula impuesto base "<< QString::number(base);
    if(desglosa_impuestos)
    {
        qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos";
        if(ty_tx_rt_ru == "PE")
        {
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos porcentaje tasa: " + QString::number(pe_rt_tx);
            nuevabase = u.redondear(base / (1+(pe_rt_tx/100)),2);
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos porcentaje tasa 1: " + QString::number(nuevabase,'f',6);
//            nuevabase = u.redondear(nuevabase,2);
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos porcentaje tasa 2: " + QString::number(nuevabase,'f',6);
            impuesto1 = base - nuevabase;
            base = nuevabase;
        }
        else
        {
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos monto: " + QString::number(mo_rt_tx, 'f', 3);
            impuesto1 = mo_rt_tx;
            base = base - impuesto1;
        }
        base_gravable=base;
        impuesto=impuesto1;
        qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos base: " << QString::number(base,'f',4) << " " << QString::number(impuesto1,'f',4) <<  " " << QString::number(3.141592,'f',4);
    }
    else
    {
        qDebug() << "rt_total_individual_tax::calcula impuesto NO desglosa impuestos";
        base_gravable=base;
        if(ty_tx_rt_ru == "PE")
        {
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos porcentaje" + QString::number(pe_rt_tx);
            impuesto1 = u.redondear((base * pe_rt_tx / 100),2);
        }
        else
        {
            qDebug() << "rt_total_individual_tax::calcula impuesto desglosa impuestos monto: " + QString::number(mo_rt_tx);
            impuesto1 = mo_rt_tx;

        }
        impuesto=impuesto1;
    }
    if(next == NULL) {
        qDebug() << "rt_total_individual_tax::calcula impuesto resultado"<< QString::number(impuesto);
        return impuesto;
    }
    else
    {
        impuesto+=next->calcula_impuesto(base_gravable);
        qDebug() << "rt_total_individual_tax::calcula impuesto resultado"<< QString::number(impuesto, 'f', 4);
        return impuesto;
    }

}

QString RT_Total_individual_Tax::Get_XML(){
    QString xml;

    xml="<SaleReturnTaxLineItem><ID_ATHY_TX>"+QString::number(id_athy_tx)+"</ID_ATHY_TX>";
    xml+="<ID_GP_TX>"+QString::number(id_gp_tx)+"</ID_GP_TX>";
    xml+="<AI_TX_RT_RU>"+QString::number(ai_tx_rt_ru)+"</AI_TX_RT_RU>";
    xml+="<MO_TXBL_RTN_SLS>"+QString::number(base_gravable,'f',2)+"</MO_TXBL_RTN_SLS>";
    xml+="<MO_TX_RTN_SLS>"+QString::number(impuesto,'f',2)+"</MO_TX_RTN_SLS></SaleReturnTaxLineItem>";
    return xml;
}

QString RT_Total_individual_Tax::Get_PrintLine()
{
    QString regreso = "";
    regreso="Impuesto "+ u.FormatoNumero(pe_rt_tx,3,2) +"%: "+u.FormatoNumero(impuesto,10,2)+"  ";
    regreso=regreso.rightJustified(46,' ')+"  \n";
    return regreso;

}

RT_Total_individual_Tax::~RT_Total_individual_Tax()
{
    if (next!=NULL)
    {
        delete next;
        next=NULL;
    }
}

