/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Raúl Fernández del Blanco LOGIN 1: r.delblanco
 * AUTHOR 2: Armando Martínez Noya LOGIN 2: a.mnoya
 * GROUP: 2.4
 * DATE: 09 / 04 / 21
 */

#include "static_list.h"


void createEmptyList(tList* L){
    L -> lastPos=LNULL;
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

bool insertItem(tItemL d, tPosL p, tList* L) {
    tPosL i;

    if (L->lastPos == MAX - 1) { //Comprueba si la lista está llena
        return false;
    } else {
        L->lastPos++;
        if (p == LNULL) { //Insertar en lista vacía o más allá del último
            L->data[L -> lastPos] = d;
        }else{ //Insertar en una posición intermedia
            for (i = L -> lastPos; i > p ; i--) {
                L -> data[i] = L -> data[i - 1];
            }
            L -> data[p + 1] = d;
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
    L-> data[p] = d;
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
    tPosL i;

    L -> lastPos--;
    for (i = p; i <= L -> lastPos; i++) {
        L -> data[i] = L -> data[i+1];
    } //Desde p hasta lastpos se sobreescriben los datos, eliminando así la posición indicada

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

    if (L.lastPos == LNULL){ //Lista vacia
        return LNULL;
    } else{
        for (p = 0; (p <= L.lastPos) && (strcmp(L.data[p].nickname,d.nickname) != 0) ; p++); //Busca la posición del nickname indicado

        if (strcmp(L.data[p].nickname,d.nickname) == 0){ //Comprueba si el nickname se encuentra en la lista
            return p;
        }else{ //No está
            return LNULL;
        }
    }

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
    return L.lastPos==LNULL;
}

/* Objetivo:
 *      Determina si la lista está vacía.
 * Entradas:
 *      Recibe la lista en la que se comprobará si está vacía.
 * Salida:
 *      Devuelve verdadero si la lista está vacía y falso en caso contrario.
*/

tItemL getItem(tPosL p, tList L){
    return L.data[p];
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
    return 0;
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
    return L.lastPos;
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
    return --p;
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
    if (p==L.lastPos){
        return LNULL;
    }else {
        return ++p;
    }
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