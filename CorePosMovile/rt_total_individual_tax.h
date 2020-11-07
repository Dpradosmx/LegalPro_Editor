#ifndef RT_TOTAL_INDIVIDUAL_TAX_H
#define RT_TOTAL_INDIVIDUAL_TAX_H
#include "QString"
#include "settings.h"
#include "utilerias.h"
#include "lista_simple.h"

class RT_Total_individual_Tax : public lista_simple
{
public:
    RT_Total_individual_Tax(int wid_athy_tx, int wid_gp_tx, int wai_tx_rt_ru, QString wty_tx_rt_ru, double wmo_txbm_mnm, double wmo_txbm_mxm, double wmo_rt_tx, double wpe_rt_tx);
    RT_Total_individual_Tax(RT_Total_individual_Tax* nodo);
    void append(RT_Total_individual_Tax* nodo1);
    ~RT_Total_individual_Tax();
    void Erase();
    double Get_Base_gravable();
    double Get_impuesto();
    double calcula_impuesto(double base);
    QString Get_XML();
    QString Get_PrintLine();
    bool desglosa_impuestos;
    int id_athy_tx;
    int id_gp_tx;
    int ai_tx_rt_ru;
    double base_gravable;
    double impuesto;
    QString ty_tx_rt_ru;
    double mo_txbm_mnm;
    double mo_txbm_mxm;
    double mo_rt_tx;
    double pe_rt_tx;
    RT_Total_individual_Tax *next;
private:
    Utilerias u;
};

#endif // RT_TOTAL_INDIVIDUAL_TAX_H
