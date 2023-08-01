#include <libepc.h>

int main(int argc, char *argv[])
{
	//+++++ Initialization +++++

	ClearScreen(0x07);
	SetCursorPosition(1, 1);
	QWORD64 x = 0;

	while(Milliseconds() < 1002)
	  {
	    if(Milliseconds() == 1000)
	      {
		x = CPU_Clock_Cycles();
	      }
	  }

	//+++++ Estimate number of CPU cycles per second +++++

	// assignment 4
	
	SetCursorPosition(2, 1);
	PutString("CPU cycles per second = ");
	PutUnsigned((DWORD32)(x / 1000000), 10, 8);
	PutString(" x 10^6 \n");
	
	//+++++ Estimate number of CPU cycles of some operation +++++

	// assignment 5

	x = CPU_Clock_Cycles();
	
	for (int i = 0; i < 10000; i++)
	  {

	  }
	x = CPU_Clock_Cycles() - x;

	
	
	SetCursorPosition(4, 1);
	PutString("Average nnumber of CPU cycles per operation: ");	
	PutUnsigned(x/10000, 10, 8);
	PutString("\n");	


	return 0;


}
