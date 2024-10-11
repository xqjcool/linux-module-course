#include <linux/module.h>
#include <linux/kernel.h>


static int __init modtest_init(void)
{
	printk(KERN_ERR "modetest_init finished!\n");
	return 0;
}

module_init(modtest_init);
static void __exit modtest_exit(void)
{
	printk(KERN_ERR "modetest exit!\n");
}

module_exit(modtest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.1");
