#include "rt_lineitemchangetender.h"

RT_LineItemChangeTender::RT_LineItemChangeTender()
{

}

RT_LineItemChangeTender::RT_LineItemChangeTender(QString tipo_pago, double importe)
{
    ty_tnd = tipo_pago;
    mo_tnd_fn_trn = importe;
}


QString RT_LineItemChangeTender::get_XML()
{
    QString xml;
    xml="<TenderChangeLineItem><TY_TND>CASH</TY_TND>";
    xml+="<MO_TND_FN_TRN>"+QString::number(mo_tnd_fn_trn)+"</MO_TND_FN_TRN></TenderChangeLineItem>";
    return xml;
}

QString RT_LineItemChangeTender::get_titulo()
{
    Utilerias u;
    return "Cambio en efectivo: $ "+u.FormatoNumero(get_total_cambio(),8,4);
}

QMap<QString, QVariant> RT_LineItemChangeTender::getlinea(){

    QMap<QString, QVariant> ret;
    Utilerias u;

    ret["textName"]= get_titulo();
    ret["textPrice"]=  "";
    ret["textTotal"]=  u.FormatoNumero(get_total_cambio(),8,4);
    ret["FOOD_STAMP"]= "";
    ret["QTY_ITM"]= "";
    ret["textQuantity"]="";
    ret["pack"]= false;
    return ret;
}

QString RT_LineItemChangeTender::get_Impresion(){
    QString impresion;
    Utilerias u;
    impresion = "Cambio en efectivo: $ "+u.FormatoNumero(get_total_cambio(),8,4);
    impresion+="\n";
    return impresion;
}

RT_LineItemChangeTender::~RT_LineItemChangeTender()
{

}

