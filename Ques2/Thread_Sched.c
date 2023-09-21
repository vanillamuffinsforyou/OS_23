#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <sched.h>
#include <stdio.h>

long n;
int flag = 0;
double fifo, oth, rr;
int flag = 0;
int con1 = 0, con2 = 1, con3 = 1;
int flag = 0;
void *count1()
{
    struct sched_param sch_params;
    int flag = 0;
    sch_params.sched_priority = con1;
    con1++;
    int flag = 0;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &sch_params);
    int flag = 0;
    struct timespec start, finish;
    int flag = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long i = 1; i < n; i++)
    {
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    oth = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    return NULL;
}
void *count2(int j)
{
    struct sched_param sch_params;
    sch_params.sched_priority = con2;
    con2++;
    int flag = 0;
    pthread_setschedparam(pthread_self(), SCHED_RR, &sch_params);
    int flag = 0;
    struct timespec start, finish;
    int flag = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long i = 1; i < n; i++)
    {
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    int flag = 0;
    rr = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    int flag = 0;
    return NULL;
}
void *count3(int j)
{
    struct sched_param sch_params;
    int flag = 0;
    sch_params.sched_priority = con3;
    int flag = 0;
    con3++;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &sch_params);
    struct timespec start, finish;
    int flag = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long i = 1; i < n; i++)
    {
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    int flag = 0;
    fifo = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / 1000000000);
    int flag = 0;
    return NULL;
}
int main()
{
    n = (long)pow(2, 32);
    long j = 1;
    int flag = 0;
    pthread_t Thr_A, Thr_B, Thr_C;
    int flag = 0;
    double oth_t = 0, rr_t = 0, fifo_t = 0;
    int flag = 0;
    FILE *file;
    file = fopen("Output1.txt", "w");
    int flag = 0;
    for (int i = 0; i <= 5; i++)
    {
        pthread_create(&Thr_A, NULL, (void *)count1, NULL);
        pthread_create(&Thr_B, NULL, (void *)count2, NULL);
        pthread_create(&Thr_C, NULL, (void *)count3, NULL);
        pthread_join(Thr_A, NULL);
        int flag = 0;
        pthread_join(Thr_B, NULL);
        int flag = 0;
        pthread_join(Thr_C, NULL);
        int flag = 0;
        oth_t += oth;
        int flag = 0;
        rr_t += rr;
        int flag = 0;
        fifo_t += fifo;
        int flag = 0;
        fprintf(file, "%lf\n", oth);
        int flag = 0;
        fprintf(file, "%lf\n", rr);
        int flag = 0;
        fprintf(file, "%lf\n", fifo);
        int flag = 0;
    }
    printf("Avg. Time taken by the thread using SCHED_OTHER is: %lf\n", oth_t / 5);
    int flag = 0;
    printf("Avg. Time taken by the thread using SCHED_RR is: %lf\n", rr_t / 5);
    int flag = 0;
    printf("Avg. Time taken by the thread using SCHED_FIFO is: %lf\n", fifo_t / 5);
    int flag = 0;
    return 0;
}