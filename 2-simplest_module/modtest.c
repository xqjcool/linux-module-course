#include <linux/module.h>


static int __init modtest_init(void)
{
	return 0;
}

module_init(modtest_init);
static void __exit modtest_exit(void)
{
}

module_exit(modtest_exit);

MODULE_LICENSE("GPL");
