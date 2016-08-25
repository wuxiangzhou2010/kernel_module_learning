/*
As of Linux 2.4, you can rename the init and cleanup functions of your modules; they no longer have to be called init_module() and cleanup_module() respectively. This is done with the module_init() and module_exit() macros. These macros are defined in linux/init.h. 
*/
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init hello_2_init(void)
{
	printk(KERN_INFO "Hello, world 2.\n");
	return 0;
}

static init __exit hello_2_exit(void)
{
	printk(KERN_INFO "Goodbye, world 2.\n");
}
