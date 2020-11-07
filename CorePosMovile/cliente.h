#ifndef CLIENTE_H
#define CLIENTE_H
#include <QVariant>
#include <QString>

class Cliente
{
public:
    Cliente();
    Cliente(QVariant wcliente, QVariant wnmcliente);
    int get_idCliente() {return id_cliente;}
    QString get_nmCliente() {return nm_cliente;}
    ~Cliente();
private:
    int id_cliente;
    QString nm_cliente;
};

#endif // CLIENTE_H
