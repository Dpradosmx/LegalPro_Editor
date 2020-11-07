#ifndef RETAIL_TRANSACTION_H
#define RETAIL_TRANSACTION_H
#include "rt_lineitem.h"
#include "line.h"
#include "item_line.h"
#include "rt_lineitemvta.h"
#include "lista_impuestos.h"
#include "ticket.h"
#include "utilerias.h"
#include <QVector>
#include "cliente.h"
#include "settings.h"
#include "till_tender.h"
class retail_Transaction
{


public:
    retail_Transaction();
    QMap<QString, QVariant> add_line(RT_LineItem *linea);
    QMap<QString, QVariant> add_line(line linea);
    QMap<QString,QVariant> actualizar();
    void inicializar(bool wdesglosaimpuestos, RT_Total_Tax* wTaxes);
    RT_LineItem* get_line(int indice) {return rt_lineitem.at(indice);}
    QString get_ts_trn_bgn(){return ts_trn_bgn;}
    QString do_transaction();
    QMap<QString,QVariant> add_line_cancel(int NoLinea);
    int do_cancel(int indice);
    QMap<QString,QVariant> do_cambio_precio(int indice, QVariant param);
    QMap<QString,QVariant> getTotales();
    int get_total_art();
    void set_cliente(QVariant cliente, QVariant wnmcliente);
    void elimina_cliente();
    bool venta_activa();
    QString UPagoFS;
    QString get_impresion(bool venta);
    int getNumeroLineas() {return rt_lineitem.length();}
    QMap<QString, QVariant> getlinea(int i);
    bool toggleflDevolucion();
    bool getflDevolucion();
    void resetflDevolucion(){flDevolucion = false;}
    bool getPosibleNoVenta();
    ~retail_Transaction();
    QMap<QString,QVariant> do_cambios(int indice, QVariant param);
    //line get_line(int indice){return lineas.at(indice);}



    QString xml;

    bool desglosaimpuestos;
    int qu_un_rtl_trn;      //numero de articulos
    int qu_itm_ln_sc;       //cantidad de lineas escaneadas
    double pe_itm_ln_sc;    //porcentaje escaneados vs tecleados
    int qu_itm_ln_ky;       //lineas tecleadas
    QString id_factura;     //id de la factura
    double total_pagado;
    double total_impuesto;
    double total_v;
    int total_articulos;

    double total_pagadofs;
    double total_impuestofs;
    double total_vfs;
    int total_articulosfs;


    QString string_impresion;
    QString articulos_impresion;
    QString pagos_impresion;
    QString tx;
    lista_impuestos total_impuestos;
    till_tender tender;
    QList<line> lineas;
    Ticket tik;//solo para obtener las funciones que acomodan el text

private:
    Utilerias u;
    bool flDevolucion;
    bool flCancelado;
    Settings settings;
    Item_tax tax;
    QString ts_trn_bgn;
    Cliente* cliente = NULL;
    RT_Total_Tax* Taxes = NULL;
    QVector<RT_LineItem*> rt_lineitem;
};

#endif // RETAIL_TRANSACTION_H
