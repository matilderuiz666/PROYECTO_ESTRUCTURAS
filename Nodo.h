#pragma once
#include "Dato.h"

class Nodo {
private:
    Dato dato;
    Nodo* sig;

public:
    Nodo();
    Nodo(Dato d);

    Dato& getDato();
    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* siguiente);
};
