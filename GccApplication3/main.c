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

volatile uint8_t Flag_SendData = 1;
char msg1[] = "\r\nPaused\r\n";
char msg2[] = "\r\nResumed\r\n";

int main(void)
{
    // Inicializacion
	
	//Para proteus
	//Si pongo '0x51' no funciona en proteus xd, por eso pusimos solo '51'
	SerialPort_Init(51); // 9600 bps con un reloj de 16MHz
	// Para IRL
	//SerialPort_Init(0x68); // 9600 bps con un reloj de 8MHz.
	
	SerialPort_TX_Enable();
	SerialPort_RX_Enable();
	SerialPort_RX_Interrupt_Enable();
	
	// Inicialización del Timer1
	Timer1_Init();
	
	// inicializacion de dht11 y ds3231
	DHT11_Init();
	I2C_Init();	
	
	sei();
	
	DS3231_SetTime(18, 39, 00); // configurar la hora (H,M,S)
	DS3231_SetDate(14, 6, 24); // configurar la fecha (D,M,A)
	
	SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
	SerialPort_Send_String("Inicializacion lista.\r\n");
	
    while (1) {
	    
		if (Flag_TemHum) {
			
			//SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
			//SerialPort_Send_String("Flag_TemHum = 1\r\n");
			
		    Task_TemHum();
		    Flag_TemHum = 0;
			
			//SerialPort_Wait_For_TX_Buffer_Free(); //9600bps formato 8N1, 10bits, 10.Tbit=10/9600=1ms
			//SerialPort_Send_String("Flag_TemHum = 0\r\n");
			
		}
    }
	
	
	return 0;
}

