#include <stdio.h>

/* Bitwise AND-operation */

/* 1000 & 0111 = 0000 = false */
/* !(0000) = true */

/* 16 */
/* 0001 0000 & 0000 0111 = 0000 0000 = false */
/* !(0000 0000) = true */

int main()
{
  int x = 8;
  int multiple = !(x & 0x07);

  return printf("%d \n", multiple);
}
