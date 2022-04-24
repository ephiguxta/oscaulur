#include <xc.h>
#include <pic16f628a.h>
#include "bit_config.h"

#define _XTAL_FREQ 4000000


int main(void){
	//0b 0000 1000 (RB3: entrada)
	TRISB = 0x08;

	while(1){
		if(PORTBbits.RB3 == 1)
			PORTBbits.RB0 = 1;
		else
			PORTBbits.RB0 = 0;

		__delay_ms(150);
	}

	return 0;
}