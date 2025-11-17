#ifndef ENTRENADOR_H
#define ENTRENADOR_H

#include "Persona.h"

class Entrenador : public Persona {
    private:
        float salarioBase;
        int anioComienzo;

    private:
        Entrenador(long, std::string, float, int);
        ~Entrenador();
        float getSalarioBase() const;
        int getAnioComienzo() const;
        string toString() const;
}

#endif