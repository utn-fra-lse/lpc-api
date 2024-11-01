#include "hardware/adc.h"

/**
 * @brief Inicializa el ADC
 */
void adc_init(void) {
    // Elijo clock desde el FRO con divisor de 1
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);
    // Prendo el ADC
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
    // Obtengo frecuencia deseada y calibro ADC
	uint32_t frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
	ADC_DoSelfCalibration(ADC0, frequency);
	// Configuracion por defecto del ADC (Synchronous Mode, Clk Divider 1, Low Power Mode true, High Voltage Range)
	adc_config_t adc_config;
	ADC_GetDefaultConfig(&adc_config);
    // Habilito el ADC
	ADC_Init(ADC0, &adc_config);
}

/**
 * @brief Habilita la funcion analogica en un gpio
 * @param gpio es el numero de gpio a usar
 */
void adc_gpio_init(uint32_t gpio) {
    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del elegido
    uint32_t channel_to_gpio[] = {
		0, 0, 0, 0,
		kSWM_ADC_CHN11, 0, kSWM_ADC_CHN1, kSWM_ADC_CHN0, 0, 0, 0, 0, 0,
		kSWM_ADC_CHN10, kSWM_ADC_CHN2, 0, 0, kSWM_ADC_CHN9, kSWM_ADC_CHN8,
		kSWM_ADC_CHN7, kSWM_ADC_CHN6, kSWM_ADC_CHN5, kSWM_ADC_CHN4, kSWM_ADC_CHN3
    };
    SWM_SetFixedPinSelect(SWM0, channel_to_gpio[gpio], true);
    // Desactivo clock de matriz de conmutacion
    CLOCK_DisableClock(kCLOCK_Swm);
}

/**
 * @brief Elige un unico canal del ADC para leer con la secuencia A
 * @param input canal del ADC para leer
 */
void adc_seqa_select_input(uint32_t input) {
	// Deshabilito la sequencia A
	ADC_EnableConvSeqA(ADC0, false);
	// Configuracion para las conversiones
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << input,								// Elijo el canal
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachConversion		// Interrupciones para cada conversion
	};
	// Configuro y habilito secuencia A
	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
	ADC_EnableConvSeqA(ADC0, true);
}

/**
 * @brief Elige un unico canal del ADC para leer con la secuencia B
 * @param input canal del ADC para leer
 */
void adc_seqb_select_input(uint32_t input) {
	// Deshabilito la sequencia A
	ADC_EnableConvSeqB(ADC0, false);
	// Configuracion para las conversiones
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << input,								// Elijo el canal
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachConversion		// Interrupciones para cada conversion
	};
	// Configuro y habilito secuencia A
	ADC_SetConvSeqBConfig(ADC0, &adc_sequence);
	ADC_EnableConvSeqB(ADC0, true);
}

/**
 * @brief Obtiene el canal seleccionado desde la mascara de canales
 * @param channels canales seleccionados en una secuencia
 * @return canal elegido
 */
static uint32_t _adc_get_selected_input(uint32_t channels) {
	// Canal seleccionado
	uint32_t selected_channel = 0;
	// Lo corro un bit a la izquierda
	while(channels != 0x01) {
		// Corro un bit
		channels >>= 1;
		// Incremento en uno el canal
		selected_channel++;
	}
	// Retorno el canal elegido
	return selected_channel;
}

/**
 * @brief Obtiene el canal seleccionado para la secuencia A
 * @return canal elegido
 */
uint32_t adc_seqa_get_selected_input(void) {
	// Obtengo el canal a partir del registro de control
	return _adc_get_selected_input(ADC0->SEQ_CTRL[0] & ADC_SEQ_CTRL_CHANNELS_MASK);
}

/**
 * @brief Obtiene el canal seleccionado para la secuencia B
 * @return canal elegido
 */
uint32_t adc_seqb_get_selected_input(void) {
	// Obtengo el canal a partir del registro de control
	return _adc_get_selected_input(ADC0->SEQ_CTRL[1] & ADC_SEQ_CTRL_CHANNELS_MASK);
}

/**
 * @brief Lee el valo analogico por poling en un canal
 * @param channel canal para leer
 * @return valor del canal
 */
static uint16_t _adc_read(uint32_t channel) {
	// Resultado de conversion
	adc_result_info_t adc_info;
	// Espero a terminar la conversion
	while(!ADC_GetChannelConversionResult(ADC0, channel, &adc_info));
	// Devuelvo resultado
	return adc_info.result;
}

/**
 * @brief Lee el canal seleccionado en la secuencia A
 * @return valor del canal
 */
uint16_t adc_seqa_read(void) {
	// Inicio conversion
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
	// Espero y leo
	return _adc_read(adc_seqa_get_selected_input());
}

/**
 * @brief Lee el canal seleccionado en la secuencia B
 * @return valor del canal
 */
uint16_t adc_seqb_read(void) {
	// Inicio conversion
	ADC_DoSoftwareTriggerConvSeqB(ADC0);
	// Espero y leo
	return _adc_read(adc_seqa_get_selected_input());
}
