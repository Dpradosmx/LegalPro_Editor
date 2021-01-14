import Felgo 3.0
import QtQuick 2.0
import "pages"
import "helper"
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0
import QtGraphicalEffects 1.0




App {

    //Pasos
    //primero hace una comparacion, pues guarda la instancia y  la  tienda  de manera global
    //si ya hay una instancia inicia con normalidad, busca impuestos, busca categorias, botones y login
    //si no hay instancia, y si no es la primera vez que se abre la aplicacion, crea la base de datos,
    //y abre la seccion de instalacion
    //si es nuevo, pide datos y  manda una solicitud para un codigo
    //si es para una tienda, pide  el usuario y solo hay que dar de alta usuario y password, pide codigo
    //al introducir el codigo se manda validar y si es correcto inicia el proceso de instalacion nuevo o Para
    //una tienda, al terminar el proceso, manda un mensaje donde ya quedan guardadas en el cel la instancia  y la tienda

    id:principal
    //secciones de la zona de registro
    property bool registroN: false
    property bool usuario: true;//botones de usuario nuevo o viejo
    property bool login:false;//login de usuario existente
    property bool datos: false;//datos  para llenar si es usuario nuevo
    property bool codigo: false;//zona para poner el codigo de nueva instalacion
    property bool datos2:false;//zona de datos necesarios cuando ya existe una instalacion
    //fin de la zona de registro
    //seccion de la zona del login
    property bool olvidocontraseña:false;//cambia a olvido contraseña
    //fin de la zona del login
    property int mesaSeleccionada:0;//mesa seleccionada
    property var modelo1:[
        {"capacidad": 4,  "ocupados":0, "idMesa":11,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."},
        {"capacidad": 4,  "ocupados":0, "idMesa":12,"status":1,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":13,"status":2,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit...."},
        {"capacidad": 4,  "ocupados":0, "idMesa":14,"status":3,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":15,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":16,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":17,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":18,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":19,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."}
        ];

    property var modelo2:[
        {"capacidad": 4,  "ocupados":0, "idMesa":11,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."},
        {"capacidad": 4,  "ocupados":0, "idMesa":12,"status":1,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":13,"status":2,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit...."},
        {"capacidad": 4,  "ocupados":0, "idMesa":14,"status":3,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":15,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":16,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":17,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":18,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":19,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."}
        ];
    property var modelo3:[
        {"capacidad": 4,  "ocupados":0, "idMesa":21,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."},
        {"capacidad": 4,  "ocupados":0, "idMesa":22,"status":1,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":23,"status":2,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit...."},
        {"capacidad": 4,  "ocupados":0, "idMesa":24,"status":3,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":25,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":26,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":27,"status":4,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit..."},
        {"capacidad": 4,  "ocupados":0, "idMesa":28,"status":5,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit."},
        {"capacidad": 4,  "ocupados":0, "idMesa":29,"status":0,"texto":"Suspendisse pellentesque urna et justo malesuada interdum. Morbi fermentum fermentum urna vestibulum pretium. Mauris sit amet tristique velit. Morbi faucibus dignissim turpis at pharetra. Maecenas eu augue velit.."}
];
    property var modelocat:[];
    property var modelotick:[];
    property int listaSeleccionada:0;
    property int estadoSeleccionada: 0;
    property bool visiblemesas:false;
    property real progresss: 0.0//progreso de actualizacion

    //busquedas y descripcion de lineas
    property bool visibleDescripcio: false
    property bool visibleCategorias: false
    property bool visibleBusqueda: false
    property bool visibleVenta: false
    property int numeroArtEncontrados: 0
    property var cantidadArtIngresados:0.0
    property var categoriaActual: ""
    property var visibleMenuDespegable1:false
    property bool visibleAlta: false
    property bool visible_visor:false
    //tickets
    property bool visibleTarjeta: false
    property bool visibleCheque:false
    property int ticketIndice:0
    //venta por default se usa cash, efectivo
    property var tySeleccionado: "CASH"
    property bool consolasql:false;

    property var impuesttos : [] ;
    property var cattegorias: [];
    FontLoader {
         id: geoFont
         source: "../assets/GeoSlab.ttf" // loaded from your assets folder
         //font.pixelSize: sp(20)
       }

    onInitTheme: {
        Theme.navigationBar.backgroundColor="#4a576c";
      Theme.normalFont=geoFont;
        Theme.navigationBar.defaultIconSize=dp(23);


       }

    Component.onCompleted:{

           var isFirstStartApplication = principal.settings.getValue("instancia")
           //principal.settings.setValue("instancia",87)
           console.debug("instancia "+isFirstStartApplication);
           if(isFirstStartApplication === undefined||isFirstStartApplication === 0) {
             //funcion que crea las tablas
               console.log("No hay instancia aun")
               if(principal.settings.getValue("numberAppStarts")===undefined)
                coneccion.base_de_datos()
               registroN=true;
               principal.settings.setValue("numberAppStarts", 1)
               coneccion.iniciar2("wss://localhost:8080/WebBackofficeV2/endpoint");
           }
           else{
                console.log("Iniciando variables")

               //botonesCategorias1.xml=funciones.buttonsRoot()
               //botonesCategorias1.xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado>"
               botonesCategorias1.xml=  "<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10005</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>CHORIZO CHICANO 1 PZ /4LB</NM_BTN><DE_BTN>CHORIZO CHICANO 1 PZ /4LB</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>CHORCHICP</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10002</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>CHORIZO CHICANO CAJA 10/4LB</NM_BTN><DE_BTN>CHORIZO CHICANO CAJA 10/4LB</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>CHORCHICA</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10000</ID_BTN><ID_BTN_PRNT></ID_BTN_PRNT><TY_BTN>RO</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>Chorizos</NM_BTN><DE_BTN>Chorizos</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS></ID_ITM_PS><ID_ITM_PS_QFR></ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10004</ID_BTN><ID_BTN_PRNT>10003</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>MILAN QUESO PUERCO GRANDE</NM_BTN><DE_BTN>MILAN QUESO PUERCO GRANDE</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>QUESMILANP</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10003</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>AG</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>Otros</NM_BTN><DE_BTN>Otros</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS></ID_ITM_PS><ID_ITM_PS_QFR></ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig></return></GETButtonConfigWResponse></Body></Envelope>";
               botonesCategorias2.xml=  "<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10005</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>CHORIZO CHICANO 1 PZ /4LB</NM_BTN><DE_BTN>CHORIZO CHICANO 1 PZ /4LB</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>CHORCHICP</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10002</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>CHORIZO CHICANO CAJA 10/4LB</NM_BTN><DE_BTN>CHORIZO CHICANO CAJA 10/4LB</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>CHORCHICA</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10000</ID_BTN><ID_BTN_PRNT></ID_BTN_PRNT><TY_BTN>RO</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>Chorizos</NM_BTN><DE_BTN>Chorizos</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS></ID_ITM_PS><ID_ITM_PS_QFR></ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10004</ID_BTN><ID_BTN_PRNT>10003</ID_BTN_PRNT><TY_BTN>PR</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>MILAN QUESO PUERCO GRANDE</NM_BTN><DE_BTN>MILAN QUESO PUERCO GRANDE</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS>QUESMILANP</ID_ITM_PS><ID_ITM_PS_QFR>1</ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig><buttonconfig><ID_STR_RT>1</ID_STR_RT><ID_BTNSET>1</ID_BTNSET><ID_BTN>10003</ID_BTN><ID_BTN_PRNT>10000</ID_BTN_PRNT><TY_BTN>AG</TY_BTN><BTN_WT>1</BTN_WT><NM_BTN>Otros</NM_BTN><DE_BTN>Otros</DE_BTN><PIC/><ICON_ADDRESS/><ID_STRGRP>1</ID_STRGRP><ID_ITM_PS></ID_ITM_PS><ID_ITM_PS_QFR></ID_ITM_PS_QFR><POSITION>0</POSITION></buttonconfig></return></GETButtonConfigWResponse></Body></Envelope>";
               //botonesTender.xml=coneccion.get_tender();
               botonesTender.xml="<?xml version='1.0' encoding='UTF-8'?><Envelope xmlns:S='http://schemas.xmlsoap.org/soap/envelope/'><Body><GETButtonConfigWResponse xmlns:ns2='http://Webmet.core/'><return><resultado><resultado>1</resultado><resultadoMsg>ok</resultadoMsg></resultado><buttonconfig><ID_STR_RT>CCAR</ID_STR_RT><ID_BTNSET>CARD</ID_BTNSET></buttonconfig><buttonconfig><ID_STR_RT>CASH</ID_STR_RT><ID_BTNSET>CASH</ID_BTNSET></buttonconfig><buttonconfig><ID_STR_RT>CHEC</ID_STR_RT><ID_BTNSET>CHEC</ID_BTNSET></buttonconfig><buttonconfig><ID_STR_RT>FDST</ID_STR_RT><ID_BTNSET>Food Stamp</ID_BTNSET></buttonconfig></return></GETButtonConfigWResponse></Body></Envelope>";
               categoriasgenerales.xml=funciones.get_categorias("");
               impuestosgenerales.xml=funciones.get_taxs();
               console.log("Syncronizacion");
               //lleva una N para ser remplazada por la linea actual
               //coneccion.send_message("N,"+principal.settings.getValue("tienda")+","+principal.settings.getValue("instancia")+",x",0);//primera vez
               coneccion.run_hilo_actualizador();
               //coneccion.insertar();
           }
           //pruebas
           //coneccion.iniciar2("wss://localhost:8080/WebBackofficeV2/endpoint");
           //registroN=true;
        }



    NavigationStack {

        Page {
            id:page
            title: qsTr("Principal")
            //backgroundColor: "aliceblue"
            backgroundColor: "white"
            useSafeArea: false // do not consider safe area insets of screen
            property bool loginvisible: true


            Rectangle{
                id:galeriaimagenes
                color:"white" //#82bee3"
                //border.color: "black";
                width:page.width/1.5
                x:dp(20)
                height: page.height/1.5
                z:1
                visible:visible_visor
                //visible:true
                border.color:"grey"
                anchors.centerIn: parent
                layer.enabled: true
                            layer.effect: DropShadow {
                                transparentBorder: true
                                horizontalOffset: 1
                                verticalOffset: 1
                            }

                property var sourse: ""
                property int valor: 0
                property variant listaimagenes:[]
                MouseArea{
                    anchors.fill: parent
                            onClicked: {
                                parent.valor=parent.valor+1;
                                if(parent.valor==parent.listaimagenes.length){
                                    parent.valor=0;
                                }
                                parent.sourse=parent.listaimagenes[parent.valor];
                            }
                }
                AppActivityIndicator {
                    width: parent.width/3
                    //x: dp(20)
                    height: parent.width/3
                    anchors.centerIn: parent
                    //fillMode: Image.PreserveAspectFit
                    //autoTransform: true
                    //source: "../assets/l.gif"

                }
                AppImage {
                           id: resultImage
                           width: parent.width-dp(40)
                           x: dp(20)
                           height: parent.height-dp(30)
                           fillMode: Image.PreserveAspectFit
                           autoTransform: true
                           source: parent.sourse
                           //anchors.leftMargin: dp(10)
                           layer.enabled: true
                                       layer.effect: DropShadow {
                                           transparentBorder: true
                                           horizontalOffset: 1
                                           verticalOffset: 1
                                       }

                         }
                AppButton {


                  flat: false
                  fontCapitalization: Font.MixedCase
                  backgroundColor: "#4a576c"
                  backgroundColorPressed: "#d6d6d6"
                  borderColor: "white"
                  fontBold: false
                        text:"Cerrar"
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: resultImage.horizontalCenter
                        onClicked: visible_visor=false
                }
                ListModel {
                   id: modeloimagenes
                }
            }

            Rectangle {

              anchors.bottom: galeriaimagenes.top
              anchors.left: galeriaimagenes.left
              color: "#4a576c"
              width: galeriaimagenes.width
              height: ingresog.height + dp(16)
              radius: dp(4)
              visible:visible_visor
              //visible: true
              border.color: "grey"
               z:1
               layer.enabled: true
                           layer.effect: DropShadow {
                               transparentBorder: true
                               horizontalOffset: 1
                               verticalOffset: 1
                           }

              AppText {
                id:ingresog
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: dp(10)
                //fontSize: sp(0)
                text: "Imagenes"
                color: "white"
              }
            }
                /*
            AppText {
              id: myText
              text: "mesa"
              anchors.horizontalCenter: parent.horizontalCenter
              anchors.top: parent.top

            }

            Column {
                id: progresion
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: myText.bottom
                visible:  !page.loginvisible
                //coneccion.progreso_actualizacion !==0 &&
                ProgressBar {
                    value: coneccion.progreso_actualizacion;
                }
                //ProgressBar {
                  //  indeterminate: true
                //}
            }
*/

            //seccion de mesas
               JsonListModel {
                   id: jsonModel1
                   source: modelo1
                   keyField: "idMesa"
                   fields: ["idMesa", "capacidad", "ocupados","status","texto"]
                 }
               AppListView {
                 id: listaMesas
                 x: dp(10) // left margin
                 //y: dp(10) // top margin
                 spacing: dp(2)//90
                 anchors.top: parent.top
                 anchors.topMargin: dp(10)
                 backgroundColor: "white"
                 //width: dp(560)
                 width: parent.width/3
                 height: parent.height-dp(60)
                 visible:principal.visiblemesas;
                 model: jsonModel1
                z:1
               delegate: Row {
                id:delegadoMesa
                spacing: dp(60)

                Rectangle{
                    id:fondocol
                    color:model.idMesa===mesaSeleccionada ? "grey":
                           index%2===0 ? "white":
                                         "#82bee3"

                    border.color: "grey"
                    //width: dp(560)
                    width:listaMesas.width
                    height: dp(90)
                    MouseArea{
                        anchors.fill: parent
                                onClicked: {
                                     //console.log("Clicked Item #"+model.idMesa+": "+JSON.stringify(model))
                                    console.log("Clicked Item #"+model.idMesa)
                                    if(model.idMesa===mesaSeleccionada){
                                        mesaSeleccionada=0;
                                        listaSeleccionada=0;
                                        estadoSeleccionada=0;
                                    }
                                    else{
                                        mesaSeleccionada=model.idMesa;
                                        listaSeleccionada=1;
                                        estadoSeleccionada=model.status;
                                    }
                                }
                    }

                    Rectangle{
                        id:col
                        width: dp(75)
                        height: dp(75)
                        color: "white"
                        border.color: "black"
                        x:5
                        y:5

                        Column{
                                            id:coll
                                            width: dp(80)

                                            //anchors.left: tecto.right
                                            anchors.horizontalCenter: col.horizontalCenter
                                            Rectangle {
                                              id: rec
                                              color: "white"
                                              border.color: "gray"
                                              width: dp(30)
                                              height: dp(30)
                                              radius: dp(15)
                                              anchors.horizontalCenter: parent.horizontalCenter
                                              anchors.top:parent.top
                                              anchors.topMargin: dp(10)
                                            }
                                            Rectangle{
                                                id:cir
                                                width: dp(30)
                                                height: dp(30)
                                                radius: dp(15)
                                                anchors.centerIn: rec
                                                color: model.status===0 ? "white":
                                                       model.status===1 ? "blue" :
                                                       model.status===2 ? "lightgreen" :
                                                       model.status===3 ? "red" :
                                                       model.status===4 ? "grey" :
                                                       model.status===5 ? "yellow" :
                                                       "white"
                                                border.color: "black"
                                            }
                                            AppText{
                                                id:comensales
                                                anchors.centerIn: cir
                                                text:model.status===0 ? model.capacidad :
                                                     model.ocupados
                                            }
                                            AppText{
                                             id:mesaText
                                             anchors.top: rec.bottom
                                             anchors.horizontalCenter: rec.horizontalCenter
                                             text: "Mesa " +model.idMesa
                                            }
                                        }
                    }

                    AppText{
                                        id:tt
                                        text:model.texto
                                        anchors.left: col.right
                                        anchors.leftMargin: dp(10)
                                        y:dp(5)
                                        //anchors.verticalCenter: parent.verticalCenter
                                        //width:dp(450)
                                        maximumLineCount: 4
                                        width:listaMesas.width-dp(85)
                                    }

                }


              }

               }

               JsonListModel {
                      id: jsonModel2
                      source: modelo2
                      keyField: "idMesa"
                      fields: ["idMesa", "capacidad", "ocupados","status","texto"]
                    }
               AppListView {
                 id: listaMesas2
                 x: dp(10) // left margin
                 //y: dp(10) // top margin
                 spacing: dp(2)//90
                 anchors.top: parent.top
                 anchors.topMargin: dp(10)
                 backgroundColor: "white"
                 anchors.left: listaMesas.right
                 //width: dp(560)
                 width: parent.width/3
                 height: parent.height-dp(60)
                 visible:principal.visiblemesas;


                 model: jsonModel2

                 z:1
                delegate: Row {
                 id:delegadoMesa2
                 spacing: dp(60)

                 Rectangle{
                     id:fondocol2
                     color:model.idMesa===mesaSeleccionada ? "grey":
                            index%2===0 ? "white":
                                          "#82bee3"

                     border.color: "grey"
                     //width: dp(560)
                     width:listaMesas.width
                     height: dp(90)
                     MouseArea{
                         anchors.fill: parent
                                 onClicked: {
                                      //console.log("Clicked Item #"+model.idMesa+": "+JSON.stringify(model))
                                     console.log("Clicked Item #"+model.idMesa)
                                     if(model.idMesa===mesaSeleccionada){
                                         mesaSeleccionada=0;
                                         listaSeleccionada=0;
                                         estadoSeleccionada=0;
                                     }
                                     else{
                                         mesaSeleccionada=model.idMesa;
                                         listaSeleccionada=1;
                                         estadoSeleccionada=model.status;
                                     }
                                 }
                     }

                     Rectangle{
                         id:col2
                         width: dp(75)
                         height: dp(75)
                         color: "white"
                         border.color: "black"
                         x:5
                         y:5

                         Column{
                                             id:coll2
                                             width: dp(80)

                                             //anchors.left: tecto.right
                                             anchors.horizontalCenter: col2.horizontalCenter
                                             Rectangle {
                                               id: rec2
                                               color: "white"
                                               border.color: "gray"
                                               width: dp(30)
                                               height: dp(30)
                                               radius: dp(15)
                                               anchors.horizontalCenter: parent.horizontalCenter
                                               anchors.top:parent.top
                                               anchors.topMargin: dp(10)
                                             }
                                             Rectangle{
                                                 id:cir2
                                                 width: dp(30)
                                                 height: dp(30)
                                                 radius: dp(15)
                                                 anchors.centerIn: rec2
                                                 color: model.status===0 ? "white":
                                                        model.status===1 ? "blue" :
                                                        model.status===2 ? "lightgreen" :
                                                        model.status===3 ? "red" :
                                                        model.status===4 ? "grey" :
                                                        model.status===5 ? "yellow" :
                                                        "white"
                                                 border.color: "black"
                                             }
                                             AppText{
                                                 id:comensales2
                                                 anchors.centerIn: cir2
                                                 text:model.status===0 ? model.capacidad :
                                                      model.ocupados
                                             }
                                             AppText{
                                              id:mesaText2
                                              anchors.top: rec2.bottom
                                              anchors.horizontalCenter: rec2.horizontalCenter
                                              text: "Mesa " +model.idMesa
                                             }
                                         }
                     }

                     AppText{
                                         id:tt2
                                         text:model.texto
                                         anchors.left: col2.right
                                         anchors.leftMargin: dp(10)
                                         y:dp(5)
                                         //anchors.verticalCenter: parent.verticalCenter
                                         //width:dp(450)
                                         maximumLineCount: 4
                                         width:listaMesas.width-dp(85)
                                     }

                 }


               }

               }

               JsonListModel {
                      id: jsonModel3
                      source: modelo3
                      keyField: "idMesa"
                      fields: ["idMesa", "capacidad", "ocupados","status","texto"]
                    }
               AppListView {
                 id: listaMesas3
                 x: dp(10) // left margin
                 //y: dp(10) // top margin
                 spacing: dp(2)//90
                 anchors.top: parent.top
                 anchors.topMargin: dp(10)
                 backgroundColor: "white"
                 anchors.left: listaMesas2.right
                 //width: dp(560)
                 width: parent.width/3
                 height: parent.height-dp(60)
                 visible:principal.visiblemesas;
                 model: jsonModel3


                 z:1
                delegate: Row {
                 id:delegadoMesa3
                 spacing: dp(60)

                 Rectangle{
                     id:fondocol3
                     color:model.idMesa===mesaSeleccionada ? "grey":
                            index%2===0 ? "white":
                                          "#82bee3"

                     border.color: "grey"
                     //width: dp(560)
                     width:listaMesas.width
                     height: dp(90)
                     MouseArea{
                         anchors.fill: parent
                                 onClicked: {
                                      //console.log("Clicked Item #"+model.idMesa+": "+JSON.stringify(model))
                                     console.log("Clicked Item #"+model.idMesa)
                                     if(model.idMesa===mesaSeleccionada){
                                         mesaSeleccionada=0;
                                         listaSeleccionada=0;
                                         estadoSeleccionada=0;
                                     }
                                     else{
                                         mesaSeleccionada=model.idMesa;
                                         listaSeleccionada=1;
                                         estadoSeleccionada=model.status;
                                     }
                                 }
                     }

                     Rectangle{
                         id:col3
                         width: dp(75)
                         height: dp(75)
                         color: "white"
                         border.color: "black"
                         x:5
                         y:5

                         Column{
                                             id:coll3
                                             width: dp(80)

                                             //anchors.left: tecto.right
                                             anchors.horizontalCenter: col3.horizontalCenter
                                             Rectangle {
                                               id: rec3
                                               color: "white"
                                               border.color: "gray"
                                               width: dp(30)
                                               height: dp(30)
                                               radius: dp(15)
                                               anchors.horizontalCenter: parent.horizontalCenter
                                               anchors.top:parent.top
                                               anchors.topMargin: dp(10)
                                             }
                                             Rectangle{
                                                 id:cir3
                                                 width: dp(30)
                                                 height: dp(30)
                                                 radius: dp(15)
                                                 anchors.centerIn: rec3
                                                 color: model.status===0 ? "white":
                                                        model.status===1 ? "blue" :
                                                        model.status===2 ? "lightgreen" :
                                                        model.status===3 ? "red" :
                                                        model.status===4 ? "grey" :
                                                        model.status===5 ? "yellow" :
                                                        "white"
                                                 border.color: "black"
                                             }
                                             AppText{
                                                 id:comensales3
                                                 anchors.centerIn: cir3
                                                 text:model.status===0 ? model.capacidad :
                                                      model.ocupados
                                             }
                                             AppText{
                                              id:mesaText3
                                              anchors.top: rec3.bottom
                                              anchors.horizontalCenter: rec3.horizontalCenter
                                              text: "Mesa " +model.idMesa
                                             }
                                         }
                     }

                     AppText{
                                         id:tt3
                                         text:model.texto
                                         anchors.left: col3.right
                                         anchors.leftMargin: dp(10)
                                         y:dp(5)
                                         //anchors.verticalCenter: parent.verticalCenter
                                         //width:dp(450)
                                         maximumLineCount: 4
                                         width:listaMesas.width-dp(85)
                                     }

                 }


               }

               }

               AppButton {
                   id:separarMesa
                 text: qsTr("Separar mesa")
                 flat: false
                 backgroundColor: "#4a576c"
                 backgroundColorPressed: "#d6d6d6"
                 anchors.right: juntarMesa.left
                 anchors.bottom: parent.bottom
                 fontBold: false
                 //fontFamily: geoFont
                 fontCapitalization: Font.MixedCase
                 visible:principal.visiblemesas;
                 onClicked: {

                 }//if onclicked
               }
               AppButton {
                   id:juntarMesa
                 text: qsTr("Juntar mesa")
                 flat: false
                 backgroundColor: "#4a576c"
                 backgroundColorPressed: "#d6d6d6"
                 anchors.right: limpiarMesa.left
                 anchors.bottom: parent.bottom
                 //fontFamily: geoFont
                 fontCapitalization: Font.MixedCase
                 fontBold: false
                 visible:principal.visiblemesas;
                 onClicked: {

                 }//if onclicked
               }
               AppButton {
                   id:limpiarMesa
                 text: qsTr("Limpiar mesa")
                 flat: false
                 backgroundColor: "#4A576C"
                 backgroundColorPressed: "#d6d6d6"
                 anchors.right: cerrarMesa.left
                 anchors.bottom: parent.bottom
                 fontBold: false
                 //fontFamily: geoFont
                 fontCapitalization: Font.MixedCase
                 visible:principal.visiblemesas;
                 onClicked: {
                 if(mesaSeleccionada>0&&estadoSeleccionada>0){
                     if(listaSeleccionada===1){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo1) ,3);
                 }
                     if(listaSeleccionada===2){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo2) ,3);
                 }
                     if(listaSeleccionada===3){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo3) ,3);
                 }
                 }
                 else{
                     NativeDialog.confirm("Error", "No hay mesa seleccionada o ya esta abierta", function(ok) {
                         if(ok) {

                         }
                       })
                 }
                     }//if onclicked
               }
               AppButton {
                   id:cerrarMesa
                 text: qsTr("Cerrar mesa")
                 flat: false
                 fontBold: false
                 backgroundColor: "#4A576C"
                 backgroundColorPressed: "#d6d6d6"
                 anchors.right: abrirMesa.left
                 anchors.bottom: parent.bottom
                 //fontFamily: geoFont
                 fontCapitalization: Font.MixedCase
                 visible:principal.visiblemesas;
                 onClicked: {
                 if(mesaSeleccionada>0&&estadoSeleccionada!=0){
                     if(listaSeleccionada===1){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo1) ,0);
                 }
                     if(listaSeleccionada===2){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo2) ,0);
                 }
                     if(listaSeleccionada===3){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo3) ,0);
                 }
                 }
                 else{
                     NativeDialog.confirm("Error", "No hay mesa seleccionada o ya esta cerrada", function(ok) {
                         if(ok) {

                         }
                       })
                 }
                     }//if onclicked
               }
               AppButton {
                   id:abrirMesa
                 text: qsTr("Abrir mesa")
                 flat: false
                 fontBold: false
                 backgroundColor: "#4A576C"
                 backgroundColorPressed: "#d6d6d6"
                 anchors.bottom: parent.bottom
                 anchors.right: parent.right

                 fontCapitalization: Font.MixedCase
                 visible:principal.visiblemesas;
                 onClicked: {
                 if(mesaSeleccionada>0&&estadoSeleccionada==0){
                     if(listaSeleccionada===1){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo1) ,1);
                 }
                     if(listaSeleccionada===2){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo2) ,1);
                 }
                     if(listaSeleccionada===3){
                  funciones.estado_Mesa(listaSeleccionada,mesaSeleccionada,JSON.stringify(modelo3) ,1);
                 }
                 }
                 else{
                     NativeDialog.confirm("Error", "No hay mesa seleccionada o ya esta abierta", function(ok) {
                         if(ok) {

                         }
                       })
                 }
                     }//if onclicked
               }

               //fin seccion de mesas
                 //seccion pantalla inicial

               Rectangle{
                    id:fondoblock
                    width: parent.width
                    height: parent.height
                    z:1
                    visible: page.loginvisible
                    //visible:false;
                    Image {
                        id: logo
                        source: "../assets/logo.png"
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.margins: dp(30)
                        width:dp(320)
                        height: dp(85)
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                consolasql= consolasql ? false:true;
                            }
                        }
                    }

                    Rectangle{
                      id:rojo
                      anchors.left: logo.right
                      anchors.top: parent.top
                      anchors.topMargin: dp(85)
                      anchors.leftMargin: dp(10)

                      color: "#FD070C"
                      height: dp(10)
                      width: parent.width -dp(500)

                    }

                    Rectangle{
                      id:azul
                      anchors.right: parent.right
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: dp(80)
                      color: "#265596"
                      height: dp(10)
                      width: parent.width -dp(330)

                    }

                    //seccion login inicial

                      Rectangle {
                        id: loginForm
                        anchors.centerIn: parent
                        color: "#d6d6d6"
                        width: content.width + dp(48)
                        height: content.height + dp(80)//16
                        radius: dp(4)
                        visible: !registroN
                        border.color: "black"
                        // login form content
                        GridLayout {
                            id: content
                            anchors.centerIn: parent
                            columnSpacing: dp(20)
                            rowSpacing: dp(10)
                            columns: 2
                            // headline


                            // email text and field
                            AppText {
                              text: qsTr("Usuario")
                              font.pixelSize: sp(12)

                              //fontFamily: geoFont
                            }

                            AppTextField {
                              id: txtUsername
                              Layout.preferredWidth: dp(200)
                              showClearButton: true
                              font.pixelSize: sp(14)
                              backgroundColor: "white";

                              borderColor: Theme.tintColor
                              borderWidth: dp(2)
                            }

                            // password text and field
                            AppText {
                                id:txtPasswordl
                              text: qsTr("Contraseña")
                              font.pixelSize: sp(12)

                              //fontFamily: geoFont
                            }

                            AppTextField {
                              id: txtPassword
                              Layout.preferredWidth: dp(200)
                              showClearButton: true
                              font.pixelSize: sp(14)
                              backgroundColor: "white"
                              borderColor: Theme.tintColor
                              borderWidth:  dp(2)
                              echoMode: TextInput.Password
                            }

                            // column for buttons, we use column here to avoid additional spacing between buttons
                            Column {
                              Layout.fillWidth: true
                              Layout.columnSpan: 2
                              Layout.topMargin: dp(12)

                              // buttons
                              AppButton {
                                  id:logbuton
                                text: "Ingreso"
                                flat: false
                                fontCapitalization: Font.MixedCase
                                backgroundColor: "#4a576c"
                                backgroundColorPressed: "#d6d6d6"
                                anchors.horizontalCenter: parent.horizontalCenter
                                fontBold: false
                                //fontFamily: geoFont
                                onClicked: {
                                  page.forceActiveFocus() // move focus away from text fields
                                  if(olvidocontraseña){//if true manda llamar nueva contraseña
                                     console.log("Mandando que se olvido la contreña")
                                  }
                                  else{//sige el proceso login
                                      // call login action
                                      //logic.login(txtUsername.text, txtPassword.text)


                                      var loginresult=funciones.login(txtUsername.text,txtPassword.text,false);
                                      if(loginresult.indexOf("<resultado>1</resultado>")>0){
                                       // if(txtUsername.text==="usuarion"){
                                       page.loginvisible=false;
                                       page.backgroundColor="aliceblue";
                                          mensajes.tipoM=1;
                                          mt.text="Sesion iniciada";
                                          mostrarTexto.start();
                                          funciones.init_principal();
                                         coneccion.init_websocket();
                                        }
                                        else{
                                         NativeDialog.confirm("Error", "Contraseña incorrecta", function(ok) {
                                             if(ok) {

                                             }
                                           })
                                        }
                                  }
                                }//if onclicked
                              }
                              AppButton{
                              id:olvidolog
                              text:"¿Olvidó su contraseña?"
                              flat: false
                              backgroundColor: "#d6d6d6"
                              backgroundColorPressed: "#d6d6d6"
                              textColor: "black"
                              dropShadow: false
                              textSize: dp(12)
                              //fontFamily: geoFont
                              fontBold: false
                              fontCapitalization: Font.MixedCase
                              anchors.horizontalCenter: logbuton.horizontalCenter
                              horizontalPadding: dp(0)
                              onClicked: {
                                 if(olvidocontraseña){
                                     olvidolog.text="¿Olvidó su contraseña?";
                                     txtPasswordl.visible=true;
                                     txtPassword.visible=true;
                                     txtUsernamel.text="Usuario";
                                     ingreso.text="Ingreso";
                                     olvidocontraseña=false;
                                     logbuton.text="Ingreso";
                                 }
                                 else{
                                     olvidolog.text="Atras";
                                     logbuton.text="Obtén nuevo password";
                                     txtPasswordl.visible=false;
                                     txtPassword.visible=false;
                                     txtUsernamel.text="Email";
                                     ingreso.text="Password olvidado";
                                     olvidocontraseña=true;
                                 }
                              }
                              }
                             }
                          }


                      }

                      Rectangle {
                        id: loginFormh
                        anchors.bottom: loginForm.top
                        anchors.left: loginForm.left
                        color: "#4a576c"
                        width: loginForm.width
                        height: ingreso.height + dp(16)
                        radius: dp(4)
                        visible: !registroN
                        border.color: "black"

                        AppText {
                          id:ingreso
                          anchors.verticalCenter: parent.verticalCenter
                          anchors.left: parent.left
                          anchors.leftMargin: dp(10)
                          //fontSize: sp(0)
                          text: "Ingreso"
                          color: "white"
                        }
                      }

                      //fin de zona login


                      // zona nuevo registro
                         Rectangle {
                           id: loginForm2
                           anchors.centerIn: parent
                           color: "#d6d6d6"
                           width: content2.width + dp(48)
                           height: content2.height + dp(80)//16
                           radius: dp(4)
                           visible:registroN
                           border.color: "black"
                           // login form content
                           GridLayout {
                               id: content2
                               anchors.centerIn: parent
                               columnSpacing: dp(20)
                               rowSpacing: dp(10)
                               columns: 2


                                //inicio, usuario nuevo o ya existente
                               AppButton{
                                     id:nuevou
                                     text: "¿Usuario nuevo?"
                                     visible: usuario
                                     onClicked:{
                                         usuario=false;
                                         datos=true;
                                         login=false;
                                         codigo=false;
                                         datos2=false;
                                         ingresof.text="Todos los datos son necesarios.";
                                     }

                                     }

                               AppButton{
                                         id:nuevoy

                                     text: "¿Usuario ya registrado?"
                                     visible: usuario
                                     onClicked:{
                                         usuario=false;
                                         datos=false;
                                         login=true;
                                         codigo=false;
                                         datos2=false;
                                         ingresof.text="Usuario ya registrado";
                                     }

                                     }

                               AppButton{
                                         id:yacodi
                                     Layout.columnSpan: 2
                                     text: "ya tengo un codigo"
                                     visible: usuario && principal.settings.getValue("instalacionpendiente")!==undefined
                                     onClicked:{
                                         usuario=false;
                                         datos=false;
                                         login=false;
                                         codigo=true;
                                         datos2=false;
                                         ingresof.text="El código tiene caducidad, también debe de haber pasado el proceso de creación nuevo o ya registrado al menos una vez.";
                                     }

                                     }

                               //ya existente 2
                               AppText {
                                 text: qsTr("Usuario")
                                 font.pixelSize: sp(12)
                                 visible:login
                                 //fontFamily: geoFont
                               }

                               AppTextField {
                                       id: usuariol
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:login
                                       placeholderText: "Usuario ya registrado"

                                     }

                               AppText {
                                 text: qsTr("Password")
                                 font.pixelSize: sp(12)
                                 visible:login
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: passwordl
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:login
                                       placeholderText: "Contraseña"

                                     }

                               Column {
                                 Layout.fillWidth: true
                                 Layout.columnSpan: 2
                                 Layout.topMargin: dp(12)
                                 visible:login
                               AppButton{
                                         id:aceptarl
                                     text: "Aceptar login"
                                     //visible: login
                                     onClicked: {
                                         //datos, L login, N nuevo codigo, C confirmar, usuario, password, codigo,email,celular,url
                                         console.log("aceptar log");
                                         coneccion.send_message_log_conf("L,"+usuariol.text+","+passwordl.text+",codigo,email,celular,url");
                                         //activa onloginf
                                         /*usuario=false;
                                         datos=false;
                                         login=false;
                                         codigo=true;*/
                                         aceptarl.enabled=false;
                                         ingresof.text="Procesando";
                                     }
                                     //anchors.horizontalCenter: parent.horizontalCenter
                                       //      anchors.top: passwordl.bottom
                                     }
                               AppButton{
                                         id:cancelar
                                     text: "Cancelar"
                                     //visible: login
                                     onClicked: {
                                         usuario=true;
                                         datos=false;
                                         login=false;
                                         codigo=false;
                                         datos2=false;
                                         principal.settings.setValue("instancia", 0);
                                         ingresof.text="Bienvenido, ¿usted es un usuario completamente nuevo o ya tiene un usuario y una contraseña? Si ya tiene un código puede introducirlo ahora.";
                                     }
                                     //anchors.horizontalCenter: parent.horizontalCenter
                                       //      anchors.top: aceptarl.bottom
                                     }
                               }
                               //ya existente 2

                               //usuario ya existente 3
                               AppText {
                                 text: qsTr("Usuario")
                                 font.pixelSize: sp(12)
                                 visible:datos2
                                 //fontFamily: geoFont
                               }

                               AppTextField {
                                       id: usuariod2
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos2
                                       placeholderText: "Usuario"

                                     }

                               AppText {
                                 text: qsTr("Password")
                                 font.pixelSize: sp(12)
                                 visible:datos2
                                 //fontFamily: geoFont
                               }

                               AppTextField {
                                       id: passwordd2
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos2
                                       placeholderText: "Password"

                                     }

                               AppText {
                                 text: qsTr("E-mail")
                                 font.pixelSize: sp(12)
                                 visible:datos2
                                 //fontFamily: geoFont
                               }

                               AppTextField {
                                       id: emaild2
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos2
                                       placeholderText: "Correo electronico"

                                     }

                               AppButton{
                                     id:aceptard2
                                     text: "Aceptar datos2"
                                     visible: datos2
                                     Layout.fillWidth: true
                                     Layout.columnSpan: 2
                                     Layout.topMargin: dp(12)

                                     onClicked: {
                                         //datos, si es nuevo, usuario, password, instancia, rfc,nombretienda, encabezadotienda,id_tienda
                                         console.log("aceptar log");
                                         coneccion.send_message_log_conf("N,"+usuariod2.text+","+passwordd2.text+",0,"+emaild2.text+",felo3443,url");
                                         principal.settings.setValue("instalacionpendiente", "U,"+usuariod2.text+","+passwordd2.text+","+principal.settings.getValue("instancia")+",n,n,n,"+principal.settings.getValue("tienda"));
                                         usuario=false;
                                         datos=false;
                                         login=false;
                                         codigo=true;
                                         datos2=false;
                                         onClicked: NativeDialog.confirm("Confirmado", "Pronto recibira  un correo con un codigo de confirmacion", function(ok) {
                                             if(ok) {}
                                           })
                                     }

                                     }

                               //usuario ya existente 3

                               //ususario ya existente 4, usuario nuevo 3
                               AppText {
                                 text: qsTr("Codigo")
                                 font.pixelSize: sp(12)
                                 visible:codigo
                                 //fontFamily: geoFont
                               }

                               AppTextField {
                                       id: codigoc
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:codigo
                                       placeholderText: "Codigo"
                                       //anchors.horizontalCenter: parent.horizontalCenter
                                       //anchors.top: parent.top
                                     }
                               Column {
                                 Layout.fillWidth: true
                                 Layout.columnSpan: 2
                                 Layout.topMargin: dp(12)
                                 visible: codigo
                               AppButton{
                                         id:aceptarc
                                     text: "Aceptar codigo"
                                     //visible: codigo
                                     onClicked: {
                                         coneccion.send_message_log_conf("C,usuario,password,"+codigoc.text+",email,felo3443,url");
                                         usuario=true;
                                         datos=false;
                                         login=false;
                                         codigo=false;
                                         datos2=false;
                                         page.loginvisible=true;
                                         registroN=false;

                                     }
                                     //anchors.horizontalCenter: parent.horizontalCenter
                                     //anchors.top: codigoc.bottom
                                     }
                               AppButton{
                                         id:cancelarc
                                     text: "Cancelar"
                                     //visible: codigo
                                     onClicked: {
                                         usuario=true;
                                         datos=false;
                                         login=false;
                                         codigo=false;
                                         datos2=false;
                                         principal.settings.setValue("instancia", 0);
                                     }
                                     //anchors.horizontalCenter: parent.horizontalCenter
                                     //        anchors.top: aceptarc.bottom
                                     }
                               }
                               //ususario ya  existente 4, codigo 1

                               //usuario nuevo 2
                               AppText {
                                 text: qsTr("Usuario")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: usuarioCampo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Usuario"

                                     }
                               AppText {
                                 text: qsTr("Password")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: passwordCampo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "password"
                                     }
                               AppText {
                                 text: qsTr("E-mail")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: correoCampo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Correo"

                                     }

                               AppText {
                                 text: qsTr("Datos de la tienda")
                                 font.pixelSize: sp(18)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppText {
                                 text: qsTr("")
                                 font.pixelSize: sp(18)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppText {
                                 text: qsTr("Nombre")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: tiendaCampo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Nombre tienda"
                                     }
                               AppText {
                                 text: qsTr("RFC")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: rfcCampo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "RFC"
                                     }
                               AppText {
                                 text: qsTr("Encabezado tiquet")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: enc1Campo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Encabezado tiquet"
                                     }
                               AppText {
                                 text: qsTr("Subtitulo tiquet")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: enc2Campo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Subtitulo tiquet"
                                     }
                               AppText {
                                 text: qsTr("Pie de tiquet")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: pie1Campo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Pie  de  tiquet 1"
                                     }
                               AppText {
                                 text: qsTr("Pie de tiquet 2")
                                 font.pixelSize: sp(12)
                                 visible:datos
                                 //fontFamily: geoFont
                               }
                               AppTextField {
                                       id: pie2Campo
                                       Layout.preferredWidth: dp(200)
                                       showClearButton: true
                                       font.pixelSize: sp(14)
                                       backgroundColor: "white";

                                       borderColor: Theme.tintColor
                                       borderWidth: dp(2)
                                       visible:datos
                                       placeholderText: "Pie  de  tiquet 2"
                                     }
                               AppButton{

                                   icon: IconType.check
                                   text: "aceptar"
                                   visible: datos
                                   Layout.fillWidth: true
                                   Layout.columnSpan: 2
                                   Layout.topMargin: dp(12)
                                   onClicked: NativeDialog.confirm("Confirmar", "¿Subir datos?", function(ok) {
                                       if(ok) {
                                           //solicita un codigo nuevo N
                                           coneccion.send_message_log_conf("N,"+usuarioCampo.text+","+passwordCampo.text+",0,"+correoCampo.text+",felo3443,url");
                                           principal.settings.setValue("instalacionpendiente", "N,"+usuarioCampo.text+","+passwordCampo.text+",0,"+rfcCampo.text+","+tiendaCampo.text+","+enc2Campo.text+"/"+pie1Campo.text+"/"+pie2Campo.text+",1");
                                           console.debug("instalacion pendiente "+principal.settings.getValue("instalacionpendiente"));
                                           usuario=false;
                                           datos=false;
                                           login=false;
                                           codigo=true;
                                           datos2=false;
                                           onClicked: NativeDialog.confirm("Confirmado", "Pronto recibira  un correo con un codigo de confirmacion", function(ok) {
                                               if(ok) {}
                                             })
                                           ingresof.text=""
                                       }
                                       else{
                                           usuario=true;
                                           datos=false;
                                           login=false;
                                           codigo=false;
                                           datos2=false;
                                           ingresof.text="Bienvenido, ¿usted es un usuario completamente nuevo o ya tiene un usuario y una contraseña? Si ya tiene un código puede introducirlo ahora."
                                       }
                                     })
                               }


                               //usuario nuevo 2

                           }


                         }

                         Rectangle {
                           id: loginFormh2
                           anchors.bottom: loginForm2.top
                           anchors.left: loginForm2.left
                           color: "#4a576c"
                           width: loginForm2.width
                           height: ingreso2.height + dp(16)
                           radius: dp(4)
                           visible: registroN
                           border.color: "black"

                           AppText {
                             id:ingreso2
                             anchors.verticalCenter: parent.verticalCenter
                             anchors.left: parent.left
                             anchors.leftMargin: dp(10)
                             //fontSize: sp(0)
                             text: "Registro"
                             color: "white"
                           }
                         }

                         Rectangle{
                             id: loginFormf
                             anchors.top: loginForm2.bottom
                             anchors.left: loginForm2.left
                             color: "gray"
                             width: loginForm2.width
                             height: ingresof.height + dp(16)
                             radius: dp(4)
                             visible: registroN
                             border.color: "black"

                             AppText {
                               id:ingresof
                               anchors.verticalCenter: parent.verticalCenter
                               anchors.left: parent.left
                               anchors.leftMargin: dp(10)
                               width: loginForm2.width-dp(20)
                               //fontSize: sp(0)
                               text: "Bienvenido, ¿usted es un usuario completamente nuevo o ya tiene un usuario y una contraseña? Si ya tiene un código puede introducirlo ahora."
                               color: "white"

                             }
                         }

                         //fin zona registro
                  }

               Rectangle{
                width: parent.width/3
                height: parent.height/3
                anchors.right: parent.right
                anchors.top: parent.top
                visible: consolasql
                color: "gray"
                z:1
                Column{

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top

                    AppTextField {
                      id: sql
                      //Layout.preferredWidth: dp(200)
                      showClearButton: true
                      font.pixelSize: sp(14)
                      backgroundColor: "white";

                      borderColor: Theme.tintColor
                      borderWidth: dp(2)
                    }
                    AppButton{
                        text: "SELECTs"
                        onClicked: {
                        coneccion.selectquery(sql.text);
                        }
                    }
                    AppButton{
                        text: "UPDATESs"
                        onClicked: {
                        coneccion.updatequery(sql.text);
                        }
                    }
                }
               }

                //fin fondo
                //ticket

                  ListModel {
                     id: myModelt
                  }
                  AppListView {
                       id: listaTicket
                       x: dp(10) // left margin
                       //y: dp(10) // top margin
                       spacing: dp(2)//90
                       anchors.top: parent.top
                       anchors.topMargin: dp(10)
                       backgroundColor: "white"
                       //width: dp(560)
                       width: parent.width/2
                       height: parent.height
                       model:myModelt
                       //model: jsonModelTicket

                     delegate: Row {
                      id:delegadoTicket
                      spacing: dp(60)

                      Rectangle{
                          id:fondotick
                          color:
                                 index%2===0 ? "white":
                                               "#82bee3"

                          border.color: "grey"
                          //width: dp(560)
                          width:listaTicket.width
                          height: dp(90)
                          MouseArea{
                              anchors.fill: parent
                                      onClicked: {
                                           //console.log("Clicked Item #"+model.idMesa+": "+JSON.stringify(model))
                                          console.log("Clicked Item #"+textName)
                                          ticketIndice=index;
                                          //pone los datos dela linea en la descripcion
                                          datosCM.text="Linea: "+lx.text
                                          d1.text=textQuantity;
                                          d2.text=textName;
                                          d2.iditmps=textid_itm_ps;
                                          d2.iditmpsqfr=textid_itm_ps_qfr;
                                          d3.text=cambios;
                                          d3e.text=cambios;
                                          t1.text=textPrice;
                                          t1e.text=textPrice;
                                          t2.text=textTotal;
                                          var lista=imagenes.split(",");
                                          //console.debug("al darle clic imagenes tiene "+imagenes +" "+imagenes.length);
                                          //console.debug("al darle clic imagenes2 tiene "+lista +" "+lista.length);
                                          galeriaimagenes.listaimagenes=lista;
                                          galeriaimagenes.valor=0;
                                          galeriaimagenes.sourse=galeriaimagenes.listaimagenes[0];
                                          visible_visor=true;

                                              visibleDescripcio=true;
                                              visibleBusqueda=false;
                                              visibleCategorias=false;
                                              visibleVenta=false;
                                              page.edicionlvisible=false;

                                      }
                          }

                          AppText{
                          id:lx
                          text:index+1
                          anchors.left: fondotick.left
                          anchors.leftMargin: dp(5)
                          anchors.top:fondotick.top
                          color: isCanceled ? "red" : "black"
                          }
                          AppText{
                          id:l1
                          text:textQuantity
                          anchors.left: fondotick.left
                          anchors.top:fondotick.top
                          color: isCanceled ? "red" : "black"
                          anchors.leftMargin: dp(10)
                          anchors.topMargin: dp(10)
                          }
                          AppText{
                          id:l2
                          text:textName
                          anchors.left: l1.right
                          anchors.top:fondotick.top
                          maximumLineCount: 2
                          anchors.leftMargin: dp(10)
                          anchors.topMargin: dp(10)
                          }

                          AppText{
                          id:l3
                          text:cambios
                          anchors.left: l2.left
                          anchors.top:l1.bottom

                          anchors.leftMargin: dp(10)
                          anchors.topMargin: dp(10)
                          //anchors.right:t1.left
                          }


                          AppText{
                          id:l4
                          text:textPrice
                          anchors.right: l5.left
                          anchors.top:fondotick.top
                          color: isCanceled ? "red" : "black"
                          anchors.rightMargin: dp(10)
                          anchors.topMargin: dp(10)
                          }

                          AppText{
                          id:l5
                          text:textTotal
                          anchors.right: fondotick.right
                          anchors.top:fondotick.top
                          color: isCanceled ? "red" : "black"
                          anchors.rightMargin: dp(10)
                          anchors.topMargin: dp(10)
                          }


                      }
                    }

                     }

                Rectangle{
                    id:totalf
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.topMargin: dp(10)
                    anchors.rightMargin: dp(10)
                    color: "#265596"
                    height: dp(60)
                    width: (parent.width/2) -dp(30)
                    border.color: "grey"

                    AppText{
                        id:totalText
                        text:"Total"
                        color: "white"
                        fontSize: sp(50)
                        anchors.top:parent.top
                        anchors.right: parent.right
                        anchors.topMargin: dp(10)
                        //anchors.rightMargin: dp(10)
                        anchors.rightMargin: parent.width/3
                    }

                    AppText{
                        id:totalticketText
                        text:"0.00"
                        color: "white"
                        fontSize: sp(50)
                        anchors.top:parent.top
                        anchors.right: parent.right
                        //anchors.rightMargin: parent.width/4
                        //width: parent.width/3
                        anchors.rightMargin: dp(10)
                        anchors.topMargin: dp(10)

                    }

                    MouseArea{
                        anchors.fill:  parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: {
                            principal.visibleBusqueda=false;
                            principal.visibleCategorias=false;
                            principal.visibleDescripcio=false;
                            principal.visibleVenta=true;
                        }

                    }

                    layer.enabled: true
                                layer.effect: DropShadow {
                                    transparentBorder: true
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                }
                }

                //seccion fondo principal
                Rectangle{
                    id:lineaDescripcion
                    anchors.right: parent.right
                    anchors.top: totalf.bottom
                    anchors.bottom: mensajes.top
                    anchors.bottomMargin: dp(10)
                    anchors.topMargin: dp(10)
                    anchors.rightMargin: dp(10)
                    color: "grey"
                    height: dp(60)
                    width: (parent.width/2) -dp(30)
                    border.color: "grey"
                    layer.enabled: true
                                layer.effect: DropShadow {
                                    transparentBorder: true
                                    horizontalOffset: 1
                                    verticalOffset: 1
                                }

                }
                //fin seccion fondo principal
                //seccion de mensajes
                Rectangle{
                id:mensajes
                anchors.left: lineaDescripcion.left
                anchors.right: parent.right
                anchors.rightMargin: dp(10)
                anchors.bottom: botonBuscar.top
                property var tipoM: 2
                //1 correcto
                //2 error
                width: dp(400)
                height: dp(80)
                color: "#265596"


                AppText{
                    id:iconText
                    text:"Mensajes"
                    anchors.top: parent.top
                    //anchors.topMargin: dp(5)
                    anchors.left: parent.left
                    anchors.leftMargin: dp(10)
                    color:"white"
                }
                Icon {
                    id:iconMensaje
                       icon:mensajes.tipoM===1? IconType.checkcircle :
                                                IconType.ban
                       size:dp(50)
                       color:"white"
                       anchors.top:iconText.bottom
                       //anchors.topMargin: dp(10)
                       anchors.left: parent.left
                       anchors.leftMargin: dp(25)
                        opacity: 0
                       visible: opacity != 0

                      Behavior on opacity {
                                NumberAnimation { duration: 500 }
                              }
                     }

                AppText{
                    id:mt
                    anchors.top:parent.top
                    anchors.topMargin: dp(5)
                    anchors.left: iconMensaje.right
                    anchors.leftMargin: dp(10)
                    anchors.right: parent.right
                    anchors.rightMargin: dp(5)
                    color:"white"
                    font.pixelSize: sp(20)
                    maximumLineCount: 3
                    height: parent.height
                    text: "No se pueden hacer cambios en esta linea"
                    opacity: 0
                    visible: opacity != 0

                   Behavior on opacity {
                             NumberAnimation { duration: 500 }
                           }
                }


                }

                SequentialAnimation {
                         // You can start the whole animation by calling start() of the top-most item
                         id: mostrarTexto
                         ParallelAnimation {
                         NumberAnimation {
                                    target: mt
                                    property: "opacity"
                                    to: 1
                                    duration: 500
                                  }
                         NumberAnimation {
                                    target: iconMensaje
                                    property: "opacity"
                                    to: 1
                                    duration: 500
                                  }
                         }

                         ParallelAnimation {
                         NumberAnimation {
                                    target: mt
                                    property: "opacity"
                                    to: 0
                                    duration: 4000
                                  }
                         NumberAnimation {
                                    target: iconMensaje
                                    property: "opacity"
                                    to: 0
                                    duration: 4000
                                  }
                         }
                }
                //fin seccion de mensajes
                XmlListModel {
                    id: botonesTender
                    query: "/Envelope/Body/GETButtonConfigWResponse/return/buttonconfig"
                    XmlRole { name: "ID_STR_RT" ; query: "ID_STR_RT/string()" }
                    XmlRole { name: "ID_BTNSET" ; query: "ID_BTNSET/string()" }
                }
                GridView {
                    id:listaTender
                       anchors.top:lineaDescripcion.top
                       anchors.topMargin: dp(20)
                       height: lineaDescripcion.height
                       width:lineaDescripcion.width/5
                       anchors.left: lineaDescripcion.left
                       anchors.leftMargin: dp(10)
                       model: botonesTender
                       visible: visibleVenta
                       cellWidth:  dp(100)
                       cellHeight: dp(62)


                       Component {
                           id: contactsDelegatete
                           Rectangle {
                               id: wrapper
                               width:listaCategoriasPadres.width
                               height: dp(50)
                               radius : dp(6)
                               //color: GridView.isCurrentItem ? "black" : "green"
                               clip : true
                               color:"#265596"
                               property var ty_tnd:ID_STR_RT

                               Text {
                                   //id: contactInfo
                                   //id: contactInfo
                                   text: ID_BTNSET
                                   font.pointSize:  sp(10)
                                   font.bold:  true
                                   anchors.centerIn: parent
                                   //width: dp(130)
                                   width:parent.width
                                   maximumLineCount: 2
                                   horizontalAlignment: Text.AlignHCenter
                                   wrapMode: Text.WordWrap
                                   color: "white"
                               }

                               MouseArea{
                                   anchors.fill:  parent
                                   acceptedButtons: Qt.LeftButton | Qt.RightButton
                                   onClicked: {
                                       if(ID_BTNSET=="CARD"){
                                        visibleTarjeta=true;
                                        visibleCheque=false;

                                       }
                                       else if(ID_BTNSET=="CHEC"){
                                           visibleTarjeta=false;
                                           visibleCheque=true;

                                       }
                                       else{
                                           visibleTarjeta=false;
                                           visibleCheque=false;
                                       }
                                      tySeleccionado=ID_BTNSET;
                                      console.log("Seleccionado "+tySeleccionado);
                                   }

                               }
                           }
                       }

                       delegate: contactsDelegatete
                }

                Column{
                    id:todosTotalestext
                    width: lineaDescripcion.width/5-dp(10)
                    anchors.left: listaTender.right
                    anchors.leftMargin: lineaDescripcion.width/5
                    anchors.top:lineaDescripcion.top
                    anchors.topMargin: dp(20)
                    visible: visibleVenta
                    AppText{
                        anchors.left: parent.left
                        text: "Suma:"
                        color: "white"
                        fontSize: sp(30)
                    }
                    AppText{
                        anchors.left: parent.left
                        text: "Impuesto:"
                        color: "white"
                        fontSize: sp(30)
                    }
                    AppText{
                        anchors.left: parent.left
                        text: "Total:"
                        color: "white"
                        fontSize: sp(30)
                    }
                }
                Column{
                    id:todosTotales
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin: lineaDescripcion.width/5
                    width: lineaDescripcion.width/5-dp(10)
                    anchors.top:lineaDescripcion.top
                    anchors.topMargin: dp(20)
                    visible:visibleVenta
                    AppText{
                        id:sumat
                        anchors.right: parent.right
                        text: "0.00"
                        color: "white"
                        fontSize: sp(30)
                    }
                    AppText{
                        id:impuestost
                        anchors.right: parent.right
                        text: "0.00"
                        color: "white"
                        fontSize: sp(30)
                    }
                    AppText{
                        id:totalt
                        anchors.right: parent.right
                        text: "0.00"
                        color: "white"
                        fontSize: sp(30)
                    }

                }

                AppText{
                    id:montotext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: todosTotalestext.bottom
                    anchors.topMargin: dp(20)
                    text: "Monto"
                    color: "white"
                    fontSize: sp(30)
                    visible:visibleVenta
                }

                AppTextField{
                    id:montot
                    anchors.top: todosTotales.bottom
                    anchors.topMargin: dp(20)
                    anchors.left: montotext.right
                    anchors.leftMargin: dp(30)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin: dp(50)
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    visible:visibleVenta
                    placeholderText: "Monto pagado"
                    validator:  DoubleValidator {bottom: 0; top: 9999.99;}
                }

                AppText{
                    id:tipotext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: montot.bottom
                    anchors.topMargin: dp(5)
                    text: "Tipo:"
                    color: "white"
                    fontSize: sp(30)
                    visible:visibleTarjeta && visibleVenta ? true:false
                }


                ComboBox {
                    id:tipot
                    anchors.top: montot.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: tipotext.right
                    anchors.right: lineaDescripcion.right
                    anchors.leftMargin:dp(30)
                    anchors.rightMargin: lineaDescripcion.width/5
                    model: [ "Visa", "MasterCard", "Dinners" , "Amex" , "Otra"] ;
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppText{
                    id:numerottext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: tipot.bottom
                    anchors.topMargin: dp(5)
                    text: "Numero: "
                    color: "white"
                    fontSize: sp(30)
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppTextField{
                    id:numerott
                    anchors.top: tipot.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: numerottext.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin: dp(50)
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    //visible:visibleVenta
                    placeholderText: "Numero de tarjeta"
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppText{
                    id:reftext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: numerott.bottom
                    anchors.topMargin: dp(5)
                    text: "referencia: "
                    color: "white"
                    fontSize: sp(30)
                    //visible:visibleVenta
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppTextField{
                    id:reftt
                    anchors.top: numerott.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: reftext.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin:lineaDescripcion.width/5
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    //visible:visibleVenta
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppText{
                    id:vencimientotext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: reftt.bottom
                    anchors.topMargin: dp(5)
                    text: "Vencimiento(MM/AA): "
                    color: "white"
                    fontSize: sp(30)
                    //visible:visibleVenta
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppTextField{
                    id:vencimientot
                    anchors.top: reftt.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: vencimientotext.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin:lineaDescripcion.width/5
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    inputMask: "99/99"
                    visible:visibleTarjeta && visibleVenta ? true:false
                }

                AppText{
                    id:numeroittext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: montot.bottom
                    anchors.topMargin: dp(5)
                    text: "Identificacion: "
                    color: "white"
                    fontSize: sp(30)
                    //visible:visibleVenta
                    visible:visibleCheque && visibleVenta ? true:false
                }

                AppTextField{
                    id:numeritt
                    anchors.top: montot.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: numeroittext.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin: dp(50)
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    //visible:visibleVenta
                    placeholderText: "Numero de dentificacion"
                    visible:visibleCheque && visibleVenta ? true:false
                }

                AppText{
                    id:refitext
                    anchors.left: listaTender.right
                    anchors.leftMargin:  dp(50)
                    anchors.top: numeritt.bottom
                    anchors.topMargin: dp(5)
                    text: "Ref. cheque: "
                    color: "white"
                    fontSize: sp(30)
                    //visible:visibleVenta
                    visible:visibleVenta && visibleCheque ? true:false
                }

                AppTextField{
                    id:refitt
                    anchors.top: numeritt.bottom
                    anchors.topMargin: dp(5)
                    anchors.left: refitext.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin:lineaDescripcion.width/5
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    font.pixelSize: sp(15)
                    //visible:visibleVenta
                    visible:visibleVenta && visibleCheque ? true:false
                }

                //secccion venta
                Row{
                    spacing: dp(5)
                    anchors.horizontalCenter: lineaDescripcion.horizontalCenter
                    anchors.bottom: lineaDescripcion.bottom
                    AppButton{
                      id:ventaAceptar
                      icon: IconType.check
                      text: ""
                      minimumWidth: dp(80)
                      minimumHeight: dp(50)
                      //anchors.left: listaTender.right
                      //anchors.leftMargin:  lineaDescripcion.width/5
                      //anchors.bottom: lineaDescripcion.bottom
                      backgroundColor: "#4a576c"
                      visible:visibleVenta
                      onClicked: {
                          if(parseFloat(montot.text) >= 0)
                          {
                              var newObject = {} ;
                              //newObject.a_pagar = totalt.text;
                              newObject.a_pagar=totalticketText.text;
                              newObject.forma_de_pago=tySeleccionado;
                              newObject.monto=montot.text;
                              newObject.n_cheke=refitt.text;
                              newObject.id_cheke= refitt.text;
                              newObject.tipo_id=numeritt.text;
                              newObject.banco_cheke= numeritt.text;
                              newObject.tipo_targeta=tipot.currentText;
                              newObject.vencimiento_m=vencimientot.text.split()[0];
                              newObject.vencimiento_a=vencimientot.text.split()[1];
                              newObject.seguridad=reftt.text;
                              newObject.ty_tnd =tySeleccionado;

                              var resultado =funciones.validacion(newObject);

                              console.log("el resultado 1 "+resultado.resultado+resultado.cambio);
                              if(resultado.resultado === "true")
                              {

                                  var objeto_aceptar;
                                  if (parseFloat(resultado.cambio) > 0)
                                  {
                                      totalText.text="Cambio:";
                                      totalticketText.text=resultado.cambio
                                      visibleVenta=false;
                                      console.debug(" clicked cambio: "+resultado.cambio);
                                      mensajes.tipoM=1;
                                      mt.text=" clicked cambio: "+resultado.cambio;
                                      mostrarTexto.start();
                                      objeto_aceptar=funciones.do_pay(newObject);
                                      funciones.finish_ticket(0,{});//clientes
                                      myModelt.clear();
                                      sumat.text="0.00";//total_venta-value.total_impuesto;
                                      impuestost.text="0.00";
                                      totalt.text="0.00";
                                      totalText.text="Cambio";
                                      montot.text="";
                                  }
                                  else
                                  {
                                      objeto_aceptar=funciones.do_pay(newObject);
                                      //accept
                                      console.debug("despues el funciones do pay")
                                      //myDisplay.addLineDisplayPago(value);
                                      var value2;
                                      value2=funciones.put_change(objeto_aceptar);
                                      if(value2.respuesta===1){
                                          //myDisplay.addLineDisplay(value2);
                                          var myObject = new Object ;
                                          myObject.textCount = value2.ln ;
                                          myObject.textQuantity = value2.unitario ;
                                          myObject.textName = value2.titulo;
                                          myObject.textPrice = value2.precio_unitario ;
                                          //txtNmItem.text=value.titulo;
                                          //txtValueItem.text=myObject.textPrice;
                                          myObject.textTotal = value2.importe;
                                          sumat.text=value2.suma;//total_venta-value.total_impuesto;
                                          impuestost.text=value2.total_impuesto;
                                          totalt.text=value2.total_venta;
                                          //txtPagado.text=value.pagado;
                                          //txtAPagar.text=value.total_a_pagar;
                                          //txtAPagar1.text=value.total_a_pagar;
                                          totalticketText.text= value2.total_a_pagar;
                                          myObject.isCanceled = false ;
                                          myObject.isCancelation = value2.isCancelation ;
                                          myObject.FOOD_STAMP = value2.FOOD_STAMP ;
                                          myObject.QTY_ITM = value2.QTY_ITM; //
                                          myObject.pack = value2.pack ;
                                          myObject.canceled = false;
                                          myObject.cambios="";

                                          myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                                          funciones.finish_ticket(0,{});//clientes
                                          //myDisplay.clearLines2();
                                          myModelt.clear();
                                          sumat.text="0.00";//total_venta-value.total_impuesto;
                                          impuestost.text="0.00";
                                          totalt.text="0.00";
                                           montot.text="";
                                          totalText.text="Cambio";
                                          mensajes.tipoM=1;
                                          mt.text="Venta";
                                          mostrarTexto.start();

                                      }
                                      else{
                                          if(value2.respuesta===2){ //No hay cambio
                                              funciones.finish_ticket(0,{});//clientes
                                              myModelt.clear();
                                              //principal.onmyModeltChanged();
                                              sumat.text="0.00";//total_venta-value.total_impuesto;
                                              impuestost.text="0.00";
                                              totalt.text="0.00";
                                               montot.text="";
                                              totalticketText.text= 0.00;
                                              mensajes.tipoM=1;
                                              mt.text="Venta";
                                              mostrarTexto.start();

                                          }

                                          if(value2.respuesta===0){ //No hay cambio
                                              myObject = new Object ;
                                              myObject.textCount = objeto_aceptar.ln ;
                                              myObject.textQuantity = objeto_aceptar.unitario ;
                                              myObject.textName = objeto_aceptar.titulo;
                                              myObject.textPrice = objeto_aceptar.precio_unitario ;
                                              //txtNmItem.text=value.titulo;
                                              //txtValueItem.text=myObject.textPrice;
                                              myObject.textTotal = objeto_aceptar.importe;
                                              sumat.text=objeto_aceptar.suma;//total_venta-value.total_impuesto;
                                              impuestost.text=objeto_aceptar.total_impuesto;
                                              totalt.text=objeto_aceptar.total_venta;
                                              //txtPagado.text=value.pagado;
                                              //txtAPagar.text=value.total_a_pagar;
                                              //txtAPagar1.text=value.total_a_pagar;
                                              totalticketText.text= objeto_aceptar.total_a_pagar;
                                              montot.text="";
                                              myObject.isCanceled = false ;
                                              myObject.isCancelation =objeto_aceptar.isCancelation ;
                                              myObject.FOOD_STAMP = objeto_aceptar.FOOD_STAMP ;
                                              myObject.QTY_ITM = objeto_aceptar.QTY_ITM; //
                                              myObject.pack = objeto_aceptar.pack ;
                                              myObject.canceled = false;
                                              myObject.cambios="";
                                              myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                                              mensajes.tipoM=1;
                                              mt.text="Pago";
                                              mostrarTexto.start();


                                          }
                                      }
                                      return;
                                  }
                              }
                          }
                          else
                          {
                              //messageLoader.theText = "El monto de pago no puede vacio o cero" ;
                              //messageLoader.isOk = true ;
                              //messageLoader.source = "MessageBox.qml" ;
                              //textField1.text = "" ;
                              //return ;
                          }
                        }
                      }
                    AppButton{
                      id:ventaCancelar
                      icon: IconType.crosshairs
                      minimumWidth: dp(80)
                      minimumHeight: dp(50)
                      //anchors.right: lineaDescripcion.right
                      //anchors.rightMargin:lineaDescripcion.width/5
                      //anchors.bottom: lineaDescripcion.bottom
                      backgroundColor: "#4a576c"
                      visible:visibleVenta
                    }
                    }
                //fin seccion venta

                //descripcion linea
                property bool edicionlvisible: false
                AppButton{
                  id:lineaBorrar
                  icon: IconType.trash
                  text: ""
                  minimumWidth: dp(50)
                  minimumHeight: dp(50)
                  anchors.right: lineaDescripcion.right
                  anchors.top:lineaDescripcion.top
                  backgroundColor: "#4a576c"
                  visible:visibleDescripcio
                  onClicked: {
                      //supervisorPending = "cancelarLinea" ;
                      page.operacion_especial=7
                      var acceso=  funciones.check_permisos("1031")
                      if(acceso===0){
                      page.supervisorLogVisible=true;
                      }
                      else{
                          if ( ticketIndice < 0 )
                          {
                             // myDisplay.alerta(true, false, "No existe renglón seleccionado");
                              console.debug("No encontramos que cancelar") ;
                              return ;
                          }
                          var res ={};
                          console.debug("Antes de validar") ;
                          res=funciones.validaCancel(ticketIndice)

                          if(res.respuesta === 1)
                          {
                              console.debug("Antes de validado") ;
                              //loginSupervisor();
                              var value;
                              value=funciones.do_cancel(ticketIndice);
                              if (value.respuesta === 1){
                                  //addLine2(value);
                                  var myObject = new Object ;
                                  myObject.textCount = value.ln ;
                                  myObject.textQuantity = value.unitario ;
                                  myObject.textName = value.titulo;
                                  myObject.textPrice = value.precio_unitario ;
                                  //txtNmItem.text=value.titulo;
                                  //txtValueItem.text=myObject.textPrice;
                                  myObject.textTotal = value.importe;
                                  sumat.text="$"+ value.suma;//total_venta-value.total_impuesto;
                                  impuestost.text="$"+value.total_impuesto;
                                  totalt.text=value.total_venta;
                                  //txtPagado.text=value.pagado;
                                  //txtAPagar.text=value.total_a_pagar;
                                  //txtAPagar1.text=value.total_a_pagar;
                                  totalticketText.text= value.total_a_pagar;
                                  myObject.isCanceled = false ;
                                  myObject.isCancelation = value.isCancelation ;
                                  myObject.FOOD_STAMP = value.FOOD_STAMP ;
                                  myObject.QTY_ITM = value.QTY_ITM; //
                                  myObject.pack = value.pack ;
                                  myObject.canceled = false;
                                  myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                                  myModelt.remove(ticketIndice);
                                  value = funciones.getlinea(ticketIndice);
                                  myModelt.insert( ticketIndice, value);
                              }
                          }
                          else
                          {
                             console.debug("No se puede realizar la cancelación") ;
                          }
                          return;
                      }
                  }
                }
                AppButton{
                  id:lineaEditar
                  icon: IconType.pencil
                  minimumWidth: dp(50)
                  minimumHeight: dp(50)
                  anchors.right: lineaBorrar.left
                  anchors.top:lineaDescripcion.top
                  backgroundColor: "#4a576c"
                  visible:visibleDescripcio
                  onClicked: {
                      var myObject = new Object ;
                      page.operacion_especial=9;
                      var acceso=  funciones.check_permisos("1036")
                      if(acceso===0){
                          page.supervisorLogVisible=true;
                      }
                      else{
                          page.cambiopVisible=true;
                          preciotext.text=t1.text;
                          motivotext.text="";
                          observaciontext.text=d3.text;
                      }
                  }
                }

                Rectangle{
                    id:previewbusqueda
                 color:white
                 width: page.width/10
                 height: page.width/10
                 visible: visibleBusqueda
                 anchors.right: lineaDescripcion.left
                 anchors.top: lineaDescripcion.top
                 border.color: "gray"
                 anchors.rightMargin: dp(10)
                 layer.enabled: true
                             layer.effect: DropShadow {
                                 transparentBorder: true
                                 horizontalOffset: 1
                                 verticalOffset: 1
                             }
                 property var sourse: "../assets/default.png"
                 property int valor: 1
                 AppActivityIndicator {
                     width: parent.width-dp(15)
                     //x: dp(20)
                     height: parent.height-dp(15)
                     anchors.centerIn: parent
                     //fillMode: Image.PreserveAspectFit
                     //autoTransform: true
                     //source: "../assets/l.gif"

                 }
                 AppImage {
                            width: parent.width-dp(5)
                            //x: dp(20)
                            height: parent.height-dp(5)
                            anchors.centerIn: parent
                            fillMode: Image.PreserveAspectFit
                            autoTransform: true
                            source: parent.sourse

                          }
                }

                AppText{
                 id:datosCM
                 text: "Datos cliente o mesa"
                 anchors.right: lineaEditar.left
                 anchors.top: lineaDescripcion.top
                 anchors.left: lineaDescripcion.left
                 color: "white"
                 fontSize: sp(50)
                 anchors.leftMargin: dp(10)
                 anchors.topMargin: dp(10)
                 visible:visibleDescripcio
                }
                AppText{
                id:d1
                text:"1.00"
                anchors.left: lineaDescripcion.left
                anchors.top:lineaBorrar.bottom
                color:"white"
                anchors.leftMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio
                }
                AppText{
                id:d2
                text:"Descripcion"
                anchors.left: d1.right
                anchors.top:lineaBorrar.bottom
                color:"white"
                maximumLineCount: 2
                anchors.right: t1.left
                anchors.leftMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio
                property var iditmps: ""
                property var iditmpsqfr: ""
                }
                AppText{
                id:d3
                text:"cambios"
                anchors.left: d2.left
                anchors.top:d1.bottom
                color:"#692333"
                anchors.leftMargin: dp(10)
                anchors.topMargin: dp(20)
                //anchors.right:t1.left
                visible:visibleDescripcio&&!page.edicionlvisible
                }
                AppTextField{
                id:d3e
                text:"cambios"
                anchors.left: d2.left
                anchors.top:d1.bottom
                color:"#692333"
                anchors.leftMargin: dp(10)
                anchors.topMargin: dp(20)
                //anchors.right:t1.left
                visible:visibleDescripcio&&page.edicionlvisible
                showClearButton: true
                backgroundColor: "white"
                borderColor: Theme.tintColor
                borderWidth:  dp(2)

                }
                AppText{
                id:t1
                text:"10.00"
                anchors.right: t2.left
                anchors.top:lineaBorrar.bottom
                color:"#692333"
                anchors.rightMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio&&!page.edicionlvisible

                }
                AppTextField{
                id:t1e
                text:"10.00"
                anchors.right: t2.left
                anchors.top:lineaBorrar.bottom
                color:"#692333"
                anchors.rightMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio&&page.edicionlvisible
                showClearButton: true
                backgroundColor: "white"
                borderColor: Theme.tintColor
                borderWidth:  dp(2)
                }
                AppText{
                id:t2
                text:"10.00"
                anchors.right: t3.left
                anchors.top:lineaBorrar.bottom
                color:"white"
                anchors.rightMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio
                }
                AppText{
                id:t3
                text:"T0"
                anchors.right: lineaDescripcion.right
                anchors.top:lineaBorrar.bottom
                color:"white"
                anchors.rightMargin: dp(10)
                anchors.topMargin: dp(10)
                visible:visibleDescripcio
                }

                Image {
                    source: "../assets/felgo-logo.png"
                    width:dp(50)
                    height: dp(50)
                    anchors.horizontalCenter: lineaDescripcion.horizontalCenter
                    anchors.top: d3.bottom
                    visible:visibleDescripcio
                }
                Image {
                    id:descripcionLogo
                    source: "../assets/felgo-logo.png"
                    width:dp(50)
                    height: dp(50)
                    anchors.left: lineaDescripcion.left
                    anchors.bottom: lineaDescripcion.bottom
                    anchors.leftMargin: dp(30)
                    anchors.bottomMargin: dp(30)
                    visible:visibleDescripcio
                }
                AppText{
                    id:descripcionHF
                    text:"28/09/2020 16:14"
                    width: (lineaDescripcion.width/3)-dp(90)
                    anchors.left: descripcionLogo.right
                    anchors.bottom: lineaDescripcion.bottom
                    anchors.top:descripcionLogo.top
                    anchors.leftMargin: dp(10)
                    anchors.bottomMargin: dp(30)
                    color:"white"
                    fontSize: sp(50)
                    visible:visibleDescripcio
                }
                AppText{
                   id:descripcionDatos
                   text:"Tienda:Demo\nCaja:caja 1\nOperador:usuarion"
                   width: (lineaDescripcion.width/3)
                   anchors.right: lineaDescripcion.right
                   anchors.bottom: lineaDescripcion.bottom
                   anchors.rightMargin: dp(10)
                   anchors.bottomMargin: dp(30)
                   anchors.top: descripcionLogo.top
                   color:"white"
                   visible:visibleDescripcio
                }
                //fin descripcion linea
                //seccion categorias

                AppButton{
                  id:backCategoria
                  icon: IconType.angledoubleleft
                  text: ""
                  minimumWidth: dp(50)
                  minimumHeight: dp(50)
                  anchors.right: lineaDescripcion.right
                  anchors.top:lineaDescripcion.top
                  backgroundColor: "#4a576c"
                  visible: visibleCategorias
                  iconSize: dp(30)
                  onClicked: {
                      console.log("cat_act en atras "+categoriaActual);
                      //categoria padre regresa "";
                      if(categoriaActual!=""){
                         categoriaActual= funciones.buttonsParent(categoriaActual);
                          if(categoriaActual==""){
                              botonesCategorias1.xml=funciones.buttonsRoot();
                              botonesCategorias2.xml="";
                              //jsonModelArbol.clear();
                              modelocat=[];
                              principal.modelocatChanged();
                          }
                          else{
                              botonesCategorias1.xml= funciones.buttonsAg(categoriaActual);
                              botonesCategorias2.xml= funciones.buttonsPr(categoriaActual);
                              modelocat.pop();
                              principal.modelocatChanged();

                          }
                      }

                  }
                }
                AppButton{
                  id:homeCategoria
                  icon: IconType.home
                  minimumWidth: dp(50)
                  minimumHeight: dp(50)
                  anchors.right: backCategoria.left
                  anchors.top:lineaDescripcion.top
                  backgroundColor: "#4a576c"
                  visible: visibleCategorias
                  iconSize: dp(30)
                  onClicked:{ botonesCategorias1.xml=funciones.buttonsRoot();
                  botonesCategorias2.xml="";
                  categoriaActual="";
                      console.log("cat_act "+categoriaActual);
                      modelocat=[];
                      principal.modelocatChanged();
                      //modelocatChanged()//no existe,pero es necesario para que se actualize la lista

                  }
                }
                JsonListModel {
                       id: jsonModelArbol
                       source: modelocat
                       keyField: "idCat"
                       fields: ["idCat", "nombre"]
                     }
                AppListView {
                     id: listaArbolC
                     //spacing: dp(90)
                     //backgroundColor: "white"
                     model: jsonModelArbol
                     anchors.right: homeCategoria.left
                     anchors.top: lineaDescripcion.top
                     anchors.left: lineaDescripcion.left
                     anchors.leftMargin: dp(10)
                     //anchors.topMargin: dp(10)
                     visible:visibleCategorias
                     orientation: Qt.Horizontal
                   delegate: Row {
                    id:delegadoarbol
                    spacing: dp(0)
                    AppButton{
                        property var valor: model.idCat
                        text:"/"+model.nombre
                        minimumWidth: dp(80)
                        minimumHeight: dp(50)
                        backgroundColor: "grey"
                        dropShadow: false
                        textColor: "white"
                        textSize: sp(20)
                        horizontalMargin: dp(0)
                        onClicked: {
                        console.log("precionado"+valor);
                            botonesCategorias1.xml= funciones.buttonsAg(model.idCat);
                            botonesCategorias2.xml= funciones.buttonsPr(model.idCat);
                            categoriaActual=model.idCat;
                            var ultimo;
                            ultimo=modelocat.pop();
                            console.log(ultimo);
                        }
                    }
                  }
                   }
                XmlListModel {
                    id: botonesCategorias1
                    query: "/Envelope/Body/GETButtonConfigWResponse/return/buttonconfig"
                    XmlRole { name: "ID_STR_RT" ; query: "ID_STR_RT/string()" }
                    XmlRole { name: "ID_BTNSET" ; query: "ID_BTNSET/string()" }
                    XmlRole { name: "ID_BTN" ; query: "ID_BTN/string()" }
                    XmlRole { name: "ID_BTN_PRNT" ; query: "ID_BTN_PRNT/string()" }
                    XmlRole { name: "TY_BTN" ; query: "TY_BTN/string()" }
                    XmlRole { name: "BTN_WT" ; query: "BTN_WT/string()" }
                    XmlRole { name: "NM_BTN" ; query: "NM_BTN/string()" }
                    XmlRole { name: "DE_BTN" ; query: "DE_BTN/string()" }
                    XmlRole { name: "PIC" ; query: "PIC/string()" }
                    XmlRole { name: "URL" ; query: "URL/string()" }
                    //XmlRole { name: "ID_ITM" ; query: "ID_ITM/string()" }
                    XmlRole { name: "ICON_ADDRESS" ; query: "ICON_ADDRESS/string()" }
                    XmlRole { name: "ID_STRGRP" ; query: "ID_STRGRP/string()" }
                    XmlRole { name: "ID_ITM_PS" ; query: "ID_ITM_PS/string()" }
                    XmlRole { name: "ID_ITM_PS_QFR" ; query: "ID_ITM_PS_QFR/string()" }


                    //source : "pic.xml"
                }
                XmlListModel {
                    id: botonesCategorias2
                    query: "/Envelope/Body/GETButtonConfigWResponse/return/buttonconfig"
                    XmlRole { name: "ID_STR_RT" ; query: "ID_STR_RT/string()" }
                    XmlRole { name: "ID_BTNSET" ; query: "ID_BTNSET/string()" }
                    XmlRole { name: "ID_BTN" ; query: "ID_BTN/string()" }
                    XmlRole { name: "ID_BTN_PRNT" ; query: "ID_BTN_PRNT/string()" }
                    XmlRole { name: "TY_BTN" ; query: "TY_BTN/string()" }
                    XmlRole { name: "BTN_WT" ; query: "BTN_WT/string()" }
                    XmlRole { name: "NM_BTN" ; query: "NM_BTN/string()" }
                    XmlRole { name: "DE_BTN" ; query: "DE_BTN/string()" }
                    XmlRole { name: "PIC" ; query: "PIC/string()" }
                    XmlRole { name: "URL" ; query: "URL/string()" }
                    ///XmlRole { name: "ID_ITM" ; query: "ID_ITM/string()" }
                    XmlRole { name: "ICON_ADDRESS" ; query: "ICON_ADDRESS/string()" }
                    XmlRole { name: "ID_STRGRP" ; query: "ID_STRGRP/string()" }
                    XmlRole { name: "ID_ITM_PS" ; query: "ID_ITM_PS/string()" }
                    XmlRole { name: "ID_ITM_PS_QFR" ; query: "ID_ITM_PS_QFR/string()" }


                    //source : "pic.xml"
                }
                GridView {
                    id:listaCategoriasPadres
                       //anchors.top: homeCategoria.bottom//no estoy seguro, pero lo toma mal
                       anchors.top:lineaDescripcion.top
                       anchors.topMargin: dp(120)
                       height: lineaDescripcion.height-dp(185)
                       width:lineaDescripcion.width/5
                       anchors.left: lineaDescripcion.left
                       anchors.leftMargin: dp(10)
                       model: botonesCategorias1
                       visible:visibleCategorias
                       cellWidth:  dp(100)
                       cellHeight: dp(92)
                       Component {
                           id: contactsDelegate1
                           Rectangle {
                               id: wrapper
                               width:listaCategoriasPadres.width
                               height: dp(80)
                               radius : dp(6)
                               //color: GridView.isCurrentItem ? "black" : "green"
                               clip : true
                               color:"#265596"
                               property bool noprecionado: true
                               Image {
                                   id: picx
                                   source: "../assets/default.png"
                                   height: dp(40)
                                   width: dp(40)
                                   anchors.top: parent.top
                                   anchors.horizontalCenter: parent.horizontalCenter
                               }
                               Text {
                                   //id: contactInfo
                                   //id: contactInfo
                                   text: DE_BTN
                                   font.pointSize:  sp(10)
                                   font.bold:  true
                                   //anchors.centerIn: parent
                                   anchors.top: picx.bottom
                                   anchors.horizontalCenter: parent.horizontalCenter
                                   //width: dp(130)
                                   width:parent.width
                                   maximumLineCount: 2
                                   horizontalAlignment: Text.AlignHCenter
                                   wrapMode: Text.WordWrap
                                   color: "white"
                               }

                               MouseArea{
                                   anchors.fill:  parent
                                   acceptedButtons: Qt.LeftButton | Qt.RightButton
                                   onClicked: {
                                       botonesCategorias1.xml= funciones.buttonsAg(ID_BTN);
                                       botonesCategorias2.xml= funciones.buttonsPr(ID_BTN);
                                       categoriaActual=ID_BTN;
                                       console.log("cat_act "+categoriaActual);
                                       var newItem = {
                                                  "idCat": ID_BTN,
                                                  "nombre": DE_BTN
                                                     }
                                                modelocat.push(newItem)
                                                principal.modelocatChanged()//no existe,pero es necesario para que se actualize la lista
                                   }

                               }
                           }
                       }

                       delegate: contactsDelegate1
                }
                GridView {
                    id:listaProductos
                    anchors.top:homeCategoria.bottom
                    //width: (lineaDescripcion/4)*3
                    height: lineaDescripcion.height-dp(150)
                    //cellWidth:  dp(150)
                    //cellWidth: listaProductos.width/4
                    cellWidth: lineaDescripcion.width/5
                    anchors.left: listaCategoriasPadres.right
                    anchors.leftMargin: dp(10)
                    anchors.right: lineaDescripcion.right
                    anchors.rightMargin: dp(10)
                    visible:visibleCategorias
                    model: botonesCategorias2
                    //cellHeight: dp(62)
                    cellHeight: dp(92)
                    Component {
                        id: contactsDelegate
                        Rectangle {
                            id: wrapper
                            //width: dp(140)
                            width: (listaProductos.width/4)-dp(10)
                            //height: dp(50)
                            height: dp(80)
                            radius : dp(6)
                            //color: GridView.isCurrentItem ? "black" : "green"
                            clip : true
                            color: "#4a576c"
                            property bool noprecionado: true

                            Image {
                                id: pic
                                source: "../assets/felgo-logo.png"
                                height: dp(40)
                                width: dp(40)
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text {
                                id: contactInfo
                                text: DE_BTN
                                font.pointSize:  sp(9)
                                font.bold:  true
                                //anchors.centerIn: parent
                                anchors.top: pic.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                //width: dp(130)
                                width:parent.width
                                maximumLineCount: 2
                                horizontalAlignment: Text.AlignHCenter
                                wrapMode: Text.WordWrap
                                color: "white"
                            }

                            MouseArea{
                                anchors.fill:  parent
                                acceptedButtons: Qt.LeftButton | Qt.RightButton
                                onClicked: {
                                    //funciones.buttonsAg()
                                    console.log("precionado "+DE_BTN+" posidentity: "+ID_ITM_PS);                        
                                    //falta las cantidades
                                    var value = funciones.set_selected(ID_ITM_PS,ID_ITM_PS_QFR,1);
                                    if(funciones.get_last_set_selected_result()>0)
                                    {
                                        console.debug("main.qml processItemLookUP 2");
                                        //myDisplay.venta2(valor);
                                        var myObject = new Object ;
                                        myObject.textCount = value.ln ;
                                        myObject.textQuantity = value.unitario ;
                                        myObject.textName = value.titulo;
                                        myObject.textPrice = value.precio_unitario ;
                                        //txtNmItem.text=value.titulo;
                                        //txtValueItem.text=myObject.textPrice;
                                        myObject.textid_itm_ps=ID_ITM_PS;
                                        myObject.textid_itm_ps_qfr=ID_ITM_PS_QFR;
                                        myObject.textTotal = value.importe;
                                        sumat.text="$"+ value.suma;//total_venta-value.total_impuesto;
                                        impuestost.text="$"+value.total_impuesto;
                                        totalt.text=value.total_venta;
                                        //txtPagado.text=value.pagado;
                                        //txtAPagar.text=value.total_a_pagar;
                                        //txtAPagar1.text=value.total_a_pagar;
                                        totalticketText.text= value.total_a_pagar;
                                        myObject.isCanceled = false ;
                                        myObject.isCancelation = value.isCancelation ;
                                        myObject.FOOD_STAMP = value.FOOD_STAMP ;
                                        myObject.QTY_ITM = value.QTY_ITM; //
                                        myObject.pack = value.pack ;
                                        myObject.canceled = false;
                                        myObject.cambios="";
                                        myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                                        //myCashPad.enableCashPad( true );
                                        //myCashPad.enableOperCaja( true );
                                        //myCashPad.enablePagos( true );
                                        //myCashPad.enableVentaEspera( true );
                                        //myCashPad.enableDevoluciones( false );
                                        //funciones.resetflDevolucion();

                                    }
                                    else
                                    {
                                        if( funciones.get_last_set_selected_result() === -1)
                                        {
                                            mensajes.tipoM=2;
                                            mt.text="El artículo no puede tener fracciones";
                                            mostrarTexto.start();
                                            console.log( "El artículo no puede tener fracciones");
                                            return;
                                        }
                                        else
                                        {
                                            mensajes.tipoM=2;
                                            mt.text="El artículo no existe";
                                            mostrarTexto.start();
                                            console.log("El artículo no existe");
                                            return;
                                        }
                                    }

                                }

                            }
                        }
                    }

                    delegate: contactsDelegate
                }

                //finn seccion categorias
                //seccion listabusqueda

                property var busquedaSelectPS:""
                property var busquedaSelectPSQFR:""

                XmlListModel {
                    id: xmlModelBusca
                     query: "/ItemSearch/ItemList"
                     XmlRole { name: "ID_ITM_PS" ; query: "ID_ITM_PS/string()" }
                     XmlRole { name: "ID_ITM_PS_QFR"; query: "ID_ITM_PS_QFR/string()" }
                     XmlRole { name: "NM_ITM"; query: "NM_ITM/string()" }
                     XmlRole { name: "PRICE"; query: "PRICE/string()" }
                     XmlRole { name: "QTY_ITM"; query: "QTY_ITM/string()" }
                     XmlRole{name: "PIC"; query: "PIC/string()"}
                }
                AppListView {
                    id:listaitems
                       anchors.top: lineaDescripcion.top
                       anchors.bottom: acepCancB.top
                       width:lineaDescripcion.width-dp(40)
                       anchors.left: lineaDescripcion.left
                       anchors.leftMargin: dp(20)
                       anchors.topMargin:  dp(10)
                       model: xmlModelBusca
                       visible:visibleBusqueda
                       delegate: Row {
                        id:delegadoitems
                        spacing: dp(10)

                        Rectangle{
                            id:fondoitm
                            color:
                                   index%2===0 ? "white":
                                    "#82bee3"
                            border.color: page.busquedaSelectPS===ID_ITM_PS ? "red":
                                                                               "grey"

                            width:listaitems.width
                            height: dp(40)
                            MouseArea{
                                anchors.fill: parent
                                        onClicked: {
                                            listaitems.focus=true;
                                            console.log("Clicked Item #"+index);
                                            // console.log("solo un articulo encontrado con "+funciones.itemsearch_getPosidentity())
                                            //funciones.itemsearch_getPosidentity(), funciones.itemsearch_getQfr()
                                             listaitems.currentIndex=index;
                                            page.busquedaSelectPS=ID_ITM_PS;
                                            page.busquedaSelectPSQFR=ID_ITM_PS_QFR;
                                            console.log("tntntntn"+PIC+"tntntnt");
                                            if(PIC.length<7){
                                            previewbusqueda.sourse="../assets/default.png";
                                            }else{
                                            previewbusqueda.sourse=PIC
                                            }
                                        }
                            }
                            AppText{
                                id:idItm
                                text: ID_ITM_PS
                                anchors.left: parent.left
                                anchors.leftMargin: dp(10)
                            }

                            AppText{
                                id:idItm2
                                text: NM_ITM
                                anchors.left: idItm.right
                                anchors.leftMargin: dp(10)
                                anchors.right: idItm3.left
                                anchors.rightMargin: dp(10)
                                maximumLineCount: 2
                            }

                            AppText{
                                id:idItm3
                                text: PRICE
                                anchors.right:  fondoitm.right
                                anchors.rightMargin: dp(10)
                            }
                        }

                        Keys.onDownPressed: {
                            listaitems.incrementCurrentIndex();
                        console.log("Down key " + listaitems.currentIndex.toString());
                            xmlModelBusca.get(listaitems.currentIndex).ID_ITM_PS;
                            console.log("Clicked Item #"+xmlModelBusca.get(listaitems.currentIndex).NM_ITM);
                            page.busquedaSelectPS=xmlModelBusca.get(listaitems.currentIndex).ID_ITM_PS;
                            page.busquedaSelectPSQFR=xmlModelBusca.get(listaitems.currentIndex).ID_ITM_PS_QFR;


                        }
                        Keys.onUpPressed: {
                            listaitems.decrementCurrentIndex();
                        console.log("Up key " + listaitems.currentIndex.toString());
                            console.log("Clicked Item #"+xmlModelBusca.get(listaitems.currentIndex).NM_ITM);
                            page.busquedaSelectPS=xmlModelBusca.get(listaitems.currentIndex).ID_ITM_PS;
                            page.busquedaSelectPSQFR=xmlModelBusca.get(listaitems.currentIndex).ID_ITM_PS_QFR;


                        }
                      }

                }

                Row{
                    id:acepCancB
                    spacing: dp(10)
                    anchors.horizontalCenter: lineaDescripcion.horizontalCenter
                    anchors.bottom: lineaDescripcion.bottom
                    AppButton{
                    id:aceptarBusca
                    icon: IconType.check
                    text:"Aceptar"
                    minimumWidth: ((teclado.width/7)*2)-dp(40)
                    minimumHeight: dp(50)
                    backgroundColor: "#4a576c"
                    visible:visibleBusqueda
                    onClicked:{
                        visibleBusqueda=false;

                        if( cantidadArtIngresados > 9999 )
                        {
                            NativeDialog.confirm("Error", "No se pueden manejar cantidades mayores a 9999", function(ok) {
                                if(ok) {

                                }
                              })
                            return;
                        }
                        if( cantidadArtIngresados <= 0 )//count multiplicador
                        {
                            NativeDialog.confirm("Error", "No se pueden manejar cantidades negativas, letras, nada o cero", function(ok) {
                                if(ok) {

                                }
                              })
                            return;
                        }
                        if(page.busquedaSelectPS.toString().length<=0||page.busquedaSelectPSQFR.toString().length<=0){
                            mensajes.tipoM=2;
                            mt.text="Sin Seleccion";
                            mostrarTexto.start();
                            return;
                        }
                        var value = funciones.set_selected(page.busquedaSelectPS ,page.busquedaSelectPSQFR ,cantidadArtIngresados);
                          if(funciones.get_last_set_selected_result()>0)
                          {
                              console.debug("en colocar de la busqueda");
                              var myObject = new Object ;
                              myObject.textCount = value.ln ;
                              myObject.textQuantity = value.unitario ;
                              myObject.textName = value.titulo;
                              myObject.textPrice = value.precio_unitario ;
                              myObject.textid_itm_ps=page.busquedaSelectPS;
                              myObject.textid_itm_ps_qfr=page.busquedaSelectPSQFR;
                              myObject.textTotal = value.importe+1;
                              sumat.text=value.suma;//total_venta-value.total_impuesto;
                              impuestost.text=value.total_impuesto;
                              totalt.text=value.total_venta;
                              totalticketText.text= value.total_a_pagar;
                              myObject.isCanceled = false ;
                              myObject.isCancelation = value.isCancelation ;
                              myObject.FOOD_STAMP = value.FOOD_STAMP ;
                              myObject.QTY_ITM = value.QTY_ITM; //
                              myObject.pack = value.pack ;
                              myObject.canceled = false;
                              myObject.cambios="";

                              myObject.imagenes=value.imagenes;
                              //myObject.imagenes=myObject.imagenes.join(",");
                              console.debug("imagenes tiene "+myObject.imagenes[0]+" tamaño "+myObject.imagenes.length);
                              myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                              visibleBusqueda=false;
                              visibleDescripcio=false;
                              visibleCategorias=false;
                              visibleVenta=false;
                              mensajes.tipoM=1;
                              mt.text="Añadido articulo";
                              mostrarTexto.start();
                              txtBusqueda.text="";
                          }

                    }
                    }
                    AppButton{
                    id:cancelarBusca
                    icon: IconType.angledoubleleft
                    text:"Atras"
                    minimumWidth: ((teclado.width/7)*2)-dp(40)
                    minimumHeight: dp(50)
                    backgroundColor: "#4a576c"
                    visible:visibleBusqueda
                    onClicked:{ visibleBusqueda=false;}
                    }
                }

                AppButton{
                  id:botonBuscar
                  icon: IconType.search
                  text: "Buscar"
                  backgroundColor: "#4a576c"
                  anchors.bottom: teclado.top
                  anchors.right:  teclado.right
                  minimumWidth: ((teclado.width/7)*2)-dp(40)
                  minimumHeight: dp(30)
                  onClicked: {

                    numeroArtEncontrados=0;
                    cantidadArtIngresados=0.0;
                    var valorABuscar="";
                      if (txtBusqueda.text.indexOf( "*") >= 0 )//busca el * de multiples articulos
                      {
                          var newValue = txtBusqueda.text.split( "*" ) ;
                          cantidadArtIngresados = parseFloat(newValue[0]) ;
                          if(isNaN(cantidadArtIngresados)){
                              cantidadArtIngresados = -1;
                          }
                          valorABuscar=newValue[1];
                      }
                      else
                      {
                          cantidadArtIngresados = 1.00 ; // No se uso el multiplicador
                          valorABuscar=txtBusqueda.text;
                      }

                      numeroArtEncontrados=funciones.itemsearchPrepare(valorABuscar);
                      if(numeroArtEncontrados===1){
                        //console.log("solo un articulo encontrado con "+funciones.itemsearch_getPosidentity())
                          mensajes.tipoM=1;
                          mt.text="solo un articulo encontrado con "+funciones.itemsearch_getPosidentity();
                          mostrarTexto.start();
                        //funciones.itemsearch_getPosidentity(), funciones.itemsearch_getQfr()
                          var value = funciones.set_selected(funciones.itemsearch_getPosidentity() ,funciones.itemsearch_getQfr() ,cantidadArtIngresados);
                          if(funciones.get_last_set_selected_result()>0)
                          {
                              console.debug("en colocar de la busqueda");
                              //myDisplay.venta2(valor);
                              var myObject = new Object ;
                              myObject.textCount = value.ln ;
                              myObject.textQuantity = value.unitario ;
                              myObject.textName = value.titulo;
                              myObject.textPrice = value.precio_unitario ;
                              myObject.textid_itm_ps=funciones.itemsearch_getPosidentity() ;
                              myObject.textid_itm_ps_qfr=funciones.itemsearch_getQfr();
                              myObject.textTotal = value.importe;
                              sumat.text=value.suma;//total_venta-value.total_impuesto;
                              impuestost.text=value.total_impuesto;
                              totalt.text=value.total_venta;
                              totalticketText.text= value.total_a_pagar;
                              myObject.isCanceled = false ;
                              myObject.isCancelation = value.isCancelation ;
                              myObject.FOOD_STAMP = value.FOOD_STAMP ;
                              myObject.QTY_ITM = value.QTY_ITM; //
                              myObject.pack = value.pack ;
                              myObject.canceled = false;
                              myObject.cambios="";
                              myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                              visibleBusqueda=false;
                              visibleDescripcio=false;
                              visibleCategorias=false;
                          }


                      }
                      else{
                          console.log("encontrados varios "+funciones.itemsearch())

                        xmlModelBusca.xml=funciones.itemsearch();
                          visibleBusqueda=true;
                          visibleDescripcio=false;
                          visibleCategorias=false;
                          visibleVenta=false;
                          listaitems.focus=true;
                          //console.log("Clicked Item #"+index);

                           listaitems.currentIndex=0;
                      }
                  }
                }

                AppTextField {
                  id: txtBusqueda
                  //Layout.preferredWidth: dp(200)
                  showClearButton: true
                  font.pixelSize: sp(18)
                  backgroundColor: "white";

                  borderColor: "black"
                  borderWidth: dp(2)
                  anchors.right: botonBuscar.left
                  anchors.bottom: teclado.top
                  anchors.left: teclado.left
                  anchors.bottomMargin:  dp(5)
                  height: dp(50)
                  layer.enabled: true
                              layer.effect: DropShadow {
                                  transparentBorder: true
                                  horizontalOffset: 1
                                  verticalOffset: 1
                              }
                }

                Rectangle{
                    id:teclado
                    color:"white"
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: dp(10)
                    anchors.rightMargin: dp(10)
                    width: totalf.width
                    height: dp(240)

                    AppButton{
                      id:scan
                      icon: IconType.rotateleft
                      text: "Devolucion"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: teclado.left
                      anchors.top:teclado.top
                      backgroundColor: "#4a576c"
                      onClicked: {

                        if(funciones.toggleflDevolucion())
                        scan.backgroundColor="#692333"
                        else
                         backgroundColor= "#4a576c"
                      }
                    }

                    AppButton{
                      id:uno
                      text: "1"
                      textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: scan.right
                      anchors.top:teclado.top
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"1"}
                    }
                    AppButton{
                      id:dos
                      text: "2"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: uno.right
                      anchors.top:teclado.top
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"2"}
                    }
                    AppButton{
                      id:tres
                      text: "3"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: dos.right
                      anchors.top:teclado.top
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"3"}
                    }

                    AppButton{
                      id:pro1
                      text: "*"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: tres.right
                      anchors.top:teclado.top
                      backgroundColor: "#4a576c"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"*"}
                    }

                    AppButton{
                      id:navegar
                      icon: IconType.bars
                      text: "Navegar"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: teclado.left
                      anchors.top:scan.bottom
                      backgroundColor: "#4a576c"
                      onClicked: {
                        visibleBusqueda=false;
                        visibleDescripcio=false;
                        visibleCategorias=true;
                        visibleVenta=false;
                      }
                    }

                    AppButton{
                      id:cuatro
                      text: "4"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: navegar.right
                      anchors.top:uno.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"4"}
                    }
                    AppButton{
                      id:cinco
                      text: "5"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: cuatro.right
                      anchors.top:dos.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"5"}
                    }
                    AppButton{
                      id:seis
                      text: "6"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: cinco.right
                      anchors.top: tres.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"6"}
                    }

                    AppButton{
                      id:pro2
                      //icon: IconType.dollar
                      icon:IconType.folderopeno
                      text: "Recuperar V."
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: seis.right
                      anchors.top:pro1.bottom
                      backgroundColor: "#4a576c"
                      onClicked: {
                          if(funciones.venta_activa())
                          {
                              mensajes.tipoM=2;
                              mt.text="Guarda primero la venta actual";
                              mostrarTexto.start();
                              return;
                          }
                          if(funciones.getNumeroVentasEspera()>0){
                              page.ventasSVisible=true;
                              page.listaComboVentas=funciones.getNombresVentaEspera();
                            }
                          else{
                              mensajes.tipoM=1;
                              mt.text="No hay ventas en espera";
                              mostrarTexto.start();
                          }
                      }
                    }

                    AppButton{
                      id:buscar
                      icon: IconType.money
                      text: "Descuento"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: teclado.left
                      anchors.top:navegar.bottom
                      backgroundColor: "#4a576c"
                    }

                    AppButton{
                      id:siete
                      text: "7"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: buscar.right
                      anchors.top:cuatro.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"7"}
                    }
                    AppButton{
                      id:ocho
                      text: "8"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: siete.right
                      anchors.top:cinco.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"8"}
                    }
                    AppButton{
                      id:nueve
                      text: "9"
                       textSize: sp(20)
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(50)
                      anchors.left: ocho.right
                      anchors.top: seis.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"9"}
                    }

                    AppButton{
                      id:pro3
                      icon: IconType.save
                      text: "V. en espera"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight:dp(50)
                      anchors.left: nueve.right
                      anchors.top:pro2.bottom
                      backgroundColor: "#4a576c"
                      onClicked: {
                          if ( !funciones.venta_activa() )
                          {
                              mensajes.tipoM=2;
                              mt.text="No hay venta";
                              mostrarTexto.start();
                              return ;
                          }
                          NativeDialog.inputText("Colocar la venta en espera", "Coloque una etiqueta a la venta", "Etiqueta", "miventa", function(ok, text) {
                                 if(ok) {
                                     //console.debug("MainUsa.qml waitSaleSave onExiting value.status 1"+value.text)
                                     if(funciones.waitSaleSave(text))
                                     {
                                         myModelt.clear();
                                         sumat.text="0.00";
                                         impuestost.text="0.00";
                                         totalt.text="0.00";
                                         totalticketText.text="0.00";
                                         //console.debug("MainUsa.qml waitSaleSave onExiting value.status 4"+value.status)
                                         //myCashPad.setVentaEnEspera(true);
                                         visibleBusqueda=false;
                                         visibleDescripcio=false;
                                         visibleCategorias=false;
                                         return;
                                      }
                                      else
                                      {
                                         mensajes.tipoM=2;
                                         mt.text="Nombre repetido en las ventas en espera";
                                         mostrarTexto.start();
                                      }
                                 }
                               })
                      }
                    }

                    AppButton{
                      id:opcion2
                      icon: IconType.angleup
                      text: "Menu"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: teclado.left
                      anchors.top:buscar.bottom
                      backgroundColor: "#4a576c"
                      onClicked: visibleMenuDespegable1 ? visibleMenuDespegable1=false : visibleMenuDespegable1=true
                    }

                    AppButton{
                      id:asterisco
                       textSize: sp(20)
                      text: "."
                      minimumWidth: (teclado.width/7)
                      minimumHeight: dp(45)
                      anchors.left: opcion2.right
                      anchors.top:ocho.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"."}
                    }
                    AppButton{
                      id:cero
                      text: "0"
                       textSize: sp(20)
                      minimumWidth: ((teclado.width/7)*2)+dp(15)
                      minimumHeight: dp(45)
                      anchors.left: asterisco.right
                      anchors.top:nueve.bottom
                      backgroundColor: "#265596"
                      onClicked: {txtBusqueda.text=txtBusqueda.text+"0"}
                    }

                    AppButton{
                      id:pro4
                      icon: IconType.check

                      text: "Enter"
                      minimumWidth: ((teclado.width/7)*2)-dp(40)
                      minimumHeight: dp(50)
                      anchors.left: cero.right
                      anchors.top:pro3.bottom
                      backgroundColor: "#4a576c"
                      onClicked: {
                            mostrarTexto.start();
                      }
                    }

                    //opcion2 menuBar
                    AppButton{
                      id:m1
                      text: "Cortez"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: opcion2.left
                      anchors.leftMargin: dp(30)
                      anchors.bottom: opcion2.top
                      verticalMargin: dp(0)
                      backgroundColor: "#692333" //#82bee3 #692333
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                        var acceso=  funciones.check_permisos("1034")
                        visibleMenuDespegable1=false;
                        if(acceso===0){
                            page.supervisorLogVisible=true;
                            page.operacion_especial=1;
                        }
                        else{
                            console.debug("procede al corte");
                            funciones.do_cortez();
                            page.loginvisible=true;
                            funciones.logout();
                            visibleMenuDespegable1=false;
                        }
                      }
                    }
                    AppButton{
                      id:m2
                      text: "Cortex"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m1.left
                      anchors.bottom: m1.top
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                      visibleMenuDespegable1=false;
                      }
                    }
                    AppButton{
                      id:m3
                      text: "Depositos"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m2.left
                      anchors.bottom: m2.top
                      //anchors.bottomMargin: dp(10)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      verticalMargin: dp(0)
                      textColor: "white"
                      onClicked: {
                          page.operacion_especial=2
                          visibleMenuDespegable1=false;
                          var acceso=  funciones.check_permisos("1043")
                          if(acceso===0){
                          page.supervisorLogVisible=true;
                          }
                          else{
                          page.despositoVisible=true;
                          montoRD.text="";
                          motivoRD.text="";
                          }
                      }
                    }
                    AppButton{
                      id:m4
                      text: "Retiros"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m3.left
                      anchors.bottom: m3.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                          page.operacion_especial=3
                          visibleMenuDespegable1=false;
                          var acceso=  funciones.check_permisos("1042")
                          if(acceso===0){
                          page.supervisorLogVisible=true;
                          }
                          else{
                          page.despositoVisible=true;
                          montoRD.text="";
                          motivoRD.text="";
                          }
                      }
                    }
                    AppButton{
                      id:m5
                      text: "Pago menor"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m4.left
                      anchors.bottom: m4.top
                      //anchors.bottomMargin: dp(10)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      verticalMargin: dp(0)
                      textColor: "white"
                      onClicked: {
                          page.operacion_especial=4
                          visibleMenuDespegable1=false;
                          var acceso=  funciones.check_permisos("1039")
                          if(acceso===0){
                          page.supervisorLogVisible=true;
                          }
                          else{
                          page.despositoVisible=true;
                          montoRD.text="";
                          motivoRD.text="";
                          }
                      }
                    }
                    AppButton{
                      id:m6
                      text: "Cobro Menor"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)

                      minimumHeight: dp(50)
                      anchors.left: m5.left
                      anchors.bottom: m5.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                          page.operacion_especial=5
                          visibleMenuDespegable1=false;
                          var acceso=  funciones.check_permisos("1040")
                          if(acceso===0){
                          page.supervisorLogVisible=true;
                          }
                          else{
                          page.despositoVisible=true;
                          montoRD.text="";
                          motivoRD.text="";
                          }
                      }
                    }
                    AppButton{
                      id:m7
                      text: "V. en espera"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m6.left
                      anchors.bottom: m6.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                        visibleMenuDespegable1=false;
                          if ( !funciones.venta_activa() )
                          {
                              mensajes.tipoM=2;
                              mt.text="No hay venta";
                              mostrarTexto.start();
                              return ;
                          }
                          NativeDialog.inputText("Colocar la venta en espera", "Coloque una etiqueta a la venta", "Etiqueta", "miventa", function(ok, text) {
                                 if(ok) {
                                     //console.debug("MainUsa.qml waitSaleSave onExiting value.status 1"+value.text)
                                     if(funciones.waitSaleSave(text))
                                     {
                                         myModelt.clear();
                                         sumat.text="0.00";
                                         impuestost.text="0.00";
                                         totalt.text="0.00";
                                         totalticketText.text="0.00";
                                         //console.debug("MainUsa.qml waitSaleSave onExiting value.status 4"+value.status)
                                         //myCashPad.setVentaEnEspera(true);
                                         visibleBusqueda=false;
                                         visibleDescripcio=false;
                                         visibleCategorias=false;
                                         return;
                                      }
                                      else
                                      {
                                         mensajes.tipoM=2;
                                         mt.text="Nombre repetido en las ventas en espera";
                                         mostrarTexto.start();
                                      }
                                 }
                               })
                      }
                    }
                    AppButton{
                      id:m8
                      text: "Recupera v."
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m7.left
                      anchors.bottom: m7.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                        visibleMenuDespegable1=false;
                          if(funciones.venta_activa())
                          {
                              mensajes.tipoM=2;
                              mt.text="Guarda primero la venta actual";
                              mostrarTexto.start();
                              return;
                          }
                          if(funciones.getNumeroVentasEspera()>0){
                              page.ventasSVisible=true;
                              page.listaComboVentas=funciones.getNombresVentaEspera();
                            }
                          else{
                              mensajes.tipoM=1;
                              mt.text="No hay ventas en espera";
                              mostrarTexto.start();
                          }
                      }
                    }
                    AppButton{
                      id:m9
                      text: "Cancelar v."
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m8.left
                      anchors.bottom: m8.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"

                      onClicked: {
                          page.operacion_especial=8
                          visibleMenuDespegable1=false;
                          var acceso=  funciones.check_permisos("1032")
                          if(acceso===0){
                          page.supervisorLogVisible=true;
                          }
                          else{
                              NativeDialog.confirm("Cancelar venta", "¿Desea cancelar la venta?", function(ok) {
                                  if(ok) {
                                      if ( funciones.getNumeroLineas() === 0 )
                                      {
                                          mensajes.tipoM=2;
                                          mt.text="No hay venta que cancelar";
                                          mostrarTexto.start();
                                          //alerta(true, false, "No hay venta que cancelar")
                                          return ;
                                      }
                                      if ( funciones.getPosibleNoVenta()){
                                          console.debug("-- INICIA PROCESO NO VENTA --");
                                          funciones.finish_ticket(1, -1);
                                          myModelt.clear();
                                          sumat.text="0.00";
                                          impuestost.text="0.00";
                                          totalt.text="0.00";
                                          totalticketText.text= "0.00";
                                          mensajes.tipoM=1;
                                          mt.text="Venta cancelada";
                                          mostrarTexto.start();
                                      }
                                      else{
                                          mensajes.tipoM=2;
                                          mt.text="Se deben cancelar los renglones";
                                          mostrarTexto.start();
                                          //alerta(true, false, "Se deben cancelar los renglones");
                                      }
                                  }

                              })
                          }

                      }
                    }
                    AppButton{
                      id:m10
                      text: "Alta Art."
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m9.left
                      anchors.bottom: m9.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                        //page.loginvisible=true;
                        //funciones.logout();
                        visibleMenuDespegable1=false;
                        visibleAlta=true;
                      }
                    }

                    AppButton{
                      id:m11
                      text: "Salir"
                      minimumWidth: ((teclado.width/7)*2)-dp(45)
                      minimumHeight: dp(50)
                      anchors.left: m10.left
                      anchors.bottom: m10.top
                      //anchors.bottomMargin: dp(10)
                      verticalMargin: dp(0)
                      backgroundColor: "#692333"
                      visible:visibleMenuDespegable1
                      borderColor: "white"
                      borderWidth: dp(1)
                      textColor: "white"
                      onClicked: {
                        page.loginvisible=true;
                        funciones.logout();
                        visibleMenuDespegable1=false;
                      }
                    }

                }

                //fin seccion listabusqueda


                //login de encargado
                property bool supervisorLogVisible: false
                property int  operacion_especial:0
                /*operaciones
                1 Cortez
                2 Depositos
                3 Retiros
                4 pago menor
                5 cobro menor
                6 salir
                7 anular de linea
                8 cancelacion de venta
                9 cambio de precio temporal
*/
                //seccion zona login supervisor

                Rectangle{
                  id:fondoblock2
                  width: parent.width
                  height: parent.height
                  z:1
                  visible: page.supervisorLogVisible

                  Image {
                      id: logo2
                      source: "../assets/logo.png"
                      anchors.left: parent.left
                      anchors.top: parent.top
                      anchors.margins: dp(30)
                      width:dp(320)
                      height: dp(85)

                  }

                  Rectangle{
                    id:rojo2
                    anchors.left: logo2.right
                    anchors.top: parent.top
                    anchors.topMargin: dp(85)
                    anchors.leftMargin: dp(10)

                    color: "#FD070C"
                    height: dp(10)
                    width: parent.width -dp(500)

                  }

                  Rectangle{
                    id:azul2
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: dp(80)
                    color: "#265596"
                    height: dp(10)
                    width: parent.width -dp(330)

                  }

                  Rectangle {
                    id: loginFormS
                    anchors.centerIn: parent
                    color: "#d6d6d6"
                    width: contentS.width + dp(48)
                    height: contentS.height + dp(80)//16
                    radius: dp(4)
                    visible: page.supervisorLogVisible
                    border.color: "black"


                    GridLayout {
                        id: contentS
                        anchors.centerIn: loginFormS
                        columnSpacing: dp(20)
                        rowSpacing: dp(10)
                        columns: 2
                        visible: page.supervisorLogVisible
                        // headline
                        z:1


                        // email text and field
                        AppText {
                          id:txtUsernamelS
                          text: qsTr("Usuario")
                          font.pixelSize: sp(12)

                          //fontFamily: geoFont
                        }

                        AppTextField {
                          id: txtUsernameS
                          Layout.preferredWidth: dp(200)
                          showClearButton: true
                          font.pixelSize: sp(14)
                          backgroundColor: "white";

                          borderColor: Theme.tintColor
                          borderWidth: dp(2)
                        }

                        // password text and field
                        AppText {
                          id:txtPasswordlS
                          text: qsTr("Contraseña")
                          font.pixelSize: sp(12)

                          //fontFamily: geoFont
                        }

                        AppTextField {
                          id: txtPasswordS
                          Layout.preferredWidth: dp(200)
                          showClearButton: true
                          font.pixelSize: sp(14)
                          backgroundColor: "white"
                          borderColor: Theme.tintColor
                          borderWidth:  dp(2)
                          echoMode: TextInput.Password
                        }

                        Column {
                          Layout.fillWidth: true
                          Layout.columnSpan: 2
                          Layout.topMargin: dp(12)

                          // buttons
                          AppButton {
                              id:logbutonS
                            text: "Ingreso"
                            flat: false
                            fontCapitalization: Font.MixedCase
                            backgroundColor: "#4a576c"
                            backgroundColorPressed: "#d6d6d6"
                            anchors.horizontalCenter: parent.horizontalCenter
                            fontBold: false
                            //fontFamily: geoFont
                            onClicked: {
                              page.forceActiveFocus() // move focus away from text fields
                                    var loginresult=funciones.login(txtUsernameS.text,txtPasswordS.text,true);
                                    if(loginresult!==""){

                                    page.supervisorLogVisible=false;
                                    page.backgroundColor="aliceblue";
                                        if(page.operacion_especial===9){
                                            page.cambiopVisible=true;
                                            preciotext.text=t1.text;
                                            motivotext.text="";
                                            observaciontext.text=d3.text;
                                            return;
                                        }
                                        else if(page.operacion_especial===8){
                                            NativeDialog.confirm("Cancelar venta", "¿Desea cancelar la venta?", function(ok) {
                                                if(ok) {
                                                if ( funciones.getNumeroLineas() === 0 )
                                                {
                                                    mensajes.tipoM=2;
                                                    mt.text="No hay venta que cancelar";
                                                    mostrarTexto.start();
                                                    return ;
                                                }
                                                if ( funciones.getPosibleNoVenta()){
                                                    console.debug("-- INICIA PROCESO NO VENTA --");
                                                    funciones.finish_ticket(1, -1);
                                                    myModelt.clear();
                                                    sumat.text="0.00";
                                                    impuestost.text="0.00";
                                                    totalt.text="0.00";
                                                    totalticketText.text= "0.00";
                                                    mensajes.tipoM=1;
                                                    mt.text="Venta cancelada";
                                                    mostrarTexto.start();
                                                    visibleBusqueda=false;
                                                    visibleCategorias=false;
                                                    visibleDescripcio=false;
                                                    visibleVenta=false;
                                                    return;
                                                }
                                                else{
                                                    mensajes.tipoM=2;
                                                    mt.text="Se deben cancelar los renglones";
                                                    mostrarTexto.start();
                                                    //alerta(true, false, "Se deben cancelar los renglones");
                                                }
                                                return;
                                                }
                                        })
                                            return;
                                        }
                                        else if(page.operacion_especial==7){
                                            if ( ticketIndice < 0 )
                                            {
                                               // myDisplay.alerta(true, false, "No existe renglón seleccionado");
                                                console.debug("No encontramos que cancelar") ;
                                                return ;
                                            }
                                            var res ={};
                                            console.debug("Antes de validar") ;
                                            res=funciones.validaCancel(ticketIndice)

                                            if(res.respuesta === 1)
                                            {
                                                console.debug("Antes de validado") ;
                                                //loginSupervisor();
                                                var value;
                                                value=funciones.do_cancel(ticketIndice);
                                                if (value.respuesta === 1){
                                                    //addLine2(value);
                                                    var myObject = new Object ;
                                                    myObject.textCount = value.ln ;
                                                    myObject.textQuantity = value.unitario ;
                                                    myObject.textName = value.titulo;
                                                    myObject.textPrice = value.precio_unitario ;
                                                    //txtNmItem.text=value.titulo;
                                                    //txtValueItem.text=myObject.textPrice;
                                                    myObject.textTotal = value.importe;
                                                    sumat.text="$"+ value.suma;//total_venta-value.total_impuesto;
                                                    impuestost.text="$"+value.total_impuesto;
                                                    totalt.text=value.total_venta;
                                                    //txtPagado.text=value.pagado;
                                                    //txtAPagar.text=value.total_a_pagar;
                                                    //txtAPagar1.text=value.total_a_pagar;
                                                    totalticketText.text= value.total_a_pagar;
                                                    myObject.isCanceled = false ;
                                                    myObject.isCancelation = value.isCancelation ;
                                                    myObject.FOOD_STAMP = value.FOOD_STAMP ;
                                                    myObject.QTY_ITM = value.QTY_ITM; //
                                                    myObject.pack = value.pack ;
                                                    myObject.canceled = false;
                                                    myModelt.insert( funciones.getNumeroLineas()-1, myObject );
                                                    myModelt.remove(ticketIndice);
                                                    value = funciones.getlinea(ticketIndice);
                                                    myModelt.insert( ticketIndice, value);
                                                    return;
                                                }
                                            }
                                            else
                                            {
                                               console.debug("No se puede realizar la cancelación") ;
                                            }
                                            return;
                                        }
                                        else{
                                          page.despositoVisible=true;
                                            montoRD.text="";
                                            motivoRD.text="";
                                            console.debug("llego aqui desde la operacion "+ page.operacion_especial);
                                        }
                                    }
                                    else{
                                     NativeDialog.confirm("Error", "Contraseña incorrecta, o no es supervisor", function(ok) {
                                         if(ok) {

                                         }
                                       })
                                    }

                            }//if onclicked
                          }
                          AppButton{
                              id:cancelbuttonS
                            text: "Cancelar"
                            flat: false
                            fontCapitalization: Font.MixedCase
                            backgroundColor: "#4a576c"
                            backgroundColorPressed: "#d6d6d6"
                            anchors.horizontalCenter: parent.horizontalCenter
                            fontBold: false
                            //fontFamily: geoFont
                            onClicked: {
                                page.supervisorLogVisible=false;
                            }
                          }
                        }
                      }

                  }

                  Rectangle {
                    id: loginFormhS
                    anchors.bottom: loginFormS.top
                    anchors.left: loginFormS.left
                    color: "#4a576c"
                    width: loginFormS.width
                    height: ingresoS.height + dp(16)
                    radius: dp(4)
                    visible: page.supervisorLogVisible
                    border.color: "black"
                    z:1

                    AppText {
                      id:ingresoS
                      anchors.verticalCenter: parent.verticalCenter
                      anchors.left: parent.left
                      anchors.leftMargin: dp(10)
                      text: "Ingreso"
                      color: "white"
                      //anchors.bottomMargin: dp(10)
                      visible: page.supervisorLogVisible
                    }


                  }

                }

                  //fin seccion de zona login

                  //seccion retiro/deposito
                  property bool despositoVisible: false
                  Rectangle {
                    id: depositoRetiro
                    anchors.centerIn: parent
                    color: "#d6d6d6"
                    width: contentd.width + dp(48)
                    height: contentd.height + dp(80)//16
                    radius: dp(4)
                    visible: page.despositoVisible
                    border.color: "black"

                  }

                  Rectangle {
                    id: drH
                    anchors.bottom: depositoRetiro.top
                    anchors.left: depositoRetiro.left
                    color: "#4a576c"
                    width: depositoRetiro.width
                    height: tituloS.height + dp(16)
                    radius: dp(4)
                    visible: page.despositoVisible
                    border.color: "black"

                  }

                  AppText {
                    id:tituloS
                    anchors.verticalCenter: drH.verticalCenter
                    anchors.left: drH.left
                    anchors.leftMargin: dp(10)
                    text: page.operacion_especial==2 ? "Despositos" :
                          page.operacion_especial==3 ? "Retiros"    :
                          page.operacion_especial==4 ? "Pago menor" :
                          "Cobro menor"
                    color: "white"
                    //anchors.bottomMargin: dp(10)
                    visible: page.despositoVisible
                  }

                  GridLayout {
                  id:contentd
                  anchors.centerIn: depositoRetiro
                  columnSpacing: dp(20)
                  rowSpacing: dp(10)
                  columns: 2
                  visible: page.despositoVisible

                  AppText {
                    visible: page.despositoVisible
                    text: qsTr("Monto")
                    font.pixelSize: sp(12)

                    //fontFamily: geoFont
                  }

                  AppTextField {
                    visible: page.despositoVisible
                    id: montoRD
                    Layout.preferredWidth: dp(200)
                    showClearButton: true
                    font.pixelSize: sp(14)
                    backgroundColor: "white";
                    validator:  DoubleValidator {bottom: 0; top: 9999.99;}
                    borderColor: Theme.tintColor
                    borderWidth: dp(2)
                  }

                  AppText {
                    visible: page.despositoVisible
                    text: qsTr("Motivo")
                    font.pixelSize: sp(12)

                    //fontFamily: geoFont
                  }

                  AppTextField {
                      visible: page.despositoVisible
                    id: motivoRD
                    Layout.preferredWidth: dp(200)
                    showClearButton: true
                    font.pixelSize: sp(14)
                    backgroundColor: "white"
                    borderColor: Theme.tintColor
                    borderWidth:  dp(2)
                    //echoMode: TextInput.Password
                  }

                  AppText {
                    visible: page.despositoVisible
                    text: qsTr("F. Pago ")
                    font.pixelSize: sp(12)

                    //fontFamily: geoFont
                  }

                  ComboBox {
                      visible: page.despositoVisible
                      id: list_view1
                      width: motivoRD.width
                      height: dp(50)

                     model: [ "CCAR","CASH","CHEC"] ;
                      //model : botonesTender;
                  }

                  Column {
                    Layout.fillWidth: true
                    Layout.columnSpan: 2
                    Layout.topMargin: dp(12)
                    visible: page.despositoVisible
                    // buttons
                    AppButton {
                        id:aceptarRD
                      text: "Aceptar"
                      flat: false
                      fontCapitalization: Font.MixedCase
                      backgroundColor: "#4a576c"
                      backgroundColorPressed: "#d6d6d6"
                      anchors.horizontalCenter: parent.horizontalCenter
                      fontBold: false
                      //fontFamily: geoFont
                      onClicked: {

                          var myObject = {} ;
                         // myObject = xmlModel.get( list_view1.currentIndex ) ;
                          myObject.hasData = true ;
                          myObject.isValid = true ;
                          myObject.TY_TND=list_view1.currentText;
                          myObject.amount = montoRD.text ; // Este es el monto depositado
                          console.debug(myObject.amount + page.operacion_especial +" OtrasFormasPago.js readXML myObject.TY_TND "+ list_view1.currentText  +" "+ list_view1.currentIndex);
                          myObject.forma_de_pago = myObject.TY_TND;
                          myObject.concepto =motivoRD.text;
                          myObject.operacion=page.operacion_especial;
                          funciones.add_tilltender(myObject);
                           motivoRD.text="";
                          montoRD.text="";
                          page.despositoVisible=false;
                       }//if onclicked
                    }
                    AppButton{
                        id:cancelbuttonRD
                      text: "Cancelar"
                      flat: false
                      fontCapitalization: Font.MixedCase
                      backgroundColor: "#4a576c"
                      backgroundColorPressed: "#d6d6d6"
                      anchors.horizontalCenter: parent.horizontalCenter
                      fontBold: false
                      //fontFamily: geoFont
                      onClicked: {
                          page.despositoVisible=false;
                      }
                    }
                  }
                  }
                    //fin seccion retiro/deposito

                  //seccion cambio de precio
                  property bool cambiopVisible: false
                  Rectangle {
                    id: cambiopf
                    anchors.centerIn: parent
                    color: "#d6d6d6"
                    width: contentcambio.width + dp(48)
                    height: contentcambio.height + dp(80)//16
                    radius: dp(4)
                    visible: page.cambiopVisible
                    border.color: "black"

                    GridLayout {
                    id:contentcambio
                    anchors.centerIn: parent
                    columnSpacing: dp(20)
                    rowSpacing: dp(10)
                    columns: 2

                    AppText {
                      text: qsTr("Precio nuevo")
                      //font.pixelSize: sp(12)

                      //fontFamily: geoFont
                    }

                    AppTextField {
                      id: preciotext
                      Layout.preferredWidth: dp(200)
                      showClearButton: true
                      //font.pixelSize: sp(14)
                      backgroundColor: "white";
                      validator:  DoubleValidator {bottom: 0; top: 9999.99;}
                      borderColor: Theme.tintColor
                      borderWidth: dp(2)
                    }

                    AppText {
                      text: qsTr("Motivo")
                      //font.pixelSize: sp(12)

                      //fontFamily: geoFont
                    }

                    AppTextField {
                      id: motivotext
                      Layout.preferredWidth: dp(200)
                      showClearButton: true
                      //font.pixelSize: sp(14)
                      backgroundColor: "white"
                      borderColor: Theme.tintColor
                      borderWidth:  dp(2)
                      placeholderText: "Motivo del cambio de precio"
                    }

                    AppText {
                      text: qsTr("C. temporal ")
                      //font.pixelSize: sp(12)

                      //fontFamily: geoFont
                    }

                    AppCheckBox {
                        id: temporalP
                        width: motivoRD.width
                        height: dp(50)


                        //model : botonesTender;
                    }

                    AppText {
                      text: qsTr("Datos extras")
                      //font.pixelSize: sp(12)

                      //fontFamily: geoFont
                    }

                    AppTextField {
                      id: observaciontext
                      Layout.preferredWidth: dp(200)
                      showClearButton: true
                      //font.pixelSize: sp(14)
                      backgroundColor: "white"
                      borderColor: Theme.tintColor
                      borderWidth:  dp(2)
                      placeholderText: "Observaciones extras"
                    }


                    Column {
                      Layout.fillWidth: true
                      Layout.columnSpan: 2
                      Layout.topMargin: dp(12)
                      // buttons
                      AppButton {
                          id:aceptarCP
                        text: "Aceptar"
                        flat: false
                        fontCapitalization: Font.MixedCase
                        backgroundColor: "#4a576c"
                        backgroundColorPressed: "#d6d6d6"
                        anchors.horizontalCenter: parent.horizontalCenter
                        fontBold: false
                        //fontFamily: geoFont
                        onClicked: {
                            var myDate = new Date ;

                            var hour = myDate.getHours()   ;
                            var minutes = myDate.getMinutes()   ;
                            var seconds = myDate.getSeconds()    ;

                            var displayDate = (( hour > 9 )  ? hour.toString() : "0" + hour.toString() ) + ":" ;
                            displayDate += (( minutes > 9 )  ? minutes.toString() : "0" + minutes.toString() ) + ":" ;
                            displayDate += ( seconds > 9 )  ? seconds.toString() : "0" + seconds.toString() ;
                            var myObject = {} ;
                            myObject.hora=displayDate;
                            myObject.isValid = true ;
                            if ( motivotext.text.length == 0 )
                            {
                                myObject.razon = "default" ;
                            }
                            else{
                            myObject.razon=motivotext.text;
                            }
                            if ( parseFloat( preciotext.text) <= 0.0000)
                            {
                                return;
                            }
                            myObject.temporal=temporalP.pressed;
                            myObject.permanente=temporalP.pressed;
                            myObject.precio_Nuevo=preciotext.text;
                            myObject.id_itm_ps=d2.iditmps;
                            myObject.id_itm_ps_qfr=d2.iditmpsqfr;
                            var value= funciones.do_Change_price(myObject,ticketIndice);
                            funciones.aplicar_cambios(observaciontext.text,ticketIndice);
                            d3.text=observaciontext.text;
                            sumat.text=value.suma;//total_venta-value.total_impuesto;
                            impuestost.text=value.total_impuesto;
                            totalt.text=value.total_venta;
                            totalticketText.text= value.total_a_pagar;
                            myModelt.remove(ticketIndice);
                            var linea=funciones.getlinea(ticketIndice);
                            myModelt.insert( ticketIndice, linea );
                            page.cambiopVisible=false;
                            return;
                         }//if onclicked
                      }
                      AppButton{
                          id:cancelbuttonCP
                        text: "Cancelar"
                        flat: false
                        fontCapitalization: Font.MixedCase
                        backgroundColor: "#4a576c"
                        backgroundColorPressed: "#d6d6d6"
                        anchors.horizontalCenter: parent.horizontalCenter
                        fontBold: false
                        //fontFamily: geoFont
                        onClicked: {
                            page.cambiopVisible=false;
                        }
                      }
                    }

                    }

                  }
                  Rectangle {
                    id: cambiopheader
                    anchors.bottom: cambiopf.top
                    anchors.left: cambiopf.left
                    color: "#4a576c"
                    width: cambiopf.width
                    height: ingresoS.height + dp(16)
                    radius: dp(4)
                    visible: page.cambiopVisible
                    border.color: "black"

                    AppText {
                      id:tituloCambio
                      anchors.verticalCenter: parent.verticalCenter
                      anchors.left: parent.left
                      anchors.leftMargin: dp(10)
                      text: "Cambio de precio"
                      color: "white"
                      //anchors.bottomMargin: dp(10)

                    }

                  }
                  // seccion cambio de precio


                  //seccion alta express

                     Rectangle {
                       id: altaX
                       anchors.centerIn: parent
                       color: "#d6d6d6"
                       width: contentxx.width + dp(60)
                       height: contentxx.height + dp(80)//16
                       radius: dp(4)
                       visible: visibleAlta
                       border.color: "black"

                       // login form content
                       GridLayout {
                           id: contentxx
                           anchors.centerIn: parent
                           columnSpacing: dp(20)
                           rowSpacing: dp(10)
                           columns: 2
                           // headline


                           // posidentity
                           AppText {
                             text: qsTr("Codigo")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }

                           AppTextField {
                             id: txtCodigoxx
                             Layout.preferredWidth: dp(200)
                             showClearButton: true
                             font.pixelSize: sp(14)
                             backgroundColor: "white";

                             borderColor: Theme.tintColor
                             borderWidth: dp(2)
                           }

                           AppText {
                             text: qsTr("Nombre")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }

                           AppTextField {
                             id: txtNombrexx
                             Layout.preferredWidth: dp(200)
                             showClearButton: true
                             font.pixelSize: sp(14)
                             backgroundColor: "white";

                             borderColor: Theme.tintColor
                             borderWidth: dp(2)
                           }


                           XmlListModel {
                               id: impuestosgenerales

                                query: "/impuestos/impuesto"

                                XmlRole { name: "id_gp_tx" ; query: "id_gp_tx/string()" }
                                XmlRole { name: "nm_ru_tx" ; query: "nm_ru_tx/string()" }



                                   onStatusChanged: {

                                    if ( status == XmlListModel.Null )
                                    {
                                        console.debug( "Status = NULL ") ;
                                        return ;
                                    }

                                    if ( status == XmlListModel.Ready  )
                                    {

                                        if(count > 0){
                                            var myObject = new Object
                                            //myListModel2.clear();
                                            console.debug("impuesttos "+count)
                                            impuesttos = new Array;

                                            for( var i = 0 ; i < impuestosgenerales.count ; i++ )
                                            {
                                                myObject =impuestosgenerales.get( i ) ;

                                                var newObject = new Object ;

                                                 newObject.id_gp_tx = myObject.id_gp_tx ;
                                                 newObject.nm_ru_tx =  myObject.nm_ru_tx ;

                                                //console.debug( "nm_ru_tx = " + newObject.id_gp_tx ) ;
                                                //console.debug( "nm_ru_tx = " + newObject.nm_ru_tx ) ;


                                                 impuesttos.push(myObject.nm_ru_tx+" "  ) ;
                                                 myListModel2.append({'text': myObject.nm_ru_tx});
                                            }

                                        }
                                        return ;

                                    }

                                    if ( status == XmlListModel.Loading )
                                    {
                                        console.debug( "AltaExpress.qml onStatusChanged Status = Loading ") ;
                                        return ;
                                    }

                                    if ( status == XmlListModel.Error )
                                    {
                                        console.debug( "AltaExpress.qml onStatusChanged Status = Error = " + xmlModel.errorString()) ;
                                        return ;
                                    }
                                }
                           }

                           XmlListModel {
                               id: categoriasgenerales

                                query: "/categorias/categoria"

                                XmlRole { name: "id_mrhrc_gp" ; query: "id_mrhrc_gp/string()" }
                                XmlRole { name: "nm_mrhrc_gp" ; query: "nm_mrhrc_gp/string()" }
                                XmlRole { name: "id_gp_tx" ; query: "id_gp_tx/string()" }
                                XmlRole { name: "nm_ru_tx" ; query: "nm_ru_tx/string()" }
                                XmlRole { name: "food_stamp" ; query: "food_stamp/string()" }



                                   onStatusChanged: {

                                    if ( status == XmlListModel.Null )
                                    {
                                        console.debug( "Status = NULL ") ;
                                        return ;
                                    }

                                    if ( status == XmlListModel.Ready  )
                                    {

                                        if(count > 0){
                                            var myObject = new Object
                                            //myListModel3.clear();
                                            console.debug("cattegorias "+count)
                                            cattegorias = new Array;

                                            for( var i = 0 ; i < categoriasgenerales.count ; i++ )
                                            {
                                                myObject = categoriasgenerales.get( i ) ;

                                                var newObject = new Object ;

                                                 newObject.id_mrhrc_gp = myObject.id_mrhrc_gp ;
                                                 newObject.nm_mrhrc_gp =  myObject.nm_mrhrc_gp ;
                                                 newObject.id_gp_tx =  myObject.id_gp_tx ;
                                                 newObject.nm_ru_tx =  myObject.nm_ru_tx ;
                                                newObject.food_stamp =  myObject.food_stamp ;

                                                 cattegorias.push( myObject.nm_mrhrc_gp+" " ) ;//en ambas estaba myobject
                                                 myListModel3.append({'text': myObject.nm_mrhrc_gp+" "});
                                        }
                                        return ;
                                        }

                                    }

                                    if ( status == XmlListModel.Loading )
                                    {
                                        console.debug( "Status = Loading ") ;
                                        return ;
                                    }

                                    if ( status == XmlListModel.Error )
                                    {
                                        console.debug( "Status = Error = " + xmlModel.errorString()) ;
                                        return ;
                                    }
                                }
                           }

                           ListModel {
                               id : myListModel2 ;
                           }
                           ListModel {
                               id : myListModel3;
                           }

                           AppText {
                             text: qsTr("Categoria")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }

                           ComboBox{
                             id: txtCategoriaxx
                             Layout.preferredWidth: dp(200)
                             model: myListModel3

                           }

                           AppText {
                             text: qsTr("Impuesto")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }


                               ComboBox{

                                 Layout.preferredWidth: dp(200)
                                 model: myListModel2

                             id: txtImpuestoxx


                           }

                           AppText {
                             text: qsTr("Precio Venta")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }

                           AppTextField {
                             id: txtVentaxx
                             Layout.preferredWidth: dp(200)
                             showClearButton: true
                             font.pixelSize: sp(14)
                             backgroundColor: "white";
                             validator: DoubleValidator{top: 999999.9999 ; bottom: 0.0001; decimals: 4; notation: DoubleValidator.StandardNotation}
                             borderColor: Theme.tintColor
                             borderWidth: dp(2)
                           }

                           AppText {
                             text: qsTr("Granel")
                             font.pixelSize: sp(12)

                             //fontFamily: geoFont
                           }

                           AppCheckBox {
                             id: txtGranelxx
                                 height: dp(50)
                             }

                           // column for buttons, we use column here to avoid additional spacing between buttons
                           Column {
                             Layout.fillWidth: true
                             Layout.columnSpan: 2
                             Layout.topMargin: dp(12)

                             // buttons
                             AppButton {
                                 id:altaAceptar
                               text: "Aceptar"
                               flat: false
                               fontCapitalization: Font.MixedCase
                               backgroundColor: "#4a576c"
                               backgroundColorPressed: "#d6d6d6"
                               anchors.horizontalCenter: parent.horizontalCenter
                               fontBold: false
                               //fontFamily: geoFont
                               onClicked: {
                                   var myObject=new Object;
                                   var myitm=new Object;
                                   //funciones.impresion_dep("Descripción  Unitario  Cant.   Importe\nCHORIZO CHI   1.0000   1.000       1.0\nCHORIZO CHI   1.0000   1.000       1.0\nCHORIZO CHI   1.0000   1.000       1.0\nCHORIZO CHI   1.0000   1.000       1.0\nEfectivo:                      4.00\n                    Subtotal: $         4.00    \n                       Total: $         4.00    \n             Impuesto   0.00%:          0.00    \n             Impuesto   7.00%:          0.00    \n\n"
                                   //            ,1,212,"11:44:00 07/12/2020",1
                                   //            );
                                   var un="";
                                   if(txtGranelxx.checked)
                                      un = "WT";
                                  else
                                      un = "UN";
                                   coneccion.send_message_log_conf("AA,"+principal.settings.getValue("instancia")+"/"+
                                                                   txtNombrexx.text+"/"+categoriasgenerales.get(txtCategoriaxx.currentIndex).food_stamp+"/"+
                                                                   categoriasgenerales.get(txtCategoriaxx.currentIndex).id_mrhrc_gp+"/1/"+
                                                                   impuestosgenerales.get(txtImpuestoxx.currentIndex).id_gp_tx+"/"+impuestosgenerales.get(txtImpuestoxx.currentIndex).id_gp_tx+"/"+
                                                                   txtCodigoxx.text+"/"+txtVentaxx.text+"/"+un
                                                                   +",email,codigo,email,celular,url");

                                  /*

                                       myObject.NM_ITM=txtNombrexx.text;
                                       myObject.DE_ITM=txtNombrexx.text;

                                       myObject.FOOD_STAMP_EX = categoriasgenerales.get(txtCategoriaxx.currentIndex).food_stamp;
                                       myObject.ID_MRHRC_GP =  categoriasgenerales.get(txtCategoriaxx.currentIndex).id_mrhrc_gp;

                                       myObject.ID_STRGRP = LoginProcess.getIdStore();

                                          myObject.ID_GP_TX = impuestosgenerales.get(txtImpuestoxx.currentIndex).id_gp_tx;
                                          myObject.ID_GP_TX_BUY = impuestosgenerales.get(txtImpuestoxx.currentIndex).id_gp_tx;


                                       if(txtGranelxx.checked)
                                         myObject.LU_CNT_SLS_WT_UN = "WT";
                                      else
                                          myObject.LU_CNT_SLS_WT_UN = "UN";

                                       myObject.ID_ITM_PS=txtCodigoxx.text;

                                       myObject.SELL_PRICE=txtVentaxx.text;


                                   }
                               */
                               }

                             }
                             AppButton {
                                 id:altaCancelar
                               text: "Cancelar"
                               flat: false
                               fontCapitalization: Font.MixedCase
                               backgroundColor: "#4a576c"
                               backgroundColorPressed: "#d6d6d6"
                               anchors.horizontalCenter: parent.horizontalCenter
                               fontBold: false
                               //fontFamily: geoFont
                               onClicked: visibleAlta=false
                             }
                            }
                         }

                       }
                     Rectangle {
                       id: altaXh
                       anchors.bottom: altaX.top
                       anchors.left: altaX.left
                       color: "#4a576c"
                       width: altaX.width
                       height: ingresoX.height + dp(16)
                       radius: dp(4)
                       visible: visibleAlta

                       border.color: "black"

                       AppText {
                         id:ingresoX
                         anchors.verticalCenter: parent.verticalCenter
                         anchors.left: parent.left
                         anchors.leftMargin: dp(10)
                         //fontSize: sp(0)
                         text: "Alta expres"
                         color: "white"
                       }
                     }

                  //fin secion alta express

                  //seccion de ventas en espera
                  property bool ventasSVisible: false
                  property var listaComboVentas: []
                  Rectangle {
                    id: ventaS
                    anchors.centerIn: parent
                    color: "#d6d6d6"
                    width: contentVentasS.width + dp(48)
                    height: contentVentasS.height + dp(40) +botonesVS.height//16
                    radius: dp(4)
                    visible: page.ventasSVisible
                    border.color: "black"

                    ComboBox{
                        id:contentVentasS
                        width: dp(300)
                        model:page.listaComboVentas
                        anchors.left: parent.left
                        anchors.leftMargin: dp(10)
                        anchors.top: parent.top
                        anchors.topMargin: dp(10)
                    }

                    Column {
                      id:botonesVS
                      anchors.topMargin: dp(10)
                      anchors.horizontalCenter: contentVentasS.horizontalCenter
                      anchors.top: contentVentasS.bottom
                      // buttons
                      AppButton {
                          id:aceptarVS
                        text: "Aceptar"
                        flat: false
                        fontCapitalization: Font.MixedCase
                        backgroundColor: "#4a576c"
                        backgroundColorPressed: "#d6d6d6"
                        anchors.horizontalCenter: parent.horizontalCenter
                        fontBold: false
                        //fontFamily: geoFont
                        onClicked: {
                            page.ventasSVisible=false;
                            console.log(contentVentasS.currentIndex);

                            funciones.waitSaleRecover(contentVentasS.currentIndex);
                            var Totales = funciones.getTotales();
                            sumat.text=Totales.Suma;//total_venta-value.total_impuesto;
                            impuestost.text=Totales.Impuesto;
                            totalt.text=Totales.Total;
                            totalticketText.text= Totales.APagar;

                            var rowelement = new Object;
                            console.debug("Display.qml recuperavtaEspera Numero de Lineas: "+funciones.getNumeroLineas());
                            for( var  i = 0 ; i < funciones.getNumeroLineas() ; i++  )
                            {
                                console.debug("Display.qml recuperavtaEspera "+i);
                                rowelement = funciones.getlinea(i);
                                console.debug("Display.qml recuperavtaEspera "+rowelement);
                                myModelt.set(i, rowelement);
                            }

                         }//if onclicked
                      }
                      AppButton{
                          id:cancelbuttonVS
                        text: "Cancelar"
                        flat: false
                        fontCapitalization: Font.MixedCase
                        backgroundColor: "#4a576c"
                        backgroundColorPressed: "#d6d6d6"
                        anchors.horizontalCenter: parent.horizontalCenter
                        fontBold: false
                        //fontFamily: geoFont
                        onClicked: {
                            page.ventasSVisible=false;
                        }
                      }
                    }


                  }
                  Rectangle {
                    id: ventaSheader
                    anchors.bottom: ventaS.top
                    anchors.left: ventaS.left
                    color: "#4a576c"
                    width: ventaS.width
                    height: ingresoS.height + dp(16)
                    radius: dp(4)
                    visible: page.ventasSVisible
                    border.color: "black"

                    AppText {
                      anchors.verticalCenter: parent.verticalCenter
                      anchors.left: parent.left
                      anchors.leftMargin: dp(10)
                      text: "Ventas en espera"
                      color: "white"
                      //anchors.bottomMargin: dp(10)

                    }

                  }
                  //fin seccion de ventas en espera
        }
    }

    Connections{
        /* signals del websocket_syncronizador
    void setInstancia(int instancia);
    void loginf(int instancia,int tienda);
    void confirmado();
    void instalacionCompleta(int instancia,tienda);
        */
        target:coneccion
        onSetsyncronizacion:{
            //esta vuelta se da porque no puede iniciar settings con la base de datos vacia
            //mas que nada es para las instalaciones nuevas
            //la pantalla siempre tiene la instancia y  la tienda disponibles, el c++ los toma de la bd
            var mensaje="N,"+principal.settings.getValue("tienda")+","+principal.settings.getValue("instancia")+",x";
            console.debug("inicia syncronizacion "+mensaje);
            coneccion.send_message(mensaje,0);//primera vez

        }

        onLoginf:{
            if(instancia===0){
                NativeDialog.confirm("Error", "Usuario o contraseña incorrecto", function(ok) {
                                                 if(ok) {}
                                               })
            }
            else{
                console.debug("instancia "+instancia+" tienda "+tienda);
            principal.settings.setValue("instancia",instancia);
            principal.settings.setValue("tienda",tienda);

            principal.usuario=false;
            principal.datos=false;
            principal.login=false;
            principal.codigo=false;
            principal.datos2=true;
            }
        }

        onConfirmado:{
            coneccion.send_message_inst(principal.settings.getValue("instalacionpendiente"));
            onClicked: NativeDialog.confirm("Creando instancia", "Creando instancia, espere un mensaje de confirmacion.", function(ok) {
                if(ok) {}
              })
        }

        onInstalacionCompleta:{
            principal.settings.setValue("instancia",instancia);
            principal.settings.setValue("tienda",tienda);
            console.log("instancia ,"+instancia+", tienda, "+tienda);
            onClicked: NativeDialog.confirm("Exito", "Instancia creada y base de datos lista, iniciala syncronizacion", function(ok) {
                if(ok) {}
              })
            coneccion.send_message("0,"+tienda+","+instancia+",x",0);//primera vez
            coneccion.run_hilo_actualizador();
        }

        onAltaExpress:{
            onClicked: NativeDialog.confirm("Exito", mensaje, function(ok) {
                if(ok) {}
                visibleAlta=false;
              })
        }
    }
    Connections{
        target: funciones
        //void actualiza_Mesa(int lista,QString modelo);
        onActualizaMesa:{
            console.log("cambiando el modelo "+lista)
            if(lista===1){
                modelo1=modelo;

            }
            if(lista===2){
                modelo2=modelo;
            }
            if(lista===3){
                modelo3=modelo;
            }
        }
    }
}
