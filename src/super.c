#include <linux/init.h>
#include <linux/module.h>

#include "super.h"

static struct file_system_type tarfs_type = {
	.owner = THIS_MODULE,
	.name = "tarfs",
	.mount = tarfs_mount,
	.kill_sb = tarfs_kill_superblock
};

static struct super_operations const tarfs_super_ops = {
	.put_super = tarfs_put_super,
};

static void aufs_put_super(struct super_block * sb) {
	pr_debug("<TARFS> tarfs super block destroyed\n");
	kill_litter_super(sb);
}

static int tarfs_fill_sb(struct super_block *sb, void *data, int silent) {
	struct inode * root = NULL;

	sb->s_blocksize = TARFS_BLOCKSIZE;
	sb->s_blocksize_bits = TARFS_BLOCKSIZE_BITS
	sb->s_magic = TARFS_MAGIC;
	sb->s_op = &tarfs_super_ops;
	
	root = tarfs_new_inode(sb);
	if(!root) {
		pr_err("<TARFS> inode allocation failes\n");
		return -ENOMEM;
	}

	root->i_ino = 0;
	root->i_sb = sb;
	root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
	inode_init_owner(root, NULL, S_IFDIR);

	sb->s_root = d_make_root(root);
	if(!sb->s_root) {
		pr_err("<TARFS> root creation failes\n");
		return -ENOMEM;
	}

	return 0;
}

static struct dentry * aufs_mount (struct file_system_type * type, int flags,
					char const * dev, void * data)
{
	struct dentry * const entry = mount_bdev(type, flags, dev, data, tarfs_fill_sb);
	if(IS_ERR(entry))
		pr_debug("<TARFS> mount failed\n");
	else
		pr_debug("<TARFS> mounted\n");

	return entry;
}

static int __init tarfs_init(void) {
	pr_debug("<TARFS> tarfs module loaded\n");
	return 0;
}

static void __exit tarfs_exit(void) {
	pr_debug("<TARFS> tarfs module unloaded\n");
}

module_init(tarfs_init);
module_exit(tarfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afal");
