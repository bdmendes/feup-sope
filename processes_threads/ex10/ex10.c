#include <pthread>

#include "stdio.h"

void* my_print(void* str) {
  const char* mstr = (const char*)str;
  printf("%s\n", mstr);
  pthread_exit(NULL);
}

int main() { const char* strings[] = {"Operating", "Systems"}; }