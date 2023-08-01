#include <stdio.h>

/* Bitwise AND-operation */

/* Decimal = Bits: (4 | 2) = (0100 | 0010) */
/* Decimal = Bits: (6) = (0110) */
/* Decimal = Bits: (6 & 1) = (0110 & 0001) */
/* Decimal = Bits: (0) = (0000) */

/* Answer = 0000 */
/* Answer = 0 */

int main()
{
  printf("Answer: %d \n", (4 | 2) & 1);  /* Bitwise AND-operation */
}
