/*
Demo of using a semaphore to signal between threads.
The message from thread 2 should always print before the message
from thread 1.
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* thread_function1(void* arg) {
    sem_wait(&semaphore);
    printf("Thread 1\n");
}

void* thread_function2(void* arg) {
    printf("Thread 2\n");
    sem_post(&semaphore);
}

int main() {
    pthread_t thread1, thread2;

    sem_init(&semaphore, 0, 0);

    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
