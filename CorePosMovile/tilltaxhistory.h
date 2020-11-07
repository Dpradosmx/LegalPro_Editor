#ifndef TILLTAXHISTORY_H
#define TILLTAXHISTORY_H
#include <QObject>

class tilltaxhistory
{
public:
    tilltaxhistory();
    tilltaxhistory(int wid_athy_tx, int wid_gp_tx, int wai_ln_tx, float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls);
    tilltaxhistory* find(int wid_athy_tx, int wid_gp_tx, int wai_ln_tx);
    void add(float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls);
    void append(tilltaxhistory* nuevo);
    QString get_linea();
    QString get_xml();
    float get_mo_txbl_rtn_sls(){return mo_txbl_rtn_sls;}
    float get_mo_tx_rtn_sls(){return mo_tx_rtn_sls;}
    ~tilltaxhistory();
private:
    int id_athy_tx;
    int id_gp_tx;
    int ai_ln_tax;
    QString nm_gp_tx;
    float mo_txbl_rtn_sls;
    float mo_tx_rtn_sls;
    tilltaxhistory* next;
};

#endif // TILLTAXHISTORY_H
