#ifndef SESSION_H
#define SESSION_H
#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QSqlIndex>
#include <QString>
#include <QMap>
#include <QList>
#include <QDate>
#include <QObject>
//#include "logthread.h"
#include <QProcess>
#include <QVariant>
#include <QVariantMap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QStack>
#include <QVariantList>
#include <QStringRef>
#include <QNetworkReply>
//#include <QDeclarativeView>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QSemaphore>
#include <QtCore/QMutex>
//#include "syncdatabase.h"
//#include "netsoapclient.h"
//#include "syncdatabasethread.h"
//#include "syncthread.h"
#include "settings.h"

class session
{
public:
    session();
    QVariant setLogin(QString usuario, QString password);
    QString login_operador(QString usuario, QString password);
    QString get_cortez(QSqlDatabase sql);
    void logout(int ultima_trn);
    void blockeo();
    QString desblockeo(QString usuario, QString password, QSqlDatabase sql);
    void abrir_dia();
    void cerrar_dia();
    QString Get_BusinessDayF(QString formato) {return fechaBusinessday.toString(formato);}
    QString Get_OperSup(){return id_opr_sup;}
    QString Get_Oper(){return id_opr;}
    QString Get_ts_tm_str(){return ts_tm_str;}
    QDateTime Get_BusinessDay(){return fechaBusinessday;}
public:

    //datos de tienda
    QString NM_STR_RT;
    QString DOMICILIO;
    QString COLONIA;
    QString CIUDAD;
    QString ESTADO;
    QString PAIS;
    QString CP;
    QSqlDatabase sqlDatabasebut ;//base de datos
    QList<QMap<QString,QString>> permisos;
    QDateTime fechaBusinessday;
    QDateTime fechaBusinessday1;
    int mismo_usuario;
    QString _cName ;
    bool blockeado;
    QString id_rpsty_tnd;
    QString OPERADOR;//nombre del operador
    Settings settings;
    QList<QMap<QString,QString>> permisosadmin;

private :
    int numero_de_intentos=0;
    QString id_opr_sup;
    QString id_str_rt; //tienda
    QString id_ws;//estacion de trabajo
    QString id_opr;//operador
    QString ts_tm_str;//inicio de sesion
    QString ts_end;//fin de sesion
    QString trn_bgn;// primera transaccion
    QString trn_end;//ultima transaccion
    QString bsn_bgn;//fecha de primera transaccion
    QString id_end;//fecha de la ultima transaccion
};

#endif // SESSION_H
