#include "Comun.h"

Comun::Comun(long ci, std::string nom, float cuota, std::string dom, Entrenador ent, float ext) : Socio(ci, nom, cuota, dom, ent), extra(ext){}

Comun::~Comun(){}

float Comun::getExtra() const{
    return extra;
}

float Comun::calcularCuota(){
    float base = getCuotaBase();
    float cuota = 0;

    if (extra > base){
        cuota = extra;
    } else if (extra <= base * 0.25){
        cuota = base + (extra / 2);
    } else if (extra <= base * 0.75){
        cuota = base + extra;
    } else {
        cuota = extra;
    }

    if (mes == 1) || (mes == 2){
        cuota = cuota * 0.8;
    }
    return cuota;
    
}

std::string Comun::getTipo(){
    return "Comun";
}

std::string toString() const{
    std::stringstream st;

    st << "Socio Comun"
       << "Cedula" << getCedula()
       << ", Nombre: " << getNombre()
       << ", Cuota Base: " << getCuotaBase()
       << ", Domicilio: " << getDomicilio()
       << ", Extra: " << extra
       << ", Entrenador: " << getEntrenador()->getNombre();

    return st.str();
}
