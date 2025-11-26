#include "Comun.h"

Comun::Comun(long ci, std::string nom, float cuota, std::string dom, Entrenador *ent, float ext) : Socio(ci, nom, cuota, dom, ent), extra(ext) {}

Comun::~Comun(){}

float Comun::getExtra() const{
    return extra;
}

float Comun::calcularCuota(int mes) const{
    float base = getCuotaBase();
    float cuota = 0;

    if (extra > base * 0.75) {
        cuota = extra;
    } else if (extra <= base * 0.25) {
        cuota = base + extra / 2;
    } else {
        cuota = base + extra;
    }

    if (mes == 1 || mes == 2) {
        cuota *= 0.8;
    }

    return cuota;
}

TipoSocio Comun::getTipo() const{
    return TipoSocio::COMUN;
}

std::string Comun::toString() const {
    std::stringstream st;

    st << "Tipo: Comun"
        << ", Cedula: " << getCedula()
        << ", Nombre: " << getNombre();

    return st.str();
}

std::string Comun::toStringCompleto() const {
    std::stringstream st;

    st << toString()
        << ", Cuota Base: " << getCuotaBase()
        << ", Domicilio: " << getDomicilio()
        << ", Extra: " << extra
        << "\nEntrenador: " << Socio::getEntrenador()->toString();

    return st.str();
}
