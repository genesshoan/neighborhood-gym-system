#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "TipoError.h"

/*
Clase Error: encapsula un `TipoError` y un mensaje opcional. Las
implementaciones de los métodos están en `Error.cpp`.
*/
class Error {
    private:
        TipoError tipo;
        std::string mensaje;

    public:
    
        /**
         * Constructor desde un valor enumerado `TipoError::Value`.
         * - `t`: tipo de error.
         * - `msg`: mensaje opcional descriptivo.
         */
        Error(TipoError::Value t, const std::string &msg = "");

        /**
         * Constructor por defecto (representa ausencia de error o valor inicial).
         */
        Error();

        /**
         * Destructor.
         */
        ~Error();

        /**
         * Obtiene el `TipoError` asociado al objeto.
         */
        TipoError getTipo() const;

        /**
         * Obtiene el mensaje asociado al error (puede estar vacío).
         */
        std::string getMensaje() const;

        /**
         * Representación legible del resultado/error, por ejemplo:
         * "Resultado[EXITOSO]: mensaje" o "Resultado[ARGUMENTO_INVALIDO]".
         */
        std::string toString() const;
};

#endif