#include <iostream>
#include <malloc.h>
#include <cstdlib>
using namespace std;

struct corredor{
    float vuelta = 0.0; 
    float ultima = 0.0;
    float tiempo = 0.0;
    float t_total = 0.0;
    float promedio = 0.0;
    int ronda = 0;
    int val = 0;
    int numero = 0;
    char nombre[30];
    corredor *sig;
    corredor *izq;
    corredor *der;
    
};

struct promedio {
    float prom;
    promedio *sigp;
    corredor *apunta;
    
};

promedio *cabp, *auxp, *aux2p;
int numerocorredor = 0;
corredor *cab, *aux, *aux2, *raiz;
int per;

int registrar_corredores();
int registrar_vuelta();
int calcular_promedio();
int mostrar_tabla();
int mostrar_corredores();

int main(){

    int opc = 0;
    do{
        

        cout<<endl<<"          TORNEO OLIMPICO"<<endl<<endl;
        cout<<"[1]... Registrar corredor"<<endl;
        cout<<"[2]... Registrar vuelta"<<endl;
        cout<<"[3]... Mostrar corredores"<<endl;
        cout<<"[4]... Ver tabla de clasificacion"<<endl;
        cout<<"[7]... Salir"<<endl;
        cin>>opc;

        switch (opc)
        {
        case 1: registrar_corredores();
            break;
        
        case 2: registrar_vuelta();
            break;

        case 3: mostrar_corredores();
            break;

        case 4: mostrar_tabla();
            break;

        default:
            break;
        }


    }while(opc!=7);
}
int registrar_corredores(){
    aux = (struct corredor*) malloc (sizeof(struct corredor));
    aux->sig = NULL;
    cout<<"Nombre del corredor >>   ";
    cin>>aux->nombre;
    aux->numero = numerocorredor;
    aux->ronda = aux->tiempo = 0;
    numerocorredor++;
    cout<<endl<<"Numero del corredor >>   "<<aux->numero;
    if(!cab){
        cab = aux;
        aux = NULL;
        free(aux);
    } else {
        aux2 = cab;
        while(aux2->sig!=NULL){
            aux2 = aux2->sig;
        }
        aux2->sig=aux;
        aux = aux2 = NULL;
        free(aux);
        free(aux2);
    }

    return 0;
}

int registrar_vuelta(){

    int numcorredor;
    int encontrado = 0;    
    mostrar_corredores();
    cout<<"      REGISTRAR DATOS DE CORREDORES"<<endl<<endl;
    cout<<"Ingrese el numero del corredor >>  ";
    cin>>numcorredor;
    aux = cab;
    while(aux!=NULL){        
        if(aux->numero == numcorredor){            
            encontrado = 1;
            aux->ronda++;
            cout<<endl<<"Corredor >> "<<aux->nombre<<" ("<<aux->ronda<<") >> "<<aux->tiempo<<endl;
            cout<<"Ingrese el tiempo de la ultima vuelta >>  ";
            cin>>aux->tiempo;
            aux->t_total = aux->t_total + aux->tiempo;
            if(aux->ronda>=2){

                calcular_promedio();
            }
        }
        aux = aux->sig;
    }
    if(encontrado==0){
        cout<<"¡EL CORREDOR NO EXISTE!"<<endl;
    }

    return 0;
}

int calcular_promedio(){

    float promedio;
    int encontrado = 0;
    promedio =  aux->t_total/aux->ronda;
    if(cabp==NULL){
        cabp = (struct promedio*) malloc (sizeof(struct promedio));
        cabp->prom = promedio;
        cabp->sigp = NULL;
        cabp->apunta = aux;
    } else {
        aux2p = cabp;
        while(aux2p!=NULL){            
            if(aux2p->apunta==aux) {
                aux2p->prom = promedio;
                encontrado = 1;
            }
            aux2p=aux2p->sigp;
        }
        if(encontrado==0){
            auxp = (struct promedio*) malloc (sizeof(struct promedio));
            auxp->prom = promedio;           
            auxp->apunta = aux;
            auxp->sigp = cabp;
            cabp = auxp;
            auxp = NULL;
            free(auxp);
        }
    }

    return 0;
}

int mostrar_tabla(){

  aux2p = cabp;
  while(aux2p!=NULL){
    cout<<endl<<"Nombre >> "<<aux2p->apunta->nombre<<" corredor numero >> "<<aux2p->apunta->numero<<" Promedio >> "<<aux2p->prom<<endl;
    aux2p = aux2p -> sigp;
  }

  return 0;
}

int mostrar_corredores(){

    cout<<endl<<"   CORREDORES REGISTRADOS"<<endl<<endl;
    for(aux=cab; aux!=NULL; aux=aux->sig){
    cout<<"Nombre del corredor >> "<<aux->nombre<<endl;
    cout<<"Numero del corredor >> "<<aux->numero<<endl;
    cout<<"Ultima vuelta >> "<<aux->tiempo<<endl;
    cout<<"______________________________"<<endl;
    }

    return 0;
}