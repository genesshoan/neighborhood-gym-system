#ifndef ENTRENADOR_H
#define ENTRENADOR_H

#include "Persona.h"
#include <sstream>

/*
Clase Entrenador que hereda de Persona. Representa a un entrenador con información de salario base y año de comienzo, 
y proporciona métodos para acceder a esos datos y obtener una representación en cadena.
*/
class Entrenador : public Persona {
    private:
    
        float salarioBase;
        int anioComienzo;

    public:
        
        /*
        Descripción: Constructor de Entrenador. Inicializa los atributos heredados
        (cédula y nombre) y los específicos de Entrenador (salarioBase y anioComienzo).

        Parámetros:
        - long: cédula del entrenador.
        - std::string: nombre del entrenador.
        - float: salarioBase del entrenador.
        - int: anioComienzo, año en que el entrenador comenzó su actividad.

        Retorna: Instancia de Entrenador inicializada.
        */
        Entrenador(long, std::string, float, int);

        /*
        Descripción: Destructor de Entrenador. Se encarga de liberar recursos asociados al objeto si es necesario.
        */
        ~Entrenador();

        /*
        Descripción: Obtiene el salario base del entrenador.

        Retorna: salarioBase actual del entrenador.
        */
        float getSalarioBase() const;

        /*
        Descripción: Obtiene el año en que el entrenador comenzó su actividad.

        Retorna: anioComienzo del entrenador.
        */
        int getAnioComienzo() const;

        /*
        Descripción: Genera y devuelve una representación en cadena con la
        información relevante del entrenador (por ejemplo id, nombre, salario y año de comienzo).

        Retorna: cadena con la representación textual del entrenador.
        */
        std::string toString() const;
};

#endif