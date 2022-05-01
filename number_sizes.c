#include <stdio.h>

#define dbg_size(typ) printf("sizeof(%s) = %lu (%lu bits)\n", #typ, sizeof(typ), sizeof(typ)*8)

int main() {
  dbg_size(char);
  dbg_size(void);
  dbg_size(short);
  dbg_size(long);
  dbg_size(float); // ~9.6 decimal digits
  dbg_size(double); // ~19.2 decimal digits
  dbg_size(long double); // ~38.4 decimal digits

  return 0;
}
