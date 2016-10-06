#include <linux/init.h>
#include <linux/module.h>

static int __init tarfs_init(void) {
	printk("tarfs module loaded\n");
	return 0;
}

static void __exit tarfs_exit(void) {
	printk("tarfs module unloaded\n");
}

module_init(tarfs_init);
module_exit(tarfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afal");
