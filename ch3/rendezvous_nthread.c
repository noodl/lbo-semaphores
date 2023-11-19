#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

/*
Implements a rendezvous that's generalised for N threads,
rather than just 2 like rendezvous.c
*/

#define NUM_THREADS 10

sem_t waiting_mutex;
int waiting = 0;
sem_t barrier;

int atomically_increment_waiting(void) {
    int rv;
    sem_wait(&waiting_mutex);
    rv = ++waiting;
    sem_post(&waiting_mutex);
    return rv;
}

void unlock_barrier(void) {
    for (int i = 0; i < NUM_THREADS; i++) {
        sem_post(&barrier);
    }
}

/*
Atomically increment the shared waiting counter and sleep if it hasn't reached
the number of threads yet. The last thread to reach the rendezvous can detect
that it hit the limit then wake all the others up to continue on.
*/
void *thread_function(void *arg) {
    (void)arg; // Stop the compiler complaining about unused args
    int position;

    printf("Before rendezvous\n");
    position = atomically_increment_waiting();
    if (position == NUM_THREADS) {
        // unlock the barrier
        printf("All threads reached the barrier. Unlocking..\n");
        unlock_barrier();
    } else {
        printf("Reached barrier with position = %d\n", position);
        sem_wait(&barrier);
    }
    printf("Through the barrier\n");
    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_THREADS];

    // Initialize globals
    sem_init(&waiting_mutex, 0, 1);
    sem_init(&barrier, 0, 0);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            fprintf(stderr, "Failed to create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("Final value of waiting: %d\n", waiting);

    return EXIT_SUCCESS;
}

/*
Note: this solution seems to work but the book presents a different one where each
thread lets through one other when the limit is reached. Their approach is apparently
called a turnstile.
*/
