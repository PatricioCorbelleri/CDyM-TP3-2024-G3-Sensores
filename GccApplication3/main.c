/*
 * GccApplication3.c
 *
 * Created: 02/06/2024 15:52:25
 * Author : agusr
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>
#include <SerialPort.h>
#include <DHT11.h>
#include <DS3231.h>
#include <TempHumReg.h>

volatile uint8_t Flag_SendData = 0;
char msg2[] = "Data sending stopped.\r\n";

int main(void)
{
    // Inicializacion
	
	// Inicialización de los módulos
	SerialPort_Init(103); // 9600 bps con un reloj de 16MHz
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();
	
	// Inicialización del Timer1
	Timer1_Init();
	
	// inicializacion de dht11 y ds3231
	DHT11_Init();
	I2C_Init();	
	
	sei();
	
    while (1) {
	    
		if (Flag_TemHum) {
		    Task_TemHum();
		    Flag_TemHum = 0;
		}
    }
	
	
	return 0;
}

