/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Armando Martínez Noya LOGIN 1: a.mnoya
 * AUTHOR 2: Raúl Fernández del Blanco LOGIN 2: r.delblanco
 * GROUP: 2.4
 * DATE: 07 / 05 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255

void Header(char *commandNumber, char command, char dosP, char *nick_maxtime, char *param1, char *video_cat, char *param2, char *minut, char *param3) {
    puts("********************");
    printf("%s %c%c %s %s %s %s %s %s\n", commandNumber, command, dosP, nick_maxtime, param1, video_cat, param2, minut, param3);
}

void New(char *commandNumber, char command, char *param1, char *param2, tUserList *lista) {

    //Cabecera
    Header(commandNumber,command,':',"nick",param1,"category",param2,"","");

    if (findItem(param1, *lista) != NULL_USER) { //Comprueba si el usuario introducido ya existe
        puts("+ Error: New not possible");
    } else {

        //Creación del usuario utilizado
        tUserItem User;
        strcpy(User.nickname, param1);
        User.totalPlayTime = 0;
        if (strcmp(param2, "standard") == 0){
            User.userCategory = 0;
        }else{
            User.userCategory = 1;
        }
        createEmptyListV(&User.videoList);

        if(insertItem(User, lista)) { //Inserta el usuario en la lista alfabéticamente
            printf("* New: nick %s category %s\n", User.nickname, User.userCategory == 0 ? "standard" : "premium");
        } else{ //En caso de que falle la creación del nodo
            puts("+ Error: New not possible");
        }
    }


}

void Delete(char *commandNumber, char command, char *param1, tUserList *lista) {
    //Cabecera
    Header(commandNumber,command,':',"nick",param1,"","","","");

    tUserItem User;
    strcpy(User.nickname, param1);
    tUserPos p = findItem(User.nickname, *lista); //Busca la posición del usuario introducido

    if (p == NULL_USER) { //Comprueba que el usuario se encuentra en la lista
        printf("+ Error: Delete not possible\n");
    } else {
        User = getItem(p, *lista);
        printf("* Delete: nick %s category %s totalplaytime %d\n", param1, User.userCategory == 0 ? "standard" : "premium",User.totalPlayTime);

        while (!isEmptyListV(User.videoList)){ //Vacía la lista de vídeos
            deleteAtPositionV(firstV(User.videoList), &User.videoList);
        }

        deleteAtPosition(p,lista);
    }

}

void Add(char *commandNumber, char command, char *param1, char *param2, tUserList *lista) {
    //Cabecera
    Header(commandNumber,command,':',"nick",param1,"video",param2,"","");

    tUserItem User;
    strcpy(User.nickname, param1);
    tUserPos p = findItem(User.nickname, *lista); //Busca la posición del usuario introducido
    tVideoPos q;


    if (p != NULL_USER) { //Comprueba que el usuario se encuentra en la lista
        User = getItem(p, *lista); //Obtiene el usuario

        q = findItemV(param2, User.videoList);

        if (q == NULL_VIDEO){ //Comprueba que el video no se encuentra en la lista
            //Crea el video
            tVideoItem Video;
            strcpy(Video.titleVideo, param2);
            Video.playTime = 0;
            insertItemV(Video, NULL_VIDEO, &User.videoList);

            updateItem(User, p, lista); //Lo actualiza en la lista
            printf("* Add: nick %s adds video %s\n", param1, param2);
        }else {
            puts("+ Error: Add not possible");
        }
    } else {
        puts("+ Error: Add not possible");
    }

}

void Play(char *commandNumber, char command, char *param1, char *param2,char *param3, tUserList *lista){
    //Cabecera
    Header(commandNumber,command,':',"nick",param1,"video",param2,"minutes",param3);

    tUserItem User;
    strcpy(User.nickname, param1);
    tUserPos p = findItem(User.nickname, *lista); //Busca la posición del usuario introducido
    tVideoPos q;

    if (p != NULL_USER) { //Comprueba que el usuario se encuentra en la lista
        User = getItem(p, *lista); //Obtiene el usuario

        q = findItemV(param2, User.videoList);

        if (q != NULL_VIDEO){ //Comprueba que el video se encuentra en la lista
            //Crea el video
            tVideoItem Video;
            Video = getItemV(q,User.videoList);
            Video.playTime +=  strtol(param3, NULL, 10);
            User.totalPlayTime += strtol(param3, NULL, 10);

            updateItemV(Video,q,&User.videoList); //Lo actualiza en la lista de videos
            updateItem(User, p, lista); //Lo actualiza en la lista de usuarios
            printf("* Play: nick %s plays video %s playtime %d totalplaytime %d\n", param1, param2, Video.playTime, User.totalPlayTime);
        }else {
            puts("+ Error: Play not possible");
        }
    } else {
        puts("+ Error: Play not possible");
    }


}

void Stats(char *commandNumber, char command, tUserList lista) {

    //Cabecera
    Header(commandNumber,command,' ',"","","","","","");

    if (isEmptyList(lista)){ //Comprueba que la lista no esté vacía
        puts("+ Error: Stats not possible");
    }else{

        tPlayTime contSU = 0, contSP = 0, contPU = 0, contPP = 0;
        float avg1, avg2;
        tUserPos p = first(lista);
        tUserItem User;
        tVideoItem Video;

        while (p != NULL_USER){ //Recorre todos los usuarios de la lista
            User = getItem(p, lista);//Obtiene el usuario
            printf("*Nick %s category %s totalplaytime %d\n", User.nickname, User.userCategory == 0 ? "standard" : "premium", User.totalPlayTime);

            if (!isEmptyListV(User.videoList)) { //Comprueba si la lista de vídeos no está vacía
                tVideoPos q = firstV(User.videoList);

                while (q != NULL_VIDEO) { //Pasa por todas las posiciones de la lista
                    Video = getItemV(q, User.videoList);

                    printf("Video %s playtime %d\n", Video.titleVideo, Video.playTime);
                    q = nextV(q, User.videoList);
                }
            } else {
                puts("No videos");
            }

            if (User.userCategory == 0){ //Actualiza los contadores de cada categoría
                contSU++;
                contSP += User.totalPlayTime;
            }else{
                contPU++;
                contPP += User.totalPlayTime;
            }
            p = next(p, lista);
        }

        if (contSU == 0){ //Comprueba si el número de usuarios es 0 porque no se puede dividir por 0
            avg1 = 0;
        }else{
            avg1 = (float)contSP / (float)contSU;
        }
        if (contPU == 0){ //Comprueba si el número de usuarios es 0 porque no se puede dividir por 0
            avg2 = 0;
        }else{
            avg2 = (float)contPP / (float)contPU;
        }

        puts("Category  Users  TimePlay  Average");
        printf("Standard %6d %9d %8.2f\n", contSU, contSP, avg1);
        printf("Premium  %6d %9d %8.2f\n", contPU, contPP, avg2);
    }

}

void Remove(char *commandNumber, char command, char *param1, tUserList *lista){
    //Cabecera
    Header(commandNumber,command,':',"maxtime",param1,"","","","");

    tUserPos p = last(*lista);
    tUserItem User;
    int aux = 0;

    while (p != NULL_USER){ //Recorre todos los usuarios de la lista
        User = getItem(p, *lista);//Obtiene el usuario
        tUserPos q = p;
        p = previous(p,*lista);

        if (User.userCategory == 0 && User.totalPlayTime > strtol(param1, NULL, 10) ) {
            printf("Removing nick %s totalplaytime %d\n", User.nickname, User.totalPlayTime);

            while (!isEmptyListV(User.videoList)){ //Borra la lista de videos del usuario
                deleteAtPositionV(firstV(User.videoList), &User.videoList);
            }

            deleteAtPosition(q,lista);
            aux++;
        }

    }

    if (aux == 0){
        puts("+ Error: Remove not possible");
    }

}


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tUserList *L) {

    switch(command) {
        case 'N': {
            New(commandNumber, command, param1, param2, L);
            break;
        }
        case 'D': {
            Delete(commandNumber, command, param1, L);
            break;
        }
        case 'A': {
            Add(commandNumber, command, param1, param2, L);
            break;
        }
        case 'P': {
            Play(commandNumber, command, param1, param2,param3, L);
            break;
        }
        case 'S': {
            Stats(commandNumber, command, *L);
            break;
        }
        case 'R': {
           Remove(commandNumber, command, param1, L);
            break;
        }
        default: {
            break;
        }
    }
}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;
    tUserList L;
    createEmptyList(&L);
    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3, &L);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
