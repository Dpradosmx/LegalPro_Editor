#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H


class lista_simple
{
public:
    lista_simple();
    void append(lista_simple* nodo);
    ~lista_simple();
protected:
    lista_simple* next;
};

#endif // LISTA_SIMPLE_H
