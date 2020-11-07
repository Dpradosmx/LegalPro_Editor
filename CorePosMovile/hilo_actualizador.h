#ifndef HILO_ACTUALIZADOR_H
#define HILO_ACTUALIZADOR_H

#include <QtCore/QObject>
#include <QtSql>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QDebug>
#include <QEventLoop>
#include <QtCore/QMutex>
#include <QWaitCondition>
#include <QTimer>
#include <QtXml>

class hilo_actualizador : public QThread
{
Q_OBJECT
public:
    QSqlDatabase db;
    explicit hilo_actualizador(QObject *parent = 0);
    static hilo_actualizador * instance( QObject * o = NULL);


private :
    void setUp() ;
    void dowork();

    static hilo_actualizador * _instance ;
    QTimer * timer;

    QString abc_item(QString idt, QString sl_prc, QString merch, QString brand, QString exm_tx,
                      QString nombre, QString descripcion, QString ty, QString food,
                      QString spr,QString lu_cnt,QString cp_un_sl,
                      QString id_sl_prc,QString sell,QString list,QString ofer,QString fl_vl, QString itm_ps,
                      QString qfr,QString prep_cc,QString qu);

    QString abc_disbursement_a(QString rcv,QString de,QString ty);

    QString abc_disbursement_c(QString rcv,QString de,QString ty);

    QString abc_merchandisegroup_a(QString gp,QString prnt,QString nm,QString pe,QString tx,QString food);

    QString abc_merchandisegroup_c(QString gp,QString prnt,QString nm,QString pe,QString tx,QString food);

    QString abc_operator_a(QString opr,QString str,QString nm,QString pwd);

    QString abc_operator_c(QString opr,QString str,QString nm,QString pwd);

    QString abc_operatorgroup_a(QString str,QString gp,QString opr);

    QString abc_operatorgroup_c(QString str,QString gp,QString opr);

    QString abc_posidentity_a(QString itm_ps,QString qfr,QString id_sl_prc,QString idt,QString prep_cc,QString qu,QString sell,QString list, QString ofer,QString fl_vl);

    QString abc_posidentity_b(QString id_sl_prc,QString itm_ps,QString qfr);

    QString abc_retailstore_a(QString id_str,QString prty,QString ty_ro,QString strgrp,QString nm,
                              QString enc1,QString enc2,QString pie1,QString pie2,
                              QString id_merchant,QString p1,QString p2,QString p3,QString p4,
                              QString p5,QString p6);

    QString abc_suplier_a(QString spr,QString prty,QString ty,QString nm,QString mf,QString peri);

    QString abc_suplier_c(QString spr,QString prty,QString ty,QString nm,QString mf,QString peri);

    QString abc_taxablegroup_a(QString idg,QString nm,QString cd);

    QString abc_taxablegroup_c(QString idg,QString nm,QString cd);

    QString abc_taxgrouprule_a(QString athy,QString gp, QString ai, QString nm, QString acnt);

    QString abc_taxgrouprule_c(QString athy,QString gp, QString ai, QString nm,QString acnt);

    QString abc_taxraterule_a(QString athy,QString gp, QString ai, QString ty, QString txbm,QString txbl,QString mo,QString pe);

    QString abc_taxraterule_c(QString athy,QString gp,QString ai, QString ty,QString txbm,QString txbl,QString mo,QString pe);

    QString abc_tender_a(QString ty,QString act,QString cny,QString tnd,QString nmb_srz,QString azn_rq,QString mth_azn,QString ep_rq,QString mxm_alow,QString rq_ct,QString prsl_rq,
                         QString lcl_cny,QString ct_rq,QString tnd_chn,QString drw_open,QString tndce_off,QString endsm_rq,QString plaz,QString itm_ps,QString btn,QString food
                         );

    QString abc_tender_c(QString ty,QString act,QString cny,QString tnd,QString nmb_srz,QString azn_rq,
                         QString mth_azn,QString ep_rq,QString mxm_alow,QString rq_ct,QString prsl_rq,
                         QString lcl_cny,QString ct_rq,QString  tnd_chn,QString drw_open,QString  tndce_off,
                         QString endsm_rq,QString plaz,QString itm_ps,QString btn,QString food
                         );

    QString abc_till_a(QString str,QString rpsty,QString ws,QString opr,QString sc,QString  opn, QString  mxm);

    QString abc_till_c(QString str,QString rpsty,QString ws,QString opr,QString sc,QString  opn, QString  mxm);

    QString abc_workstation_a(QString str,QString ws,QString eq, QString se, QString  qu,QString fl);

    QString abc_buttonconfig_a(QString id_str,QString btnset,QString btn,QString prnt,QString ty,QString wt,
                           QString nm, QString de,QString itm, QString icon,QString strgrp,
                           QString itm_ps,QString qfr,QString webserv,QString params,QString pos);

    QString buttonconfig_c(QString id_str,QString btnset,QString btn,QString prnt,QString ty,QString wt,
                           QString nm, QString de,QString itm, QString icon,QString strgrp,
                           QString itm_ps,QString qfr,QString webserv,QString param,QString pos);

    QString buttonconfig_b(QString str,QString btnset,QString btn);

    QString ejecutaQuery(QString quer);
signals:

    void setservice(double valor);


public slots:
    void CicloRecover();
};

#endif // HILO_ACTUALIZADOR_H
