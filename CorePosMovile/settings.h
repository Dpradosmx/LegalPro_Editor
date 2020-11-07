#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QDateTime>
#include <QtSerialPort/QSerialPort>

class Settings : public QObject
{
    Q_OBJECT
public:

    explicit Settings(QObject *parent = 0);

    Q_INVOKABLE QString getBackDbName() ;
    Q_INVOKABLE QString getBackPassword() ;
    Q_INVOKABLE QString getBackUser() ;
    Q_INVOKABLE QString getBtnHome() ;
    Q_INVOKABLE QDateTime getBusinessDay(){return DC_DY_BSN;}
    Q_INVOKABLE void      setBusinessDay(QString);
    Q_INVOKABLE QString getCountry(){return Country; }
    Q_INVOKABLE void setCountry(QString value);
    Q_INVOKABLE QString getDbName() ;
    Q_INVOKABLE QString getDesglosaImpuestos();
    Q_INVOKABLE void    setDesglosaImpuestos(QString value);
    Q_INVOKABLE bool    getDebug(){return debug;}
    Q_INVOKABLE void    setDebug(bool wdebug);
    Q_INVOKABLE QString getHasVirtualWindow() ;
    Q_INVOKABLE void    setHasVirtualWindow(QString value);
    Q_INVOKABLE QString getIdContent() { return idContent ;}
    Q_INVOKABLE QString getIdInstancia() ;
    Q_INVOKABLE QString getIdMerchant() { return idMerchant ; }
    Q_INVOKABLE QString getIdStore() ;
    Q_INVOKABLE int     getIdOpr() { return idOpr; }
    Q_INVOKABLE void    setIdOpr(int);
    Q_INVOKABLE QString getIdWorkStation() ;
    Q_INVOKABLE void    setIdWorkStation(QString value);
    Q_INVOKABLE QString getImpuestoPOrig() { return ImpuestoPOrig;}
    Q_INVOKABLE void    setImpuestoPOrig(QString value);
    Q_INVOKABLE QString getIsNew() ;
    Q_INVOKABLE void    setIsNew( QString value ) ;
    Q_INVOKABLE QString getLineMax() ;
    Q_INVOKABLE void    setNewLineMax( QString value ) ;
    Q_INVOKABLE void    setNoIntentos(int value);
    Q_INVOKABLE int     getNoIntentos();
    Q_INVOKABLE QString getPassword() ;
    Q_INVOKABLE QString getScale() {return Scale; }
    Q_INVOKABLE QString getScalePort() {return ScalePort; }
    Q_INVOKABLE QString getScaleBaudRatetxt() {return ScaleBaudRate;}
    Q_INVOKABLE QSerialPort::BaudRate getScaleBaudRate();
    Q_INVOKABLE QString getScaleDataBitstxt() {return ScaleDataBits;}
    Q_INVOKABLE QSerialPort::DataBits getScaleDataBits();
    Q_INVOKABLE QString getScaleFlowControltxt() {return ScaleFlowControl;}
    Q_INVOKABLE QSerialPort::FlowControl getScaleFlowControl();
    Q_INVOKABLE QString getScaleParitytxt() {return ScaleParity;}
    Q_INVOKABLE QSerialPort::Parity getScaleParity();
    Q_INVOKABLE QString getScaleStopBitstxt() {return ScaleStopBits;}
    Q_INVOKABLE QSerialPort::StopBits getScaleStopBits();
    Q_INVOKABLE QString getScaleRemLeft() {return ScaleRemLeft;}
    Q_INVOKABLE QString getScaleRemRight() {return ScaleRemRight;}
    Q_INVOKABLE QString getScaleRequest() {return ScaleRequest;}
    Q_INVOKABLE QDateTime getSessionTime() {return Ts_Tm_Str;}
    Q_INVOKABLE void      setSessionTime(QString);

    Q_INVOKABLE void setScale(QString value);
    Q_INVOKABLE void setScalePort(QString value);
    Q_INVOKABLE void setScaleBaudRate(QString value);
    Q_INVOKABLE void setScaleDataBits(QString value);
    Q_INVOKABLE void setScaleFlowControl(QString value);
    Q_INVOKABLE void setScaleParity(QString value);
    Q_INVOKABLE void setScaleStopBits(QString value);
    Q_INVOKABLE void setScaleRemLeft(QString value);
    Q_INVOKABLE void setScaleRemRight(QString value);
    Q_INVOKABLE void setScaleRequest(QString value);
    Q_INVOKABLE QString getSerie() ; // Se nos proporciona el numero de serie de la maquina
    Q_INVOKABLE QString getTaxInPrice() ;
    Q_INVOKABLE void    setTaxInPrice(QString value);
    Q_INVOKABLE QString getTraining () {return Training; }
    Q_INVOKABLE void    setTraining(QString value);
    Q_INVOKABLE QString getUpdateVer() {return UpdatePos; }
    Q_INVOKABLE QString getUser() ;
    Q_INVOKABLE QString getVersion() { return VersionPos; }
    Q_INVOKABLE QString getWebAccess() ;
    Q_INVOKABLE QString getWebCambioPass ();
    Q_INVOKABLE QString getWebAccessSync() ;
    Q_INVOKABLE QString getWebAccessTH1() ;
    Q_INVOKABLE int     getWindowWidth() ;
    Q_INVOKABLE void setBloqued_Time(bool bloquea);
    Q_INVOKABLE QString getBloqued_Time();
    Q_INVOKABLE bool getFullscreen();
    Q_INVOKABLE void reload() { setUp(); }
    Q_INVOKABLE void set_habilita_Alta(bool value);
    Q_INVOKABLE bool get_habilita_Alta();
    void setIdStore(QString value);
    void setUp() ;

private:
    QString backDbName ;
    QString backPassword ;
    QString backUser ;
    QString btnHome;
    QString Country;
    QString dbName ;
    bool debug;
    QString desglosaImpuestos;
    bool habilita_Alta;
    QString idContent;
    QString idInstancia ;
    QString idMerchant ;
    QString idStore ;
    int idOpr;
    QString idWorkStation ;
    QString ImpuestoPOrig;
    QString Scale;
    QString ScalePort;
    QString ScaleBaudRate;
    QString ScaleDataBits;
    QString ScaleFlowControl;
    QString ScaleParity;
    QString ScaleStopBits;
    QString ScaleRemLeft;
    QString ScaleRemRight;
    QString ScaleRequest;
    QString hasVirtualWindow ;
    QDateTime Ts_Tm_Str;
    QString host ;
    QString isNew ;
    QString lineMax ;
    QString password ;
    int     port ;
    QString taxInPrice ; // El taz esta encluido en el precio ( visible )
    QString Training;
    QString UpdatePos;
    QString user ;
    QString VersionPos;
    QString webAccess ;
    QString webServices ;
    QString webServicesSync ;
    QString webServicesTH1;
    int     windowWidth ; // El ancho de la ventana principal
    bool fullcreen;
    int cerrar;

    QDateTime DC_DY_BSN;

signals:
    
public slots:
    
};

#endif // SETTINGS_H
