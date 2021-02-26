#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void func(int signo) {
  fprintf(stderr, "\nDefault handler, received signal %d!\n", signo);
}

int main() {
  struct sigaction new, old;
  sigset_t smask; // defines signals to block while func() is running

  // prepare struct sigaction
  if (sigemptyset(&smask) == -1) // block no signal
    perror("sigsetfunctions");

  new.sa_handler = func; // default sig handler (should do more than printing!)
  new.sa_mask = smask;
  new.sa_flags = 0; // usually works

  if (sigaction(SIGUSR1, &new, &old) ==
      -1) // better alternative to signal(), which is an older version with less
          // options; allows setting up default signal handling action
    perror("sigaction");

  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork failed");
    return -1;
  case 0: // Child
    printf("Hello ");
    kill(pid, SIGUSR1);
    break;
  default: // Parent
    pause();
    printf("World!\n");
    break;
  }

  return 0;
}
