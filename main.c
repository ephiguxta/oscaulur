#include <xc.h>
#include <pic16f628a.h>
#include <stdint.h>
#include <math.h>

#include "bit_config.h"
#include "lcd.h"

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
	//
	// pinos RS e E são na porta A também
	TRISA = 0x02;

	// datasheet: página 25
	// associando o prescaler ao WDT (bit 3)
	// prescaler 1:64 (bit 0 - 2)
	// 16 * 64ms = 1152 ms
	// 110 = 0x6
	OPTION_REG = 0b10001110;

	// prescaler 1:1
	// datasheet: pág 50 - reg 7.1
	T1CONbits.T1CKPS = 0x0;
	// clock interno: (fosc/4)
	T1CONbits.TMR1CS = 0;

	uint16_t length = 0;

	lcd_reset();
	lcd_initialize();

	uint8_t text_1[16] = "Dist: ";
	write_str(text);

	while(1){
		TMR1H = 0;
		TMR1L = 0;

		length = centimeters(length);

		cursor_addr(0x86);
		write_str(text_1);

		// caso o usuário esteja a uma distância
		// menor que 30cm
		if(length >= 10 && length <= 30) {
			PORTBbits.RB5 = 1;
			__delay_ms(25);

		} else {
			PORTBbits.RB5 = 0;
		}

		// limpando o timer interno do WDT
		CLRWDT();
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
