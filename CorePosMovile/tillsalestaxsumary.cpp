#include "tillsalestaxsumary.h"
#include "utilerias.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QString"
#include "QVariant"

tillsalestaxsumary::tillsalestaxsumary()
{
    id_gp_tx = -1;
    ai_athy_tx = -1;
    ai_ln_tax = -1;
    mo_txbl_rtn_sls = 0;
    mo_tx_rtn_sls = 0;
    mo_exm_txbl_sls = 0;
    mo_exm_tx = 0;
    next = NULL;
}

tillsalestaxsumary::tillsalestaxsumary(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax){
    QString query;
    QSqlDatabase sqldatabase;
    QSqlQuery sqlQuery1( sqldatabase.database("Origen") );
    Utilerias u;

    id_gp_tx = wid_gp_tx;
    ai_athy_tx = wai_athy_tx;
    ai_ln_tax = wai_ln_tax;
    mo_txbl_rtn_sls = 0;
    mo_tx_rtn_sls = 0;
    mo_exm_txbl_sls = 0;
    mo_exm_tx = 0;
    next = NULL;
    query="select tg.nm_gp_tx, tr.pe_rt_tx from TaxableGroup tg, TaxRateRule tr where tg.id_gp_tx = tr.id_gp_tx and ";
    query+="tr.id_gp_tx = "+QString::number(id_gp_tx)+" and tr.id_athy_tx = " + QString::number(ai_athy_tx) + " and tr.ai_tx_rt_ru = "+QString::number(ai_ln_tax);
    sqlQuery1.exec( query ) ;
    if (sqlQuery1.first())
    {
        nm_gp_tx = sqlQuery1.value("nm_gp_tx").toString();
        nm_gp_tx+= " ";
        nm_gp_tx+= u.FormatoNumero(sqlQuery1.value("pe_rt_tx").toDouble(),5,3)+"%";
    }
    else
        nm_gp_tx="";
    next=NULL;
}

tillsalestaxsumary* tillsalestaxsumary::find(int wid_gp_tx, int wai_athy_tx, int wai_ln_tax){
    tillsalestaxsumary* ret;
    ret = NULL;
    if((id_gp_tx == wid_gp_tx && ai_athy_tx == wai_athy_tx) && ai_ln_tax == wai_athy_tx)
        ret = this;
    else
        if(next != NULL) ret=next->find(wid_gp_tx, wai_athy_tx, wai_ln_tax);
    return ret;
}

void tillsalestaxsumary::append(tillsalestaxsumary* nodo){
    if(next == NULL) next = nodo;
    else next->append(nodo);
}

void tillsalestaxsumary::add(float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls, float wmo_exm_txbl_sls, float wmo_exm_tx){
    mo_txbl_rtn_sls+=wmo_txbl_rtn_sls;
    mo_tx_rtn_sls+=wmo_tx_rtn_sls;
    mo_exm_txbl_sls+=wmo_exm_txbl_sls;
    mo_exm_tx+=wmo_exm_tx;
}

QString tillsalestaxsumary::get_xml(){

    QString xmlCorte;
    Utilerias u;
    xmlCorte="<AI_LN_TAX>"+QString::number(ai_ln_tax)+"</AI_LN_TAX><ID_GP_TX>"+QString::number(id_gp_tx)+"</ID_GP_TX><AI_ATHY_TX>"+QString::number(ai_athy_tx)+"</AI_ATHY_TX>";
    xmlCorte+="<MO_TXBL_RTN_SLS>"+u.FormatoNumero(mo_txbl_rtn_sls,8,2)+"</MO_TXBL_RTN_SLS><MO_TX_RTN_SLS>"+u.FormatoNumero(mo_tx_rtn_sls,8,2)+"</MO_TX_RTN_SLS><MO_EXM_TXBL_SLS>"+u.FormatoNumero(mo_exm_txbl_sls,8,2);
    xmlCorte+="</MO_EXM_TXBL_SLS><MO_EXM_TX>"+u.FormatoNumero(mo_exm_tx,8,2)+"</MO_EXM_TX>";
    return xmlCorte;
}

tillsalestaxsumary::~tillsalestaxsumary(){
    if(next != NULL) delete next;
    next = NULL;
}
