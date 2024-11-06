#include "hardware/pwm.h"

// Cuatro eventos para los canales
static uint32_t events[4] = {0};

/**
 * @brief Configura una salida de PWM
 * @param gpio numero de GPIO para configurar la salida
 * @param freq frecuencia para el PWM
 */
void pwm_config(uint32_t gpio, uint32_t freq) {
    // Eligo el clock para el Timer
    uint32_t sctimer_clock = CLOCK_GetFreq(kCLOCK_Fro);
    // Configuracion del SCT Timer
    sctimer_config_t sctimer_config;
    SCTIMER_GetDefaultConfig(&sctimer_config);
    SCTIMER_Init(SCT0, &sctimer_config);

    // Veo la salida asociada al GPIO
    uint32_t output = gpio_get_function(gpio) - kSWM_SCT_OUT0;
    // Configuro el PWM
    sctimer_pwm_signal_param_t config = {
		.output = output,				// Salida del Timer
		.level = kSCTIMER_HighTrue,		// Logica positiva
		.dutyCyclePercent = 0			// Salida apagada
    };

    // Inicializo el PWM
    SCTIMER_SetupPwm(
		SCT0,
		&config,
		kSCTIMER_CenterAlignedPwm,
		freq,
		sctimer_clock,
		&events[output]
	);
}

/**
 * @brief Configura el duty de una salida de PWM
 * @param gpio numero de GPIO configurado como salida de PWM
 * @param duty porcentaje de ancho de pulso (0 a 100)
 */
void pwm_set_gpio_duty(uint32_t gpio, uint32_t duty) {
    // Canal de salida
    uint32_t output = gpio_get_function(gpio) - kSWM_SCT_OUT0;
	// Actualizo el ciclo de trabajo
	SCTIMER_UpdatePwmDutycycle(SCT0, output, duty, events[output]);
}
