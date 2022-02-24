//mylibraries



#include "../../my_libraries/my_headers/conf_pin.h"

void configure_digital_IO_ports(){
    #ifdef PIC24FJ128GA306_16bit_SSD1289
        //16 digital output for UTFT data pins
        // 4 digital output for UTFT control pins 
    
        ANSBbits.ANSB2 = 0;
        ANSBbits.ANSB3 = 0;
        ANSBbits.ANSB4 = 0;
        ANSBbits.ANSB5 = 0;
        ANSBbits.ANSB12 = 0; 
        ANSBbits.ANSB13 = 0;
        ANSBbits.ANSB14 = 0;
        ANSBbits.ANSB15 = 0;
                              //......-->TFT PIN NAMES---PIC24FJ128GA306 PIN NUMBER
        TRISBbits.TRISB2 = 0; //DATA15-->DB15------------>PIN14
        TRISBbits.TRISB3 = 0; //DATA14-->DB14------------>PIN13
        TRISBbits.TRISB4 = 0; //DATA13-->DB13------------>PIN12
        TRISBbits.TRISB5 = 0; //DATA12-->DB12------------>PIN11
        TRISBbits.TRISB12 = 0;//P_RS---->RS-------------->PIN27
        TRISBbits.TRISB13 = 0;//P_WR---->WR-------------->PIN28
        TRISBbits.TRISB14 = 0;//P_CS---->CS-------------->PIN29
        TRISBbits.TRISB15 = 0;//P_RST--->REST------------>PIN30       
                       //LATD7-->DATA11->DB11------------>PIN55
                       //LATD6-->DATA10->DB10------------>PIN54
                       //LATD5-->DATA9-->DB9------------->PIN53
                       //LATD4-->DATA8-->DB8------------->PIN52
                       //LATD3-->DATA7-->DB7------------->PIN51
                       //LATD2-->DATA6-->DB6------------->PIN50
                       //LATD1-->DATA5-->DB5------------->PIN49
                       //LATD0-->DATA4-->DB4------------->PIN46
                       //LATD11->DATA3-->DB3------------->PIN45
                       //LATD10->DATA2-->DB2------------->PIN44
                       //LATD9-->DATA1-->DB1------------->PIN43
                       //LATD8-->DATA0-->DB0------------->PIN42
        TRISD = 0;
                     
        #define P_RS LATBbits.LATB12   // P_RS = 0 -> COMMAND  P_RS = 1 -> DATA
        #define P_WR LATBbits.LATB13   // P_WR = 0 -> WRITE    P_WR = 1 -> DON'T WRITE
        #define P_CS LATBbits.LATB14   // P_CS = 0 -> Chip Select  P_CS = 1 -> DON'T SELECT CHIP
        #define P_RST LATBbits.LATB15  // P_RST = 0 -> Reset system P_RST = 1 -> DON'T RESET system
    #endif
    #ifdef PIM_dsPIC33EP512MU810_16bit_SSD1289
        ANSELB = 0x80F0; //RB0:3 - RB8:11 - RB12:14 are digital io
        TRISB = 0x80F0;  //RB0:3 - RB8:11 - RB12:14 are data output
        TRISD = 0x26F0;  //RD0:3 - RD8 are data output RD11-12-14-15 control output
                     // 0010 0110 1111 0000
        #define P_RS LATDbits.LATD14
        #define P_WR LATDbits.LATD15
        #define P_CS LATDbits.LATD11
        #define P_RST LATDbits.LATD12
    #endif
    #ifdef PIM_dsPIC33EP512MU810_ST7789_SPI
        ANSELBbits.ANSB15 = 0; //RB15 as digital
        ANSELBbits.ANSB14 = 0; //RB14 as digital
        
        TRISBbits.TRISB15 = 0; //RB15 as digital_output
        TRISBbits.TRISB14 = 0; //RB14 as digital_output
    #endif
    #ifdef PIC24FJ64GA004  
        #ifdef command_data_via_IO
            TRISBbits.TRISB7 = 0; //RB7-->PIN43(of_pic)-->PIN3(of_explorer16/32board)
            TRISBbits.TRISB6 = 0; //RB6-->PIN42(of_pic)-->PIN4(of_explorer16/32board)
            TRISBbits.TRISB5 = 0; //RB5-->PIN41(of_pic)-->PIN5(of_explorer16/32board)
            TRISCbits.TRISC5 = 0; //RC5-->PIN38(of_pic)-->PIN12(of_explorer16/32board)
        #endif
        #ifdef command_data_via_SPI
            TRISBbits.TRISB7 = 0; //RB7-->PIN43(of_pic)-->PIN3(of_explorer16/32board)
            #define DC LATBbits.LATB7 
            TRISBbits.TRISB6 = 0; //RB6-->PIN42(of_pic)-->PIN4(of_explorer16/32board)
            #define RST LATBbits.LATB6
            // AN9/RP15(=SCK1)/C11/PMPCS1/RB15 ->> pin55 of explorer 16/32
            // AN6/RP16(=SDO1)/CN8/RC0 is configured as digital ->> pin53 of explorer 16/32
            
        #endif
        TRISAbits.TRISA10 = 0;
            
    #endif
    #ifdef PIC24F16KA102
        #ifdef MAFS //Project MAFS
            AD1PCFGbits.PCFG0 = 1;
            AD1PCFGbits.PCFG1 = 1;
            TRISAbits.TRISA0 = 0;
            TRISAbits.TRISA1 = 0;
        #endif
#endif
    #ifdef PIC24FJ128GA306
        #ifdef MAFS
            ANSBbits.ANSB12 = 0;
            ANSBbits.ANSB15 = 0;
            
            TRISBbits.TRISB12 = 0; //PIN27 digital output
            TRISBbits.TRISB15 = 0; //PIN30 digital output
            TRISFbits.TRISF4 = 0;  //PIN31 digital output
            TRISFbits.TRISF5 = 0; //PIN32 digital output
        #endif
        #ifdef pic24f_deneme_2
            ANSBbits.ANSB12 = 0;
            ANSBbits.ANSB15 = 0;
            TRISBbits.TRISB12 = 0; //PIN27
            TRISBbits.TRISB15 = 0; //PIN30
        #endif
        #ifdef IR_cam_PIC24f
            #ifdef PIC24FJ128GA306_Serial_4pin_ST7789
                /*GENERAL PURPOSE IO PIN CONFIGURATIONS*/
                TRISDbits.TRISD9 = 1;   //PIN43
                TRISDbits.TRISD10 = 0;  //PIN44
                TRISFbits.TRISF6 = 0;   //PIN35
                /*UART PIN CONFIGURATIONS*/
                #ifdef command_data_via_IO
                    ANSBbits.ANSB12 = 0; 
                    ANSBbits.ANSB13 = 0;
                    ANSBbits.ANSB14 = 0;
                    ANSBbits.ANSB15 = 0;

                    TRISBbits.TRISB12 = 0;//SDA-------------->PIN27
                    TRISBbits.TRISB13 = 0;//SCL-------------->PIN28
                    TRISBbits.TRISB14 = 0;//DC--------------->PIN29
                    TRISBbits.TRISB15 = 0;//RST-------------->PIN30  
                #endif
                #ifdef command_data_via_SPI
                    ANSBbits.ANSB14 = 0;
                    ANSBbits.ANSB15 = 0;
                    TRISBbits.TRISB14 = 0;//DC--------------->PIN29
                    TRISBbits.TRISB15 = 0;//RST-------------->PIN30  
                                          //SCK-------------->PIN34
                                          //SDA-------------->PIN42

                #endif
        #endif
        #endif

    #endif
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef my_OV7670
            ANSELBbits.ANSB15 = 0; //RB15 as digital
            ANSELBbits.ANSB14 = 0; //RB14 as digital
            ANSELBbits.ANSB5 = 0; //RB5 as digital
            ANSELBbits.ANSB4 = 0; //RB4 as digital
            ANSELBbits.ANSB3 = 0; //RB3 as digital
            ANSELBbits.ANSB2 = 0; //RB2 as digital
            ANSELBbits.ANSB1 = 0; //RB2 as digital
            ANSELBbits.ANSB8 = 0; //RB8 as digital
            ANSELBbits.ANSB9 = 0; //RB9 as digital
            ANSELBbits.ANSB10 = 0; //RB10 as digital
            ANSELBbits.ANSB11 = 0; //RB11 as digital
            ANSELBbits.ANSB12 = 0; //RB12 as digital
            ANSELBbits.ANSB0 = 0; //RB2 as digital
            ANSELAbits.ANSA7 = 0; //RA7 as digital
            ANSELDbits.ANSD7 = 0; //RD7 as digital
            ANSELDbits.ANSD6 = 0; //RD6 as digital
            ANSELCbits.ANSC1 = 0; //RC1 as digital
            ANSELCbits.ANSC2 = 0; //RC2 as digital
            ANSELCbits.ANSC3 = 0; //RC3 as digital
            ANSELCbits.ANSC4 = 0; //RC4 as digital

            TRISBbits.TRISB15 = 0; //RB15 as digital_output
            TRISBbits.TRISB14 = 0; //RB14 as digital_output
            TRISBbits.TRISB5 = 1; //RB5 as digital_input
            TRISBbits.TRISB4 = 1; //RB4 as digital_input
            TRISBbits.TRISB3 = 1; //RB3 as digital_input
            TRISBbits.TRISB2 = 1; //RB2 as digital_input
            TRISBbits.TRISB1 = 1; //RB1 as digital_input
            TRISBbits.TRISB0 = 1; //RB0 as digital_input
            TRISBbits.TRISB8 = 1; //RB8 as digital_input
            TRISBbits.TRISB9 = 1; //RB9 as digital_input
            TRISBbits.TRISB10 = 1; //RB10 as digital_input
            TRISBbits.TRISB11 = 1; //RB11 as digital_input
            TRISBbits.TRISB12 = 1; //RB12 as digital_input
            TRISAbits.TRISA0 = 0;  //RA0 as digital output LED3 on exp16/32
            TRISAbits.TRISA1 = 0;  //RA1 as digital output LED4 on exp16/32
            
            TRISDbits.TRISD7 = 1;  //S3 on exp16/32
            TRISDbits.TRISD13 = 1; //S4 on exp16/32
            TRISDbits.TRISD7 = 1;  //S6 on exp16/32
            TRISAbits.TRISA7 = 1;  //S5 on exp16/32
            
            TRISCbits.TRISC1 = 0;
            TRISCbits.TRISC2 = 0;
            TRISCbits.TRISC3 = 0;
            TRISCbits.TRISC4 = 0;
            

            
            /*unlock registers*/__builtin_write_OSCCONL(OSCCON & ~(1<<6));
            RPOR0bits.RP64R = 0b110001;     // chipin 72nci pinindeki RP64 pinine REFCLK fonksiyonu tanimlandi                
            /*lock registers*/__builtin_write_OSCCONL(OSCCON | ~(1<<6));
            REFOCONbits.ROON = 0;
            REFOCONbits.ROSSLP = 1;
            REFOCONbits.ROSEL = 0;          // SystemClock=140MHz
            REFOCONbits.RODIV = 0b0011;    /* Clock -> 140/8 = 17.5Mhz
                                            1111 = Reference clock divided by 32,768
                                            1110 = Reference clock divided by 16,384
                                            1101 = Reference clock divided by 8,192
                                            1100 = Reference clock divided by 4,096
                                            1011 = Reference clock divided by 2,048
                                            1010 = Reference clock divided by 1,024
                                            1001 = Reference clock divided by 512
                                            1000 = Reference clock divided by 256   
                                            0111 = Reference clock divided by 128
                                            0110 = Reference clock divided by 64
                                            0101 = Reference clock divided by 32
                                            0100 = Reference clock divided by 16
                                            0011 = Reference clock divided by 8
                                            0010 = Reference clock divided by 4
                                            0001 = Reference clock divided by 2
                                            0000 = Reference clock
*/
                                        
            REFOCONbits.ROON = 1;
     
        #endif
        #ifdef auo_lcd     
            ANSELB = 0;
            ANSELD = 0;
            TRISB = 0;
            TRISD = 0;
            ANSELAbits.ANSA10 = 0;
            TRISAbits.TRISA10 = 1;
            CNENAbits.CNIEA10 =1;
            IEC1bits.CNIE = 1;
            IFS1bits.CNIF = 0;
            /*unlock registers*/__builtin_write_OSCCONL(OSCCON & ~(1<<6));
            //RPOR0bits.RP64R = 0b110001;     // chipin 72nci pinindeki RP64 pinine REFCLK fonksiyonu tanimlandi                
            RPOR14bits.RP125R = 0b110001;     // chipin 97nci pinindeki RP125 pinine REFCLK fonksiyonu tanimlandi                
            /*lock registers*/__builtin_write_OSCCONL(OSCCON | ~(1<<6));
            REFOCONbits.ROON = 0;
            REFOCONbits.ROSSLP = 1;
            REFOCONbits.ROSEL = 0;          // SystemClock=140MHz
            REFOCONbits.RODIV = 0b1111;          /* Clock -> 140/4 = 35 Mhz
                                            1111 = Reference clock divided by 32,768
                                            1110 = Reference clock divided by 16,384
                                            1101 = Reference clock divided by 8,192
                                            1100 = Reference clock divided by 4,096
                                            1011 = Reference clock divided by 2,048
                                            1010 = Reference clock divided by 1,024
                                            1001 = Reference clock divided by 512
                                            1000 = Reference clock divided by 256   
                                            0111 = Reference clock divided by 128
                                            0110 = Reference clock divided by 64
                                            0101 = Reference clock divided by 32
                                            0100 = Reference clock divided by 16
                                            0011 = Reference clock divided by 8
                                            0010 = Reference clock divided by 4
                                            0001 = Reference clock divided by 2
                                            0000 = Reference clock
*/
                                        
            REFOCONbits.ROON = 1;
     
        #endif
        #ifdef dspic33_deneme
            ANSELCbits.ANSC1 = 0;
            ANSELCbits.ANSC2 = 0;
            ANSELCbits.ANSC3 = 0;
            ANSELCbits.ANSC4 = 0;

            TRISCbits.TRISC1 = 0;
            TRISCbits.TRISC2 = 0;
            TRISCbits.TRISC3 = 0;
            TRISCbits.TRISC4 = 0;
            
            LATCbits.LATC1 = 0;
            LATCbits.LATC2 = 0;
            LATCbits.LATC3 = 1;
            LATCbits.LATC4 = 0;

            // PIN6  = LATC1-----> RST for LCD_ST7789
            // PIN7  = LATC2-----> DC for LCD_ST7789
            // PIN8  = LATC3-----> SCL for LCD_ST7789
            // PIN9  = LATC4-----> SDA for LCD_ST7789
            
            /*unlock registers*/__builtin_write_OSCCONL(OSCCON & ~(1<<6));
            RPOR0bits.RP64R = 0b110001;     // chipin 72nci pinindeki RP64 pinine REFCLK fonksiyonu tanimlandi                
            /*lock registers*/__builtin_write_OSCCONL(OSCCON | ~(1<<6));
            REFOCONbits.ROON = 0;
            REFOCONbits.ROSSLP = 1;
            REFOCONbits.ROSEL = 0;          // SystemClock=140MHz
            REFOCONbits.RODIV = 0b0001;    /* Clock -> 140/8 = 17.5Mhz
                                            1111 = Reference clock divided by 32,768
                                            1110 = Reference clock divided by 16,384
                                            1101 = Reference clock divided by 8,192
                                            1100 = Reference clock divided by 4,096
                                            1011 = Reference clock divided by 2,048
                                            1010 = Reference clock divided by 1,024
                                            1001 = Reference clock divided by 512
                                            1000 = Reference clock divided by 256   
                                            0111 = Reference clock divided by 128
                                            0110 = Reference clock divided by 64
                                            0101 = Reference clock divided by 32
                                            0100 = Reference clock divided by 16
                                            0011 = Reference clock divided by 8
                                            0010 = Reference clock divided by 4
                                            0001 = Reference clock divided by 2
                                            0000 = Reference clock
*/
                                        
            REFOCONbits.ROON = 1;
        #endif
        #ifdef _93C46_eprom
            TRISAbits.TRISA0 = 0; //pCS
            TRISAbits.TRISA1 = 0; //pSK
            TRISAbits.TRISA2 = 0; //pDI
            TRISAbits.TRISA3 = 1; //pDO
            
            LATAbits.LATA0 = 0;
            LATAbits.LATA1 = 0;
            LATAbits.LATA2 = 0;
                    
            
        #endif
    #endif
    #ifdef PIC18F4620
        #ifdef Bedheater_LCD
            
            ADCON1 = 0x0F;
            
            PORTD = 0;
            LATD = 0;
            TRISD = 0;          //DATA_PORT
            
            PORTC = 0;
            LATC = 0;
            TRISC = 0;
            
            PORTE = 0;
            LATE = 0;
            TRISE = 0;  //RES
                    

        #endif
    #endif
    
}

/*TEST ROUTINES FOR DIGITAL IO SETTINGS*/
/*START*/
//void test_digital_IO_ports(){
//    #ifdef PIM_dsPIC33EP512MU810
//        #ifdef _93C46_eprom
//        T1CONbits.TON = 0; //disable timer
//        T1CONbits.TCS = 0; //internal instruction clock cycle
//        T1CONbits.TGATE = 0; //disable gated timer
//        T1CONbits.TCKPS = 0b011; //select 1:8
//        TMR1 = 0; // HER CLK CYCLEDA TMR1 REGISTERI 1 ARTACAK
//        PR1 = 10; // TMR1=PR1 OLDUGUNDA INTERRUPT FLAG CEKILECEK
//        
//        IPC0bits.T1IP = 0x01; //set timer1 interrupt priority level
//        IFS0bits.T1IF = 0;      // clear timer1 interrupt flag
//        IEC0bits.IC1IE = 1; //enable timer1 interrupt
//        
//        TRISAbits.TRISA0 = 0; //pCS
//        TRISAbits.TRISA1 = 0; //pSK
//        TRISAbits.TRISA2 = 0; //pDI // TEST AMACIYLA BU PIN OUTPUT OLARAK AYARLANDI
//        TRISAbits.TRISA3 = 0; //pDO
//        
//        LATAbits.LATA0=1; 
//        LATAbits.LATA1=1; 
//        LATAbits.LATA2=1; 
//        LATAbits.LATA3=1; 
//        
//        T1CONbits.TON = 1; // start timer
//        #endif
//    #endif
//
//
//
//}
//void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//{
//    /* Interrupt Service Routine code goes here */
//    IFS0bits.T1IF = 0; //Clear Timer1 interrupt flag
//    LATAbits.LATA0^=1; 
//    LATAbits.LATA1^=1; 
//    LATAbits.LATA2^=1; 
//    LATAbits.LATA3^=1; 
//}
/*END*/



