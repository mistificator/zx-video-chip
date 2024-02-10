/*
 * main.c
 *
 * Created: 12/1/2023 12:25:37 AM
 *  Author: mistp
 */ 

#include <xc.h>
#include "ili9341.h"
#include "zx_defs.h"

#define COLOR_MODE

#ifdef COLOR_MODE // Color mode

#define ZX_ATTR_SZ	0x300
uint8_t zx_attr[ZX_ATTR_SZ];

inline void DrawPixels(uint16_t p_x, uint16_t p_y, uint8_t pixels, uint8_t attr)
{
	uint16_t blue = ZX_BLUE;
	uint16_t red = ZX_RED;
	uint16_t green = ZX_GREEN;
	if (attr & (1 << 6))
	{
		blue <<= 1;		
		red <<= 1;
		green <<= 1;
	}
	const uint8_t zx_ink = (attr & 0x07);
	uint16_t tft_ink = 0;
	if ((zx_ink & 0x01) != 0) tft_ink |= blue;
	if ((zx_ink & 0x02) != 0) tft_ink |= red;
	if ((zx_ink & 0x04) != 0) tft_ink |= green;
	const uint8_t zx_paper = ((attr & 0x38) >> 3);
	uint16_t tft_paper = 0;
	if ((zx_paper & 0x01) != 0) tft_paper |= blue;
	if ((zx_paper & 0x02) != 0) tft_paper |= red;
	if ((zx_paper & 0x04) != 0) tft_paper |= green;

	CS_ACTIVE;
	TFT9341_SetAddrWindow(p_x, p_y, 319, 239);	
	CD_COMMAND;
	TFT9341_Write8(0x2C);	
	CD_DATA;
	for (uint8_t i = 0; i < 8; ++i)
	{		
		const uint16_t tft_color = (pixels & (0x80 >> i)) ? tft_ink : tft_paper;
		TFT9341_Write8(tft_color >> 8); TFT9341_Write8(tft_color);
	}	
	CS_IDLE;
}

inline void TranslatePixelsData(uint16_t addr, uint8_t data)
{
	DrawPixels(
		((addr & 0x1F) << 3) + ZX_OFFSET_X,
		(((addr & 0x1800) >> 5) | ((addr & 0x00E0) >> 2) | ((addr & 0x0700) >> 8)) + ZX_OFFSET_Y,
		data,
		zx_attr[((addr & 0x1800) >> 3) | (addr & 0x00FF)]
	);
}

#else // Black & White mode

inline void TranslatePixelsData(uint16_t addr, uint8_t data)
{
	CS_ACTIVE;
	TFT9341_SetAddrWindow(((addr & 0x1F) << 3) + ZX_OFFSET_X, (((addr & 0x1800) >> 5) | ((addr & 0x00E0) >> 2) | ((addr & 0x0700) >> 8)) + ZX_OFFSET_Y, 319, 239);
	CD_COMMAND;
	TFT9341_Write8(0x2C);
	CD_DATA;
	for (uint8_t i = 0; i < 8; ++i)
	{
		const uint16_t tft_color = (data & (0x80 >> i)) ? 0 : (ZX_RED | ZX_GREEN | ZX_BLUE);
		TFT9341_Write8(tft_color >> 8); TFT9341_Write8(tft_color);
	}
	CS_IDLE;	
}
#endif

inline void TranslateVideoData(void)
{	
	if ((MEM_PIN & (1 << MEM_CLK)) == 0)
	{
		const uint8_t half_addr = ADDR_PIN;		
		const uint8_t data = PIXEL_PIN;
		while ((MEM_PIN & (1 << MEM_CLK)) == 0);
		const uint16_t addr = half_addr | (ADDR_PIN << 8); 
		if (addr >= 0x4000 && addr < 0x5B00)
		{
			if (addr < 0x5800)
			{
				TranslatePixelsData(addr, data);				
			}
#ifdef COLOR_MODE			
			else
			{
				zx_attr[addr - 0x5800] = data;
			}
#endif			
		}
	}	
}

int main(void)
{	
	TFT9341_Init();	
	TFT9341_FillScreen(ZX_RED | ZX_GREEN | ZX_BLUE);
	
	while(1) TranslateVideoData();
	
	return 0;
}