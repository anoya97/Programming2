/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Armando Martínez Noya LOGIN 1: a.mnoya
 * AUTHOR 2: Raúl Fernández del Blanco LOGIN 2: r.delblanco
 * GROUP: 2.4
 * DATE: 07 / 05 / 21
 */


#include "user_list.h"

#include <stdlib.h>
#include <string.h>

//**********************************************************************************************************************
//                                                     OBSERVADORA
//**********************************************************************************************************************

tUserPos findPosition(tUserList L, tUserItem d){
    tUserPos p;

    p = L;
    while (p->next != NULL_USER && strcmp(p->next->data.nickname, d.nickname) < 0){
        p = p -> next;
    }
    return p;
}

/* Función auxiliar que solo funciona en el archivo user_list y no en el main.
 * Busca la posición del item indicado dentro de la lista de usuarios.
*/

//**********************************************************************************************************************
//                                                     GENERADORAS
//**********************************************************************************************************************

bool createNode(tUserPos *p){
    *p = malloc(sizeof(struct tNode)); //Reserva espacio en memoria
    return *p != NULL_USER;
}

/* Función auxiliar que solo funciona en el archivo user_list y no en el main.
 * Reserva un espacio en memoria para usarlo como un nodo.
*/

void createEmptyList(tUserList* L){
    *L = NULL_USER;
}

/* Objetivo:
 *      Crea una lista vacía.
 * Entradas:
 *      Recibe una tUserList.
 * Salidas:
 *      Una lista vacía.
 * PostCD:
 *      La lista queda inicializada y no contiene elementos.
 */

bool insertItem(tUserItem d, tUserList* L){
    tUserPos q;
    tUserPos p;

    if (!createNode(&q)){
        return false;
    } else {
        q -> data = d;
        q -> next = NULL_USER;
        if (*L == NULL_USER) {  //Lista vacía
            *L = q;
        } else{
            if (strcmp(d.nickname, (*L) -> data.nickname) <= 0){  //Insertar en la primera posición
                q -> next = *L;
                *L = q;
            }else{
                p = findPosition(*L, d);  //Busca la posición
                q -> next = p -> next;
                p -> next = q;
            }
        }
        return true;
    }
}

/* Objetivo:
 *      Inserta un elemento en la lista según el criterio de ordenación
 *      sobre el campo Item, es decir, alfabéticamente.
 * Entradas:
 *      Recibe un tUserItem (información para insertar).
 *      Recibe la lista en la que insertaremos la información.
 * Salidas:
 *      La lista con la información insertada en la posición correspondiente según su contenido.
 *      Devuelve verdadero si se inserta correctamente y falso en caso contrario.
 * PreCD:
 *      La lista está previamente inicializada.
 * PostCD:
 *      Las posiciones de los elementos de la lista posteriores a la del
 *      elemento insertado han podido variar.
 */

//**********************************************************************************************************************
//                                                     MODIFICADORAS
//**********************************************************************************************************************

void updateItem(tUserItem d , tUserPos p, tUserList* L){
    p -> data = d;
}

/* Objetivo:
 *      Modifica el contenido de un elemento de la lista.
 * Entradas:
 *      Recibe un tUserItem (información para actualizar el dato en la posición introducida).
 *      Recibe una posición en la que se actualizará la información.
 *      Recibe la lista en la que se actualizará la información.
 * Salida:
 *      La lista con la información actualizada.
 * PreCD:
 *      La posición introducida es válida.
 *      La lista está previamente inicializada.
 */

//**********************************************************************************************************************
//                                                     DESTRUCTORAS
//**********************************************************************************************************************

void deleteAtPosition(tUserPos p, tUserList* L){
    tUserPos q;

    if (p == *L){ //Borrar primer elemento
        *L = (*L) -> next; //Ahora la lista apunta al segundo elemento
    }else{
        if (p -> next == NULL_USER){ //Eliminar ultima posición

            for (q = *L; q -> next != p; q = q -> next); //Busca el anterior de p
            q -> next = NULL_USER;
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
 *      La lista está previamente inicializada.
 * PostCD:
 *      Las posiciones de los elementos de la lista posteriores a la del
 *      elemento eliminado han podido variar.
 */

//**********************************************************************************************************************
//                                                     OBSERVADORAS
//**********************************************************************************************************************

tUserPos findItem(tNickname d, tUserList L){
    tUserPos p;

    for (p = L; (p != NULL_USER) && (strcmp(p -> data.nickname,d) != 0); p = p -> next);

    if (p != NULL_USER && strcmp(p -> data.nickname,d) == 0){
        return p;
    }else{
        return NULL_USER;
    }
}

/* Objetivo:
 *      Busca en la lista el primer elemento que tenga el mismo nickname que el indicado.
 * Entradas:
 *      Recibe un tNickname (información para buscar).
 *      Recibe la lista en la que se buscará la información.
 * Salida:
 *      La posición en la que se encuentra el elemento buscado.
*/

bool isEmptyList(tUserList L){
    return L == NULL_USER;
}

/* Objetivo:
 *      Determina si la lista está vacía.
 * Entradas:
 *      Recibe la lista en la que se comprobará si está vacía.
 * Salida:
 *      Devuelve verdadero si la lista está vacía y falso en caso contrario.
*/


tUserItem getItem(tUserPos p, tUserList L){
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

tUserPos first(tUserList L){
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

tUserPos last(tUserList L){
    tUserPos p;

    for(p = L; p -> next != NULL_USER; p = p -> next);
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

tUserPos previous(tUserPos p, tUserList L){
    tUserPos q;

    if (p == L){
        return NULL_USER;
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

tUserPos next(tUserPos p, tUserList L){
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

