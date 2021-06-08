#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>
#include <_ansi.h>

/* Директивы компилятора */
//#define __packed(x)    __attribute__((__packed__,__aligned__(x)))
//#define __unused       __attribute__((unused))
//#define __inline       __attribute__((always_inline)) inline

/* Константы времени */
#define EPOCH                           2020U
#define MONTH_JANUARY                   1U
#define MONTH_FEBRUARY                  2U
#define MONTH_MARCH                     3U
#define MONTH_APRIL                     4U
#define MONTH_MAY                       5U
#define MONTH_JUNE                      6U
#define MONTH_JULY                      7U
#define MONTH_AUGUST                    8U
#define MONTH_SEPTEMBER                 9U
#define MONTH_OCTOBER                   10U
#define MONTH_NOVEMBER                  11U
#define MONTH_DECEMBER                  12U
#define DATE(year,month)                ((year - EPOCH) * 12 + month)


/**
 * @brief Состояние, вкл./выкл.
 * 
 */
typedef enum {
	ST_OFF    = 0,
	ST_ON     = 1,
} STATE_t;

/**
 * @brief Код возврата из функции
 * 
 */
typedef enum {
	ST_SUCCESS = 254,
	ST_ERROR   = 255,
} STATUS_t;

/**
 * @brief Коды физических величин
 * 
 */
typedef enum {
	VOLTAGE  = 0,
	CURRENT  = 1,
	FREQUENCY = 2,
	COEFFICIENT = 3,
	TEMPERATURE = 4
} PHYSICAL_t;

#endif /* __DEFINES_H__ */