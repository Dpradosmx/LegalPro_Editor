#include "lista_impuestos.h"

lista_impuestos::lista_impuestos()
{

}

void lista_impuestos::add_to_list(QString impuesto, double valor, double base, QString tipo){

    QMap<QString,QVariant> temp;
    double total=0;
    double basel=0;
    bool no_cambio = true;//si no se encuentra en la lista

    qDebug() << "lista_impuestos::add_to_list() impuesto: " << impuesto << valor << base << tipo;

    if(impuestos.length()==0){
        temp["base_gravable"] = base;
        temp["impuesto"] = impuesto;
        if(tipo.compare("PE")==0){
            temp["total"]=base*valor/100;}
        if(tipo.compare("FII")==0){
            temp["total"]=valor;
        }
        impuestos.append(temp);
        no_cambio=false;
        qDebug() << "lista_impuestos::add_to_list() base inicial "<<basel;
      }

    else{
        for(int x=0;x<impuestos.length();x++){//barrido para obtener el total

            if(impuestos.at(x)["impuesto"]==impuesto && tipo == "PE"){
               basel=impuestos.at(x)["base_gravable"].toDouble()+base;
               qDebug() << "base "<<basel;
               temp["base_gravable"] = basel;
               temp["impuesto"] = impuesto;
               temp["total"]=basel*valor/100;
               impuestos.removeAt(x);
               impuestos.append(temp);
               no_cambio = false;
            }

            if(impuestos.at(x)["impuesto"]==impuesto && tipo == "FII"){
               basel+=impuestos.at(x)["base_gravable"].toDouble()+base;
               total+=impuestos.at(x)["total"].toDouble()+valor;
               temp["base_gravable"] = basel;
               temp["impuesto"] = impuesto;
               temp["total"]=total;
               impuestos.removeAt(x);
               impuestos.append(temp);
               no_cambio = false;
               qDebug() << "base fii "<<basel;
            }
        }
        if(no_cambio){
            temp["base_gravable"] = base;
            temp["impuesto"] = impuesto;
            if(tipo.compare("PE")==0){
                temp["total"]=base*valor/100;}
            if(tipo.compare("FII")==0){
                temp["total"]=valor;
            }
            impuestos.append(temp);
            qDebug() << "lista_impuestos::add_to_list() base inicial2 "<<basel;
        }
    }
}

void lista_impuestos::add_to_list(QString impuesto, double valor, double base){
    QMap<QString,QVariant> temp;
    double total=0;
    double basel=0;
    bool no_cambio = true;//si no se encuentra en la lista
    if(impuestos.length()==0){
        temp["base_gravable"] = base;
        temp["impuesto"] = impuesto;

        temp["total"]=valor;

        impuestos.append(temp);
        no_cambio=false;
      }

    else{
        for(int x=0;x<impuestos.length();x++){//barrido para obtener el total

            if(impuestos.at(x)["impuesto"]==impuesto){
               basel+=impuestos.at(x)["base_gravable"].toDouble()+base;
               temp["base_gravable"] = basel;
               temp["impuesto"] = impuesto;
               total=impuestos.at(x)["total"].toDouble()+valor;
               temp["total"]=total;
               impuestos.removeAt(x);
               impuestos.append(temp);
               no_cambio = false;
            }
        }
        if(no_cambio){
            temp["base_gravable"] = base;
            temp["impuesto"] = impuesto;

                temp["total"]=base+valor;

            impuestos.append(temp);
        }
    }
}

void lista_impuestos::print(){
    for(int x=0;x<impuestos.length();x++){
        qDebug() << "dato numero " << x+1 <<" base " << impuestos.at(x)["base_gravable"] << " impuesto " << impuestos.at(x)["impuesto"] << " total " << impuestos.at(x)["total"];
    }
}
void lista_impuestos::clear(){
    impuestos.clear();
}



