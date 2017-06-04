#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "ArrayFicha.h" //Esta clase facilita el uso de las fichas como un tipo de datos array

typedef struct nodo *Nodo;
typedef struct arista *Arista;
typedef struct lista *Lista;

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

struct lista{
    Nodo nodo;
    lista *sgte;
    lista *atras;
};

Lista ptr;
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

void desmarcarTodasHumano(){
    Nodo aux = cabeza;
    Arista auxA;
    while(aux){
        auxA = aux->ady;
        while(auxA){
            auxA->recorrida = false;
            auxA = auxA->sgte;
        }
        aux = aux->sgte;
    }
}

#include "jugarHumano.h"
int segundosMaquina;
bool terminado = false;
#include "fleury.h"

void jugarMaquina(){
    time_t t_ini, t_fin;

    t_ini = time(0);
    IniciandFleury( FichasHumano.getByPos(0)->n1 ); //Juega la maquina con el inicio del humano
    t_fin = time(0);

    segundosMaquina = t_fin-t_ini;

    //Mostramos resultado
    
}

void MostrarResultados(){
    system("clear");
    cout<<endl<<"  * * * * Maquina * * * * "<<endl;
    for(int i = 0; i<28; i++){
        cout<<"["<<FichasMaquina.getByPos(i)->n1<<"|"<<FichasMaquina.getByPos(i)->n2<<"]-";
    }
    cout<<endl<<endl;

    cout<<endl<<"  * * * * Tu * * * * "<<endl;
    for(int i = 0; i<28; i++){
        cout<<"["<<FichasHumano.getByPos(i)->n1<<"|"<<FichasHumano.getByPos(i)->n2<<"]-";
    }
    cout<<endl<<endl;
    cout<<"Tu tiempo: "<<SegundosHumano<<endl;
    cout<<"Tiempo PC: "<<segundosMaquina<<endl;
    FichasMaquina.reiniciar();
}

void menu(){
    int op = 0;
    while(true){
        cout<<endl<<endl<<"****************************************************"<<endl;
        cout<<" 1. Jugar"<<endl;
        cout<<" 2. Salir"<<endl;
        cin>>op;
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');
            op = 4;
        }
        switch(op){
            case 1:
                jugarHumano();
                jugarMaquina();
                MostrarResultados();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout<<"Digite una opcion valida"<<endl;
                system("pause");
                break;
        }
    }
}

int main(){
    srand(time(NULL));
    inicializarGrafo();
    imprimirGrafo();
    // cabeza->ady->sgte->recorrida = true;
    menu();
    
    return 0;
}