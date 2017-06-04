arrayFicha FichasHumano;
int SegundosHumano;
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

arrayFicha fichasDisponibles(){ //Devuelve cuantas fichas aun no han sido utilizadas
    Nodo aux = cabeza;
    Arista aux2;
    arrayFicha fichas = arrayFicha();
    while(aux != NULL){
        aux2 = aux->ady;
        while(aux2 !=NULL){
            if(aux2->recorrida==false){
                fichas.push(aux->dato,aux2->destino->dato); //Las inserta en el aarray que es retornado
            }
            aux2 = aux2->sgte;
        }
        aux = aux->sgte;
    }
    return fichas;
}

Ficha seleccionarFicha(){
    arrayFicha h = fichasDisponibles();
    int op = 0;
    /* Mostrar */
    do{
        for(int i = 1; i <= h.length; i++){
            cout<<i<<". ["<<h.getByPos(i-1)->n1<<"|"<<h.getByPos(i-1)->n2<<"]"<<endl;
        }
        cout<<"Digite el numero de la ficha deseada"<<endl;
        cin>>op;
        if(cin.fail() || op>h.length || op<1){
            cin.clear();
            cin.ignore(256, '\n');
            op = 0;
            cout<<"Datos incorrectos"<<endl;
            continue;
        }
        return h.getByPos(op-1);
    }while(true);
}

void intercambiar(Ficha uso){
    int aux = uso->n1;
    uso->n1 = uso->n2;
    uso->n2 = aux;
}

void jugando(){
    Ficha uso;
    int op = 0;
    while(true){
        if(FichasHumano.length == 28){
            cout<<" * * * * Terminaste * * * * "<<endl;
            if(FichasHumano.getByPos(0)->n1 == FichasHumano.ultimo()->n2 ){
                cout<<"Hiciste camino Perfecto"<<endl;
            }else{
                cout<<"Hiciste camino Imperfecto"<<endl;
            }
            break;
        }
        system("clear");
        for(int i = 1; i <= FichasHumano.length; i++){
            cout<<"["<<FichasHumano.getByPos(i-1)->n1<<"|"<<FichasHumano.getByPos(i-1)->n2<<"]-";
        }
        cout<<endl<<"____________________________________________________"<<endl;
        uso = seleccionarFicha();
        cout<<"La ficha seleccionada es: "<<"["<<uso->n1<<"|"<<uso->n2<<"]"<<endl;
        if(!FichasHumano.ultimo()){ //Si es la primera ficha
            //Preguntar en que direccion la usará;
            cout<<"Seleccione como la usará"<<endl;
            cout<<"1. ["<<uso->n1<<"|"<<uso->n2<<"]    2. ["<<uso->n2<<"|"<<uso->n1<<"]"<<endl;
            cin>>op;
            if(cin.fail()){
                cin.clear();
                cin.ignore(256, '\n');
                op = 1;
            }
            if(op == 2){
                intercambiar(uso);
            }

            usarFicha(uso);
            FichasHumano.pushFicha(uso);
            continue;
        }
        if(uso->n1 == FichasHumano.ultimo()->n2){ // Si es consecuente
            usarFicha(uso);
            FichasHumano.pushFicha(uso);
        }else{
            if(uso->n2 == FichasHumano.ultimo()->n2){
                intercambiar(uso);
                usarFicha(uso);
                FichasHumano.pushFicha(uso);
            }else{
                cout<<"Perdiste"<<endl;
                cout<<"La ficha seleccionada no continua el ciclo "<<endl;
                // system("pause");
                break;
            }
        }

    }
}

void jugarHumano(){
    time_t t_ini, t_fin;
    FichasHumano.reiniciar();
    t_ini = time(0);
    jugando();
    t_fin = time(0);

    cout<<"Tu tiempo fue: "<<t_fin-t_ini<<" segundos"<<endl<<endl;
    SegundosHumano = t_fin-t_ini;
    desmarcarTodasHumano();
}

// FichasHumano.reiniciar();
//     clock_t t_ini, t_fin;
//     double secs;

//     t_ini = clock();
//     jugando();
//     t_fin = clock();

//     secs = (double)(t_fin - t_ini) / 1000;
//     cout<<secs * 1000.0<<" milisegundos\n"<<endl;
    
//     desmarcarTodasHumano();