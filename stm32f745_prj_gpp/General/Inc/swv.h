/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SWV_H__
#define __SWV_H__

#include <_ansi.h>

_BEGIN_STD_C

#include "stm32f7xx_hal.h"

int _write ( int file, char *ptr, int len );

uint8_t printfGraph(uint8_t ch, size_t const port);

_END_STD_C

#endif // __SSD1306_H__
