#ifndef __SWV_H__
#define __SWV_H__

#include <_ansi.h>

_BEGIN_STD_C

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

// NOTE: для включения функции работы с SWO нужно определить PRINT_SWO || PLOT_SWO. ФУНКЦИИ ВЗАИМОИСКЛЮЧАЮЩИЕ
#define PRINT_SWO 
//#define PLOT_SWO

#define SWO_BUFFER_SIZE          256

typedef enum
{
    PORT_0 = 0,
    PORT_1 = 1,
} PORT_SWO_t;

/**
 * @brief функция аналогично printf
 * 
 * @param format управляющая строка
 * @param ... параметры
 */
void printSWO(const char *format, ...);

/**
 * @brief построитель графиков
 * 
 * @param ch значение
 * @param port порт, по умолчанию можно строить 2 графика
 * @return uint8_t 
 */
uint32_t plotSWO(uint32_t ch, PORT_SWO_t port);

_END_STD_C

#endif 
