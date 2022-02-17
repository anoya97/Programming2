/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Armando Martínez Noya LOGIN 1: a.mnoya
 * AUTHOR 2: Raúl Fernández del Blanco LOGIN 2: r.delblanco
 * GROUP: 2.4
 * DATE: 07 / 05 / 21
 */

#include "video_list.h"

//**********************************************************************************************************************
//                                                     GENERADORAS
//**********************************************************************************************************************

void createEmptyListV(tVideoList* L){
    L -> lastPos=NULL_VIDEO;
}

/* Objetivo:
 *      Crea una lista vacía.
 * Entradas:
 *      Recibe una tVideoList.
 * Salidas:
 *      Una lista vacía.
 * PostCD:
 *      La lista queda inicializada y no contiene elementos.
 */

bool insertItemV(tVideoItem d, tVideoPos p, tVideoList* L) {
    tVideoPos i;

    if (L->lastPos == MAX - 1) { //Comprueba si la lista está llena
        return false;
    } else {
        L->lastPos++;

        if (p == NULL_VIDEO) { //Insertar en lista vacía o más allá del último
            L->data[L -> lastPos] = d;
        }else{ //Insertar en una posición intermedia
            for (i = L -> lastPos; i > p ; i--) {
                L -> data[i] = L -> data[i - 1];
            }
            L -> data[p] = d;
        }

        return true;
    }
}

/* Objetivo:
 *      Si la posición es nula, añade un elemento al final de la lista.
 *      En caso contrario, el elemento quedará insertado justo antes del que actualmente ocupa
 *      la posición indicada.
 * Entradas:
 *      Recibe un tVideoItem (información para insertar).
 *      Recibe la posición en la que se insertará dicho item.
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

//**********************************************************************************************************************
//                                                     MODIFICADORAS
//**********************************************************************************************************************

void updateItemV(tVideoItem d , tVideoPos p, tVideoList* L){
    L-> data[p] = d;
}

/* Objetivo:
 *      Modifica el contenido de un elemento de la lista en la posición indicada.
 * Entradas:
 *      Recibe un tVideoItem (información para actualizar el dato en la posición introducida).
 *      Recibe una posición en la que se actualizará la información.
 *      Recibe la lista en la que se actualizará la información.
 * Salida:
 *      La lista con la información actualizada.
 * PreCD:
 *      La posición introducida es válida.
 */

//**********************************************************************************************************************
//                                                     DESTRUCTORAS
//**********************************************************************************************************************

void deleteAtPositionV(tVideoPos p, tVideoList* L){
    tVideoPos i;

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
 *      elemento eliminado han podido variar.
 */

//**********************************************************************************************************************
//                                                     OBSERVADORAS
//**********************************************************************************************************************

tVideoPos findItemV(tTitleVideo d, tVideoList L){

    tVideoPos p;

    if (L.lastPos == NULL_VIDEO){ //Lista vacia
        return NULL_VIDEO;
    } else{
        for (p = 0; (p <= L.lastPos) && (strcmp(L.data[p].titleVideo ,d) != 0) ; p++); //Busca la posición del title video indicado

        if (strcmp(L.data[p].titleVideo,d) == 0){ //Comprueba si el title video se encuentra en la lista
            return p;
        }else{ //No está
            return NULL_VIDEO;
        }
    }

}

/* Objetivo:
 *      Busca en la lista el primer elemento que tenga el mismo nickname que el indicado.
 * Entradas:
 *      Recibe un tTitleVide (información para buscar).
 *      Recibe la lista en la que se actualizará la información.
 * Salida:
 *      La posición en la que se encuentra el elemento buscado.
*/

bool isEmptyListV(tVideoList L){
    return L.lastPos == NULL_VIDEO;
}

/* Objetivo:
 *      Determina si la lista está vacía.
 * Entradas:
 *      Recibe la lista en la que se comprobará si está vacía.
 * Salida:
 *      Devuelve verdadero si la lista está vacía y falso en caso contrario.
*/

tVideoItem getItemV(tVideoPos p, tVideoList L){
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

tVideoPos firstV(tVideoList L){
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

tVideoPos lastV(tVideoList L){
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

tVideoPos previousV(tVideoPos p, tVideoList L){
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

tVideoPos nextV(tVideoPos p, tVideoList L){
    if (p==L.lastPos){
        return NULL_VIDEO;
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


























