#ifndef _MAINUSER_H
#define _MAINUSER_H

#include <_ansi.h>


_BEGIN_STD_C

#include "main.h"

#include "build_info.h"

#include "swv.h"
#include "logger.h"

#ifdef DEBUG
	#define BUILD_TYPE_STR "Debug"
#else
	#define BUILD_TYPE_STR "Release"
#endif


/**
 * @brief Восстановление после запуска
 * - Перенос таблицы векторов
 * - Проверка проснулись ли мы по IWDG
 * */
void restore();

/**
 * @brief Настройка после HAL
 * */
void setup();

/**
 * @brief Основной цикл программы
 * */
void loop();

_END_STD_C

#endif
