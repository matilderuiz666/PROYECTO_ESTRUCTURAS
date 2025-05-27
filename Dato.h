#pragma once
#include <string>
#include "Ubicacion.h"
using namespace std;

class Dato {
private:
    int idUsuario;
    string nombre;
    string correo;
    string contrasena;
    Ubicacion ubicacion;

public:
    Dato();
    Dato(int id, string nom, string mail, string pass, Ubicacion ubi);

    int getIdUsuario() const;
    string getNombre() const;
    string getCorreo() const;
    string getContrasena() const;
    Ubicacion getUbicacion() const;

    void setIdUsuario(int id);
    void setNombre(string nom);
    void setCorreo(string mail);
    void setContrasena(string pass);
    void setUbicacion(Ubicacion ubi);
};
