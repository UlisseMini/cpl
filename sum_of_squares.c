#include <stdio.h>
#include <assert.h>

// want n = a^2 + b^2 + c^2 + d^2
// (these are used since C has no tuple type to return from functions)
int a, b, c, d;

int ceil_sqrt(int n) {
  int s;
  // bsearch [0, n] would be faster but isn't needed here
  for (s = 0; s*s < n; s++);
  return s;
}

// infeasible for large n, see as_squares_smart.
void as_squares_dumb(int n) {
  int s = ceil_sqrt(n);
  for (a = 0; a < s; a++) {
    for (b = 0; b < s; b++) {
      for (c = 0; c < s; c++) {
        for (d = 0; d < s; d++) {
          if (a*a+b*b+c*c+d*d == n)
            return;
        }
      }
    }
  }
}

#define MAX 1000*1000*100

static int one_squares[MAX]; // n = a^2
static int two_squares[MAX]; // n = a^2 + b^2 (only b is saved, b>=a)


// Roughly O(sqrt(n)^2) = O(n) with tables, very fast!
void as_squares_smart(int n) {
  int s = ceil_sqrt(n);

  for (a = 0; a < s; a++) {
    for (b = 0; b < s; b++) {
      int r;
      r = n - a*a - b*b;
      if (r < 0)
        continue; // TODO: only loop b while r>0 (more elegant)

      c = two_squares[r];
      if (c != 0) {
        d = one_squares[r - c*c];
        return;
      }
    }
  }
}

void init_tables() {
  fprintf(stderr, "building tables... ");
  for (int a = 0; a*a < MAX; a++) {
    one_squares[a*a] = a;
    for (int b = a; a*a+b*b<MAX; b++) {
      two_squares[a*a + b*b] = b;
    }
  }
  fprintf(stderr, "done\n");
}

int main() {
  int n = 31903488;
  assert(n < MAX);
  init_tables();
  as_squares_smart(n);
  printf("found %d^2 + %d^2 + %d^2 + %d^2 = %d\n", a,b,c,d,n);
  printf("got %d^2 + %d^2 + %d^2 + %d^2 = %d\n", a,b,c,d,a*a+b*b+c*c+d*d);

  return 0;
}
