#include <stdio.h>

#define NORMAL 0
#define STRING 1
#define EOLCOMMENT 2
#define INLINECOMMENT 3

int main() {
  char curr, peek;
  int state = NORMAL;

  // foo /* bar */
  //

  for (curr = getchar(); (peek = getchar()), curr != EOF; curr=peek) {
    switch (state) {
      case NORMAL:
        if (curr == '"') {
          state = STRING;
          putchar(curr);
        } else if (curr == '/' && peek == '/') {
          state = EOLCOMMENT;
        } else if (curr == '/' && peek == '*') {
          state = INLINECOMMENT;
        } else {
          putchar(curr);
        }
        break;
      case STRING:
        if (curr == '"') {
          state = NORMAL;
        }
        putchar(curr);
        break;
      case EOLCOMMENT:
        if (curr == '\n') {
          state = NORMAL;
          putchar(curr);
        }
        break;
      case INLINECOMMENT:
        if (curr == '*' && peek == '/') {
          state = NORMAL;
          // Advance
          curr = peek;
          peek = getchar();
        }
        break;
    }
  }

  return 0;
}

