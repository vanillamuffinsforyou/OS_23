#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include  <dirent.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
FILE *output;
long double denom=1e9;
char arg1[]="/bin/sh";
char arg2[]="sh";
void parallel_process_creator(int flag){
    char temp_path[100];
    getcwd(temp_path,sizeof(temp_path));

    if(flag==1){
        double pro_time1;
        pid_t pid_child1=fork();
        struct timespec  s1,e1;
        struct sched_param sched_param1;
        sched_param1.sched_priority=0;
        sched_setscheduler(getpid(),SCHED_OTHER,&sched_param1);
        int error1;
        clock_gettime(CLOCK_REALTIME,&s1);
        if(pid_child1==0){
            strcat(temp_path,"/Script1.sh");
            execl(arg1,arg2,temp_path,NULL);
            printf("%s\n",temp_path);
        }else if(pid_child1<0){
            printf("Fork Not Called Properly. Kindly Restart The Program.\n");
            exit(1);
        }else{
            waitpid(pid_child1,&error1,0);
            clock_gettime(CLOCK_REALTIME,&e1);
            pro_time1=(e1.tv_sec-s1.tv_sec)+((e1.tv_nsec-s1.tv_nsec)/(double)denom);
            printf("Time taken by Process 1 (using SCHED_OTHER) to compile: %lf\n",pro_time1);
            fprintf(output,"%lf\n",pro_time1);
        }
    }
    if(flag==2){
        double pro_time2;
        pid_t pid_child2=fork();
        struct timespec  s2,e2;
        struct sched_param sched_param2;
        sched_param2.sched_priority=1;
        sched_setscheduler(getpid(),SCHED_RR,&sched_param2);
        int error2;
        clock_gettime(CLOCK_REALTIME,&s2);
        if(pid_child2==0){
            strcat(temp_path,"/Script2.sh");
            execl(arg1,arg2,temp_path,NULL);
        }else if(pid_child2<0){
            printf("Fork Not Called Properly. Kindly Restart The Program.\n");
            exit(1);
        }else{
            waitpid(pid_child2,&error2,0);
            clock_gettime(CLOCK_REALTIME,&e2);
            pro_time2=(e2.tv_sec-s2.tv_sec)+((e2.tv_nsec-s2.tv_nsec)/(double)denom);
            printf("Time taken by Process 2 (using SCHED_RR) to compile: %lf\n",pro_time2);
            fprintf(output,"%lf\n",pro_time2);
        }
    }
    if(flag==3){
        double pro_time3;
        pid_t pid_child3=fork();
        struct timespec  s3,e3;
        struct sched_param sched_param3;
        sched_param3.sched_priority=1;
        sched_setscheduler(getpid(),SCHED_FIFO,&sched_param3);
        int error3;
        clock_gettime(CLOCK_REALTIME,&s3);
        if(pid_child3==0){
            strcat(temp_path,"/Script3.sh");
            execl(arg1,arg2,temp_path,NULL);
        }else if(pid_child3<0){
            printf("Fork Not Called Properly. Kindly Restart The Program.\n");
            exit(1);
        }else{
            waitpid(pid_child3,&error3,0);
            clock_gettime(CLOCK_REALTIME,&e3);
            pro_time3=(e3.tv_sec-s3.tv_sec)+((e3.tv_nsec-s3.tv_nsec)/(double)denom);
            printf("Time taken by Process 3 (using SCHED_FIFO) to compile: %lf\n",pro_time3);
            fprintf(output,"%lf\n",pro_time3);
        }
    }
}

int main(){
    output=fopen("Output2 .txt","w");
    pid_t mini_parent1=fork();
    if(mini_parent1==0){
        parallel_process_creator(1);
    }else{
        pid_t mini_parent2=fork();
        if(mini_parent2==0){
            parallel_process_creator(2);
        }else{
            pid_t mini_parent3=fork();
            if(mini_parent3==0){
                parallel_process_creator(3);
            }
            waitpid(mini_parent3,0,0);
        }
        waitpid(mini_parent2,0,0);
    }
    waitpid(mini_parent1,0,0);
    fclose(output);
    return 0;
}