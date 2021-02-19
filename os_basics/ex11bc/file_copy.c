#include <stdio.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for read()
#include <stdbool.h>

// run "man 2 <syscall> to view the documentation"

int main(int argc, char** argv){
    bool write_to_stdout = true;
    char* file1_path, *file2_path;
    FILE* f1, *f2;
    if (argc == 2){
        file1_path = argv[1];
    }
    else if (argc == 3){
        file1_path = argv[1];
        file2_path = argv[2];
        write_to_stdout = false;
    }
    else {
        perror("invalid number of arguments");
        return -1;
    }

    f1 = fopen(file1_path, "r"); // "r" so that open() is called with O_RDONLY
    if (f1 == NULL){
        perror("file1 not found");
        return -1;
    }
    if (!write_to_stdout){
        f2 = fopen(file2_path, "w");
        if (f2 == NULL){
            perror("file2 not found");
            return -1;
        }
    }

    int i,j; // store read and written bytes
    char buf[1024];
    while ( (i = fread(&buf, sizeof(char), sizeof(buf), f1)) > 0){
        if (write_to_stdout){
            fwrite(&buf, sizeof(char), i, stdout);
        }
        else {
            j = fwrite(&buf, sizeof(char), i, f2);
            if (j <= 0){
                perror("error writing to file2!");
                fclose(f1);
                fclose(f2);
                return -1;
            }
        }
    }

    fclose(f1);
    if (!write_to_stdout) fclose(f2);
    return 0;
}
