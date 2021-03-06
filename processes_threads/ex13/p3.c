#include <unistd.h> // for pipe()
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    if (pipe(fd) == -1){
        perror("pipe failed");
        return -1;
    }
    int id = fork();
    if (id == 0){
        char w[100];
        if (read(fd[0], w, 100) == -1){ // will block until parent writes to pipe
            perror("error reading from pipe");
            return -1;
        }
        char* w2 = "Systems";
        char* str = strcat(w,w2);
        write(fd[1], str, strlen(str) + 1);
        close(fd[0]);
        close(fd[1]);
    } else {
        const char* str1 = "Operating ";
        if (write(fd[1], str1, strlen(str1) + 1) == -1){
            perror("error writing to pipe");
            return -1;
        }
        close(fd[1]);
        wait(NULL); // wait for the child to finish
        char w[100];
        if (read(fd[0], w, 100) == -1) return -1;
        printf("%s\n",w);
        close(fd[0]);
    }
}