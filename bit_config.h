#ifndef BIT_CONFIG
#define BIT_CONFIG
	// utilizando o oscilador interno
	#pragma config FOSC = INTOSCCLK

	// não utilizaremos watchdog ainda
	#pragma config WDTE = OFF

	
	// desabilitando o power-up timer
	#pragma config PWRTE = OFF

	// habilitando master clear
	#pragma config MCLRE = ON

	// desabilitando brown-out
	#pragma config BOREN = OFF

	// o low-voltage é necessário
	#pragma config LVP = ON

	// desabilitando proteção dos dados da
	// memória
	#pragma config CPD = OFF

	// desabilitando a proteção da memória flash
	#pragma config CP = OFF
#endif