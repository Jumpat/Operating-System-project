#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void){
	printk("<3>Hi,Mr.Stark.\n");
	return 0;
}

static void __exit hello_exit(void){
	printk("<3>Bye.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
