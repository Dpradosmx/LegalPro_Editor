#include "settings.h"
#include <QtNetwork/QNetworkInterface>


Settings::Settings(QObject *parent) :
    QObject(parent)
{

}

void Settings::setUp()
{
    // *************************   IMPORTANTE *************************************
    // Mantener las variables de ambiente que toma del registry en orden alfabético


    //QSettings settings( QSettings::UserScope , "CORE" , "POINTOS" , this ) ;
    QSettings settings("CORE" , "POSMOBILE" ) ;

    if ( settings.contains( "BACKDBNAME") == false )
    {
        settings.setValue( "BACKDBNAME" , "BackOffice" ); // Es el contador de maximas lineas
    }
    backDbName =settings.value( "BACKDBNAME").toString()  ;

    if ( settings.contains( "BACKPASSWORD") == false )
    {
        settings.setValue( "BACKPASSWORD" , "" ); // Es el contador de maximas lineas
    }
    backPassword = settings.value( "BACKPASSWORD").toString()  ;
    if ( settings.contains( "BACKUSER") == false )
    {
        settings.setValue( "BACKUSER" , "root" ); // Es el contador de maximas lineas
    }
    backUser = settings.value( "BACKUSER").toString()  ;
    if (settings.contains("BLOQUED_TIME")==false)
    {
        settings.setValue("BLOQUED_TIME", "1900-01-01 00:00:00");
    }
    if ( settings.contains( "BTNHOME") == false )
    {
        settings.setValue( "BTNHOME" , "true" ); // Es el contador de maximas lineas
    }
    btnHome = settings.value( "BTNHOME" ).toString()  ;
    if ( settings.contains( "COUNTRY") == false )
    {
        settings.setValue( "COUNTRY" , "USA");
    }
    Country = settings.value( "COUNTRY").toString() ;
    if ( settings.contains( "DbName") == false )
    {
        settings.setValue( "DbName" , "PosOS"); // Para mexico
    }
    dbName = settings.value( "DbName").toString() ;
    if ( settings.contains( "DESGLOSAIMPUESTOS") == false )
    {
        settings.setValue( "DESGLOSAIMPUESTOS" , "TRUE"); // para usa es false
    }
    desglosaImpuestos = settings.value( "DESGLOSAIMPUESTOS").toString() ;
    if ( settings.contains( "FULLSCREEN") == false )
    {
        settings.setValue( "FULLSCREEN" , "TRUE" ); // pantalla completa
    }
    fullcreen = settings.value("FULLSCREEN").toBool();
    if ( settings.contains("HABILITA_ALTA")  == false)
    {
        settings.setValue("HABILITA_ALTA", "TRUE");
    }
    if (settings.value( "HABILITA_ALTA").toString() == "TRUE")
    {
       habilita_Alta = true;
    }
    else
    {
       habilita_Alta = false;
    }
    if( settings.contains("DEBUG") == false)
    {
        settings.setValue("DEBUG", "TRUE");
    }
    if (settings.value("DEBUG") == "TRUE")
    {
        debug = true;
    }
    else
    {
        debug = false;
    }
    if ( settings.contains( "HASVIRTUALWINDOW") == false )
    {
        settings.setValue( "HASVIRTUALWINDOW" , "true" ); // Es el contador de maximas lineas
    }
    hasVirtualWindow = settings.value( "HASVIRTUALWINDOW" ).toString()  ;
    if ( settings.contains( "HOST") == false )
    {
        settings.setValue( "HOST" , "business.core.com.mx" ); //
    }
    host = settings.value( "HOST").toString()  ;
    if ( settings.contains( "IDCONTENT") == false )
    {
        settings.setValue( "IDCONTENT" , "2" ); // Es el contador de maximas lineas
    }
    idContent = settings.value( "IDCONTENT" ).toString()  ;
    if ( settings.contains( "IDINSTANCIA") == false )
    {
        settings.setValue( "IDINSTANCIA" , "1");
    }
    idInstancia = settings.value( "IDINSTANCIA").toString() ;
    if ( settings.contains( "IDMERCHANT") == false )
    {
        settings.setValue( "IDMERCHANT" , "NULL");
    }
    idMerchant = settings.value( "IDMERCHANT").toString() ;
    if ( settings.contains( "IDSTORE") == false )
    {
        settings.setValue( "IDSTORE" , "1");
    }
    idStore = settings.value( "IDSTORE").toString() ;
    if ( settings.contains( "IDWORKSTATION") == false )
    {
        settings.setValue( "IDWORKSTATION" , "1");
    }
    idWorkStation = settings.value( "IDWORKSTATION").toString() ;
    if ( settings.contains( "IMPUESTOPORIG") == false)
    {
        settings.setValue("IMPUESTOPORIG", "FALSE");
    }
    ImpuestoPOrig = settings.value("IMPUESTOPORIG").toString() ;
    if ( settings.contains( "LINEMAX") == false )
    {
        settings.setValue( "LINEMAX" , 0 ); // Es el contador de maximas lineas
    }
    if ( settings.contains( "NO_INTENTOS") == false )
    {
        settings.setValue( "NO_INTENTOS" , 0 ); // Es el contador de maximas lineas
    }
    lineMax = QString::number( settings.value( "LINEMAX").toInt() ) ;
    if ( settings.contains( "password") == false )
    {
        settings.setValue( "password" , "password"); // Para mexico
    }
    password = settings.value( "password").toString() ;
    if ( settings.contains( "PORT") == false )
    {
        settings.setValue( "PORT" , 8080 ); // Es el puerto
    }
    port = settings.value( "PORT" ).toInt()  ;
    if ( settings.contains( "SCALE") == false)
    {
        settings.setValue("SCALE", "NONE");
    }
    Scale = settings.value("SCALE").toString() ;
    if ( settings.contains( "SCALEPORT") == false)
    {
        settings.setValue("SCALEPORT", "COM1");
    }
    ScalePort = settings.value("SCALEPORT").toString() ;
    if ( settings.contains( "SCALEBAUDRATE") == false)
    {
        settings.setValue("SCALEBAUDRATE", "Baud9600");
    }
    ScaleBaudRate = settings.value("SCALEBAUDRATE").toString() ;
    if ( settings.contains( "SCALEDATABITS") == false)
    {
        settings.setValue("SCALEDATABITS", "Data8");
    }
    ScaleDataBits = settings.value("SCALEDATABITS").toString() ;
    if ( settings.contains( "SCALEFLOWCONTROL") == false)
    {
        settings.setValue("SCALEFLOWCONTROL", "NoFlowControl");
    }
    ScaleFlowControl = settings.value("SCALEFLOWCONTROL").toString() ;
    if ( settings.contains( "SCALEPARITY") == false)
    {
        settings.setValue("SCALEPARITY", "NoParity");
    }
    ScaleParity = settings.value("SCALEPARITY").toString() ;
    if ( settings.contains( "SCALESTOPBITS") == false)
    {
        settings.setValue("SCALESTOPBITS", "OneStop");
    }
    ScaleStopBits = settings.value("SCALESTOPBITS").toString() ;
    if ( settings.contains( "TAXINPRICE") == false )
    {
        settings.setValue( "TAXINPRICE" , "false"); // para usa es false
    }
    taxInPrice = settings.value( "TAXINPRICE").toString() ;
    if ( settings.contains( "SCALEREMLEFT") == false )
    {
        settings.setValue( "SCALEREMLEFT" , ""); // para usa es false
    }
    ScaleRemLeft = settings.value( "SCALEREMLEFT").toString() ;
    if ( settings.contains( "SCALEREMRIGHT") == false )
    {
        settings.setValue( "SCALEREMRIGHT" , ""); // para usa es false
    }
    ScaleRemRight = settings.value( "SCALEREMRIGHT").toString() ;
    if ( settings.contains( "SCALEREQUEST") == false )
    {
        settings.setValue( "SCALEREQUEST" , ""); // para usa es false
    }
    ScaleRequest = settings.value( "SCALEREQUEST").toString() ;

    if ( settings.contains( "TRAINING") == false)
    {
        settings.setValue("TRAINING", "FALSE");
    }
    Training = settings.value("TRAINING").toString() ;
    if ( settings.contains( "UPDATEPOS") == false)
    {
        settings.setValue("UPDATEPOS", "FALSE");
    }
    UpdatePos = settings.value("UPDATEPOS").toString() ;
    if ( settings.contains( "user") == false )
    {
        settings.setValue( "user" , "root"); // Para mexico
    }
    user = settings.value( "user").toString() ;
    if ( settings.contains( "VERSION") == false)
    {
        settings.setValue("VERSION", "1.002.002");
    }
    VersionPos = settings.value("VERSION").toString() ;
    if ( settings.contains( "WEBSERVICES") == false )
    {
        settings.setValue( "WEBSERVICES" , "/EJBWebServicev2_0/EJBWebServicev2_0" ); // Es la extension del Webservices que atiende al pos.
    }
    webServices = settings.value( "WEBSERVICES" ).toString()  ;
    if ( settings.contains( "WEBSERVICESSYNC") == false )
    {
        settings.setValue( "WEBSERVICESSYNC" , "/EJBWebServicev2_0/EJBWebServicev2_0" );
    }
    webServicesSync = settings.value( "WEBSERVICESSYNC" ).toString()  ;
    if ( settings.contains( "WEBSERVICESTH1") == false )
    {
        settings.setValue( "WEBSERVICESTH1" , "/VentaCorteWS/VentaCorteWS" ); // Es el nombre del webserver qiue atiende venta y cortez
    }
    webServicesTH1 = settings.value( "WEBSERVICESTH1" ).toString()  ;
    if ( settings.contains( "WINDOWWIDTH") == false )
    {
        settings.setValue( "WINDOWWIDTH" , 1024 ); // Es el contador de maximas lineas
    }
    windowWidth = settings.value( "WINDOWWIDTH" ).toInt()  ;

}

QString Settings::getBackDbName()
{
    return backDbName ;
}
QString Settings::getBackPassword()
{
    return backPassword ;
}
QString Settings::getBackUser()
{
    return backUser ;
}
QString Settings::getBtnHome()
{
    return btnHome;
}
void Settings::setBusinessDay(QString wDC_DY_BSN)
{
    if(wDC_DY_BSN.length()==10) wDC_DY_BSN = wDC_DY_BSN + " 00:00:00";
    wDC_DY_BSN.replace(QString("/"),QString("-"));
    wDC_DY_BSN.replace(QString("T"),QString(" "));
    DC_DY_BSN = QDateTime::fromString(wDC_DY_BSN, "yyyy-MM-dd hh:mm:ss");
}
QString Settings::getDbName()
{
    return dbName ;
}
QString Settings::getDesglosaImpuestos()
{
    return desglosaImpuestos;
}

void Settings::setDesglosaImpuestos(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "DESGLOSAIMPUESTOS" , value);
    desglosaImpuestos = value;
}

void Settings::setDebug(bool wdebug){
    QSettings settings(  "CORE" , "POSMOBILE") ;
    QString value;

    if (wdebug) value = "TRUE";
    else value = "FALSE";
    settings.setValue("DEBUG", value);
    debug = wdebug;
}

bool Settings::getFullscreen(){
    return fullcreen;
}

void Settings::setSessionTime(QString wTS_TM_STR)
{
    if(wTS_TM_STR.length()==10) wTS_TM_STR = wTS_TM_STR + " 00:00:00";
    wTS_TM_STR.replace(QString("/"),QString("-"));
    wTS_TM_STR.replace(QString("T"),QString(" "));
    Ts_Tm_Str=QDateTime::fromString(wTS_TM_STR, "yyyy-MM-dd hh:mm:ss");
}
QString Settings::getHasVirtualWindow()
{
    return hasVirtualWindow ;
}
void    Settings::setHasVirtualWindow(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    hasVirtualWindow = value;
    settings.setValue("HASVIRTUALWINDOW", value);
}
QString Settings::getIdInstancia()
{
    return idInstancia ;
}
void Settings::setIdOpr(int widOpr)
{
    idOpr = widOpr;
}

void    Settings::setIdStore(QString value)
{

    QSettings settings(  "CORE" , "POSMOBILE") ;
    idStore = value;
    settings.setValue( "IDSTORE" , value);
}

QString Settings::getIdStore()
{
    return idStore ;
}
QString Settings::getIdWorkStation()
{
    return idWorkStation ;
}
void    Settings::setIdWorkStation(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    idWorkStation = value;
    settings.setValue( "IDWORKSTATION" , value);
}

void Settings::setImpuestoPOrig(QString value){
    QSettings settings(  "CORE" , "POSMOBILE") ;
    ImpuestoPOrig = value;
    settings.setValue( "IMPUESTOPORIG" , value);
}

void Settings::setIdInstancia(QString value){
    QSettings settings(  "CORE" , "POSMOBILE") ;
    idInstancia = value;
    settings.setValue( "IDINSTANCIA" , value);

}

QString Settings::getIsNew()
{

    QSettings settings(  "CORE" , "POSMOBILE") ;

    if ( settings.contains( "ISNEW") == false )
    {
        settings.setValue( "ISNEW" , "N");
    }
    return settings.value( "ISNEW").toString() ;
}
void    Settings::setIsNew( QString value)
{

    QSettings settings(  "CORE" , "POSMOBILE") ;

    settings.setValue( "ISNEW" , value );
}
QString Settings::getLineMax()
{
    QSettings settings(  "CORE" , "POSMOBILE") ;


    if ( settings.contains( "LINEMAX") == false )
    {
        settings.setValue( "LINEMAX" , 0 ); // Es el contador de maximas lineas
    }
    lineMax = QString::number( settings.value( "LINEMAX").toInt() ) ;

    return lineMax ;

}
void    Settings::setNewLineMax(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "LINEMAX" , value.toInt() ); // Es el contador de maximas lineas
    lineMax = QString::number( settings.value( "LINEMAX").toInt() ) ;
}
QString Settings::getPassword()
{
    return password ;
}

void Settings::setScale(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALE" , value );
    Scale = value;
}

void Settings::setScalePort(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEPORT" , value );
    ScalePort = value;
}

void Settings::setScaleBaudRate(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEBAUDRATE" , value );
    ScaleBaudRate = value;
}

void Settings::setScaleDataBits(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEDATABITS" , value );
    ScaleDataBits = value;
}

void Settings::setScaleFlowControl(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEFLOWCONTROL" , value );
    ScaleFlowControl = value;
}

void Settings::setScaleParity(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEPARITY" , value );
    ScaleParity = value;
}

void Settings::setScaleStopBits(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALESTOPBITS" , value );
    ScaleStopBits = value;
}

void Settings::setScaleRemLeft(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEREMLEFT" , value );
    ScaleRemLeft = value;
}

void Settings::setScaleRemRight(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEREMRIGHT" , value );
    ScaleRemRight = value;
}

void Settings::setScaleRequest(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "SCALEREQUEST" , value );
    ScaleRequest = value;
}

QString Settings::getSerie()
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(interface.flags() & QNetworkInterface::IsLoopBack))
            return interface.hardwareAddress();
    }
    return QString();
}
QString Settings::getTaxInPrice()
{
    return taxInPrice ;
}
void    Settings::setTaxInPrice(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;

    settings.setValue( "TAXINPRICE" , value); // Es el contador de maximas lineas
    taxInPrice = value;
}

void Settings::setTraining(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "TRAINING" , value );
    Training = value;
}

QString Settings::getUser()
{
    return user ;
}
QString Settings::getWebAccess()
{
    return "https://" + host + ":" + QString::number( port ) + webServices ;
}

QString Settings::getWebCambioPass ()
{
    return "https://" + host + ":" + QString::number( port ) + "/WebBackofficeV2/faces/CambioPass.xhtml" ;
}

int     Settings::getWindowWidth()
{
    return windowWidth ;
}
QString Settings::getWebAccessSync()
{
    return "https://" + host + ":" + QString::number( port ) + webServicesSync ;
}
QString Settings::getWebAccessTH1()
{
    return "https://" + host + ":" + QString::number( port ) + webServicesTH1 ;
}

void Settings::setCountry(QString value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue( "COUNTRY" , value );
}

QSerialPort::BaudRate Settings::getScaleBaudRate()
{
    QSerialPort::BaudRate retorno;
    QString v;
    v= getScaleBaudRatetxt();
    if(v == "Baud1200")
        retorno = QSerialPort::Baud1200;
    else if (v == "Baud2400")
        retorno = QSerialPort::Baud2400;
    else if (v == "Baud4800")
        retorno = QSerialPort::Baud4800;
    else if (v == "Baud9600")
        retorno = QSerialPort::Baud9600;
    else if (v == "Baud19200")
        retorno = QSerialPort::Baud19200;
    else if (v == "Baud48400")
        retorno = QSerialPort::Baud38400;
    else if (v == "Baud57600")
        retorno = QSerialPort::Baud57600;
    else if (v == "Baud115200")
        retorno = QSerialPort::Baud115200;
    return retorno;
}

QSerialPort::DataBits Settings::getScaleDataBits()
{
    QSerialPort::DataBits resultado;
    QString v;
    v = getScaleDataBits();
    if(v == "Data5")
        resultado = QSerialPort::Data5;
    else if(v == "Data6")
        resultado = QSerialPort::Data6;
    else if(v == "Data7")
        resultado = QSerialPort::Data7;
    else if (v == "Data8")
        resultado = QSerialPort::Data8;
    return resultado;
}

QSerialPort::FlowControl Settings::getScaleFlowControl()
{
    QSerialPort::FlowControl resultado;
    QString v;
    v = getScaleFlowControl();
    if(v == "NoFlowControl")
        resultado = QSerialPort::NoFlowControl;
    else if(v == "HardwareControl")
        resultado = QSerialPort::HardwareControl;
    else if(v == "SoftwareControl")
        resultado = QSerialPort::SoftwareControl;
    return resultado;
}

QSerialPort::Parity Settings::getScaleParity()
{
    QSerialPort::Parity resultado;
    QString v;
    v = getScaleParitytxt();
    if (v=="NoParity")
        resultado = QSerialPort::NoParity;
    else if (v == "EvenParity")
        resultado = QSerialPort::EvenParity;
    else if (v== "OddParity")
        resultado = QSerialPort::OddParity;
    else if (v=="SpaceParity")
        resultado = QSerialPort::SpaceParity;
    else if (v=="MarkParity")
        resultado = QSerialPort::MarkParity;
    return resultado;
}

QSerialPort::StopBits Settings::getScaleStopBits()
{
    QSerialPort::StopBits resultado;
    QString v;
    v = getScaleStopBitstxt();
    if (v=="OneStop")
        resultado = QSerialPort::OneStop;
    else if (v == "OneAndHalfStop")
        resultado = QSerialPort::OneAndHalfStop;
    else if (v == "TwoStop")
        resultado = QSerialPort::TwoStop;
    return resultado;
}

void Settings::setBloqued_Time(bool bloquea)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    if (bloquea)
    {
        settings.setValue("BLOQUED_TIME", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    }
    else
    {
        settings.setValue("BLOQUED_TIME", "1900-01-01 00:00:00");
    }
}

QString Settings::getBloqued_Time()
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    return settings.value( "BLOQUED_TIME").toString();
}

void Settings::setNoIntentos(int value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    settings.setValue("NO_INTENTOS", value);
}

int Settings::getNoIntentos()
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    qDebug() << "Settings.cpp " << settings.value( "NO_INTENTOS").toInt();
    return settings.value( "NO_INTENTOS").toInt();
}

void Settings::set_habilita_Alta(bool value)
{
    QSettings settings(  "CORE" , "POSMOBILE") ;
    if (value){
        settings.setValue("HABILITA_ALTA","TRUE");
    }
    else{
        settings.setValue("HABILITA_ALTA","FALSE");
    }
}

bool Settings::get_habilita_Alta()
{
    return habilita_Alta;
}
