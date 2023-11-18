#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/*
Demonstrates using a semaphore to implement a multiplex.
A hotel with more guests than rooms is represented by a
semaphore. The guests are represented by threads.
*/

#define NUM_ROOMS 6
#define NUM_GUESTS 20

sem_t rooms_available;

void sleep_random_interval() {
    struct timespec ts;
    ts.tv_sec = 0;
    // Random number between 0.5 and 1 seconds in nanoseconds
    ts.tv_nsec = (rand() % 500000001) + 500000000;

    nanosleep(&ts, NULL);
}

void *visit(void *arg) {
    int thread_num = *((int *) arg);

    printf("TH(%2d) Waiting for check in\n", thread_num);
    if (sem_wait(&rooms_available) == -1) {
        perror("Error waiting on semaphore");
        free(arg);
        pthread_exit(NULL);
    }

    printf("TH(%2d) Got a room, sleeping..\n", thread_num);
    sleep_random_interval();
    printf("TH(%2d) Garcon, coffee!\n", thread_num);

    if (sem_post(&rooms_available) == -1) {
        perror("Error posting to semaphore");
        free(arg);
        pthread_exit(NULL);
    }
    printf("TH(%2d) Room key returned\n", thread_num);

    free(arg);
    pthread_exit(NULL);
    return NULL; // Should never be reached
}

int main(void) {
    pthread_t threads[NUM_GUESTS];
    int *arg;

    // Seed the random number generator, otherwise rand() always
    // returns the same value on each program run.
    srand(time(NULL));

    if (sem_init(&rooms_available, 0, NUM_ROOMS) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_GUESTS; i++) {
        // The thread argument needs to live on the heap for it to be available
        // to other threads.
        arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            perror("Couldn't allocate memory for thread arg.");
            exit(EXIT_FAILURE);
        }

        *arg = i;
        if (pthread_create(&threads[i], NULL, visit, arg) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_GUESTS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining thread");
            exit(EXIT_FAILURE);
        }
    }

    // This can fail but the program's about to die anyway
    sem_destroy(&rooms_available);

    return EXIT_SUCCESS;
}
