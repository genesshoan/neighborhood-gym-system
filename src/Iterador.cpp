#include "Iterador.h"

Iterador::Iterador() : prim(nullptr), actual(nullptr), ult(nullptr) {}

Iterador::~Iterador() {
    while (prim) {
        Nodo *aux = prim->sig;
        delete prim;
        prim = aux;
    }
}

void Iterador::insertarPersona(Persona * per) {
    Nodo *nuevo = new Nodo;
    nuevo->info = per;
    nuevo->sig = nullptr;

    if (!prim) {
        prim = nuevo;
        actual = nuevo;
        ult = nuevo;
    } else {
        ult->sig = nuevo;
        ult = nuevo;
    }
}

bool Iterador::hayPersonas() { return actual != nullptr; }

const Persona* Iterador::siguientePersona() { 
    if (!actual) return nullptr;

    const Persona *resu = actual->info;
    actual = actual->sig;
    
    return resu; 

}