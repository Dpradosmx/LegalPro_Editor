#include "rt_lineitemtender.h"
#include "utilerias.h"

RT_LineItemTender::RT_LineItemTender()
{

}

RT_LineItemTender::RT_LineItemTender(QString tipo_pago, double importe)
{
    ty_tnd = tipo_pago;
    mo_frg_cy = importe;
    mo_itm_ln_tnd = importe;
    id_persona = "";
    id_cheque = "";
    id_banco = "";
    fdst=false;
}


RT_LineItemTender::RT_LineItemTender(QString tipo_pago, double importe, QString wid_persona, QString wid_cheque, QString wid_banco)
{
    ty_tnd = tipo_pago;
    mo_frg_cy = importe;
    mo_itm_ln_tnd = importe;
    id_persona = wid_persona;
    id_cheque = wid_cheque;
    id_banco = wid_banco;
    id_tdc="";
    fecha = "";
    nip = "";
    fdst=false;
    tipo_pago = "";
}

RT_LineItemTender::RT_LineItemTender(QString tipo_pago, double importe, QString wid_persona, QString wid_tdc, QString mes, QString anio, QString wnip, QString wtipo_tdc)
{
    ty_tnd = tipo_pago;
    mo_frg_cy = importe;
    mo_itm_ln_tnd = importe;
    id_cheque = "";
    id_banco = "";
    id_persona = wid_persona;
    id_tdc=wid_tdc;
    fecha = mes+anio;
    nip = wnip;
    fdst=false;
    tipo_pago = wtipo_tdc;
    if(tipo_pago == "FDST")
        fdst=true;
}

QString RT_LineItemTender::get_XML()
{
    QString xml;
    Utilerias u;

    xml=" <TenderLineItem><TY_TND>"+ty_tnd+"</TY_TND>";
    xml+="<MO_FRG_CY>"+u.FormatoNumero(mo_frg_cy,8,2)+"</MO_FRG_CY>"+"<MO_ITM_LN_TND>"+u.FormatoNumero(mo_itm_ln_tnd,8,2)+"</MO_ITM_LN_TND>";
    if(id_cheque!="")
        xml+="<CHECKTENDERLINEITEM><ID_BN>"+id_banco+"</ID_BN><ID_ACNT_CK>"+id_cheque+"</ID_ACNT_CK><ID_PRSL_AZN>"+id_persona+"</ID_PRSL_AZN></CHECKTENDERLINEITEM>";
    if(id_tdc != "")
        xml+="<CREDITDEBITCARDTENDERLINEITEM><ID_ACNT_DB_CR_CRDN>"+id_tdc+"</ID_ACNT_DB_CR_CRDN><DE_EP_CRD>"+fecha+"</DE_EP_CRD><NM_CRD_HLD>"+id_persona+"</NM_CRD_HLD><AI_CRED_ISS>"+nip+"</AI_CRED_ISS></CREDITDEBITCARDTENDERLINEITEM>";
    xml+="</TenderLineItem>";
    return xml;
}

QString RT_LineItemTender::get_titulo()
{
    QString regreso = "Efectivo: ";
    if(id_cheque!="")
        regreso = "Cheque " + id_cheque;
    if(id_tdc != "")
        regreso = "Tarjeta crédito/débito "+id_tdc.right(4);
    return regreso;
}

QMap<QString, QVariant> RT_LineItemTender::getlinea(){

    QMap<QString, QVariant> ret;
    Utilerias u;

    ret["textQuantity"]= "";
    ret["textName"]= get_titulo();
    ret["textPrice"]=  "";
    ret["textTotal"]=  u.FormatoNumero(mo_itm_ln_tnd,8,2);
    ret["FOOD_STAMP"]= "";
    ret["QTY_ITM"]= "";
    ret["textQuantity"]="";
    ret["pack"]= false;
    return ret;
}

QString RT_LineItemTender::get_Impresion(){
    QString impresion;
    Utilerias u;
    impresion = "Efectivo:               "+u.FormatoNumero(get_total_pagado(),8,2);
    if(id_cheque!="")
        impresion = "Cheque:                 " + id_cheque + " $"+u.FormatoNumero(get_total_pagado(),8,2);
    if(id_tdc != "")
        impresion = "Tarjeta crédito/débito: "+id_tdc.right(4) + " $"+u.FormatoNumero(get_total_pagado(),8,2);
    impresion+='\n';
    return impresion;
}

double RT_LineItemTender::get_total_pagado(){
    return mo_itm_ln_tnd;
}

double RT_LineItemTender::get_total_pagadofs(){
    if(fdst)
        return mo_itm_ln_tnd;
    else
        return 0;
}

RT_LineItemTender::~RT_LineItemTender()
{

}

