# Основные настройки проекта
set(PRJ_NAME        "EXAMP_01") # название приложения
set(BTL_VERSION     "0.0.0") # версия загрузчика
set(APP_VERSION     "0.1.0") # версия приложения
set(MCU_BOARD           "B") # код МК на плате: A, B, C, D ....
set(BOARD_REV           "A") # ревизия платы: A, B, C, D ....

set(MCU_FLASH_KB           "64") # сколько кб флеша доступно
set(MCU_RAM_KB              "20") # сколько кб оперативной памяти доступно

set(MCU_FLASH_ORIGIN "0x8000000") # начальный адрес флеша, менять не нужно!
set(MCU_RAM_ORIGIN   "0x20000000") # начальный адрес оперативной памяти, менять не нужно!

set(BOOT_SIZE_KB 		 "24") 
set(SETT_SIZE_KB    	 "0") 
math(EXPR APPL_SIZE_KB   "${MCU_FLASH_KB} - (${BOOT_SIZE_KB} + ${SETT_SIZE_KB})") # сектора 4-7

# Расчёт всех адресов
math(EXPR BOOT_ORIGIN "${MCU_FLASH_ORIGIN}" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR APPL_ORIGIN "${BOOT_ORIGIN} + ${BOOT_SIZE_KB} * 1024" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR SETT_ORIGIN "${APPL_ORIGIN} + ${APPL_SIZE_KB} * 1024" OUTPUT_FORMAT HEXADECIMAL)

# Выводим расчитанные данные для отладки
message(STATUS "Name: ${PRJ_NAME}_${MCU_BOARD}")
message(STATUS "Memory map:
    - Bootloader    [Boot]  size is  ${BOOT_SIZE_KB} kb (origin ${BOOT_ORIGIN})
    - Application   [App]   size is ${APPL_SIZE_KB} kb (origin ${APPL_ORIGIN})
    - Settings              size is  ${SETT_SIZE_KB} kb (origin ${SETT_ORIGIN})")
