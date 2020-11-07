#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QObject>

class transactions
{
public:
    transactions();
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

};

#endif // TRANSACTIONS_H
