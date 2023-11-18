#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/*
Demo of a rendezvous where 2 threads meet at a point in the code.
For this to work whichever thread reaches that point first must wait
for the other to catch up. Uses a pair of semaphores to indicate readiness.
*/

sem_t thread1_ready;
sem_t thread2_ready;

void* thread1_function(void* arg) {
    printf("Thread 1 start\n");

    sem_post(&thread1_ready); // Signal that Thread 1 is ready
    sem_wait(&thread2_ready); // Wait for Thread 2 to be ready

    printf("Thread 1 continuing\n");
}

void* thread2_function(void* arg) {
    printf("Thread 2 start\n");

    sem_post(&thread2_ready); // Signal that Thread 2 is ready
    sem_wait(&thread1_ready); // Wait for Thread 1 to be ready

    printf("Thread 2 continuing\n");
}

int main() {
    // Initialize semaphores
    sem_init(&thread1_ready, 0, 0);
    sem_init(&thread2_ready, 0, 0);

    // Create threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
