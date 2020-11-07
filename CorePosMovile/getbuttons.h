#ifndef GETBUTTONS_H
#define GETBUTTONS_H

#include <QObject>
#include <QVariantMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QSqlIndex>
#include <QDateTime>
#include <QMap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "settings.h"

class getbuttons
{
public:
    getbuttons();
    ~getbuttons();
    QString traerBotones();
    QString traerBotonesRoot();
    QString traerBotonesA(QString value);//A trae los conjuntos
    QString traerBotonesB(QString value);//B  trae los productos
    QString traerPadreDePadre(QString id_prnt);
    QList<QVariant> agregarBotones(QString value);

private:
    QString _cName ;
    Settings settings;
};

#endif // GETBUTTONS_H
