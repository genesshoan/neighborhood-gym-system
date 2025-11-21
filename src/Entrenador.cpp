#include "Entrenador.h"

Entrenador::Entrenador(long c, std::string n, float sB, int aC) : Persona(c, n), salarioBase(sB), anioComienzo(aC) {} 
        
Entrenador::~Entrenador() {}
        
float Entrenador::getSalarioBase() const { return salarioBase; }
        
int Entrenador::getAnioComienzo() const { return anioComienzo; }
       
std::string Entrenador::toString() const {
    std::stringstream st;

    st << "Cedula: " << getCedula()
       << ", Nombre: " << getNombre()
       << ", Salario Base: " << getSalarioBase()
       << ", Anio de comienzo: " << getAnioComienzo();

    return st.str();
}