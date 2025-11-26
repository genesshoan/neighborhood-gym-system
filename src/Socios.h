#ifndef SOCIOS_H
#define SOCIOS_H

#include "Socio.h"
#include "Iterador.h"
#include "Fecha.h"
#include "Becado.h"

class Socios{
    private:
    
        /* Nodo de árbol binario que almacena punteros a `Socio` */
        struct Nodo{
            Socio *info;  // invariant: info != nullptr
            Nodo *hizq;
            Nodo *hder;
        };

        // Raíz del árbol binario de búsqueda por cédula
        Nodo *abb;

        // Métodos auxiliares recursivos (privados)
        void destruir(Nodo *);
        bool member(Nodo *, long);
        void insert(Nodo* &, Socio *);
        Socio * find(Nodo *, long);
        void listarSocios(Nodo *, Iterador &);
        float calcularIngresoMensual(Nodo *, int);
        int calcularSociosBecadosFecha(Nodo *,Fecha);
        void socioMayorCuotaMensual(Nodo *, int, Socio* &);
        
    public:
    
        /*
        Clase Socios: árbol binario de búsqueda que gestiona socios del gimnasio
        indexados por cédula.

        Ownership: Esta clase es propietaria de los objetos `Socio*` insertados.
        El destructor liberará (delete) los objetos almacenados en el árbol.
        */
        Socios();

        /*
        Descripción: Destructor. Libera memoria de los nodos y de los objetos
        `Socio*` (ownership asumida por la clase).
        */
        ~Socios();

        /*
        Descripción: Indica si existe un socio con la cédula dada.

        Parámetros:
        - long: cédula a buscar

        Retorna: true si el socio existe, false en caso contrario.
        */
        bool member(long);

        /*
        Descripción: Inserta un socio en el árbol.

        Precondición: no debe existir ya un socio con la misma cédula en el árbol.

        Parámetros:
        - Socio*: puntero al socio a insertar (no debe ser nullptr).
        */
        void insert(Socio *);

        /*
        Descripción: Busca y devuelve un puntero constante al socio con la cédula
        dada.

        Retorna: puntero const a `Socio` si lo encuentra, o `nullptr` si no existe.
        */
        Socio * find(long);

        /*
        Descripción: Devuelve un `Iterador` que itera los socios en orden (in-order).
        */
        Iterador listarSocios();

        /*
        Descripción: Calcula el ingreso mensual total sumando las cuotas de todos
        los socios para el `mes` especificado.

        Precondición: `mes` debe estar en el rango 1..12 según convención.
        */
        float calcularIngresoMensual(int);

        /*
        Descripción: Cuenta la cantidad de socios becados cuya fecha de otorgamiento
        es posterior a la `Fecha` proporcionada.

        Precondición: `f` idealmente debe ser una fecha válida (`f.esValida()`).
        */
        int calcularSociosBecadosFecha(Fecha);

        /*
        Descripción: Indica si el árbol está vacío.
        */
        bool esVacio();

        /*
        Descripción: Devuelve un puntero al socio que tenga la mayor cuota para
        el mes especificado. Si no hay socios, devuelve nullptr.
        */
        Socio * socioMayorCuotaMensual(int);
        
};

#endif