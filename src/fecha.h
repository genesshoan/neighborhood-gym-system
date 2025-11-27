#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <cstdlib>

class Fecha {
    private:

        // Tabla de días por mes (no bisiesto). Usar `Fecha::diasMes` desde los métodos.
        static constexpr int diasMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int dia, mes, anio;

    public:

        /*
        Descripción: Constructor por defecto. Inicializa la fecha a 1/1/2000.
        */
        Fecha ();

        /*
        Descripción: Constructor común. Inicializa la fecha con los valores dados.

        Parámetros:
        - int: día
        - int: mes
        - int: año
        */
        Fecha (int, int, int);

        /*
        Descripción: Constructor copia.
        */
        Fecha (const Fecha&);

        /*
        Descripción: Destructor.
        */
        ~Fecha();

        /*
        Descripción: Obtiene el día.

        Retorna: día (int).
        */
        int getDia () const;

        /*
        Descripción: Obtiene el mes.

        Retorna: mes (int).
        */
        int getMes () const;

        /*
        Descripción: Obtiene el año.

        Retorna: año (int).
        */
        int getAnio () const;

        /*
        Descripción: Avanza la fecha un día.
        */
        void siguiente ();

        /*
        Descripción: Compara si dos fechas son iguales. Si cualquiera de las
        dos fechas no es válida, devuelve false.
        */
        bool operator== (const Fecha &) const;

        /*
        Descripción: Determina si la fecha implícita es anterior a la dada.
        Si alguna de las fechas no es válida, devuelve false.
        */
        bool operator< (const Fecha &) const;
        /*
        Operadores adicionales de comparación.
        */
        bool operator!= (const Fecha &) const;
        bool operator>  (const Fecha &) const;
        bool operator<= (const Fecha &) const;
        bool operator>= (const Fecha &) const;

        /*
        Descripción: Operadores de incremento (prefijo y sufijo).
        */
        Fecha& operator++ ();
        Fecha operator++ (int);

        /*
        Descripción: Suma un número de días y devuelve la fecha resultante.

        Parámetros:
        - int: número de días a sumar (positivo)
        */
        Fecha operator+ (int) const;

        /*
        Descripción: Calcula la diferencia en días (valor absoluto) entre dos fechas.
        */
        int operator- (const Fecha & f) const;

        /*
        Descripción: Indica si la fecha es válida (mes en 1..12 y día dentro
        del rango del mes, considerando años bisiestos).
        */
        bool esValida () const;

        /*
        Descripción: Devuelve la cantidad de días transcurridos desde 1/1/1
        hasta la fecha (útil para calcular diferencias en días entre fechas).
        */
        int cantidadDias() const;

        /*
        Descripción: Indica si el año de la fecha es bisiesto.
        */
        bool esBisiesto() const;

};

#endif