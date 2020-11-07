#ifndef TICKET_H
#define TICKET_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "settings.h"
class Ticket
{
public:
    Ticket();
    QString encabezado1;
    QString encabezado2;
    QString pie1;
    QString pie2;

   void inicializar();
   QString text_centrado(QString texto, int tamanobuff);
   QString text_lista(QString texto1, QString valor, int tamanobuff);
   QString text_ticket(QString texto1, QString unit, QString valor, int tamanobuff, QString tx, QString precio_unitario);
private:
   Settings settings;
};

#endif // TICKET_H
