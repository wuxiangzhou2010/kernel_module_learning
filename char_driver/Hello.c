#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int param_var[3] = {1,2,3};
// module_param(param_var, int, S_IRUSR | S_IRGRP);
module_param_array(param_var, int , NULL, S_IRUSR | S_IWUSR);

void display(void)
{
	int i = 0;
	do
	{
		printk(KERN_ALERT "TEST: %d\n", param_var[i]);
	}while(++i<3);
}
static int hello_init(void)
{
	printk(KERN_ALERT "TEST:hello_init\n");
	display();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "TEST exit\n");

}

module_init(hello_init);
module_exit(hello_exit);
