#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <sched.h>
#include <time.h>

long n;
double fifo, oth, rr;
int con1 = 0, con2 = 1, con3 = 1;

void *C1()
{
    // Set thread scheduling policy to SCHED_OTHER
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &(struct sched_param){con1++});

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    while (n > 0)
    {
        n--;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    oth = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    return NULL;
}

void *C2()
{
    // Set thread scheduling policy to SCHED_RR
    pthread_setschedparam(pthread_self(), SCHED_RR, &(struct sched_param){con2++});

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    while (n > 0)
    {
        n--;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    rr = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    return NULL;
}

void *C3()
{
    // Set thread scheduling policy to SCHED_FIFO
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &(struct sched_param){con3++});

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    while (n > 0)
    {
        n--;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    fifo = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    return NULL;
}

int main()
{
    n = (long)pow(2, 32);
    pthread_t Thr_C1, Thr_C2, Thr_C3;
    double oth_t = 0, rr_t = 0, fifo_t = 0;
    FILE *file = fopen("Output1.txt", "w");

    int i = 0;
    while (i <= 5)
    {
        pthread_create(&Thr_C1, NULL, C1, NULL);
        pthread_create(&Thr_C2, NULL, C2, NULL);
        pthread_create(&Thr_C3, NULL, C3, NULL);
        pthread_join(Thr_C1, NULL);
        pthread_join(Thr_C2, NULL);
        pthread_join(Thr_C3, NULL);
        oth_t += oth;
        rr_t += rr;
        fifo_t += fifo;
        fprintf(file, "%lf\n%lf\n%lf\n", oth, rr, fifo);
        i++;
    }
    printf("Avg. Time taken by the thread using SCHED_RR is: %lf\n", rr_t / 5);
    printf("Avg. Time taken by the thread using SCHED_FIFO is: %lf\n", fifo_t / 5);
    printf("Avg. Time taken by the thread using SCHED_OTHER is: %lf\n", oth_t / 5);

    return 0;
}
