#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h> // for scheduling functions

int main()
{
    pid_t child_pid;

    // Create Process 1 (SCHED_OTHER with nice 0)
    child_pid = fork();
    if (child_pid == 0)
    {
        struct sched_param param;
        param.sched_priority = 0;
        if (sched_setscheduler(0, SCHED_OTHER, &param) == -1)
        {
            perror("sched_setscheduler");
            exit(1);
        }
        execl("./count1", "count1", NULL);
        perror("execl");
        exit(1);
    }

    // Create Process 2 (SCHED_RR with default priority)
    child_pid = fork();
    if (child_pid == 0)
    {
        struct sched_param param;
        param.sched_priority = 0;
        if (sched_setscheduler(0, SCHED_RR, &param) == -1)
        {
            perror("sched_setscheduler");
            exit(1);
        }
        execl("./count1", "count1", NULL);
        perror("execl");
        exit(1);
    }

    // Create Process 3 (SCHED_FIFO with default priority)
    child_pid = fork();
    if (child_pid == 0)
    {
        struct sched_param param;
        param.sched_priority = 0;
        if (sched_setscheduler(0, SCHED_FIFO, &param) == -1)
        {
            perror("sched_setscheduler");
            exit(1);
        }
        execl("./count1", "count1", NULL);
        perror("execl");
        exit(1);
    }

    // Wait for all child processes to finish
    int status;
    while (wait(&status) > 0)
    {
        // Do nothing, just wait for all children to finish
    }

    return 0;
}
