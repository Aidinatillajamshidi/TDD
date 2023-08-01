#include <stdio.h>

/* Array */

/* Refer to value at index a[2] with pointer and subtract 1 and deref pointer and return value */
/* i = 0 */
/* Value --- Index: a[0] = 1 --- *(a + 0) = 0 + 1 */
/* i = 1 */
/* Value --- Index: a[1] = 2 --- *(a + 1) = 1 + 1 */
/* i = 2 */
/* Value --- Index: a[2] = 3 --- *(a + 2) = 2 + 1 */
/* Value --- Index: 2 --- *(&a[2] - 1) = 3 - 1 */

/* Answer = 2 */

int main()
{
  int a[5];

  for(int i = 0; i < 5; ++i) /* Pre-increment - from 0 to 4 */
    {
      *(a + i) = i + 1;
      printf("%d \n", *(a + i)); /* 1, 2, 3, 4, 5 */
    }
  printf("Answer: %d \n", *(&a[2] - 1)); 
  
  return 0;
}
