#ifndef __PID_H__
#define __PID_H__

#include <_ansi.h>

_BEGIN_STD_C

#include "defines.h"

/**
 * @brief Структура ПИД-регулятора.
 *
 */
typedef struct _PidController
{
	float* target; //целевая
	float* current; //текущая

	float ki;
	float kd;
	float kp;

	uint32_t dt;

	float E;
	float E0;
	float P;
	float Int;
	float I;
	float D;

	float PID;

	float clamp_min;
	float clamp_max;

} pid_controller_t;

/**
 * @brief Инициализирует ПИД-регулятор.
 *
 * @param controller ПИД-регулятор.
 * @param target целевая
 * @param current текущая
 * @param kp Пропорциональный коэффициент.
 * @param ki Интегральный коэффициент.
 * @param kd Дифференциальный коэффициент.
 * @param dt Время 1 цикла работы PID
 */
void PID_Init(pid_controller_t* _controller, float* _target, float* _current, float _kp, float _ki, float _kd, uint32_t dt);

/**
 * @brief Вычисляет значение регулирования.
 *
 * @param controller ПИД-регулятор.
 */
void PID_Calculate(pid_controller_t* controller);

/**
 * @brief Получает значение регулирования.
 *
 * @param controller ПИД-регулятор.
 * @return Значение регулирования.
 */
float PID_value(pid_controller_t* _controller);


/**
 * @brief Устанавливает значения отсечения.
 *
 * @param controller ПИД-регулятор.
 * @param clamp_min Минимальное значение.
 * @param clamp_max Максимальное значение.
 */
void PID_clamp(pid_controller_t* controller, float clamp_min, float clamp_max);

_END_STD_C

#endif
