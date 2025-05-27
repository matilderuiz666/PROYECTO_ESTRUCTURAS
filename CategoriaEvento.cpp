#include "CategoriaEvento.h"

CategoriaEvento::CategoriaEvento() {
    categoria = new string;
    tipo = new string;
    tipoPublico = new string;
    rangoEdad = new string;
    requisitos = new vector<string>();
}

CategoriaEvento::~CategoriaEvento() {
    delete categoria;
    delete tipo;
    delete tipoPublico;
    delete rangoEdad;
    delete requisitos;
}

// Getters
string CategoriaEvento::getCategoria() const { return *categoria; }
string CategoriaEvento::getTipo() const { return *tipo; }
string CategoriaEvento::getTipoPublico() const { return *tipoPublico; }
string CategoriaEvento::getRangoEdad() const { return *rangoEdad; }
vector<string> CategoriaEvento::getRequisitos() const { return *requisitos; }

// Setters
void CategoriaEvento::setCategoria(const string& c) { *categoria = c; }
void CategoriaEvento::setTipo(const string& t) { *tipo = t; }
void CategoriaEvento::setTipoPublico(const string& tp) { *tipoPublico = tp; }
void CategoriaEvento::setRangoEdad(const string& r) { *rangoEdad = r; }
void CategoriaEvento::agregarRequisito(const string& requisito) {
    requisitos->push_back(requisito);
}
