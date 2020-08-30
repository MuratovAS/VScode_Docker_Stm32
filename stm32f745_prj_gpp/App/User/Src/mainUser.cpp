
#include "main.h"
#include "mainUser.hpp"
#include "SecToMSec.hpp"

#ifdef DEBUG
#define DEBUG_STR "Debug"
#else
#define DEBUG_STR "Release"
#endif

uint8_t i = 0;
uint8_t j = 255;

void Setup()
{

}

void Loop()
{
	//test SWD 
    printf("%s git:%s\n\r", DEBUG_STR, GIT_STR);
    
	//test SWD graph
	//printfGraph(i,0);
	//printfGraph(j,1);
	//i+= 10;
	//j-= 10;

	//test gpio
    uint32_t tmp = SecToMSec(1);
	HAL_Delay(tmp);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

}