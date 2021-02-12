#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void exit_message(){
    printf("I'm called by atexit\n");
}

int main(){
    int i = atexit(exit_message);
    if (i) {
        printf("Could not set atexit function!\n");
        exit(0);
    }
    sleep(5); // your chance to push ctrl-c now
}
