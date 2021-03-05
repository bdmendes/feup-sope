#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "stdio.h"

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct MyStr {
  char** strings;
  int currToPrint;
  int n;
} MyStr;


void* my_print(void* ss) {
    // Using mutexes to avoid data races issues
    MyStr* ss_p = (MyStr*)ss;
    pthread_mutex_lock(&my_mutex); // acquire lock; other threads will block here
    if (ss_p->currToPrint < ss_p->n) printf("%s ", ss_p->strings[ss_p->currToPrint++]);
    pthread_mutex_unlock(&my_mutex); // unlock mutex for other threads
    pthread_exit(NULL);
}

int main() {
    MyStr ss;
    char* strings[] = {"Operating", "Systems"};
    bool done[] = {false, false};
    ss.strings = strings;
    ss.currToPrint = 0;
    ss.n = 2;
    pthread_t ids[2];
    if (pthread_create(&ids[0], NULL, my_print, (void*)(&ss)) != 0) return -1;
    if (pthread_create(&ids[1], NULL, my_print, (void*)(&ss)) != 0) return -1;

    // Wait until thread completion, otherwise would finish abruptly
    for (int i = 0; i < 2; i++) {
        pthread_join(ids[i], NULL);
    }
}