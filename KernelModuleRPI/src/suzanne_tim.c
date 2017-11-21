#include <linux/module.h>
#include <linux/kernel.h>
//#include <wiringPi.h>

//#define GPIO_LED_PIN 21

int hello_init(void) {
	pr_alert("Character Device van Suzanne Peerdeman & Tim Visser\n");
//	if (wiringPiSetup () == -1) {
//		pr_alert("Wiring Pi is niet geinstalleerd!");
//		return 1;
//	}
//	pinMode(GPIO_LED_PIN, OUTPUT);
	return 0;
}

void hello_exit(void) {
	pr_alert("Character Device ontkoppeld...\n");
}

static void LED_aan(void) {
	pr_alert("LEDje aan...\n");
//	digitalWrite(GPIO_LED_PIN, HIGH);
}

static void LED_uit(void) {
	pr_alert("LEDje uit...\n");
//	digitalWrite(GPIO_LED_PIN, LOW);
}

module_init(hello_init);
module_exit(hello_exit);
