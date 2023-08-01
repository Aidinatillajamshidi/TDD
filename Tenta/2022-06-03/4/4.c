#include <stdio.h>

unsigned int main(unsigned int current)
{
  if ((current & 0x3F) < 59)
	return current + 1;

 unsigned int rslt = (current >> 6) & 0x7FF;

 if ((rslt & 0x3F) < 59)
	return (rslt + 1) << 6;

 rslt =  rslt >> 6;
 if(rslt < 23)
	return (rslt+1) << 12;
 return 0;
}
