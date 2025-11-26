#ifndef CAPALOGICA_H
#define CAPALOGICA_H

#include "Socios.h"
#include "Entrenadores.h"
#include "Error.h"
#include "Comun.h"
#include <algorithm>
#include <cctype>

class CapaLogica {
    private:

        Socios socios;
        Entrenadores entrenadores;
        
        bool esStringValido(std::string);

    public:

        /**
         * Constructor por defecto.
         * Inicializa las estructuras internas de `socios` y `entrenadores`.
         */
        CapaLogica();

        /**
         * Destructor.
         * Libera las estructuras internas; las políticas de propiedad
         * se manejan en las clases contenedoras (`Socios` y `Entrenadores`).
         */
        ~CapaLogica();

        /**
         * Registrar un nuevo entrenador en el sistema.
         * Parámetros:
         * - `cedulaIdentidad`: identificador único (debe ser >= 0).
         * - `nombre`: nombre no vacío.
         * - `salario`: salario (>= 0).
         * - `anio`: año de ingreso (>= 0).
         * - `error`: salida por referencia con el resultado de la operación.
         * Comportamiento:
         * - Si los parámetros son inválidos, no modifica el estado y devuelve
         *   el error correspondiente (`ARGUMENTO_INVALIDO`).
         * - Si ya existe un entrenador (o la cédula pertenece a un socio),
         *   devuelve `YA_EXISTE`.
         * - En éxito, inserta el `Entrenador` y setea `EXITOSO`.
         */
        void registrarEntrenador(long cedulaIdentidad, std::string nombre, float salario, int anio, Error &error);

        /**
         * Registrar un nuevo socio en el sistema.
         * Parámetros:
         * - `cedulaIdentidad`: identificador único del socio (>= 0).
         * - `nombre`, `domicilio`: cadenas no vacías.
         * - `cuotaBase`: monto base (> 0).
         * - `tipoSocio`: `TipoSocio::COMUN` o `TipoSocio::BECADO`.
         * - `extra`: utilizado si `COMUN` (>= 0).
         * - `porcentaje`: utilizado si `BECADO` (>= 0).
         * - `fechaOtorgada`: fecha otorgada para becas (debe ser válida si se usa).
         * - `ciEnt`: cédula del entrenador responsable (debe existir en el sistema).
         * - `error`: salida por referencia con el resultado de la operación.
         * Comportamiento:
         * - Valida parámetros y existencia/colisiones de cédulas.
         * - Si el entrenador indicado por `ciEnt` no existe devuelve `NO_ENCONTRADO`.
         * - En caso de parámetros inválidos devuelve `ARGUMENTO_INVALIDO`.
         * - En éxito, crea e inserta el `Socio` correspondiente y setea `EXITOSO`.
         */
        void registrarSocio(long cedulaIdentidad, std::string nombre, float cuotaBase, std::string domicilio, TipoSocio tipoSocio, float extra, float porcentaje, Fecha fechaOtorgada, long ciEnt, Error &error);

        /**
         * Retorna un `Iterador` para recorrer los entrenadores registrados.
         */
        Iterador listarEntrenadores();

        /**
         * Retorna un `Iterador` para recorrer los socios registrados.
         */
        Iterador listarSocios();

        /**
         * Devuelve un puntero constante al `Socio` con la cédula `ci`.
         * Si no existe, retorna `nullptr` y rellena `error` con `NO_ENCONTRADO`.
         */
        const Socio* listarSocio(long ci, Error &error);

        /**
         * Calcula la cuota mensual de un socio identificado por `ci` para el mes `mes`.
         * - `mes` debe estar en 1..12 (si no, se setea `ARGUMENTO_INVALIDO`).
         * - Si el socio no existe, se setea `NO_ENCONTRADO`.
         * - En éxito devuelve la cuota y `EXITOSO` en `error`.
         */
        float calcularMontoMensualSocio(int mes, long ci, Error &error);

        /**
         * Calcula el ingreso total del gimnasio para el mes `mes`.
         * - `mes` debe estar en 1..12.
         * - Devuelve -1 y `ARGUMENTO_INVALIDO` ante mes inválido.
         */
        float calcularIngresoMensual(int mes, Error &error);

        /**
         * Cuenta cuántos socios becados existen cuya fecha de otorgamiento
         * cumple la condición deseada (usa `Fecha`).
         * - En caso de fecha inválida devuelve `ARGUMENTO_INVALIDO`.
         */
        int calcularSociosBecadosFecha(Fecha f, Error &error);

        /**
         * Calcula promedio y cantidad de entrenadores ingresados en `anio`.
         * - `anio` debe ser >= 0.
         * - `promedio` y `cant` se retornan por referencia.
         */
        void entrenadoresIngresadosAnio(int anio, float &promedio, int &cant, Error &error);

        /**
         * Devuelve el `Socio` con mayor cuota mensual para `mes`.
         * - Si no hay socios registrados se setea `VACIO` y retorna `nullptr`.
         * - Si `mes` es inválido se setea `ARGUMENTO_INVALIDO`.
         */
        const Socio* socioMayorCuotaMensual(int mes, Error & error);    
        
};

#endif