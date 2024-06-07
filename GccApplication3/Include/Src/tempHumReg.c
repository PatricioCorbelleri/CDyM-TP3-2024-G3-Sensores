#include <TempHumReg.h>
#include <DHT11.h>
#include <DS3231.h>
#include <SerialPort.h>
#include <stdio.h>

extern volatile uint8_t Flag_SendData;
extern char msg2[];

void Task_TemHum(void) {
	float temperature = 0;
	float humidity = 0;

	if (DHT11_Read(&temperature, &humidity) == 0) {
		char buffer[100];
		uint8_t hour, minute, second, day, month, year;
		DS3231_GetTime(&hour, &minute, &second);
		DS3231_GetDate(&day, &month, &year);

		snprintf(buffer, sizeof(buffer),
		"TEMP: %f°C HUM: %f%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
		temperature, humidity, day, month, year, hour, minute, second);

		if (Flag_SendData) {
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
			SerialPort_Send_String(msg2);
		}
	}
}
