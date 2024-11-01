#ifndef _I2C_H_
#define _I2C_H_

#ifdef __LPC84X__
#include "lpc845/fsl_i2c.h"
#include "lpc845/fsl_power.h"
#include "lpc845/fsl_swm.h"

#define i2c0            I2C0
#define i2c1            I2C1
#define i2c_inst_t      I2C_Type
#endif

void i2c_init(i2c_inst_t *i2c, uint32_t baudrate);
int32_t i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop);
int32_t i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop);

#endif
