#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>

struct new_device
{
	char data[100];
	struct semaphore sem;
}virtual_device;

struct cdev *mcdev;
int major_no;			//Stores major number extracted from mknod director/file c major minor
int ret;
dev_t dev_num;


#define DEVICE_NAME "new_dev"

int device_open(struct inode *inode,struct file *fp)  //inode references to file on disk and contains info about that file
{
	if(down_interruptible(&virtual_device.sem)!=0)
	{
		printk(KERN_ALERT "Could not lock device during open\n");
		return -1;
	}

	printk(KERN_INFO "Opened device\n");
	return 0;
}

ssize_t device_read(struct file* fp,char* bufStoreData, size_t bufCount, loff_t* curOffset)
{
	printk(KERN_INFO "Reading from device\n");
	ret = copy_to_user(bufStoreData,virtual_device.data,bufCount);
	return ret;
}


ssize_t device_write(struct file* fp,const char* bufSourceData, size_t bufCount, loff_t* curOffset)
{
	printk(KERN_INFO "Writing to device\n");
	ret = copy_from_user(virtual_device.data,bufSourceData,bufCount);
	return ret;
}

int device_close(struct inode *inode,struct file *fp)
{
	up(&virtual_device.sem);
	printk(KERN_INFO "Closed device\n");
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
	ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
	if(ret<0)
	{
		printk(KERN_ALERT "Failed to allocate a major number\n");
		return ret;
	}
	major_no = MAJOR(dev_num);
	printk(KERN_INFO "new_dev major number is %d\n",major_no);
	printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file\n",DEVICE_NAME,major_no);

	mcdev = cdev_alloc();
	mcdev->ops =&fops;
	mcdev->owner = THIS_MODULE;
	ret = cdev_add(mcdev,dev_num,1); //(cdev struct,device number,count)

	if(ret<0)
	{
		printk(KERN_ALERT "unable to add device to the kernel\n");
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