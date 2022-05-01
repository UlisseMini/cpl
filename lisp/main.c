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

/* static Token advance_if(token_type t) { */
/*   if (peek().type == t) */
/*     return advance(); */
/* } */

List* list_new(void* v) {
  List* l = malloc(sizeof(List));
  l->value = v;
  l->next = NULL;
  return l;
}

List* append(List* head, void* v) {
  List* new = list_new(v);
  if (head == NULL) {
    return new;
  }

  List* l;
  for (l = head; l->next != NULL; l = l->next);
  l->next = new;

  return head;
}

void die(char* msg) {
  fprintf(stderr, "error: %s\n", msg);
  exit(EXIT_FAILURE);
}

SExpr* parse_expr() {
  SExpr* e = malloc(sizeof(SExpr));

  Token t = advance();
  e->tok = t;
  switch (t.type) {
    case IDENT:
      e->type = IDENTIFIER;
      e->value = NULL; /* lexeme is in e->tok */
      break;
    case LPAREN:
      e->type = LIST;
      List* head = NULL;
      while (peek().type != RPAREN && peek().type != END)
        head = append(head, parse_expr());
      e->value = head;
      t = advance(); // consume rparen

      break;
    case RPAREN:
      /* die("rparen not expected"); */
      break;
    case END:
      fprintf(stderr, "reached end, returning null\n");
      free(e);
      e = NULL;
      break;
  }
  return e;
}

void print_sexpr(SExpr* expr) {
  if (expr == NULL) {
    printf("null");
    return;
  }


  Token tok;
  switch (expr->type) {
    case IDENTIFIER:
      tok = expr->tok;
      for (int i = tok.start; i < tok.end; i++)
        putchar(buf[i]);
      putchar(' ');
      break;
    case LIST:
      printf("(");
      for (List* l  = expr->value; l != NULL; l = l->next) {
        print_sexpr(l->value);
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
  curr_token = next_token(); // SO UGLY
  SExpr* expr = parse_expr();
  print_sexpr(expr);
  printf("\n");

  return 0;
}
