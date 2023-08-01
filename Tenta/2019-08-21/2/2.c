#include <stdio.h>

/* Returns little-endian value corresponding to 4 bytes big-endian number */

unsigned convert(unsigned num)
{
  unsigned result = 0;
  result |= (num & 0xFF) << 24;  // Extract and shift the least significant byte
  result |= (num & 0xFF00) << 8;  // Extract and shift the second least significant byte
  result |= (num & 0xFF0000) >> 8;  // Extract and shift the second most significant byte
  result |= (num & 0xFF000000) >> 24;  // Extract and shift the most significant byte
  return result;
}

int main()
{
  unsigned num;
  
  printf("Answer: %d \n", convert(num));
  return 0;
}
