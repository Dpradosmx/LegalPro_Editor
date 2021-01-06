#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QObject>
#include <settings.h>
#include <qsqldatabase.h>
#include<qsqlquery.h>
#include <qdebug.h>

class transactions
{
public:
    transactions(QString bsn,QString ts, int idopr);
    transactions(QString ty_trn);
   QString dcdybsn;
   QString aitrn;
   QString idopr;
   QString tstmstr;
   QString tytrn;
   QString tstrnbgn;
   QString tstrnend;
   QString flcncl;
   QString flvd;
   QString fltrgtrn;
   QString flkeyofl;
   QString xml;
public Q_SLOTS:
   int anular_Transaccion();
   int cancelar_transaccion(int id_trn);
   int terminar_transaccion();

   Settings settings;
   QSqlDatabase sqldatabasecortex;
};

#endif // TRANSACTIONS_H
