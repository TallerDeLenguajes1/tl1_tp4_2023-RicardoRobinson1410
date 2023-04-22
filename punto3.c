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

int main()
{
    lista tareasPendientesFinal=CrearLista();
    lista tareaspendientes;
    lista tareasrealizadas;
    tareaspendientes = CrearLista();
    tareasrealizadas=CrearLista();

    int cant;
    printf("Ingrese la cantidad de elementos que desea ingresar\n");
    scanf("%d", &cant);
    for (int i = 0; i < cant; i++)
    {
        InsertarPrimero(&tareaspendientes, i);
    }
    tareasPendientesFinal=realizaTareas(&tareaspendientes, &tareasrealizadas);
    printf("---------TAREAS PENDIENTES--------\n");
    Mostrar(tareasPendientesFinal);
    printf("--------TAREAS REALIZADAS-------\n");
    Mostrar(tareasrealizadas);
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