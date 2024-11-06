#ifndef _LSE_PWM_H_
#define _LSE_PWM_H_

#ifdef __LPC84X__
#include "lpc845/fsl_sctimer.h"
#include "lpc845/fsl_swm.h"
#endif

#include "hardware/gpio.h"

// Prototipos

void pwm_config(uint32_t gpio, uint32_t freq);
void pwm_set_gpio_duty(uint32_t gpio, uint32_t duty);

/**
 * @brief Da inicio al Timer que usa el PWM
 */
static inline void pwm_init(void) { SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U); }

/**
 * @brief Detiene el Timer que usa el PWM
 */
static inline void pwm_deinit(void) { SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_U); }

#endif
