#ifndef _Comun_h
#define _Comun_h

#include "Socio.h"
#include "fecha.h"

class Comun : public Socio{
private:
    float extra;
public:
    Comun(long, std::string, float, std::string, Entrenador, float);
    ~Comun();
    float getExtra() const;
    float calcularCuota();
    std::string getTipo();
    std::string toString() const;
};

#endif