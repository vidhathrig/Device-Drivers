#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("GPL"); 
  
///< The author -- visible when you use modinfo 
MODULE_AUTHOR("Vidhathri"); 
  
///< The description -- see modinfo 
MODULE_DESCRIPTION("A simple Hello world LKM!"); 
  
///< The version of the module 
MODULE_VERSION("0.1"); 

static int hello_init(void)
{
	printk(KERN_INFO "Hello kernel world!!\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "Bye kernel world!!\n");
}

module_init(hello_init);
module_exit(hello_exit);	