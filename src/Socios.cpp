#include "Socios.h"

void Socios::destruir(Nodo * nodo) {
    if (nodo == nullptr) return;

    destruir(nodo->hizq);
    destruir(nodo->hder);

    delete nodo->info;
    delete nodo;
}

bool Socios::member(Nodo * nodo, long c) {
    if (nodo == nullptr) return false;

    if (c == nodo->info->getCedula())
        return true;
    else if (c < nodo->info->getCedula())
        return member(nodo->hizq, c);
    else
        return member(nodo->hder, c);
}

void Socios::insert(Nodo* &nodo, Socio * s){
    if (nodo == nullptr){
        nodo = new Nodo;
        nodo->info = s;
        nodo->hizq = nullptr;
        nodo->hder = nullptr;
    }else if(s->getCedula() < nodo->info->getCedula())
        insert(nodo->hizq, s);
    else
        insert(nodo->hder, s);
}

Socio *Socios::find(Nodo * nodo, long c) {
    if (nodo == nullptr) return nullptr;

    if (c == nodo->info->getCedula())
        return nodo->info;
    else if (c < nodo->info->getCedula())
        return find(nodo->hizq, c);
    else
        return find(nodo->hder, c);
}

void Socios::listarSocios(Nodo * nodo, Iterador &it) {
    if (nodo == nullptr) return;

    listarSocios(nodo->hizq, it);
    it.insertarPersona(nodo->info);
    listarSocios(nodo->hder, it);
}

float Socios::calcularIngresoMensual(Nodo * nodo, int mes) {
    if (nodo == nullptr) return 0.0f;

    return nodo->info->calcularCuota(mes)
     + calcularIngresoMensual(nodo->hizq, mes)
      + calcularIngresoMensual(nodo->hder, mes);
}

int Socios::calcularSociosBecadosFecha(Nodo * nodo, Fecha f) {
    if (nodo == nullptr) return 0;

    int res = 0;
    if (nodo->info->getTipo() == TipoSocio::BECADO) {
        if (((Becado *)nodo->info)->getFechaOtorgada() >= f)
            res = 1;
    }

    return res
            + calcularSociosBecadosFecha(nodo->hder, f)
            + calcularSociosBecadosFecha(nodo->hizq, f);
}

void Socios::socioMayorCuotaMensual(Nodo * nodo, int mes, Socio* &mayorCuota) {
    if (nodo == nullptr)  return;

    socioMayorCuotaMensual(nodo->hizq, mes, mayorCuota);
    socioMayorCuotaMensual(nodo->hder, mes, mayorCuota);

    if (nodo->info->calcularCuota(mes) > mayorCuota->calcularCuota(mes)) 
        mayorCuota = nodo->info;
}

Socios::Socios() : abb(nullptr) {}

Socios::~Socios() {
    destruir(abb);
}

bool Socios::member(long c) {
    return member(abb, c);
}
        
void Socios::insert(Socio *s) {
    insert(abb, s);
} 
        
Socio * Socios::find(long c) {
    return find(abb, c);
}

Iterador Socios::listarSocios() {
    Iterador it;
    listarSocios(abb, it);
    return it;
}
        
float Socios::calcularIngresoMensual(int mes) {
    return calcularIngresoMensual(abb, mes);
} 
        
int Socios::calcularSociosBecadosFecha(Fecha f) {
    return calcularSociosBecadosFecha(abb, f);
}
        
bool Socios::esVacio() {
    return abb == nullptr;
}

Socio * Socios::socioMayorCuotaMensual(int mes) {
    if (esVacio()) return nullptr;
    Socio *mayorCuota = abb->info;
    socioMayorCuotaMensual(abb, mes, mayorCuota);
    return mayorCuota;
}