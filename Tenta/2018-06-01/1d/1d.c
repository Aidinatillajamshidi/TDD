#include <stdio.h>

/* Logical AND-operation */

/* Decimal = Bits: (1 && 2) = (0001 && 0010) */
/* Decimal = Bits: 1 = true */
/* Decimal = Bits: (1 && 4) = (0001 && 0100) */
/* Decimal = Bits: 1 = true */

/* Answer = true */
/* Answer = 1 */

int main()
{
  printf("Answer: %d \n", (1 && 2) && 4);  /* Logical AND-operation */
}
