#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "scanner.h"

static char* buf; // input buffer
static int len; // length of buf
static int start; // start of lexeme in buf
static int pos; // current pos in buf

void init_scanner(char* input) {
  buf = input;
  len = strlen(buf);
  start = pos = 0;
}


static char peek() { return pos < len ? buf[pos] : '\0'; }
static char advance() { return pos < len ? buf[pos++] : '\0';  }
/* static bool advance_if(char c) { */
/*   return (peek() == c) ? advance() : false; */
/* } */

static void advance_while(int pred(int c)) {
  char c;
  while ((c = peek()) && pred(c))
    advance();
}

// --------------

Token next_token() {
  Token tok;
  tok.type = END; // default if no type is assigned

  char c;
  while ((c = advance()) != '\0') {
    if (c == '(') {
      tok.type = LPAREN;
    } else if (c == ')') {
      tok.type = RPAREN;
    } else if (isalpha(c)) {
      tok.type = IDENT;
      advance_while(isalnum);
    } else if (isdigit(c)) {
      tok.type = NUMBER;
      advance_while(isdigit);
    }

    if (tok.type == END)
      // nothing matched, ignore (probably whitespace, etc)
      start = pos;
    else
      break;
  }

  tok.start = start;
  tok.end = pos;
  start = pos;
  return tok;
}

void print_token(Token tok) {
  printf("token type %d lexeme: '", tok.type);
  for (int i = tok.start; i < tok.end; i++)
    putchar(buf[i]);
  printf("'\n");
}
