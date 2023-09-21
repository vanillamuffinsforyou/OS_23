
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <math.h>
#include <unistd.h>   // Include for fork() and execl()
#include <sys/wait.h> // Include for wait()

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
    long i = 1;
    while (i < n)
    {
        i++;
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

    pid_t child_pid; // Store the child process ID

    int iteration = 0;
    while (iteration < NUM_ITERATIONS)
    {
        // Create a child process
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (child_pid == 0)
        {
            // This code runs in the child process
            execl("./child_program", "./child_program", NULL);
            perror("execl"); // Print an error if execl() fails
            return 1;
        }
        else
        {
            // This code runs in the parent process
            // Wait for the child process to finish
            int status;
            wait(&status);

            int i = 0;
            while (i < NUM_THREADS)
            {
                pthread_create(&threads[i], NULL, count, &thread_ids[i]);
                i++;
            }

            i = 0;
            while (i < NUM_THREADS)
            {
                pthread_join(threads[i], NULL);
                i++;
            }

            i = 0;
            while (i < NUM_THREADS)
            {
                avg_times[i] += times[i];
                fprintf(file, "%lf\n", times[i]);
                i++;
            }
        }
        iteration++;
    }

    int i = 0;
    while (i < NUM_THREADS)
    {
        printf("Avg. Time taken by the thread using %s is: %lf\n",
               (priorities[i] == SCHED_OTHER) ? "SCHED_OTHER" : ((priorities[i] == SCHED_RR) ? "SCHED_RR" : "SCHED_FIFO"),
               avg_times[i] / NUM_ITERATIONS);
        i++;
    }

    fclose(file);
    return 0;
}
