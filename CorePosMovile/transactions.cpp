#include "transactions.h"

transactions::transactions(QString bsnday,QString ts, int idopr)
{
    dcdybsn=bsnday;
    aitrn="0";
    idopr=idopr;
    tstmstr=ts;
   // tstrnbgn=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tstrnbgn="";
    tstrnend="";
    flcncl="";
    flvd="";
    fltrgtrn="";
    flkeyofl="0";
    xml="";

    settings.setUp();
    sqldatabasecortex =QSqlDatabase::addDatabase("QSQLITE","Origen"); // El acceso es a traves del driver de ODBC
    sqldatabasecortex.setDatabaseName("pruebas");
    if(!sqldatabasecortex.open()){
        qDebug() << "Error syncronizacion 1: "; //<< sqldatabasecortex.lastError();
    }
}

int transactions::terminar_transaccion(){

    tstrnbgn=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tstrnend=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery sqlQuery2( sqldatabasecortex.database("Origen") );
    QString query ="select coalesce(max(ai_trn),0) as trn from transactions where  dc_dy_bsn = '"+dcdybsn+"'";

        bool ok = sqlQuery2.exec( query ) ;
        sqlQuery2.first();
        aitrn =QString::number(sqlQuery2.value("trn").toInt()+1);
        QString query2="insert into transactions values ("+settings.getIdStore()+","+settings.getIdWorkStation()+",'"+dcdybsn+"',"+aitrn+","+idopr+",'"+tstmstr+"','TIEN','"+tstrnbgn+"','"+tstrnend+"',"+flcncl+",0,0,1,'"+xml+"')";
        ok = sqlQuery2.exec( query2 ) ;
    return 1;

}

int transactions::anular_Transaccion(){
    flcncl="1";

}

int transactions::cancelar_transaccion(int id){

    QSqlQuery sqlQuery2( sqldatabasecortex.database("Origen") );
    QString query ="update transacctions set fl_cncl = 1 where ty_trn="+QString::number(id)+" and dc_dy_bsn="+dcdybsn;
    bool ok = sqlQuery2.exec( query ) ;
    terminar_transaccion();
    return 1;
}
