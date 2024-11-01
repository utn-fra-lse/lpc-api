#ifndef _LSE_GPIO_H_
#define _LSE_GPIO_H_

#ifdef __LPC84X__
#include "lpc845/LPC845.h"
#include "lpc845/fsl_gpio.h"
#include "lpc845/fsl_swm.h"

// Macro para obtener el puerto de un pin determinado
#define PIN_TO_PORT(pin)	(pin > 31)? 1 : 0
// Macro para redefinir el nombre de las funciones de swm
#define gpio_function_t			swm_select_movable_t

// Redefiniciones de los nombres de las funciones

#define GPIO_FUNC_I2C1_SDA		kSWM_I2C1_SDA
#define GPIO_FUNC_I2C1_SCL		kSWM_I2C1_SCL
#define GPIO_FUNC_I2C2_SDA		kSWM_I2C2_SDA
#define GPIO_FUNC_I2C2_SCL		kSWM_I2C2_SCL
#define GPIO_FUNC_I2C3_SDA		kSWM_I2C3_SDA
#define GPIO_FUNC_I2C3_SCL		kSWM_I2C3_SCL

#endif

// Prototipos

void gpio_set_function(uint32_t gpio, gpio_function_t func);

/**
 * @brief Inicializa el puerto para el GPIO elegido
 * @param gpio numero de gpio a usar
 */
static inline void gpio_init(uint32_t gpio) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Inicializo el puerto
	GPIO_PortInit(GPIO, port);
}

/**
 * @brief Configura una direccion para el gpio
 * @param gpio numero de gpio a configurar
 * @param direction true para salida, false para entrada
 */
static inline void gpio_set_dir(uint32_t gpio, bool direction) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Inicializa la direccion del gpio
	if(direction) { GPIO->DIR[port] |= (1UL << gpio); }
	else { GPIO->DIR[port] &= ~(1UL << gpio); }
}

/**
 * @brief Escribe un valor en una salida
 * @param gpio numero de gpio a escribir
 * @param output valor para escribir
 */
static inline void gpio_put(uint32_t gpio, bool output) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Configura valor de salida
	GPIO_PinWrite(GPIO, port, gpio, output);
}

/**
 * @brief Lee el valor de un gpio
 * @param gpio numero de gpio a leer
 * @return estado del gpio
 */
static inline bool gpio_get(uint32_t gpio) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Configura valor de salida
	return (bool)GPIO_PinRead(GPIO, port, gpio);
}

#endif
