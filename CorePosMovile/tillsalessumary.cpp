#include "tillsalessumary.h"
#include "utilerias.h"

tillsalessumary::tillsalessumary()
{
     id_itm = -1;
     id_rpsty_tnd = -1;
     id_lcn = -1;
     mo_sls_itm = 0;
     qu_sls_itm = 0;
     qu_sls_trn = 0;
     mo_rtn_itm = 0;
     qu_rtn_itm = 0;
     qu_rtn_trn = 0;
     mo_xdep_itm = 0;
     qu_xdep_itm = 0;
     qu_xdep_trn = 0;
     mo_pag_itm = 0;
     qu_pag_itm = 0;
     qu_pag_trn = 0;
     impuestos = NULL;
     next=NULL;
}

tillsalessumary::tillsalessumary(int wid_itm, int wid_rpsty_tnd, int wid_lcn)
{
    id_itm = wid_itm;
    id_rpsty_tnd = wid_rpsty_tnd;
    id_lcn = -wid_lcn;
    mo_sls_itm = 0;
    qu_sls_itm = 0;
    qu_sls_trn = 0;
    mo_rtn_itm = 0;
    qu_rtn_itm = 0;
    qu_rtn_trn = 0;
    mo_xdep_itm = 0;
    qu_xdep_itm = 0;
    qu_xdep_trn = 0;
    mo_pag_itm = 0;
    qu_pag_itm = 0;
    qu_pag_trn = 0;
    impuestos = NULL;
    next=NULL;
}


tillsalessumary* tillsalessumary::find(int wid_itm, int wid_rpsty_tnd, int wid_lcn){
    tillsalessumary* ret;
    ret = NULL;
    if((id_itm==wid_itm && id_rpsty_tnd==wid_rpsty_tnd) && id_lcn == wid_lcn) ret= this;
    else if (next != NULL) ret = next->find(wid_itm, wid_rpsty_tnd, wid_lcn);
    return ret;
}

void tillsalessumary::add(float wmo_sls_itm, float wqu_sls_itm, float wqu_sls_trn,
                          float wmo_rtn_itm , float wqu_rtn_itm, float wqu_rtn_trn, float wmo_xdep_itm,
                          float wqu_xdep_itm, float wqu_xdep_trn, float wmo_pag_itm, float wqu_pag_itm,
                          float wqu_pag_trn){
    mo_sls_itm += wmo_sls_itm;
    qu_sls_itm += wqu_sls_itm;
    qu_sls_trn += wqu_sls_trn;
    mo_rtn_itm += wmo_rtn_itm;
    qu_rtn_itm += wqu_rtn_itm;
    qu_rtn_trn += wqu_rtn_trn;
    mo_xdep_itm += wmo_xdep_itm;
    qu_xdep_itm += wqu_xdep_itm;
    qu_xdep_trn += wqu_xdep_trn;
    mo_pag_itm += wmo_pag_itm;
    qu_pag_itm += wqu_pag_itm;
    qu_pag_trn += wqu_pag_trn;
}

void tillsalessumary::add_tax(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax, float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls, float wmo_exm_txbl_sls, float wmo_exm_tx)
{
    tillsalestaxsumary* nodo;
    if(impuestos == NULL)
    {
        impuestos = new tillsalestaxsumary(wid_gp_tx, wai_athy_tx, wai_ln_tax);
        impuestos->add(wmo_txbl_rtn_sls, wmo_tx_rtn_sls, wmo_exm_txbl_sls, wmo_exm_tx);
    }
    else
    {
        nodo = impuestos->find(wid_gp_tx, wai_athy_tx, wai_ln_tax);
        if(nodo==NULL)
        {
            nodo = new tillsalestaxsumary(wid_gp_tx, wai_athy_tx, wai_ln_tax);
            impuestos->append(nodo);
        }
        nodo->add(wmo_txbl_rtn_sls, wmo_tx_rtn_sls, wmo_exm_txbl_sls, wmo_exm_tx);
    }
}

void tillsalessumary::append(tillsalessumary* nuevo)
{
    if(next == NULL) next=nuevo;
    else next->append(nuevo);
}

QString tillsalessumary::get_xml()
{
    QString xmlCorte;
    Utilerias u;
    xmlCorte= "<TillSalesSummary><ID_ITM>"+QString::number(id_itm)+"</ID_ITM><MO_SLS_ITM>"+u.FormatoNumero(mo_sls_itm,8,2)+"</MO_SLS_ITM><QU_SLS_ITM>"+u.FormatoNumero(qu_sls_itm,8,3)+"</QU_SLS_ITM><QU_SLS_TRN>"+u.FormatoNumero(qu_sls_trn,8,3)+"</QU_SLS_TRN>";
    xmlCorte+="<MO_RTN_ITM>"+u.FormatoNumero(mo_rtn_itm,8,2)+"</MO_RTN_ITM><QU_RTN_ITM>"+u.FormatoNumero(qu_rtn_itm,8,3)+"</QU_RTN_ITM><QU_RTN_TRN>"+u.FormatoNumero(qu_rtn_trn,8,3)+"</QU_RTN_TRN><MO_XDEP_ITM>"+u.FormatoNumero(mo_xdep_itm,8,2)+"</MO_XDEP_ITM>";
    xmlCorte+="<QU_XDEP_ITM>"+u.FormatoNumero(qu_xdep_itm,8,2)+"</QU_XDEP_ITM><QU_XDEP_TRN>"+u.FormatoNumero(qu_xdep_trn,8,2)+"</QU_XDEP_TRN><MO_PAG_ITM>"+u.FormatoNumero(mo_pag_itm,8,2)+"</MO_PAG_ITM><QU_PAG_ITM>"+u.FormatoNumero(qu_pag_itm,8,2)+"</QU_PAG_ITM>";
    xmlCorte+="<QU_PAG_TRN>"+u.FormatoNumero(qu_pag_trn,8,2)+"</QU_PAG_TRN>";
    if(impuestos != NULL)
    {
        xmlCorte+="<TillSalesTaxSummary>"+impuestos->get_xml()+"</TillSalesTaxSummary>";
    }
    xmlCorte+="</TillSalesSummary>";
    if(next !=NULL)
        xmlCorte+=next->get_xml();
    return xmlCorte;
}

tillsalessumary::~tillsalessumary(){
    if(next != NULL) delete next;
    next = NULL;
    if(impuestos != NULL) delete impuestos;
    impuestos = NULL;
}
