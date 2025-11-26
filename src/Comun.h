#ifndef _Comun_h
#define _Comun_h

#include "Socio.h"
#include <sstream>

/*
Clase Comun que hereda de Socio. Representa a un socio de tipo común con un
recargo/extra específico. Implementa el cálculo de cuota según reglas propias
y provee una representación en cadena.
*/
class Comun : public Socio{
    private:

        // Extra (recargo) aplicado al cálculo de la cuota
        float extra;
        
    public:

        /*
        Descripción: Constructor de Comun. Inicializa los atributos heredados
        (cédula, nombre, cuota base, domicilio y entrenador) y el recargo
        específico del socio común.

        Parámetros:
        - long: cédula del socio
        - std::string: nombre del socio
        - float: cuotaBase del socio
        - std::string: domicilio del socio
        - Entrenador*: puntero al entrenador asignado
        - float: extra o recargo aplicado al socio
        */
        Comun(long, std::string, float, std::string, Entrenador *, float);

        /*
        Descripción: Destructor de Comun.
        */
        ~Comun();

        /*
        Descripción: Obtiene el valor del recargo/extra del socio.

        Retorna: extra (float).
        */
        float getExtra() const;

        /*
        Descripción: Calcula la cuota a pagar por el socio aplicando las
        reglas propias del tipo Comun. El parámetro entero puede representar
        meses o alguna unidad definida en la lógica de negocio.

        Parámetros:
        - int: unidad/cantidad usada para calcular la cuota (por ejemplo meses)

        Retorna: cuota calculada (float).
        */
        float calcularCuota(int) const;

        /*
        Descripción: Devuelve el tipo de socio. Para esta clase devuelve
        una cadena representando el tipo (por ejemplo "Comun").

        Retorna: cadena con el tipo de socio.
        */
        TipoSocio getTipo() const;

        /*
        Descripción: Genera y devuelve una representación en cadena con la
        información relevante del socio (incluyendo el extra y datos heredados).

        Retorna: cadena con la representación textual del socio.
        */
        std::string toString() const;

        std::string toStringCompleto() const;

};

#endif