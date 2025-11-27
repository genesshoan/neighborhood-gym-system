#include "TipoError.h"

TipoError::TipoError(Value v) : val(v) {}
TipoError::TipoError() : val(NO_ENCONTRADO) {}

TipoError::~TipoError() {}

std::string TipoError::toString() const {
    switch (val) {
        case EXITOSO:
            return "EXITOSO";
        case NO_ENCONTRADO:
            return "NO ENCONTRADO";
        case ARGUMENTO_INVALIDO:
            return "ARGUMENTO INVALIDO";
        case YA_EXISTE:
            return "YA EXISTE";
        case VACIO:
            return "VACIO";
        default:
            return "DESCONOCIDO";
    }
}

TipoError::Value TipoError::value() const { return val; }