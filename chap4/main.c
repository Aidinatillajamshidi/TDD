#include <libepc.h>

/* Assembly Clock Cycles: 24479232 */
/* C Clock Cycles: 25980555  */
/* -O3 C : 30 300 000 */
/* -O0 C : 31 000 000  */

//long int -> 32 bit
//long long int -> 64 bit


//Assembly function call
void llmultiply(unsigned long long int l1,
                unsigned long long int l2,
                unsigned char *result);


//r1 = a
//r2 = b
// C_llmultiply

void c_llmultiply(unsigned long long int a,
		  unsigned long long int b,
		  unsigned char *result)
{
  unsigned long long a_lo = (unsigned long int)a;
  unsigned long long a_hi = a >> 32;
  unsigned long long b_lo = (unsigned long int)b;
  unsigned long long b_hi = b >> 32;

  unsigned long long a_x_b_hi = a_hi * b_hi;
  unsigned long long a_x_b_mid = a_hi * b_lo;
  unsigned long long b_x_a_mid = b_hi * a_lo;
  unsigned long long a_x_b_lo = a_lo * b_lo;

  unsigned long long carry_bit = ((unsigned long long int)(unsigned long int)a_x_b_mid +
				  (unsigned long long int)(unsigned long int)b_x_a_mid +
				  (a_x_b_lo >> 32)) >> 32;

  unsigned long long int hi = a_x_b_hi + (a_x_b_mid >> 32) + (b_x_a_mid >> 32) + carry_bit;
  unsigned long long int lo = a_x_b_lo + (a_x_b_mid << 32) + (b_x_a_mid << 32);

  unsigned long long int* p = (unsigned long long int*) result;
  p[0] = lo;
  p[1] = hi;
}




struct test_case {
  unsigned long long int a;
  unsigned long long int b;
  unsigned long long int rh;
  unsigned long long int rl;
};

struct test_case cases[6] = {

  { 0x0000111122223333ULL, 0x0000555566667777ULL,
    0x0000000005B061D9ULL, 0x58BF0ECA7C0481B5ULL },

  { 0x3456FEDCAAAA1000ULL, 0xEDBA00112233FF01ULL,
    0x309A912AF7188C57ULL, 0xE62072DD409A1000ULL },

  { 0xFFFFEEEEDDDDCCCCULL, 0xBBBBAAAA99998888ULL,
    0xBBBB9E2692C5DDDCULL, 0xC28F7531048D2C60ULL },

  { 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL,
    0xFFFFFFFFFFFFFFFEULL, 0x0000000000000001ULL },
  
  { 0x00000001FFFFFFFFULL, 0x00000001FFFFFFFFULL,
    0x0000000000000003ULL, 0xFFFFFFFC00000001ULL },

  { 0xFFFEFFFFFFFFFFFFULL, 0xFFFF0001FFFFFFFFULL,
    0xFFFE0002FFFDFFFEULL, 0x0001FFFE00000001ULL }
};

void PutUnsignedLongLong(unsigned long long int* ulli)
{
  unsigned long int* uli = (unsigned long int*)ulli; 
  PutUnsigned(uli[1], 16, 8);
  PutUnsigned(uli[0], 16, 8); 
}

int main(int argc, char *argv[])
{
  unsigned char result[16];
  int i;
  QWORD64 start_time, end_time;
  
  ClearScreen(0x07);
  SetCursorPosition(0, 0);

  start_time = CPU_Clock_Cycles();
  for (i = 0; i < 6; ++i)
  {
    PutString("Test : ");
    PutUnsignedLongLong(&cases[i].a);
    PutString(" * ");
    PutUnsignedLongLong(&cases[i].b); 
    PutString("\r\n");
   
    PutString("    == ");
    PutUnsignedLongLong(&cases[i].rh);
    PutUnsignedLongLong(&cases[i].rl);
    PutString("\r\n");
    
    //llmultiply(cases[i].a, cases[i].b, result);  //Assembly
    c_llmultiply(cases[i].a, cases[i].b, result);  //C
    
    PutString("Result ");
    PutUnsignedLongLong((unsigned long long int*)&result[8]);
    PutUnsignedLongLong((unsigned long long int*)&result[0]); 
    PutString("\r\n");
    
    PutString("\r\n");
  }

  end_time = CPU_Clock_Cycles();
  PutString("Clock Cycles: ");
  end_time = (end_time - start_time) / 6;
  PutUnsigned(end_time, 10, 16);
  
  
  return 0;
}
