#include <stdio.h>

/* Loop return values = 0, 2, 4, 6 */
/* *(a + 1) refers to value at index 1 in array a which is 2 */
/* (a + (2)) is the return value */
/* *(a + 2) refers to value at index 2 in array which is 4 */
/* Dereference pointer with * before to return value and free up memory */

/* Answer = 4 */

int main()
{
  int a[4];  /* Init array of size 4 */

  for(int i = 0; i < 4; ++i)  /* Increment i and return value before loop - 4 iterations */
    {
      a[i] = 2 * i;
      printf("%d \n", a[i]);
    }
  printf("Answer: %d \n", *(a + *(a + 1)));  /* Return value at a[2] and dereference pointer */
}
