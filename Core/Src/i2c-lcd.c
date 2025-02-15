/** 
Edit by modify: Ngoc Hang 
**/

#include "i2c-lcd.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD (0x21 << 1) // change this according to your setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;
	data_t[1] = data_u|0x08;
	data_t[2] = data_l|0x0C;
	data_t[3] = data_l|0x08;
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;
	data_t[1] = data_u|0x09;
	data_t[2] = data_l|0x0D;
	data_t[3] = data_l|0x09;
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void) {
	lcd_send_cmd (0x33);
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28);
	HAL_Delay(50);
	lcd_send_cmd (0x01);
	HAL_Delay(50);
	lcd_send_cmd (0x06);
	HAL_Delay(50);
	lcd_send_cmd (0x0c);
	HAL_Delay(50);
	lcd_send_cmd (0x02);
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1) 
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	lcd_send_cmd(pos_Addr);
}


void lcd_update(){
	if(timer3_flag == 1){
			lcd_goto_XY(1, 1);
			lcd_send_string("                ");
			lcd_goto_XY(2, 1);
			lcd_send_string("                ");

		lcd_goto_XY(1, 1);
		lcd_send_string(buffer1);
		lcd_goto_XY(2, 1);
		lcd_send_string(buffer2);
		setTimer3(100);
	}
}



