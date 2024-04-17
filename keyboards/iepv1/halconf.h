#pragma once
#include_next <halconf.h>

#undef HAL_USE_PAL
#define HAL_USE_PAL                 TRUE

#undef HAL_USE_SERIAL 
#define HAL_USE_SERIAL TRUE

/* for split bitbang */
#undef PAL_USE_CALLBACKS
#define PAL_USE_CALLBACKS TRUE

#undef PAL_USE_WAIT
#define PAL_USE_WAIT TRUE


/* ws2812 */

