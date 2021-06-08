#include "test_core.hpp"
#include <graphs.hpp>

#include <cmath>

#include <pid_.h>

pid_controller_t PID;
float target = 80;
float signal = 0;
float FB = 0;


#define LOW_VALUE 10      // к этому значению "остывает" система
#define SIGNAL_COEF 1   // сила сигнала
#define DELAY_AMOUNT 5   // задержка изменения
float COEF = 0.2;

void process() {
  static float valueSpeed;
  static float signalSpeed;
  static bool firstFlag = false;
  static float delayArray[DELAY_AMOUNT];
  
  // сигнал == скорость нагрева
  // ограничивает сигнал его же значением и плавно к нему стремится
  signalSpeed += (signal - signalSpeed) * 0.003;

  // складываем скорость сигнала и скорость охлаждения
  // скорость охлаждения получаем как разность "температуры" и её нулевого значения
  valueSpeed = signalSpeed * SIGNAL_COEF + (LOW_VALUE - FB) * COEF;

  if (!firstFlag) {
    firstFlag = true;
    for (int i = 0; i < DELAY_AMOUNT; i++) delayArray[i] = valueSpeed;
  }

  for (int i = 0; i < DELAY_AMOUNT - 1; i++) delayArray[i] = delayArray[i + 1];
  delayArray[DELAY_AMOUNT - 1] = valueSpeed;

  // прибавляем скорость (интегрируем)
  FB += /*valueSpeed*/delayArray[0];
}

double tmp_result_cur = 0;
double tmp_result_tar = 0; 
double afunction(double x)
{
	PID_Calculate(&PID);
 	signal = PID_value(&PID);
	process();
	return tmp_result_tar = target;
}

double bfunction(double x)
{
	return signal;
}

double cfunction(double x)
{
	return tmp_result_cur = FB;
}

int main(int /* argc */, char const * /* argv */[])
{
	UT_START("PID")
	//TEST START
	PID_Init(&PID, &target, &FB, 3, 0.0033, 0, 1);
	PID_clamp(&PID, 0, 50);

	const size_t height = 70;
	const size_t width = 150;

	const long double ymin = 0;
	const long double ymax = 100;
	const long double xmin = 0;
	const long double xmax = 200;
	// Output array as plot
	size_t numfunctions = 3;
	double (*functions[])(double) = {afunction, bfunction, cfunction};

	graph(height, width, xmin, xmax, ymin, ymax, numfunctions, functions, graphdefaultoptions);

	std::cout << "target: " << tmp_result_tar << std::endl;
	std::cout << "current: " << tmp_result_cur << std::endl;
	if(round(tmp_result_tar) == round(tmp_result_cur))
		UT_SUCCESS
	else
		UT_ERROR
}
