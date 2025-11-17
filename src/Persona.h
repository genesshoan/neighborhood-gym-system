#ifndef _Persona_h_
#define _Persona_h_

#include <string>

class Persona {
private:
    long cedula;
    std::string nombre;

public:
    Persona(long ci, std::string nom);
    long getCedula() const;
    std::string getNombre() const;
    virtual std::string toString() const = 0; 
    virtual ~Persona() {} 
};

#endif