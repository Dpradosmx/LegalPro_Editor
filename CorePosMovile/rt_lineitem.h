#ifndef RT_LINEITEM_H
#define RT_LINEITEM_H
#include <QString>
#include "item.h"
#include "rt_lineitemvta.h"
#include "rt_total_tax.h"
#include "rt_lineitemovr.h"
#include "rt_lineitemtender.h"
#include "rt_lineitemchangetender.h"

class RT_LineItem
{
public:
    RT_LineItem();
    RT_LineItem(int wai_ln_item);
    RT_LineItem(int wai_ln_item, QString wty_ln_item, QString wlu_mth_ltm_rtl_trn);
    RT_LineItem(Item *warticulo, double cantidad, RT_Total_Tax *taxes, bool wfldevolucion);
    RT_LineItem(QString ty_tnd, double importe, bool change);
    RT_LineItem(QString ty_tnd, double importe, QString wid_persona, QString wid_cheque, QString wid_banco);
    RT_LineItem(QString wty_tnd, double importe, QString wid_persona, QString wid_tdc, QString anio, QString mes, QString wnip, QString wtipo_tdc);
    bool get_cancelable();
    bool get_cancelada();
    bool do_cancel(int lineacancel);
    QString get_tipo_renglon();
    double get_cantidad();
    Item* get_articulo();
    QString get_titulo();
    double get_precio_unitario();
    double get_importe();
    double get_total_tax();
    double get_importefs();
    double get_total_taxfs();
    double get_total_pagado();
    double get_total_cambio();
    double get_total_pagadofs();
    double get_total_cambiofs();
    void set_line(int line){ai_ln_item=line;}
    QString get_lu_mth_ltm_rtl_trn();
    QString get_print_line(bool venta);
    QString get_ty_ln_item(){return ty_ln_item;}
    QString get_ty_tnd();
    QString get_XML();
    QMap<QString, QVariant> getlinea(int i);
    void CambioPrecio(double wprecio, QString wTs, QString wId_opr, QString wRC_Ltx);
    void subtract(RT_Total_Tax* taxes);
    void add(RT_Total_Tax* taxes);
    ~RT_LineItem();
    void set_cambios(QString c);
    QString get_cambios();

protected:
    RT_LineItemVta* lineitemvta;
    rt_lineitemovr* lineitemovr;
    RT_LineItemTender* lineitemtender;
    RT_LineItemChangeTender* lineitemchangetender;
    int ai_ln_item; //numero de la linea
    QString ty_ln_item; //Tipo de concepto en la linea;
    int fl_vd_ln_item; //numero de la linea que anula a esta
    QString lu_mth_ltm_rtl_trn; //como se crea la linea
};

#endif // RT_LINEITEM_H
