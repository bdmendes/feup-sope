#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>

// for mkfifo()
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    if (mkfifo("myfifo", 0777) == -1){
        if (errno != EEXIST){
            perror("Making fifo failed");
            return -1;
        }
    }
    int id = fork();
    if (id == 0){
        int fd = open("myfifo", O_RDONLY);
        if (fd == -1) return -1;
        char w[100];
        if (read(fd, w, 100) == -1){
            perror("error reading from pipe");
            return -1;
        }
        char* w2 = "Systems";
        char* str = strcat(w,w2);
        printf("%s\n",str);
        if (close(fd) == -1) return -1;
    } else {
        int fd = open("myfifo",O_WRONLY);
        if (fd == -1) return -1;
        if (write(fd, "Operating ", 11) == -1){
            perror("error writing to pipe");
            return -1;
        }
        if (close(fd) == -1) return -1;
    }
}