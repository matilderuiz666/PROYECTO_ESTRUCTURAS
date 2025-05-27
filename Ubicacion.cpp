#include "Ubicacion.h"
#include <cmath>
#include <fstream>
#include <sstream>

Ubicacion::Ubicacion(string pais, string ciudad, string direccion, double latitud, double longitud)
    : pais(pais), ciudad(ciudad), direccion(direccion), latitud(latitud), longitud(longitud) {
}

string Ubicacion::getPais() const { return pais; }
void Ubicacion::setPais(string pais) { this->pais = pais; }

string Ubicacion::getCiudad() const { return ciudad; }
void Ubicacion::setCiudad(string ciudad) { this->ciudad = ciudad; }

string Ubicacion::getDireccion() const { return direccion; }
void Ubicacion::setDireccion(string direccion) { this->direccion = direccion; }

double Ubicacion::getLatitud() const { return latitud; }
void Ubicacion::setLatitud(double latitud) { this->latitud = latitud; }

double Ubicacion::getLongitud() const { return longitud; }
void Ubicacion::setLongitud(double longitud) { this->longitud = longitud; }

double Ubicacion::calcularDistancia(const Ubicacion& otraUbicacion) const {
    double latDiff = latitud - otraUbicacion.getLatitud();
    double lonDiff = longitud - otraUbicacion.getLongitud();
    return sqrt(latDiff * latDiff + lonDiff * lonDiff);
}

string Ubicacion::toString() const {
    stringstream ss;
    ss << pais << "," << ciudad << "," << direccion << "," << latitud << "," << longitud;
    return ss.str();
}

void Ubicacion::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        getline(archivo, pais, ',');
        getline(archivo, ciudad, ',');
        getline(archivo, direccion, ',');
        archivo >> latitud;
        archivo.ignore();
        archivo >> longitud;
        archivo.close();
    }
}

void Ubicacion::guardarEnArchivo(string nombreArchivo) const {
    ofstream archivo;
    archivo.open(nombreArchivo, ios::out);
    if (archivo.is_open()) {
        archivo << toString() << endl;
        archivo.close();
    }
}
