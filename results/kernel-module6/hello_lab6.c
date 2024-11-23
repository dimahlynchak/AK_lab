#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/bug.h>
#include <linux/param.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Глинчак Дмитро <iohlynchakdmytrod@gmail.com>");
MODULE_DESCRIPTION("Lab 6: Adding manual sections handling and debugging features");
MODULE_VERSION("1.1");

static struct kobject *hello_kobj;

static char text_section[32] = "0xbf000000";
static char data_section[32] = "0xbf002000";
static char bss_section[32] = "0xbf004000";

static ssize_t section_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    if (strcmp(attr->attr.name, ".text") == 0)
        return sprintf(buf, "%s\n", text_section);
    else if (strcmp(attr->attr.name, ".data") == 0)
        return sprintf(buf, "%s\n", data_section);
    else if (strcmp(attr->attr.name, ".bss") == 0)
        return sprintf(buf, "%s\n", bss_section);
    return -EINVAL;
}

static struct kobj_attribute text_attr = __ATTR(.text, 0444, section_show, NULL);
static struct kobj_attribute data_attr = __ATTR(.data, 0444, section_show, NULL);
static struct kobj_attribute bss_attr = __ATTR(.bss, 0444, section_show, NULL);

static struct attribute *attrs[] = {
    &text_attr.attr,
    &data_attr.attr,
    &bss_attr.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

// Параметри модуля
static int count = 1;
module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of hello world messages");

struct hello_item {
    struct list_head list;
    char *message;
};

static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
    int ret, i;
    struct hello_item *item;

    pr_info("Hello_lab6 module initializing\n");

    // Ініціалізація sysfs
    hello_kobj = kobject_create_and_add("hello_lab6", kernel_kobj);
    if (!hello_kobj) {
        pr_err("Failed to create kobject\n");
        return -ENOMEM;
    }

    ret = sysfs_create_group(hello_kobj, &attr_group);
    if (ret) {
        pr_err("Failed to create sysfs group\n");
        kobject_put(hello_kobj);
        return ret;
    }

    BUG_ON(count < 0);

    for (i = 0; i < count; i++) {
        item = kmalloc(sizeof(*item), GFP_KERNEL);

        if (i == count - 1) {
            item = NULL;
        }

        if (!item) {
            pr_err("Failed to allocate memory for item %d\n", i);
            break;
        }

        item->message = kasprintf(GFP_KERNEL, "Hello, world! %d\n", i + 1);
        if (!item->message) {
            kfree(item);
            pr_err("Failed to allocate message for item %d\n", i);
            break;
        }

        list_add_tail(&item->list, &hello_list);
        pr_info("%s", item->message);
    }

    return 0;
}

static void __exit hello_exit(void)
{
    struct hello_item *item, *tmp;

    pr_info("Hello_lab6 module exiting\n");

    kobject_put(hello_kobj);

    list_for_each_entry_safe(item, tmp, &hello_list, list) {
        pr_info("Freeing: %s", item->message);
        kfree(item->message);
        kfree(item);
    }
}

module_init(hello_init);
module_exit(hello_exit);

