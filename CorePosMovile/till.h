#ifndef TILL_H
#define TILL_H

#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>

class Till : public QObject
{
    Q_OBJECT
public:
    explicit Till(QObject *parent = 0);
    void abrir_Caja();
   void cajon_Abierto();

signals:

public slots:
};

#endif // TILL_H
