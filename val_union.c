#include <stdio.h>

union val {
  int ival;
  char* sval;
};

int main() {
  // can only init as first value in union, unless you do {.sval = "foo"}.
  union val u = {69};
  printf("%d\n", u.ival);
  u.sval = "foo";
  printf("%s\n", u.sval);

  return 0;
}
