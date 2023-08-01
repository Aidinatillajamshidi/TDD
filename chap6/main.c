#include <mtc.h>
#include <dos.h>  /* This library has functions that are used for handling interrupts, producing sound, date and time functions */
#include <libepc.h>  /* Libepec stands for "Library for Electrical Power System Calculations" and provides a set of functions for performing various calculations related to electrical power systems.  */
#include "serial.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Function prototypes for the threads */
void OutBound(void) ;
void InBound(void) ;
void DisplayElapsedTime(void) ;
PRIVATE void SerialInit(void) ;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QUEUE *inbound_queue ;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  inbound_queue = QueueCreate(sizeof(char), 20) ;
  
  ClearScreen(0x07) ;
  SetCursorVisible(TRUE) ;
  SerialInit() ;
  
  MtCCoroutine(OutBound()) ;
  MtCCoroutine(InBound()) ;
  MtCCoroutine(DisplayElapsedTime()) ;  //La till tidvisaren här

  return 0 ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PRIVATE void SerialInit(void)
{
  /* Disable interrupts during initialization */
  disable() ;
  
  /* 9600 baud */
  outportb(SER_LCR, SER_LCR_DLAB) ;
  outportb(SER_DLO, 12) ;
  outportb(SER_DHI, 0) ;
  
  /* 8 data bits, even parity, 1 stop bit */
  outportb(SER_LCR, 0x1B) ;
  
  /* Enable only receiver data ready interrupts */
  outportb(SER_IER, 0x01) ;
  
  /* Request to send, data terminal ready, enable interrupts */
  outportb(SER_MCR, SER_MCR_RTS|SER_MCR_DTR|SER_MCR_OUT2) ;
  
  /* Store address of ISR in IDT */
  SetISR(IRQ2INT(SER_IRQ), SerialISR) ;
  
  /* Unmask the UART's IRQ line */
  outportb(0x21, inportb(0x21) & ~SER_MSK) ;
  
  /* Re-enable interrupts */
  enable() ;
}

void DisplayElapsedTime(void)  //Displays elapsed time on screen and waits one second between updates
{
  WINDOW *w = WindowCreate("Time", 22, 24, 0, 79);  /* Create a Window of size(22, 24, 0, 79) */
  unsigned long long prev_time = 0;

  for( ; ; )  /* Pseudo-code */
    {
      unsigned long long current_time = Milliseconds();  /* Init milliseconds() included from <libepc.h> */
      if(current_time >= prev_time + 1000)
	{
	  unsigned long long elapsed_seconds = current_time / 1000;
	  unsigned long long seconds = elapsed_seconds % 60;  //Modulo operator for hh:mm:ss
	  unsigned long long minutes = (elapsed_seconds / 60) % 60;  //Modulo operator for hh:mm:ss
	  unsigned long long hours = (elapsed_seconds / 3600) % 24;  //Modulo operator for hh:mm:ss

	  WindowSelect(w);  //Output numbers to screen
	  PutUnsigned(hours%24, 10, 2);  //Show hours with % 24 "divided"
	  PutString(":");
	  PutUnsigned(minutes%60, 10, 2);  //Show minutes with % 60 "divided"
	  PutString(":");
	  PutUnsigned(seconds%60, 10, 2);  //Show seconds with % 60 "divided"

	  prev_time = current_time;
	}
      MtCYield();  /* Note that the elapsed time thread must release the processor whenever it is idle by explicitly calling the function “MtCYield”. */
    }
};
