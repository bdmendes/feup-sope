#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[], char* envp[]){
    //to disassemble, run "objdump -d test-read"
    char arr[3];
    read(open("file", O_RDONLY), arr, 2);
    printf("%s\n",arr);
}
