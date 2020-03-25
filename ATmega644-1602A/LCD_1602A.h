#include <inttypes.h>

#ifndef LCD1602A_H_
#define LCD1602A_H_

#define LINE_1_START_ADDRESS		0x00
#define LINE_1_END_ADDRESS			0x0F
#define LINE_2_START_ADDRESS		0x40
#define LINE_2_END_ADDRESS			0x4F

#define CLEAR_DISAPLAY				0b00000001
#define RETURN_HOME					0b00000010
#define ENTRY_MODE_SET				0b00000100
#define ENTRY_MODE_SET_INCREMENT	0b00000010
#define ENTRY_MODE_SET_SHIFT		0b00000001
#define CONTROLL					0b00001000
#define CONTROLL_Display_ON			0b00000100
#define CONTROLL_CURSOR_ON			0b00000010
#define CONTROLL_CURSOR_BLINK_ON	0b00000001
#define SHIFT_CURSOR_LEFT			0b00010000
#define SHIFT_CURSOR_RIGHT			0b00010100
#define SHIFT_DISPLAY_LEFT			0b00011000
#define SHIFT_DISPLAY_RIGHT			0b00011100
#define FUNCTION_SET				0b00100000
#define FUNCTION_SET_8BIT_BUS_MODE	0b00010000
#define FUNCTION_SET_2LINE_MODE		0b00001000
#define FUNCTION_SET_FONT			0b00000100

#define SET_CGRAM_ADDRESS			0b01000000 // 6 Bit
#define SET_DRAM_ADDRESS			0b10000000 // 7 Bit


typedef struct lcd_t {
	volatile uint8_t *Controll_ddr;
	volatile uint8_t *Controll_port;
	volatile uint8_t *Controll_pin;
	uint8_t E;
	uint8_t RS;
	uint8_t RW;
	
	volatile uint8_t *DB_ddr;
	volatile uint8_t *DB_port;
	volatile uint8_t *DB_pin;
	uint8_t data_pins;
} lcd_t;


void LCD_1602A_set_bus_output(lcd_t *lcd);
void LCD_1602A_set_bus_input(lcd_t *lcd);
void LCD_1602A_init(lcd_t *lcd);

void LCD_1602A_pulse(lcd_t *lcd);
void LCD_1602A_send_command(lcd_t *lcd, uint8_t cmd);
void LCD_1602A_clear(lcd_t *lcd);
void LCD_1602A_set_courser(lcd_t *lcd, uint8_t row, uint8_t col);

void LCD_1602A_print_int(lcd_t *lcd, uint8_t i);
void LCD_1602A_print_char(lcd_t *lcd, char c);
void LCD_1602A_print_string(lcd_t *lcd, char *str);
void LCD_1602A_print_prog_string(lcd_t *lcd, char const* string);


#endif /* 1602A_H_ */