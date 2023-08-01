#include <stdio.h>

/* Logical AND-operation */

/* Decimal = Bits: (0 || 2) = (0000 || 0010) = (0010) */
/* Decimal = Bits: (2 && 3) = (0010 && 0011) = true */
/* Both sides are non-zero which returns true = 1 */

/* Answer = true */
/* Answer = 1 */

int main()
{
  return printf("%d \n", (0 || 2) && 3);  /* Logical AND-operation */
}
