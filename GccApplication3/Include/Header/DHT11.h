#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

void DHT11_Init(void);
uint8_t DHT11_Read(uint8_t *temperature_1, uint8_t *temperature_2, uint8_t *humidity_1, uint8_t *humidity_2);

#endif /* DHT11_H_ */