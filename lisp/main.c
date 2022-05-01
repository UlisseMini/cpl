#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "scanner.h"

#define BUF_SIZE 1024*1024

int main() {
  static char buf[BUF_SIZE];

  size_t nread = fread(buf, sizeof(char), BUF_SIZE, stdin);
  if (nread == 0) {
    fprintf(stderr, "failed to read anything from stdin\n");
    return 1;
  }

  init_scanner(buf);
  Token t;
  do {
    t = next_token();
    print_token(t);
  } while (t.type != END);

  return 0;
}
