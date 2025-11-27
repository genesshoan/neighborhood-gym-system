#ifndef _Menu_h_
#define _Menu_h_

#include "CapaLogica.h"

/*
Clase `Menu`: capa de interacción por consola que presenta el menú al usuario
y delega operaciones a `CapaLogica`. Las funciones `opcion*` implementan
cada acción del menú y realizan validación mínima de entrada.
*/
class Menu {
    private:

        CapaLogica sistema;

        bool esNumero(std::string);
        bool pedirNumero(const std::string &, std::string &);
        void listarIterador(Iterador &);
        int pedirOpcion();
        void opcionRegistrarEntrenador();
        void opcionRegistrarSocio();
        void opcionListarEntrenadores();
        void opcionListarSocios();
        void opcionListarSocio();
        void opcionCalcularCuota();
        void opcionCalcularIngresoMensual();
        void opcionContarBecadosFecha();
        void opcionEntrenadoresIngresadosAnio();
        void opcionSocioMayorCuota();

    public:

        /*
         * Constructor y destructor.
         */
        Menu();
        ~Menu();

        /**
         * Inicia el bucle interactivo del menú y procesa órdenes del usuario.
         */
        void ejecutar();

};

#endif