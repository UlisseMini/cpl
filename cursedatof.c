#include <stdio.h>
#include <stdlib.h>

int main() {
  char test[] = "3.14";

  int i = 0;
  for (; s[i] != '.'; i++);
  s[i] = '\0';
  int a = atoi(s);
  s[i] = '.';
  int b = atoi(s + sizeof(char)*(i+1));
  printf("%d dot %d\n", a, b);

  return 0;
}


