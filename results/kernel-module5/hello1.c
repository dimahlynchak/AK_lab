#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Глинчак Дмитро <iohlynchakdmytrod@gmail.com>");
MODULE_DESCRIPTION("Hello1 Module for Lab 5");
MODULE_LICENSE("GPL");

static ktime_t start_time;
static int count = 1;

module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

void print_hello(void) {
    int i;
    for (i = 0; i < count; i++) {
        pr_info("Hello, world! %d\n", i + 1);
    }
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) {
    pr_info("Hello1 Module initialized\n");
    start_time = ktime_get();
    return 0;
}

static void __exit hello1_exit(void) {
    ktime_t end_time = ktime_get();
    pr_info("Hello1 Module exited. Time elapsed: %lld ns\n",
            ktime_to_ns(ktime_sub(end_time, start_time)));
}

module_init(hello1_init);
module_exit(hello1_exit);

