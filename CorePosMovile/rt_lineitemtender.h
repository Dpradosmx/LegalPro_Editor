#ifndef RT_LINEITEMTENDER_H
#define RT_LINEITEMTENDER_H
#include <QString>
#include <QVariant>
#include <QMap>


class RT_LineItemTender
{
public:
    RT_LineItemTender();    
    RT_LineItemTender(QString tipo_pago, double importe);
    RT_LineItemTender(QString tipo_pago, double importe, QString wid_persona, QString wid_cheque, QString wid_banco);
    RT_LineItemTender(QString tipo_pago, double importe, QString wid_persona, QString wid_tdc, QString mes, QString anio, QString wnip, QString wtipo_tdc);
    double get_total_pagado();
    double get_total_pagadofs();
    QString get_ty_tnd(){return ty_tnd;}
    QString get_XML();
    QString get_Impresion();
    QMap<QString, QVariant> getlinea();
    QString get_titulo();
    ~RT_LineItemTender();
private:
    double mo_frg_cy;
    double mo_itm_ln_tnd;
    QString ty_tnd;
    QString titulo;

    //Datos Banco
    QString id_persona;
    QString id_cheque;
    QString id_banco;

    //Datos TDC
    QString id_tdc;
    QString fecha;
    QString nip;
    QString tipo_tdc;

    bool fdst;
};

#endif // RT_LINEITEMTENDER_H
