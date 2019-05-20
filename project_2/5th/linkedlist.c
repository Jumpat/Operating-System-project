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

struct color{
	int red;
	int blue;
	int green;
	
	struct list_head list;

};
static LIST_HEAD(color_list);


int proc_init(void)
{
	
	struct color *ptr;
	struct color *c[4];
	
	int i=0;
	for(i=0;i<4;i++)
	{
		c[i]=kmalloc(sizeof(*c[i]),GFP_KERNEL);
		c[i]->red=i;
		c[i]->blue=i;
		c[i]->green=i;
		if(i==0)
			INIT_LIST_HEAD(&c[i]->list);
		list_add_tail(&c[i]->list,&color_list);
	}

	
	list_for_each_entry(ptr,&color_list,list)
	{
		printk(KERN_INFO "red=%d,blue=%d,green=%d \n",ptr->blue,ptr->blue,ptr->green);
		
	}


	return 0;
}

void proc_exit(void)
{
	struct color *ptr,*next;

	list_for_each_entry_safe(ptr,next,&color_list,list)
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












