const int MaxFichas = 28;
typedef struct ficha *Ficha;

struct ficha{ //Etructura ficha, para mover los dos numeros en un solo dato
    int n1;
    int n2;
    ficha *sgte;
};

class arrayFicha{
    private:
        Ficha fichas[MaxFichas];
        Ficha crearFicha(){
            return (struct ficha *)malloc(sizeof(struct ficha));
        }
    public:
        int length; // Campo que indica cuantas fichas hay
        arrayFicha(){
            length = 0;
        }
        void push(int d1, int d2){ // Metodo que inserta un elemento en el array
            if(this->length < MaxFichas){
                Ficha aux = crearFicha();
                aux->n1 = d1;
                aux->n2 = d2;
                this->fichas[length] = aux;
                this->length++;
            }else{
                cout<<"Array lleno"<<endl;
            }
        }
        Ficha getByPos(int p){ // Metodo que retorna una ficha segun la posicion
            return this->fichas[p];
        }
        int tamano(){
            return this->length; // Metodo que indica el tamano del array
        }
        void reiniciar(){
            for(int i = 0; i<28;i++)
                this->fichas[i] = crearFicha();
            this->length = 0;
        }
        Ficha ultimo(){
            return this->fichas[this->length];
        }
};