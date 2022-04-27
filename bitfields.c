#include <stdio.h>

struct clock {
  unsigned int is_pm : 1; // is it PM or AM?
  unsigned int hour : 4; // 0-16 (really only 0-12)
  unsigned int minute : 6; // 0-64 (really only 0-59)
};

int main() {
  struct clock c = {1, 2, 48}; // time as I write this
  char *ampm = c.is_pm ? "PM" : "AM";
  printf("%d:%d %s\n", c.hour, c.minute, ampm);
  // Supposed to be 2 (total of 11 bits so 2 bytes) but gets rounded up to 4 bytes somehow (modern compilers don't care?)
  printf("clock size: %lu\n", sizeof(struct clock));

  return 0;
}

