#include "settings.h"
#include "stm32f3xx_hal.h"
#include "build_info.h"

SETTINGS_t settings;

void settings_load(void)
{
	/// указатель на структуру настроек
	uint32_t* ptr = (uint32_t*)&settings;
	//NOTE: размер страницы 2 килобайта
	/// копируем данные из флеша в структуру по 4 байта (32 бита) (выравненное по 4 байта!)
	for (uint32_t i = 0; i < (sizeof(SETTINGS_t) / sizeof(uint32_t)); i++)
		ptr[i] = *(uint32_t*)(SETT_ORIGIN + i * sizeof(uint32_t));
}

void settings_save(void)
{
	//Настройки стирания Flash
	FLASH_EraseInitTypeDef flash_settings =
	{
		.NbPages = (SETT_SIZE_KB * BYTES_IN_KBYTE) / FLASH_PAGE_SIZE,	//Число страниц для стирания
		.PageAddress = SETT_ORIGIN,					//Начальный адрес для стирания
		.TypeErase = FLASH_TYPEERASE_PAGES			//Стираем постранично
	};

	//Сюда кладем ошибку от стирания если она есть
	uint32_t error = 0;

	//Ахтунг: Flash разблокирована
	HAL_FLASH_Unlock();
	{
		HAL_FLASHEx_Erase(&flash_settings, &error); //Стираем память
		//TODO: нужно как-то обработать ошибку стирания
		uint64_t* WriteThisToFlash = (uint64_t*)&settings;
		for (uint32_t i = 0; i < (sizeof(SETTINGS_t) / sizeof(uint64_t)); i++)
		{
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
							  SETT_ORIGIN + i * sizeof(uint64_t),
							  WriteThisToFlash[i]);
		}
	}
	HAL_FLASH_Lock();
}