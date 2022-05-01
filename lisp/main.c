#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"

#define BUF_SIZE 1024*1024

static char buf[BUF_SIZE];

/*********************** Parser ***********************/

typedef enum {
  IDENTIFIER,
  LIST,
  NUMERIC, // TODO: Fix duplicatino between expr_type and token_type
} expr_type;

typedef struct SExpr {
  expr_type type;
  Token tok;
  void* value;
} SExpr;

typedef struct List {
  struct SExpr* value;
  struct List* next;
} List;

static Token curr_token;
static Token advance() {
  Token old = curr_token;
  curr_token = next_token();
  return old;
}
static Token peek() { return curr_token; }

void init_parser() {
  curr_token = next_token();
}

List* new_list(void* v) {
  List* l = malloc(sizeof(List));
  l->value = v;
  l->next = NULL;
  return l;
}

List* append(List* head, void* v) {
  List* new = new_list(v);
  if (head == NULL) {
    return new;
  }

  List* l;
  for (l = head; l->next != NULL; l = l->next);
  l->next = new;

  return head;
}

void die(Token t, char* msg) {
  fprintf(stderr, "parse error (%d - %d): %s\n", t.start, t.end, msg);
  exit(EXIT_FAILURE);
}

SExpr* new_sexpr(expr_type type, Token tok, void* value) {
  SExpr* e = malloc(sizeof(SExpr));
  e->type = type; e->tok = tok; e->value = value;
  return e;
}

List* parse_list() {
  extern SExpr* parse_expr();
  // TODO: Keep reference to tail for quick append
  List* head = NULL;
  while (peek().type != RPAREN && peek().type != END)
    head = append(head, parse_expr());
  advance(); // consume rparen
  return head;
}

int* toktoi(Token tok) {
  char old = buf[tok.end];
  buf[tok.end] = '\0';
  int* ret = malloc(sizeof(int));
  *ret = atoi(buf + tok.start);
  buf[tok.end] = old;
  return ret;
}

SExpr* parse_expr() {
  Token tok = advance();
  switch (tok.type) {
    case IDENT:
      return new_sexpr(IDENTIFIER, tok, NULL);
    case NUMBER:
      return new_sexpr(NUMERIC, tok, toktoi(tok));
    case LPAREN:
      return new_sexpr(LIST, tok, parse_list());
    case RPAREN:
      die(tok, "rparen not expected");
      return NULL;
    case END:
      fprintf(stderr, "warning: at end, returning null from parse_expr()\n");
      return NULL;
  }
}

void print_sexpr(SExpr* expr) {
  if (expr == NULL) {
    printf("nil");
    return;
  }

  Token tok;
  switch (expr->type) {
    case IDENTIFIER:
      tok = expr->tok;
      for (int i = tok.start; i < tok.end; i++)
        putchar(buf[i]);
      break;
    case NUMERIC:
      printf("%d", *(int*)expr->value);
      break;
    case LIST:
      printf("(");
      for (List* l  = expr->value; l != NULL; l = l->next) {
        print_sexpr(l->value);
        if (l->next != NULL)
          putchar(' ');
      }
      printf(")");
      break;
  }
}

/*********************** Main   ***********************/

int main() {
  size_t nread = fread(buf, sizeof(char), BUF_SIZE, stdin);
  if (nread == 0) {
    fprintf(stderr, "failed to read anything from stdin\n");
    return 1;
  }

  init_scanner(buf);
  init_parser();
  SExpr* expr = parse_expr();
  print_sexpr(expr);
  printf("\n");

  return 0;
}
