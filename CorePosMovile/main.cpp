#include <QApplication>
#include <FelgoApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QComboBox>
#include <qcombobox.h>
#include "websocket_syncronizacion.h"
#include "principal.h"
// uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
//#include <FelgoLiveClient>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    FelgoApplication felgo;

    // Use platform-specific fonts instead of Felgo's default font
    felgo.setPreservePlatformFonts(true);

    QQmlApplicationEngine engine;
    felgo.initialize(&engine);

    // Set an optional license key from project file
    // This does not work if using Felgo Live, only for Felgo Cloud Builds and local builds
    felgo.setLicenseKey(PRODUCT_LICENSE_KEY);

    // use this during development
    // for PUBLISHING, use the entry point below
    felgo.setMainQmlFileName(QStringLiteral("qml/Main.qml"));

    // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
    // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
    // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
    // also see the .pro file for more details
    //felgo.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));
    //inicializacion de objetos en c++ añadidos
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
        sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
        QSslConfiguration::setDefaultConfiguration(sslConf);

    websocket_syncronizacion* client= new websocket_syncronizacion(QUrl(QStringLiteral("wss://localhost:8080/WebBackofficeV2/actualizacion")), true);
    client->iniciar(QUrl(QStringLiteral("wss://localhost:8080/WebBackofficeV2/confirmacion")));
    //client->iniciar2(QUrl(QStringLiteral("wss://localhost:8080/WebBackofficeV2/endpoint")));
    //client->base_de_datos();
    //client->insertar();
    //client->select();
   // client->get_tender()
    engine.rootContext()->setContextProperty("coneccion", client);
    principal* princi=new principal(1);
    engine.rootContext()->setContextProperty("funciones", princi);
    engine.load(QUrl(felgo.mainQmlFileName()));

    // to start your project as Live Client, comment (remove) the lines "felgo.setMainQmlFileName ..." & "engine.load ...",
    // and uncomment the line below
    //FelgoLiveClient client (&engine);

    return app.exec();
}
