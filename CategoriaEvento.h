#pragma once
#include <string>
#include <vector>
using namespace std;

class CategoriaEvento {
private:
    string* categoria;
    string* tipo;
    string* tipoPublico;
    string* rangoEdad;
    vector<string>* requisitos;

public:
    CategoriaEvento();
    ~CategoriaEvento();

    // Getters
    string getCategoria() const;
    string getTipo() const;
    string getTipoPublico() const;
    string getRangoEdad() const;
    vector<string> getRequisitos() const;

    // Setters
    void setCategoria(const string& categoria);
    void setTipo(const string& tipo);
    void setTipoPublico(const string& tipoPublico);
    void setRangoEdad(const string& rangoEdad);
    void agregarRequisito(const string& requisito);
};
