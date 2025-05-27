#include "Nodo.h"

Nodo::Nodo() : sig(nullptr) {}
Nodo::Nodo(Dato d) : dato(d), sig(nullptr) {}

Dato& Nodo::getDato() { return dato; }
Nodo* Nodo::getSiguiente() const { return sig; }
void Nodo::setSiguiente(Nodo* siguiente) { sig = siguiente; }
