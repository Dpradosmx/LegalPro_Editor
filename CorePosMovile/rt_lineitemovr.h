#ifndef RT_LINEITEMOVR_H
#define RT_LINEITEMOVR_H
#include <QString>

class rt_lineitemovr
{
public:
    rt_lineitemovr();
    rt_lineitemovr(QString wTs, QString wId_Opr, QString RC_LTX);
    void set(QString wTs, QString wId_Opr, QString RC_LTX);
    QString get_xml();
    ~rt_lineitemovr();
private:
    QString TS_LTM_RTL_TRN_OVR;
    QString Id_OPr;
    QString RC_LTX_RTL_TRN_OVR;
};

#endif // RT_LINEITEMOVR_H
