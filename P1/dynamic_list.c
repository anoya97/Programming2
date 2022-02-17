/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Raúl Fernández del Blanco LOGIN 1: r.delblanco
 * AUTHOR 2: Armando Martínez Noya LOGIN 2: a.mnoya
 * GROUP: 2.4
 * DATE: 09 / 04 / 21
 */

#include "dynamic_list.h"
#include <stdlib.h>
#include <string.h>


bool createNode(tPosL *p){
    *p = malloc(sizeof(struct tNode)); //Reserva espacio en memoria
    return *p != LNULL;
}

/* Función auxiliar que solo funciona en el archivo dynamic_list y no en el main.
 * Reserva un espacio en memoria para usarlo como un nodo.
*/

void createEmptyList(tList* L){
    *L = LNULL;
}

/* Objetivo:
 *      Crea una lista vacía.
 * Entradas:
 *      Recibe una tList.
 * Salidas:
 *      Una lista vacía.
 * PostCD:
 *      La lista queda inicializada y no contiene elementos.
 */

bool insertItem(tItemL d, tPosL p, tList* L){
    tPosL q, r; //Punteros a un Nodo

    if (!createNode(&q)){
        return false;
    }else{
        q -> data = d; //Le asigna el item d a q
        q -> next = LNULL;

        if (*L == LNULL){ //Lista vacía
            *L = q;
        }else{
            if (p == LNULL){ //Insertar al final de lista no vacia
                for (r = *L; r->next != LNULL ; r = r->next);
                r -> next = q;
            }else{
                if (p == *L){ //Insertar en la primera posición
                    q -> next = p;
                    *L = q; //Hace que q sea el primer elemento y p el segundo
                }else { //Insertar en una posición intermedia
                    q -> data = p -> data; //Mueve dato de p a q
                    p -> data = d; //Pone un dato nuevo en p
                    q -> next = p -> next;
                    p -> next = q;
                }
            }
        }
        return true;
    }

}

/* Objetivo:
 *      Si la posición es nula, añade un elemento al final de la lista.
 *      En caso contrario, el elemento quedará insertado justo antes del que actualmente ocupa
 *      la posición indicada.
 * Entradas:
 *      Recibe un itemL (información para insertar).
 *      Recibe la posición en la que se insertará dicho itemL.
 *      Recibe la lista en la que insertaremos la información.
 * Salidas:
 *      La lista con la información insertada.
 *      Devuelve verdadero si se inserta correctamente y falso en caso contrario.
 * PreCD:
 *      La posición introducida es válida o es nula.
 * PostCD:
 *      Las posiciones de los elementos de la lista posteriores a la del
 *      elemento insertado han podido variar.
 */


void updateItem(tItemL d , tPosL p, tList* L){
    p -> data = d;
}

/* Objetivo:
 *      Modifica el contenido de un elemento de la listo.
 * Entradas:
 *      Recibe un itemL (información para actualizar el dato en la posición introducida).
 *      Recibe una posición en la que se actualizará la información.
 *      Recibe la lista en la que se actualizará la información.
 * Salida:
 *      La lista con la información actualizada.
 * PreCD:
 *      La posición introducida es válida.
 */

void deleteAtPosition(tPosL p, tList* L){
    tPosL q;

    if (p == *L){ //Borrar primer elemento
        *L = (*L) -> next; //Ahora la lista apunta al segundo elemento
    }else{
        if (p -> next == LNULL){ //Eliminar ultima posición

            for (q = *L; q -> next != p; q = q -> next); //Busca el anterior de p
            q -> next = LNULL;
        }else{ //eliminar posición intermedia
            q = p -> next;
            p -> data = q -> data;
            p -> next = q -> next;
            p = q; 
        }
    }
    free(p); //Libera el espacio de memoria de p
}

/* Objetivo:
 *      Elimina de la lista el elemento de la posición indicada.
 * Entradas:
 *      Recibe la posición del elemento que se quiere eliminar.
 *      Recibe la lista en la que se eliminará el elemento.
 * Salida:
 *      La lista sin el elemento que había en la posición indicada.
 * PreCD:
 *      La posición introducida es válida.
 * PostCD:
 *      Las posiciones de los elementos de la lista posteriores a la del
 *      elemento insertado han podido variar.
 */


tPosL findItem(tItemL d, tList L){
    tPosL p;

    for ( p = L; (p != LNULL) && (strcmp(p -> data.nickname,d.nickname) != 0); p = p -> next); //Busca la posición del nickname introducido

    return p;
}

/* Objetivo:
 *      Busca en la lista el primer elemento que tenga el mismo nickname que el indicado.
 * Entradas:
 *      Recibe un itemL (información para buscar).
 *      Recibe la lista en la que se actualizará la información.
 * Salida:
 *      La posición en la que se encuentra el elemento buscado.
*/

bool isEmptyList(tList L){
    return L == LNULL;
}

/* Objetivo:
 *      Determina si la lista está vacía.
 * Entradas:
 *      Recibe la lista en la que se comprobará si está vacía.
 * Salida:
 *      Devuelve verdadero si la lista está vacía y falso en caso contrario.
*/


tItemL getItem(tPosL p, tList L){
    return p -> data;
}

/* Objetivo:
 *      Consigue el contenido de un elemento de la lista.
 * Entradas:
 *      Recibe la posición del elemento que se quiere conseguir.
 *      Recibe la lista en la que se realizará la búsqueda.
 * Salida:
 *      Devuelve el item que contiene la información requerida.
 * PreCD:
 *      La posición introducida es válida.
*/

tPosL first(tList L){
    return L;
}

/* Objetivo:
 *      Obtener la primera posición de la lista.
 * Entradas:
 *      Recibe la lista en la que se realizará la búsqueda.
 * Salida:
 *      Devuelve la posición del primer elemento.
 * PreCD:
 *      La lista no está vacía.
*/

tPosL last(tList L){
    tPosL p;

    for(p = L; p -> next != LNULL; p = p -> next);
    return p;

}

/* Objetivo:
 *      Consigue la última posición de la lista.
 * Entradas:
 *      Recibe la lista en la que se realizará la búsqueda.
 * Salida:
 *      Devuelve la posición del último elemento.
 * PreCD:
 *      La lista no está vacía.
*/

tPosL previous(tPosL p, tList L){
    tPosL q;

    if (p == L){
        return LNULL;
    }else{
        for(q = L; q -> next != p; q = q -> next);
        return q;
    }
}

/* Objetivo:
 *      Consigue la posición del elemento anterior al actual.
 * Entradas:
 *      Recibe la posición del elemento actual.
 *      Recibe la lista en la que se realizará la búsqueda.
 * Salida:
 *      Devuelve la posición del elemento anterior y, en caso de que sea el primer elemento
 *      de la lista, devuelve nulo.
 * PreCD:
 *      La posición introducida es válida.
*/

tPosL next(tPosL p, tList L){
    return p -> next;
}

/* Objetivo:
 *      Consigue la posición del elemento siguiente al actual.
 * Entradas:
 *      Recibe la posición del elemento actual.
 *      Recibe la lista en la que se realizará la búsqueda.
 * Salida:
 *      Devuelve la posición del elemento siguiente y, en caso de que sea el último elemento
 *      de la lista, devuelve nulo.
 * PreCD:
 *      La posición introducida es válida.
*/