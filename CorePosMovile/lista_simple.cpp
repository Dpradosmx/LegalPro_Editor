#include "lista_simple.h"
#include <iostream>
#include <QDebug>

lista_simple::lista_simple()
{
    next = NULL;
}

lista_simple::~lista_simple()
{
    if(next!=NULL)
        delete next;
    next=NULL;
}

void lista_simple::append(lista_simple* nodo)
{
    if(next == NULL)
    {
        next = nodo;
    }
    else
    {
        next->append(nodo);
    }
}
