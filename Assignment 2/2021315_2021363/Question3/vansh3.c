#include<linux/kernel.h>
#include<linux/sched/signal.h>
#include<linux/moduleparam.h>
#include<linux/module.h>
#include<linux/fs_struct.h>

MODULE_LICENSE("Vansh");
MODULE_AUTHOR("YADAV");

static int MY_Module_init(void){
    struct task_struct *task_list;
    int count = 0;
    for_each_process(task_list){

        if(task_list->__state == TASK_RUNNING){
            count++;
        }

    }

    printk(KERN_INFO "Number of running processes: %d\n",count);
    return 0;
}

static void My_Module_exit(void){
    printk(KERN_ALERT "Module have been unloaded\n");
}

module_init(My_Module_init);
module_exit(My_Module_exit);