#include <TempHumReg.h>
#include <DHT11.h>
#include <DS3231.h>
#include <SerialPort.h>
#include <stdio.h>

<<<<<<< HEAD
extern volatile uint8_t Flag_SendData;
extern char msg1[];
extern char msg2[];

void Task_TemHum(void) {
	uint8_t temperature_1 = 0;
	uint8_t temperature_2 = 0;
	uint8_t humidity_1 = 0;
	uint8_t humidity_2 = 0;

	if (DHT11_Read(&temperature_1, &temperature_2, &humidity_1, &humidity_2) == 0) {
		
=======
extern volatile uint8_t Flag_SendData = 0;
extern char msg2[];

void Task_TemHum(void) {
	int temperature_1 = 0;
	int temperature_2 = 0;
	int humidity_1 = 0;
	int humidity_2 = 0;

	if (DHT11_Read(&temperature_1, &temperature_2, &humidity_1, &humidity_2) == 0) {
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22
		char buffer[100];
		uint8_t hour, minute, second, day, month, year;
		DS3231_GetTime(&hour, &minute, &second);
		DS3231_GetDate(&day, &month, &year);

		snprintf(buffer, sizeof(buffer),
<<<<<<< HEAD
		"\r\nTEMP: %d.%d C HUM: %d.%d%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
		temperature_1, temperature_2, humidity_1, humidity_2,
		day, month, year, hour, minute, second);

// 		snprintf(buffer, sizeof(buffer),
// 		"\r\ntemperatura_1: %d\r\ntemperatura_2: %d\r\nhumidity_1: %d\r\nhumidity_2: %d\r\n\r\n",
// 		temperature_1, temperature_2, humidity_1, humidity_2);
=======
		"TEMP: %d.%d°C HUM: %d.%d%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
		temperature_1, temperature_2, humidity_1, humidity_2,
		day, month, year, hour, minute, second);
>>>>>>> 84b9747c9fd520650ce82ea90db77b7c42fe6d22

		if (Flag_SendData) {
// 			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
// 			SerialPort_Send_String("\r\nimpresion\r\n");
			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
			SerialPort_Send_String(buffer);
		}
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
	
// 	if (RX_Buffer == 'a' || RX_Buffer == 'A') {
// 		if (!Flag_SendData) {
// 			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
// 			SerialPort_Send_String("agus\r\n");
// 		}
// 	}
// 	
// 	if (RX_Buffer == 'p' || RX_Buffer == 'P') {
// 		if (!Flag_SendData) {
// 			SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
// 			SerialPort_Send_String("pato\r\n");
// 		}
// 	}
}
