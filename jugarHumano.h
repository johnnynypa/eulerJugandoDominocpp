arrayFicha FichasHumano;

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
        system("clear");
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

void jugarHumano(){
    FichasHumano.reiniciar();
    Ficha uso = seleccionarFicha();
    cout<<"La ficha seleccionada es: "<<"["<<uso->n1<<"|"<<uso->n2<<"]"<<endl;
    // arrayFicha h = fichasDisponibles();
    // cout<<"*******************************"<<endl;
    // usarFicha(h.getByPos(3) );
    // cout<<"*******************************"<<endl;
    // h = fichasDisponibles();
    // usarFicha(h.getByPos(7));
    // cout<<"*******************************"<<endl;
    // h = fichasDisponibles();
    // usarFicha(h.getByPos(14) );
    // cout<<"*******************************"<<endl;
    // h = fichasDisponibles();
}