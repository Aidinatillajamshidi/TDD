#include <stdio.h>

/* Logical AND-operation */

/* Decimal = Bits: ~(5) = ~(2 + 3) = ~(0101) */
/* Decimal = Bits: ~(5) = ~(0101) -> 10 = 1010 */
/* Decimal = Bits: ~1 = ~0001 */
/* Decimal = Bits: ~1 = ~0001 -> 14 = 1110 */
/* Both sides are non-zero which results in true - 10 && 14 */

/* Answer = true */
/* Answer = 1 */

int main()
{
  printf("%d \n", ~(2 + 3) && ~1);  /* Logical AND-operation */
  return 0;
}
