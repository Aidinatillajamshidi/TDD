#include <stdio.h>

/* 2 slots in data with every spot being 4 bytes */
/* 4 bytes + 4 bytes = 8 bytes */


union Data  /* Union created named Data */
{
  int i;
  int arr[2];  /* Array of size 2 */
} data;  /* Variable "data" is created */

int main()
{
  data.i = 2;  /* Variable "i" in union Data is assigned value 2 = 4 bytes */

  printf("Answer: %d \n", sizeof(data));  /* Use function sizeof() to calculate size in bytes */
  
  return 0;
}
