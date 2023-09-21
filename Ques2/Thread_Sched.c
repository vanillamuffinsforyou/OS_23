#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <math.h>

#define NUM_THREADS 3
#define NUM_ITERATIONS 5

long n;
double times[NUM_THREADS];
int priorities[NUM_THREADS] = {SCHED_OTHER, SCHED_RR, SCHED_FIFO};

void *count(void *arg)
{
    int thread_num = *((int *)arg);
    struct sched_param sch_params;
    sch_params.sched_priority = thread_num + 1;
    pthread_setschedparam(pthread_self(), priorities[thread_num], &sch_params);

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long i = 1; i < n; i++)
    {
    }
    clock_gettime(CLOCK_REALTIME, &finish);

    times[thread_num] = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    return NULL;
}

int main()
{
    n = (long)pow(2, 32);
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1, 2};
    double avg_times[NUM_THREADS] = {0};

    FILE *file = fopen("Output1.txt", "w");

    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++)
    {
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, count, &thread_ids[i]);
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
            avg_times[i] += times[i];
            fprintf(file, "%lf\n", times[i]);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        printf("Avg. Time taken by the thread using %s is: %lf\n",
               (priorities[i] == SCHED_OTHER) ? "SCHED_OTHER" : ((priorities[i] == SCHED_RR) ? "SCHED_RR" : "SCHED_FIFO"),
               avg_times[i] / NUM_ITERATIONS);
    }

    fclose(file);
    return 0;
}
