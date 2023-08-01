#include <stdio.h>

/* Bitwise AND-operation */

/* Decimal = Bits: (1 | 4) = (0001 | 0100) */
/* Decimal = Bits: 5 = 0101 */
/* Decimal = Bits: 5 & 13 = 0101 & 1101 */
/* Decimal = Bits: 0101 */

/* Answer = 0101 */
/* Answer = 5 */

int main()
{
  printf("Answer: %d \n", (1 | 4) & 13);  /* Bitwise AND-operation */
  
  return 0;
}
