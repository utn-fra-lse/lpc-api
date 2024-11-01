#ifndef _LSE_ADC_H_
#define _LSE_ADC_H_

#ifdef __LPC84X__
#include "lpc845/fsl_adc.h"
#include "lpc845/fsl_swm.h"
#include "lpc845/fsl_power.h"
#endif

// Prototipos

void adc_init(void);
void adc_gpio_init(uint32_t gpio);
void adc_seqa_select_input(uint32_t input);
void adc_seqb_select_input(uint32_t input);
uint32_t adc_seqa_get_selected_input(void);
uint32_t adc_seqb_get_selected_input(void);
uint16_t adc_seqa_read(void);
uint16_t adc_seqb_read(void);

/**
 * @brief Selecciona una entrada para leer en el ADC
 * @param input canal para leer
 */
static inline void adc_select_input(uint32_t input) { adc_seqa_select_input(input); }

/**
 * @brief Obtiene la entrada seleccionada para el ADC
 * @return entrada elegida
 */
static inline uint32_t adc_get_selected_input(void) { return adc_seqa_get_selected_input(); }

/**
 * @brief Hace una lectura por polling del ADC
 * @return valor del canal elegido del ADC
 */
static inline uint16_t adc_read(void) { return adc_seqa_read(); }

#endif
