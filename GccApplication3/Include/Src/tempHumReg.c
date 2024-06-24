#include <TempHumReg.h>
#include <DHT11.h>
#include <DS3231.h>
#include <SerialPort.h>
#include <stdio.h>
#include <string.h>

extern volatile uint8_t Flag_SendData;
extern char msg1[];
extern char msg2[];
volatile char buffer[100];
volatile uint8_t i = 0;
extern volatile uint8_t Flag_String;

void Task_TemHum(void) {
	uint8_t temperature_1 = 0;
	uint8_t temperature_2 = 0;
	uint8_t humidity_1 = 0;
	uint8_t humidity_2 = 0;

	if (DHT11_Read(&temperature_1, &temperature_2, &humidity_1, &humidity_2) == 0) {
		
		uint8_t hour, minute, second, day, month, year;
		DS3231_GetTime(&hour, &minute, &second);
		DS3231_GetDate(&day, &month, &year);

		snprintf(buffer, sizeof(buffer),
		"\r\nTEMP: %d.%d C HUM: %d.%d%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
		temperature_1, temperature_2, humidity_1, humidity_2,
		day, month, year, hour, minute, second);

		Flag_String = 1;
	}
}

ISR(USART_RX_vect) {
	static volatile uint8_t RX_Buffer = 0;
	RX_Buffer = UDR0; // Read received data

	if (RX_Buffer == 's' || RX_Buffer == 'S') {
		Flag_SendData = !Flag_SendData; // Toggle data sending
		if (!Flag_SendData) {
			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
			SerialPort_Send_String(msg1);
		} else {
			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
			SerialPort_Send_String(msg2);
		}
	}
}

ISR(USART_UDRE_vect){
	
	if (buffer[i]){ // Si sigue habiendo datos
		SerialPort_Send_Data(buffer[i]); // Enviar dato
		i++;
	}
	else {
		Flag_String = 0; // Termino de transmitir
		i = 0;
		memset(buffer, '\0', sizeof(buffer));
		SerialPort_TX_Interrupt_Disable(); // Deshabilitar interrupción de transmisión
	}
}
