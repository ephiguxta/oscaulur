#ifndef BIT_CONFIG
#define BIT_CONFIG
	// utilizando o oscilador interno
	#pragma config FOSC = INTOSCCLK

	// utilizando o WDT
	#pragma config WDTE = ON

	// estabilizando a inicialização
	#pragma config PWRTE = ON

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
