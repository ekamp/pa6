#include <stdio.h>
#include "datstr.h"

int main (int argc, char**argv){
printf("size of Order:%d\n", sizeof(struct Order));
printf("size of Node:%d\n", sizeof(struct Node));
printf("size of User:%d\n", sizeof(struct User));
printf("size of ConsumerThreadData:%d\n", sizeof(struct ConsumerThreadData));

printf("size of sem_t:%d\n", sizeof(sem_t));
printf("size of pthread_mutex_t:%d\n", sizeof(pthread_mutex_t));
printf("size of pthread_cond_t:%d\n", sizeof(pthread_cond_t));





}
