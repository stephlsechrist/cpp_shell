/****************************************************************
 * Name        :  Stephanie Sechrist                            *
 * Class       :  CSC 415                                       *
 * Date        :                                                *
 * Description :  Writing a simple bash shell program           *
 *                that will execute simple commands. The main   *
 *                goal of the assignment is working with        *
 *                fork, pipes and exec system calls.            *
 ****************************************************************/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/* CANNOT BE CHANGED */
#define BUFFERSIZE 256
/* --------------------*/
#define PROMPT "myShell >> "
#define PROMPTSIZE sizeof(PROMPT)

char
**getInput(char **arguments, char *input) {
//    char buffer[BUFFERSIZE];
//    char **myargv = malloc(BUFFERSIZE * sizeof(char *));

//    printf("%s%s >> ",PROMPT,getenv("PWD"));
//    fgets(buffer, BUFFERSIZE, stdin);
//    strtok(buffer, "\n");
//    char *status = strtok(buffer, " ");
//    int i = 0;
//
//    while (status != NULL) {
//        myargv[i] = status;
////        printf("myargv[%d]: %s\n", i, status);
//        i++;
//        status = strtok(NULL, " ");
//    }
//
//    myargv[i] = NULL;
//    return myargv;
    printf(PROMPT);
    fgets(input, BUFFERSIZE, stdin);

    strtok(input, "\n");
    char *status = strtok(input, " ");
    int i = 0;

    while (status != NULL) {
        arguments[i] = status;
        i++;
        status = strtok(NULL, " ");
    }

    arguments[i] = NULL;
    return arguments;
}

int
getArgCount(char **currArgs) {
    int argCount = 1;
    for (int i = 1; currArgs[i] != NULL; i++) {
        argCount++;
    }

    return argCount;
}

// below does not work; permission always denied.
void
executeArgs(char **currArgs) {
    pid_t pid = fork();
    if (pid < 0)
        perror("Fork failed\n");
        // in parent process
    else if (pid > 0) {

        wait(0);
    }
        // in child process
    else {
//        printf("%s\n", currArgs[0]);
        execvp(currArgs[0], currArgs);
        perror("There was an error in executeArgs");
        exit(96);
//        int exStatus = execvp(args[0], args);
//        if (exStatus < 0) {
//            perror("There was an error during execution");
//            exit(96);
//        }
    }

}

void
inputRedirect(char **currArgs) {
}

void
getpwd() {
    char tempwd[BUFFERSIZE];
    getcwd(tempwd, sizeof(tempwd));
    printf("%s\n", tempwd);
}

void
changeDir(char **thing) {
//    if(strcmp(thing[1],"\0") == 0){
    // if statement if cd is only argument
    // will change to home directory
    if (thing[1] == NULL) {
        const char *homeName = getenv("HOME");
        chdir(homeName);
    } else if (chdir(thing[1]) < 0) {
        printf("No such directory\n");
    } else;
}

int
main(int argc, char **argv) {
    char buffer[BUFFERSIZE];
    char **myargv = malloc(BUFFERSIZE * sizeof(char *));

//    char **myargv;
    int myargc;
    while (1) {
        myargv = getInput(myargv, buffer);
        if (strcmp(myargv[0], "exit") == 0) {
            break;
        }
        myargc = getArgCount(myargv);
//    printf("Number of arguments: %d",myargc);


        if (strcmp(myargv[0], "pwd") == 0) {
            getpwd();
        } else if (strcmp(myargv[0], "cd") == 0) {
            changeDir(myargv);
            // wanted to put in separate execute function. haven't figured out yet
        } else {
            executeArgs(myargv);
//            pid_t pid = fork();
//            if (pid < 0) {
//                perror("Fork failed\n");
//            }
//                // inside child process
//            else if (pid == 0) {
//                int exStatus = execvp(myargv[0], myargv);
//                if (exStatus < 0) {
//                    perror("There was an error during execution");
//                    exit(96);
////            executeArgs(myargv);
//                }
//            }
//
//                // back in parent process
//            else {
//                wait(0);
//            }
        }
    }
    return 0;
}