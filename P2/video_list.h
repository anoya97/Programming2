/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Armando Martínez Noya LOGIN 1: a.mnoya
 * AUTHOR 2: Raúl Fernández del Blanco LOGIN 2: r.delblanco
 * GROUP: 2.4
 * DATE: 07 / 05 / 21
 */

#ifndef P2_VIDEO_LIST_H
#define P2_VIDEO_LIST_H


#include "types.h"
#include <stdbool.h>
#include <string.h>

/* Definicion de tipos */

#define NULL_VIDEO -1
#define MAX 25

typedef int tVideoPos;

typedef tVideo tVideoItem;

typedef struct {
    tVideoItem data[MAX];
    tVideoPos lastPos;
}tVideoList;

/* Prototipos de funciones */

void createEmptyListV(tVideoList* L);
bool insertItemV(tVideoItem d, tVideoPos p, tVideoList* L);
void updateItemV(tVideoItem d , tVideoPos p, tVideoList* L);
void deleteAtPositionV(tVideoPos p, tVideoList* L);
tVideoPos findItemV(tTitleVideo d, tVideoList L);
bool isEmptyListV(tVideoList L);
tVideoItem getItemV(tVideoPos p, tVideoList L);
tVideoPos firstV(tVideoList L) ;
tVideoPos lastV(tVideoList L);
tVideoPos previousV(tVideoPos p, tVideoList L);
tVideoPos nextV(tVideoPos p, tVideoList L);

#endif //P2_VIDEO_LIST_H

