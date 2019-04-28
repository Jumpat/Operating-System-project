#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <asm/param.h>

static int __init hello_init(void){
	printk("<3>Hi,Mr.Stark.\n");
	printk("The GOLDEN_RATIO_PRIME is");
	printk(KERN_INFO "%lu\n", GOLDEN_RATIO_PRIME);
	printk("The value of HZ is %d \n",HZ);
	printk("Jiffies is %d \n",jiffies);
	return 0;
}

static void __exit hello_exit(void){
	int result=gcd(3300,24);
	printk("The gcd of 3300 & 24 is %d \n",result);
	printk("Now jiffies is %d \n",jiffies);
	printk("<3>Bye.\n");
	
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
