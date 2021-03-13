#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void traverse(char path[]) {
  DIR* dir = opendir(path);
  if (dir == NULL) return;
  struct dirent* dirent;
  while ((dirent = readdir(dir)) != NULL) {
    char curr_path[1000];
    sprintf(curr_path, "%s/%s", path, dirent->d_name);
    if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
      struct stat st;
      if (stat(curr_path, &st) == -1) {
        printf("stat failed for file: %s\n", curr_path);
        return;
      }
      if (S_ISDIR(st.st_mode)) {
        printf("Dir: %s\n", curr_path);
        traverse(curr_path);
      } else {
        printf("Regular file: %s\n", curr_path);
      }
    }
  }
}

int main() { traverse("."); }