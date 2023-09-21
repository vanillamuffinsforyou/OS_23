#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>

#define MAX_PATH_LENGTH 100
#define DENOMINATOR 1e9

void runCompilation(const char *scriptPath, int priority, const char *scheduler, FILE *output)
{
    struct timespec startTime, endTime;
    pid_t childPid;
    int status;

    struct sched_param schedParam;
    schedParam.sched_priority = priority;

    clock_gettime(CLOCK_REALTIME, &startTime);

    childPid = fork();
    if (childPid == -1)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (childPid == 0)
    {
        // Child process
        sched_setscheduler(0, sched_getscheduler(0), &schedParam);
        execl("/bin/sh", "sh", scriptPath, NULL);
        perror("Exec failed");
        exit(1);
    }
    else
    {
        // Parent process
        waitpid(childPid, &status, 0);
        clock_gettime(CLOCK_REALTIME, &endTime);

        double executionTime = (endTime.tv_sec - startTime.tv_sec) +
                               (endTime.tv_nsec - startTime.tv_nsec) / DENOMINATOR;

        printf("Time taken by process using %s to compile: %lf\n", scheduler, executionTime);
        fprintf(output, "%lf\n", executionTime);
    }
}

int main()
{
    FILE *outputFile = fopen("Output2.txt", "w");
    if (outputFile == NULL)
    {
        perror("Failed to open output file");
        return 1;
    }

    pid_t parentPid = getpid();

    for (int i = 1; i <= 3; i++)
    {
        char scriptPath[MAX_PATH_LENGTH];
        snprintf(scriptPath, sizeof(scriptPath), "Script%d.sh", i);

        int priority = (i == 1) ? 0 : 1;
        const char *scheduler = (i == 1) ? "SCHED_OTHER" : (i == 2) ? "SCHED_RR"
                                                                    : "SCHED_FIFO";

        runCompilation(scriptPath, priority, scheduler, outputFile);
    }

    fclose(outputFile);
    return 0;
}
