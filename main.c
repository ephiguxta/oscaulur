#include <xc.h>
#include <pic16f628a.h>
#include <stdint.h>
#include <math.h>

#include "bit_config.h"

#define _XTAL_FREQ 4000000

uint16_t centimeters(uint16_t length);

int main(void){
	// habilitando o led vermelho
	TRISB = 0x00;

	// desligando os comparadores
	// datasheet: pág 64 - fig 10.1
	CMCONbits.CM = 0x7;

	// pinos do sensor ultrassônico
	// trisa0: echo
	// trisa1: trig
	TRISA = 0x02;

	// prescaler 1:1
	// datasheet: pág 50 - reg 7.1
	T1CONbits.T1CKPS = 0x0;
	// clock interno: (fosc/4)
	T1CONbits.TMR1CS = 0;

	uint16_t length = 0;

	while(1){
		TMR1H = 0;
		TMR1L = 0;

		length = centimeters(length);

		if(length >= 10 && length <= 30) {
			PORTBbits.RB0 = 1;
			__delay_ms(25);

		} else {
			PORTBbits.RB0 = 0;
		}
	}

	return 0;
}

uint16_t centimeters(uint16_t length) {
	// envia um pulso de 10us para o trigger
	PORTAbits.RA0 = 1;
	__delay_us(10);
	PORTAbits.RA0 = 0;

	// aguarda o echo receber sinal
	while(!PORTAbits.RA1);

	// habilita o timer1
	T1CONbits.TMR1ON = 1;

	// aguarda o echo sair do estado alto
	while(PORTAbits.RA1);

	// desabilita o timer1
	T1CONbits.TMR1ON = 0;

	// lê os dados dos dois registradores de
	// 8-bits e atribui ao MSB/LSB do length,
	// que é de 16-bits.
	length = (TMR1H << 8) | TMR1L;

	// calculando a distância
	length = (uint16_t) round(length / 58.8235f);

	return length;
}