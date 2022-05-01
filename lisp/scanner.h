typedef enum {
  END, // end of file type
  LPAREN,
  RPAREN,
  IDENT,
  NUMBER,
} token_type;

typedef struct {
  token_type type;
  int start;
  int end;
} Token;

Token next_token();
void print_token(Token);
void init_scanner(char* buf);
