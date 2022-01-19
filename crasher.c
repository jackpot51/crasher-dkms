// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

static struct kobject *crasher_kobject = NULL;

static ssize_t crasher_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	return *(ssize_t *)NULL;
}

static struct kobj_attribute crasher_attribute = __ATTR(
	crasher,
	0440,
	crasher_show,
	NULL
);

static int __init crasher_init(void) {
	crasher_kobject = kobject_create_and_add("crasher", kernel_kobj);
	if (!crasher_kobject) {
		return -ENOMEM;
	}

	return sysfs_create_file(crasher_kobject, &crasher_attribute.attr);
}

static void __exit crasher_exit(void) {
	if (crasher_kobject != NULL) {
		kobject_put(crasher_kobject);
		crasher_kobject = NULL;
	}
}

module_init(crasher_init);
module_exit(crasher_exit);

MODULE_DESCRIPTION("crasher");
MODULE_AUTHOR("Jeremy Soller <jeremy@system76.com>");
MODULE_LICENSE("GPL");
