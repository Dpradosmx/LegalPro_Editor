#ifndef UTILERIAS_H
#define UTILERIAS_H
#include <QObject>
#include <QString>

class Utilerias
{
public:
    Utilerias();
    ~Utilerias();
    QString FormatoNumero(float fNumber, int enteros, int decimales);
    QString FormatoNumero(QString sNumber, int enteros, int decimales);
    float redondear(double x, int decimal);
};

#endif // UTILERIAS_H
