//mylibraries
#ifndef CONF_PIN_H
#define CONF_PIN_H


#include "../my_headers/header_definition.h"
#ifdef IR_cam_PIC24f
#include "../../IR_cam_PIC24f.X/project_specific.h"
#endif
#ifdef pic24f_deneme_2
#include "../../pic24f_deneme_2.X/project_specific.h"
#endif
#ifdef pic24f_lcd_st7789
#include "../../pic24f_lcd_st7789.X/project_specific.h"
#endif
#ifdef dspic33_deneme
#include "../../dspic33_deneme.X/project_specific.h"
#endif
#ifdef MAFS
#include "../../MAFS.X/project_specific.h"
#endif
#ifdef DATAACQ
#include "../../DATAACQ.X/project_specific.h"
#endif
#ifdef my_OV7670
#include "../../my_OV7670.X/project_specific.h"
#endif
#ifdef Bedheater_LCD
#include "../../pic18f_projects/Bedheater_LCD.X/project_specific.h"
#endif
#ifdef DATAACQ
#include "../../auo_lcd.X/project_specific.h"
#endif
#ifdef auo_lcd
#include "../../auo_lcd.X/project_specific.h"
#endif
#ifdef _93C46_eprom
#include "../../_93C46_eprom.X/project_specific.h"
#endif



#ifdef PIC24FJ64GA004
    #ifdef command_data_via_SPI
        #define DC LATBbits.LATB7 //PIN43(of_pic)-->PIN3(of_explorer16/32board)
        #define RST LATBbits.LATB6 //PIN42(of_pic)-->PIN4(of_explorer16/32board)
    #endif
    #ifdef command_data_via_IO
        #define DC LATBbits.LATB7 //PIN43(of_pic)-->PIN3(of_explorer16/32board)
        #define RST LATBbits.LATB6 //PIN42(of_pic)-->PIN4(of_explorer16/32board)
        #define SCL LATBbits.LATB5 //PIN41(of_pic)-->PIN5(of_explorer16/32board)
        #define SDA LATCbits.LATC5 //PIN38(of_pic)-->PIN12(of_explorer16/32board)
    #endif
#define LED LATAbits.LATA10
#endif
#ifdef PIM_dsPIC33EP512MU810_ST7789_SPI
                #define RST LATBbits.LATB15 //PIN44 of explorer16/32
                #define DC  LATBbits.LATB14 //PIN43 of explorer16/32
                      //SCK------------------>PIN53 of explorer16/32
                      //SDO------------------>PIN52 of explorer16/32
#endif
#ifdef PIC24FJ128GA306
    #ifdef MAFS
            #define IN1_P27 LATBbits.LATB12
            #define IN2_P30 LATBbits.LATB15
            #define IN3_P31 LATFbits.LATF4 
            #define IN4_P32 LATFbits.LATF5 
    #endif
    #ifdef PIC24FJ128GA306_Serial_4pin_ST7789 //defined in project_specific of IR_cam_PIC24f
    #ifdef command_data_via_IO
                #define RST LATBbits.LATB15 //PIN30
                #define DC  LATBbits.LATB14 //PIN29
                #define SCL LATBbits.LATB13 //PIN28
                #define SDA LATBbits.LATB12 //PIN27
    #endif
    #ifdef command_data_via_SPI
                #define RST LATBbits.LATB15 //PIN30
                #define DC  LATBbits.LATB14 //PIN29
                          //SCK-------------->PIN34
                          //SDA-------------->PIN42
    #endif
    #define INPUT_PIN43 PORTDbits.RD9
    #define OUTPUT_PIN44 LATDbits.LATD10 
    #define OUTPUT_PIN35 LATFbits.LATF6 
#endif

#endif
#ifdef PIM_dsPIC33EP512MU810
    #ifdef my_OV7670
        #define PIN44_O LATBbits.LATB15 //PIN44 of explorer16/32
        #define PIN43_O  LATBbits.LATB14 //PIN43 of explorer16/32
        #define S6      PORTDbits.RD7 //S6 pushbutton of exp16/32
        #define S5      PORTAbits.RA7 //S5 pushbutton of exp16/32
        #define S4      PORTDbits.RD13 //S4 pushbutton of exp16/32
        #define S3      PORTDbits.RD6 //S3 pushbutton of exp16/32
        #define LED3    LATAbits.LATA0 //LED3 of exp16/32
        #define LED4    LATAbits.LATA1 //LED4 of exp16/32
        #define D7      PORTBbits.RB5 //D7bit of OV7670
        #define D6      PORTBbits.RB4 //D6bit of OV7670
        #define D5      PORTBbits.RB3 //D5bit of OV7670
        #define D4      PORTBbits.RB2 //D4bit of OV7670
        #define D3      PORTBbits.RB1 //D3bit of OV7670
        #define D2      PORTBbits.RB0 //D2bit of OV7670
        #define D1      PORTBbits.RB9 //D1bit of OV7670
        #define D0      PORTBbits.RB8 //D0bit of OV7670
        #define HREF    PORTBbits.RB10 //HREF of OV7670
        #define VSYNC   PORTBbits.RB11 //VSYNC of OV7670
        #define PCLK    PORTBbits.RB12 //PCLK of OV7670
        #define CS1     PORTDbits.RD11 //CS1 of PMP
        #define PMWR    PORTDbits.RD4 //PMWR of PMP
        #define PMRD    PORTDbits.RD5 //PMRD of PMP
        #define RST     LATCbits.LATC1//RST  of LCD_ST7789
        #define DC      LATCbits.LATC2//DC   of LCD_ST7789
        #define SSCL     LATCbits.LATC3//SCL  of LCD_ST7789
        #define SSDA     LATCbits.LATC4//SDA  of LCD_ST7789

    #endif
    #ifdef auo_lcd
        #define PIN44_O LATBbits.LATB15 //PIN44 of explorer16/32
        #define PIN43_O  LATBbits.LATB14 //PIN43 of explorer16/32
        #define S6      PORTDbits.RD7 //S6 pushbutton of exp16/32
        #define S5      PORTAbits.RA7 //S5 pushbutton of exp16/32
        #define S4      PORTDbits.RD13 //S4 pushbutton of exp16/32
        #define S3      PORTDbits.RD6 //S3 pushbutton of exp16/32
        #define LED3    LATAbits.LATA0 //LED3 of exp16/32
        #define LED4    LATAbits.LATA1 //LED4 of exp16/32
        #define D7      PORTBbits.RB5 //D7bit of OV7670
        #define D6      PORTBbits.RB4 //D6bit of OV7670
        #define D5      PORTBbits.RB3 //D5bit of OV7670
        #define D4      PORTBbits.RB2 //D4bit of OV7670
        #define D3      PORTBbits.RB1 //D3bit of OV7670
        #define D2      PORTBbits.RB0 //D2bit of OV7670
        #define D1      PORTBbits.RB9 //D1bit of OV7670
        #define D0      PORTBbits.RB8 //D0bit of OV7670
        #define HREF    PORTBbits.RB10 //HREF of OV7670
        #define VSYNC   PORTBbits.RB11 //VSYNC of OV7670
        #define PCLK    PORTBbits.RB12 //PCLK of OV7670
        #define CS1     PORTDbits.RD11 //CS1 of PMP
        #define PMWR    PORTDbits.RD4 //PMWR of PMP
        #define PMRD    PORTDbits.RD5 //PMRD of PMP
        #define CLK_IN  PORTAbits.RA10 
    #endif
    #ifdef dspic33_deneme
            // PIN6  = LATC1-----> RST for LCD_ST7789
            // PIN7  = LATC2-----> DC for LCD_ST7789
            // PIN8  = LATC3-----> SCL for LCD_ST7789
            // PIN9  = LATC4-----> SDA for LCD_ST7789
            #define RST LATCbits.LATC1
            #define DC LATCbits.LATC2
            #define SSCL LATCbits.LATC3
            #define SSDA LATCbits.LATC4
        #endif
    #ifdef _93C46_eprom
        #define pCS LATAbits.LATA0 // TMS/RP16/RA0
        #define pSK LATAbits.LATA1 // TCK/RP17/RA1
        #define pDI LATAbits.LATA2 //ASCL2/RP18/RA2
        #define pDO PORTAbits.RA3// ASDA2/RP19/RA3 
    #endif
#endif
#ifdef PIC18F4620
    #ifdef Bedheater_LCD
        #define DATA_PORT LATD
        #define RS      LATCbits.LATC0
        #define RW      LATCbits.LATC1
        #define EN      LATCbits.LATC2
        #define CS1     LATCbits.LATC4
        #define CS2     LATCbits.LATC5
        #define RES     LATEbits.LATE2
    #endif
#endif

void configure_digital_IO_ports(void);
void test_digital_IO_ports(void);

#endif
