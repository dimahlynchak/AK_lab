#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Глинчак Дмитро <iohlynchakdmytrod@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Module for Lab 4");
MODULE_LICENSE("GPL");

static uint count = 1;
module_param(count, uint, S_IRUGO);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

struct time_entry {
    struct list_head list;
    ktime_t time;
};

static LIST_HEAD(time_list);

static int __init hello_init(void) {
    if (count == 0 || (count >= 5 && count <= 10)) {
        pr_warn("Warning: count is 0 or in the range 5-10\n");
    }
    if (count > 10) {
        pr_err("Error: count is greater than 10\n");
        return -EINVAL;
    }

    for (uint i = 0; i < count; i++) {
        struct time_entry *entry = kmalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry) {
            pr_err("Failed to allocate memory\n");
            return -ENOMEM;
        }
        entry->time = ktime_get();
        list_add_tail(&entry->list, &time_list);
        pr_info("Hello, world!\n");
    }
    return 0;
}

static void __exit hello_exit(void) {
    struct time_entry *entry, *tmp;
    list_for_each_entry_safe(entry, tmp, &time_list, list) {
        pr_info("Time: %lld\n", ktime_to_ns(entry->time));
        list_del(&entry->list);
        kfree(entry);
    }
}

module_init(hello_init);
module_exit(hello_exit);

