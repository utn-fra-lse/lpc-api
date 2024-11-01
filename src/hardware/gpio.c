#include "hardware/gpio.h"

/**
 * @brief Asigna una funcion de las disponibles a un gpio
 * @param gpio numero de gpio para usar
 * @param func funcion a asignar dentro de las disponibles en gpio_function_t
 */
void gpio_set_function(uint32_t gpio, gpio_function_t func) {

	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetMovablePinSelect(SWM0, func, gpio);
	CLOCK_DisableClock(kCLOCK_Swm);
}
