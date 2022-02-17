/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Armando Martínez Noya LOGIN 1: a.mnoya
 * AUTHOR 2: Raúl Fernández del Blanco LOGIN 2: r.delblanco
 * GROUP: 2.4
 * DATE: 07 / 05 / 21
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H

#include "types.h"
#include <stdbool.h>
#include "video_list.h"

/* Definicion de tipos */

#define NULL_USER NULL
#define MAX 25

typedef struct tNode* tUserPos;

typedef struct tUserItem {
    tNickname nickname;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
} tUserItem;

struct tNode {
    tUserItem data;
    tUserPos next;
};

typedef tUserPos tUserList;


/* Prototipos de funciones */

void createEmptyList(tUserList* L);
bool insertItem(tUserItem d, tUserList* L);
void updateItem(tUserItem d , tUserPos p, tUserList* L);
void deleteAtPosition(tUserPos p, tUserList* L);
tUserPos findItem(tNickname d, tUserList L);
bool isEmptyList(tUserList L);
tUserItem getItem(tUserPos p, tUserList L);
tUserPos first(tUserList L) ;
tUserPos last(tUserList L);
tUserPos previous(tUserPos p, tUserList L);
tUserPos next(tUserPos p, tUserList L);

#endif //P2_USER_LIST_H