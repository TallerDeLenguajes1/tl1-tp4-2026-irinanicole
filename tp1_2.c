#include <stdio.h>
#include <stdlib.h>

// LISTAS NECESARIAS
typedef struct Tarea
{ 
    int tareaID; //Numérico autoincremental comenzando en 1000 
    char *descripcion;       
    int duracion; // entre 10 – 100  
} Tarea;

typedef struct Nodo
{ 
    Tarea T;  
    Nodo *siguiente;  
} Nodo;

// FUNCIONES
Nodo * crearLista();
Nodo crearTarea(int * num_id_tarea, char * detalle, int tiempo);
void insertarTarea(Nodo ** lista, Nodo * tarea);
void marcarTarea(Nodo ** lista_p, Nodo ** lista_r, Nodo * tarea); // mueve una tarea de la lista de pendientes a la de realizadas

int main()
{
    Nodo * pendientes = crearLista();
    Nodo * realizadas = crearLista();
    int cantidad_tareas = 1000;

    Nodo tarea1 = crearTarea(&cantidad_tareas, "tarea1", rand() % 91 + 10);
    insertarTarea(&pendientes, &tarea1);


    return 0;
}

Nodo * crearLista()
{
    return NULL;
}

Nodo crearTarea(int * num_id_tarea, char * detalle, int tiempo)
{
    Nodo nueva;
    *num_id_tarea++;
    nueva.T.tareaID = *num_id_tarea;
    nueva.T.descripcion = detalle;
    nueva.T.duracion = tiempo;
    nueva.siguiente = NULL;

    return nueva;
}

void insertarTarea(Nodo ** lista, Nodo * tarea)
{
    tarea->siguiente = *lista;
    *lista = tarea;
}

void marcarTarea(Nodo ** lista_p, Nodo ** lista_r, Nodo * tarea)
{
    insertarTarea(*lista_r,tarea);
    Nodo * aux = *lista_p;
    while(aux && aux->siguiente != tarea)
    {
        aux = aux->siguiente;
    }
    aux->siguiente = aux->siguiente->siguiente;
    
}