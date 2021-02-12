#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_in(const char* s, char** arr, int size){
    for (int i = 1; i < size; ++i){
        if (strcmp(s,arr[i]) == 0) return true;
    }
    return false;
}

int main(int argc, char* argv[], char* envp[]){
    for (int i = 0; i < argc; ++i){
        printf("arg %d: %s\n",i,argv[i]);
    }
    printf("\n");
    for (int i = 0; envp[i] != NULL; ++i){
        char* var_name = strtok(envp[i], "=");
        if (!is_in(var_name,argv,argc)) continue;

        printf("env var %i name: %s\n", i, var_name);

        //in order to get next token and to continue with the same string
        //NULL is passed as first argument since strtok maintains a static pointer to your previous passed string
        printf("env var %i path: %s\n\n", i, strtok(NULL, "="));
    }
}
