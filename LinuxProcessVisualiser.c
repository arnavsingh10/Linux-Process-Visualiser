#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>

int child_function(void *arg);

struct task_struct *parent_task;
struct task_struct *child_tasks[3];

int child_function(void *arg) {
    int id = *(int *)arg;
    printk(KERN_INFO "  ├── Child Process [%d]: PID = %d, Memory Allocated at %p\n", id, current->pid, arg);
    kfree(arg);
    return 0;
}

static int __init my_kernel_module_init(void) {
    printk(KERN_INFO "my_kernel_module<%d>\n", current->pid);  // Tree structure root
    printk(KERN_INFO "  ├── Kernel Module Loaded\n");

    for (int i = 0; i < 3; i++) {
        int *child_id = kmalloc(sizeof(int), GFP_KERNEL);
        if (!child_id) {
            printk(KERN_ERR "Memory Allocation Failed\n");
            return -ENOMEM;
        }

        *child_id = i;
        child_tasks[i] = kthread_run(child_function, child_id, "child_thread-%d", i);
        if (IS_ERR(child_tasks[i])) {
            printk(KERN_ERR "Failed to create child thread\n");
            kfree(child_id);
        } else {
            printk(KERN_INFO "  ├── Created Child Thread %d: PID = %d\n", i, child_tasks[i]->pid);
        }
    }
    return 0;
}
