#include "Menu.h"

bool Menu::esNumero(std::string str) {
    if (str.empty()) return false;

    bool tienePunto = false;
    bool tieneDigito = false;

    int i = 0;
    if (str[0] == '-' || str[0] == '+') {
        i = 1;
        if (str.size() == 1) return false;
    }

    for (; i < str.size(); i++) {
        char c = str[i];

        if (std::isdigit((unsigned char)c)) {
            tieneDigito = true;

        } else if (c == '.') {
            if (tienePunto) return false;
            tienePunto = true;

        } else {
            return false;
        }
    }

    return tieneDigito;
}

bool Menu::pedirNumero(const std::string &msg, std::string &dest) {
    std::cout << msg;
    std::getline(std::cin, dest);
    return esNumero(dest);
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

    return esNumero(opcion) ? std::stoi(opcion) : -1;
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

    if (!esNumero(ci) || !esNumero(salario) || !esNumero(anio)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Uno de los valores númericos ingresados no es tal");
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

    if (!pedirNumero("Cuota Base: ", cuotaBase))
    {
        error = Error(TipoError::ARGUMENTO_INVALIDO,
                      "La cuota base debe ser un número");
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Domicilio: ";
    std::getline(std::cin, domicilio);

    std::cout << "Cedula Entrenador: ";
    std::getline(std::cin, ciEnt);

    if (!esNumero(ci) || !esNumero(ciEnt)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Las cédulas deben ser numéricas");
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Seleccione tipo:\n\t1.\tComun\n\t2.\tBecado\n";
    std::getline(std::cin, tipo);

    int opcionTipo = esNumero(tipo) ? std::stoi(tipo) : -1;

    switch (opcionTipo) {
    case 1:
    {
        std::string extra;
        if (!pedirNumero("Extra: ", extra)) {
            error = Error(TipoError::ARGUMENTO_INVALIDO, "El extra debe ser un valor numérico");
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

        if (!pedirNumero("Porcentaje: ", porcentaje) ||
            !pedirNumero("Dia: ", dia) ||
            !pedirNumero("Mes: ", mes) ||
            !pedirNumero("Anio: ", anio)) {
            error = Error(TipoError::ARGUMENTO_INVALIDO, "Valores numéricos inválidos para fecha o porcentaje");
        }
        else
        {
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
        std::cout << Error(TipoError::ARGUMENTO_INVALIDO, "No hay entrenadores en el sistema").toString() << "\n";
    else
        listarIterador(it);
}

void Menu::opcionListarSocios() {
    Iterador it = sistema.listarSocios();
    if (!it.hayPersonas()) 
        std::cout << Error(TipoError::ARGUMENTO_INVALIDO, "No hay socios en el sistema").toString() << "\n";
    else
    listarIterador(it);
}

void Menu::opcionListarSocio() {
    Error error;
    std::string ci;

    if (!pedirNumero("Cedula: ", ci)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cedula debe de ser un valor numerico");
        std::cout << error.toString() << "\n";
        return;
    }

    const Socio* socio = sistema.listarSocio(std::stol(ci), error);

    if (socio != nullptr) {
        std::cout << socio->toStringCompleto();
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionCalcularCuota() {
    Error error;
    std::string mes, ci;

    if (!pedirNumero("Mes: ", mes) || !pedirNumero("Cedula: ", ci)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico para cedula o mes");
    } else {
        sistema.calcularMontoMensualSocio(std::stoi(mes), std::stol(ci), error);
    }

    std::cout << error.toString() << "\n";
}

void Menu::opcionCalcularIngresoMensual() {
    Error error;
    std::string mes;

    if (!pedirNumero("Mes: ", mes)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico para mes");
        std::cout << error.toString() << "\n";
        return;
    }

    int m = std::stoi(mes);
    float ingreso = sistema.calcularIngresoMensual(m, error);
    if (error.getTipo().value() != TipoError::EXITOSO) {
        std::cout << error.toString() << "\n";
        return;
    }

    std::cout << "Ingreso total mes " << m << ": " << ingreso << "\n";
}


void Menu::opcionContarBecadosFecha() {
    Error error;
    std::string dia, mes, anio;

    if (!pedirNumero("Dia: ", dia) || !pedirNumero("Mes: ", mes) || !pedirNumero("Anio: ", anio)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valores numéricos inválidos para la fecha");
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

    if (!pedirNumero("Anio: ", anio)) {
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

    std::cout << "Entrenadores ingresados en " << anio << ": cantidad=" << cantidad << ", promedio salario=" << promedio << "\n";
}


void Menu::opcionSocioMayorCuota() {
    Error error;
    std::string mes;

    if (!pedirNumero("Mes: ", mes)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "Valor no numerico para mes");
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




