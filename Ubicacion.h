#pragma once
#include <string>
using namespace std;

class Ubicacion {
private:
    string pais;
    string ciudad;
    string direccion;
    double latitud;
    double longitud;

public:
    Ubicacion(string pais = "", string ciudad = "", string direccion = "", double latitud = 0.0, double longitud = 0.0);

    string getPais() const;
    void setPais(string pais);

    string getCiudad() const;
    void setCiudad(string ciudad);

    string getDireccion() const;
    void setDireccion(string direccion);

    double getLatitud() const;
    void setLatitud(double latitud);

    double getLongitud() const;
    void setLongitud(double longitud);

    double calcularDistancia(const Ubicacion& otraUbicacion) const;
    string toString() const;
    void cargarDesdeArchivo(string nombreArchivo);
    void guardarEnArchivo(string nombreArchivo) const;
};
