#include "Persona.h"

Persona::Persona(long ci, std::string nom) : cedula(ci), nombre(nom){}

long Persona::getCedula() const{
    return cedula;
}

std::string Persona::getNombre() const{
    return nombre;
}

Persona::~Persona() {}