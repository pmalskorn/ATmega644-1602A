
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "LCD_1602A.h"


void LCD_1602A_init(lcd_t *lcd){
	*(lcd->Controll_ddr) = 0xff;
	*(lcd->Controll_port) = 0x00;
	*(lcd->DB_ddr) = 0xff;
	*(lcd->DB_port) = 0x00;
}


void LCD_1602A_set_output(lcd_t *lcd){
	LCD_1602A_init(lcd);
}


void LCD_1602A_pulse(lcd_t *lcd){
	*(lcd->Controll_port) &= ~E;
	_delay_us(1);
	*(lcd->Controll_port) |= E;
	_delay_us(1);
	*(lcd->Controll_port) &= ~E;
	_delay_us(100);
}


void LCD_1602A_send_command(lcd_t *lcd, uint8_t cmd){
	*(lcd->DB_port) = cmd;
	LCD_1602A_pulse(lcd);
}


void LCD_1602A_print_char(lcd_t *lcd, char c){
	*(lcd->Controll_port) |= RS;
	*(lcd->DB_port) = c;
	LCD_1602A_pulse(lcd);
	*(lcd->Controll_port) &= ~RS;
}

void LCD_1602A_print_int(lcd_t *lcd, uint8_t i){
	LCD_1602A_print_char(lcd, i / 100 + 48);
	LCD_1602A_print_char(lcd, (i % 100) / 10  + 48);
	LCD_1602A_print_char(lcd, i % 10  + 48);
}


void LCD_1602A_print_string(lcd_t *lcd, char *str){
	char c = *str++;
	while(c != 0 && c != 0x10){
		LCD_1602A_print_char(lcd, c);
		c = *str++;
	}
}

void LCD_1602A_print_prog_string(lcd_t *lcd, char const* string) {
	char c;
	while ((c = (char)pgm_read_byte(string++))) {
		LCD_1602A_print_char(lcd, c);
	}
}




