#include "NodoEvento.h"

NodoEvento::NodoEvento(Evento* e) : evento(e), siguiente(nullptr) {}

NodoEvento::~NodoEvento() {
    delete evento;
}

Evento* NodoEvento::getEvento() const {
    return evento;
}

NodoEvento* NodoEvento::getSiguiente() const {
    return siguiente;
}

void NodoEvento::setSiguiente(NodoEvento* sig) {
    siguiente = sig;
}
