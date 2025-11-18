#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
private:
    long cedula;
    std::string nombre;

public:
    /*
    Descripción: Constructor de Persona. Inicializa la cédula y el nombre de la persona.

    Parámetros
    - long: cédula de la persona.
    - std::string: nombre de la persona.

    Retorna: Instancia de Persona inicializada.
    */
    Persona(long, std::string);

    /*
    Descripción: Obtiene la cédula de la persona.

    Retorna: cédula (long) de la persona.
    */
    long getCedula() const;

    /*
    Descripción: Obtiene el nombre de la persona.

    Retorna: nombre (std::string) de la persona.
    */
    std::string getNombre() const;

    /*
    Descripción: Genera y devuelve una representación en cadena con la información relevante de la persona.

    Retorna: cadena con la representación textual de la persona.
    */
    virtual std::string toString() const = 0; 

    /*
    Descripción: Destructor virtual de Persona. Permite limpieza correcta en clases derivadas.
    */
    virtual ~Persona();
};

#endif