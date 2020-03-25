#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "LCD_1602A.h"

int main(void)
{
	
	lcd_t lcd;
	lcd.Controll_ddr = &DDRC;
	lcd.Controll_pin = &PINC;
	lcd.Controll_port = &PORTC;
	lcd.DB_ddr = &DDRD;
	lcd.DB_pin = &PIND;
	lcd.DB_port = &PORTD;
	
	LCD_1602A_init(&lcd);
	
	
	while (1)
	{

		LCD_1602A_send_command(&lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
		_delay_us(4500);
		LCD_1602A_send_command(&lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
		_delay_us(4500);
		LCD_1602A_send_command(&lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE);
		_delay_us(150);
		LCD_1602A_send_command(&lcd, FUNCTION_SET | FUNCTION_SET_8BIT_BUS_MODE | FUNCTION_SET_2LINE_MODE);
		
		LCD_1602A_send_command(&lcd, CONTROLL);
		LCD_1602A_send_command(&lcd, ENTRY_MODE_SET | ENTRY_MODE_SET_INCREMENT);
		LCD_1602A_send_command(&lcd, CONTROLL | CONTROLL_Display_ON);
		LCD_1602A_send_command(&lcd,RETURN_HOME);
		
		LCD_1602A_clear(&lcd);
		for (uint8_t i = 0; i < 255; i++)
		{
			_delay_ms(1000);
			LCD_1602A_print_prog_string(&lcd, PSTR("Hallo !!!"));
			_delay_ms(1000);
			//LCD_1602A_print_int(&lcd, 27);
			//LCD_1602A_print_char(&lcd, 0b11011111);
			LCD_1602A_clear(&lcd);
		}

	}
	
	
}

