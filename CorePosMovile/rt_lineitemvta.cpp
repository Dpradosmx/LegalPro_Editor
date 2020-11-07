#include "rt_lineitemvta.h"
#include "utilerias.h"


RT_LineItemVta::RT_LineItemVta()
{
    tax=NULL;
}

RT_LineItemVta::RT_LineItemVta(Item *warticulo, double cantidad, RT_Total_Tax *taxes)
{
    Utilerias u;
    articulo = warticulo;
    qu_itm_lm_rtn_sls = cantidad;
    tax = new RT_Total_Tax(articulo->id_gp_tx, taxes);
    mo_prc_act = articulo->precio;
    mo_prc_reg = mo_prc_act;
    importe = u.redondear(mo_prc_act * cantidad,2);
    desglosa_imp=taxes->desglosa_impuestos;
    qDebug() << "RT_LineItemVta::RT_LineItemVta: importe: " << QString::number(importe);
    tax->calcula_impuesto(importe);
    if(desglosa_imp){
        importe_base=importe - tax->impuesto;
        importe_full=importe;
    }
    else{
        importe_base = importe;
        importe_full = importe + tax->impuesto;
    }
    fldevolucion = false;
}

RT_LineItemVta::RT_LineItemVta(Item *warticulo, double cantidad, RT_Total_Tax *taxes, bool devolucion)
{
    Utilerias u;
    articulo = warticulo;
    if (fldevolucion)
        qu_itm_lm_rtn_sls = (-1) * cantidad;
    else
        qu_itm_lm_rtn_sls = cantidad;
    tax = new RT_Total_Tax(articulo->id_gp_tx, taxes);
    mo_prc_act = articulo->precio;
    mo_prc_reg = mo_prc_act;
    importe = u.redondear(mo_prc_act * qu_itm_lm_rtn_sls, 2);
    qDebug() << "RT_LineItemVta::RT_LineItemVta: importe: " << QString::number(importe);
    tax->calcula_impuesto(importe);
    fldevolucion = devolucion;
    if(desglosa_imp){
        importe_base=importe - tax->impuesto;
        importe_full=importe;
    }
    else{
        importe_base = importe;
        importe_full = importe + tax->impuesto;
    }
    //taxes->acumula_impuesto(tax);
}

void RT_LineItemVta::set_precio_unitario(double wPrecio){
    Utilerias u;

    mo_prc_act = wPrecio;
    importe = u.redondear(mo_prc_act * qu_itm_lm_rtn_sls, 2);
    tax->inicia();
    tax->calcula_impuesto(importe);
    if(desglosa_imp){
        importe_base=importe - tax->impuesto;
        importe_full=importe;
    }
    else{
        importe_base = importe;
        importe_full = importe + tax->impuesto;
    }
}

void RT_LineItemVta::subtract(RT_Total_Tax *taxes)
{
    taxes->resta_impuesto(tax);
}

void RT_LineItemVta::add(RT_Total_Tax *taxes)
{
    taxes->acumula_impuesto(tax);
}

double RT_LineItemVta::get_total_tax()
{
    return tax->impuesto;
}

double RT_LineItemVta::get_total_taxfs()
{
    return 0;
}

double RT_LineItemVta::get_precio_unitario()
{
    return mo_prc_act;
}

double RT_LineItemVta::get_importe()
{
    return importe;
}

double RT_LineItemVta::get_cantidad()
{
    return qu_itm_lm_rtn_sls;
}

QString RT_LineItemVta::get_titulo(){
    return articulo->nm_itm;
}

QMap<QString, QVariant> RT_LineItemVta::getlinea(){
    QMap<QString, QVariant> ret;
    Utilerias u;

    ret["textQuantity"]= u.FormatoNumero(qu_itm_lm_rtn_sls,3,3);
    ret["id_itm_ps"] = articulo->id_itm_ps;
    ret["id_itm_ps_qfr"] = articulo->id_itm_ps_qfr;
    ret["qu_itm"]=articulo->qu_itm;
    ret["textName"]= articulo->nm_itm;
    ret["textPrice"]=  u.FormatoNumero(mo_prc_act,8,4);
    ret["theTotal"] = u.FormatoNumero(importe,8,2);
    ret["textTotal"]=  u.FormatoNumero(importe,8,2);
    ret["QTY_ITM"]= articulo->ty_itm;
    ret["importe_base"]=importe_base;
    ret["importe_full"]=importe_full;
    ret["st"]="";
    ret["FOOD_STAMP"]= "";
    ret["pack"]= false;
    return ret;
}

QString RT_LineItemVta::get_XML()
{
    QString xml;
    Utilerias u;

    xml="<SaleReturnLineItem><ID_ITM>"+QString::number(articulo->id_itm)+"</ID_ITM>";
    xml+="<ID_ITM_PS>"+articulo->id_itm_ps+"</ID_ITM_PS><ID_ITM_PS_QFR>"+articulo->id_itm_ps_qfr+"</ID_ITM_PS_QFR>";
    xml+="<ID_GP_TX>"+QString::number(articulo->id_gp_tx)+"</ID_GP_TX> <TY_ITM>"+articulo->ty_itm+"</TY_ITM>";
    xml+="<TY_ITM_SV>"+articulo->ty_itm_sv+"</TY_ITM_SV><MO_PRC_REG>"+ u.FormatoNumero(mo_prc_reg,6,4)+"</MO_PRC_REG><FOOD_STAMP>"+articulo->food_stamp_ex+"</FOOD_STAMP>";
    xml+="<MO_PRC_ACT>"+u.FormatoNumero(mo_prc_act,8,4)+"</MO_PRC_ACT><MO_PRC_REG>"+u.FormatoNumero(mo_prc_reg,8,4)+"</MO_PRC_REG><MO_EXTND>"+u.FormatoNumero(importe,8,2)+"</MO_EXTND>";
    xml+="<QU_ITM_LM_RTN_SLS>"+QString::number(qu_itm_lm_rtn_sls,'f',4)+"</QU_ITM_LM_RTN_SLS>";
    xml+="<QU_ITM>"+QString::number(articulo->qu_itm)+"</QU_ITM><MO_IMPORTE_BASE>"+u.FormatoNumero(importe_base,8,4)+"</MO_IMPORTE_BASE><MO_IMPORTE_COB>"+u.FormatoNumero(importe_full,8,4)+"</MO_IMPORTE_COB>";
    xml+= tax->Get_XML();
    xml+="</SaleReturnLineItem>";
    return xml;
}

QString RT_LineItemVta::get_Impresion(){
    QString impresion;
    Ticket tik;
    Utilerias u;

    impresion=tik.text_ticket(get_titulo(),u.FormatoNumero(get_cantidad(),4,3),u.FormatoNumero(get_importe(),8,2),46,articulo->lu_exm_tx,u.FormatoNumero(get_precio_unitario(),4,4))+"\n";
    return impresion;
}

RT_LineItemVta::~RT_LineItemVta()
{
    delete articulo;
    delete tax;
    articulo=NULL;
    tax=NULL;
}

