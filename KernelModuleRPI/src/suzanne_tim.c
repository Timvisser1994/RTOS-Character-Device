#include <linux/module.h>
#include <linux/kernel.h>

int hello_init(void) {
	pr_alert("Hello World ;)\n");
	return 0;
}

void hello_exit(void) {
	pr_alert("Goodbye World!\n");
}

static void LED_aan(void) {
	pr_alert("LEDje aan...\n");
}

static void LED_uit(void) {
	pr_alert("LEDje uit...\n");
}

module_init(hello_init);
module_exit(hello_exit);
