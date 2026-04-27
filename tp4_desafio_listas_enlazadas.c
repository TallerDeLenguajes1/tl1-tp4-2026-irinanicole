#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// LISTAS NECESARIAS
typedef struct Tarea
{ 
    int id; //Numérico autoincremental comenzando en 1000 
    char *descripcion;       
    int duracion; // entre 10 – 100  (horas o días)
} Tarea;

typedef struct NodoTarea
{ 
    Tarea T;  
    NodoTarea *siguienteTarea;  
} NodoTarea;

// FUNCIONES
NodoTarea * crearListaVacia(); // devuelve una direccion a 'NULL'
Tarea crearTarea(int * id_tarea);
NodoTarea * crearNodoTarea(NodoTarea ** lista_pendientes,int * id_tarea);
void insertarTarea(NodoTarea ** lista, NodoTarea * nodo_tarea);
void marcarTarea(NodoTarea ** lista_p, NodoTarea ** lista_r, NodoTarea * nodo_tarea); // mueve una tarea de la lista de t_Pendientes a la de t_Realizadas

int main()
{
    //
    srand(time(NULL));
    //
    int cantidad_tareas = 1000;
    NodoTarea * t_Pendientes = crearListaVacia();
    NodoTarea * t_Realizadas = crearListaVacia();

    //NodoTarea * nodo_tarea_nueva = crearNodoTarea(&t_Pendientes, &cantidad_tareas);


    return 0;
}

NodoTarea * crearListaVacia()
{
    return NULL;
}

Tarea crearTarea(int * id_tarea)
{
    int inicio=10, fin=100;
    Tarea nuevaTarea;
    *id_tarea++;
    nuevaTarea.id = *id_tarea;
    nuevaTarea.descripcion = "detalle";
    nuevaTarea.duracion = inicio + rand() % (fin-inicio+1); 
    
    return nuevaTarea;
}

NodoTarea * crearNodoTarea(NodoTarea ** lista_pendientes, int * id_tarea)
{
    Tarea nueva_tarea = crearTarea(id_tarea);

    NodoTarea * nuevo_nodoTarea = (NodoTarea *)malloc(sizeof(NodoTarea));
    nuevo_nodoTarea->T = nueva_tarea;
    nuevo_nodoTarea->siguienteTarea = NULL;

    insertarTarea(lista_pendientes, nuevo_nodoTarea);

    return nuevo_nodoTarea;
}

void insertarTarea(NodoTarea ** lista, NodoTarea * nodo_tarea)
{
    nodo_tarea->siguienteTarea = *lista; // si *lista = NULL => nodo_tarea->siguienteTarea = NULL
    *lista = nodo_tarea;
}

void marcarTarea(NodoTarea ** lista_p, NodoTarea ** lista_r, NodoTarea * nodo_tarea)
{
    insertarTarea(lista_r,nodo_tarea);
    NodoTarea * aux = *lista_p;
    while(aux && aux->siguienteTarea != nodo_tarea)
    {
        aux = aux->siguienteTarea;
    }
    aux->siguienteTarea = aux->siguienteTarea->siguienteTarea;
}