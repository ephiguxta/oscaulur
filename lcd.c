#include <xc.h>
#include <pic16f628a.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

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
	data_or_cmd(data, mode);
	PORTB = 0x00;

	// nibble menos significativo
	PORTB = (data & 0x0f);
	data_or_cmd(data, mode);
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

void write_string(uint8_t text[16]) {
	// calculando o tamanho real do texto
	uint8_t str_size = (uint8_t) strlen(text);

	for(uint8_t i = 0; i < str_size; i++)
		write_char(text[i]);
}

void cursor_addr(uint8_t addr) {
	// RS e E devem ser zero para que seja
	// enviado o endereço da matriz
	PORTAbits.RA2 = 0;
	PORTAbits.RA3 = 0;

	// os nibble mais significativo devem
	// variar entre 1 0x8 a 0xf (7 possibilidades)
	// o OR bit a bit foi feito para manter o
	// quarto bit sempre ativo (0b1000);
	PORTD = 0x0f & (addr | 0x08);
	PORTAbits.RA3 = 1;
	__delay_us(50);
	PORTAbits.RA3 = 0;
	PORTD = 0x00;

	// nibble menos significatido;
	PORTD = 0x0f & (addr >> 4);
	PORTAbits.RA3 = 1;
	__delay_us(50);
	PORTAbits.RA3 = 0;
	PORTD = 0x00;
}

void cursor_addr(uint8_t addr) {
	if(addr >= 0x80 && addr <= 0x8f || \
		addr >= 0xc0 && addr <= 0xcf) {
		// linha 1: 0x80 a 0x8f
		// linha 2: 0xc0 a 0xcf

		byte_slice(addr, 0);
	}
}
