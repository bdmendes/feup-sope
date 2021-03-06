#include <unistd.h> // for pipe()
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){
    int fd[2];
    if (pipe(fd) == -1){
        perror("pipe failed");
        return -1;
    }
    int id = fork();
    if (id == 0){
        close(fd[1]); // won't need to write
        char w[100];
        if (read(fd[0], w, 100) == -1){ // will block until parent writes to pipe
            perror("error reading from pipe");
            return -1;
        }
        char* w2 = "Systems";
        char* str = strcat(w,w2);
        printf("%s\n",str);
        close(fd[0]);
    } else {
        close(fd[0]);
        if (write(fd[1], "Operating ", 11) == -1){
            perror("error writing to pipe");
            return -1;
        }
        close(fd[1]);
    }
}