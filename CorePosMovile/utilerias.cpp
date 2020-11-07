#include "utilerias.h"
#include "math.h"
#include <QDebug>

Utilerias::Utilerias()
{

}

Utilerias::~Utilerias()
{

}

QString Utilerias::FormatoNumero(QString sNumber, int enteros, int decimales)
{
    QString sNumberIntPart="";
    QString sNumberDecPart="";
    int posicion;

    posicion = sNumber.indexOf(".",0);
    if (posicion == -1) {sNumberIntPart = sNumber;sNumberDecPart="0";}
    else {sNumberIntPart = sNumber.left(posicion); sNumberDecPart = sNumber.right(sNumber.length()-posicion-1);}
    while (sNumberIntPart.length() < enteros)
    {
        if(sNumberIntPart.length() == 0)
        {
            sNumberIntPart.insert(0,"0");
        }
        else
        {
            sNumberIntPart.insert(0," ");
        }
        //qDebug() << "loginprocess.qpp query "<< sNumberIntPart;
    }
    sNumberIntPart.append(".");
    sNumberIntPart.append(sNumberDecPart);
    while (sNumberIntPart.length()<(enteros+decimales+1))
    {
        sNumberIntPart.append("0");
    }
    return sNumberIntPart;
}

QString Utilerias::FormatoNumero(float fNumber, int enteros, int decimales)
{
    return FormatoNumero(QString::number(redondear(fNumber,decimales)), enteros, decimales);
}

float Utilerias::redondear(double x, int decimal){

    float potencia, potencia1;
    double x1 = x;
    int redondear;

    potencia = pow(10,decimal);
    x = x * potencia;
    redondear = x;
    x = redondear / potencia;


    potencia1 = pow(10,decimal+1);
    x1 = x1 * potencia1;
    redondear = x1;
    x1 = redondear / potencia1;

    x1 = x1 - x;
    x1 = x1 * potencia1; //esto nos arroja un numero entero entre 0 y 9;
    if(x1 >= 4.9)
    {
        x = x + (1 / potencia);
    }
    return x;
}
