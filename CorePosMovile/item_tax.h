#ifndef ITEM_TAX_H
#define ITEM_TAX_H

#include <QDebug>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>
#include "settings.h"

class Item_tax
{

public:
    Item_tax();
    double get_tax(QString id_gp_tx, double monto, QSqlDatabase sql);
    void set_tax(QString id_gp_tx1, double cantidad);
    //QString ty_tx_rt_ru; //impuesto de porcentaje o directo

    QString id_athy_tx;
    QString id_gp_tx;
    QString ai_cmpnd;
    QList<QMap<QString,QVariant>> impuestos;
    bool DesglosaImp;
private:
    Settings *settings;
};

#endif // ITEM_TAX_H
