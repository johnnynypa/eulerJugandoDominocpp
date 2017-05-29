#include <cstdio>
#include <vector>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>       /* time */

void removerAresta(int u, int v);
void adicionarAresta(int u, int v);

using namespace std;

const int NVertice = 7;
typedef vector<int> VI;
typedef vector<VI> VVI;

typedef struct NO{
	int x;
	int y;
} NO;

int termina = 0;
int NFichas = 0;
VVI grafo;
int V,E;
enum { INF = 1 << 30 };

void imprime(VVI& dist){
	const int V = dist.size();
	for(int i=0;i<V;++i){
		for(int j=0;j<V;++j){
			if(dist[i][j]==INF) cout<<"- ";
			else cout<<dist[i][j]<< " ";
		}
		cout<<endl;
	}
}


/**
 * conta o numero de vizinhos de um grafo nao direcionado
 */
int contaVizinhosDeV(int v){
	int contador = 0;

	for(int i=0;i<V;++i)
	{
		if(grafo[v][i] != INF)
		{ 
			contador++;//v com adjacencia para outro no
		}
	}
	return contador;
}


// deep fisrt search para contar os vertices alcancados apartir de v
int dfsContador(int v, bool visitado[]){
	visitado[v] = true;
	int contador = 0;

	for(int j=0;j<V;++j){
		if (grafo[v][j] != INF && !visitado[j])
			contador += dfsContador(j, visitado);
	}
	return contador;
}

//verifica se u-v nao eh um caminho valido: v eh unico possivel caminho ou nao eh ponte
// The function to check if edge u-v can be considered as next edge in
// Euler Tout
bool ehAdjacenciaValida(int u, int v)
{
	//se v eh o unico caminho possivel
	int cont=0;
	for(int j=0;j<V;++j){
		if (grafo[u][j] != INF)
			cont++;
	}

	if (cont == 1)
		return true;


	//Se nao era unico, entao testa se nao eh ponte

	// Conta quantos vertices alcanca via dfs apartir de u
	bool visitados[V];
	memset(visitados, false, V);
	int cont1 = dfsContador(u, visitados);

	// remove a aresta u-v e conta o alcance sem ele
	removerAresta(u, v);
	memset(visitados, false, V);
	int cont2 = dfsContador(u, visitados);

	//adiciona novamente para poder continuar
	adicionarAresta(u, v);

	// testa se eh ponte: se con1 for maior u-v eh ponte
	return (cont1 > cont2)? false: true;
}

int numAleatorio(){    
    return rand() % 7;
}

void removerAresta(int u, int v)
{
	grafo[u][v]=grafo[v][u]=INF;
}

void RestaurarArista(int u, int v){
	NFichas--;
	grafo[u][v]=grafo[v][u]=0;
}

void adicionarAresta(int u, int v)
{
	grafo[u][v]=grafo[v][u]=1;
}

int contFichas = 0;

void fleury(int u, int ant){
	for(int i = 0; i<1000000; i++){

	}
	if(NFichas>28){ //Si ya hizo 28 fichas
		return;
	}
	int ale = 0;
	bool sw = false;
	int cont = 0;
		while(sw==false){
			ale = numAleatorio();

            //Tratamos de que primero use los dobles
			if(grafo[u][u] != INF && ehAdjacenciaValida(u,u)){
				ale = u;
			}

			sw = grafo[u][ale] != INF && ehAdjacenciaValida(u,ale);
			if(cont == 200){ //Aqui ya debe haber detectado si el vertice es puente
				if(ant!=NULL){
					RestaurarArista(ant, u);
				}
				return;
			}
            //Si logra entrar
			if(sw){	
				cont=0;

				cout << u << "-" << ale << "  ";
				contFichas++;

				NFichas++;
				removerAresta(u, ale);
				termina = ale;
				sw = true;
				fleury(ale, u);
				break;
				return;
			}
			cont++;
		}
		if(ant!=NULL){
			RestaurarArista(ant, u);
		}
		return;
	
}




void IniciandFleury(int inicio1){
	srand(time(NULL));
	while(true){
		V = NVertice;
		V=V+1;
		if(V==0)
            break;
		do{
			contFichas = 0;
			grafo = VVI(V,VI(V,INF));
			for(int i=0;i<V;++i){
				for(int j=0;j<V;++j){
					int c=1;
					if(c==0){
						c = INF;
					}
					grafo[i][j] = c;
				}
			}

			
			NFichas = 0;
			fleury(inicio1, NULL);
			cout<<"Se repite"<<endl;
			if(contFichas>27)
				break;
		}while(true);
		cout<<termina;
		break;
	}
	return;
}