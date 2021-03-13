#define _GNU_SOURCE  // so that execvpe which is a GNU extension is included
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// preparation for exec:
char *cmdline[] = {"sleep", "5", (void *)0};
char *newenviron[] = {"USER=Linus", NULL};

int main() {
  pid_t id;
  setbuf(stdout, NULL);  // to make sure printf() have no buffer so, nodelay!

  printf("\nParent: %d. USER=%s\n", getpid(), getenv("USER"));

  id = fork();
  switch (id) {
    case -1:
      perror("fork()");
      exit(1);
    case 0:
      printf("Child: %d. USER=%s\n", getpid(), getenv("USER"));
      printf(
          "Child: check that exec was succeful with: \"ps x | grep "
          "sleep\"\n");
      if (execvpe("/bin/sleep", cmdline, newenviron) == -1) {
        perror("execve");
      }
      printf(
          "If you see this, exec failed and current process was not "
          "replaced\n");
      break;
    default:
      printf("Parent still: %d. USER=%s\n", getpid(), getenv("USER"));
      int status = -1;
      if (waitpid(id, &status, 0) <=
          0) {  // or wait(&status) since only one child exists
        perror("could not obtain child termination code");
        return (EXIT_FAILURE);
      };
      printf("Child process terminated with status code %d\n", status);
      printf("\nParent after child terminated: %d. USER=%s\n", getpid(),
             getenv("USER"));
  }
  return 0;
}
