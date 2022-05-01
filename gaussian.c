#include <stdio.h>
#include <math.h>

#define cdf(x) (0.5*(1 + erf(x)))
#define within(x) (cdf(x) - cdf(-x))

int main() {
  printf("cdf(0) = %f\n", cdf(0.0));
  for (double f = 0; f < 3; f += 0.1) {
    printf("within(%f) = %f\n", f, within(f));
  }
  return 0;
}
