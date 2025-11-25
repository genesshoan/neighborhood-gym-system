#ifndef SOCIOS_H
#define SOCIOS_H

#include "Socio.h"
#include "Iterador.h"
#include "Fecha.h"
#include "Becado.h"

class Socios{
    private:
    
        struct Nodo{
            Socio *info;
            Nodo *hizq;
            Nodo *hder;
        };

        Nodo *abb;

        void destruir(Nodo *);
        bool member(Nodo *, long);
        void insert(Nodo* &, Socio *);
        Socio * find(Nodo *, long);
        void listarSocios(Nodo *, Iterador &);
        float calcularIngresoMensual(Nodo *, int);
        int calcularSociosBecadosFecha(Nodo *,Fecha);
        void socioMayorCuotaMensual(Nodo *, int, Socio* &);
        
    public:
    
        Socios();
        ~Socios();
        bool member(long);
        void insert(Socio *);
        const Socio * find(long);
        Iterador listarSocios();
        float calcularIngresoMensual(int);
        int calcularSociosBecadosFecha(Fecha);
        bool esVacio();
        Socio * socioMayorCuotaMensual(int);
        
};

#endif