#ifndef ILI9341_H_
#define ILI9341_H_

#include <stdlib.h>
#include "global.h"

#define swap(a,b) {int16_t t=a;a=b;b=t;}
#define  ADDR_PIN PINA
#define  PIXEL_PIN PINC
#define  DATA_PORT PORTD
#define  COMMAND_PORT PORTB
#define  MEM_PIN PINB
#define  MEM_CLK 1
#define  LCD_CD 6 //Command/Data
#define  LCD_WR 7 //LCD Write
#define  WR_IDLE COMMAND_PORT|=(1<<LCD_WR)
#define  WR_ACTIVE COMMAND_PORT&=~(1<<LCD_WR)
#define  CD_COMMAND COMMAND_PORT&=~(1<<LCD_CD)
#define  CD_DATA COMMAND_PORT|=(1<<LCD_CD)

#if 0
	#define  LCD_CS 2//Chip Select
	#define  LCD_RD 4//LCD Read
	#define  LCD_RESET 0//LCD Reset
	#define  RESET_IDLE COMMAND_PORT|=(1<<LCD_RESET)
	#define  CS_IDLE COMMAND_PORT|=(1<<LCD_CS)
	#define  RD_IDLE COMMAND_PORT|=(1<<LCD_RD)
	#define  RESET_ACTIVE COMMAND_PORT&=~(1<<LCD_RESET)
	#define  CS_ACTIVE COMMAND_PORT&=~(1<<LCD_CS)
	#define  RD_ACTIVE COMMAND_PORT&=~(1<<LCD_RD)
#else	
	#define  RESET_IDLE 
	#define  CS_IDLE
	#define  RD_IDLE 
	#define  RESET_ACTIVE 
	#define  CS_ACTIVE 
	#define  RD_ACTIVE 
#endif


#define  BLACK 0x0000
#define  BLUE 0x001F
#define  RED 0x0F800
#define  GREEN 0x07E0
#define  CYAN 0x07FF
#define  MAGENTA 0xF81F
#define  YELLOW 0xFFE0
#define  WHITE 0xFFFF

#define  WR_STROBE {WR_ACTIVE;WR_IDLE;}

void TFT9341_Init(void);
void TFT9341_FillScreen(unsigned int color);
void TFT9341_FillRectangle(unsigned int color,unsigned int x1, unsigned int y1,
					unsigned int x2, unsigned int y2);
unsigned int TFT9341_RandColor(void);
void TFT9341_DrawPixel(int x, int y, unsigned int color);
void TFT9341_DrawLine(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2);
void TFT9341_DrawRect(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2);
void TFT9341_DrawCircle(unsigned int x0, unsigned int y0, int r, unsigned int color);
void TFT9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone,
unsigned char charcode, unsigned char size);
void TFT9341_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone,
char *str, unsigned char size);

void TFT9341_Write8(unsigned char dt);
void TFT9341_SetAddrWindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

#endif /* ILI9341_H_ */