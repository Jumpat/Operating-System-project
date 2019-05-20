#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>

struct collatz
{
	int value;
	struct list_head list;


};
static int start=25;
static LIST_HEAD(collatz_list);
module_param(start,int,0);

int proc_init(void)
{
	
	
	int tmp=start;
	struct collatz *ptr;
	
	while(tmp!=1)
	{
		struct collatz *new;
		if(tmp%2==0)
			tmp=tmp/2;
		else
			tmp=3*tmp+1;
		new = kmalloc(sizeof(*new),GFP_KERNEL);
		new->value=tmp;
		if(tmp==start)
			INIT_LIST_HEAD(&new->list);
		else list_add_tail(&new->list,&collatz_list);		

	}

	
	list_for_each_entry(ptr,&collatz_list,list)
	{
		printk(KERN_INFO "%d  ",ptr->value);
		
	}


	return 0;
}

void proc_exit(void)
{
	struct collatz *ptr,*next;

	list_for_each_entry_safe(ptr,next,&collatz_list,list)
	{
		list_del(&ptr->list);
		kfree(ptr);
		printk(KERN_INFO "DELETE SUCCESSFULLY");
	}
	
	return;
}



module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");












