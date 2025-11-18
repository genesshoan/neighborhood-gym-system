#include "Socio.h"

Socio::Socio(long c, std::string n, float cB, std::string d, Entrenador *e) : Persona(c, n), cuotaBase(cB), domicilio(d), entrenador(e) {}

Socio::~Socio() {}

float Socio::getCuotaBase() const { return cuotaBase; }

std::string Socio::getDomicilio() const { return domicilio; }

const Entrenador* Socio::getEntrenador() const { return entrenador; }