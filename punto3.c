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
tarea CargarTarea();
lista CrearLista();
bool esvacia(lista aux);
lista CrearNodo(int i);
void InsertarPrimero(lista *aux, int i);
void Mostrar(lista aux);
void Mostrartarea(tarea aux);
void borrarprimero(lista *aux); // sin liberar la memoria
lista realizaTareas(lista *tareaspendientes, lista* tareasrealizadas);
void InsertarNodoALista(lista* pendientes, lista nodo);
lista DesenlazarNodo(lista* pendientes);
tarea BuscarNodo(lista tareaspendientes, lista tareasrealiazadas, int i);

int main()
{
    lista tareasPendientesFinal=CrearLista();
    lista tareaspendientes;
    lista tareasrealizadas;
     int menu;
     int cant;
     int numtarea;
     tarea buscar;
    tareaspendientes = CrearLista();
    tareasrealizadas=CrearLista();
    while(menu!=0){
        printf("-------MENU--------\n");
        printf("1. INGRESAR\n");
        printf("2. Mostrar tareas ingresadas\n");
        printf("3. Indicar tareas pendientes y realizadas\n");
        printf("4. Mostrar tareas pendientes\n");
        printf("5. Mostrar tareas realizadas");

        

        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            printf("    INGRESAR    \n");
            printf("Ingrese la cantidad de elementos que desea ingresar\n");
        scanf("%d", &cant);
        for (int i = 0; i < cant; i++)
        {
            InsertarPrimero(&tareaspendientes, i);
        }
            break;
        case 2: 
        {
            printf("Mostrar tareas ingresadas\n");
            Mostrar(tareaspendientes);
        }
            break;
        case 3:
        {
            printf("INDICAR TAREAS PENDIENTES Y REALIZADAS\n");
            tareasPendientesFinal=realizaTareas(&tareaspendientes, &tareasrealizadas);
        }
            break;
        case 4:
        {
            printf("MOSTRAR TAREAS PENDIENTES\n");
            printf("---------TAREAS PENDIENTES--------\n");
            Mostrar(tareasPendientesFinal);
        }
            break;
        case 5:
        {
            printf("MOSTRAR TAREAS REALIZADAS\n");
            printf("--------TAREAS REALIZADAS-------\n");
            Mostrar(tareasrealizadas);
        }
            break;
        case 6: 
        {
            printf("BUSCAR TAREAS\n");
            printf("Ingrese la tarea que desea buscar\n");
            scanf("%d",&numtarea);
            buscar=BuscarNodo(tareasPendientesFinal,tareasrealizadas, numtarea);
            printf("-------TAREA ENCONTRADA---------\n");
            Mostrartarea(buscar);
        }
        break;
        }
    }

    free(tareasPendientesFinal);
    free(tareasrealizadas);
    return 0;
}

tarea CargarTarea()
{
    tarea aux;
    printf("Ingrese la descripcion de la tarea\n");
    char desc[TAMA];
    fflush(stdin);
    gets(desc);
    aux.Descripcion = (char *)malloc((strlen(desc) + 1) * sizeof(char));
    strcpy(aux.Descripcion, desc);
    aux.Duracion = rand() % 91 + 10;
    return (aux);
}

lista CrearLista()
{
    lista aux;
    return (NULL);
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

lista CrearNodo(int i)
{
    lista aux;
    aux = (struct nodo*)malloc(sizeof(struct nodo));
    aux->dato = CargarTarea();
    aux->dato.TareaID=i;
}

void InsertarPrimero(lista *aux, int i)
{
    lista nodo = CrearNodo(i);
    nodo->siguiente=*aux;
    *aux=nodo;
}

void Mostrar(lista aux)
{
    while ((!esvacia(aux)))
    {
        Mostrartarea(aux->dato); 
        aux = aux->siguiente;
    }
}
void Mostrartarea(tarea aux)
{
    printf("TAREA ID: %d\n", aux.TareaID);
    printf("descripcion: %s\n", aux.Descripcion);
    printf("Duracion: %d\n", aux.Duracion);
}

void borrarprimero(lista *aux)
{
    if (!esvacia(*aux))
    {
        (*aux) = (*aux)->siguiente;
    }
}
lista realizaTareas(lista *tareaspendientes, lista* tareasrealizadas)
{
        lista nodoSacado;
        int booleano;
        lista aux=CrearLista();
        while(!esvacia(*tareaspendientes)){
            printf("Realizo la tarea?\n");
            scanf("%d",&booleano);
            nodoSacado=DesenlazarNodo(tareaspendientes);
            if(booleano==1){
                InsertarNodoALista(tareasrealizadas,nodoSacado);
                //borrarprimero(&aux);
                //(*tareasrealizadas)->siguiente=(*tareasrealizadas);
                //(*tareasrealizadas)=(aux);
            }else{
                InsertarNodoALista(&aux,nodoSacado);
                //(aux)=(aux)->siguiente;
            }
        }
    return(aux);

}
lista DesenlazarNodo(lista* pendientes){
    lista aux;
    aux=*pendientes;
    *pendientes=(*pendientes)->siguiente;
    aux->siguiente=NULL;
    return(aux);
}

void InsertarNodoALista(lista* pendientes, lista nodo){
    nodo->siguiente=*pendientes;
    *pendientes=nodo;
}

tarea BuscarNodo(lista tareaspendientes, lista tareasrealiazadas, int i){
    int bandera=0;
    while(!esvacia(tareaspendientes)||bandera==1)
    {
        if(tareaspendientes->dato.TareaID==i){
            bandera=1;
            return(tareaspendientes->dato);
        }
        tareaspendientes=tareaspendientes->siguiente;
    }
    if(bandera==0){
        while(!esvacia(tareasrealiazadas)||bandera==1){
            if(tareasrealiazadas->dato.TareaID==i){
                bandera==1;
                return(tareasrealiazadas->dato);
            }
        }
    }
    printf("No se encontró el elemento\n");

    
}