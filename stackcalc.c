#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

char gettoken() {
  char c;
  while ((c = getchar()) != EOF) {
    if (c != ' ' && c != '\t' && c != '\n')
      break;
  }
  return c;
}

int stack[STACK_SIZE];
int height = 0;

int pop(void) {
  if (height == 0) {
    printf("stack underflow\n");
    exit(EXIT_FAILURE);
  }

  return stack[--height];
}

void push(int n) {
  if (height >= STACK_SIZE) {
    printf("stack overflow\n");
    exit(EXIT_FAILURE);
  }

  stack[height++] = n;
}

int main() {
  char c;
  int op2;

  while ((c = gettoken()) != EOF) {
    printf("tok: %c\n", c);
    if ('0' <= c && c <= '9')
      push(c - '0');
    else if (c == '+')
      push(pop() + pop());
    else if (c == '/')
      op2 = pop(), push(pop() / op2);
    else if (c == '*')
      push(pop() * pop());
    else if (c == '-')
      op2 = pop(), push(pop() - op2);
    else if (c == '.')
      printf("%d\n", stack[--height]);
  }


  return 0;
}

