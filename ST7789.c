//mylibraries

/********************************BAY_OLEG**************************************/
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*********************IPS240x240DISPLAY DRIVED BY******************************/
/******************************ST7789.c****************************************/
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*This code is based on 2 main source                                         */  
/* 1. Adafruits GFX graphics core library                                     */
/* https://github.com/adafruit/Adafruit-GFX-Library  
 *                         */
/* 2. ananevilya/Arduino-ST7789-Library                                       */
/*https://github.com/ananevilya/Arduino-ST7789-Library/blob/master/ --->>>    */
/*                                      --->>>    Arduino_ST7789.cpp#L496-L507*/
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*Adafruits GFX graphics core library comprised of some high level graphics   */
/*functions to draw shapes, bitmap operations and character/text issues.      */
/*drawCircle, drawGrayscaleBitmap_PROGMEM_withMASK are 2 of them              */
/*Besides these detailed functions, it also involves some mid-low level functi*/
/*ons such as : fillScreen, writePixel, writeFastVLine. These mid low level   */
/*functions use low level functions and in Adafruits GFX graphics core library*/
/*it is stated that those low level functions can be implemented in a display */
/*driver ic graphics library.                                                 */
/******************************************************************************/
/*ananevilya/Arduino-ST7789-Library has some initialization functions specific*/
/*to ST7789 driver chip. And moreover has low level functions such as         */
/*setAddrWindow which is used by high level and mid     level functions defi- */
/*ned in Adafruits GFX graphics core library                                  */
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/***************PIN CONFIGURATIONS ARE HANDLED IN conf_pin.c*******************/
/*              #define RST LATBbits.LATB15 //PIN30
                #define DC  LATBbits.LATB14 //PIN29
                #define SCL LATBbits.LATB13 //PIN28
                #define SDA LATBbits.LATB12 //PIN27
*/


#include <xc.h>
#include <stdbool.h>
#include "../my_headers/conf_clock.h"
#include "../my_headers/ST7789.h"
#include "../my_headers/conf_pin.h"
#include "../../my_libraries/my_headers/conf_SPI.h"
#include <libpic30.h>


struct ST7789_parameters{
    uint16_t _xstart;
    uint16_t _xstart;
    uint16_t _xstart;
    uint16_t _xstart;
    uint8_t  hi;
    uint8_t  lo;
    uint8_t  _colstart;
    uint8_t  _rowstart;
}

uint16_t    _xstart; 
uint16_t    _ystart; 
uint16_t    _width; 
uint16_t    _height; 
uint8_t     hi;
uint8_t     lo;
uint8_t     _colstart;
uint8_t     _rowstart;

#define     pulse(x) (x = 0) ; (x = 1);

/******************************************************************************/
static uint8_t   cmd_240x240[] = {          
    10,                       				// 9 commands in list:
    ST7789_SWRESET,   0,              		// 1: Software reset, no args, w/delay
      15,                     				// 150 ms delay
    ST7789_SLPOUT ,   0,              		// 2: Out of sleep mode, no args, w/delay
      25,                    				// 255 = 500 ms delay
    ST7789_COLMOD ,   1,              		// 3: Set color mode, no args 
      0x55,                   				// arg1:16-bit color
      1,                     				// 10 ms delay
    ST7789_MADCTL , 1,  					// 4: Memory access ctrl (directions), no args
      0x00,                   				// arg1: Row addr/col addr, bottom to top refresh
      0,                                    // no delay
    ST7789_CASET  , 4,  					// 5: Column addr set, no args, 
      0x00, ST7789_240x240_XSTART,          // XSTART high addr byte, xstart low addr byte
	  (ST7789_TFTWIDTH+ST7789_240x240_XSTART) >> 8, //xend high address byte
	  (ST7789_TFTWIDTH+ST7789_240x240_XSTART) & 0xFF,   // XEND = 240 low address byte
        0,                                  //no delay
    ST7789_RASET  , 4,  					// 6: Row addr set, no args, 
      0x00, ST7789_240x240_YSTART,          // YSTART = 0 high, ystart low
      (ST7789_TFTHEIGHT+ST7789_240x240_YSTART) >> 8, //yend high
	  (ST7789_TFTHEIGHT+ST7789_240x240_YSTART) & 0xFF,	// YEND = 240 low byte
        0,                                  //no delay
    ST7789_INVON ,   0,               		// 7: Inversion ON , no args
      1,                                    //delay
    ST7789_NORON  ,   0,              		// 8: Normal display on, no args,
      1,                     				// 10 ms delay
    ST7789_DISPON ,   0,                    // 9: Main screen turn on, no args
    25 };    
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/*inline uint16_t swapcolor(uint16_t x) { */
//  return (x << 11) | (x & 0x07E0) | (x >> 11);
//}
/*----------------------------------------------------------------------------*/


/******************************************************************************/
// This is a routine that uses general purpose io pins in order to mimic SPI functions
// according to ST7789 chip data sheet, ic use SPI communication protocol. SPI 
// clock polarity should be HIGH IDLE. And data sampling must be at low to high 
// edge of the clock signal.
// SCL and SDA pins definitions are in conf_pin.h and configurations are handled in 
// conf_pin.c 
// Actually this is a slow routine. And should be replaced with a genuine SPI code
void send_data(uint8_t VL){
    #ifdef command_data_via_IO
        SSCL = 1;            // we set the clock line HIGH at the start.
        __delay_us(1);

            if (VL & 0x80)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x40)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x20)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x10)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x08)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x04)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x02)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);

            if (VL & 0x01)
                SSDA=1;
            else
                SSDA=0;
            __delay_us(1);

            pulse(SSCL);
    #endif
    #ifdef command_data_via_SPI
            send_SPI_data(VL);
    #endif
}
/******************************************************************************/


/*----------------------------------------------------------------------------*/
void writecommand(uint8_t c){
    DC = 0;
    send_data(c);
}
void writedata(uint8_t c){
    DC = 1;
    send_data(c);
}
/*----------------------------------------------------------------------------*/



/******************************************************************************/
// This function takes commands, arguments of commands and required delay time 
// from cmd_240x240[] array. And thanks to writecommand and writedata functions
// configure the LCD.
//uint8_t displayInit(uint8_t* cmd_ptr){
//    uint8_t numCommands,numArgs;
//    uint16_t ms;
//    numCommands = *cmd_ptr;
//    while(numCommands--){
//        cmd_ptr++;
////        printf("Command %d code is %d \n",9-numCommands,*cmd_ptr);   
//        writecommand(*cmd_ptr);
//        cmd_ptr++;
//        numArgs = *cmd_ptr;
////        printf("Number of arguments for the current command is : %d \n",numArgs);
//        while(numArgs){
//            cmd_ptr++;
////            printf("Code of data is %d\n",*cmd_ptr);
//            writedata(*cmd_ptr);
//            numArgs--;
//        }
//        cmd_ptr++;
//        ms = *cmd_ptr;
////        printf("Time delay for the current command is : %d \n\n",ms);
//        __delay_ms(ms);
//    }
//
//    return 0;
//}
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/*_xstart ve _ystart parametrelerinin degerlerini ayarliyor
 _xstart ve _ystart parametreleri */
//void setRotation(uint8_t m) {
//  writecommand(ST7789_MADCTL);
//  uint8_t rotation;
//  rotation = m % 4; // can't be higher than 3
//  switch (rotation) {
//   case 0:
//     writedata(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
//
//     _xstart = _colstart;
//     _ystart = _rowstart;
//     break;
//   case 1:
//     writedata(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
//
//     _ystart = _colstart;
//     _xstart = _rowstart;
//     break;
//  case 2:
//     writedata(ST7789_MADCTL_RGB);
// 
//     _xstart = _colstart;
//     _ystart = _rowstart;
//     break;
//
//   case 3:
//     writedata(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
//
//     _ystart = _colstart;
//     _xstart = _rowstart;
//     break;
//  }
//}
/*----------------------------------------------------------------------------*/



/******************************************************************************/
/*This function sets the CASET(Column Address Set) and RASET (Row Address Set)
 registers. Those register values determine the pixel address that is going to be
 written.
 After determination of the address the next step is writing graphic data 
 to the display ram. The first part of this writing to RAM operation is placed 
 in the last code of this setAddrWindow ==> writecommand(ST7789_RAMWR); The data subsequent 
 to this code must be the content of RAM data.
 Usually in all the high level functions after a reference to the setAddrWindow
 function there place a writedata command.*/
//void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
//  uint16_t x_start, x_end, y_start, y_end;  
//  x_start = x0 + _xstart; 
//  x_end = x1 + _xstart;
//  y_start = y0 + _ystart; 
//  y_end = y1 + _ystart;
//  
//
//  writecommand(ST7789_CASET); // Column addr set
//  writedata(x_start >> 8);
//  writedata(x_start & 0xFF);     // XSTART 
//  writedata(x_end >> 8);
//  writedata(x_end & 0xFF);     // XEND
//
//  writecommand(ST7789_RASET); // Row addr set
//  writedata(y_start >> 8);
//  writedata(y_start & 0xFF);     // YSTART
//  writedata(y_end >> 8);
//  writedata(y_end & 0xFF);     // YEND
//
//  writecommand(ST7789_RAMWR); // write to RAM
//}
/******************************************************************************/



/******************************************************************************/
//void pushColor(uint16_t color) {
//    writedata(color>>8);
//    writedata(color);
//}
/******************************************************************************/



/******************************************************************************/
//void drawPixel(int16_t x, int16_t y, uint16_t color) {
//
//  if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;
//
//  setAddrWindow(x,y,x+1,y+1);
//
//  writedata(color >> 8);
//  writedata(color);
//
//  
//}
/******************************************************************************/



/******************************************************************************/
//void drawFastVLine(int16_t x, int16_t y, int16_t h,uint16_t color) {
////   Rudimentary clipping
//  if((x >= _width) || (y >= _height)) return;
//  if((y+h-1) >= _height) h = _height-y;
//  setAddrWindow(x, y, x, y+h-1);
//
//  hi = color >> 8;
//  lo = color;
//
//  while (h--) {
//    writedata(hi);
//    writedata(lo);
//  }
//}
/******************************************************************************/



/******************************************************************************/
//void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
//
////   Rudimentary clipping
//  if((x >= _width) || (y >= _height)) return;
//  if((x+w-1) >= _width)  w = _width-x;
//  setAddrWindow(x, y, x+w-1, y);
//
//  hi = color >> 8;
//  lo = color;
//
//  while (w--) {
//    writedata(hi);
//    writedata(lo);
//  }
//
//
//
//}
/******************************************************************************/



/******************************************************************************/
//void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
//
////   rudimentary clipping (drawChar w/big text requires this)
//  if((x >= _width) || (y >= _height)) return;
//  if((x + w - 1) >= _width)  w = _width  - x;
//  if((y + h - 1) >= _height) h = _height - y;
//
//  setAddrWindow(x, y, x+w-1, y+h-1);
//
//  hi = color >> 8;
//  lo = color;
//
//  for(y=h; y>0; y--) {
//    for(x=w; x>0; x--) {
//      writedata(hi);
//      writedata(lo);
//    }
//  }
//}
/******************************************************************************/



/******************************************************************************/
//uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
//  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
//}
/******************************************************************************/



/******************************************************************************/
//void invertDisplay(bool i) {
//  writecommand(i ? ST7789_INVON : ST7789_INVOFF);
//}
/******************************************************************************/

                        /*>>>||||||||||||||||<<<*/

/******************************************************************************/
/*This function initiates some global variables that are related to the hardware
 of LDC graphic display.
 Then makes a hard reset
 And finally calls displayInit function so as to configure chip*/
void init(uint16_t width, uint16_t height) {
//    uint8_t *ptr;

//  _colstart = ST7789_240x240_XSTART;
//  _rowstart = ST7789_240x240_YSTART;
//  _height = height;
//  _width = width;

//    RST = 1;
//    __delay_ms(50);
//    RST = 0;
//    __delay_ms(50);
//    RST = 1;
//    __delay_ms(50);


//  displayInit(cmd_240x240);
 
//  setRotation(2);
}
/******************************************************************************/

