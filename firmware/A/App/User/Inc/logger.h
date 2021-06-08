//
// Created by chrns on 4/30/20.
//

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "swv.h"

#ifdef  DEBUG
	//NOTE: настройка режима работы логгера
	#define USE_LOGGER

	#define LOGGER_SHOW_DEBUG           1
	#define LOGGER_SHOW_INFO            1
	#define LOGGER_SHOW_WARN            1

	#define LOGGER_SEQUENTIAL           0
#endif

#ifdef PRINT_SWO
	#define LOGGER_BUFFER_SIZE          SWO_BUFFER_SIZE
#else
	#define LOGGER_BUFFER_SIZE          256
#endif


// define somewhere in the project
extern void logger_out(const char* str, uint32_t len);

typedef void (*pLogger)(const char* format, ...);

/**
 * @brief Режимы вывода логгера
 * 
 */
typedef enum
{
	LOGGER_LVL_DEBUG = 0x00,
	LOGGER_LVL_INFO = 0x01,
	LOGGER_LVL_WARN = 0x02,

	LOGGER_LVL_PLAIN = 0xFF,
} LOGGER_LEVEL_t;

/**
 * @brief Указатель на какую-то функцию
 * 
 */
typedef void (*pLogger)(const char* format, ...);

/**
 * @brief Структура режимов вывода логгера
 * 
 */
typedef struct
{
	pLogger debug;
	pLogger info;
	pLogger warn;
	pLogger ln;
#if LOGGER_SEQUENTIAL
	LOGGER_LEVEL_t current_level;
#endif
} LOGGER_t;

/**
 * @brief Функция логгера
 * 
 */
extern LOGGER_t logger;

#endif //__LOGGER_H__
