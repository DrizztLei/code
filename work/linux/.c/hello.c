#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
static int __init lkp_init(void);
static int __exit lkp_exit(void);

static int __init lkp_init(void){
	printk("<1>Hello , World .\n");
	return 0;
}

static int __exit lkp_exit(void){
	printk("<2>Hello , World exit\n");
}

module_init(lkp_init);
module_exit(lkp_init);

