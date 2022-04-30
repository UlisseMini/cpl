#include <stdlib.h>
#include <string.h>
#include "table.h"

#define HASHSIZE 101

static struct bucket *table[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

struct bucket *lookup(char *s) {
  struct bucket *b;
  for (b = table[hash(s)]; b != NULL; b = b->next) {
    if (strcmp(s, b->name) == 0)
      return b;
  }
  return NULL;
}

struct bucket *install(char *name, char* value) {
  unsigned int hashval;
  struct bucket *b;

  if ((b = lookup(name)) == NULL) {
    b = malloc(sizeof(struct bucket));
    if (b == NULL || (b->name = strdup(name)) == NULL)
        return NULL;
    hashval = hash(name);
    b->next = table[hashval];
    table[hashval] = b;
  } else
    free(b->value);

  if ((b->value = strdup(value)) == NULL)
    return NULL;

  return b;
}
