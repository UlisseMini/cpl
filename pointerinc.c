#include <stdio.h>

int main() {
  /* when you run ptr+1 the compiler will handle sizes,
   * i.e. it will count in units of long* (8 bytes I think)
   */
  long arr[4] = {1,2};
  long* ptr = arr;
  printf("%ld\n", *(ptr++));
  printf("%ld\n", *(ptr++));

  return 0;
}
