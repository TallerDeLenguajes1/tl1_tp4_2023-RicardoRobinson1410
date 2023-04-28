#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define TAMA 100

typedef struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} tarea;

struct nodo
{
    tarea dato;
    struct nodo *siguiente;
};
typedef struct nodo *lista;

bool pertenece(lista tareaspendientes, int tareasid);
bool esvacia(lista aux);
void movertareas(lista* tareaspendientes, lista* tareasrealizadas, lista* tareasenproceso, int tareaid);
lista DesenlazarNodo(lista* pendientes);
lista BuscarNodo(lista tareaspendientes, lista tareasrealiazadas, lista tareasenproceso, int i);
tarea CargarTarea();
lista CrearLista();
tarea** CargarPuntero(int cant);
tarea**InicializarNulo(int cant);
void Mostrartarea(tarea aux);
void Mostrartareas(tarea** aux, int cant);
void InsertarPrimero(lista *aux, int i);
void InsertarNodoALista(lista* pendientes, lista nodo);
lista CrearNodo(int i);
void Mostrar(lista aux);
lista realizaTareas(lista *tareaspendientes, lista* tareasrealizadas, lista*tareasenproceso);
void agregarprimero(lista *aux, lista nodo);
void desapuntarnodo(lista* aux, lista nodo);
int main(){
    lista tareasPendientesFinal=CrearLista(); 
    lista tareaspendientes;
    lista tareasrealizadas;
    lista tareasenproceso;
    int seleccion;
     int menu;
     int cant;
     int numtarea;
     int tareaid;
     tarea buscar;
    tareaspendientes = CrearLista();
    tareasrealizadas=CrearLista();
    tareasenproceso=CrearLista();
    printf("Ingrese la cantidad de tareas qeu desea ingresar\n");
    scanf("%d",&cant);
    for(int i=0;i<cant;i++){
        printf("---NODO %d:---------\n",i+1);
        InsertarPrimero(&tareaspendientes, i+1);
    }
    printf("----LISTA CREADA-----\n");
    Mostrar(tareaspendientes);
    printf("-----Indicar tareas pendientes realizadas y en proceso------\n");
    tareasPendientesFinal=realizaTareas(&tareaspendientes,&tareasrealizadas,&tareasenproceso);
    printf("Mostrar tareas pendientes\n");
    Mostrar(tareasPendientesFinal);
    printf("Mostrar tareas realizadas\n");
    Mostrar(tareasrealizadas);
    printf("Mostrar tareas en proceso\n");
    Mostrar(tareasenproceso);
    printf("Ingrese la tarea que desea mover\n");
    scanf("%d",&tareaid);
    movertareas(&tareasPendientesFinal,&tareasrealizadas,&tareasenproceso, tareaid);
    printf("Mostrar tareas pendientes\n");
    Mostrar(tareasPendientesFinal);
    printf("Mostrar tareas realizadas\n");
    Mostrar(tareasrealizadas);
    printf("Mostrar tareas en proceso\n");
    Mostrar(tareasenproceso);
    return 0;
}


lista CrearLista()
{
    lista aux;
    return (NULL);
}

lista BuscarNodo(lista tareaspendientes, lista tareasrealiazadas, lista tareasenproceso, int i){
    int bandera=0;
    while(!esvacia(tareaspendientes)&&bandera==0)
    {
        if(tareaspendientes->dato.TareaID==i){
            bandera=1;
            return(tareaspendientes);
        }
        tareaspendientes=tareaspendientes->siguiente;
    }
    if(bandera==0){
        while(!esvacia(tareasrealiazadas)&&bandera==0){
            if(tareasrealiazadas->dato.TareaID==i){
                bandera==1;
                return(tareasrealiazadas);
            }
            tareasrealiazadas=tareasrealiazadas->siguiente;
        }
    }if(bandera==0){
        while(!esvacia(tareasenproceso)&&bandera==0){
            if(tareasenproceso->dato.TareaID==i){
                bandera==1;
                return(tareasenproceso);
            }
            tareasenproceso=tareasenproceso->siguiente;
        }
    }
    printf("No se encontró el elemento\n");

    
}

void InsertarPrimero(lista *aux, int i)
{
    lista nodo = CrearNodo(i);
    nodo->siguiente=*aux;
    *aux=nodo;
}

void InsertarNodoALista(lista* pendientes, lista nodo){
    nodo->siguiente=*pendientes;
    *pendientes=nodo;
}

bool pertenece(lista tareaspendientes, int tareasid){
    bool bandera=false;
    while(!esvacia(tareaspendientes)){
        if(tareaspendientes->dato.TareaID==tareasid){
            bandera=true;
        }
        tareaspendientes=tareaspendientes->siguiente;
    }
    return(bandera);
}

bool esvacia(lista aux)
{
    if ((aux) == NULL)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void movertareas(lista* tareaspendientes, lista* tareasrealizadas, lista* tareasenproceso, int tareaid)
{
    lista nodo=BuscarNodo(*tareaspendientes,*tareasrealizadas,*tareasenproceso, tareaid);
    if(pertenece(*tareaspendientes, tareaid)){
        desapuntarnodo(tareaspendientes,nodo);
    }else{
        if(pertenece(*tareasrealizadas, tareaid)){
            desapuntarnodo(tareasrealizadas,nodo);
        }else{
            if(pertenece(*tareasenproceso, tareaid)){
                desapuntarnodo(tareasenproceso,nodo);
            }else{
                printf("NO SE ENCUENTRA EL NODO\n");
            }
        }
    }
    int elegir;
    printf("Ingrese 0 si quiere marcar tarea como pendiente, 1 si quiere marcarla como realizada y 2 en proceso\n");
    scanf("%d",&elegir);
    if(pertenece(*tareaspendientes, tareaid)){
        
    }
    switch (elegir)
    {
    case 0:
        if(!pertenece(*tareaspendientes,tareaid)){
            agregarprimero(tareaspendientes,nodo);  
        }
        break;
    case 1:
        if(!pertenece(*tareasrealizadas, tareaid)){
            agregarprimero(tareasrealizadas,nodo);
        }
        break;
    case 2:
        if(!pertenece(*tareasenproceso, tareaid)){
            agregarprimero(tareasenproceso,nodo);
        }
        break;
    }
}

tarea CargarTarea(){
    tarea aux;
    printf("Ingrese la descripcion de la tarea\n");
    char desc[TAMA];
    fflush(stdin);
    gets(desc);
    aux.Descripcion=(char*)malloc((strlen(desc)+1)*sizeof(char));
    strcpy(aux.Descripcion,desc);
    aux.Duracion=rand()%91+10;
    return(aux);
}

tarea** CargarPuntero(int cant){
    tarea** aux;
    aux=(tarea**)malloc(cant*sizeof(tarea*));
    for(int i=0;i<cant;i++){
        aux[i]=(tarea*)malloc(sizeof(tarea));
        *aux[i]=CargarTarea();
        aux[i]->TareaID=i;
    }
    return(aux);
}

tarea**InicializarNulo(int cant){
tarea** aux;
aux=((tarea**)malloc(cant*sizeof(tarea*)));
for(int i=0;i<cant;i++){
    aux[i]=NULL;
}
return(aux);
}

void Mostrartarea(tarea aux){
    printf("TAREA ID: %d\n",aux.TareaID);
    printf("descripcion: %s\n",aux.Descripcion);
    printf("Duracion: %d\n",aux.Duracion);

}

void Mostrartareas(tarea** aux, int cant){
    for(int i=0;i<cant;i++){
        if(aux[i]!=NULL){
            printf("    EMPLEADO %d     \n",i+1);
            Mostrartarea(*aux[i]);
        }
    }
}

void Mostrar(lista aux)
{
    while ((!esvacia(aux)))
    {
        Mostrartarea(aux->dato); 
        aux = aux->siguiente;
    }
}

lista CrearNodo(int i)
{
    lista aux;
    aux = (struct nodo*)malloc(sizeof(struct nodo));
    aux->dato = CargarTarea();
    aux->dato.TareaID=i;
}

lista DesenlazarNodo(lista* pendientes){
    lista aux;
    aux=*pendientes;
    *pendientes=(*pendientes)->siguiente;
    aux->siguiente=NULL;
    return(aux);
}

void agregarprimero(lista *aux, lista nodo){
    nodo->siguiente=(*aux);
    (*aux)=nodo;
}


void desapuntarnodo(lista* aux, lista nodo){
    lista auxiliarnodo=*aux;
    lista nodoSeleccionado=NULL;
    lista anterior=auxiliarnodo;
    nodo->siguiente=NULL;
    int bandera=0;
    if(!esvacia(*aux) && esvacia((*aux)->siguiente)&&(*aux) ==nodo){
        nodoSeleccionado=*aux;
        (*aux)=NULL;
    }else
    {
        while(!esvacia((auxiliarnodo)) && bandera==0){
            if((auxiliarnodo)==nodo){
                    anterior->siguiente=auxiliarnodo->siguiente;
                    bandera=1;
            }
                anterior=auxiliarnodo;
                auxiliarnodo=auxiliarnodo->siguiente;
    }    
    }
    
}
lista realizaTareas(lista *tareaspendientes, lista* tareasrealizadas, lista*tareasenproceso)
{
        lista nodoSacado;
        int booleano;
        lista aux=CrearLista();
        while(!esvacia(*tareaspendientes)){
            printf("Realizo la tarea (1 si, 0 no, 2 en proceso)?\n");
            scanf("%d",&booleano);
            nodoSacado=DesenlazarNodo(tareaspendientes);
            if(booleano==1){
                InsertarNodoALista(tareasrealizadas,nodoSacado);
                //borrarprimero(&aux);
                //(*tareasrealizadas)->siguiente=(*tareasrealizadas);
                //(*tareasrealizadas)=(aux);
            }else{
                if(booleano==0){
                    InsertarNodoALista(&aux,nodoSacado);
                }else{
                    InsertarNodoALista(tareasenproceso,nodoSacado);
                }
                
            }
        }
    return(aux);

}