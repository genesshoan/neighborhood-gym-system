#include "Menu.h"

bool Menu::esNumero(const std::string &str, bool permitirFloat) {
    if (str.empty()) return false;

    bool tienePunto = false;
    bool tieneDigito = false;

    int i = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) return false;
        i = 1;
    }

    for (; i < str.size(); i++) {
        char c = str[i];

        if (std::isdigit((unsigned char)c)) {
            tieneDigito = true;
        }
        else if (c == '.') {
            if (!permitirFloat) return false;
            if (tienePunto) return false;
            tienePunto = true;
        }
        else {
            return false;
        }
    }

    return tieneDigito;
}


bool Menu::pedirNumero(const std::string &msg, std::string &dest, bool permitirFloat) {
    std::cout << msg;
    std::getline(std::cin, dest);
    return esNumero(dest, permitirFloat);
}

void Menu::listarIterador(Iterador &it) {
    while (it.hayPersonas()) {
        std::cout << it.siguientePersona()->toString() << "\n";
    }
}


int Menu::pedirOpcion() {
    std::string opcion;

    std::cout << "\nMENU\n"
        << "\t1.\t Registrar Entrenador\n"
        << "\t2.\t Registrar Socio\n"
        << "\t3.\t Listar Entrenadores\n"
        << "\t4.\t Listar Socios\n"
        << "\t5.\t Listar Socio\n"
        << "\t6.\t Calcular Cuota Mensual\n"
        << "\t7.\t Ingreso Mensual Total\n"
        << "\t8.\t Contar Becados por Fecha\n"
        << "\t9.\t Entrenadores desde un Anio\n"
        << "\t10.\t Socio con Mayor Cuota\n"
        << "\t0.\t Salir\n"
        << "Seleccione opcion: ";
        
    std::getline(std::cin, opcion);

    return esNumero(opcion, false) ? std::stoi(opcion) : -1;
}

void Menu::opcionRegistrarEntrenador()
{
    std::string ci, nombre, salario, anio;
    Error error;

    std::cout << "\nCedula: ";
    std::getline(std::cin, ci);
    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);
    std::cout << "Salario Base: ";
    std::getline(std::cin, salario);
    std::cout << "Anio de Comienzo: ";
    std::getline(std::cin, anio);

    if (!esNumero(ci, false) || !esNumero(anio, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Cedula y anio deben de ser valores numericos enteros");    
    } else if (!esNumero(salario, true)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El salario base debe de ser un valor numerico");  
    } else {
        sistema.registrarEntrenador(std::stol(ci), nombre, std::stof(salario), std::stoi(anio), error);
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionRegistrarSocio()
{
    std::string ci, ciEnt, nombre, domicilio, cuotaBase, tipo;
    Error error;

    std::cout << "\nCedula: ";
    std::getline(std::cin, ci);

    std::cout << "Nombre: ";
    std::getline(std::cin, nombre);

    if (!pedirNumero("Cuota Base: ", cuotaBase, true)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cuota base debe ser un valor numerico");
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Domicilio: ";
    std::getline(std::cin, domicilio);

    std::cout << "Cedula Entrenador: ";
    std::getline(std::cin, ciEnt);

    if (!esNumero(ci,  false) || !esNumero(ciEnt, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Las cedulas deben ser un valor numerico entero");
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Seleccione tipo:\n\t1.\tComun\n\t2.\tBecado\n";
    std::getline(std::cin, tipo);

    int opcionTipo = esNumero(tipo, false) ? std::stoi(tipo) : -1;

    switch (opcionTipo) {
    case 1:
    {
        std::string extra;
        if (!pedirNumero("Extra: ", extra, true)) {
            error = Error(TipoError::ARGUMENTO_INVALIDO, "El extra debe ser un valor numerico");
        }
        else
        {
            sistema.registrarSocio(
                std::stol(ci), 
                nombre, 
                std::stof(cuotaBase), 
                domicilio,
                TipoSocio::COMUN, 
                std::stof(extra), 
                0.0f, 
                Fecha(),
                std::stol(ciEnt), 
                error
            );
        }
        break;
    }

    case 2:
    {
        std::string porcentaje, dia, mes, anio;

        if (!pedirNumero("Porcentaje: ", porcentaje, true)) {
            error = Error(TipoError::ARGUMENTO_INVALIDO, "El porcentaje debe de ser un valor numerico");
        } else if (!pedirNumero("Dia: ", dia, false) ||
            !pedirNumero("Mes: ", mes, false) ||
            !pedirNumero("Anio: ", anio, false)) {
            error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor ingresados para la fecha son invalidos, deben de ser numeros enteros");
        } else {
            Fecha f(std::stoi(dia), std::stoi(mes), std::stoi(anio));
            sistema.registrarSocio(
                std::stol(ci), 
                nombre, 
                std::stof(cuotaBase), 
                domicilio,
                TipoSocio::BECADO, 
                0.0f, 
                std::stof(porcentaje), 
                f,
                std::stol(ciEnt), 
                error
            );
        }
        break;
    }

    default:
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Tipo de socio no válido");
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionListarEntrenadores() {
    Iterador it = sistema.listarEntrenadores();
    if (!it.hayPersonas()) 
        std::cout << Error(TipoError::VACIO, "No hay entrenadores en el sistema").toString() << "\n";
    else
        listarIterador(it);
}

void Menu::opcionListarSocios() {
    Iterador it = sistema.listarSocios();
    if (!it.hayPersonas()) 
        std::cout << Error(TipoError::VACIO, "No hay socios en el sistema").toString() << "\n";
    else
    listarIterador(it);
}

void Menu::opcionListarSocio() {
    Error error;
    std::string ci;

    if (!pedirNumero("Cedula: ", ci, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cedula debe de ser un valor numerico");
        std::cout << error.toString() << "\n";
        return;
    }

    const Socio* socio = sistema.listarSocio(std::stol(ci), error);

    if (socio != nullptr) {
        std::cout << socio->toStringCompleto() << "\n";
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionCalcularCuota() {
    Error error;
    std::string mes, ci;

    if (!pedirNumero("Mes: ", mes, false) || !pedirNumero("Cedula: ", ci, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico entero para cedula o mes");
    } else {
        float res = sistema.calcularMontoMensualSocio(std::stoi(mes), std::stol(ci), error);
        std::cout << "Cuota del socio para el mes " << mes << ": " << res;
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionCalcularIngresoMensual() {
    Error error;
    std::string mes;

    if (!pedirNumero("Mes: ", mes, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El valor ingresado para mes es invalido, debe ser un numero entero");
        std::cout << error.toString() << "\n";
        return;
    }

    int m = std::stoi(mes);
    float ingreso = sistema.calcularIngresoMensual(m, error);
    if (error.getTipo().value() != TipoError::EXITOSO) {
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Ingreso total del mes " << m << ": " << ingreso << "\n";
}


void Menu::opcionContarBecadosFecha() {
    Error error;
    std::string dia, mes, anio;

    if (!pedirNumero("Dia: ", dia, false) || !pedirNumero("Mes: ", mes, false) || !pedirNumero("Anio: ", anio, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valores numericos invalidos para la fecha, deben ser numeros enteros");
        std::cout << error.toString() << "\n";
        return;
    }
    
    Fecha f(std::stoi(dia), std::stoi(mes), std::stoi(anio));
    int cantidad = sistema.calcularSociosBecadosFecha(f, error);
    if (error.getTipo().value() != TipoError::EXITOSO) {
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Cantidad de socios becados desde fecha " << dia << "/" << mes << "/" << anio << ": " << cantidad << "\n";
}


void Menu::opcionEntrenadoresIngresadosAnio() {
    Error error;
    std::string anio;

    if (!pedirNumero("Anio: ", anio, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico para anio");
        std::cout << error.toString() << "\n";
        return;
    }

    float promedio = 0.0f;
    int cantidad = 0;
    sistema.entrenadoresIngresadosAnio(std::stoi(anio), promedio, cantidad, error);

    if (error.getTipo().value() != TipoError::EXITOSO) {
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Entrenadores ingresados en " << anio << ": cantidad=" << cantidad << ", salario promedio=" << promedio << "\n";
}


void Menu::opcionSocioMayorCuota() {
    Error error;
    std::string mes;

    if (!pedirNumero("Mes: ", mes, false)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico entero para mes");
        std::cout << error.toString() << "\n";
        return;
    }

    int m = std::stoi(mes);
    const Socio* s = sistema.socioMayorCuotaMensual(m, error);

    if (s == nullptr) {
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Socio con mayor cuota en mes " << m << ":\n" << s->toStringCompleto() << "\n";
    std::cout << error.toString() << "\n";
}


Menu::Menu() : sistema() {}

Menu::~Menu() {}

void Menu::ejecutar() {
    int opcion;

    do {
        opcion = pedirOpcion();

        switch (opcion) {
            case 1: opcionRegistrarEntrenador(); break;
            case 2: opcionRegistrarSocio(); break;
            case 3: opcionListarEntrenadores(); break;
            case 4: opcionListarSocios(); break;
            case 5: opcionListarSocio(); break;
            case 6: opcionCalcularCuota(); break;
            case 7: opcionCalcularIngresoMensual(); break;
            case 8: opcionContarBecadosFecha(); break;
            case 9: opcionEntrenadoresIngresadosAnio(); break;
            case 10: opcionSocioMayorCuota(); break;
            case 0: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
}




