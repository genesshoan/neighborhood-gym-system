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
        // Constructor desde el valor del enumerado
        Error(TipoError::Value t, const std::string &msg = "");

        // Constructor desde el wrapper TipoError
        Error(const TipoError &t, const std::string &msg = "");

        TipoError getTipo() const;
        std::string getMensaje() const;
        std::string toString() const;
};

#endif