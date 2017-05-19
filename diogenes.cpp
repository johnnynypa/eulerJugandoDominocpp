const int tamMatriz = 7;

int matriz1[tamMatriz][tamMatriz];

void inicializarMatriz(){
    for (int i = 0; i<tamMatriz; i++){
        for ( int j = 0; j<tamMatriz; j++ ){
            if(i == j){
                matriz1[i][j] = 0;
            }else{
                matriz1[i][j] = 1;
            }
        }
    }
}

void imprimirMatriz(){
    for (int i = 0; i<tamMatriz; i++){
        printf("\n");
        for ( int j = 0; j<tamMatriz; j++ ){
            printf(" [%i]" , matriz1[i][j]);
        }
    }
}