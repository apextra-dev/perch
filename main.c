#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signo) {
    printf("\nperch> ");
    fflush(stdout);
}

int main() 
{
    signal(SIGINT, handler);
    printf("Welcome to Perch v0.0.1\n\n");

    struct dirent *de; 

    while (1)
    {
        printf("perch> ");
        fflush(stdout);

        char str[100];

        if(fgets(str, sizeof(str), stdin) == NULL) {
            printf("\n");
            continue;
        }

        char *command = strtok(str, " \n");

        if(command == NULL) {
            continue;
        }

        char *arg = strtok(NULL, " \n");

        if(strcmp(command, "exit") == 0) {
            printf("Ending...\n");
            break;
        }
        else if(strcmp(command, "ls") == 0) {
            DIR *dir = opendir(".");

            if(dir == NULL) {
                printf("Could not open current directory\n");
                continue;
            }

            if((de = readdir(dir)) != NULL) {
                printf("\n");
                while ((de = readdir(dir)) != NULL) 
                {
                    if(de->d_name[0] == '.') continue;
                    printf("%s\n", de->d_name);
                }

                printf("\n");
                closedir(dir);
                continue;
            }

            continue;
        }
        else if(strcmp(command, "cd") == 0) {
            if(arg == NULL) {
                char *home_dir = getenv("HOME");

                if(home_dir == NULL) {
                    printf("cd: HOME was not found\n");
                } else {
                    if(chdir(home_dir) != 0) {
                        printf("cd: Could not look up home directoty\n");
                    }
                }
            } else {
                if(chdir(arg) != 0) {
                    printf("cd: No such file or directory\n");
                }
            }
        }
        else if(strcmp(command, "help") == 0) {
            printf("== Perch help page ==\n\n");


            printf("Commands: \n");

            printf("+ help - Open the help page\n");
            printf("+ ls - Show you files and directories in current directory\n");
            printf("+ cd - Go to a required directory\n");
            printf("+ exit - Leave perch\n\n");

            printf("=====================\n");
            continue;
        }
        else {
            printf("Unknown command <%s>\n", command);
        }
    }
    return 0;
}