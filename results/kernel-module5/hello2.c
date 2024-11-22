#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Глинчак Дмитро <iohlynchakdmytrod@gmail.com>");
MODULE_DESCRIPTION("Hello2 Module for Lab 5");
MODULE_LICENSE("GPL");

static int count = 1;

module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of times to call print_hello() from hello1");

static int __init hello2_init(void) {
    pr_info("Hello2 Module initialized\n");
    print_hello();
    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 Module exited\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
