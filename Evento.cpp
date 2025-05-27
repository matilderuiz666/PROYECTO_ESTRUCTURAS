#include "Evento.h"
#include <iostream>

Evento::Evento() {
    nombre = new string;
    cantidadInvitados = new int(0);
    fecha = new string;
    ubicacion = new Ubicacion();
    distanciaDestino = new int(0);
    precio = new int(0);
    descripcion = new string;
    horaInicio = new string;
    horaFinal = new string;
    organizador = new string;
    estado = new string;
    etiqueta = new string;
}

Evento::~Evento() {
    delete nombre;
    delete cantidadInvitados;
    delete fecha;
    delete ubicacion;
    delete distanciaDestino;
    delete precio;
    delete descripcion;
    delete horaInicio;
    delete horaFinal;
    delete organizador;
    delete estado;
    delete etiqueta;
}

// Getters
string Evento::getNombre() const { return *nombre; }
int Evento::getCantidadInvitados() const { return *cantidadInvitados; }
string Evento::getFecha() const { return *fecha; }
Ubicacion Evento::getUbicacion() const { return *ubicacion; }
int Evento::getDistanciaDestino() const { return *distanciaDestino; }
int Evento::getPrecio() const { return *precio; }
string Evento::getDescripcion() const { return *descripcion; }
string Evento::getHoraInicio() const { return *horaInicio; }
string Evento::getHoraFinal() const { return *horaFinal; }
string Evento::getOrganizador() const { return *organizador; }
string Evento::getEstado() const { return *estado; }
string Evento::getEtiqueta() const { return *etiqueta; }

// Setters
void Evento::setNombre(const string& n) { *nombre = n; }
void Evento::setCantidadInvitados(int c) { *cantidadInvitados = c; }
void Evento::setFecha(const string& f) { *fecha = f; }
void Evento::setUbicacion(const Ubicacion& u) { *ubicacion = u; }
void Evento::setDistanciaDestino(int d) { *distanciaDestino = d; }
void Evento::setPrecio(int p) { *precio = p; }
void Evento::setDescripcion(const string& d) { *descripcion = d; }
void Evento::setHoraInicio(const string& h) { *horaInicio = h; }
void Evento::setHoraFinal(const string& h) { *horaFinal = h; }
void Evento::setOrganizador(const string& o) { *organizador = o; }
void Evento::setEstado(const string& e) { *estado = e; }
void Evento::setEtiqueta(const string& e) { *etiqueta = e; }

void Evento::mostrarEvento() const {
    cout << "\n======= EVENTO =======" << endl;
    cout << "Nombre: " << *nombre << endl;
    cout << "Fecha: " << *fecha << endl;
    cout << "Hora de inicio: " << *horaInicio << endl;
    cout << "Hora de finalización: " << *horaFinal << endl;
    cout << "Ubicación: " << endl;
    cout << "  " << ubicacion->toString() << endl;
    cout << "Cantidad de invitados: " << *cantidadInvitados << endl;
    cout << "Precio: $" << *precio << endl;
    cout << "Descripción: " << *descripcion << endl;
    cout << "Organizador: " << *organizador << endl;
    cout << "Estado: " << *estado << endl;
    cout << "Etiqueta: " << *etiqueta << endl;
    cout << "=======================\n" << endl;
}
