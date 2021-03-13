#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

volatile static int should_exit =
    0;  // it's changed in polling, so disable optimizations

void handler(int signo) {
  printf("Hi from process %d! Received signal: %d\n", getpid(), signo);
  if (signo == SIGINT) {
    should_exit = 1;
  }
}

int main() {
  // define signal handling before fork(), so it is inherited
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = handler;
  sigaction(SIGINT, &action, NULL);
  action.sa_handler = handler;
  sigaction(SIGUSR1, &action, NULL);

  printf("I'm a newly born process: %d\n", getpid());
  fflush(stdout);
  pid_t id = fork();
  if (id == 0) {
    printf("I'm a newly born child process: %d\n", getpid());
    fflush(stdout);
    pid_t id2 = fork();
    if (id2 == 0) {
      printf("I'm a newly born grand child process: %d\n", getpid());
      fflush(stdout);
    }
  }

  // executed by all processes
  while (!should_exit) {
    continue;
  }
  printf("Process %d exiting...\n", getpid());
  fflush(stdout);
}