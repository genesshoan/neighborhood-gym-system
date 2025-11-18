#ifndef SOCIO_H
#define SOCIO_H

#include "Persona.h"
#include "Entrenador.h"

/*
Clase Socio que hereda de Persona. Representa a un socio del gimnasio con información
de cuota base, domicilio y un entrenador asignado. Provee métodos para acceder a
estos datos y operaciones virtuales que deben implementar las subclases.
*/
class Socio : public Persona {
    private:

        float cuotaBase;
        std::string domicilio;
        Entrenador *entrenador;

    public:

        /*
        Descripción: Constructor de Socio. Inicializa los atributos heredados (cédula y nombre)
        y los específicos de Socio (cuotaBase, domicilio y puntero a Entrenador).

        Parámetros
        - long: cédula del socio.
        - std::string: nombre del socio.
        - float: cuotaBase del socio.
        - std::string: domicilio del socio.
        - Entrenador*: puntero al entrenador asignado (puede ser nullptr).

        Retorna: Instancia de Socio inicializada.
        */
        Socio(long, std::string, float, std::string, Entrenador *);

        /*
        Descripción: Destructor de Socio. Se encarga de liberar recursos asociados al objeto si es necesario.
        */
        ~Socio();

        /*
        Descripción: Obtiene la cuota base del socio.

        Retorna: cuotaBase (float) del socio.
        */
        float getCuotaBase() const;

        /*
        Descripción: Obtiene el domicilio del socio.

        Retorna: domicilio (std::string) del socio.
        */
        std::string getDomicilio() const;

        /*
        Descripción: Obtiene el entrenador asignado al socio.

        Retorna: puntero constante a Entrenador asignado (const Entrenador*), puede ser nullptr.
        */
        const Entrenador* getEntrenador() const;

        /*
        Descripción: Calcula la cuota que debe pagar el socio. Método virtual puro que
        debe ser implementado por las clases derivadas para aplicar reglas específicas.

        Retorna: cuota calculada (float).
        */
        virtual float calcularCuota() const = 0;

        /*
        Descripción: Devuelve el tipo de socio (por ejemplo "Activo", "VIP", etc.).
        Método virtual puro que debe implementarse en las subclases.

        Retorna: cadena con el tipo del socio.
        */
        virtual std::string getTipo() const = 0;
};

#endif