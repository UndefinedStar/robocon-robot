#include "fifo.h"

void fifo_wrst()
{
   FIFO_WR=0;
   __NOP();
  __NOP();
  FIFO_WRST=0;
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  __NOP();
  FIFO_WRST=1;
}
void fifo_rrst()
{
    unsigned char i;
  FIFO_OE=0;
  FIFO_RRST=0;
  for(i = 0;i < 6;i ++)
  {
      FIFO_RCK=0;
      __NOP();
      FIFO_RCK=1;
      __NOP();
   }
  FIFO_OE=1;
  FIFO_RRST=1; 
}
void fifo_init()
{
  fifo_wrst();
  fifo_rrst();
}