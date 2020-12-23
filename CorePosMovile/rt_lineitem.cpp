#include "rt_lineitem.h"

RT_LineItem::RT_LineItem()
{

}

RT_LineItem::RT_LineItem(int wai_ln_item)
{
    ai_ln_item = wai_ln_item; //numero de la linea
    ty_ln_item = "AN"; //Tipo de concepto en la linea;
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = ""; //como se crea la linea
    lineitemvta = NULL;
    lineitemovr = NULL;
    lineitemtender = NULL;
    lineitemchangetender = NULL;
}

RT_LineItem::RT_LineItem(int wai_ln_item, QString wty_ln_item, QString wlu_mth_ltm_rtl_trn)
{
    ai_ln_item = wai_ln_item; //numero de la linea
    ty_ln_item =wty_ln_item; //Tipo de concepto en la linea;
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = wlu_mth_ltm_rtl_trn; //como se crea la linea
    lineitemvta = NULL;
    lineitemovr = NULL;
    lineitemtender = NULL;
    lineitemchangetender = NULL;
}

RT_LineItem::RT_LineItem(Item *warticulo, double cantidad, RT_Total_Tax *taxes, bool wfldevolucion)
{
    //2020 Es la creacion de la linea de venta
    ty_ln_item = "VE";
    qDebug() << "RTLineItem::RT_LineItem 3: " << ty_ln_item;
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = ""; //como se crea la linea
    if(wfldevolucion)
        lineitemvta = new RT_LineItemVta(warticulo, cantidad, taxes, wfldevolucion);
    else
        lineitemvta = new RT_LineItemVta(warticulo, cantidad, taxes);
    lineitemovr = NULL;
    lineitemtender = NULL;
    lineitemchangetender = NULL;
}

RT_LineItem::RT_LineItem(QString wty_tnd, double importe, bool change){
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = ""; //como se crea la linea
    lineitemovr=NULL;
    lineitemvta=NULL;
    if(!change)
    {
        ty_ln_item = "TE";
        lineitemtender= new RT_LineItemTender(wty_tnd, importe);
        lineitemchangetender = NULL;
    }
    else
    {
        ty_ln_item = "CH";
        lineitemtender= NULL;
        lineitemchangetender = new RT_LineItemChangeTender(wty_tnd, importe);
    }
}

RT_LineItem::RT_LineItem(QString wty_tnd, double importe, QString wid_persona, QString wid_cheque, QString wid_banco)
{
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = ""; //como se crea la linea
    lineitemovr=NULL;
    lineitemvta=NULL;
    ty_ln_item = "TE";
    lineitemtender= new RT_LineItemTender(wty_tnd, importe, wid_persona, wid_cheque, wid_banco);
    lineitemchangetender = NULL;
}

RT_LineItem::RT_LineItem(QString wty_tnd, double importe, QString wid_persona, QString wid_tdc, QString anio, QString mes, QString wnip, QString wtipo_tdc)
{
    fl_vd_ln_item = -1; //numero de la linea que anula a esta
    lu_mth_ltm_rtl_trn = ""; //como se crea la linea
    lineitemovr=NULL;
    lineitemvta=NULL;
    ty_ln_item = "TE";
    lineitemtender = new RT_LineItemTender(wty_tnd, importe, wid_persona, wid_tdc, anio, mes, wnip, wtipo_tdc);
    lineitemchangetender = NULL;
}

void RT_LineItem::subtract(RT_Total_Tax *taxes)
{
    if(lineitemvta !=NULL) lineitemvta->subtract(taxes);
}

void RT_LineItem::add(RT_Total_Tax *taxes)
{
    if(lineitemvta !=NULL) lineitemvta->add(taxes);
}

bool RT_LineItem::get_cancelable()
{
    //2020 Participa en cancelacion
    bool cancelable = true;

    qDebug() << "RT_LineItem::get_cancelable(): " << ty_ln_item << " " << QString::number(fl_vd_ln_item);
    if (ty_ln_item == "AN")
    {
        cancelable = false;
    }
    else
    {
        if(fl_vd_ln_item > -1)
            cancelable=false;
    }
    return cancelable;
}

bool RT_LineItem::do_cancel(int lineacancel){
    fl_vd_ln_item=lineacancel;
    return true;
}

void RT_LineItem::CambioPrecio(double wprecio, QString wTs, QString wId_opr, QString wRC_Ltx)
{

    if( lineitemovr == NULL)
        lineitemovr = new rt_lineitemovr(wTs, wId_opr, wRC_Ltx);
    else
        lineitemovr->set(wTs, wId_opr, wRC_Ltx);
    lineitemvta->set_precio_unitario(wprecio);
}

void RT_LineItem::set_cambios(QString c){

    lineitemvta->set_cambios(c);
}

QString RT_LineItem::get_titulo()
{
    QString resultado;
    if(ty_ln_item == "VE") resultado = lineitemvta->get_titulo();
    else if(ty_ln_item == "AN") resultado = "Cancela linea: " + QString::number(fl_vd_ln_item+1);
    else if(ty_ln_item == "TE") resultado = lineitemtender->get_titulo();
    else resultado = "";
    qDebug() << "RT_LineItem::get_titulo()" << resultado << " " << ty_ln_item;
    return resultado;
}

double RT_LineItem::get_importe(){
    double resultado;
    if(ty_ln_item == "VE") resultado = lineitemvta->get_importe();
    else resultado = 0;
    return resultado;
}

QString RT_LineItem::get_cambios(){
    QString resultado;
    if(ty_ln_item == "VE") resultado = lineitemvta->get_cambios();
    else resultado = "";
    return resultado;
}

double RT_LineItem::get_importefs(){
    double resultado;
    if(ty_ln_item == "VE") resultado = 0;
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_cantidad(){
    double resultado;
    if(ty_ln_item == "VE") resultado = lineitemvta->get_cantidad();
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_precio_unitario()
{
    double resultado;
    if (ty_ln_item == "VE") resultado = lineitemvta->get_precio_unitario();
    else resultado = 0;
    return resultado;
}

bool RT_LineItem::get_cancelada(){
    return (fl_vd_ln_item > 0);
}

QString RT_LineItem::get_tipo_renglon(){
    return ty_ln_item;
}

Item* RT_LineItem::get_articulo()
{
    if(ty_ln_item == "VE")return lineitemvta->articulo;
    else return NULL;
}

double RT_LineItem::get_total_tax()
{
    double resultado;
    if(ty_ln_item == "VE") resultado = lineitemvta->get_total_tax();
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_total_taxfs()
{
    double resultado;
    if(ty_ln_item == "VE") resultado = 0;
    else resultado = 0;
    return resultado;
}

QString RT_LineItem::get_ty_tnd()
{
    QString resultado;
    if(ty_ln_item == "TE")
        resultado = lineitemtender->get_ty_tnd();
        else if(ty_ln_item == "CH") resultado = lineitemchangetender->get_ty_tnd();
            else resultado = "";
    return resultado;
}

double RT_LineItem::get_total_pagado()
{
    double resultado;

    if(ty_ln_item == "TE")
        resultado = lineitemtender->get_total_pagado();
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_total_cambio(){
    double resultado;

    if(ty_ln_item == "CH")
        resultado = lineitemchangetender->get_total_cambio();
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_total_pagadofs()
{
    double resultado;

    if(ty_ln_item == "TE")
        resultado = lineitemtender->get_total_pagadofs();
    else resultado = 0;
    return resultado;
}

double RT_LineItem::get_total_cambiofs(){
    double resultado;

    if(ty_ln_item == "CH")
        resultado = lineitemchangetender->get_total_cambiofs();
    else resultado = 0;
    return resultado;
}

QString RT_LineItem::get_lu_mth_ltm_rtl_trn()
{
    return lu_mth_ltm_rtl_trn;
}

QString RT_LineItem::get_print_line(bool venta)
{
    QString regreso;
    regreso ="";
        if(fl_vd_ln_item == -1)
        {
            if(venta)
                if(lineitemvta != NULL) regreso=lineitemvta->get_Impresion();
            else{
                if(lineitemtender != NULL) regreso=lineitemtender->get_Impresion();
                if(lineitemchangetender != NULL) regreso=lineitemchangetender->get_Impresion();
            }
        }
    return regreso;
}

QMap<QString, QVariant> RT_LineItem::getlinea(int i){
    QMap<QString, QVariant> regreso;

    if(ty_ln_item == "AN")
    {
        regreso["textName"]="Cancela linea: " + QString::number(fl_vd_ln_item+1);
        regreso["isCancelation"]= true;
        regreso["textPrice"]="";
        regreso["textTotal"]="";
    }
    else
    {
        if(lineitemvta != NULL) regreso=lineitemvta->getlinea();
        else
            if(lineitemtender != NULL) regreso=lineitemtender->getlinea();
            else
                if(lineitemchangetender != NULL) regreso=lineitemchangetender->getlinea();
    }
    if(fl_vd_ln_item > 0){
        regreso["st"]="X";
        regreso["isCanceled"]= true;
        regreso["canceled"]=  true;
    }
    regreso["respuesta"]=1;
    qDebug() << "RT_LineItem::getlinea(int i) " << regreso["theTotal"].toString() << " " << regreso["textName"].toString() << " " << regreso["textQuantity"].toString() << " " << regreso["st"].toString();
    regreso["textCount"] = i+1;
    regreso["cambios"]=get_cambios();
    return regreso;
}

QString RT_LineItem::get_XML()
{
    QString xml;

    xml = "<RetailTransactionLineItem><AI_LN_ITEM>"+QString::number(ai_ln_item)+"</AI_LN_ITEM>";
    xml+= "<TY_LN_ITEM>"+ty_ln_item+"</TY_LN_ITEM>";
    xml+="<FL_VD_LN_ITEM>"+QString::number(fl_vd_ln_item)+"</FL_VD_LN_ITEM>";
    xml+="<LU_MTH_LTM_RTL_TRN>"+lu_mth_ltm_rtl_trn+"</LU_MTH_LTM_RTL_TRN>";
        if(lineitemvta !=NULL)
        xml+=lineitemvta->get_XML();
    if(lineitemovr != NULL)
        xml+=lineitemovr->get_xml();
    if(lineitemtender != NULL)
        xml+=lineitemtender->get_XML();
    if(lineitemchangetender != NULL)
        xml+=lineitemchangetender->get_XML();
    xml+= "</RetailTransactionLineItem>";
    return xml;
}

RT_LineItem::~RT_LineItem()
{
    if (lineitemovr != NULL)
    {
        delete lineitemovr;
        lineitemovr = NULL;
    }
    if (lineitemtender != NULL){
        delete lineitemtender;
        lineitemtender = NULL;
    }
    if (lineitemvta != NULL){
        delete lineitemvta;
        lineitemvta = NULL;
    }
    if (lineitemchangetender != NULL)
    {
        delete lineitemchangetender;
        lineitemchangetender = NULL;
    }
}

