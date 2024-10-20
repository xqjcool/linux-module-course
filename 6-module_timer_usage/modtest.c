#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/timer.h>

static unsigned long testparam = 0;
module_param(testparam, ulong, 0444);
MODULE_PARM_DESC(testparam, "just for module param test");

struct timer_struct {
	struct timer_list mtimer;
	char name[16];
	int times;
};

static char modpriority;
static struct timer_struct timer_test;


static void modtest_timer(struct timer_list *timer)
{
	struct timer_struct *mt = from_timer(mt, timer, mtimer);
	mt->times += 1;
	printk("timer name:%s, times:%d\n", mt->name, mt->times);

	/* modity timer inside this function */
	mod_timer(timer, jiffies + 3 * HZ);

}
static int show_modparam(struct seq_file *p, void *v)
{
	seq_printf(p, "testparam=%lu\n", testparam);
	return 0;
}

static int show_modpriority(struct seq_file *p, void *v)
{
        seq_printf(p, "priority=%d\n", modpriority);
        return 0;
}


static int modtest_open(struct inode *inode, struct file *file)
{
	return single_open(file, show_modpriority, NULL);
}

static ssize_t modtest_write(struct file *file, const char __user *buffer,
		size_t count, loff_t *ppos)
{
	char c;

	if (get_user(c, buffer))
		return -EFAULT;

	if (c < '0' || c > '9')
		return -EINVAL;

	modpriority = c - '0';

	printk("priority: %d\n", modpriority);

	return count;
}

struct proc_ops modtest_ops = {
	.proc_open	= modtest_open,
	.proc_read	= seq_read,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_write	= modtest_write,
};

static int __init modtest_init(void)
{
	timer_setup(&timer_test.mtimer, modtest_timer, 0);
	timer_test.times = 0;
	strncpy(timer_test.name, "modtest_timer", sizeof(timer_test.name));

	mod_timer(&timer_test.mtimer, jiffies + 5 * HZ);
	proc_create("modpriority", 0666, NULL, &modtest_ops);
	proc_create_single("modparam", 0666, NULL, show_modparam);
	printk(KERN_ERR "modetest_init finished! testparam:%lu\n", testparam);
	return 0;
}

module_init(modtest_init);
static void __exit modtest_exit(void)
{
	del_timer_sync(&timer_test.mtimer);
	remove_proc_entry("modpriority", NULL);
	remove_proc_entry("modparam", NULL);
	printk(KERN_ERR "modetest exit!\n");
}

module_exit(modtest_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.1");
