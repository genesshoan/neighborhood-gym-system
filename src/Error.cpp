#include "Error.h"
#include <sstream>

Error::Error(TipoError::Value t, const std::string &msg) : tipo(t), mensaje(msg) {}

Error::Error() : tipo(TipoError::EXITOSO), mensaje("") {}

Error::~Error() {}

TipoError Error::getTipo() const { return tipo; }

std::string Error::getMensaje() const { return mensaje; }

std::string Error::toString() const {
    std::stringstream ss;
    ss << "Resultado[" << tipo.toString() << "]";
    if (!mensaje.empty()) ss << ": " << mensaje;
    return ss.str();
}
