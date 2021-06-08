#include "pid_.h"

void PID_Init(pid_controller_t* _controller, float* _target, float* _current, float _kp, float _ki, float _kd, uint32_t _dt)
{
	_controller->target = _target;
	_controller->current = _current;

	_controller->dt = _dt;

	_controller->ki = _ki;
	_controller->kd = _kd;
	_controller->kp = _kp;

	_controller->E = 0;
	_controller->E0 = 0;
	_controller->P = 0;
	_controller->Int = 0;
	_controller->I = 0;
	_controller->D = 0;

	_controller->PID = 0;

	_controller->clamp_min = 0;
	_controller->clamp_max = 0;
}

void PID_Calculate(pid_controller_t* _controller)
{
	_controller->E0 = _controller->E;						  // Предыдущее значение ошибки
	_controller->E = *(_controller->target) - *(_controller->current); // Текущая ошибка в градусах

	// Пропорциональная составляющая
	if (_controller->kp != 0)
		_controller->P = (_controller->kp) * (_controller->E); // Пропорциональнsq вклад в регулирование
	else
		_controller->P = 0;

	// Интегральная составляющая
	if (_controller->ki != 0)
	{
		_controller->Int = _controller->Int + (_controller->E ) * (_controller->dt); // Интеграл разсогласования
		_controller->I = (_controller->ki) * (_controller->Int);
		//_controller->I = (_controller->ki) * (_controller->I + (_controller->E * _controller->dt));
	}
	else
		_controller->I = 0;

	// Дифференциальная составляющая
	if (_controller->kd != 0)
		_controller->D = (_controller->kd) * (((_controller->E) - (_controller->E0)) / (_controller->dt)); // Дифференциальный вклад в регулирование
	else
		_controller->D = 0;

	_controller->PID = ((_controller->P) + (_controller->I) + (_controller->D)); // Регулятор
}

float PID_value(pid_controller_t* _controller)
{
	if (_controller->PID < _controller->clamp_min)
		_controller->PID = _controller->clamp_min;
	else if (_controller->PID > _controller->clamp_max)
		_controller->PID = _controller->clamp_max;
	return _controller->PID;
}

void PID_clamp(pid_controller_t* _controller, float _clamp_min, float _clamp_max)
{
	_controller->clamp_max = _clamp_max;
	_controller->clamp_min = _clamp_min;
}
