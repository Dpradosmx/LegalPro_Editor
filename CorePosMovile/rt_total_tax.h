#ifndef RT_TOTAL_TAX_H
#define RT_TOTAL_TAX_H
#include "rt_total_individual_tax.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class RT_Total_Tax
{

// La estructura nos permite manejar tanto los calculos como la acumulacion de impuestos
// La estructura se puede cargar leyendo la base de datos o clonando la estructura completa
public:
    RT_Total_Tax(bool wdesglosa); //Carga la totalidad de grupos de impuesto
    RT_Total_Tax(RT_Total_Tax* nodo); //Clona la lista de nodos
    RT_Total_Tax(int wid_gpo_tx, RT_Total_Tax* nodo); //Clona un nodo de la lista de nodos
    RT_Total_Tax(bool wdesglosa, int wid_gp_tx, QString wnm_gp_tx, QString wcd_rcpt_prn );
    double calcula_impuesto(double base); //Calcula el impuesto
    void acumula_impuesto(RT_Total_Tax* nodo_fuente); //acumula los impuestos desde un nodo fuente
    void resta_impuesto(RT_Total_Tax* nodo_fuente);
    void inicia(){impuesto=0;}
    QString Get_XML(); // regresa las lineas de XML
    QString Get_PrintLines(); // Regresa las lineas de impresión
    bool desglosa_impuestos;
    RT_Total_individual_Tax *reglas;
    RT_Total_Tax* next;
    double impuesto;
    QString nm_gp_tx;
    QString cd_rcpt_prn;
    ~RT_Total_Tax();
protected:
    int id_gp_tax;
    //RT_Total_Tax nodo_inicial;
    QString query;
    QSqlDatabase sql;
    RT_Total_Tax* find(int wid_gp_tax); //encuentra un nodo a partir del raiz
    void RT_Total_Tax_Reglas(); //carga la totalidad de las reglas de impuestos
};

#endif // RT_TOTAL_TAX_H
