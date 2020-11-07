#include "cliente.h"

Cliente::Cliente()
{

}

Cliente::Cliente(QVariant wcliente, QVariant wnmcliente){
    id_cliente = wcliente.toInt();
    nm_cliente = wnmcliente.toString();
}

Cliente::~Cliente()
{

}

