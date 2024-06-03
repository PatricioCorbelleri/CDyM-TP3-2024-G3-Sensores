#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define DHT11_PIN PORTC0

void DHT11_Init(void) {
	DDRC |= (1 << DHT11_PIN);
	PORTC |= (1 << DHT11_PIN);
}

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity) {
	uint8_t bits[5];
	uint8_t i, j = 0;

	// Reset port
	PORTC &= ~(1 << DHT11_PIN);
	_delay_ms(18);
	PORTC |= (1 << DHT11_PIN);
	_delay_us(20);
	DDRC &= ~(1 << DHT11_PIN);

	_delay_us(40);
	if (PINC & (1 << DHT11_PIN)) return 1;
	_delay_us(80);
	if (!(PINC & (1 << DHT11_PIN))) return 1;

	_delay_us(80);

	// Read 5 bytes
	for (j = 0; j < 5; j++) {
		uint8_t result = 0;
		for (i = 0; i < 8; i++) {
			while (!(PINC & (1 << DHT11_PIN)));
			_delay_us(30);
			if (PINC & (1 << DHT11_PIN)) result |= (1 << (7 - i));
			while (PINC & (1 << DHT11_PIN));
		}
		bits[j] = result;
	}

	DDRC |= (1 << DHT11_PIN); // Set as output
	PORTC |= (1 << DHT11_PIN); // Pull high

	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) return 1;

	*humidity = bits[0];
	*temperature = bits[2];
	return 0;
}