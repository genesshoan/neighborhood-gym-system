#include "Entrenador.h"

Entrenador::Entrenador(long c, std::string n, float sB, int aC) : Persona(c, n), salarioBase(sB), anioComienzo(aC) {} 
        
Entrenador::~Entrenador() {}
        
float Entrenador::getSalarioBase() const { return salarioBase; }
        
int Entrenador::getAnioComienzo() const { return anioComienzo; }
       
std::string Entrenador::toString() const {
    return "Cedula: " + std::to_string(getCedula()) +
           " Nombre: " + getNombre() +
           " Salario Base: " + std::to_string(getSalarioBase()) +
           " Anio de comienzo: " + std::to_string(getAnioComienzo());
}