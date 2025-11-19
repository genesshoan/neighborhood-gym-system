#ifndef ITERADOR_H
#define ITERADOR_H

#include "Persona.h"

/*
Clase Iterador que gestiona una lista enlazada de `Persona` mediante nodos
internos. Proporciona operaciones para insertar personas y recorrer la lista
de manera secuencial.
*/
class Iterador {
    private:

        /* Nodo interno de la lista enlazada */
        struct Nodo {
            Persona *info;
            Nodo *sig;
        };

        Nodo *prim;
        Nodo *actual;
        Nodo *ult;

    public:

        /*
        Descripción: Constructor de Iterador. Inicializa una lista vacía.
        */
        Iterador();

        /*
        Descripción: Destructor de Iterador. Libera la memoria asociada a los nodos
        de la lista.
        */
        ~Iterador();

        /*
        Descripción: Inserta una persona al final de la lista.

        Parámetros
        - Persona*: puntero a la persona a insertar (no se gestiona la propiedad aquí).
        */
        void insertarPersona(Persona *);

        /*
        Descripción: Indica si todavía quedan personas por recorrer.

        Retorna: true si hay al menos una persona disponible, false en caso contrario.
        */
        bool hayPersonas();

        /*
        Descripción: Devuelve la siguiente persona en la secuencia y avanza el
        cursor interno. Puede devolver nullptr si no hay más personas.

        Retorna: puntero constante a Persona o nullptr.
        */
        const Persona* siguientePersona();
        
};

#endif