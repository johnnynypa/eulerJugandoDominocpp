#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "ArrayFicha.h" //Esta clase es un objeto que facilita el uso de las fichas como un tipo de datos como un array

typedef struct nodo *Nodo;
typedef struct arista *Arista;


struct nodo{ //Nodo del grafo
    int dato;
    nodo *sgte; 
    arista *ady; //Puntero a la lista de sus aristas
};

struct arista{ // comunica con los otros nodos del grafo
    nodo *destino; //puntero al nodo de llegada
    bool recorrida;
    arista *sgte;
};

Nodo cabeza; //Primer nodo de la multilista del grafo.

/*              Crear Nodo                  */
//////////////////////////////////////////////
Nodo crearNodo(){
    Nodo n = (struct nodo *)malloc(sizeof(struct nodo));
    n->dato = (int)NULL;
    n->sgte = NULL;
    n->ady = NULL;
    return n;
}

/*              Crear Arista                  */
//////////////////////////////////////////////
Arista crearArista(){
    Arista n = (struct arista *)malloc(sizeof(struct arista));
    n->destino = NULL;
    n->recorrida = false;
    n->sgte = NULL;
    return n;
}

/*              Insertar Arista             */
//////////////////////////////////////////////
void InsertarArista(Nodo &Origen, Nodo &Destino){
    Arista nueva = crearArista();
    Arista aux = Origen->ady;
    nueva->destino = Destino;
    
    // if(Origen == Destino){
    //     return;
    // }

    if(Origen->ady == NULL){
        Origen->ady = nueva;    
    }else{
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = nueva;
    }
}

/*              Insertar Nodo               */
//////////////////////////////////////////////
void insertarNodo(int dato){
    Nodo nuevo = crearNodo();
    Nodo aux;
    nuevo->dato = dato;

    if(cabeza == NULL){
        cabeza = nuevo; //Si la lista esta vacia
    }else{
        aux = cabeza;
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
    }
    // printf("Nodo insertado \n");
}

void inicializarGrafo(){ //Esta funcion inicializa el grafo como no dirigido
    for( int i = 0; i < 7; i++ ){
        insertarNodo(i);
    }
    int i = 0, cont = 0;
    Nodo aux1 = cabeza;
    Nodo aux2 = cabeza;
    while( aux1 != NULL){
        i = 0;
        while( aux2 != NULL ){
            if(i>= cont)
                InsertarArista(aux1, aux2);
            aux2 = aux2->sgte;
            i++;
        }
        aux2 = cabeza;
        aux1 = aux1->sgte;
        cont++;
    }
}

void imprimirGrafo(){ // Hackea la NASA jejeje
    Nodo aux = cabeza;
    Arista aux2;
    while(aux != NULL){
        aux2 = aux->ady;
        cout<<"["<<aux->dato<<"]";
        while(aux2 != NULL){
            cout<<"["<<aux2->destino->dato<<"]";
            aux2 = aux2->sgte;
        }
        cout<<endl;
        aux = aux->sgte;
    }
}

void fichasDisponibles(){ //Devuelve cuantas fichas aun no han sido utilizadas
    Nodo aux = cabeza;
    Arista aux2;
    arrayFicha fichas = arrayFicha();

    while(aux != NULL){
        aux2 = aux->ady;
        while(aux2 !=NULL){
            if(aux2->recorrida==false){
                fichas.push(aux->dato,aux2->destino->dato); //Las inserta en el aarray que es retornado
                cout<<"["<<aux->dato<<"|"<<aux2->destino->dato<<"]"<<endl; //Esta linea las imprime
            }
            aux2 = aux2->sgte;
        }
        aux = aux->sgte;
    }
    // return fichas;
}

void usarFicha(Ficha f){ 
    //Debe recibir un struct ficha, con los dos numeros ejemplo (2,3), esta ficha ya no estará disponible en el grafo
    Nodo aux = cabeza;
    Arista aux2;
    int mayor, menor;
    if(f->n1 > f->n2){
        mayor = f->n1;
        menor = f->n2;
    }else{
        mayor = f->n2;
        menor = f->n1;
    }
    while(aux != NULL){
        if(aux->dato == menor){
            aux2 = aux->ady;
            while( aux2 != NULL){
                if(aux2->destino->dato == mayor){
                    aux2->recorrida = true;
                    break;
                }
                aux2 = aux2->sgte;
            }
        }
        aux = aux->sgte;
    }
}


void menu(){
    int op = 0;
    arrayFicha f = arrayFicha();
    while(true){
        cout<<"****************************************************"<<endl;
        cout<<" 1. Jugar Humano"<<endl;
        cout<<" 2. Jugar Maquina"<<endl;
        cout<<" 3. Salir"<<endl;
        cin>>op;
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            op = 4;
        }
        // printf("%i \n", op);
        switch(op){
            case 1:
                // jugarHumano();
                f.push(5,2);
                usarFicha(f.getByPos(0));
                fichasDisponibles();
                break;
            case 2:
                // jugarMaquina();
                break;
            case 3:
                exit(0);
        }
    }
}
int main(){
    inicializarGrafo();
    imprimirGrafo();
    menu();
    return 0;
}