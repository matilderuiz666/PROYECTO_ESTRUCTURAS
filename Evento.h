#pragma once
#include "string"
#include "Ubicacion.h"
using namespace std;

class Evento {
private:
    string* nombre;
    int* cantidadInvitados;
    string* fecha;
    Ubicacion* ubicacion;
    int* distanciaDestino;
    int* precio;
    string* descripcion;
    string* horaInicio;
    string* horaFinal;
    string* organizador;
    string* estado;
    string* etiqueta;

public:
    Evento();
    ~Evento();

    // Getters
    string getNombre() const;
    int getCantidadInvitados() const;
    string getFecha() const;
    Ubicacion getUbicacion() const;
    int getDistanciaDestino() const;
    int getPrecio() const;
    string getDescripcion() const;
    string getHoraInicio() const;
    string getHoraFinal() const;
    string getOrganizador() const;
    string getEstado() const;
    string getEtiqueta() const;

    // Setters
    void setNombre(const string& nombre);
    void setCantidadInvitados(int cantidad);
    void setFecha(const string& fecha);
    void setUbicacion(const Ubicacion& ubi);
    void setDistanciaDestino(int distancia);
    void setPrecio(int precio);
    void setDescripcion(const string& descripcion);
    void setHoraInicio(const string& horaInicio);
    void setHoraFinal(const string& horaFinal);
    void setOrganizador(const string& organizador);
    void setEstado(const string& estado);
    void setEtiqueta(const string& etiqueta);

    void mostrarEvento() const;
};
