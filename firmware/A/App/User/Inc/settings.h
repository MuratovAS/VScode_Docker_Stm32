#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <_ansi.h>

_BEGIN_STD_C
#include <stdbool.h>
#include <stdint.h>

#define BYTES_IN_KBYTE			1024

typedef struct __PACKED_8
{
	/// modbus RTU
	bool use_modbus_rtu;
	uint32_t modbus_rtu_rate;
	uint8_t modbus_rtu_addr;
	/// logger
	bool use_logger;
	bool use_logger_debug;
	bool use_logger_info;
	bool use_logger_warn;
	bool use_logger_error;
} SETTINGS_t;

/**
 * @brief Модифицировать можно на лету, сохранение только по вызову
 * settings_save(). Функция settings_load() должна быть вызвана в
 * самом начале программы
 * */
extern SETTINGS_t settings;

/**
 * @brief
 * */
void settings_load(void);

/**
 * @brief
 * */
void settings_save(void);

_END_STD_C

#endif //__SETTINGS_H__
