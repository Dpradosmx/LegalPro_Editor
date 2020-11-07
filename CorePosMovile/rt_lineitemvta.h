#ifndef RT_LINEITEMVTA_H
#define RT_LINEITEMVTA_H
#include "rt_total_tax.h"
#include "item.h"
#include "ticket.h"

class RT_LineItemVta
{
public:
    RT_LineItemVta();
    RT_LineItemVta(Item *warticulo, double cantidad, RT_Total_Tax *taxes);
    RT_LineItemVta(Item *warticulo, double cantidad, RT_Total_Tax *taxes, bool devolucion);
    void subtract(RT_Total_Tax *taxes);
    void add(RT_Total_Tax *taxes);
    QString get_titulo();
    double get_importe();
    double get_importefs();
    double get_cantidad();
    double get_precio_unitario();
    QString get_XML();
    QString get_Impresion();
    void set_precio_unitario(double wPrecio);
    double get_total_tax();
    double get_total_taxfs();
    QMap<QString, QVariant> getlinea();
    Item* articulo;
    ~RT_LineItemVta();
    void set_cambios(QString c){cambios=c;}
    QString get_cambios(){return cambios;}
protected:
    bool fldevolucion;
    double mo_prc_reg;
    double mo_prc_act;
    double qu_itm_lm_rtn_sls;
    double importe;
    double importe_base; //sin impuestos
    double importe_full; //con impuestos
    bool desglosa_imp;
    RT_Total_Tax *tax;
    //linea de cambios
    QString cambios;
};

#endif // RT_LINEITEMVTA_H
