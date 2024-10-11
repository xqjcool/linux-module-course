#include <linux/module.h>
#include <linux/kernel.h>

static unsigned long testparam = 0;
module_param(testparam, ulong, 0444);
MODULE_PARM_DESC(testparam, "just for module param test");

static int __init modtest_init(void)
{
	printk(KERN_ERR "modetest_init finished! testparam:%lu\n", testparam);
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
