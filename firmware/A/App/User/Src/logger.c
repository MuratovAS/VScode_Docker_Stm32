//
// Created by chrns on 4/30/20.
//

#include "logger.h"

/** Прототипы локальных функций **/
static void logger_debug(const char* format, ...);
static void logger_info(const char* format, ...);
static void logger_warn(const char* format, ...);
static void logger_ln(const char* format, ...);

/** Локальные константы **/
__UNUSED const char lebel_debug[] = "[DEBUG]: ";
__UNUSED const char lebel_info[] = "[INFO ]: ";
__UNUSED const char lebel_warn[] = "[WARN ]: ";
__UNUSED uint32_t LEVEL_LEN = sizeof(lebel_debug);
static char buffer[LOGGER_BUFFER_SIZE] = {'\0'};

/** Инициализация  **/
LOGGER_t logger =
{
	.debug = logger_debug,
	.info = logger_info,
	.warn = logger_warn,
	.ln = logger_ln,
};

__INLINE void __logger(const char* str, uint32_t len, __UNUSED LOGGER_LEVEL_t level)
{
#if LOGGER_SEQUENTIAL
	logger.current_level = level;
#else
	switch (level)
	{
#if LOGGER_SHOW_DEBUG
	case LOGGER_LVL_DEBUG:
		logger_out(lebel_debug, LEVEL_LEN);
		break;
#endif
#if LOGGER_SHOW_INFO
	case LOGGER_LVL_INFO:
		logger_out(lebel_info, LEVEL_LEN);
		break;
#endif
#if LOGGER_SHOW_WARN
	case LOGGER_LVL_WARN:
		logger_out(lebel_warn, LEVEL_LEN);
		break;
#endif
	default:
		break;
	}
#endif
	logger_out(str, len);
}

void logger_debug(__UNUSED const char* format, ...)
{
#ifdef USE_LOGGER
	va_list arg;
	va_start(arg, format);
	uint32_t len = vsnprintf((char*)buffer, LOGGER_BUFFER_SIZE, format, arg);
	va_end(arg);
	__logger(buffer, len, LOGGER_LVL_DEBUG);
#endif
}

void logger_info(__UNUSED const char* format, ...)
{
#ifdef USE_LOGGER
	va_list arg;
	va_start(arg, format);
	uint32_t len = vsnprintf((char*)buffer, LOGGER_BUFFER_SIZE, format, arg);
	va_end(arg);
	__logger(buffer, len, LOGGER_LVL_INFO);
#endif
}

void logger_warn(__UNUSED const char* format, ...)
{
#ifdef USE_LOGGER
	va_list arg;
	va_start(arg, format);
	uint32_t len = vsnprintf((char*)buffer, LOGGER_BUFFER_SIZE, format, arg);
	va_end(arg);
	__logger(buffer, len, LOGGER_LVL_WARN);
#endif
}

void logger_ln(__UNUSED const char* format, ...)
{
#ifdef USE_LOGGER
	va_list arg;
	va_start(arg, format);
	uint32_t len = vsnprintf((char*)buffer, LOGGER_BUFFER_SIZE, format, arg);
	va_end(arg);
	__logger(buffer, len, LOGGER_LVL_PLAIN);
#endif
}
