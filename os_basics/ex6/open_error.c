#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open()
#include <string.h>

// use shell redirection:
// ./open_error > ofile 2> efile
// ofile will contain stdout output, efile stderr output
int main(int argc, char** argv){
    int i = open("myfile.txt",O_RDWR); // open in read/write mode
    if (i == -1){
        printf("Could not open file! Via stdout\n");
        if (argc == 2 && strcmp(argv[1],"perror") == 0){
            perror("Could not open file! Via stderr; perror call\n");
        }
        else {
            fprintf(stderr,"Could not open file! Via stderr; fprintf call\n");
        }
    }
    else {
        printf("File opened successfully!\n");
    }
}
