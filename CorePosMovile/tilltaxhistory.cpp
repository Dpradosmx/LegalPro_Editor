#include "tilltaxhistory.h"
#include "ticket.h"
#include "utilerias.h"
#include "QSqlQuery"
tilltaxhistory::tilltaxhistory()
{
    id_athy_tx = -1;
    id_gp_tx = -1;
    ai_ln_tax = -1;
    mo_txbl_rtn_sls=0;
    mo_tx_rtn_sls = 0;
    next=NULL;
    nm_gp_tx = "";
}

tilltaxhistory::tilltaxhistory(int wid_athy_tx, int wid_gp_tx, int wai_ln_tx, float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls)
{
    QString query;
    QSqlDatabase sqldatabase;
    QSqlQuery sqlQuery1( sqldatabase.database("Origen") );
    Utilerias u;

    id_athy_tx = wid_athy_tx;
    id_gp_tx = wid_gp_tx;
    ai_ln_tax = wai_ln_tx;
    mo_txbl_rtn_sls=wmo_txbl_rtn_sls;
    mo_tx_rtn_sls = wmo_tx_rtn_sls;
    query="select tg.nm_gp_tx, tr.pe_rt_tx from TaxableGroup tg, TaxRateRule tr where tg.id_gp_tx = tr.id_gp_tx and ";
    query+="tr.id_gp_tx = "+QString::number(id_gp_tx)+" and tr.id_athy_tx = " + QString::number(id_athy_tx) + " and tr.ai_tx_rt_ru = "+QString::number(ai_ln_tax);
    sqlQuery1.exec( query ) ;
    if (sqlQuery1.first())
    {
        nm_gp_tx=sqlQuery1.value("nm_gp_tx").toString() + " " + u.FormatoNumero(sqlQuery1.value("pe_rt_tx").toDouble(),5,3)+"%";
    }
    else
        nm_gp_tx="";
    next=NULL;
}

void tilltaxhistory::add(float wmo_txbl_rtn_sls, float wmo_tx_rtn_sls)
{
    mo_txbl_rtn_sls+= wmo_txbl_rtn_sls;
    mo_tx_rtn_sls+= wmo_tx_rtn_sls;
}

tilltaxhistory* tilltaxhistory::find(int wid_athy_tx, int wid_gp_tx, int wai_ln_tx){
    tilltaxhistory *ret;

    if((id_athy_tx == wid_athy_tx && wid_gp_tx == id_gp_tx) && wai_ln_tx == ai_ln_tax)
        ret = this;
    else
        if(next != NULL) ret=next->find(wid_athy_tx, wid_gp_tx, wai_ln_tx);
        else ret = NULL;
    return ret;
}

void tilltaxhistory::append(tilltaxhistory* nuevo){
    if(next == NULL)
        next = nuevo;
    else
        next->append(nuevo);
}

QString tilltaxhistory::get_linea(){
    QString ret;
    Ticket T;
    Utilerias u;

    ret=T.text_centrado(nm_gp_tx,48)+"\n\n";
    ret+=T.text_lista("Base Gravable",u.FormatoNumero(mo_txbl_rtn_sls,8,2),48);
    ret+=T.text_lista("Total del impuesto",u.FormatoNumero(mo_tx_rtn_sls,8,2),48)+"\n\n";
    if(next!=NULL) ret+=next->get_linea();
    return ret;
}

QString tilltaxhistory::get_xml(){
    QString ret;
    Utilerias u;
    ret="<TillTaxHistory><ID_ATHY_TX>"+QString::number(id_athy_tx)+"</ID_ATHY_TX><ID_GP_TX>"+QString::number(id_gp_tx)+"</ID_GP_TX><AI_LN_TAX>"+QString::number(ai_ln_tax)+"</AI_LN_TAX>";
    ret+="<MO_TXBL_RTN_SLS>"+u.FormatoNumero(mo_txbl_rtn_sls,8,2)+"</MO_TXBL_RTN_SLS><MO_TX_RTN_SLS>"+u.FormatoNumero(mo_tx_rtn_sls,8,2)+"</MO_TX_RTN_SLS><MO_EXM_TXBL>0.00</MO_EXM_TXBL><MO_EXM_TX>0.00</MO_EXM_TX></TillTaxHistory>";
    if(next != NULL) ret+=next->get_xml();
    return ret;
}


tilltaxhistory::~tilltaxhistory(){
    if(next != NULL)
    {
        delete next;
        next = NULL;
    }
}
