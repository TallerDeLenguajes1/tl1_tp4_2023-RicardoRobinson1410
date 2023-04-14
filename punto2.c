#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define TAMA 100

typedef struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
}tarea;
tarea CargarTarea();
tarea** CargarTareas();






tarea** CargarPuntero(int cant);
tarea** InicializarNulo(int cant);
void Mostrartarea(tarea aux);
void Mostrartareas(tarea** aux, int cant);
tarea** Cargartareas(int cant);
void encontrarTareasporID(tarea** aux, int id, int cant);

int main(){
    tarea** tareasPendientes;
    int cant;
    int id;
    int realizo;
    printf("Ingrese la cantidad de empleados\n");
    scanf("%d",&cant);
    tareasPendientes=CargarPuntero(cant);
    tarea** tareasrealizadas=InicializarNulo(cant);
    printf("Ingrese el id que desea buscar\n");
    scanf("%d",&id);
    encontrarTareasporID(tareasPendientes,id,cant);
    for(int i=0;i<cant;i++){
        printf("Realizo la tarea %d?\n",i);
        scanf("%d",&realizo);
        if(realizo==1){
            tareasrealizadas[i]=tareasPendientes[i];
            tareasPendientes[i]=NULL;
        }
    }
    printf("--------TAREAS PENDIENTES--------\n");
    Mostrartareas(tareasPendientes,cant);
    printf("---------Tareas realizadas---------\n");
    Mostrartareas(tareasrealizadas,cant);
    return 0;
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

void encontrarTareasporID(tarea** aux, int id, int cant){
    for(int i=0;i<cant;i++){
        if((aux[i]->TareaID)==id){
            printf("=========TAREA ID\n======");
            Mostrartarea(*aux[i]);
        }
    }
}

