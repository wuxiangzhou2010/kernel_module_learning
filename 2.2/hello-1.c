/* printk 
in kernel mode, you can't use the standard C library, so printf is not available, hence printk.
	int printk(const char *fmt, ...);
Logging Levels
	printk(KERN_DEBUG "Debug message shown!\n");
*/

#include<linux/module.h>
#include<linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello world 1.n");

	return 0;
}
void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
