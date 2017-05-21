#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "ArrayFicha.h"

typedef struct nodo *Nodo;
typedef struct arista *Arista;


    struct nodo{
        int dato;
        nodo *sgte; 
        arista *ady; //Puntero a la lista de sus aristas
    };

    struct arista{
        nodo *destino; //puntero al nodo de llegada
        bool recorrida;
        arista *sgte;
    };

    Nodo cabeza; //Primer nodo de la multilista del grafo.

    /*              Crear Nodo                  */
    //////////////////////////////////////////////
    Nodo crearNodo(){
        Nodo n = (struct nodo *)malloc(sizeof(struct nodo));
        n->dato = NULL;
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
        
        if(Origen == Destino){
            return;
        }

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

    void inicializarGrafo(){
        for( int i = 0; i < 7; i++ ){
            insertarNodo(i);
        }
        Nodo aux1 = cabeza;
        Nodo aux2 = cabeza;
        while( aux1 != NULL){
            while( aux2 != NULL ){
                InsertarArista(aux1, aux2);
                aux2 = aux2->sgte;
            }
            aux2 = cabeza;
            aux1 = aux1->sgte;
        }
    }

    void imprimirGrafo(){
        Nodo aux = cabeza;
        Arista aux2;
        while(aux != NULL){
            aux2 = aux->ady;
            printf("[%i]", aux->dato);
            while(aux2 != NULL){
                printf("[%i]", aux2->destino->dato);
                aux2 = aux2->sgte;
            }
            printf("\n");
            aux = aux->sgte;
        }
    }





arrayFicha fichasDisponibles(){
    Nodo aux = cabeza;
    Arista aux2;
    arrayFicha fichas = arrayFicha();
    int i, cont = 0;

    while(aux != NULL){
        aux2 = aux->ady;
        i = 0;
        while(aux2 !=NULL){
            if( i >= cont && aux2->recorrida==false){
                fichas.push(aux->dato,aux2->destino->dato);
            }
            aux2 = aux2->sgte;
            i++;
        }
        aux = aux->sgte;
        cont++;
    }
    return fichas;
}


void menu(){
    int op = 0;

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
                jugarHumano();
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
    printf("\n");
    printf("\n");
    printf("\n");
    menu();
    printf("\n");
    printf("\n");
    return 0;
}