#ifndef TILL_TENDER_H
#define TILL_TENDER_H
#include <QVariant>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMap>
#include "settings.h"
#include <QStringList>
#include "rt_lineitem.h"
class till_tender: public QObject
{
    Q_OBJECT
public:
    explicit till_tender(QObject *parent = 0);

    Q_INVOKABLE bool addTillTender(QString ty_tnd, int ty_trn, QString monto, QString signo);
    Q_INVOKABLE bool addTillTender(RT_LineItem* linea, QString signo);
    Q_INVOKABLE QMap<QString, QVariant> valida_Operacion(QString ty_tnd, double monto, double monto_cobro, QMap<QString, QVariant> capturas);
    Q_INVOKABLE void revision(QMap<QString,QVariant> capturas);
    Q_INVOKABLE bool altaformapago(QString wty_tnd);
    Q_INVOKABLE QStringList tenderlist(int modo, QString wty_tnd); //modo 1 = regresa todas las formas de pago, modo 2 = regresa las otras formas de pago, modo 3 = regresa 1 forma de pago
    Q_INVOKABLE bool searchTender(QString wty_tnd);
    Q_INVOKABLE int tenderlist_prepare(char tipo);
    Q_INVOKABLE QString get_tenderlist(char tipo);
    Q_INVOKABLE QMap<QString, QVariant> getPropertiesTender(QString wty_tnd);
private:
    Settings settings ;
    QString ty_tnd;
    int id_act_ldg;
    int id_cny;
    int id_itm;
    QString de_tnd;
    bool fl_nmb_srz;
    bool fl_azn_rq;
    QString lu_mth_azn;
    bool fl_idtn_rq_ct;
    bool fl_id_prsl_rq;
    bool fl_avlb_lcl_cny;
    bool fl_sgntr_ct_rq;
    float mo_th_tnd_chn;
    bool fl_drw_open;
    float mo_apvl_tndce_off;
    bool plazos;
    bool fl_dt_azn_ep_rq;
    bool tenderlistprepared;
    QString xmlResultado;
    QString btn_asigned;
};

#endif // TILL_TENDER_H
