#ifndef BECADO_H
#define BECADO_H

#include "Socio.h"
#include "Fecha.h"
#include <sstream>


/*
Clase Becado que hereda de Socio. Representa a un socio que recibe una beca
o descuento aplicado a su cuota. Incluye el porcentaje de descuento y la
fecha en que se otorgó la beca. Proporciona métodos para obtener los datos
y calcular la cuota aplicando descuentos (con reglas específicas para enero/febrero).
*/
class Becado : public Socio{
    private:
        // Descuento fijo (porcentaje) aplicable en enero y febrero.
        static constexpr float DESCUENTO_ENERO_FEBRERO = 30.0;

        float porcentaje;       // porcentaje de descuento aplicado al socio
        Fecha fechaOtorgada;    // fecha en que se otorgó la beca

    public:

        /*
        Descripción: Constructor de Becado. Inicializa los atributos heredados
        (cédula, nombre, cuota base, domicilio y entrenador) y los específicos
        de la beca (porcentaje y fecha de otorgamiento).

        Parámetros:
        - long: cédula del socio
        - std::string: nombre del socio
        - float: cuotaBase del socio
        - std::string: domicilio del socio
        - Entrenador*: puntero al entrenador asignado
        - float: porcentaje de descuento (0..100)
        - Fecha: fecha en que se otorgó la beca
        */
        Becado(long, std::string, float, std::string, Entrenador *, float, Fecha);

        /*
        Descripción: Destructor de Becado.
        */
        ~Becado();

        /*
        Descripción: Obtiene el porcentaje de descuento de la beca.

        Retorna: porcentaje (float).
        */
        float getPorcentaje() const;

        /*
        Descripción: Obtiene la fecha en que se otorgó la beca.

        Retorna: Fecha (por valor) con la fecha de otorgamiento.
        */
        Fecha getFechaOtorgada() const;

        /*
        Descripción: Calcula la cuota a pagar por el socio aplicando el
        porcentaje de descuento y reglas adicionales (por ejemplo:
        descuento fijo adicional en enero/febrero definido por
        `DESCUENTO_ENERO_FEBRERO`).

        Parámetros:
        - int: unidad/cantidad usada para calcular la cuota (por ejemplo meses)

        Retorna: cuota calculada (float).
        */
        float calcularCuota(int) const;

        /*
        Descripción: Devuelve el tipo de socio como cadena (por ejemplo "Becado").

        Retorna: cadena con el tipo de socio.
        */
        std::string getTipo() const;

        /*
        Descripción: Genera una representación en cadena con la información
        básica del socio (id, nombre, tipo, cuota, etc.).

        Retorna: cadena con la representación textual del socio.
        */
        std::string toString() const;

        /*
        Descripción: Genera una representación en cadena más completa del
        socio, incluyendo información específica de la beca (porcentaje y
        fecha de otorgamiento).

        Retorna: cadena con la representación completa del socio becado.
        */
        std::string toStringCompleto() const;

};

#endif