#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
int processID=0;
module_param(processID,int,0);
int __init pid_properties(void){
    pid_t t_pid;
    pid_t t_uid;
    pid_t t_pgid;
    struct task_struct *pro;
    pro= pid_task(find_vpid(processID),PIDTYPE_PID);
    if(!pro){
        return -ESRCH;
    }
    t_pid=pro->pid;
    t_uid=pro->cred->uid.val;
    t_pgid=pro->group_leader->pid;
    printk(KERN_INFO "pid of process: %d\n",t_pid);
    printk(KERN_INFO "uid of process: %d\n",t_uid);
    printk(KERN_INFO "pgid of process: %d\n",t_pgid);
    printk(KERN_INFO "comm of process: %s\n",pro->comm);
    return 0;
}
void __exit cleanup(void){
    printk(KERN_INFO "Cleaning up\n");
}
module_init(pid_properties);
module_exit(cleanup);
MODULE_LICENSE("GPL");