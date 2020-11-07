#ifndef TILLSALESTAXSUMARY_H
#define TILLSALESTAXSUMARY_H
#include <QObject>
#include "QString"

class tillsalestaxsumary
{
public:
    tillsalestaxsumary();
    tillsalestaxsumary(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax);
    tillsalestaxsumary* find(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax);
    void append(tillsalestaxsumary* nodo);
    void add(float mo_txbl_rtn_sls, float mo_tx_rtn_sls, float mo_exm_txbl_sls, float mo_exm_tx);
    QString get_xml();
    ~tillsalestaxsumary();
protected:
    int id_gp_tx;
    int ai_athy_tx;
    int ai_ln_tax;
    QString nm_gp_tx;
    float mo_txbl_rtn_sls;
    float mo_tx_rtn_sls;
    float mo_exm_txbl_sls;
    float mo_exm_tx;
    tillsalestaxsumary *next;
};

#endif // TILLSALESTAXSUMARY_H
