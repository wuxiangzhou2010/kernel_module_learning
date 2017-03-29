#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h> /* copy_to_user; copy_from_user */

struct fake_device
{
	char data[100];
	struct semaphore sem;
}virtual_device;

struct cdev *mcdev;
int major_num;
int ret; 
dev_t dev_num;

#define DEVICE_NAME "solidusedevice"

int device_open(struct inode *inode, struct file *filp)
{
	if(down_interruptible(&virtual_device.sem) != 0)
	{
		printk(KERN_ALERT "could not lock device during open");
		return -1;
	}
	printk(KERN_INFO "open device ");
	return 0;
}
ssize_t device_read(struct file * filp, char __user *bufStoreData, size_t bufCount, loff_t *curOffset)
{
	printk(KERN_INFO "Reading from device");
	ret = copy_to_user(bufStoreData, virtual_device.data,bufCount);
	return ret;
}

ssize_t device_write(struct file *filp, const char __user *bufSourceData, size_t bufCount, loff_t *curOffset)
{
	printk(KERN_INFO "writing to device");
	ret = copy_from_user(virtual_device.data, bufSourceData,bufCount);
	return ret;
}
int device_close(struct inode* inode, struct file * filp)
{
	up(&virtual_device.sem);
	printk(KERN_INFO "close device");
	return 0;
}


struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_close,
	.write = device_write,
	.read = device_read
};
static int driver_entry(void)
{
	ret = alloc_chrdev_region(&dev_num, 0,1, DEVICE_NAME);
	if(ret < 0){
		printk(KERN_ALERT "soliduscode: failed to allocate a major number\n");
		return ret;
		}
	major_num = MAJOR(dev_num);
	printk(KERN_INFO "soliduscode:major_num is %d\n",major_num);
	printk(KERN_INFO "use \" mknod /dev/%s c %d 0 \" for device file\n", DEVICE_NAME, major_num);


	mcdev = cdev_alloc();
	mcdev->ops = &fops;
	mcdev->owner = THIS_MODULE;

	ret = cdev_add(mcdev, dev_num, 1);
	if(ret < 0)
	{
		printk(KERN_ALERT "unable to add cdev to kernel");
		return ret;
	}
	sema_init(&virtual_device.sem,1);
	return 0;
}

static void driver_exit(void)
{
	cdev_del(mcdev);
	unregister_chrdev_region(dev_num,1);
	printk(KERN_ALERT "unloaded module");
}

module_init(driver_entry);
module_exit(driver_exit);
