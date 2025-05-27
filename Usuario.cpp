#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

Usuario::Usuario() : cabeza(nullptr) {}

Usuario::Usuario(int id, string nombre, string correo, string contrasena) {
    // Crea un solo usuario y lo mete como primer nodo
    Dato d;
    d.setIdUsuario(id);
    d.setNombre(nombre);
    d.setCorreo(correo);
    d.setContrasena(contrasena);
    d.setUbicacion(Ubicacion());

    Nodo* nuevo = new Nodo(d);
    cabeza = nuevo;
}

bool Usuario::validarCorreo(string correo) const {
    regex patronCorreo(R"((^[\w\.-]+@[a-zA-Z\d\.-]+\.[a-zA-Z]{2,6}$))");
    return regex_match(correo, patronCorreo);
}

bool Usuario::validarContrasena(string contr) const {
    if (contr.length() < 8) return false;
    bool mayus = false, minus = false, num = false;
    for (char c : contr) {
        if (isupper(c)) mayus = true;
        if (islower(c)) minus = true;
        if (isdigit(c)) num = true;
    }
    return mayus && minus && num;
}

bool Usuario::correoUnico(string correo) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getDato().getCorreo() == correo)
            return false;
        actual = actual->getSiguiente();
    }
    return true;
}

void Usuario::agregarUsuario(Dato nuevoDato) {
    if (!validarCorreo(nuevoDato.getCorreo())) {
        cout << "Correo inválido." << endl;
        return;
    }
    if (!validarContrasena(nuevoDato.getContrasena())) {
        cout << "Contraseña inválida." << endl;   ////////////////////////////////////////7ya esta hciendo esto no? en el main
        return;
    }
    if (!correoUnico(nuevoDato.getCorreo())) {
        cout << "Correo ya registrado." << endl;
        return;
    }

    Nodo* nuevo = new Nodo(nuevoDato);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}

void Usuario::mostrarUsuarios() const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->getDato().getIdUsuario() << endl;
        cout << "Nombre: " << actual->getDato().getNombre() << endl;
        cout << "Correo: " << actual->getDato().getCorreo() << endl;
        cout << "Ubicación: " << actual->getDato().getUbicacion().toString() << endl;
        cout << "--------------------------" << endl;
        actual = actual->getSiguiente();
    }
}

bool Usuario::autenticar(string correo, string contr) const {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getDato().getCorreo() == correo && actual->getDato().getContrasena() == contr)
            return true;
        actual = actual->getSiguiente();
    }
    return false;
}

void Usuario::cargarDesdeArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string temp;
        int id;
        string nombre, correo, contr;
        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, nombre, ',');
        getline(ss, correo, ',');
        getline(ss, contr, ',');

        Ubicacion ubi;
        ubi.cargarDesdeArchivo("ubicacion_" + to_string(id) + ".txt");

        Dato d;
        d.setIdUsuario(id);
        d.setNombre(nombre);
        d.setCorreo(correo);
        d.setContrasena(contr);
        d.setUbicacion(ubi);

        agregarUsuario(d);
    }
    archivo.close();
}

void Usuario::guardarEnArchivo(string nombreArchivo) const {
    ofstream archivo;
    archivo.open(nombreArchivo, ios::out);
    if (!archivo.is_open())
        return;

    Nodo* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->getDato().getIdUsuario() << ","
            << actual->getDato().getNombre() << ","
            << actual->getDato().getCorreo() << ","
            << actual->getDato().getContrasena() << endl;

        actual->getDato().getUbicacion().guardarEnArchivo("ubicacion_" + to_string(actual->getDato().getIdUsuario()) + ".txt");
        actual = actual->getSiguiente();
    }
    archivo.close();
}

Nodo* Usuario::getCabeza() const {
    return cabeza;
}

Usuario::~Usuario() {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->getSiguiente();
        delete temp;
    }
}
