#include <stdio.h>
#include <time.h>
#include "corelib.h"
#include <string.h>

int main(int argc, char *argv[]) {

    // If Statements for performing specific functions
    // -h, -l, -n, -q, -c, init

    if (argc != 1) {
        if (strcmp(argv[1], "-h")==0) {

            const int sz = 255;
            char str[sz];

            FILE *fp;

            fp = fopen("help.txt", "r");
            
            if (fp == NULL) {
                printf("Text file isn't available (Create one with \"help.txt\").");
            } else {
                while(fgets(str, sz, fp) != NULL) {
                    printf("%s", str);
                }
                printf("\n");
            }

            fclose(fp);
        } else if (strcmp(argv[1], "-l")==0) {
            // List all ToDos this is supposed to List the logs.
            LIST_ALL();

        } else if (strcmp(argv[1], "-n")==0) {

            //Create New ToDo / SubToDo
            if (argc == 3) {
                CREATE_NEW(argv[2]);
            } else if (argc == 4) {
                int num = atoi(*argv[2]);
                CREATE_SUBTODO(num, argv[3]);
            } else {
                printf("Not enough arguments, Add title \"Your title\" as argument with \"-n\"\n");
            }

        } else if (strcmp(argv[1], "-q")==0) {

            // Query One ToDo, this is supposed to list all the unfinished ToDos.
            if (argc == 3) {
                int num = atoi(*argv[2]);
                QUERY_ONE(num);
            } else {
                printf("Not enough arguments. Add your database name with your arguments.\n");
            }

        } else if (strcmp(argv[1], "-c")==0) {

            // Set one ToDo Completed
            if (argc == 3) {
                int num = atoi(*argv[2]);
                COMPLETE_ONE(num);
            } else {
                printf("Not enough arguments. Add your ToDo Id as arguments.\n");
            }

        } else if (strcmp(argv[1], "init")==0) {

            // Create New Database
            if (argc == 2) {
                CREATE_DB();
            } else {
                printf("Not enough arguments. Add your database name with your current argument.\n");
            }

        } else {

            // Output for the wrong/undefined argument/arguments
            printf("Argument %s is undefined. Try \"-h\" for more information.\n");
        }

    } else {

        // Funtion for no argument
        greeting();

    }

    return 0;
}
