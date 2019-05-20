#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>


#define BUFFER_SIZE 128


ssize_t proc_read(struct file *file, char __user *usr_buf,
	size_t count, loff_t *pos);

ssize_t proc_write(struct file *file,const char __user *usr_buf,size_t count, loff_t *pos);

static struct file_operations proc_ops={
	.owner = THIS_MODULE,
	.write = proc_write,
	.read = proc_read,
};

long int destination=0;
struct task_struct *result;

int proc_init(void)
{
	
	proc_create("pid",0666,NULL,&proc_ops);
	

	return 0;
}

void proc_exit(void)
{
	
	remove_proc_entry("pid",NULL);
	
}

ssize_t proc_read(struct file *file,char __user *usr_buf,
	size_t count, loff_t *pos)
{
	int rv=0;
	char buffer[BUFFER_SIZE];
	static int completed=0;
	
	if(completed){
		completed=0;
		return 0;
	}
	completed = 1;
	
	
	result=pid_task(find_vpid(destination),PIDTYPE_PID);
	if(result!=NULL)
	{
		rv = sprintf(buffer,"command=%s,pid=%d,state=%ld \n",result->comm,result->pid,result->state);
		copy_to_user(usr_buf,buffer,rv);
	}
	else
	{
		rv = sprintf(buffer,"There is no such proc\n Your destination is %ld\n",destination);
		copy_to_user(usr_buf,buffer,rv);
	}

	return rv;
}


ssize_t proc_write(struct file *file,const char __user *usr_buf,size_t count, loff_t *pos)
{
	
	char *k_mem;
	long int  res=1;
	k_mem= kmalloc(count,GFP_KERNEL);
	
	copy_from_user(k_mem,usr_buf,count);
	k_mem[count]='\0';

	printk(KERN_INFO "%ld\n", count);
	printk(KERN_INFO "%s\n", k_mem);
	
	
	//destination=(long int *)malloc(sizeof(long));
	//int t;
	kstrtol(k_mem,10, &res);
	//destination=atoi(k_mem);
	destination=res;
	printk(KERN_INFO "%ld\n", destination);


	kfree(k_mem);
	return count;
}






module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");












