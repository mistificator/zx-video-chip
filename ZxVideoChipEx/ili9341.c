﻿#include "ili9341.h"
//--------------------------------------------------------------
unsigned int X_SIZE = 0;
unsigned int Y_SIZE = 0;
unsigned long dtt=0;
//--------------------------------------------------------------
//font 16
const unsigned char chars16[][32] PROGMEM =
{
	//SPACE
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	//0
	{0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x0f, 0xe0, 0x0c, 0x60, 0x18, 0x30, 0x18, 0x30, 0x18, 0x30,
	0x18, 0x30, 0x18, 0x30, 0x18, 0x30, 0x0c, 0x60, 0x0f, 0xe0, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00},
	//1
	{0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
	0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x03, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00},
	//A
	{0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x07, 0xf0, 0x01, 0x40, 0x03, 0x60, 0x03, 0x60, 0x06, 0x30,
	0x07, 0xf0, 0x0f, 0xf8, 0x0c, 0x18, 0x0c, 0x18, 0x3e, 0x3e, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00},
	//B
	{0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x0f, 0xf0, 0x06, 0x30, 0x06, 0x30, 0x07, 0xe0, 0x07, 0xf0,
	0x06, 0x38, 0x06, 0x18, 0x06, 0x18, 0x06, 0x38, 0x0f, 0xf0, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00},
	//C
	{0x00, 0x00, 0x00, 0x00, 0x07, 0xd8, 0x0f, 0xf8, 0x1c, 0x38, 0x38, 0x18, 0x30, 0x00, 0x30, 0x00,
	0x30, 0x00, 0x30, 0x08, 0x38, 0x0c, 0x1c, 0x38, 0x0f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00}
};
//--------------------------------------------------------------
//font 8
const unsigned char chars8[][8] PROGMEM ={
	//SPACE
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	// !
	{0x04,0x04,0x04,0x04,0x00,0x04,0x00,0x00},
	// "
	{0x0A,0x0A,0x0A,0x00,0x00,0x00,0x00,0x00},
	// #
	{0x0A,0x0A,0x1F,0x0A,0x1F,0x0A,0x0A,0x00},
	// $
	{0x04,0x0F,0x14,0x0E,0x05,0x1E,0x04,0x00},
	// %
	{0x18,0x19,0x02,0x04,0x08,0x13,0x03,0x00},
	// &
	{0x0C,0x12,0x14,0x08,0x14,0x12,0x0D,0x00},
	// '
	{0x0C,0x04,0x08,0x00,0x00,0x00,0x00,0x00},
	// (
	{0x02,0x04,0x08,0x08,0x08,0x04,0x02,0x00},
	// )
	{0x08,0x04,0x02,0x02,0x02,0x04,0x08,0x00},
	// *
	{0x00,0x04,0x15,0x0E,0x15,0x04,0x00,0x00},
	// +
	{0x00,0x04,0x04,0x1F,0x04,0x04,0x00,0x00},
	// ,
	{0x00,0x00,0x00,0x00,0x0C,0x04,0x08,0x00},
	// -
	{0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00},
	// .
	{0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00},
	// /
	{0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00},
	// 0
	{0x0E,0x11,0x13,0x15,0x19,0x11,0x0E,0x00},
	// 1
	{0x04,0x0C,0x04,0x04,0x04,0x04,0x0E,0x00},
	// 2
	{0x0E,0x11,0x01,0x02,0x04,0x08,0x1F,0x00},
	// 3
	{0x1F,0x02,0x04,0x02,0x01,0x11,0x0E,0x00},
	// 4
	{0x02,0x06,0x0A,0x12,0x1F,0x02,0x02,0x00},
	// 5
	{0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E,0x00},
	// 6
	{0x06,0x08,0x10,0x1E,0x11,0x11,0x0E,0x00},
	// 7
	{0x1F,0x01,0x02,0x04,0x08,0x08,0x08,0x00},
	// 8
	{0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E,0x00},
	// 9
	{0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C,0x00},
	// :
	{0x00,0x01,0x02,0x04,0x08,0x10,0x00,0x00},
	// ;
	{0x00,0x0C,0x0C,0x00,0x0C,0x04,0x08,0x00},
	// <
	{0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00},
	// =
	{0x00,0x00,0x1F,0x00,0x1F,0x00,0x00,0x00},
	// >
	{0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00},
	// ?
	{0x0E,0x11,0x01,0x02,0x04,0x00,0x04,0x00},
	// @
	{0x0E,0x11,0x01,0x0D,0x15,0x15,0x0E,0x00},
	// A
	{0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00},
	// B
	{0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E,0x00},
	// C
	{0x0E,0x11,0x10,0x10,0x10,0x11,0x0E,0x00},
	// D
	{0x1C,0x12,0x11,0x11,0x11,0x12,0x1C,0x00},
	// E
	{0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F,0x00},
	// F
	{0x1F,0x10,0x10,0x1E,0x10,0x10,0x10,0x00},
	// G
	{0x0E,0x11,0x10,0x17,0x11,0x11,0x0E,0x00},
	// H
	{0x11,0x11,0x11,0x1F,0x11,0x11,0x11,0x00},
	// I
	{0x0E,0x04,0x04,0x04,0x04,0x04,0x0E,0x00},
	// J
	{0x07,0x02,0x02,0x02,0x02,0x12,0x0C,0x00},
	// K
	{0x11,0x12,0x14,0x18,0x14,0x12,0x11,0x00},
	// L
	{0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0x00},
	// M
	{0x11,0x1B,0x15,0x15,0x11,0x11,0x11,0x00},
	// N
	{0x11,0x11,0x19,0x15,0x13,0x11,0x11,0x00},
	// O
	{0x0E,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},
	// P
	{0x1E,0x11,0x11,0x1E,0x10,0x10,0x10,0x00},
	// Q
	{0x0E,0x11,0x11,0x11,0x15,0x12,0x0D,0x00},
	// R
	{0x1E,0x11,0x11,0x1E,0x14,0x12,0x11,0x00},
	// S
	{0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E,0x00},
	// T
	{0x1F,0x04,0x04,0x04,0x04,0x04,0x04,0x00},
	// U
	{0x11,0x11,0x11,0x11,0x11,0x11,0x0E,0x00},
	// V
	{0x11,0x11,0x11,0x11,0x11,0x0A,0x04,0x00},
	// W
	{0x11,0x11,0x11,0x11,0x15,0x15,0x0E,0x00},
	// X
	{0x11,0x11,0x0A,0x04,0x0A,0x11,0x11,0x00},
	// Y
	{0x11,0x11,0x11,0x0A,0x04,0x04,0x04,0x00},
	// Z
	{0x1F,0x01,0x02,0x04,0x08,0x10,0x1F,0x00},
	// [
	{0x0E,0x08,0x08,0x08,0x08,0x08,0x0E,0x00},
	//
	{0x11,0x0A,0x1F,0x04,0x1F,0x04,0x04,0x00},
	// ]
	{0x0E,0x02,0x02,0x02,0x02,0x02,0x0E,0x00},
	// ^
	{0x04,0x0A,0x11,0x00,0x00,0x00,0x00,0x00},
	// _
	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00},
	// '
	{0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x00},
	// a
	{0x00,0x00,0x0E,0x01,0x0F,0x11,0x0F,0x00},
	// b
	{0x10,0x10,0x1E,0x11,0x11,0x11,0x1E,0x00},
	// c
	{0x00,0x00,0x0E,0x10,0x10,0x11,0x0E,0x00},
	// d
	{0x01,0x01,0x0D,0x13,0x11,0x11,0x0F,0x00},
	// e
	{0x00,0x00,0x0E,0x11,0x1F,0x10,0x0E,0x00},
	// f
	{0x06,0x09,0x08,0x1C,0x08,0x08,0x08,0x00},
	// g
	{0x00,0x0F,0x11,0x11,0x0F,0x01,0x0E,0x00},
	// h
	{0x10,0x10,0x16,0x19,0x11,0x11,0x11,0x00},
	// i
	{0x04,0x00,0x0C,0x04,0x04,0x04,0x0E,0x00},
	// j
	{0x02,0x00,0x06,0x02,0x02,0x12,0x0C,0x00},
	// k
	{0x10,0x10,0x12,0x14,0x18,0x14,0x12,0x00},
	// l
	{0x18,0x08,0x08,0x08,0x08,0x08,0x1C,0x00},
	// m
	{0x00,0x00,0x1A,0x15,0x15,0x11,0x11,0x00},
	// n
	{0x00,0x00,0x16,0x19,0x11,0x11,0x11,0x00},
	// o
	{0x00,0x00,0x0E,0x11,0x11,0x11,0x0E,0x00},
	// p
	{0x00,0x00,0x1E,0x11,0x1E,0x10,0x10,0x00},
	// q
	{0x00,0x00,0x0F,0x11,0x0F,0x01,0x01,0x00},
	// r
	{0x00,0x00,0x16,0x19,0x10,0x10,0x10,0x00},
	// s
	{0x00,0x00,0x0E,0x10,0x0E,0x01,0x1E,0x00},
	// t
	{0x08,0x08,0x1C,0x08,0x08,0x09,0x06,0x00},
	// u
	{0x00,0x00,0x11,0x11,0x11,0x13,0x0D,0x00},
	// v
	{0x00,0x00,0x11,0x11,0x11,0x0A,0x04,0x00},
	// w
	{0x00,0x00,0x11,0x11,0x11,0x15,0x0A,0x00},
	// x
	{0x00,0x00,0x11,0x0A,0x04,0x0A,0x11,0x00},
	// y
	{0x00,0x00,0x11,0x11,0x0F,0x01,0x0E,0x00},
	// z
	{0x00,0x00,0x1F,0x02,0x04,0x08,0x1F,0x00}
};
//--------------------------------------------------------------
void Port_Init(void)
{
	// disable ADC
	ADCSRA = 0;
	
	// Init A, B, C, D	
	PORTA =		0xFF;
	PINA =		0x00;
	DDRA =		0x00;
	PORTB =		0xFF;
	PINB =		0x00;
	DDRB =		(1<<LCD_CD)|(1 << LCD_WR);
	PORTC =		0xFF;
	PINC =		0x00;
	DDRC =		0x00;
	PORTD =		0xFF;
	PIND =		0x00;
	DDRD =		0xFF;
}
//--------------------------------------------------------------
inline void TFT9341_SendCommand(unsigned char cmd)
{
	CD_COMMAND;//лапка в состоянии посылки команды
	RD_IDLE;//отключим чтение
	CS_ACTIVE;//выбор дисплея
	DATA_PORT=cmd;
	WR_STROBE;
	CS_IDLE;
}
//--------------------------------------------------------------
inline void TFT9341_SendData(unsigned char dt)
{
	CD_DATA;//лапка в состоянии посылки данных
	RD_IDLE;//отключим чтение
	CS_ACTIVE;//выбор дисплея
	DATA_PORT=dt;
	WR_STROBE;
	CS_IDLE;
}
//--------------------------------------------------------------
inline void TFT9341_Write8(unsigned char dt)
{
	DATA_PORT=dt;
	WR_STROBE;
}
//--------------------------------------------------------------
void TFT9341_Reset(void)
{
	CS_IDLE;
	WR_IDLE;
	RD_IDLE;
	RESET_ACTIVE;
	Sleep(2);
	RESET_IDLE;
	CS_ACTIVE;
	TFT9341_SendCommand(0x01); //Software Reset
	for (uint8_t i=0;i<3;i++) WR_STROBE;
	CS_IDLE;
}
//--------------------------------------------------------------
void TFT9341_SetRotation(unsigned char r)
{
	TFT9341_SendCommand(0x36);
	switch(r)
	{
		case 0:
		TFT9341_SendData(0x48);
		X_SIZE = 240;
		Y_SIZE = 320;
		break;
		case 1:
		TFT9341_SendData(0x28);
		X_SIZE = 320;
		Y_SIZE = 240;
		break;
		case 2:
		TFT9341_SendData(0x88);
		X_SIZE = 240;
		Y_SIZE = 320;
		break;
		case 3:
		TFT9341_SendData(0xE8);
		X_SIZE = 320;
		Y_SIZE = 240;
		break;
	}
}
//--------------------------------------------------------------
void TFT9341_Flood(unsigned short color, unsigned long len)
{
	unsigned short blocks;
	unsigned char i, hi = color>>8, lo=color;
	CS_ACTIVE;
	CD_COMMAND;
	TFT9341_Write8(0x2C);
	CD_DATA;
	TFT9341_Write8(hi);
	TFT9341_Write8(lo);
	len--;
	blocks=(unsigned short)(len/64);//64 pixels/block
	if (hi==lo)
	{
		while(blocks--)
		{
			i=16;
			do 
			{
				WR_STROBE;WR_STROBE;WR_STROBE;WR_STROBE;//2bytes/pixel
				WR_STROBE;WR_STROBE;WR_STROBE;WR_STROBE;//x4 pixel
			} while (--i);
		}
		//Fill any remaining pixels(1 to 64)
		for (i=(unsigned char)len&63;i--;)
		{
			WR_STROBE;
			WR_STROBE;
		}
	}
	else
	{
		while(blocks--)
		{
			i=16;
			do
			{
				TFT9341_Write8(hi);TFT9341_Write8(lo);TFT9341_Write8(hi);TFT9341_Write8(lo);
				TFT9341_Write8(hi);TFT9341_Write8(lo);TFT9341_Write8(hi);TFT9341_Write8(lo);
			} while (--i);
		}
		//Fill any remaining pixels(1 to 64)
		for (i=(unsigned char)len&63;i--;)
		{
			TFT9341_Write8(hi);
			TFT9341_Write8(lo);
		}
	}
	CS_IDLE;
}
//--------------------------------------------------------------
inline void TFT9341_WriteRegister32(unsigned char r, unsigned long d)
{
	CS_ACTIVE;
	CD_COMMAND;
	TFT9341_Write8(r);
	CD_DATA;
//	_delay_us(1);
	TFT9341_Write8(d>>24);
//	_delay_us(1);
	TFT9341_Write8(d>>16);
//	_delay_us(1);
	TFT9341_Write8(d>>8);
//	_delay_us(1);
	TFT9341_Write8(d);
	CS_IDLE;
}
//--------------------------------------------------------------
union
{
	unsigned long t;
	unsigned int v[2];
} p;
inline void TFT9341_SetAddrWindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	CS_ACTIVE;
	p.v[1] = x1;
	p.v[0] = x2;
	TFT9341_WriteRegister32(0x2A, p.t);//Column Address Set
	p.v[1] = y1;
	p.v[0] = y2;
	TFT9341_WriteRegister32(0x2B, p.t);//Page Address Set
	CS_IDLE;
}
//--------------------------------------------------------------
void TFT9341_FillScreen(unsigned int color)
{
	TFT9341_SetAddrWindow(0,0,X_SIZE-1,Y_SIZE-1);
	TFT9341_Flood(color,(long)X_SIZE*(long)Y_SIZE);
}
//--------------------------------------------------------------
void TFT9341_FillRectangle(unsigned int color,unsigned int x1, unsigned int y1,
							 unsigned int x2, unsigned int y2)
{
	TFT9341_SetAddrWindow(x1, y1, x2, y2);
	TFT9341_Flood(color, (long)(x2-x1+1) * (long)(y2-y1+1));
}
//--------------------------------------------------------------
inline void TFT9341_DrawPixel(int x, int y, unsigned int color)
{
//	if((x<0)||(y<0)||(x>=X_SIZE)||(y>=Y_SIZE)) return;
	CS_ACTIVE;
	TFT9341_SetAddrWindow(x,y,X_SIZE-1,Y_SIZE-1);
	CS_ACTIVE;
	CD_COMMAND;
	TFT9341_Write8(0x2C);
	CD_DATA;
	TFT9341_Write8(color>>8);TFT9341_Write8(color);
	CS_IDLE;
}
//--------------------------------------------------------------
void TFT9341_DrawLine(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2)
{
	int steep = abs(y2-y1)>abs(x2-x1);
	if (steep)
	{
		swap(x1,y1);
		swap(x2,y2);
	}
	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	int dx,dy;
	dx=x2-x1;
	dy=abs(y2-y1);
	int err=dx/2;
	int ystep;
	if(y1<y2)	ystep = 1;
	else		ystep = -1;
	for (;x1<=x2;x1++)
	{
		if (steep)	TFT9341_DrawPixel(y1,x1,color);
		else TFT9341_DrawPixel(x1,y1,color);
		err-=dy;
		if (err<0)
		{
			y1 += ystep;
			err=dx;
		}
	}
}
//--------------------------------------------------------------
void TFT9341_DrawRect(unsigned int color,unsigned int x1, unsigned int y1,
unsigned int x2, unsigned int y2)
{
	TFT9341_DrawLine(color,x1,y1,x2,y1);
	TFT9341_DrawLine(color,x2,y1,x2,y2);
	TFT9341_DrawLine(color,x1,y1,x1,y2);
	TFT9341_DrawLine(color,x1,y2,x2,y2);
}
//--------------------------------------------------------------
void TFT9341_DrawCircle(unsigned int x0, unsigned int y0, int r, unsigned int color)
{
	int f = 1-r;
	int ddF_x=1;
	int ddF_y=-2*r;
	int x = 0;
	int y = r;
	TFT9341_DrawPixel(x0,y0+r,color);
	TFT9341_DrawPixel(x0,y0-r,color);
	TFT9341_DrawPixel(x0+r,y0,color);
	TFT9341_DrawPixel(x0-r,y0,color);
	while (x<y)
	{
		if (f>=0)
		{
			y--;
			ddF_y+=2;
			f+=ddF_y;
		}
		x++;
		ddF_x+=2;
		f+=ddF_x;
		TFT9341_DrawPixel(x0+x,y0+y,color);
		TFT9341_DrawPixel(x0-x,y0+y,color);
		TFT9341_DrawPixel(x0+x,y0-y,color);
		TFT9341_DrawPixel(x0-x,y0-y,color);
		TFT9341_DrawPixel(x0+y,y0+x,color);
		TFT9341_DrawPixel(x0-y,y0+x,color);
		TFT9341_DrawPixel(x0+y,y0-x,color);
		TFT9341_DrawPixel(x0-y,y0-x,color);
	}
}
//--------------------------------------------------------------
unsigned int TFT9341_RandColor(void)
{
	unsigned char c = rand()%8;
	switch(c)
	{
		case 0:
		return BLACK;
		break;
		case 1:
		return BLUE;
		break;
		case 2:
		return RED;
		break;
		case 3:
		return GREEN;
		break;
		case 4:
		return CYAN;
		break;
		case 5:
		return MAGENTA;
		break;
		case 6:
		return YELLOW;
		break;
		case 7:
		return WHITE;
		break;
	}
	return BLACK;
}
//--------------------------------------------------------------
void TFT9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone,
				unsigned char charcode, unsigned char size)
{
	switch(size)
	{
		int i,h;
		case 1:
			for(h=0;h<8;h++)
			{
				for(i=0;i<8;i++)
				{
					if ((pgm_read_byte(&chars8[charcode-0x20][h])>>(7-i))&0x01)
					{
						TFT9341_DrawPixel(x+i,y+h,color);
					}
					else
					{
						TFT9341_DrawPixel(x+i,y+h,phone);
					}
				}
			}
			break;
		case 2:
			for(h=0;h<16;h++)
			{
				for(i=0;i<8;i++)
				{
					if ((pgm_read_byte(&chars16[charcode-0x20][h*2])>>(7-i))&0x01)
					{
						TFT9341_DrawPixel(x+i,y+h,color);
					}
					else
					{
						TFT9341_DrawPixel(x+i,y+h,phone);
					}
					if ((pgm_read_byte(&chars16[charcode-0x20][h*2+1])>>(7-i))&0x01)
					{
						TFT9341_DrawPixel(x+i+8,y+h,color);
					}
					else
					{
						TFT9341_DrawPixel(x+i+8,y+h,phone);
					}
				}
			}
			break;
	}
}
//--------------------------------------------------------------
void TFT9341_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone,
					char *str, unsigned char size)
{
	while (*str)
	{
		if ((x+(size*8))>X_SIZE)
		{
			x = 1;
			y = y + (size*8);
		}
		TFT9341_Draw_Char(x,y,color,phone,*str,size);
		x += size*8;
		str++;
	}
}
//--------------------------------------------------------------
void TFT9341_Init(void)
{
	Port_Init();
	TFT9341_Reset();
	Sleep(10);
	CS_ACTIVE;
	TFT9341_SendCommand(0x01);//Software Reset
	TFT9341_SendCommand(0xCB);//Power Control A
	TFT9341_SendData(0x39);
	TFT9341_SendData(0x2C);
	TFT9341_SendData(0x00);
	TFT9341_SendData(0x34);
	TFT9341_SendData(0x02);
	TFT9341_SendCommand(0xCF);//Power Control B
	TFT9341_SendData(0x00);
	TFT9341_SendData(0xC1);
	TFT9341_SendData(0x30);
	TFT9341_SendCommand(0xE8);//Driver timing control A
	TFT9341_SendData(0x85);
	TFT9341_SendData(0x00);
	TFT9341_SendData(0x78);
	TFT9341_SendCommand(0xEA);//Driver timing control B
	TFT9341_SendData(0x00);
	TFT9341_SendData(0x00);
	TFT9341_SendCommand(0xED);//Power on Sequence control
	TFT9341_SendData(0x64);
	TFT9341_SendData(0x03);
	TFT9341_SendData(0x12);
	TFT9341_SendData(0x81);
	TFT9341_SendCommand(0xF7);//Pump ratio control
	TFT9341_SendData(0x20);
	TFT9341_SendCommand(0xC0);//Power Control 1
	TFT9341_SendData(0x10);
	TFT9341_SendCommand(0xC1);//Power Control 2
	TFT9341_SendData(0x10);
	TFT9341_SendCommand(0xC5);//VCOM Control 1
	TFT9341_SendData(0x3E);
	TFT9341_SendData(0x28);
	TFT9341_SendCommand(0xC7);//VCOM Control 2
	TFT9341_SendData(0x86);
	TFT9341_SetRotation(1);
	TFT9341_SendCommand(0x3A);//Pixel Format Set
	TFT9341_SendData(0x55);//16bit
	TFT9341_SendCommand(0xB1);
	TFT9341_SendData(0x00);
	TFT9341_SendData(0x18);// Частота кадров 79 Гц
	TFT9341_SendCommand(0xB6);//Display Function Control
	TFT9341_SendData(0x08);
	TFT9341_SendData(0x82);
	TFT9341_SendData(0x27);//320 строк
	TFT9341_SendCommand(0xF2);//Enable 3G (пока не знаю что это за режим)
	TFT9341_SendData(0x00);//не включаем
	TFT9341_SendCommand(0x26);//Gamma set
	TFT9341_SendData(0x01);//Gamma Curve (G2.2) (Кривая цветовой гаммы)
	TFT9341_SendCommand(0xE0);//Positive Gamma  Correction
	TFT9341_SendData(0x0F);
	TFT9341_SendData(0x31);
	TFT9341_SendData(0x2B);
	TFT9341_SendData(0x0C);
	TFT9341_SendData(0x0E);
	TFT9341_SendData(0x08);
	TFT9341_SendData(0x4E);
	TFT9341_SendData(0xF1);
	TFT9341_SendData(0x37);
	TFT9341_SendData(0x07);
	TFT9341_SendData(0x10);
	TFT9341_SendData(0x03);
	TFT9341_SendData(0x0E);
	TFT9341_SendData(0x09);
	TFT9341_SendData(0x00);
	TFT9341_SendCommand(0xE1);//Negative Gamma  Correction
	TFT9341_SendData(0x00);
	TFT9341_SendData(0x0E);
	TFT9341_SendData(0x14);
	TFT9341_SendData(0x03);
	TFT9341_SendData(0x11);
	TFT9341_SendData(0x07);
	TFT9341_SendData(0x31);
	TFT9341_SendData(0xC1);
	TFT9341_SendData(0x48);
	TFT9341_SendData(0x08);
	TFT9341_SendData(0x0F);
	TFT9341_SendData(0x0C);
	TFT9341_SendData(0x31);
	TFT9341_SendData(0x36);
	TFT9341_SendData(0x0F);
	TFT9341_SendCommand(0x11);//Выйдем из спящего режим
	Sleep(10);
	TFT9341_SendCommand(0x29);//Включение дисплея
	TFT9341_SendData(0x2C);
	Sleep(10);
}