#include "swv.h"


int _write ( int file, char *ptr, int len )
{
  int i = 0;
  for ( i = 0; i < len; i++ )
    ITM_SendChar ( *ptr++ );
  return len;
}

uint8_t printfGraph(uint8_t ch, size_t const port)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM enabled */
      ((ITM->TER & (port+1)          ) != 0UL)   )     /* ITM Port enabled */
  {
    while (ITM->PORT[port].u32 == 0UL)
    {
      __NOP();
    }
    ITM->PORT[port].u8 = (uint8_t)ch;
   }
  return (ch);
}