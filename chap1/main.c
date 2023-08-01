#include <libepc.h>

int main(int argc, char *argv[])
{
   ClearScreen(0x07);
   SetCursorPosition(0, 0);
   
   //PutString(">>>>>>> Empty Floppy Used as Skeleton <<<<<<<\r\n");
   PutString("Name: Aidin \r\n");
   PutString("LiU-id: aidja644 \r\n");
   PutString("Period: VT22 \r\n");
   PutString("Age: 1337 \r\n");
   PutString("#Coolboiiii1337");
   
   return 0;
}
