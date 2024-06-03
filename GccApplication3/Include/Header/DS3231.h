#ifndef DS3231_H_
#define DS3231_H_

#include <avr/io.h>

// Definir la direccion del DS3231
#define DS3231_ADDRESS 0x68

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read_Ack(void);
uint8_t I2C_Read_NAck(void);

void DS3231_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year);

#endif /* DS3231_H_ */