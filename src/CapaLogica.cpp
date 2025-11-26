#include "CapaLogica.h"

bool CapaLogica::esStringValido(std::string str) {
    if (str.empty() || std::all_of(str.begin(), str.end(), [](unsigned char c){ return std::isspace(c); })) {
        return false;
    }
    
    return true;
}

CapaLogica::CapaLogica() : socios(), entrenadores() {}

CapaLogica::~CapaLogica() {}

void CapaLogica::registrarEntrenador(long cedulaIdentidad, std::string nombre, float salario, int anio, Error &error) {
    if (cedulaIdentidad < 0) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cedula no puede ser menor que cero");
        return;
    }

    if (entrenadores.member(cedulaIdentidad)) {
        error = Error(TipoError::YA_EXISTE, "Ya existe el Entrenador en el sistema");
        return;
    }

    if (socios.member(cedulaIdentidad)) {
        error = Error(TipoError::YA_EXISTE, "La cedula pertenece a un socio");
        return;
    }

    if (!esStringValido(nombre)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El nombre no puede ser vacio");
        return;
    }

    if (anio < 0) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El anio proporcionado es invalido");
        return;
    }

    if (salario < 0) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El salario no puede ser menor que cero");
        return;
    }

    error = Error(TipoError::EXITOSO, "Entrenador ingresado con exito");
    entrenadores.insert(new Entrenador(cedulaIdentidad, nombre, salario, anio));
}


void CapaLogica::registrarSocio(long cedulaIdentidad, std::string nombre, float cuotaBase, std::string domicilio, TipoSocio tipoSocio, float extra, float porcentaje, Fecha fechaOtorgada, long ciEnt, Error &error) {
    if (cedulaIdentidad < 0) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cedula del socio no puede ser menor que cero");
        return;
    }
    
    if (socios.member(cedulaIdentidad)) {
        error = Error(TipoError::YA_EXISTE, "Ya existe el socio en el sistema");
        return;
    }

    if (entrenadores.member(cedulaIdentidad)) {
        error = Error(TipoError::YA_EXISTE, "Ya existe la cedula en el sistema y pertenece a un entrenador");
        return;
    }

    if (!entrenadores.member(ciEnt)) {
        error = Error(TipoError::NO_ENCONTRADO, "La cédula proporcionada no pertenece a un entrenador. Por favor proporcione una cédula de entrenador válida");
        return;
    }

    if (cuotaBase <= 0.0f) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La cuota debe ser mayor que cero");
        return;
    }

    if (!esStringValido(nombre)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El nombre no puede ser vacio");
        return;
    }

    if (!esStringValido(domicilio)) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El domicilio no puede ser vacio");
        return;
    }

    Socio *nuevo = nullptr;
    
    switch (tipoSocio) {
    case TipoSocio::COMUN:
            if (extra < 0) {
                error = Error(TipoError::ARGUMENTO_INVALIDO, "El extra no puede ser menor que cero");
                return;
            }

            nuevo = new Comun(cedulaIdentidad, nombre, cuotaBase, domicilio, entrenadores.find(ciEnt), extra);
        break;
    case TipoSocio::BECADO:
            if (porcentaje < 0) {
                error = Error(TipoError::ARGUMENTO_INVALIDO, "El porcentaje no puede ser menor que cero");
                return;
            }

            if (!fechaOtorgada.esValida()) {
                error = Error(TipoError::ARGUMENTO_INVALIDO, "La fecha proporcionada es invalida");
                return;
            }

            nuevo = new Becado(cedulaIdentidad, nombre, cuotaBase, domicilio, entrenadores.find(ciEnt), porcentaje, fechaOtorgada);

        break;
    }

    socios.insert(nuevo);
    error = Error(TipoError::EXITOSO, "Socio registrado con exito");
}

Iterador CapaLogica::listarEntrenadores() {
    return entrenadores.listarEntrenadores();
}

Iterador CapaLogica::listarSocios() {
    return socios.listarSocios();
}

const Socio* CapaLogica::listarSocio(long ci, Error &error){
    if (!socios.member(ci)) {
        error = Error(TipoError::NO_ENCONTRADO, "El socio no pertenece al sistema");
        return nullptr;
    }

    error = Error(TipoError::EXITOSO, "Consulta realizada con exito");
    return socios.find(ci);
}

float CapaLogica::calcularMontoMensualSocio(int mes, long ci, Error &error){
    if (mes < 1 || mes > 12) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El mes proporcionado es invalido");
        return -1;
    }

    if (!socios.member(ci)) {
        error = Error(TipoError::NO_ENCONTRADO, "El Socio no pertenece al sistema");
        return -1;
    }

    error = Error(TipoError::EXITOSO, "Calculo realizado con exito");
    return socios.find(ci)->calcularCuota(mes);
}

float CapaLogica::calcularIngresoMensual(int mes, Error &error) {
    if (mes < 1 || mes > 12) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El mes proporcionado es invalido");
        return -1;
    }

    error = Error(TipoError::EXITOSO, "Calculo realizado con exito");
    return socios.calcularIngresoMensual(mes);
}

int CapaLogica::calcularSociosBecadosFecha(Fecha f, Error &error){
    if (!f.esValida()) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "La fecha proporcionada es invalida");
        return -1;
    }

    error = Error(TipoError::EXITOSO, "Calculo realizado con exito");
    return socios.calcularSociosBecadosFecha(f);
}

void CapaLogica::entrenadoresIngresadosAnio(int anio, float &promedio, int &cant, Error &error){
    if (anio < 0) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El anio proporcionado es invalido");
        return;
    }

    error = Error(TipoError::EXITOSO, "Calculo realizado con exito");
    entrenadores.entrenadoresIngresadosAnio(anio, promedio, cant);
}

const Socio* CapaLogica::socioMayorCuotaMensual(int mes, Error & error){
    if (mes < 1 || mes > 12) {
        error = Error(TipoError::ARGUMENTO_INVALIDO, "El mes proporcionado es invalido");
        return nullptr;
    }

    if (socios.esVacio()) {
        error = Error(TipoError::VACIO, "No hay socios registrados en el sistema");
        return nullptr;
    }

    error = Error(TipoError::EXITOSO, "Calculo realizado con exito");
    return socios.socioMayorCuotaMensual(mes);
}