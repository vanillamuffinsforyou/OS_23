#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include <time.h>
#include <pthread.h>
#include<math.h>
#include<sched.h>
long n;
double fifo,oth,rr;
int con1=0,con2=1,con3=1;
void *countA(){
    struct sched_param sch_params;
    sch_params.sched_priority=con1;
    con1++;
    pthread_setschedparam(pthread_self(),SCHED_OTHER,&sch_params);
    struct timespec start, finish;
    clock_gettime( CLOCK_REALTIME, &start );
    for(long i=1;i<n;i++){
    }
    clock_gettime( CLOCK_REALTIME, &finish );
    oth= (finish.tv_sec - start.tv_sec)+((finish.tv_nsec - start.tv_nsec)/1000000000);
    return NULL;
}
void *countB(int j){
    struct sched_param sch_params;
    sch_params.sched_priority=con2;
    con2++;
    pthread_setschedparam(pthread_self(),SCHED_RR,&sch_params);
    struct timespec start, finish;
    clock_gettime( CLOCK_REALTIME, &start );
    for(long i=1;i<n;i++){

    }
    clock_gettime( CLOCK_REALTIME, &finish );
    rr=(finish.tv_sec - start.tv_sec)+((finish.tv_nsec - start.tv_nsec)/1000000000);
    return NULL;
}
void *countC(int j){
    struct sched_param sch_params;
    sch_params.sched_priority=con3;
    con3++;
    pthread_setschedparam(pthread_self(),SCHED_FIFO,&sch_params);
    struct timespec start, finish;
    clock_gettime( CLOCK_REALTIME, &start );
    for(long i=1;i<n;i++){

    }
    clock_gettime( CLOCK_REALTIME, &finish );
    fifo=(finish.tv_sec - start.tv_sec)+((finish.tv_nsec - start.tv_nsec)/1000000000);
    return NULL;
}
int main(){
    n=(long)pow(2,32);
    long j=1;
    pthread_t Thr_A,Thr_B,Thr_C;
    double oth_t=0,rr_t=0,fifo_t=0;
    FILE *file;
    file=fopen("Output1.txt","w");
    for(int i=0;i<=5;i++){
        pthread_create(&Thr_A,NULL,(void*)countA,NULL);
        pthread_create(&Thr_B,NULL,(void*)countB,NULL);
        pthread_create(&Thr_C,NULL,(void*)countC,NULL);
        pthread_join(Thr_A,NULL);
        pthread_join(Thr_B,NULL);
        pthread_join(Thr_C,NULL);
        oth_t+=oth;
        rr_t+=rr;
        fifo_t+=fifo;
        fprintf(file,"%lf\n",oth);
        fprintf(file,"%lf\n",rr);
        fprintf(file,"%lf\n",fifo);
        }
    printf("Avg. Time taken by the thread using SCHED_OTHER is: %lf\n",oth_t/5);
    printf("Avg. Time taken by the thread using SCHED_RR is: %lf\n",rr_t/5);
    printf("Avg. Time taken by the thread using SCHED_FIFO is: %lf\n",fifo_t/5);
    return 0;
}