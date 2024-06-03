#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define DHT11_PIN PORTC0
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN_INPUT PINC

void DHT11_Init(void) {
	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida
	DHT11_PORT |= (1 << DHT11_PIN); // Establece el pin en alto
}

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity) {
	uint8_t bits[5];
	uint8_t i, j = 0;

	// Reset port
	DHT11_PORT &= ~(1 << DHT11_PIN); // Lleva el pin a bajo
	_delay_ms(18); // Mantén bajo por al menos 18 ms
	DHT11_PORT |= (1 << DHT11_PIN); // Lleva el pin a alto
	_delay_us(20); // Espera 20 us
	DHT11_DDR &= ~(1 << DHT11_PIN); // Configura el pin como entrada

	// Siempre retorna 1

	_delay_us(40);
	if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
		return 1; // Error: no se detectó respuesta del DHT11
	}
	_delay_us(80);
	if (!(DHT11_PIN_INPUT & (1 << DHT11_PIN))) {
		return 1; // Error: no se detectó el bit de inicio del DHT11
	}

	_delay_us(80);
	
	// while(1); Lo deje andando 4 minutos y medio y nunca llega aca

	// Leer 5 bytes (40 bits)
	for (j = 0; j < 5; j++) {
		uint8_t result = 0;
		for (i = 0; i < 8; i++) {
			while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN))); // Espera a que el pin se ponga alto
			_delay_us(30);
			if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
				result |= (1 << (7 - i));
			}
			while (DHT11_PIN_INPUT & (1 << DHT11_PIN)); // Espera a que el pin se ponga bajo
		}
		bits[j] = result;
	}

	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida
	DHT11_PORT |= (1 << DHT11_PIN); // Lleva el pin a alto

	// Verificación de la suma de comprobación
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
		return 1; // Error: la suma de comprobación no coincide
	}

	*humidity = bits[0];
	*temperature = bits[2];
	return 0; // Lectura exitosa
}
