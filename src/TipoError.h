#ifndef TIPOERROR_H
#define TIPOERROR_H

#include <string>

/*
Wrapper para el tipo enumerado de errores. Separado en .h/.cpp para facilitar
extensiones y pruebas.
*/
class TipoError {
public:
    enum Value { EXITOSO, NO_ENCONTRADO, ARGUMENTO_INVALIDO, YA_EXISTE, VACIO };

private:
    Value val;

public:
    TipoError(Value v);
    TipoError();

    Value value() const;
    std::string toString() const;

    operator Value() const;
};

#endif
