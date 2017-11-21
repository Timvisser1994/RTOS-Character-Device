#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void LED_aan() {
  signed int fd, ret;
  fd = open("/dev/suzanne_tim_driver", O_RDWR);
  if (fd < 0) {
    perror("Failed to open character device...");
  }
  ret = write(fd, "1", 1);
  if (ret < 0) {
    perror("Failed to write to the character device...");
  }
}
