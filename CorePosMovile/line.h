#ifndef LINE_H
#define LINE_H
#include <QDebug>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>
#include <QObject>
#include "item.h"
#include "item_tax.h"

class line
{
public:
    line();
    void set_titulo(QString val){titulo=val;}
    QString get_titulo() const {return titulo;}
    void set_importe(double val){importe=val;}
    double get_importe() const {return importe;}
    void set_grupo_impuestos(QString val){grupo_impuestos=val;}
    QString get_grupo_impuestos() const {return grupo_impuestos;}
    void set_unitario(double val){unitario=val;}
    double get_unitario() const {return unitario;}
    void set_tipo_renglon(QString val){tipo_renglon=val;}
    QString get_tipo_renglon() const {return tipo_renglon;}
    void set_xml(QString val){xml=val;}
    QString get_xml() const {return xml;}
    void set_cancelable(bool var){cancelable=var;}
    bool get_cancelable() const{return cancelable;}


    void set_line(Item art,double unit);
    void set_line(QString titulo_line,double importe);
    void set_line(QString titulo_line,QString tipo_pago,double importe);
    void set_line(line linea, int indice);
    void set_line(double importe);
    void set_line(double importe, QString tipo);
    //line_item
    void set_articulo(Item var){articulo=var;}
    Item get_articulo(){return articulo;}
    void set_precio_unitario(double var){precio_unitario=var;}
    double get_precio_unitario(){return precio_unitario;}
    void set_cambio_precio(QString xml){cambio_de_precio=xml;}
    double total_tax;
    //line_pay
    void set_tipo_pago(QString value){tipo_pago=value;}
    QString get_tipo_pago()const {return tipo_pago;}
    //Line_cancelacion
    void set_cancelacion(int x){cancelacion=x;}
    int get_cancelacion() const {return cancelacion;}
    double precio_unitario;

private:
    QString titulo;
    double importe;
    QString grupo_impuestos;
    double unitario;
    QString tipo_renglon;
    QString xml;
    bool cancelable;
    //item
    Item articulo;
    Item_tax impuestos;
    QString cambio_de_precio;
    //pago
    QString tipo_pago;
    //cancelacion
    int cancelacion;


};

#endif // LINE_H
