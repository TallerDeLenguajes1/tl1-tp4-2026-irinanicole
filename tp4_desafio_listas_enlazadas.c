#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Función para LIMPIAR EL BUFFER
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

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
    struct NodoTarea *siguienteTarea;  
} NodoTarea;

// FUNCIONES
NodoTarea * crearListaVacia(); // devuelve una direccion a 'NULL'
Tarea crearTarea(int * id_tarea, char * descripcion_tarea, int duracion_tarea);
NodoTarea * crearNodoTarea(NodoTarea ** lista_pendientes,int * id_tarea, char * descripcion_tarea, int duracion_tarea);
void insertarTarea(NodoTarea ** lista, NodoTarea * nodo_tarea);
void mostrarTareas(NodoTarea * lista);
NodoTarea * marcarTarea(NodoTarea ** lista_p, NodoTarea ** lista_r, int id_tarea); // mueve una tarea de la lista de t_Pendientes a la de t_Realizadas

int main()
{
    //
    srand(time(NULL));
    //
    int cantidad_tareas = 1000-1;
    NodoTarea * t_Pendientes = crearListaVacia();
    NodoTarea * t_Realizadas = crearListaVacia();

    NodoTarea * nodo_tarea_nueva;
    // INTERFAZ DE USUARIO: CARGA DE TAREAS PENDIENTES //
    int seguir_cargando = 1;
    char buffer[50];
    char * descripcionTareaNueva;
    int duracionTareaNueva;
    int repetir_ingreso;
    printf("\n\n<<<< INTERFAZ DE USUARIO >>>>\n\n***CARGA DE TAREAS PENDIENTES***\n");
    while (seguir_cargando)
    {
        printf("\n¿Desea registrar una nueva tarea? (SI: 1 | NO: 0): ");
        scanf("%d",&seguir_cargando);

        if (seguir_cargando)
        {
            printf("\n**NUEVA TAREA**\n");
            //
            limpiarBuffer(); // para la siguiente lectura por fgets()
            //
            printf("\nDESCRIPCION: ");
            fgets(buffer, sizeof(buffer), stdin);
            // corrijo el final del buffer: reemplazo el '\n' (que agrega el fgets() en la cadena al final) por '\0'
            buffer[sizeof(buffer)-1] = '\0';
            // defino tamaño para la cadena 'descripcionTareaNueva'
            descripcionTareaNueva = (char *)malloc(sizeof(char) * sizeof(buffer));
            strcpy(descripcionTareaNueva, buffer);
            //
            repetir_ingreso = 1;
            while(repetir_ingreso){
                printf("\nDURACION (10-100)(min): ");
                scanf("%d",&duracionTareaNueva);
                if(100 < duracionTareaNueva || duracionTareaNueva < 10){
                    printf("¡¡ATENCION!!\nLa tarea debe tener una DURACION entre 10 y 100 min.");
                }
                else
                {
                    repetir_ingreso = 0;
                }
            }
            // creo un nuevo nodoTarea
            nodo_tarea_nueva = crearNodoTarea(&t_Pendientes, &cantidad_tareas, descripcionTareaNueva, duracionTareaNueva);
            // inserto el nodo en la LISTA DE TAREAS PENDIENTES
            insertarTarea(&t_Pendientes, nodo_tarea_nueva);
        }
        
    }
    printf("\n*********** FIN DE CARGA DE TAREAS ***********\n");
    //
    //
    //
    int respuesta, cambiarTareaARealizada = 1;
    NodoTarea * nodo_tareaMarcada;
    while(cambiarTareaARealizada)
    {
        printf("\n\n>>>>LISTA DE TAREAS PENDIENTES<<<<\n");
        mostrarTareas(t_Pendientes);
        //
        printf("\n¿Desea marcar alguna tarea como realizada?\nSi la respuesta es 'SI', ingrese el numero de la TAREA correspondiente.\nSi la respuesta es 'NO', ingrese '0'.");
        printf("\nR: ");
        scanf("%d",&respuesta);
        if (respuesta)
        {
            nodo_tareaMarcada = marcarTarea(&t_Pendientes, &t_Realizadas, respuesta);
            if (nodo_tareaMarcada)
            {
                printf("\nLa tarea %d fue movida a la lista de REALIZADAS con exito!\n",nodo_tareaMarcada->T.id);
                printf("\n\t=> LISTA DE TAREAS REALIZADAS: **ACTUALIZADA**");
            }
            else
            {
                printf("\n-----------------------------");
                printf("\nLa tarea %d aun no ha sido agregada a la lista de Tareas Pendientes.\n");
                printf("\n-----------------------------");
            }
        }
        else
        {
            cambiarTareaARealizada = 0;
        }
        printf("\n\n>>>>LISTA DE TAREAS REALIZADAS<<<<\n");
        if (t_Realizadas)
        {
            mostrarTareas(t_Realizadas);
        }
        else
        {
            printf("\n-----------------------------");
            printf("\n.*** Aun no existen tareas REALIZADAS ***.");
            printf("\n-----------------------------");
        }
    }

    getchar();
    return 0;
}

NodoTarea * crearListaVacia()
{
    return NULL;
}

Tarea crearTarea(int * id_tarea, char * descripcion_tarea, int duracion_tarea)
{
    //int inicio=10, fin=100;
    Tarea nuevaTarea;
    (*id_tarea)++;
    nuevaTarea.id = *id_tarea;
    nuevaTarea.descripcion = descripcion_tarea;
    //nuevaTarea.duracion = inicio + rand() % (fin-inicio+1); 
    nuevaTarea.duracion = duracion_tarea; 
    //
    return nuevaTarea;
}

NodoTarea * crearNodoTarea(NodoTarea ** lista_pendientes,int * id_tarea, char * descripcion_tarea, int duracion_tarea)
{
    Tarea nueva_tarea = crearTarea(id_tarea, descripcion_tarea, duracion_tarea);
    //
    NodoTarea * nuevo_nodoTarea = (NodoTarea *)malloc(sizeof(NodoTarea));
    nuevo_nodoTarea->T = nueva_tarea;
    nuevo_nodoTarea->siguienteTarea = NULL;
    //
    return nuevo_nodoTarea;
}

void insertarTarea(NodoTarea ** lista, NodoTarea * nodo_tarea)
{
    nodo_tarea->siguienteTarea = *lista; // si *lista = NULL => nodo_tarea->siguienteTarea = NULL
    *lista = nodo_tarea;
}

void mostrarTareas(NodoTarea * lista)
{
    NodoTarea * aux = lista;
    while (aux)
    {
        printf("\n-----------------------------");
        printf("\n[TAREA: %d]", aux->T.id);
        printf("\nDescripcion: %s", aux->T.descripcion);
        printf("\nDuracion: %d min", aux->T.duracion);
        printf("\n-----------------------------");
        aux = aux->siguienteTarea;
    }
}

// CONSULTAR PORQUE NO ME ESTÁ FUNCIONANDO BIEN
// LA LISTA DE REALIZADAS LA HACE BIEN HASTA CIERTO PUNTO
// LA LISTA DE PENDIENTES LA ACTUALIZA DE MANERA QUE COMINEZA DESDE LA TAREA QUE QUIERO MOVER 
// (Y LA DEJA TODAVÍA EN LA LISTA_PENDIENTES)
NodoTarea * marcarTarea(NodoTarea ** lista_p, NodoTarea ** lista_r, int id_tarea)
{   
    NodoTarea * aux = *lista_p;
    while(aux && (aux->siguienteTarea)->T.id != id_tarea)
    {
        aux = aux->siguienteTarea;
    }
    NodoTarea * nodo_a_cambiar_de_lista = aux->siguienteTarea;
    aux = (nodo_a_cambiar_de_lista)->siguienteTarea;
    insertarTarea(lista_r,nodo_a_cambiar_de_lista);

    return nodo_a_cambiar_de_lista;
}