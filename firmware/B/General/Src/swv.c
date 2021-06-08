#include "swv.h"

#include "stm32f1xx.h"

__UNUSED static char buffer[SWO_BUFFER_SIZE] = {'\0'};

__STATIC_INLINE uint32_t ITM_SendChar_C(uint32_t ch, size_t const port)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && /* ITM enabled */
      ((ITM->TER & (port + 1)) != 0UL))           /* ITM Port enabled */
  {
    while (ITM->PORT[port].u32 == 0UL)
    {
      __NOP();
    }
    ITM->PORT[port].u8 = (uint8_t)ch;
  }
  return (ch);
}

uint32_t plotSWO(__UNUSED uint32_t ch, __UNUSED PORT_SWO_t port)
{
#ifdef  DEBUG
#ifdef  PLOT_SWO
#ifndef PRINT_SWO
  return ITM_SendChar_C(ch, port);
#endif
#endif
#endif
  return 0;
}

void printSWO(__UNUSED const char *format, ...)
{
#ifdef  DEBUG
#ifdef  PRINT_SWO
#ifndef PLOT_SWO
  va_list arg;
  va_start(arg, format);
  uint32_t len = vsnprintf((char *)buffer,SWO_BUFFER_SIZE, format, arg);
  va_end(arg);
  for (uint32_t i = 0; i < len; i++)
  {
    ITM_SendChar_C((char)buffer[i], 0);
  }
#endif
#endif
#endif
}
