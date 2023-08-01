#include <stdio.h>

/* Index: a[0] = 2 */
/* Index: a[1] = 3 */
/* Index: a[2] = 4 */
/* Index: a[3] = 5 */
/* Index: a[4] = 6 */
/* Pointer = Index: *(a + 3) = a[3] */

/* a[3] = 5 */
/* Answer = 5 */

int main()
{
  int a[5];
  char* tmp[] = {"First loop:", "Second loop:", "Third loop:", "Fourth loop:", "Fifth loop:"};

  for(int i = 0; i < 5; ++i)  /* Preincrement - from 0 to 4 (5 times) */
    {
      a[i] = i + 2;
      printf("%s %d \n", tmp[i], a[i]);  /* Print out value */
    }
  
  printf("\nAnswer: %d \n", *(a + 3)); /* Access value at index 3 and dereference pointer */
}
