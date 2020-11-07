#ifndef RT_LINEITEMCHANGETENDER_H
#define RT_LINEITEMCHANGETENDER_H
#include "utilerias.h"
#include <QMap>
#include <QVariant>


class RT_LineItemChangeTender
{
public:
    RT_LineItemChangeTender();
    RT_LineItemChangeTender(QString tipo_pago, double importe);
    double get_total_cambio(){return mo_tnd_fn_trn;}
    double get_total_cambiofs(){return 0;}
    QString get_ty_tnd(){return ty_tnd;}
    QString get_XML();
    QString get_Impresion();
    QString get_titulo();
    QMap<QString, QVariant> getlinea();
    ~RT_LineItemChangeTender();
private:
    QString ty_tnd;
    double mo_tnd_fn_trn;
};

#endif // RT_LINEITEMCHANGETENDER_H
