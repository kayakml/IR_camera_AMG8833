//mylibraries

#ifndef __ST7789_H
#define	__ST7789_H


#include "../my_headers/header_definition.h"

#ifdef dspic33_deneme
#include "../../dspic33_deneme.X/project_specific.h"
#endif
#ifdef IR_cam_PIC24f
#include "../../IR_cam_PIC24f.X/project_specific.h"
#endif
#ifdef my_OV7670
#include "../../my_OV7670.X/project_specific.h"
#endif






#include <stdbool.h>

//#define command_data_via_SPI
#define command_data_via_IO

#define ST7789_TFTWIDTH 	240
#define ST7789_TFTHEIGHT 	240

#define ST7789_240x240_XSTART 0
#define ST7789_240x240_YSTART 0

#define ST_CMD_DELAY   0x80    // special signifier for command lists

#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

#define ST7789_MADCTL_MY  0x80
#define ST7789_MADCTL_MX  0x40
#define ST7789_MADCTL_MV  0x20
#define ST7789_MADCTL_ML  0x10
#define ST7789_MADCTL_RGB 0x00

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

// Color definitions
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define RIGHT 9999
#define CENTER 9






void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void pushColor(uint16_t color);
void fillScreen(uint16_t color);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void setRotation(uint8_t r);
void invertDisplay(bool i);
void init(uint16_t width, uint16_t height);
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
//uint16_t color565(uint8_t r, uint8_t g, uint8_t b) /*{ return Color565(r, g, b)*/; 




void send_data(uint8_t VL);
uint8_t displayInit(uint8_t *cmd_ptr);
void writecommand(uint8_t c);
void writedata(uint8_t d);           
//void commonInit(const uint8_t *cmdList);


#endif
