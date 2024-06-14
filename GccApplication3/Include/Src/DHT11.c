<<<<<<< HEAD
// IRL
//#define F_CPU 16000000UL
//proteus
#define F_CPU 8000000UL

=======
#define F_CPU 8000000UL
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22
#include <util/delay.h>
#include <avr/io.h>
#include <SerialPort.h>

#define DHT11_PIN PORTC0
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN_INPUT PINC

void DHT11_Init(void) {
	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida
	DHT11_PORT |= (1 << DHT11_PIN); // Establece el pin en alto
}

<<<<<<< HEAD
uint8_t DHT11_Read(uint8_t *temperature_1, uint8_t *temperature_2, uint8_t *humidity_1, uint8_t *humidity_2) {
	uint8_t bits[5] = {0}; // Asegurarse de inicializar los bits a 0
	uint8_t i, j = 0;
	
	DHT11_DDR |= (1 << DHT11_PIN); // Configura el pin como salida

	// Enviar señal de inicio: Señal baja por 18 ms
	DHT11_PORT &= ~(1 << DHT11_PIN);
	_delay_ms(18);
	// MCU envía señal alta por 20-40 us para esperar que se prepare el DHT11
	DHT11_PORT |= (1 << DHT11_PIN);
	// Configura el pin como ENTRADA para LEER la respuesta del DHT11
	DHT11_DDR &= ~(1 << DHT11_PIN);
	
	// 	_delay_us(20);
	// 	//si alto
	// 	if ((DHT11_PIN_INPUT & (1 << DHT11_PIN))) {
	// 		_delay_us(21);
	// 		//si alto
	// 		if ((DHT11_PIN_INPUT & (1 << DHT11_PIN))) {
	// 			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
	// 			SerialPort_Send_String("\r\nERROR: DHT no respondio.\r\n");
	// 			return 1;
	// 		}
	// 	}
	
	//Esperar q se ponga en bajo (80 us)
	while ((DHT11_PIN_INPUT & (1 << DHT11_PIN)));
	
	//Esperar q se ponga en alto (80 us)
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));
	
	//Esperar q se ponga en bajo (50 us)
	while ((DHT11_PIN_INPUT & (1 << DHT11_PIN)));
	
=======
uint8_t DHT11_Read(int *temperature_1, int *temperature_2, int *humidity_1, int *humidity_2) {
	uint8_t bits[5] = {0}; // Asegurarse de inicializar los bits a 0
	uint8_t i, j = 0;

	// Enviar señal de inicio: Señal baja por 18 ms
	DHT11_PORT &= ~(1 << DHT11_PIN);
	_delay_ms(18);
	// MCU envía señal alta por 20-40 us para esperar que se prepare el DHT11
	DHT11_PORT |= (1 << DHT11_PIN);
	_delay_us(20);

	// Configura el pin como ENTRADA para LEER la respuesta del DHT11
	DHT11_DDR &= ~(1 << DHT11_PIN);
	
	// Espera a que el pin se ponga bajo (máximo 80 us)
	while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
	//_delay_us(80);

	// Espera a que el pin se ponga alto (máximo 80 us)
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));
	//_delay_us(80);

	// Espera a que el pin se ponga bajo nuevamente
	while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
	//_delay_us(50);

>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22
	// Lee los datos del DHT11
	for (j = 0; j < 5; j++) {
		//SerialPort_Send_String("\r\n\r\nJ\r\n");
		uint8_t result = 0;
		for (i = 0; i < 8; i++) {
<<<<<<< HEAD
			//SerialPort_Send_String("i ");
			
			//Esperar q se ponga en alto
			while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

			_delay_us(29); // Espera 40 us
=======
			// Espera a que el pin se ponga alto
			while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

			_delay_us(40); // Espera 40 us
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22

			// Si despues de 40 us esta:
			// -En alto: bit = 1
			// -En bajo: bit = 0
<<<<<<< HEAD
			
			//Si esta en alto
			if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
				result |= (1 << (7 - i)); // Establece el bit 'i' en 1
				//_delay_us(30);
				//Esperar q se ponga en bajo
				while ((DHT11_PIN_INPUT & (1 << DHT11_PIN)));
			}
			
=======
			// Como result se inicializa con todo en 0, no hace falta
			// especificar que se le esta asignando un 0 a la posicion i
			// Solo se asigna 1 cuando es necesario
			if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
				result |= (1 << (7 - i)); // Establece el bit 'i' en 1
			}

			// Espera a que el pin se ponga bajo
			while (DHT11_PIN_INPUT & (1 << DHT11_PIN));
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22
		}
		bits[j] = result;
	}
	
<<<<<<< HEAD
	//_delay_us(50);
	
	// Espera a que el pin se ponga alto
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));
=======
	// Espera a que el pin se ponga alto
	while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

	// Configura el pin como salida y lo establece en alto
	DHT11_DDR |= (1 << DHT11_PIN);
	DHT11_PORT |= (1 << DHT11_PIN);
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22

	// Verificación de la suma de comprobación
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
		//SerialPort_Send_String("Suma incorrecta\r\n");
		// Configura el pin como salida y lo establece en alto
		//DHT11_DDR |= (1 << DHT11_PIN);
		//DHT11_PORT |= (1 << DHT11_PIN);
		return 1; // Error: la suma de comprobación no coincide
	}
	
	*humidity_1 = bits[0];
	*humidity_2 = bits[1];
	*temperature_1 = bits[2];
	*temperature_2 = bits[3];
<<<<<<< HEAD
	
	//SerialPort_Send_String("Suma correcta\r\n");
	return 0; // Lectura exitosa uwu
}
=======

	return 0; // Lectura exitosa uwu
}
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22
