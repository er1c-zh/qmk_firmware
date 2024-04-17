#pragma once
#include_next <mcuconf.h>

/* ws2812 */

/* split */
#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE