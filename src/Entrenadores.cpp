#include "Entrenadores.h"

int Entrenadores::h(long cedula) { return cedula % B; }

Entrenadores::Entrenadores() : hash{} {} // para quien lo lea, inicializa todo el array en nullptr

Entrenadores::~Entrenadores() {
    for (int i = 0; i < B; i++) {
        Nodo *aux = hash[i];
        while (aux) {
            Nodo *temp = aux;
            aux = aux->sig;
            delete temp->info; 
            delete temp;    
        }
        hash[i] = nullptr;
    }
}

bool Entrenadores::member(long cedula) {
    Nodo *aux = hash[h(cedula)];

    while (aux) { // si no existe la cubeta no itera, porque si el puntero es null la condicion es falsa, por lo tanto no es necesario chequear previamente
        if (aux->info->getCedula() == cedula) return true;
        aux = aux->sig;
    }
    
    return false;
}
        
void Entrenadores::insert(Entrenador *ent) {
    int cubeta = h(ent->getCedula());
    Nodo *aux = hash[cubeta];

    if (!aux) {
        hash[cubeta] = new Nodo{ ent, nullptr };
        return;
    }

    while (aux->sig) {
        aux = aux->sig;
    }
    aux->sig = new Nodo{ ent, nullptr };
}
        
const Entrenador * Entrenadores::find(long cedula) {
    Nodo *aux = hash[h(cedula)];

    while (aux && aux->info->getCedula() != cedula) {
        aux = aux->sig;
    }

    return aux ? aux->info : nullptr;
}


Iterador Entrenadores::listarEntrenadores() {
    Iterador it;

    for (int i = 0; i < B; i++) {
        Nodo *aux = hash[i];
        
        while (aux) {
            it.insertarPersona(aux->info);
            aux = aux->sig;
        }
    }

    return it;
}

void Entrenadores::entrenadoresIngresadosAnio(int anio, float &promedioSalario, int &cantidadEnt) {
    float totalSalarios = 0;
    cantidadEnt = 0;

    for (int i = 0; i < B; i++) {
        Nodo* aux = hash[i];

        while (aux) {
            if (aux->info->getAnioComienzo() == anio) {
                totalSalarios += aux->info->getSalarioBase();
                cantidadEnt++;
            }
            aux = aux->sig;
        }
    }

    promedioSalario = cantidadEnt > 0 ? totalSalarios / cantidadEnt : 0;
}