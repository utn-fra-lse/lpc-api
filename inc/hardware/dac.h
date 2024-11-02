#ifndef _LSE_DAC_H_
#define _LSE_DAC_H_

#ifdef __LPC84X__
#include "lpc845/fsl_dac.h"
#include "lpc845/fsl_power.h"
#include "lpc845/fsl_swm.h"
#include "lpc845/fsl_iocon.h"

#define dac_inst_t	DAC_Type
#endif

// Prototipos

/**
 * @brief Habilita la salida de dac en un gpio
 * @param gpio numero de gpio a usar
 */
void dac_gpio_init(uint32_t gpio);

/**
 * @brief Obtiene la salida de dac para un gpio
 * @param gpio numero de gpio a usar
 * @return puntero a salida de dac
 */
static inline dac_inst_t* dac_gpio_to_output(uint32_t gpio) {

	if(gpio == 17) { return DAC0; }
	else if(gpio == 29) { return DAC1; }
	return NULL;
}

/**
 * @brief Actualiza la salida de dac en un gpio
 * @param gpio numero de gpio a usar
 * @param output valor de salida
 */
static inline void dac_gpio_set_level(uint32_t gpio, uint16_t output) {

	DAC_SetBufferValue(dac_gpio_to_output(gpio), output & 0x3ff);
}

#endif
