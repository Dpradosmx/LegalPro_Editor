#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtCore/QDebug>
#include "retail_transaction.h"
#include "getbuttons.h"
#include "session.h"
#include <QPrinter>
#include <QPrinterInfo>
#include "qpainter.h"

#include "tillsalessumary.h"
#include "tillsalestaxsumary.h"
#include "tilltaxhistory.h"
#include "tillhistory.h"
#include <QtXml>
class principal : public QObject
{
Q_OBJECT
public:
    principal();
    Settings settings;
    QSqlDatabase sqldatabasecortex;
    bool modoventa; // true = venta, false consulta precios.
    RT_Total_Tax* Taxes;
    Item item;
    Ticket datos_ticket;
    int last_set_selected_result;
    session sesion_actual;
    QString xmlCorte;


    //ticket
    retail_Transaction* tiket;
    QVector<retail_Transaction*> tiket_espera;
    //fin ticket
signals:
    void actualizaMesa(int lista,QVariantList modelo);
//public signals:
  // void actualiza_mesa(int lista,QString modelo);
public slots:
   void estado_Mesa(int lista, int mesa,QString modelo,int estado);
   int itemsearchPrepare(QVariant value);
   QVariant itemsearch();
   QString itemsearch_getPosidentity();
   QString itemsearch_getQfr();
   QString buttonsRoot();
   QString buttonsAg(QString id_parent);
   QString buttonsPr(QString id_parent);
   QString buttonsParent(QString id_parent);

   QVariant set_selected(QString posidentity, QString posidentity_qfr, double cantidad);
   int get_last_set_selected_result(){return last_set_selected_result;}
   int getNumeroLineas();
   QVariant validacion(QVariant values);
   QVariant do_pay(QVariant value);
   QVariant put_change(QVariant value);
   QVariant finish_ticket(int is_cancelacion,QVariant cliente);
   void aplicar_cambios(QString cambio, int indice);
   QString login(QString u, QString p, bool supervisor);
   QVariant do_cortez();
   void impresion_dep(QString texto, int tipo,int transaction,QString fecha,int caja);
   void add_tilltender(QVariant values);
   QVariant do_cancel(QVariant value);
   QVariant validaCancel(QVariant value);
   QMap<QString, QVariant> getlinea(int i);
   QString logout();
};

#endif // PRINCIPAL_H
