#ifndef __MANAGERDWT_H_
#define __MANAGERDWT_H_

#include <_ansi.h>

_BEGIN_STD_C
#include "defines.h"

#include "stm32f3xx.h"

#define DWT_CYCCNT *(volatile uint32_t *)0xE0001004
#define DWT_CONTROL *(volatile uint32_t *)0xE0001000
#define SCB_DEMCR *(volatile uint32_t *)0xE000EDFC

#define SYSTEMCLOCK 64000000
#define TICKSPERUS  (SYSTEMCLOCK / 1000000)

/**
 * @brief Запуск DWT
 *
 */
__INLINE void ManagerDWT_Init(void)
{
	SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать DWT
	DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;   // включаем счётчик
	DWT_CYCCNT = 0;                          // обнуляем счётчик
}

/**
 * @brief Получить значение DWT
 *
 */
__INLINE uint32_t ManagerDWT_Get(void)
{
	return DWT_CYCCNT;
}

/**
 * @brief Сброс значение DWT
 *
 * @return uint32_t
 */
__INLINE void ManagerDWT_Reset(void)
{
	DWT_CYCCNT = 0; // обнуляем счётчик
}

/**
 * @brief Задержка в us
 *
 * @param us
 * @return __INLINE
 */
__INLINE uint32_t ManagerDWT_Delay(uint32_t us)
{
	uint32_t us_count_tic = us * TICKSPERUS; // получаем кол-во тактов за 1 мкс и умножаем на наше значение
	DWT_CYCCNT = 0U;                                          // обнуляем счётчик
	while (DWT_CYCCNT < us_count_tic)
		;
	return us;
}

_END_STD_C

#endif