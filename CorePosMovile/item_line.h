#ifndef ITEM_LINE_H
#define ITEM_LINE_H
#include "line.h"
#include "item.h"
#include "item_tax.h"

class item_line : public line
{
public:
    item_line();
    void set_item_line(Item art, double unit);//precio es la linea del precio
    void set_articulo(Item var){articulo=var;}
    Item get_articulo(){return articulo;}
    void setstring(QString val){stringdearticulo=val;}
    QString getstring(){return stringdearticulo;}

private:
    Item articulo;
    QString stringdearticulo;
    Item_tax impuestos;
};

#endif // ITEM_LINE_H
