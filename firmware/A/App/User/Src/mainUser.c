#include "mainUser.h"

void restore()
{
	//SCB->VTOR = (uint32_t)APPL_ORIGIN; // TODO: check it
	//__enable_irq();

#ifdef DEBUG
	__HAL_DBGMCU_FREEZE_IWDG(); /// Отключаем IWDG на время отладки
#else
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	{
		__HAL_RCC_CLEAR_RESET_FLAGS();
		/// NOTE: запустились после вылета по WatchDog, нужно что-то сделать
	}
#endif
	//settings_load();
}

void setup()
{
	ManagerDWT_Init();

	logger.info("%s\n", BUILD_TYPE_STR);
	logger.info("git:%s\n", GIT_REVISION_FULL);

}

void loop()
{
	logger.info("test swo");
	HAL_Delay(1000);

}

__INLINE void logger_out(__UNUSED const char* str, __UNUSED uint32_t len)
{
#ifdef PRINT_SWO
	printSWO("%.*s", (int)len, str);
#endif
}