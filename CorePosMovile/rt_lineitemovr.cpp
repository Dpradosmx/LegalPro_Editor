#include "rt_lineitemovr.h"

rt_lineitemovr::rt_lineitemovr()
{
}

rt_lineitemovr::rt_lineitemovr(QString wTs, QString wId_Opr, QString RC_LTX){
    set(wTs, wId_Opr, RC_LTX);
}

void rt_lineitemovr::set(QString wTs, QString wId_Opr, QString RC_LTX){
    TS_LTM_RTL_TRN_OVR =wTs;
    Id_OPr=wId_Opr;
    RC_LTX_RTL_TRN_OVR=RC_LTX;
}

QString rt_lineitemovr::get_xml()
{
    QString resultado;
    resultado = "<RetailTransactionLineItemOverride><ID_OPR>"+Id_OPr+"</ID_OPR><TS_LTM_RTL_TRN_OVR>"+TS_LTM_RTL_TRN_OVR+"</TS_LTM_RTL_TRN_OVR><RC_LTM_RTL_TRN_OVR>"+RC_LTX_RTL_TRN_OVR+"</RC_LTM_RTL_TRN_OVR></RetailTransactionLineItemOverride>";
    return resultado;
}

rt_lineitemovr::~rt_lineitemovr()
{

}

