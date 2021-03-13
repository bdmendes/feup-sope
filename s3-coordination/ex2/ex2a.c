#define _GNU_SOURCE  // so that execvpe which is a GNU extension is included
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// preparation for exec:
char *cmdline[] = {"sleep", "30", (void *)0};
char *newenviron[] = {"USER=Linus", NULL};

int main() {
  pid_t id;
  setbuf(stdout, NULL);  // to make sure printf() have no buffer so, nodelay!

  printf("\nParent: %d. USER=%s", getpid(), getenv("USER"));

  id = fork();
  switch (id) {
    case -1:
      perror("fork()");
      exit(1);
    case 0:
      printf("\nChild: %d. USER=%s", getpid(), getenv("USER"));
      printf(
          "\nChild: check that exec was succeful with: \"ps x | grep "
          "sleep\"\n");
      if (execvpe("/bin/sleep", cmdline, newenviron) == -1) {
        perror("execve");
      }
      printf(
          "\nIf you see this, exec failed and current process was not "
          "replaced\n");
      break;
    default:
      printf("\nParent still: %d. USER=%s", getpid(), getenv("USER"));
  }
  return 0;
}
