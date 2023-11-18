#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/*
Demonstrates using a semaphore to implement a multiplex.
A hotel has a fixed number of rooms available but there
are more guests than that waiting. The guests are represented
by threads and a semaphore is used to store the number of
remaining rooms available.
*/

#define NUM_ROOMS 6
#define NUM_GUESTS 20

sem_t rooms_available;

void sleep_random_interval() {
    struct timespec ts;
    ts.tv_sec = 0;
    // Random number between 0.5 and 1 seconds in nanoseconds
    ts.tv_nsec = (rand() % (500000001)) + 500000000;

    nanosleep(&ts, NULL);
}

void *visit(void *arg) {
    int thread_num = *((int *) arg);

    printf("TH(%2d) Waiting at checking queue\n", thread_num);
    sem_wait(&rooms_available);
    printf("TH(%2d) Got a room, sleeping..\n", thread_num);
    sleep_random_interval();
    printf("TH(%2d) Garcon, coffee!\n", thread_num);
    sem_post(&rooms_available);
    printf("TH(%2d) Room key returned\n", thread_num);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_GUESTS];
    int *arg;

    // Seed the random number generator, otherwise rand() always
    // returns the same value.
    srand(time(NULL));

    sem_init(&rooms_available, 0, NUM_ROOMS);

    for (int i = 0; i < NUM_GUESTS; i++) {
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

    return EXIT_SUCCESS;
}
