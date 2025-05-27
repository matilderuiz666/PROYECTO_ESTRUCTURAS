#include "Dato.h"

Dato::Dato() : idUsuario(0), nombre(""), correo(""), contrasena(""), ubicacion() {}

Dato::Dato(int id, string nom, string mail, string pass, Ubicacion ubi)
    : idUsuario(id), nombre(nom), correo(mail), contrasena(pass), ubicacion(ubi) {
}

int Dato::getIdUsuario() const { return idUsuario; }
string Dato::getNombre() const { return nombre; }
string Dato::getCorreo() const { return correo; }
string Dato::getContrasena() const { return contrasena; }
Ubicacion Dato::getUbicacion() const { return ubicacion; }

void Dato::setIdUsuario(int id) { idUsuario = id; }
void Dato::setNombre(string nom) { nombre = nom; }
void Dato::setCorreo(string mail) { correo = mail; }
void Dato::setContrasena(string pass) { contrasena = pass; }
void Dato::setUbicacion(Ubicacion ubi) { ubicacion = ubi; }
