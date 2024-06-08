#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

void DHT11_Init(void);
uint8_t DHT11_Read(int *temperature_1, int *temperature_2, int *humidity_1, int *humidity_2);

#endif /* DHT11_H_ */