#include <avr/io.h>
#include <util/twi.h>
#include <DS3231.h>

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
	*second = bcd_to_dec(I2C_Read_Ack());
	*minute = bcd_to_dec(I2C_Read_Ack());
	*hour = bcd_to_dec(I2C_Read_NAck());
	I2C_Stop();
}

void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x04);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*day = bcd_to_dec(I2C_Read_Ack());
	*month = bcd_to_dec(I2C_Read_Ack());
	*year = bcd_to_dec(I2C_Read_NAck());
	I2C_Stop();
}

void DS3231_SetTime(uint8_t hour, uint8_t minute, uint8_t second) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00); // Dirección del registro de segundos
	I2C_Write(dec_to_bcd(second));
	I2C_Write(dec_to_bcd(minute));
	I2C_Write(dec_to_bcd(hour));
	I2C_Stop();
}

void DS3231_SetDate(uint8_t day, uint8_t month, uint8_t year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x04); // Dirección del registro del día
	I2C_Write(dec_to_bcd(day));
	I2C_Write(dec_to_bcd(month));
	I2C_Write(dec_to_bcd(year));
	I2C_Stop();
}

uint8_t dec_to_bcd(uint8_t dec) {
	return ((dec / 10 * 16) + (dec % 10));
}

uint8_t bcd_to_dec(uint8_t bcd) {
	return ((bcd / 16) * 10) + (bcd % 16);
}
