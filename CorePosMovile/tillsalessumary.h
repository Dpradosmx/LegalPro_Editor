#ifndef TILLSALESSUMARY_H
#define TILLSALESSUMARY_H
#include <QObject>
#include "tillsalestaxsumary.h"
#include "QString"

class tillsalessumary
{
public:
    tillsalessumary();
    tillsalessumary(int wid_itm, int wid_rpsty_tnd, int wid_lcn);
    tillsalessumary* find(int wid_itm, int wid_rpsty_tnd, int wid_lcn);
    void add(float wmo_sls_itm, float wqu_sls_itm, float wqu_sls_trn,
             float wmo_rtn_itm , float wqu_rtn_itm, float wqu_rtn_trn, float wmo_xdep_itm,
             float wqu_xdep_itm, float wqu_xdep_trn, float wmo_pag_itm, float wqu_pag_itm,
             float wqu_pag_trn);
    void add_tax(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax, float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls, float wmo_exm_txbl_sls, float wmo_exm_tx);
    QString get_xml();
    void append(tillsalessumary* nuevo);
    ~tillsalessumary();
private:
     int id_itm;
     int id_rpsty_tnd;
     int id_lcn;
     float mo_sls_itm;
     float qu_sls_itm;
     int qu_sls_trn;
     float mo_rtn_itm;
     float qu_rtn_itm;
     float qu_rtn_trn;
     float mo_xdep_itm;
     float qu_xdep_itm;
     float qu_xdep_trn;
     float mo_pag_itm;
     float qu_pag_itm;
     float qu_pag_trn;
     tillsalestaxsumary* impuestos;
     tillsalessumary* next;
};

#endif // TILLSALESSUMARY_H
