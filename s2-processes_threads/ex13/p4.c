#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

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
        int fd = open("myfifo", O_RDWR);
        if (fd == -1) return -1;
        char w[100];
        if (read(fd, w, 100) == -1){
            perror("error reading from pipe");
            return -1;
        }
        char* w2 = "Systems";
        char* str = strcat(w,w2);
        write(fd,str,strlen(str)+1);
        if (close(fd) == -1) return -1;
    } else {
        int fd = open("myfifo",O_RDWR);
        if (fd == -1) return -1;
        if (write(fd, "Operating ", 11) == -1){
            perror("error writing to pipe");
            return -1;
        }
        wait(NULL);
        char buf[100];
        if (read(fd, buf, 100) == -1) return -1;
        printf("%s\n",buf);
        if (close(fd) == -1) return -1;
    }
}