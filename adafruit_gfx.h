//mylibraries
#ifndef ADAFRUIT_GFX_H
#define ADAFRUIT_GFX_H


#include "../my_headers/header_definition.h"
#ifdef dspic33_deneme
#include "../../dspic33_deneme.X/project_specific.h"
#endif
#ifdef IR_cam_PIC24f
#include "../../IR_cam_PIC24f.X/project_specific.h"
#endif


#include "stdbool.h"
#include <stdlib.h>
#include "../../my_libraries/my_headers/gfxfont.h"
#include "../../my_libraries/my_headers/ST7789.h"





// void Adafruit_GFX(int16_t w, int16_t h);
 void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                             uint16_t color);
 void startWrite();
 void writePixel(int16_t x, int16_t y, uint16_t color);
 void writeFastVLine(int16_t x, int16_t y, int16_t h,
                                  uint16_t color);
 void writeFastHLine(int16_t x, int16_t y, int16_t w,
                                  uint16_t color) ;
 void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 uint16_t color) ;
 void endWrite();
 void drawFastVLine(int16_t x, int16_t y, int16_t h,
                                 uint16_t color);
 void drawFastHLine(int16_t x, int16_t y, int16_t w,
                                 uint16_t color);
// void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
//                            uint16_t color);
 void fillScreen(uint16_t color);
 void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                            uint16_t color) ;
 void drawCircle(int16_t x0, int16_t y0, int16_t r,
                              uint16_t color) ;
 void drawCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                    uint8_t cornername, uint16_t color) ;
 void fillCircle(int16_t x0, int16_t y0, int16_t r,
                              uint16_t color);
 void fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
                                    uint8_t corners, int16_t delta,
                                    uint16_t color) ;
 void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                            uint16_t color);
 void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t r, uint16_t color);
 void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
                                 int16_t r, uint16_t color) ;
 void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color) ;
 void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                int16_t x2, int16_t y2, uint16_t color);
 /* BITMAP / XBITMAP / GRAYSCALE / RGB BITMAP FUNCTIONS ---------------------*/
 /* BITMAP / XBITMAP / GRAYSCALE / RGB BITMAP FUNCTIONS ---------------------*/
 void drawBitmap_PROGMEM_FGcl(int16_t x, int16_t y, const uint8_t bitmap[],
                              int16_t w, int16_t h, uint16_t color);
 void drawBitmap_PROGMEM_FGcl_BGcl(int16_t x, int16_t y, const uint8_t bitmap[],
                              int16_t w, int16_t h, uint16_t color,
                              uint16_t bg) ;
 void drawBitmap_RAM_FGcl(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                              int16_t h, uint16_t color);
void drawBitmap_RAM_FGcl_BGcl(int16_t x, int16_t y, uint8_t *bitmap, int16_t w,
                                  int16_t h, uint16_t color, uint16_t bg) ;
void drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
                               int16_t w, int16_t h, uint16_t color) ;
void drawGrayscaleBitmap_PROGMEM(int16_t x, int16_t y,
                                       const uint8_t bitmap[], int16_t w,
                                       int16_t h);
void drawGrayscaleBitmap_RAM(int16_t x, int16_t y, uint8_t *bitmap,
                                       int16_t w, int16_t h);
void drawGrayscaleBitmap_PROGMEM_withMASK(int16_t x, int16_t y,
                                       const uint8_t bitmap[],
                                       const uint8_t mask[], int16_t w,
                                       int16_t h);
void drawGrayscaleBitmap_RAM_withMASK(int16_t x, int16_t y, uint8_t *bitmap,
                                       uint8_t *mask, int16_t w, int16_t h) ;
void drawRGBBitmap_PROGMEM(int16_t x, int16_t y, const uint16_t bitmap[],
                                 int16_t w, int16_t h);
void drawRGBBitmap_RAM(int16_t x, int16_t y, uint16_t *bitmap,
                                 int16_t w, int16_t h) ;
void drawRGBBitmap_PROGMEM_withMASK(int16_t x, int16_t y, const uint16_t bitmap[],
                                 const uint8_t mask[], int16_t w, int16_t h) ;
void drawRGBBitmap_RAM_withMASK(int16_t x, int16_t y, uint16_t *bitmap,
                                 uint8_t *mask, int16_t w, int16_t h) ;
/* TEXT- AND CHARACTER-HANDLING FUNCTIONS ----------------------------------*/
void drawChar_originalsize(int16_t x, int16_t y, unsigned char c,
                            uint16_t color, uint16_t bg, uint8_t size) ;
void drawChar(int16_t x, int16_t y, unsigned char c,
                            uint16_t color, uint16_t bg, uint8_t size_x,
                            uint8_t size_y);
uint8_t write(uint8_t c);
void setTextSize_Magnify(uint8_t s) ;
void setTextSize_Incr(uint8_t s_x, uint8_t s_y) ;
//void setRotation(uint8_t x) ;
void setFont(const GFXfont *f);
void charBounds(unsigned char c, int16_t *x, int16_t *y,
                              int16_t *minx, int16_t *miny, int16_t *maxx,
                              int16_t *maxy) ;
void getTextBounds(const char *str, int16_t x, int16_t y,
                                 int16_t *x1, int16_t *y1, uint16_t *w,
                                 uint16_t *h);
/*void getTextBounds*/
/*void getTextBounds*/
//void invertDisplay(bool i) ;



 #endif




