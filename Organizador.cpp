#include "Organizador.h"
#include <iostream>
#include <fstream>

Organizador::Organizador() : Usuario(), cabezaEvento(nullptr) {}

Organizador::Organizador(int idUsuario, string nombre, string correo, string contraseña)
    : Usuario(idUsuario, nombre, correo, contraseña), cabezaEvento(nullptr) {
}

NodoEvento* Organizador::getCabezaEvento() const {
    return cabezaEvento;
}

void Organizador::setCabezaEvento(NodoEvento* nuevoCabeza) {
    cabezaEvento = nuevoCabeza;
}

void Organizador::crearEvento(Evento* evento) {
    NodoEvento* nuevo = new NodoEvento(evento);
    nuevo->setSiguiente(cabezaEvento);
    cabezaEvento = nuevo;

    ofstream archivo("eventos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << evento->getNombre() << "," << evento->getDescripcion() << "\n"; // reemplazá con toString si implementás uno
        archivo.close();
    }
    else {
        cout << "No se pudo guardar el evento." << endl;
    }
}

void Organizador::mostrarEventos() const {
    NodoEvento* actual = cabezaEvento;
    if (!actual) {
        cout << "No tienes eventos creados." << endl;
        return;
    }
    while (actual) {
        Evento* e = actual->getEvento();
        cout << "Evento: " << e->getNombre() << " - " << e->getDescripcion() << endl; // personalizá esto
        actual = actual->getSiguiente();
    }
}

bool Organizador::modificarEvento(int idEvento, Evento* nuevoEvento) {
    NodoEvento* actual = cabezaEvento;
    while (actual) {
        if (actual->getEvento()->getNombre() == nuevoEvento->getNombre()) { // suponiendo nombre como identificador
            *actual->getEvento() = *nuevoEvento;
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

bool Organizador::eliminarEvento(const string& nombreEvento) {
    NodoEvento* actual = cabezaEvento;
    NodoEvento* anterior = nullptr;

    while (actual) {
        if (actual->getEvento()->getNombre() == nombreEvento) {
            if (anterior)
                anterior->setSiguiente(actual->getSiguiente());
            else
                cabezaEvento = actual->getSiguiente();

            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}


void Organizador::guardarEventosEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::out); // sobreescribe el archivo
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de eventos." << endl;
        return;
    }

    NodoEvento* actual = cabezaEvento;
    while (actual != nullptr) {
        Evento* e = actual->getEvento();
        archivo << e->getNombre() << "," << e->getFecha() << "," << e->getHoraInicio() << ",";
        archivo << e->getHoraFinal() << "," << e->getDescripcion() << "," << e->getEstado() << ",";
        archivo << e->getEtiqueta() << "," << e->getCantidadInvitados() << "," << e->getDistanciaDestino() << ",";
        archivo << e->getPrecio() << "," << e->getUbicacion().toString() << "," << e->getOrganizador() << endl;

        actual = actual->getSiguiente();
    }

    archivo.close();
    cout << "Eventos guardados exitosamente en archivo.\n";
}

Organizador::~Organizador() {
    while (cabezaEvento) {
        NodoEvento* temp = cabezaEvento;
        cabezaEvento = cabezaEvento->getSiguiente();
        delete temp;
    }
}
