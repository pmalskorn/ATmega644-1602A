
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "LCD_1602A.h"

uint8_t char_counter;

void LCD_1602A_set_bus_output(lcd_t *lcd){
	*(lcd->Controll_ddr) |= (lcd->E | lcd->RS | lcd->RW);
	*(lcd->Controll_port) &= ~(lcd->E | lcd->RS | lcd->RW);
	*(lcd->DB_ddr) = lcd->data_pins;
	*(lcd->DB_port) &= ~(lcd->data_pins);
}


void LCD_1602A_set_bus_input(lcd_t *lcd){
	*(lcd->Controll_ddr) &= ~(lcd->E | lcd->RS | lcd->RW);
	*(lcd->Controll_port) &= ~(lcd->E | lcd->RS | lcd->RW);
}


void LCD_1602A_init(lcd_t *lcd){
	char_counter = 0;
	LCD_1602A_set_bus_output(lcd);
	LCD_1602A_send_command(lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
	_delay_us(4500);
	LCD_1602A_send_command(lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
	_delay_us(4500);
	LCD_1602A_send_command(lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
	_delay_us(150);
	LCD_1602A_send_command(lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE | FUNCTION_SET_2LINE_MODE);
	LCD_1602A_send_command(lcd, CONTROLL);
	LCD_1602A_clear(lcd);
	LCD_1602A_send_command(lcd, ENTRY_MODE_SET | ENTRY_MODE_SET_INCREMENT);
	LCD_1602A_send_command(lcd, CONTROLL | CONTROLL_Display_ON);
}


void LCD_1602A_pulse(lcd_t *lcd){
	*(lcd->Controll_port) &= ~(lcd->E);
	_delay_us(1);
	*(lcd->Controll_port) |= (lcd->E);
	_delay_us(1);
	*(lcd->Controll_port) &= ~(lcd->E);
	_delay_us(100);
}


void LCD_1602A_send_command(lcd_t *lcd, uint8_t cmd){
	*(lcd->DB_port) = cmd;
	LCD_1602A_pulse(lcd);
}


void LCD_1602A_clear(lcd_t *lcd){
	LCD_1602A_send_command(lcd, CLEAR_DISAPLAY);
	_delay_ms(2);
}


void LCD_1602A_set_courser(lcd_t *lcd, uint8_t row, uint8_t col){
	uint8_t address = ( (1 - row) * LINE_1_START_ADDRESS) + (row * LINE_2_START_ADDRESS) + col; 
	LCD_1602A_send_command(lcd, SET_DRAM_ADDRESS | address);
}


void LCD_1602A_print_char(lcd_t *lcd, char c){
	*(lcd->Controll_port) |= (lcd->RS);
	*(lcd->DB_port) = c;
	LCD_1602A_pulse(lcd);
	*(lcd->Controll_port) &= ~(lcd->RS);
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






