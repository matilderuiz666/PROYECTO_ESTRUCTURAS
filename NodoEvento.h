#pragma once
#include "Evento.h"

class NodoEvento {
private:
    Evento* evento;
    NodoEvento* siguiente;

public:
    NodoEvento(Evento* e);
    ~NodoEvento();

    Evento* getEvento() const;
    NodoEvento* getSiguiente() const;
    void setSiguiente(NodoEvento* sig);
};
