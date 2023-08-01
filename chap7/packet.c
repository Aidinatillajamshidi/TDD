#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "inbound.h"
#include "elapsed.h"
#include "serial.h"

extern OS_EVENT *send; /* Data-struct from <uc/os.h> */ 

//Added into "main.c" file

void ReceivePackets(void)
{
  SerialInit() ;
  
  for (;;)
  {
    int type, byte, bytes ;
    BYTE8 *bfr ;
    
    if (SerialGet() != 0xFF)
      continue ;
    
    switch (type = SerialGet())
    {
      default:
        continue ;
      case 1:
      case 2:
        break ;
    }
    
    bytes = SerialGet();
    bfr = (BYTE8 *) malloc(bytes) ;
    if (!bfr)
    {
      for (;;)
        ;
    }
    
    for (byte = 0; byte < bytes; byte++)
    {
      bfr[byte] = SerialGet() ;
    }
    switch (type)
    {
      case 1:
        PostText(bfr) ;
        break ;
      case 2:
        PostTime(bfr) ;
        break ;
    }
  }
}

/* Send each byte of the packet by calling "SerialPut"  */
/* "send = OSSemCreate()" created in "main.c" */
void SendPacket(int type, BYTE8 *bfr, int bytes)
{
  OSSemPend(send, 0, NULL);  /* Included semaphore from <uc/os.h> */
  SerialPut((BYTE8)0xFF);  //Startflag
  SerialPut((BYTE8)type);  //0x01 = Chat, 0x02 = Time
  SerialPut((BYTE8)bytes);  //Actual data bytes

  for(int i = 0; i < bytes; i++)
    {
      SerialPut((BYTE8)bfr[i]);  /* Send every byte of data until it reaches NULL  */
    }
  OSSemPost(send);
}
