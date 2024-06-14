#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

void DHT11_Init(void);
<<<<<<< HEAD
uint8_t DHT11_Read(uint8_t *temperature_1, uint8_t *temperature_2, uint8_t *humidity_1, uint8_t *humidity_2);
=======
uint8_t DHT11_Read(int *temperature_1, int *temperature_2, int *humidity_1, int *humidity_2);
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22

#endif /* DHT11_H_ */