#include <stdio.h>

/* Fibonacci sequence */

/* Answer = 2 */

int main()
{
  int a[5];  /* Init a int array of size 5 */
  char* tmp[] = {"First loop:", "Second loop:", "Third loop:"}; /* Text for loop */
  a[0] = 0;  /* Initialize value of Fibonacci sequence (0) */
  a[1] = 1;  /* Initialize value of Fibonacci sequence (1) */ 

  for(int i = 0; i < 3; ++i)  /* Preincrement - from 0 to 2 */
    {
      *(a + i + 2) = *(a + i) + *(a + i + 1);  /* Calculate next Fibonacci number */

      printf("\n%s: %d ", tmp[i], a[i]);  /* %s for char/string and %d for int */
    }
  
  printf("\n\nAnswer: %d \n", a[3]);  /* Result is printed here */
  
  return 0;
}
