/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Raúl Fernández del Blanco LOGIN 1: r.delblanco
 * AUTHOR 2: Armando Martínez Noya LOGIN 2: a.mnoya
 * GROUP: 2.4
 * DATE: 09 / 04 / 21
 */


#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>

/* Definicion de tipos */

#define LNULL NULL
#define MAX 1000

typedef struct tNode* tPosL;
struct tNode {
    tItemL data;
    tPosL next;
};
typedef tPosL tList;

/* Prototipos de funciones */

void createEmptyList(tList* L);
bool insertItem(tItemL d, tPosL p, tList* L);
void updateItem(tItemL d , tPosL p, tList* L);
void deleteAtPosition(tPosL p, tList* L);
tPosL findItem(tItemL d, tList L);
bool isEmptyList(tList L);
tItemL getItem(tPosL p, tList L);
tPosL first(tList L) ;
tPosL last(tList L);
tPosL previous(tPosL p, tList L);
tPosL next(tPosL p, tList L);





#endif

