#ifndef LISTA_IMPUESTOS_H
#define LISTA_IMPUESTOS_H
#include <QDebug>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>
#include <QObject>

class lista_impuestos
{
public:
    lista_impuestos();
    QList <QMap<QString,QVariant>> get_listaimpuestos(){return impuestos;}
    void add_to_list(QString impuesto, double valor, double base,QString tipo);
    void add_to_list(QString impuesto, double valor, double base);
    void add_to_list_usa(QString impuesto, double valor, double base);
    void print();
    void clear();
    QList <QMap<QString,QVariant>> impuestos;

private:


};

#endif // LISTA_IMPUESTOS_H
