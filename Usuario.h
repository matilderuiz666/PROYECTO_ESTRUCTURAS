#pragma once
#include <string>
#include "Nodo.h"
using namespace std;

class Usuario {
private:
    Nodo* cabeza;
public:
    Usuario();
    Usuario(int id, string nombre, string correo, string contrasena);
    bool validarCorreo(string correo) const;
    bool validarContrasena(string contrasena) const;
    bool correoUnico(string correo) const;
    void agregarUsuario(Dato nuevoDato);
    void mostrarUsuarios() const;
    bool autenticar(string correo, string contrasena) const;
    void cargarDesdeArchivo(string nombreArchivo);
    void guardarEnArchivo(string nombreArchivo) const;
    Nodo* getCabeza() const;
    ~Usuario();
};
