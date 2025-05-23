/*
 * LCD_GFX.c
 *
 * Created: 9/20/2021 6:54:25 PM
 *  Author: You
 */ 

#include "LCD_GFX.h"
#include "ST7735.h"
#include <math.h>


#define LCD_WIDTH 180
#define LCD_HEIGHT 128

/******************************************************************************
* Local Functions
******************************************************************************/

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}


/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
}

/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if ((pixels>>j)&1==1){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/

/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
{
	for (int x = -(int)radius; x <= radius; x++) {
        int y = sqrt(radius * radius - x * x);
        
        if (x+x0 >= LCD_WIDTH || x+x0 < 0) {
            continue;
        }
        
        LCD_drawBlock(x+x0,-y+y0,x+x0,y+y0,color);
    }
}


/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/
void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
{
	int dx = x1 - x0;
    int dy = y1 - y0;
    int D = 2*dy - dx;
    int y = y0;
    
    int xMin = min(max(x0, 0), LCD_WIDTH-1);
    int xMax = min(max(x1, 0), LCD_WIDTH-1);

    for (short x = xMin; x <= xMax; x++) {
        if (y >= 0 && y < LCD_HEIGHT) {
            LCD_drawPixel(x, y, c);
        }
        if (D > 0) {
            y = y + 1;
            D = D - 2*dx;
        }
        
        D = D + 2*dy;
    }
}


void LCD_setAddrWithColor(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
    LCD_setAddr(x0, y0, x1, y1);
    for (uint8_t i = x0; i <= x1; i++) {
        for (uint8_t j = y0; j <= y1; j++) {
            SPI_ControllerTx_16bit(color);
        }
    }
}


/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
{
    uint8_t xMax = min(x1, LCD_WIDTH-1);
    uint8_t yMax = min(y1, LCD_HEIGHT-1);
    LCD_setAddrWithColor(x0, y0, xMax, yMax, color);
}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color)
{
    LCD_drawBlock(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1, color);
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
{
	while (*str != '\0') {
        LCD_drawChar(x,y, (uint16_t) *str, fg,bg);
        x+=8; // increment by 8 lines each time
        str++;
    }
}

void LCD_drawBlockPixelByPixel(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
    for (uint8_t i = x0; i < x1; i++) {
        for (uint8_t j = y0; j < y1; j++) {
            LCD_drawPixel(i,j,color);
        }
    }
}