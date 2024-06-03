#include <avr/io.h>
#include <util/twi.h>
#include "DS3231.h"

void I2C_Init(void) {
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = (1 << TWEN);
}

void I2C_Start(void) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_Read_Ack(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t I2C_Read_NAck(void) {
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void DS3231_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*second = I2C_Read_Ack();
	*minute = I2C_Read_Ack();
	*hour = I2C_Read_NAck();
	I2C_Stop();
}

void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x04);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*day = I2C_Read_Ack();
	*month = I2C_Read_Ack();
	*year = I2C_Read_NAck();
	I2C_Stop();
}