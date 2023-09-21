#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

int __init count_running_processes(void)
{
    int count = 0;
    struct task_struct *task;

    // Traverse the process list and count running processes
    for_each_process(task)
    {
        if (task->state == TASK_RUNNING)
        {
            count++;
        }
    }

    printk(KERN_INFO "Number of currently running processes: %d\n", count);
    return 0;
}

void __exit cleanup(void)
{
    printk(KERN_INFO "Cleaning up\n");
}

module_init(count_running_processes);
module_exit(cleanup);
MODULE_LICENSE("GPL");
