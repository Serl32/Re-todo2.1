#include <stdio.h>
#include <time.h>
#include "corelib.h"
#include <string.h>

int main(int argc, char *argv[]) {

    //void greeting() {
    //    time_t t;
    //    time(&t);

    //    printf("\n# \tRe-ToDo Version %s %100s\n", CURRENT_VERSION, ctime(&t));

    //    printf("# A Simple To-Do List Program written in C by Serl.\n");
    //    printf("# The data files are located in the same folder where the program is located.\n");
    //    printf("# for easier access and backup, this program will save the files in the .txt format or JSON format.\n");
    //    printf("# A seperate database and management features aren't currently available.\n");
    //    printf("# Use \"-h\" as the artument for more information and help.\n");
    //    printf("# The main.c source file was corrupted and rewriting the code again.\n");
    //}

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
            LIST_ALL(argv[2]);
        } else if (strcmp(argv[1], "-n")==0) {
            if (argc == 3) {
                CREATE_NEW(argv[2]);
            } else if (argc == 4) {
                CREATE_SUBTODO(argv[2], argv[3]);
            } else {
                printf("Not enough arguments, Add your title as \"Your title\" as argument.\n");
            }
        } else if (strcmp(argv[1], "-q")==0) {
            if (argc == 3) {
                QUERY_ONE(argv[2]);
            } else {
                printf("Not enough arguments. Add your database name with your arguments.\n");
            }
        } else if (strcmp(argv[1], "-c")==0) {
            if (argc == 3) {
                COMPLETE_ONE(argv[2]);
            } else {
                printf("Not enough arguments. Add your ToDo Id as an arguments.\n");
            }
        } else if (strcmp(argv[1], "init")==0) {
            if (argc == 3) {
                CREATE_DB(argv[2]);
            } else {
                printf("Not enough arguments. Add your database name with your current argument.\n");
            }
        } else {
            printf("Argument %s is undefined. Try \"-h\" for more information.\n");
        }
    } else {
        greeting();
    }
    return 0;
}
