#include <stdio.h>


void string() {
  char c;
  while ((c = getchar()) != EOF) {
    putchar(c);
    if (c != '\\') {
      c = getchar();
      putchar(c);
      if (c == '"') break;
    }
  }
}

void inlinecomment() {
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '*' && (getchar() == '/'))
      break;
  }
}

void linecomment() {
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '\n')
      break;
  }
  putchar(c);
}


void normal() {
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '"') {
      putchar(c);
      string();
    } else if (c == '/') {
      char peek = getchar();
      if (peek == '/') {
        linecomment();
      } else if (peek == '*') {
        inlinecomment();
      } else {
        putchar(c);
        putchar(peek);
      }
    } else {
      putchar(c);
    }
  }
}

int main() {
  normal();

  return 0;
}

