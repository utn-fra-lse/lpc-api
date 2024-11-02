#include "hardware/dac.h"

static void _dac_init(DAC_Type *dac, pd_bit_t power_dac) {
    // Prendo el DAC
	POWER_DisablePD(power_dac);
	// Configuro por defecto el DAC
	dac_config_t dac_config;
	DAC_GetDefaultConfig(&dac_config);
	DAC_Init(dac, &dac_config);
}

void dac_gpio_init(uint32_t gpio) {
	// Veo que DAC es el que tengo que habilitar
	DAC_Type *dac;
	swm_select_fixed_pin_t dac_out;
	pd_bit_t power_dac;
	uint8_t pio_number;

    if(gpio == 17) {
    	dac = DAC0;
    	dac_out = kSWM_DAC_OUT0;
    	power_dac = kPDRUNCFG_PD_DAC0;
    	pio_number = IOCON_INDEX_PIO0_17;
    }
    else if(gpio == 29) {
    	dac = DAC1;
    	dac_out = kSWM_DAC_OUT1;
    	power_dac = kPDRUNCFG_PD_DAC1;
    	pio_number = IOCON_INDEX_PIO0_29;
    }
    // Configuro el periferico
    _dac_init(dac, power_dac);
    // Configuro la salida del DAC en el SWM
	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetFixedPinSelect(SWM0, dac_out, true);
	CLOCK_DisableClock(kCLOCK_Swm);
    // Habilito la funcion de DAC en el IOCON
	CLOCK_EnableClock(kCLOCK_Iocon);
	IOCON_PinMuxSet(IOCON, pio_number, IOCON_PIO_DACMODE_MASK);
	CLOCK_DisableClock(kCLOCK_Iocon);
}
