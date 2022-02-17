/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3) {

    switch(command) {
        case 'N': {
            break;
        }
        /* ... */
        default: {
            break;
        }
    }
}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;

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
            processCommand(commandNumber, command[0], param1, param2, param3);
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
