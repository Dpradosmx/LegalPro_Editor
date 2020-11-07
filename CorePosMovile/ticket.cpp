#include "ticket.h"
#include <QSqlError>
#include "settings.h"
#include <qdebug.h>

Ticket::Ticket()
{
    settings.setUp();
}

void Ticket::inicializar(){
    //SyncDatabase basededatos;

    QSqlDatabase sqlda = QSqlDatabase::database("Origen");
    QSqlQuery sqlQuery(sqlda);
    QString query ="Select POSITION1,POSITION2, PIE_PRN1,PIE_PRN2 from retailstore";
    bool ok = sqlQuery.exec( query ) ;
    if (!ok){
        qDebug() << "Ticket.cpp Base de datos cerrada " << sqlda.lastError().text();
    }
    sqlQuery.first();
    encabezado1=sqlQuery.value("POSITION1").toString();
    qDebug() << "Ticket.cpp Base de datos Ok " << encabezado1;
    encabezado2=sqlQuery.value("POSITION2").toString();
    pie1=sqlQuery.value("PIE_PRN1").toString();
    pie2=sqlQuery.value("PIE_PRN2").toString();
}

QString Ticket::text_centrado(QString texto, int tamanobuff){
    int tamanobuff2=tamanobuff-4;//son espacios en blanco
    QString justificado;
    if(tamanobuff2>texto.length()){
        int restante=tamanobuff2-texto.length();
        int centrado=restante/2;
        justificado=texto.rightJustified(texto.length()+centrado+2,' ');
        justificado=justificado.leftJustified(justificado.length(),' ');
    }
    else{

    }
    return justificado;
}

QString Ticket::text_lista(QString texto1, QString valor, int tamanobuff){
    int tamanobuff2=tamanobuff-4;//son espacios en blanco
    QString justificado;
    if(tamanobuff2>texto1.length()+valor.length()){
        int centrado=tamanobuff2/2;
        justificado="  "+texto1.leftJustified(centrado,' ');
        justificado+=valor.rightJustified(centrado+2,' ');
    }
    else{

    }
    return justificado;
}

QString Ticket::text_ticket(QString descripcion,QString cantidad, QString importe, int tamanobuff,QString tx,QString precio_unitario){
    int tamanobuff2=tamanobuff-4;//son espacios en blanco
    int tunitario = 8;
    int tcantidad = 7;
    int timporte = 10;
    int ttx = 2;
    int tespacios = 4;
    QString justificado;
    tamanobuff2=tamanobuff2-tunitario-tcantidad-timporte-ttx-tespacios;//20 es la cantidad perfecta para "cant.  valor"
    justificado=descripcion.leftJustified(tamanobuff2,' ',true);
    justificado+=precio_unitario.leftJustified(tunitario,' ');
    justificado+=cantidad.rightJustified(tcantidad,' ');
    justificado+=importe.rightJustified(timporte,' ',true)+tx;
    return justificado;
}
