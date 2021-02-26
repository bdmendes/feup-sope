#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // On success, the PID of the child process is returned in the parent, and 0
  // is returned in the child
  pid_t process_id = fork();
  int stat_loc = 0;
  switch (process_id) {
  case -1:
    perror("fork failed");
    return -1;
  case 0: // In the child
    printf("Hello ");
    break;
  default:           // In the parent
    wait(&stat_loc); // Mandatory; no way to know which one would run first
    printf("World!\n");
    break;
  }
  // Should we need to invert the order (the parent acting first), signals are
  // needed
}
