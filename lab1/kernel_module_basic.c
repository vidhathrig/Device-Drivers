#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

//Create a variable
MODULE_LICENSE("GPL"); 

int val[3] = {0,0,0};

module_param_array(val,int,NULL,S_IRUSR | S_IWUSR); //(parameter_name,data type,no of ele,permissions)  Read and write permission given to user

void display(void)
{
	printk(KERN_ALERT "HELLO::parameter value: %d\n" ,val[0]*val[1]);

	printk(KERN_ALERT "HELLO::parameter value: %d\n" ,val[1]+val[2]);

	printk(KERN_ALERT "HELLO::parameter value: %d\n" ,val[2]);


}

static int mod_init(void)
{
	printk(KERN_ALERT "Parameter Allocation");
	display();
	return 0;
}

static void mod_exit(void)
{
	printk(KERN_ALERT "Deallocate");
}

module_init(mod_init);
module_exit(mod_exit);	