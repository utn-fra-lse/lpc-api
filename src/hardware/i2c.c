#include "hardware/i2c.h"

void i2c_init(i2c_inst_t *i2c, uint32_t baudrate) {
	// Elijo clock para I2C que corresponda
	clock_select_t clock;
	if(i2c == I2C0) { clock = kI2C0_Clk_From_MainClk; }
	else if(i2c == I2C1) { clock = kI2C1_Clk_From_MainClk; }
	else if(i2c == I2C2) { clock = kI2C2_Clk_From_MainClk; }
	else if(i2c == I2C3) { clock = kI2C3_Clk_From_MainClk; }
	// Inicializo clock
	CLOCK_Select(clock);
    // Configuracion de master para el I2C con 400 KHz de clock
    i2c_master_config_t config;
    I2C_MasterGetDefaultConfig(&config);
    config.baudRate_Bps = baudrate;
    // Usa el clock del sistema de base para generar el de la comunicacion
    I2C_MasterInit(i2c, &config, SystemCoreClock);
}

int32_t i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop) {
	// Arranca la comunicacion
	if(I2C_MasterStart(i2c, addr, kI2C_Write) == kStatus_Success) {
		I2C_MasterWriteBlocking(i2c, src, len, kI2C_TransferDefaultFlag);
		// Depende del booleano
		if(!nostop) { I2C_MasterStop(i2c); }
		return len;
	}
	return -1;
}

int32_t i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop) {
	// Arranca la comunicacion
	if(I2C_MasterStart(i2c, addr, kI2C_Read) == kStatus_Success) {
		I2C_MasterReadBlocking(i2c, dst, len, kI2C_TransferDefaultFlag);
		// Depende del booleano
		if(!nostop) { I2C_MasterStop(i2c); }
		return len;
	}
	return -1;
}
