#ifndef ENTRENADORES_H
#define ENTRENADORES_H

#include "Entrenador.h"
#include "Iterador.h"

/*
Clase Entrenadores: tabla hash simple que almacena punteros a objetos
`Entrenador`. Provee operaciones para insertar, buscar, listar y calcular
estadísticas (por ejemplo promedio de salarios por año de ingreso).
*/
class Entrenadores {
    private:

        // Cantidad de cubetas en la tabla hash
        static constexpr int B = 30;

        /* Nodo interno para listas enlazadas en cada cubeta */
        struct Nodo {
            Entrenador *info;
            Nodo *sig;
        };

        // Array de punteros a nodos (cubetas)
        Nodo * hash[B];

        /*
        Descripción: Función hash privada.

        Parámetros:
        - long: cédula a hashear

        Retorna: índice de cubeta (int)
        */
        int h(long);

    public:

        /*
        Descripción: Constructor. Inicializa la tabla hash vacía.
        */
        Entrenadores();

        /*
        Descripción: Destructor. Libera la memoria de todos los entrenadores
        almacenados en la tabla y destruye los nodos internos. Esta clase
        adquiere la propiedad (ownership) de los punteros `Entrenador*`
        insertados: por lo tanto se encarga de `delete` sobre ellos.
        */
        ~Entrenadores();

        /*
        Descripción: Comprueba si existe un entrenador con la cédula dada en la tabla.

        Parámetros:
        - long: cédula a buscar

        Retorna: true si existe, false en caso contrario.
        */
        bool member(long);

        /*
        Descripción: Inserta un puntero a `Entrenador` en la tabla hash.

        Parámetros:
        - Entrenador*: puntero al entrenador a insertar.
        */
        void insert(Entrenador *);

        /*
        Descripción: Busca y devuelve un puntero constante al entrenador con
        la cédula dada.

        Parámetros:
        - long: cédula a buscar

        Retorna: puntero const a Entrenador si lo encuentra, o nullptr si no existe.
        */
        const Entrenador * find(long);

        /*
        Descripción: Devuelve un `Iterador` con todos los entrenadores
        actualmente almacenados en la tabla (recorrido por cubetas).
        */
        Iterador listarEntrenadores();

        /*
        Descripción: Calcula el promedio salarial y la cantidad de entrenadores
        que ingresaron en un año específico.

        Parámetros:
        - int: año a consultar
        - float&: referencia donde se escribirá el promedio de salario
        - int&: referencia donde se escribirá la cantidad de entrenadores
        */
        void entrenadoresIngresadosAnio(int, float &, int &);

};

#endif