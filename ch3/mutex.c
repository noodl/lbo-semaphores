/*
Demonstration of using a semaphore to implement a mutex.
Two threads increment a shared variable.  The variable should
end up with the sum of all increments with no loses.
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0;
sem_t mutex;
#define ITERATIONS 1000000

void *inc(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        sem_wait(&mutex);
        count++;
        sem_post(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    sem_init(&mutex, 0, 1);

    if (pthread_create(&tid1, NULL, inc, NULL) != 0)
        printf("Error creating thread 1\n");
    if (pthread_create(&tid2, NULL, inc, NULL) != 0)
        printf("Error creating thread 2\n");

    if (pthread_join(tid1, NULL) != 0)
        printf("Error joining thread 1\n");
    if (pthread_join(tid2, NULL) != 0)
        printf("Error joining thread 2\n");

    if (count < 2 * ITERATIONS)
        printf("BOOM! count is [%d], should be %d\n", count, 2 * ITERATIONS);
    else
        printf("OK! count is [%d]\n", count);

    return 0;
}
