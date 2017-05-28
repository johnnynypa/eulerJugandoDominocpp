#include <time.h>       /* time */

bool ariDisponible[7];
int iCont = 0;

int numAleatorio(){    
    return rand() % 7;
}

void aristaDisponible(Nodo actual){
    Nodo auxCabeza = cabeza;
    Arista auxA;

    while(auxCabeza){
        if(actual->dato > auxCabeza->dato ){
            auxA = auxCabeza->ady;
            while(auxA){
                if(auxA->destino->dato == actual->dato){
                    (!auxA->recorrida) && (ariDisponible[iCont]= true);
                }
                auxA = auxA->sgte;
            }
        }else{
            break;
        }
        auxCabeza = auxCabeza->sgte;
        iCont++;
    }
    auxA = actual->ady;
    while(auxA){
        (!auxA->recorrida) && (ariDisponible[iCont]=true);
        auxA = auxA->sgte;
        iCont++;
    }
}

void fleury(Nodo actual){
    int ale = numAleatorio(); //Se guarda numero aleatorio
    
    arrayFicha Fichas = fichasDisponibles();
    if( Fichas.length>0){
        aristaDisponible(actual);
        for(int i = 0 ; i<7;i++){
            cout<<i<<": "<<ariDisponible[i]<<endl;
        }
    }
}