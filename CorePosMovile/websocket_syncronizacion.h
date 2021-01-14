#ifndef WEBSOCKET_SYNCRONIZACION_H
#define WEBSOCKET_SYNCRONIZACION_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtSql>
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <settings.h>

class websocket_syncronizacion : public QObject
{
Q_OBJECT
    Q_PROPERTY(double progreso_actualizacion READ progreso_actualizacion WRITE setProgreso_actualizacion NOTIFY progreso_actualizacionChanged)
QThread workerThread;
public:
    int ai_ln_max;
    int ai_ln_actual;
    QSqlDatabase db;
    Settings settings;
    websocket_syncronizacion();
    explicit websocket_syncronizacion(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    QStringList opciones;
    bool primeravez=true;
Q_SIGNALS:
    void closed();
signals:
    void progreso_actualizacionChanged();
    void setsyncronizacion();
    void loginf(int instancia,int tienda);
    void confirmado(int valor);//1 si 0 no
    void instalacionCompleta(int instancia,int tienda);
    void altaExpress(QString mensaje);
private Q_SLOTS:
    void onConnected();
    void onConnected2();
    void onConnected3();
    void onTextMessageReceived(QString message);

public slots:
    void init_websocket();
    void iniciar(const QUrl &url2);
    void iniciar2(const QString &url3);
    void send_message(QString mensaje,int actual);
    void send_message_log_conf(QString mensaje);
    void send_message_inst(QString mensaje);
    void cerrar_slot();
    int get_max();
    void base_de_datos();
    void run_hilo_actualizador() ;
    void muestra_progreso_sincronizacion(double text);
    //set y get del valor de la actualizacion
    double progreso_actualizacion() const;
    void setProgreso_actualizacion(double value);
    void insertar();
    void select();
    void selectquery(QString query);
    void updatequery(QString querys);
    QString get_tender();
private:
    QWebSocket m_webSocket;//syncronizacion
    QWebSocket m_webSocket2;//login/confirmacion
    QWebSocket m_webSocket3;//instalacion
    QUrl m_url;
    bool m_debug;
    double m_progreso_actualizacion;
    QString ejecutaQuery(QString quer);
    QString abc_item(QString idt, QString sl_prc, QString merch, QString brand, QString exm_tx,
                      QString nombre, QString descripcion, QString ty, QString food,
                      QString spr,QString lu_cnt,QString cp_un_sl,
                      QString id_sl_prc,QString sell,QString list,QString ofer,QString fl_vl, QString itm_ps,
                      QString qfr,QString prep_cc,QString qu);
};

#endif // WEBSOCKET_SYNCRONIZACION_H
