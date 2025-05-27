#pragma once
#include "Usuario.h"
#include "NodoEvento.h"

class Organizador : public Usuario {
private:
    NodoEvento* cabezaEvento;
public:
    Organizador();
    Organizador(int idUsuario, string nombre, string correo, string contraseña);

    void crearEvento(Evento* evento);
    void mostrarEventos() const;
    bool modificarEvento(int idEvento, Evento* nuevoEvento);
    bool eliminarEvento(const string& nombreEvento);
    NodoEvento* getCabezaEvento() const;
    void setCabezaEvento(NodoEvento* nuevoCabeza);
    void guardarEventosEnArchivo(const string& nombreArchivo) const;


    ~Organizador();
};
