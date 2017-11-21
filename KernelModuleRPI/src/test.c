#include "suzanne_tim.c"
#include <unistd.h>

int main (int argc, char **argv) {

    while (1) {
        LED_aan();
        usleep(1000000);
        LED_uit();
        usleep(1000000);
    }

    return 0;
}