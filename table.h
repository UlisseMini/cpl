struct bucket {
  char* name;
  char* value;
  struct bucket *next;
};

unsigned hash(char *s);
struct bucket *lookup(char *s);
struct bucket *install(char *name, char* value);
