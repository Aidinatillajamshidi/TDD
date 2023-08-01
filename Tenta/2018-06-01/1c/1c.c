#include <stdio.h>

/* Pointers */

/* Answer = 0 0 */

int main()
{
  unsigned long int a = 2;  /* Value of a set to 2 */
  unsigned long int *b = &a;  /* Assigned address of variable a */
  unsigned long int *c = b;  /* Assigned value of b */
  *b = 0;  /* Assign value of 0 to same memory as a */
  
  printf("Answer: %lu %lu \n", a, *c);  /* Print 0 0 */
}
