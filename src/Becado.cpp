#include "Becado.h"

Becado::Becado(long ci, std::string nom, float cuota, std::string dom, Entrenador *ent, float p, Fecha f) : Socio(ci, nom, cuota, dom, ent), porcentaje(p), fechaOtorgada(f) {}

Becado::~Becado() {}
        
float Becado::getPorcentaje() const { return porcentaje; }

Fecha Becado::getFechaOtorgada() const { return fechaOtorgada; }

float Becado::calcularCuota(int mes) const {
    float base = getCuotaBase();
    float cuota = 0;

    if(fechaOtorgada > Fecha(28, 2, 2025)) {
        cuota = base - (base * porcentaje) / 100.0f;
    } else {
        cuota = base - (base * (porcentaje / 2.0f)) / 100.0f;
    }

    if (mes == 1 || mes == 2) {
        cuota -= (cuota * DESCUENTO_ENERO_FEBRERO) / 100.0f;
    }

    return cuota;
}

TipoSocio Becado::getTipo() const {
    return TipoSocio::BECADO;
}

std::string Becado::toString() const {
    std::stringstream st;

    st << "Tipo: Becado"
        << ", Cedula: " << getCedula()
        << ", Nombre: " << getNombre();

    return st.str();
}

std::string Becado::toStringCompleto() const {
    std::stringstream st;

    st << toString()
        << ", Cuota Base: " << getCuotaBase()
        << ", Domicilio: " << getDomicilio()
        << ", Porcentaje: " << porcentaje
        << ", Fecha: " << fechaOtorgada.getDia() 
        << " / " << fechaOtorgada.getMes() 
        << " / " << fechaOtorgada.getAnio()
        << "\nEntrenador: " << Socio::getEntrenador()->toString();

    return st.str();
}