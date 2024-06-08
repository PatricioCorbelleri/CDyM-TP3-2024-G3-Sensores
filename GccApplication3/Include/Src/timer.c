#include "Timer.h"
#include <avr/interrupt.h>

volatile uint8_t Flag_TemHum = 0;

// void Timer1_Init(void) {
// 	// Configurar Timer1 en modo CTC
// 	TCCR1B |= (1 << WGM12); // Modo CTC
// 	
// 	// Establecer el valor de comparación para 2 segundos
// 	OCR1A = 15625 - 1; // 15624 cuentas para 2 segundos con prescaler 1024 y 8 MHz
// 	
// 	// Habilitar la interrupción por comparación de salida A
// 	TIMSK1 |= (1 << OCIE1A);
// 	
// 	// Configurar el prescaler a 1024 y arrancar el temporizador
// 	TCCR1B |= (1 << CS12) | (1 << CS10);
// }

//Creo que tarda lo mismo usando 256 y 1024
void Timer1_Init(void) {
	// Configurar Timer1 en modo CTC
	TCCR1B |= (1 << WGM12); // Modo CTC
	
	// Establecer el valor de comparación para 2 segundos
	OCR1A = 62499; // 62499 cuentas para 2 segundos con prescaler 256
	
	// Habilitar la interrupción por comparación de salida A
	TIMSK1 |= (1 << OCIE1A);
	
	// Configurar el prescaler a 256 y arrancar el temporizador
	TCCR1B |= (1 << CS12); // CS12 = 1, CS11 = 0, CS10 = 0
}
// ISR para el evento de comparación del Timer1
ISR(TIMER1_COMPA_vect) {
	Flag_TemHum = 1;
}
