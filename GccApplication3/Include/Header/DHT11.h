#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

void DHT11_Init(void);
uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity);

#endif /* DHT11_H_ */