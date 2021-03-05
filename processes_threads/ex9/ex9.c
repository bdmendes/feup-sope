/*
 *	Example of threads in action
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void* rot(void* arg) {  // our threads start routine
  printf("\n\t In thread PID: %d ; TID: %lu.", getpid(),
         (unsigned long)pthread_self());
  int* retval = malloc(sizeof(int));
  int n = *((int*)arg);
  *retval = n * n;
  pthread_exit((void*)retval);
}

int main() {
  int i;                    // thread counter
  pthread_t ids[NTHREADS];  // storage of (system) Thread Identifiers

  // Must allocate on the heap
  // Would we allocate on the stack on each iteration, would get popped
  // (eventually) in the next iteration (would the thread be faster? don't know)
  int* id_copies = malloc(3 * sizeof(int));
  for (int i = 0; i < NTHREADS; ++i) {
    ids[i] = i;
    id_copies[i] = ids[i];
    printf("%d, %d, \n", ids[i], id_copies[i]);
  }

  setbuf(stdout, NULL);  // only for debugging
  printf("\nMain thread PID: %d ; TID: %lu.\n", getpid(),
         (unsigned long)pthread_self());

  // new threads creation
  for (i = 0; i < NTHREADS; i++) {
    if (pthread_create(&ids[i], NULL, rot, (void*)(id_copies + i)) !=
        0)       // pass
      exit(-1);  // here, we decided to end process
    else
      printf("\nNew thread %d ; TID: %lu.", i, (unsigned long)ids[i]);
  }

  // wait for finishing of created threads
  for (i = 0; i < NTHREADS; i++) {
    void* retval;
    pthread_join(ids[i], &retval);  // Note: threads give no termination code
    printf("\nTermination of thread %d: %lu, with retval: %d", i,
           (unsigned long)ids[i], *((int*)retval));
  }

  // free memory
  free(id_copies);

  printf("\n");
  pthread_exit(NULL);  // here, not really necessary...
  return 0;            // will not run this!
}
