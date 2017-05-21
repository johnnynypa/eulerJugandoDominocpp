const int MaxFichas = 21;
typedef struct ficha *Ficha;

struct ficha{
    int n1;
    int n2;
};

class arrayFicha{
    private:
        Ficha fichas[MaxFichas];
        int length;
        Ficha crearFicha(){
            return (struct ficha *)malloc(sizeof(struct ficha));
        }
    public:
        arrayFicha(){
            length = 0;
        }
        void push(int d1, int d2){
            if(length < MaxFichas){
                Ficha aux = crearFicha();
                aux->n1 = d1;
                aux->n2 = d2;
                this->fichas[length] = aux;
                this->length++;
            }else{
                cout<<"Array lleno"<<endl;
            }
        }
        Ficha getByPos(int p){
            return this->fichas[p];
        }
};