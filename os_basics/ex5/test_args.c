#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]){
    for (int i = 0; i < argc; ++i){
        printf("arg %d: %s\n",i,argv[i]);
    }
    printf("\n");
    for (int i = 0; ; ++i){
        if (envp[i] == NULL) break;
        printf("env var %i name: %s\n", i, strtok(envp[i], "="));

        //"in order to get next token and to continue with the same string
        //NULL is passed as first argument since strtok maintains a static pointer to your previous passed string"
        printf("env var %i path: %s\n\n", i, strtok(NULL, "="));
    }
}
