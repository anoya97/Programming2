/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practica 1
 * AUTHOR 1: Raúl Fernández del Blanco LOGIN 1: r.delblanco
 * AUTHOR 2: Armando Martínez Noya LOGIN 2: a.mnoya
 * GROUP: 2.4
 * DATE: 09 / 04 / 21
 */


#include <stdio.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif


void New(char *commandNumber, char command, char *param1, char *param2, tList *lista) {

    //Cabecera
    printf("********************\n");
    printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);

    //Creación del usuario utilizado
    tItemL User;
    strcpy(User.nickname, param1);
    User.numPlay = 0;
    if (strcmp(param2, "standard") == 0){
        User.userCategory = 0;
    }else{
        User.userCategory = 1;
    }

    if (findItem(User, *lista) != LNULL) { //Comprueba si el usuario introducido ya existe
        printf("+ Error: New not possible\n");
    } else {
        if(insertItem(User, LNULL, lista)) { //Inserta el usuario en la lista en la ultima posición
            printf("* New: nick %s category %s\n", User.nickname, User.userCategory == 0 ? "standard" : "premium");
        } else{ //En caso de que la lista esté llena o que falle la creación del nodo
            printf("+ Error: New not possible\n");
        }
    }

}

void Delete(char *commandNumber, char command, char *param1, tList *lista){

    //Cabecera
    printf("********************\n");
    printf("%s %c: nick %s\n", commandNumber, command, param1);

    tItemL User;

    strcpy(User.nickname, param1);
    tPosL p = findItem(User, *lista); //Busca la posición del usuario introducido

    if (p != LNULL){ //Comprueba que el usuario se encuentra en la lista
        User = getItem(p, *lista); //Obtiene el usuario
        deleteAtPosition(p, lista); //Elimina el usuario
        printf("* Delete: nick %s category %s numplays %d\n" , param1, User.userCategory == 0 ? "standard" : "premium", User.numPlay);
    } else {
        printf("+ Error: Delete not possible\n");
    }

}

void Play(char *commandNumber, char command, char *param1, char* param2, tList *lista){

    //Cabecera
    printf("********************\n");
    printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);

    tItemL User;

    strcpy(User.nickname, param1);
    tPosL p = findItem(User, *lista); //Busca la posición del usuario introducido


    if (p != LNULL){ //Comprueba que el usuario se encuentra en la lista
        User = getItem(p, *lista); //Obtiene el usuario
        User.numPlay++; //Aumenta el número de reproducciones en una unidad
        updateItem(User, p, lista); //Lo actualiza en la lista
        printf("* Play: nick %s plays video %s numplays %d\n" , param1, param2, User.numPlay);
    } else {
        printf("+ Error: Play not possible\n");
    }

}

void Stats(char *commandNumber, char command, tList lista) {
    tNumPlay contSU = 0, contSP = 0, contPU = 0, contPP = 0;
    float avg1, avg2;
    tPosL p;
    tItemL User;

    //Cabecera
    printf("********************\n");
    printf("%s %c\n", commandNumber, command);

    if (isEmptyList(lista)){ //Comprueba que la lista no esté vacía
        printf("+ Error: Stats not possible");
    }else{
        p = first(lista);
        while (p != LNULL){ //Recorre todos los usuarios de la lista
            User = getItem(p, lista);//Obtiene el usuario
            printf("Nick %s category %s numplays %d\n", User.nickname, User.userCategory == 0 ? "standard" : "premium", User.numPlay);
            if (User.userCategory == 0){ //Actualiza los contadores de cada categoría
                contSU++;
                contSP += User.numPlay;
            }else{
                contPU++;
                contPP += User.numPlay;
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

        printf("Category  Users  Plays  Average\n");
        printf("Standard    %d     %d     %.2f\n", contSU, contSP, avg1);
        printf("Premium     %d     %d     %.2f\n", contPU, contPP, avg2);
    }

}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *list) {

    switch(command) { //Se encarga de elegir la tarea indicada
        case 'N': {
            New(commandNumber, command, param1, param2, list);
            break;
        }
        case 'D': {
            Delete(commandNumber, command, param1, list);
            break;
        }
        case 'P': {

            Play(commandNumber, command, param1, param2, list);
            break;
        }
        case 'S': {
            Stats(commandNumber, command, *list);
            break;
        }
        default: {
            break;
        }
    }

}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2;
    tList list;
    createEmptyList(&list);

    df = fopen(filename, "rb");
    if (df != NULL) { //Comprueba que el fichero se pueda abrir
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) { //Lectura línea a línea de los ficheros
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, &list);
        }
        fclose(df); //Cierra el archivo

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args){

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


