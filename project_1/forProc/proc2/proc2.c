#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 128


ssize_t proc_read(struct file *file, char __user *usr_buf,
	size_t count, loff_t *pos);

static struct file_operations proc_ops={
	.owner = THIS_MODULE,
	.read = proc_read,
};

int start;

int proc_init(void)
{
	
	proc_create("seconds",0666,NULL,&proc_ops);
	start=jiffies/HZ;
	return 0;
}

void proc_exit(void)
{
	
	remove_proc_entry("seconds",NULL);
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



	int end = jiffies/HZ;
	int result=end-start;
	rv = sprintf(buffer,"It has passed %d seconds \n",result);
	copy_to_user(usr_buf,buffer,rv);
	
	return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
