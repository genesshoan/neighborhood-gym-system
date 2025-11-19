#include "fecha.h"

Fecha::Fecha() : dia(1), mes(1), anio(2000) {}

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

Fecha::Fecha(const Fecha& f) : dia(f.dia), mes(f.mes), anio(f.anio) {}

Fecha::~Fecha() {}

int Fecha::getDia () const {
    return dia;
}

int Fecha::getMes () const {
    return mes;
} 

int Fecha::getAnio () const {
    return anio;
}

bool Fecha::esValida() const {
    if (mes < 1 || mes > 12) return false;
    if (dia < 1) return false;

    int maxDia = diasMes[mes - 1];
    if (mes == 2 && esBisiesto()) maxDia = 29;
    return dia <= maxDia;
} 

void Fecha::siguiente () {
    int maxDia = diasMes[mes - 1];
    if (mes == 2 && esBisiesto()) maxDia = 29;

    dia++;
    if (dia > maxDia) {
        dia = 1;
        mes++;
        if (mes > 12) {
            mes = 1;
            anio++;
        }
    }
}

bool Fecha::operator== (const Fecha & f2) const {
    if ((!esValida()) || (!f2.esValida())) return false;
    return dia == f2.dia && mes == f2.mes && anio == f2.anio;
}

bool Fecha::operator< (const Fecha & f2) const {
    if ((!esValida()) || (!f2.esValida())) return false;
    if (anio != f2.anio) return anio < f2.anio;
    if (mes != f2.mes) return mes < f2.mes;
    return dia < f2.dia;
}

Fecha& Fecha::operator++ () {
    this->siguiente();
    return *this;
}

Fecha Fecha::operator++ (int) {
    Fecha temp(*this);
    this->siguiente();
    return temp;
}

Fecha Fecha::operator+ (int dias) const{
    Fecha resu(*this);
    while(dias > 0){
        resu.siguiente();
        dias--;
    }
    return resu;
}

int Fecha::cantidadDias() const {
    // Contar días completos de los años anteriores (anio - 1)
    int y = anio - 1;
    int dias = y * 365 + (y / 4 - y / 100 + y / 400);

    for (int i = 0; i < mes - 1; ++i) {
        dias += diasMes[i];
    }
    if (mes > 2 && esBisiesto()) dias += 1;

    dias += dia;
    return dias;
}

int Fecha::operator- (const Fecha & f) const {
    return abs(cantidadDias() - f.cantidadDias());
}

bool Fecha::esBisiesto() const {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}
