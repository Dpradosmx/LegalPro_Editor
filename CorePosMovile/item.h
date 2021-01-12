#ifndef ITEM_H
#define ITEM_H

#include <QVariant>
#include "item_tax.h"
#include <QDateTime>

class Item {
public:
    Item();
    Q_INVOKABLE void set_item(QString ID_ITM, QString ID_ITM_PS_QFR);// obtiene un id y asigna bvalores al objeto
    Q_INVOKABLE void getprecios();
    Q_INVOKABLE int search_items(QString item, QString ps_qfr);
    //Q_INVOKABLE Item_tax get_item_tax(){return impuestos;}
    //Q_INVOKABLE double get_total_tax(){return total_tax;}
    Q_INVOKABLE QVariant get_item();
    void getpicture();
    Q_INVOKABLE int itemsearchPrepare(QVariant value);
    Q_INVOKABLE QString itemsearch();
    Q_INVOKABLE QString itemsearch_getPosidentity();
    Q_INVOKABLE QString itemsearch_getQfr();
    QString posidentity="";
    QString qfr="";
    int id_itm;
    QString xmlResultado;
    int id_itm_sl_prc;
    int id_mrhrc_gp;
    int id_brn;
    QString lu_exm_tx;
    QString nm_itm;
    QString de_itm;
    QString ty_itm;
    QString ty_itm_sv;
    int id_gp_tx;
    int id_gp_tx_buy;
    QString lu_cnt_sls_wt_un;
    QString url;
    QString food_stamp_ex;
    QString id_itm_ps;
    QString id_itm_ps_qfr;
    int qu_itm;
    double sell_price;
    double price_list;
    double offer_price;
    QVariant precio_volumen;
    double precio;
    QString itempictures="";
//    Item_tax impuestos;
//    double total_tax;

};

#endif // ITEM_H
