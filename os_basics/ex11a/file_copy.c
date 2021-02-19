#include <stdio.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for read()

// run "man 2 <syscall> to view the documentation"

int main(int argc, char** argv){
    if (argc != 3) return -1;
    char* file1 = argv[1];
    char* file2 = argv[2];

    /* check if file1 exists and open it */
    // one could also open file2 here, and pass later its descriptor
    int f1_open = open(file1, O_RDONLY);
    if (f1_open <= 0){
        fprintf(stderr,"could not open file1: %s", file1);
        return -1;
    }

    /* read file1 contents to buffer and then close it */
    char buf[1024];
    // pass current file descriptor as first parameter
    // returns number of bytes read, or 0 (error or eof reached)
    // note that there is no "eof" byte in a file
    int bytes_read_from_f1 = read(f1_open, buf, sizeof(buf));
    if (bytes_read_from_f1 == 0){
        // could wrap in a loop, and read in f1 + write in f2 at once
        // allowing to read the entire file
        perror("Did not allocate more than 1024 bytes, exiting...");
        close(f1_open);
        return -1;
    }
    printf("read %d bytes from %s\n", bytes_read_from_f1, file1);
    close(f1_open);

    int f2_open = open(file2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (f2_open <= 0){
        fprintf(stderr,"could not access file2: %s", file2);
        return -1;
    }
    // do not write junk from buf, only whats defined!
    int f2_write = write(f2_open, buf, bytes_read_from_f1);
    if (f2_write == -1){
        perror("error writing to file2!");
        close(f2_open);
        return -1;
    }
    close(f2_open);

    return 0;
}
