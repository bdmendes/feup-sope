#include "stdio.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("wrong number of arguments\n");
    return -1;
  }
  const char *dir_path = argv[1];
  DIR *dir_stream = opendir(dir_path);
  if (dir_stream == NULL) {
    perror("could not open the directory");
    return -1;
  }
  struct dirent *dp;                           // dir records
  struct stat st_buf;                          // hold file info
  while ((dp = readdir(dir_stream)) != NULL) { // end of directory not reached
    if (dp->d_type != DT_REG)
      continue; // do not read non regular files
    if (stat(dp->d_name, &st_buf) != 0) {
      perror("could not read file info");
      closedir(dir_stream);
      return -1;
    }
    printf("%s: %ld bytes\n", dp->d_name, st_buf.st_size);
  }
  return closedir(dir_stream);
}
