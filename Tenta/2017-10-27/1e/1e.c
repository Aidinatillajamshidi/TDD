#include <stdio.h>

/* Bitwise OR-operation */

/* Decimal = Bits: (0 | 2) = (0000 | 0010) */
/* Decimal = Bits: 2 = 0010 */
/* Decimal = Bits: (2 & 3) = (0010 & 0011) */
/* Decimal = Bits: 2 = 0010 */

/* Answer = 2 */

int main()
{
  return printf("Answer: %d \n", (0 | 2) & 3);  /* Bitwise OR-operation */
}
