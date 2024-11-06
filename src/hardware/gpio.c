#include "hardware/gpio.h"

// Funciones asignadas para cada GPIO
static gpio_function_t _gpio_functions[40] = {0};


/**
 * @brief Asigna una funcion de las disponibles a un GPIO
 * @param gpio numero de GPIO para usar
 * @param func funcion a asignar dentro de las disponibles en gpio_function_t
 */
void gpio_set_function(uint32_t gpio, gpio_function_t func) {

	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetMovablePinSelect(SWM0, func, gpio);
	CLOCK_DisableClock(kCLOCK_Swm);

	// Guardo la funcion en el array
	_gpio_functions[gpio] = func;
}

/**
 * @brief Obtiene la funcion asociada a un GPIO
 * @return funcion configurada en el GPIO
 */
gpio_function_t gpio_get_function(uint32_t gpio) {
	return _gpio_functions[gpio];
}
