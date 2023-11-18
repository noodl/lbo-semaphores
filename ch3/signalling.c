#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* thread_function1(void* ptr) {
    sem_wait(&semaphore);
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

void* thread_function2(void* ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
    sem_post(&semaphore);
}

int main() {
    pthread_t thread1, thread2;

    sem_init(&semaphore, 0, 0);

    char *message1 = "Thread 1";
    char *message2 = "Thread 2";

    pthread_create(&thread1, NULL, thread_function1, (void*) message1);
    pthread_create(&thread2, NULL, thread_function2, (void*) message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
