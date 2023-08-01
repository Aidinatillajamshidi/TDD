#include <stdio.h>

/* Logical AND-operation */

/* Decimal = Bits: 1 = 0001 */
/* Decimal = Bits: ~1 = 1110 */
/* Bitwise complement operator ~ inverts all bits */
/* Decimal = Bits: 2 = 0010 */
/* 11|1|0 && 00|1|0 = 1 = true */

/* Answer = true */
/* Answer = 1 */

int main()
{
  printf("Answer: %d \n", ~1 && 2);  /* Logical AND-operation */

  return 0;
}
