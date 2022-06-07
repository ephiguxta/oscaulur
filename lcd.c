#include <xc.h>
#include <pic16f628a.h>
#include <stdint.h>
#include <math.h>

#define _XTAL_FREQ 4000000

#include "lcd.h"

// estabilizando o lcd
void lcd_reset(void) {
	__delay_ms(20);

	for(uint8_t i = 0; i <= 2; i++) {
		byte_slice(0x03, 0);
		__delay_us(50);
	}

	byte_slice(0x02, 0);
	__delay_us(50);
}

void lcd_initialize(void) {
	// comunicação de 4 bits,
	// display com duas ou mais linhas,
	// matriz 8x5
	byte_slice(0x28, 0);
	__delay_us(50);

	// liga o display com o cursor
	// piscando
	byte_slice(0x0f, 0);
	__delay_us(50);

	// desloca cursor para direita
	// após inserção de dados.
	// não desloca a mensagem.
	byte_slice(0x06, 0);
	__delay_us(50);

	// limpa a tela do display e desloca
	// o cursor para L1 e C1
	byte_slice(0x01, 0);
	__delay_ms(2);
}

void byte_slice(uint8_t data, uint8_t mode) {
	// nibble mais significativo
	PORTB = (data >> 4);
	data_or_cmd(mode);
	PORTB = 0x00;

	// nibble menos significativo
	PORTB = (data & 0x0f);
	data_or_cmd(mode);
	PORTB = 0x00;
}

void data_or_cmd(uint8_t mode) {
	// caso os dados sejam de inserção,
	// habilita RS (Register Select)
	// 0 - Instrução
	// 1 - Dados
	if(mode)
		PORTAbits.RA2 = 1; // RS - dados
	else
		PORTAbits.RA2 = 0; // RS - instrução

	// habilita lcd para receber comando/dado
	PORTAbits.RA3 = 1; //E

	__delay_ms(50);

	PORTAbits.RA3 = 0; // E
	PORTAbits.RA2 = 0; // RS
}

void write_char(uint8_t data) {
	// TODO:
	// arrumar a quebra de linha,
	// caso escreva no endereço além do lcd
	//
	// programar uma função que escreva texto
	// ao invés de caractere único.
	byte_slice(data, 1);
	__delay_us(50);
}
