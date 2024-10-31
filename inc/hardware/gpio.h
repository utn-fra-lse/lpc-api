#ifndef _LSE_GPIO_H_
#define _LSE_GPIO_H_

#ifdef __LPC84X__
#include "lpc845/LPC845.h"
#include "lpc845/fsl_gpio.h"
#endif

// Macro para obtener el puerto de un pin determinado
#define PIN_TO_PORT(pin)	(pin > 31)? 1 : 0

/**
 * @brief Inicializa el puerto para el GPIO elegido
 * @param pin numero de pin a usar
 */
static inline void gpio_init(uint32_t pin) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(pin);
	// Inicializo el puerto
	GPIO_PortInit(GPIO, port);
}

/**
 * @brief Configura una direccion para el pin
 * @param pin numero de pin a configurar
 * @param direction true para salida, false para entrada
 */
static inline void gpio_set_dir(uint32_t pin, bool direction) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(pin);
	// Inicializa la direccion del pin
	if(direction) { GPIO->DIR[port] |= (1UL << pin); }
	else { GPIO->DIR[port] &= ~(1UL << pin); }
}

/**
 * @brief Escribe un valor en una salida
 * @param pin numero de pin a escribir
 * @param output valor para escribir
 */
static inline void gpio_put(uint32_t pin, bool output) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(pin);
	// Configura valor de salida
	GPIO_PinWrite(GPIO, port, pin, output);
}

/**
 * @brief Lee el valor de un pin
 * @param pin numero de pin a leer
 * @return estado del pin
 */
static inline bool gpio_get(uint32_t pin) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(pin);
	// Configura valor de salida
	return (bool)GPIO_PinRead(GPIO, port, pin);
}

#endif
