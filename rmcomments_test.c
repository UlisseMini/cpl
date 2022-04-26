#include <stdio.h>

/* // Nested comment */

/* a comment *//* next to another */

int main(/* comment in args */) { // end of line comment
  printf("Hello // comment inside string!\n");
  printf("Hello /* comment inside string! */\n");
  printf("some math: %f\n", 3.14 / 5.2 /*foo*/* 1.3);
  printf("escaped \"\n");
  // TODO: char comments?
}
