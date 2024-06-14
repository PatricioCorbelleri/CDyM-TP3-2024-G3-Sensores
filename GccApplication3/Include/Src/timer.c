#include "Timer.h"
#include <avr/interrupt.h>

volatile uint8_t Flag_TemHum = 0;
volatile uint8_t cont = 0;

void Timer1_Init(void) {
	// Configurar Timer1 en modo CTC
	TCCR1B |= (1 << WGM12); // Modo CTC
	
	// Establecer el valor de comparación para 2 segundos
	OCR1A = 62499; // 62499 cuentas para 2 segundos con prescaler 256 8 MHz
	
	//Ignorar
	//OCR1A = 31249; // 31249 cuentas para 2 segundos con prescaler 256 16 MHz
	
	// Habilitar la interrupción por comparación de salida A
	TIMSK1 |= (1 << OCIE1A);
	
	// Configurar el prescaler a 256 y arrancar el temporizador
	TCCR1B |= (1 << CS12); // CS12 = 1, CS11 = 0, CS10 = 0
}

// ISR para el evento de comparación del Timer1
ISR(TIMER1_COMPA_vect) {
	// para proteus: 1
	// para IRL: 2
	if (++cont == /*2*/1) {
		Flag_TemHum = 1;
		cont = 0;
	}
}
