#include "Timer.h"
#include <avr/interrupt.h>

volatile uint8_t Flag_TemHum = 0;

void Timer1_Init(void) {
	// Configurar Timer1 en modo CTC
	TCCR1B |= (1 << WGM12); // Modo CTC
	
	// Establecer el valor de comparación para 2 segundos
	OCR1A = 31250 - 1; // 31250 cuentas para 2 segundos con prescaler 1024
	
	// Habilitar la interrupción por comparación de salida A
	TIMSK1 |= (1 << OCIE1A);
	
	// Configurar el prescaler a 1024 y arrancar el temporizador
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

// ISR para el evento de comparación del Timer1
ISR(TIMER1_COMPA_vect) {
	Flag_TemHum = 1;
}
