#include <stdio.h>

/* Pointers */

/* Answer = 7 5 */

int main()
{
  unsigned long int a = 5;  /* Assign value 5 */
  unsigned long int *b = &a;  /* Assign adress of a */
  unsigned long int c = *b;  /* Assign value storated at mem address b */
  *b = 7;  /* Changes value stored at mem address pointed by b to 7 */
  
  return printf("%lu %lu \n", a, c);  /* Print 7 5 */
}
