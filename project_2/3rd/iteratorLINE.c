#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/uaccess.h>
//#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>



//task=&init_task;


int proc_init(void)
{
	struct task_struct *task;
	//task=init_task->next_task;
	for_each_process(task)
	{
		
		printk(KERN_INFO "command=%s,pid=%d,state=%ld \n",task->comm,task->pid,task->state);
		
		
	}


	return 0;
}

void proc_exit(void)
{
	
	
	return;
}



module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");












