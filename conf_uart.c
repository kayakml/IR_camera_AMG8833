//dikkat mylibraries dosyasi icinde

#include "../my_headers/conf_clock.h"
#include "../my_headers/conf_uart.h"
#include <stdbool.h>
#ifndef UART_VER_2
#ifdef PIM_dsPIC33EP512MU810
    void configure_uart(void){
        #ifdef _dsPIC33EP512MU810_uart1
            #ifdef Control_Register_Bit_Poll
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));
                RPINR18bits.U1RXR = 0b1100100;  // U1RX fonksiyonu chipin 49ncu pinindeki RP100 pinine tanimlandi
                RPOR9bits.RP101R = 0b00001;     // chipin 50nci pinindeki RP101 pinine U1TX fonksiyonu tanimlandi                
                //lock registers
                __builtin_write_OSCCONL(OSCCON | ~(1<<6));
                U1MODEbits.BRGH = 1;
                U1BRG = BRGVAL1;
                U1MODEbits.UARTEN = 1;
                U1MODEbits.STSEL = 0; //1 stop bit
                U1STAbits.UTXISEL1 = 0;
                U1STAbits.UTXISEL0 = 1;
                U1STAbits.UTXEN = 1;
                IFS0bits.U1TXIF = 0;
                U1MODEbits.BRGH = 1;
            #endif
            #ifdef Interrupt_Flag_Poll
                ..//
            #endif
            #ifdef Interrupt_Enable
                //...
            #endif
        #endif         
        #ifdef _dsPIC33EP512MU810_uart2
            #ifdef Control_Register_Bit_Poll
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));
                RPINR19bits.U2RXR = 109;     // U2RX fonksiyonu chipin 39ncu pinindeki RP109 pinine tanimlandi/RF4
                RPOR11bits.RP108R = 0b000011;// chipin 40nci pinindeki RP108 pinine U2TX fonksiyonu tanimlandi/RF5
                //lock registers
                __builtin_write_OSCCONL(OSCCON | ~(1<<6));
                U2MODEbits.BRGH = 1;
                U2BRG = BRGVAL2;
                U2MODEbits.UARTEN = 1;
                U2MODEbits.STSEL = 0; //1 stop bit
                U2STAbits.UTXISEL1 = 0;
                U2STAbits.UTXISEL0 = 1;
                U2STAbits.UTXEN = 1;
                IFS1bits.U2TXIF = 0;
            #endif

        //.....

        #endif
    }
    void send_uart_8(uint8_t send_data){
        #ifdef _dsPIC33EP512MU810_uart1
            #ifdef Control_Register_Bit_Poll
                while(TRANSMIT_NOT_READY()){};
                U1TXREG = send_data;
            #endif
        #endif    
    }
    void send_uart2_8(uint8_t send_data){
        #ifdef _dsPIC33EP512MU810_uart2
            #ifdef Control_Register_Bit_Poll
                while(TRANSMIT_NOT_READY()){};
                U2TXREG = send_data;
            #endif
        #endif       
    }
    void outString (const char* message){
        #ifdef _dsPIC33EP512MU810_uart1
            #ifdef Control_Register_Bit_Poll
                while(*message){
                    while (TRANSMIT_NOT_READY()){};
                    send_uart_8(*message);
                    message++;
            #endif
        #endif
     }
   }            
    void outString_uart2 (const char* message){
        #ifdef _dsPIC33EP512MU810_uart2
            #ifdef Control_Register_Bit_Poll
                while(*message){
                    while (TRANSMIT_NOT_READY_uart2()){};
                    send_uart2_8(*message);
                    message++;}
            #endif
        #endif
     
    }            
    void send_data_MPLABVis(uint8_t data){
        #ifdef _dsPIC33EP512MU810_uart1
        #ifdef Control_Register_Bit_Poll
            send_uart_8(0x03);
            send_uart_8(data);
            send_uart_8(0xFC);
        #endif
    #endif
     }
    void send_float_MPLABVis(float data){   
        #ifdef _dsPIC33EP512MU810_uart1
        #ifdef Control_Register_Bit_Poll
        //A float occupies 4 bytes in memory
        // In the following we define a pointer which will point 1 byte data
        // Then we assign the address of our float to the pointer 
        // and we send each time one of 4 byte of float variable
        // after each send we increment the pointer
            unsigned char *chptr;
            chptr = (unsigned char *) &data;

            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0x03;

            while(TRANSMIT_NOT_READY()){};
            U1TXREG = *chptr++;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = *chptr++;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = *chptr++;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = *chptr;

            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0xFC;

        #endif
    #endif
     }
    void outString_to_MPLABVis (const char* message){
         #ifdef _dsPIC33EP512MU810_uart1
        #ifdef Control_Register_Bit_Poll

            while(*message){
            while (TRANSMIT_NOT_READY()){};
            send_data_MPLABVis(*message);
            message++;            
        #endif
    #endif
         }
     }
    uint8_t inChar(void) {
        #ifdef _dsPIC33EP512MU810_uart1
            #ifdef Control_Register_Bit_Poll
                while (!IS_CHAR_READY_UART1())
                return U1RXREG; //read the receive register
            #endif
        #endif
    return U1RXREG;
    }
    uint8_t inString_uart1() {
        #ifdef _dsPIC33EP512MU810_uart1
            #ifdef Control_Register_Bit_Poll
                char *strptr ;
                while (!IS_CHAR_READY_UART1());
                *strptr = U1RXREG;
                strptr++;
                return &strptr[0]; //read the receive register
            #endif
        #endif
    return U1RXREG;
    }
    uint8_t inChar_uart2(void) {
        #ifdef _dsPIC33EP512MU810_uart2
        #ifdef Control_Register_Bit_Poll
            while (!IS_CHAR_READY_UART2())
            return U2RXREG; //read the receive register
        #endif
    #endif
    return U2RXREG;
    }
#endif
#ifdef PIC24F16KA102
/********************************************************/
/*DEFINE OPTIONS FOR PIC24F16KA102*/
    #define PIC24F16KA102_uart1
    //#define _uart2
    //#define Interrupt_Enable
    //#define Interrupt_Flag_Poll
    #define Control_Register_Bit_Poll
/*********************************************************/
/*UART FUCTIONS FOR PIC24F16KA102*/
    void configure_uart(void){
    #ifdef PIC24F16KA102_uart1   // U1TX: PIN_16=U1TX/INT0/CN23/RB7****U1RX: PIN_6=RB2/CN6/U1RX/C2IND/C1INB/AN4
        /* configure U1RX*/
        // Pin configured as digital 
        //comparator module is disabled default
        AD1PCFGbits.PCFG4 = 1 ; 
        /* configure U1TX*/
        //....
        #ifdef Control_Register_Bit_Poll
            #ifdef BRGH_VALUE_HIGH
            U1MODEbits.BRGH = 1;
            #else
            U1MODEbits.BRGH = 0;
            #endif  
            U1BRG = BRGVAL;
            U1MODEbits.UARTEN = 1;
            U1MODEbits.PDSEL = 0; //0: 8 data bits, no parity 1: 8 data bits, even parity, 2:8 data bits, odd parity
            #ifdef ONE_STOP_BIT
            U1MODEbits.STSEL = 0; //number of stop bits 0: 1 stop bit 1:2 stop bit
            #endif
            #ifdef TWO_STOP_BIT
            U1MODEbits.STSEL = 1; //number of stop bits 0: 1 stop bit 1:2 stop bit
            #endif
            U1STAbits.UTXISEL1 = 0; //interrupt will occur ...
            U1STAbits.UTXISEL0 = 1; //...When all the transmission is completed 
            U1STAbits.UTXEN = 1;
            IFS0bits.U1TXIF = 0;
        #endif
        #ifdef Interrupt_Flag_Poll
            ..//
        #endif
        #ifdef Interrupt_Enable
            //...
        #endif 
    #endif         
    #ifdef PIC24F16KA102_uart2
    //....
    #endif
    }
    void send_uart_8(uint8_t send_data){
        #ifdef Control_Register_Bit_Poll
//            while(TRANSMIT_NOT_READY()){};
//            U1TXREG = send_data;
         while(U1STAbits.UTXBF);
         U1TXREG = send_data;
         while(!U1STAbits.TRMT);
        #endif
    }
    void send_data_MPLABVis(uint8_t data){
        #ifdef Control_Register_Bit_Poll
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0x03;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = data;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0xFC;
        #endif

 }
    void send_float_MPLABVis(float data){ 
        #ifdef Control_Register_Bit_Poll
    //A float occupies 4 bytes in memory
    // In the following we define a pointer which will point 1 byte data
    // Then we assign the address of our float to the pointer 
    // and we send each time one of 4 byte of float variable
    // after each send we increment the pointer
        unsigned char *chptr;
        chptr = (unsigned char *) &data;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0x03;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0xFC;
        
    #endif
 }
    void outString_to_MPLABVis (const char* message){
        #ifdef Control_Register_Bit_Poll
            while(*message){
            while (TRANSMIT_NOT_READY()){};
            send_data_MPLABVis(*message);
            message++;}            
        #endif
    } 
    void outString (const char* message){
        #ifdef Control_Register_Bit_Poll
             while(*message){
             while (TRANSMIT_NOT_READY()){};
             send_uart_8(*message);
             message++; }
        #endif
    }
    uint8_t inChar() {
        #ifdef Control_Register_Bit_Poll
            while (!IS_CHAR_READY_UART1())
        #endif
        return U1RXREG; //read the receive register
    }
    void print_8x8_table_MPLABVis(uint8_t *ptr){
    uint8_t i,row,col;
    row = 0; 
    col = 0;
    for (i=0;i<64;i++){
        

             
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             outString_to_MPLABVis(",");

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             
             outString_to_MPLABVis("\t");
             
             
             
             col ++; 
             if (col == 8) {
                 outString_to_MPLABVis("\n");
                 col = 0; 
                 row ++;
                 if (row == 8){
                 outString_to_MPLABVis("\n\n");
                 outString_to_MPLABVis("TABLE 8X8\n");
                 }
             }
    }
    
   
}
#endif
#ifdef PIC24FJ128GA306
/********************************************************/
/*DEFINE OPTIONS FOR PIC24FJ128GA306*/
    //#define Interrupt_Enable
    //#define Interrupt_Flag_Poll
    #define Control_Register_Bit_Poll
/*********************************************************/
/*UART FUCTIONS FOR PIC24FJ128GA306*/
    void configure_uart(void){
    #ifdef PIC24FJ128GA306_uart1   
        //U1TX----->PIN21 (AN8/RP8/SEG31/COM7/CN26/RB8)
        /*U1RX----->PIN22 (AN9/RP9/SEG30/COM6/PMA7/CN27/RB9)*/
        ANSBbits.ANSB8 = 0; // AN8 is disabled, pin configured as digital 
        ANSBbits.ANSB9 = 0; // AN9 is disabled, pin configured as digital 
        __builtin_write_OSCCONL(OSCCON & 0xbf);
        RPOR4bits.RP8R = 0x3; // RP8(pin21) is configured as U1TX
        RPINR18bits.U1RXR = 0x9; // RP9 is configured as U1RXR
        __builtin_write_OSCCONL(OSCCON | 0x40);
        #ifdef Control_Register_Bit_Poll
            #ifdef BRGH_VALUE_HIGH
                U1MODEbits.BRGH = 1;
            #else
                U1MODEbits.BRGH = 0;
            #endif  
            U1BRG = BRGVAL1;
            UART1_MODULE_ENABLE;
            UART1_TRANSMIT_ENABLE;
            asm ("NOP");
            asm ("NOP");
            asm ("NOP");
            IFS0bits.U1TXIF = 0;
        #endif
        #ifdef Interrupt_Flag_Poll
            //...
        #endif
        #ifdef Interrupt_Enable
            //...
        #endif 
    #endif         
    #ifdef PIC24FJ128GA306_uart2   
        //U2TX----->PIN31 (RP10/SDA2/SEG10/PMA9/CN17/RF4)
        //U2RX----->PIN32  (PMA8/RP17/SCL2/SEG11/CN18/RF5) 
        __builtin_write_OSCCONL(OSCCON & 0xbf);
        RPOR5bits.RP10R = 0x5; // RP10(pin31) is configured as U2TX
        RPINR19bits.U2RXR = 17; // RP17(pin30) is configured as U2RXR
        __builtin_write_OSCCONL(OSCCON | 0x40);
        #ifdef Control_Register_Bit_Poll
            #ifdef BRGH_VALUE_HIGH
                U2MODEbits.BRGH = 1;
            #else
                U2MODEbits.BRGH = 0;
            #endif  
            U2BRG = BRGVAL2;
            UART2_MODULE_ENABLE;
            UART2_TRANSMIT_ENABLE;
            asm ("NOP");
            asm ("NOP");
            asm ("NOP");
            IFS1bits.U2TXIF = 0;
        #endif
        #ifdef Interrupt_Flag_Poll
            //...
        #endif
        #ifdef Interrupt_Enable
            //...
        #endif 
    #endif         
    #ifdef PIC24F16KA102_uart2
    //....
    #endif
    }
    void send_uart_8(uint8_t send_data){
        #ifdef Control_Register_Bit_Poll
         while(U1STAbits.UTXBF); //wait until recent transmit is complete
         U1TXREG = send_data;
         while(!U1STAbits.TRMT);//wait until current transmit is complete
        #endif
    }
    void send_uart2_8(uint8_t send_data){
        #ifdef Control_Register_Bit_Poll
            while(U2STAbits.UTXBF); //wait until recent transmit is complete
            U2TXREG = send_data;
            while(!U2STAbits.TRMT);//wait until current transmit is complete
        #endif
}
    void send_data_MPLABVis(uint8_t data){
        #ifdef Control_Register_Bit_Poll
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0x03;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = data;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0xFC;
        #endif

 }
    void send_float_MPLABVis(float data){ 
        #ifdef Control_Register_Bit_Poll
    //A float occupies 4 bytes in memory
    // In the following we define a pointer which will point 1 byte data
    // Then we assign the address of our float to the pointer 
    // and we send each time one of 4 byte of float variable
    // after each send we increment the pointer
        unsigned char *chptr;
        chptr = (unsigned char *) &data;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0x03;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0xFC;
        
    #endif
 }
    void outString_to_MPLABVis (const char* message){
        #ifdef Control_Register_Bit_Poll
            while(*message){
            while (TRANSMIT_NOT_READY()){};
            send_data_MPLABVis(*message);
            message++;}            
        #endif
    } 
    void outString (const char* message){
        #ifdef Control_Register_Bit_Poll
             while(*message){
             while (TRANSMIT_NOT_READY()){};
             send_uart_8(*message);
             message++; }
        #endif
    }
    uint8_t inChar() {
        uint16_t temp;
        #ifdef Control_Register_Bit_Poll
            while (!IS_CHAR_READY_UART1())
        #endif
            temp = U1RXREG; 
        return temp ; //read the receive register
        }
    void print_8x8_table_MPLABVis(uint8_t *ptr){
    uint8_t i,row,col;
    row = 0; 
    col = 0;
    for (i=0;i<64;i++){
        

             
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             outString_to_MPLABVis(",");

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             
             outString_to_MPLABVis("\t");
             
             
             
             col ++; 
             if (col == 8) {
                 outString_to_MPLABVis("\n");
                 col = 0; 
                 row ++;
                 if (row == 8){
                 outString_to_MPLABVis("\n\n");
                 outString_to_MPLABVis("TABLE 8X8\n");
                 }
             }
    }
    
   
}
#endif
#ifdef PIC24FJ64GA004
/*WHICH UART MODULE ?*/
    //#define PIC24FJ64GA004_uart1
    #define PIC24FJ64GA004_uart2
/*WHICH METHOD ?*/
    //#define Interrupt_Enable
    //#define Interrupt_Flag_Poll
    #define Control_Register_Bit_Poll
/*UART FUCTIONS FOR PIC24FJ64GA004*/
    void configure_uart(void){
        #ifdef PIC24FJ64GA004_uart2   
            /*U2RX -----> RP19/CN28/PMPBE/RC3*/
            /*U2TX -----> RP25/CN19/PMPA6/RC9*/
            //__builtin_write_OSCCONL(OSCCON & 0xbf);
            RPINR19 = 0x1F13;
            RPOR12 = 0x0500;
            //__builtin_write_OSCCONL(OSCCON | 0x40);
            #ifdef Control_Register_Bit_Poll
                #ifdef BRGH_VALUE_HIGH
                U2MODEbits.BRGH = 1;
                #else
                U2MODEbits.BRGH = 0;
                #endif  
                U2BRG = BRGVAL;
                U2MODEbits.UARTEN = 1;
                U2MODEbits.PDSEL = 0; //0: 8 data bits, no parity 1: 8 data bits, even parity, 2:8 data bits, odd parity
                #ifdef ONE_STOP_BIT
                U1MODEbits.STSEL = 0; //number of stop bits 0: 1 stop bit 1:2 stop bit
                #endif
                #ifdef TWO_STOP_BIT
                U1MODEbits.STSEL = 1; //number of stop bits 0: 1 stop bit 1:2 stop bit
                #endif
                U2STAbits.UTXISEL1 = 0; //interrupt will occur ++
                U2STAbits.UTXISEL0 = 1; //++ When all the transmission is completed 
                U2STAbits.UTXEN = 1;
                IFS1bits.U2TXIF = 0;
            #endif
            #ifdef Interrupt_Flag_Poll
                //..
            #endif
            #ifdef Interrupt_Enable
                //...
            #endif 
        #endif         
    }
    void send_uart_8(uint8_t send_data){
        #ifdef PIC24FJ64GA004_uart2
            #ifdef Control_Register_Bit_Poll
                while(U2STAbits.UTXBF);
                U2TXREG = send_data;
                while(!U2STAbits.TRMT);
            #endif    
        #endif
    }
    void send_data_MPLABVis(uint8_t data){
        #ifdef Control_Register_Bit_Poll
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0x03;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = data;
            while(TRANSMIT_NOT_READY()){};
            U1TXREG = 0xFC;
        #endif

 }
    void send_float_MPLABVis(float data){ 
        #ifdef Control_Register_Bit_Poll
    //A float occupies 4 bytes in memory
    // In the following we define a pointer which will point 1 byte data
    // Then we assign the address of our float to the pointer 
    // and we send each time one of 4 byte of float variable
    // after each send we increment the pointer
        unsigned char *chptr;
        chptr = (unsigned char *) &data;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0x03;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr++;
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = *chptr;
        
        while(TRANSMIT_NOT_READY()){};
        U1TXREG = 0xFC;
        
    #endif
 }
    void outString_to_MPLABVis (const char* message){
        #ifdef Control_Register_Bit_Poll
            while(*message){
            while (TRANSMIT_NOT_READY()){};
            send_data_MPLABVis(*message);
            message++;}            
        #endif
    } 
    void outString (const char* message){
        #ifdef Control_Register_Bit_Poll
             while(*message){
             while (TRANSMIT_NOT_READY()){};
             send_uart_8(*message);
             message++; }
        #endif
    }
    uint8_t inChar() {
        #ifdef Control_Register_Bit_Poll
            while (!IS_CHAR_READY_UART1())
        #endif
        return U1RXREG; //read the receive register
    }
    void print_8x8_table_MPLABVis(uint8_t *ptr){
    uint8_t i,row,col;
    row = 0; 
    col = 0;
    for (i=0;i<64;i++){
        

             
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             outString_to_MPLABVis(",");

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             send_data_MPLABVis(*ptr);

             ptr++;
             
             outString_to_MPLABVis("\t");
             
             
             
             col ++; 
             if (col == 8) {
                 outString_to_MPLABVis("\n");
                 col = 0; 
                 row ++;
                 if (row == 8){
                 outString_to_MPLABVis("\n\n");
                 outString_to_MPLABVis("TABLE 8X8\n");
                 }
             }
    }
    
   
}
#endif
    
void print_space(void){outString(" ");}
void new_line(void){outString("\n");}
uint8_t test_uart(){
    uint8_t i;
    for (i=0;i<15;i++){
        send_uart_8(0x55);
    }
    return 0;
}
#endif
#ifdef UART_VER_2
/*MLA circular buffer'i nasil kullanacagiz?*/
/*
 * 1) conf_uart.h icinden DRV_UART1_CONFIG_TX_BYTEQ_LENGTH parametresini tanimlayacagiz.
 *    gondermek istedigimiz verinin olasi maximum boyutunu baz olarak almaliyiz. 
 * 2) Ayni mesaji while loop içinden pe?pe?e sonsuz sayida göndermek isteyince 
 *    sorun cikiyor. 
 *    Sebebi ?u: veri gonderimi sirasinda program counter surekli olarak ISR ile 
 *    main(while loop) arasinda gidip geliyor. Her while loopA girdiginde veri
 *    iletim bufferini yeniden yukluyor Bir sekilde head-tail pointerleri tekrar 
 *    ilk pozisyonlarina donuyor. Bu da mesajin hep baslangic kisminin iletilmesi
 *    ne sebep oluyor. 
 *    Bunun cozumu su: while loop icine toplam veri iletim suresi kadar delay 
 *    koymak . Boylelikle veri iletimi tamamlanmadan pointerlerin resetlemesinin 
 *    onune geceriz
 * 3) 
 *  
 */


/***************************UART1****************************/
#if defined (_UART1)& defined (UART1_TXINT_RXINT)

//    #ifndef DRV_UART1_CONFIG_TX_BYTEQ_LENGTH
//            #define DRV_UART1_CONFIG_TX_BYTEQ_LENGTH 4
//    #endif
//    #ifndef DRV_UART1_CONFIG_RX_BYTEQ_LENGTH
//            #define DRV_UART1_CONFIG_RX_BYTEQ_LENGTH 4
//    #endif

//    static uint8_t uart1_txByteQ[DRV_UART1_CONFIG_TX_BYTEQ_LENGTH] ;
//    static uint8_t uart1_rxByteQ[DRV_UART1_CONFIG_RX_BYTEQ_LENGTH] ;



DRV_UART_OBJECT drv_uart1_obj;
/**************************************************************************/
    void configure_dspic33_UART1(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0)
    {

                
                #ifdef PIM_dsPIC33EP512MU810
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));
                RPINR18bits.U1RXR = 0b1100100;  // U1RX fonksiyonu chipin 49ncu pinindeki RP100 pinine tanimlandi/RF4
                RPOR9bits.RP101R = 0b00001;     // chipin 50nci pinindeki RP101 pinine U1TX fonksiyonu tanimlandi/RF5
                __builtin_write_OSCCONL(OSCCON | (1<<6));
                //lock registers
#endif
                #ifdef PIC24F16KA102
                TRISBbits.TRISB7 = 0; //U1TX/INT0/CN23/RB7
                AD1PCFGbits.PCFG4 = 1; //AN4/C1INB/C2IND/U1RX/CN6/RB2
                TRISBbits.TRISB2 =1;
                #endif
                #ifdef PIC24FJ128GA306
                    #ifdef MAFS
                        //unlock registers
                        __builtin_write_OSCCONL(OSCCON & 0xbf);
                        ANSBbits.ANSB6 = 0;
                        ANSBbits.ANSB7 = 0;
                        TRISBbits.TRISB6 = 1;
                        TRISBbits.TRISB7 = 0;
                        RPINR18bits.U1RXR = 6;  // U1RX fonksiyonu chipin 17nci pinindeki RP6 pinine tanimlandi/RB6
                        RPOR3bits.RP7R = 3;     // chipin 18nci pinindeki RP7 pinine U1TX fonksiyonu tanimlandi/RB7
                        __builtin_write_OSCCONL(OSCCON | 0x40);
                        //lock registers
                    #endif
                #endif
                switch(brghilo0){
                    case BRG_HI:
                        U1MODEbits.BRGH = 1;
                        U1BRG = (((FCY/baudrate0)/4)-1);
                       //U1BRG = 8;
                        break;
                    case BRG_LO:
                        U1MODEbits.BRGH = 0;
                        U1BRG = (((FCY/baudrate0)/16)-1);
                    default:
                        break;
                }
                switch(stopbit0){
                    case STOPBIT_ONE:
                        U1MODEbits.STSEL = 0;
                        break;
                    case STOPBIT_TWO:
                        U1MODEbits.STSEL = 1;
                        break;
                    default:
                        break;
                }
                switch(paritydata0){
                    case _9BIT_NOPAR:
                        U1MODEbits.PDSEL=3; 
                        break;
                    case _8BIT_ODDPAR:
                        U1MODEbits.PDSEL=2;
                        break;
                    case _8BIT_EVENPAR:
                        U1MODEbits.PDSEL=1;
                        break;
                    case _8BIT_NOPAR:
                        U1MODEbits.PDSEL=0;
                        break;
                    default:
                        break;
                }
                switch(txintmode0){
                    case TX_INT_MODE_2:
                        U1STAbits.UTXISEL1 =1;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    case TX_INT_MODE_1:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =1;
                        break;
                    case TX_INT_MODE_0:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    default:
                        break;
                }
                switch(rxintmode0){
                    case RX_INT_MODE_3:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =1;
                        break;
                    case RX_INT_MODE_2:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =0;
                        break;
                    case RX_INT_MODE_0:
                        U1STAbits.URXISEL1 =0;
                        U1STAbits.URXISEL0 =0;
                        break;
                    default:
                        break;
                }

        U1MODEbits.UARTEN = 1;
        IEC0bits.U1RXIE = 1;
        U1STAbits.UTXEN = 1;
        
        drv_uart1_obj.txHead = uart1_txByteQ;
        drv_uart1_obj.txTail = uart1_txByteQ;
        drv_uart1_obj.rxHead = uart1_rxByteQ;
        drv_uart1_obj.rxTail = uart1_rxByteQ;
        drv_uart1_obj.rxStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.full = false;
        drv_uart1_obj.rxStatus.s.full = false;
    }
/**************************************************************************/
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void )
    { 
        if(drv_uart1_obj.txStatus.s.empty)
        {
            IEC0bits.U1TXIE = false;
            return;
        }

        IFS0bits.U1TXIF = false;

        int count = 0;
        while((count < DRV_UART1_TX_FIFO_LENGTH)&& !(U1STAbits.UTXBF == 1))
        {
            count++;

            U1TXREG = *drv_uart1_obj.txHead;

            drv_uart1_obj.txHead++;

            if(drv_uart1_obj.txHead == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
            {
                drv_uart1_obj.txHead = uart1_txByteQ;
            }

            drv_uart1_obj.txStatus.s.full = false;

            if(drv_uart1_obj.txHead == drv_uart1_obj.txTail)
            {
                drv_uart1_obj.txStatus.s.empty = true;
                break;
            }
        }
    }


/**************************************************************************/    
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt ( void )
    {
        int count = 0;

        while((count < DRV_UART1_RX_FIFO_LENGTH) && (U1STAbits.URXDA == 1))
        {
            count++;

            *drv_uart1_obj.rxTail = U1RXREG;                    

            drv_uart1_obj.rxTail++;

            if(drv_uart1_obj.rxTail == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
            {
                drv_uart1_obj.rxTail = uart1_rxByteQ;
            }

            drv_uart1_obj.rxStatus.s.empty = false;

            if(drv_uart1_obj.rxTail == drv_uart1_obj.rxHead)
            {
                //Sets the flag RX full
                drv_uart1_obj.rxStatus.s.full = true;
                break;
            }

        }

        IFS0bits.U1RXIF = false;

    }
/**************************************************************************/    
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void )
    {
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }
#ifdef PIC24FJ128GA306
    IFS4bits.U1ERIF = false;
#endif
    //IFS4bits.U1EIF = false;
}
/**************************************************************************/
    void DRV_UART1_WriteByte(const uint8_t byte)
    {
        *drv_uart1_obj.txTail = byte;

        drv_uart1_obj.txTail++;

        if (drv_uart1_obj.txTail == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.txTail = uart1_txByteQ;
        }

        drv_uart1_obj.txStatus.s.empty = false;

        if (drv_uart1_obj.txHead == drv_uart1_obj.txTail)
        {
            drv_uart1_obj.txStatus.s.full = true;
        }

        if (IEC0bits.U1TXIE  == false)
        {
            IEC0bits.U1TXIE = true ;
        }

    }
 /**************************************************************************/
    /*  Function:
    unsigned int DRV_UART1_Write( uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes written into the internal buffer

*/
/**************************************************************************/
    unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes )
    {
    unsigned int numBytesWritten = 0 ;

    while ( numBytesWritten < ( numbytes ))
    {
        if((drv_uart1_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            DRV_UART1_WriteByte (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;

} 
/**************************************************************************/
    uint8_t DRV_UART1_ReadByte( void)
    {
        uint8_t data = 0;

        data = *drv_uart1_obj.rxHead;

        drv_uart1_obj.rxHead++;

        if (drv_uart1_obj.rxHead == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.rxHead = uart1_rxByteQ;
        }

        if (drv_uart1_obj.rxHead == drv_uart1_obj.rxTail)
        {
            drv_uart1_obj.rxStatus.s.empty = true;
        }

        drv_uart1_obj.rxStatus.s.full = false;

        return data;
    }
/**************************************************************************/
    /*  Function:
    int DRV_UART1_Read(uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes read by the UART1 peripheral

*/
    unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes)
    {
        unsigned int numBytesRead = 0 ;
        while ( numBytesRead < ( numbytes ))
        {
            if( drv_uart1_obj.rxStatus.s.empty)
            {
                break;
            }
            else
            {
                buffer[numBytesRead++] = DRV_UART1_ReadByte () ;
            }
        }

        return numBytesRead ;
    }  
/***************************************************************************/
    /* Function:
        DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void)

      Summary:
        Returns the transmitter and receiver transfer status

    */
    DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void )
    {
        DRV_UART1_TRANSFER_STATUS status = 0;

        if(drv_uart1_obj.txStatus.s.full)
        {
            status |= DRV_UART1_TRANSFER_STATUS_TX_FULL;
        }

        if(drv_uart1_obj.txStatus.s.empty)
        {
            status |= DRV_UART1_TRANSFER_STATUS_TX_EMPTY;
        }

        if(drv_uart1_obj.rxStatus.s.full)
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_FULL;
        }

        if(drv_uart1_obj.rxStatus.s.empty)
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_EMPTY;
        }
        else
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_DATA_PRESENT;
        }
        return status;
    }
/***************************************************************************/
    /* Function:
      uint8_t DRV_UART1_Peek(uint16_t offset)

      Summary:
        Returns the character in the read sequence at the offset provided, without
        extracting it

    */
    uint8_t DRV_UART1_Peek(uint16_t offset)
    {
        if( (drv_uart1_obj.rxHead + offset) > (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
          return uart1_rxByteQ[offset - (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - drv_uart1_obj.rxHead)];
        }
        else
        {
          return *(drv_uart1_obj.rxHead + offset);
        }
    }
/***************************************************************************/
    /* Function:
      unsigned int DRV_UART1_RXBufferSizeGet (void)

      Summary:
        Returns the size of the receive buffer

    */
    unsigned int DRV_UART1_RXBufferSizeGet(void)
    {
        if(drv_uart1_obj.rxHead > drv_uart1_obj.rxTail)
        {
            return(DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - (int)(drv_uart1_obj.rxHead) - (int)(drv_uart1_obj.rxTail));
        }
        else
        {
            return(drv_uart1_obj.rxTail - drv_uart1_obj.rxHead);
        }
    }
/***************************************************************************/
    /* Function:
      unsigned int DRV_UART1_TXBufferSizeGet (void)

      Summary:
        Returns the size of the transmit buffer

    */
    unsigned int DRV_UART1_TXBufferSizeGet(void)
    {
         if(drv_uart1_obj.txHead > drv_uart1_obj.txTail)
        {
            return(DRV_UART1_CONFIG_TX_BYTEQ_LENGTH - (int)drv_uart1_obj.txHead - (int)drv_uart1_obj.txTail);
        }
        else
        {
            return(drv_uart1_obj.txTail - drv_uart1_obj.txHead);
        }
    }
/***************************************************************************/
    /* Function:
      bool DRV_UART1_RXBufferIsEmpty (void)

      Summary:
        Returns the status of the receive buffer

    */
    bool DRV_UART1_RXBufferIsEmpty (void)
    {
        return(drv_uart1_obj.rxStatus.s.empty);
    }
/***************************************************************************/
    /* Function:
    bool DRV_UART1_TXBufferIsFull (void)

  Summary:
    Returns the status of the transmit buffer

*/
    bool DRV_UART1_TXBufferIsFull (void)
    {
    return(drv_uart1_obj.txStatus.s.full);
}
/***************************************************************************/
    /* Function:
    DRV_UART1_STATUS DRV_UART1_Status (void)

  Summary:
    Returns the status of the transmit and receive

*/
    DRV_UART1_STATUS DRV_UART1_Status (void)
    {
        return U1STA;
    }
/***************************************************************************/
#endif    
#if defined (_UART1)& defined (UART1_TXPOLL_RXINT)
    #ifndef DRV_UART1_CONFIG_TX_BYTEQ_LENGTH
            #define DRV_UART1_CONFIG_TX_BYTEQ_LENGTH 4
    #endif
    #ifndef DRV_UART1_CONFIG_RX_BYTEQ_LENGTH
            #define DRV_UART1_CONFIG_RX_BYTEQ_LENGTH 4
    #endif
    static uint8_t uart1_txByteQ[DRV_UART1_CONFIG_TX_BYTEQ_LENGTH] ;
    static uint8_t uart1_rxByteQ[DRV_UART1_CONFIG_RX_BYTEQ_LENGTH] ;

    #define DRV_UART1_TX_FIFO_LENGTH 1
    #define DRV_UART1_RX_FIFO_LENGTH 1 

    DRV_UART_OBJECT drv_uart1_obj;
/**************************************************************************/
    void configure_dspic33_UART1(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0)
    {

                //pin configurations
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));//<<-----Bu satir sorgulanmali
                RPINR18bits.U1RXR = 0b1100100;  // U1RX fonksiyonu chipin 49ncu pinindeki RP100 pinine tanimlandi/RF4
                RPOR9bits.RP101R = 0b00001;     // chipin 50nci pinindeki RP101 pinine U1TX fonksiyonu tanimlandi/RF5
                __builtin_write_OSCCONL(OSCCON | (1<<6));//<<-----Bu satir sorgulanmali
                //lock registers

                switch(brghilo0){
                    case BRG_HI:
                        U1MODEbits.BRGH = 1;
                        U1BRG = (((FCY/baudrate0)/4)-1);
                        break;
                    case BRG_LO:
                        U1MODEbits.BRGH = 0;
                        U1BRG = (((FCY/baudrate0)/16)-1);
                    default:
                        break;
                }
                switch(stopbit0){
                    case STOPBIT_ONE:
                        U1MODEbits.STSEL = 0;
                        break;
                    case STOPBIT_TWO:
                        U1MODEbits.STSEL = 1;
                        break;
                    default:
                        break;
                }
                switch(paritydata0){
                    case _9BIT_NOPAR:
                        U1MODEbits.PDSEL=3; 
                        break;
                    case _8BIT_ODDPAR:
                        U1MODEbits.PDSEL=2;
                        break;
                    case _8BIT_EVENPAR:
                        U1MODEbits.PDSEL=1;
                        break;
                    case _8BIT_NOPAR:
                        U1MODEbits.PDSEL=0;
                        break;
                    default:
                        break;
                }
                switch(txintmode0){
                    case TX_INT_MODE_2:
                        U1STAbits.UTXISEL1 =1;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    case TX_INT_MODE_1:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =1;
                        break;
                    case TX_INT_MODE_0:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    default:
                        break;
                }
                switch(rxintmode0){
                    case RX_INT_MODE_3:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =1;
                        break;
                    case RX_INT_MODE_2:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =0;
                        break;
                    case RX_INT_MODE_0:
                        U1STAbits.URXISEL1 =0;
                        U1STAbits.URXISEL0 =0;
                        break;
                    default:
                        break;
                }

        U1MODEbits.UARTEN = 1;
        IEC0bits.U1RXIE = 1;
        U1STAbits.UTXEN = 1;
        
        drv_uart1_obj.txHead = uart1_txByteQ;
        drv_uart1_obj.txTail = uart1_txByteQ;
        drv_uart1_obj.rxHead = uart1_rxByteQ;
        drv_uart1_obj.rxTail = uart1_rxByteQ;
        drv_uart1_obj.rxStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.full = false;
        drv_uart1_obj.rxStatus.s.full = false;
    }
/**************************************************************************/    
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt ( void )
    {
        int count = 0;

        while((count < DRV_UART1_RX_FIFO_LENGTH) && (U1STAbits.URXDA == 1))
        {
            count++;

            *drv_uart1_obj.rxTail = U1RXREG;                    

            drv_uart1_obj.rxTail++;

            if(drv_uart1_obj.rxTail == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
            {
                drv_uart1_obj.rxTail = uart1_rxByteQ;
            }

            drv_uart1_obj.rxStatus.s.empty = false;

            if(drv_uart1_obj.rxTail == drv_uart1_obj.rxHead)
            {
                //Sets the flag RX full
                drv_uart1_obj.rxStatus.s.full = true;
                break;
            }

        }

        IFS0bits.U1RXIF = false;

    }
/**************************************************************************/    
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void )
    {
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }

    IFS4bits.U1EIF = false;
}
/**************************************************************************/
    /* Function:
    void DRV_UART1_TasksTX ( void )

  Summary:
    Maintains the driver's transmitter state machine in a polled manner

*/
    void DRV_UART1_TasksTX ( void )
    { 
    if(drv_uart1_obj.txStatus.s.empty)
    {
        return;
    }

    IFS0bits.U1TXIF = false;

    int count = 0;
    while((count < DRV_UART1_TX_FIFO_LENGTH)&& !(U1STAbits.UTXBF == 1))
    {
        count++;

        U1TXREG = *drv_uart1_obj.txHead;

        drv_uart1_obj.txHead++;

        if(drv_uart1_obj.txHead == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.txHead = uart1_txByteQ;
        }

        drv_uart1_obj.txStatus.s.full = false;

        if(drv_uart1_obj.txHead == drv_uart1_obj.txTail)
        {
            drv_uart1_obj.txStatus.s.empty = true;
            break;
        }
    }
}
/***************************************************************************/
    void DRV_UART1_WriteByte(const uint8_t byte)
    {
        *drv_uart1_obj.txTail = byte;

        drv_uart1_obj.txTail++;

        if (drv_uart1_obj.txTail == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.txTail = uart1_txByteQ;
        }

        drv_uart1_obj.txStatus.s.empty = false;

        if (drv_uart1_obj.txHead == drv_uart1_obj.txTail)
        {
            drv_uart1_obj.txStatus.s.full = true;
        }

    }
/**************************************************************************/
    /*  Function:
    unsigned int DRV_UART1_Write( uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes written into the internal buffer

*/
    unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes )
    {
    unsigned int numBytesWritten = 0 ;

    while ( numBytesWritten < ( numbytes ))
    {
        if((drv_uart1_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            DRV_UART1_WriteByte (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;

} 
/**************************************************************************/
    uint8_t DRV_UART1_ReadByte( void)
    {
        uint8_t data = 0;

        data = *drv_uart1_obj.rxHead;

        drv_uart1_obj.rxHead++;

        if (drv_uart1_obj.rxHead == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.rxHead = uart1_rxByteQ;
        }

        if (drv_uart1_obj.rxHead == drv_uart1_obj.rxTail)
        {
            drv_uart1_obj.rxStatus.s.empty = true;
        }

        drv_uart1_obj.rxStatus.s.full = false;

        return data;
    }
/**************************************************************************/
    /*  Function:
    int DRV_UART1_Read(uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes read by the UART1 peripheral

*/
    unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes)
    {
        unsigned int numBytesRead = 0 ;
        while ( numBytesRead < ( numbytes ))
        {
            if( drv_uart1_obj.rxStatus.s.empty)
            {
                break;
            }
            else
            {
                buffer[numBytesRead++] = DRV_UART1_ReadByte () ;
            }
        }

        return numBytesRead ;
    }  
/***************************************************************************/
    /* Function:
        DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void)

      Summary:
        Returns the transmitter and receiver transfer status

    */
    DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void )
    {
        DRV_UART1_TRANSFER_STATUS status = 0;

        if(drv_uart1_obj.txStatus.s.full)
        {
            status |= DRV_UART1_TRANSFER_STATUS_TX_FULL;
        }

        if(drv_uart1_obj.txStatus.s.empty)
        {
            status |= DRV_UART1_TRANSFER_STATUS_TX_EMPTY;
        }

        if(drv_uart1_obj.rxStatus.s.full)
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_FULL;
        }

        if(drv_uart1_obj.rxStatus.s.empty)
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_EMPTY;
        }
        else
        {
            status |= DRV_UART1_TRANSFER_STATUS_RX_DATA_PRESENT;
        }
        return status;
    }
/***************************************************************************/
    /* Function:
      uint8_t DRV_UART1_Peek(uint16_t offset)

      Summary:
        Returns the character in the read sequence at the offset provided, without
        extracting it

    */
    uint8_t DRV_UART1_Peek(uint16_t offset)
    {
        if( (drv_uart1_obj.rxHead + offset) > (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
          return uart1_rxByteQ[offset - (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - drv_uart1_obj.rxHead)];
        }
        else
        {
          return *(drv_uart1_obj.rxHead + offset);
        }
    }
/***************************************************************************/
    /* Function:
      unsigned int DRV_UART1_RXBufferSizeGet (void)

      Summary:
        Returns the size of the receive buffer

    */
    unsigned int DRV_UART1_RXBufferSizeGet(void)
    {
        if(drv_uart1_obj.rxHead > drv_uart1_obj.rxTail)
        {
            return(DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - (int)(drv_uart1_obj.rxHead) - (int)(drv_uart1_obj.rxTail));
        }
        else
        {
            return(drv_uart1_obj.rxTail - drv_uart1_obj.rxHead);
        }
    }
/***************************************************************************/
    /* Function:
      unsigned int DRV_UART1_TXBufferSizeGet (void)

      Summary:
        Returns the size of the transmit buffer

    */
    unsigned int DRV_UART1_TXBufferSizeGet(void)
    {
         if(drv_uart1_obj.txHead > drv_uart1_obj.txTail)
        {
            return(DRV_UART1_CONFIG_TX_BYTEQ_LENGTH - (int)drv_uart1_obj.txHead - (int)drv_uart1_obj.txTail);
        }
        else
        {
            return(drv_uart1_obj.txTail - drv_uart1_obj.txHead);
        }
    }
/***************************************************************************/
    /* Function:
      bool DRV_UART1_RXBufferIsEmpty (void)

      Summary:
        Returns the status of the receive buffer

    */
    bool DRV_UART1_RXBufferIsEmpty (void)
    {
        return(drv_uart1_obj.rxStatus.s.empty);
    }
/***************************************************************************/
    /* Function:
    bool DRV_UART1_TXBufferIsFull (void)

  Summary:
    Returns the status of the transmit buffer

*/
    bool DRV_UART1_TXBufferIsFull (void)
    {
    return(drv_uart1_obj.txStatus.s.full);
}
/***************************************************************************/
    /* Function:
    bool DRV_UART1_TXBufferIsFull (void)

  Summary:
    Returns the status of the transmit buffer

*/
    bool DRV_UART1_TXBufferIsEmpty (void)
    {
    return(drv_uart1_obj.txStatus.s.empty);
}
/***************************************************************************/
    /* Function:
    DRV_UART1_STATUS DRV_UART1_Status (void)

  Summary:
    Returns the status of the transmit and receive

*/
    DRV_UART1_STATUS DRV_UART1_Status (void)
    {
        return U1STA;
    }
/***************************************************************************/
#endif    
#if defined (_UART1)& defined (UART1_TXPOLL_RXPOLL)
    #ifndef DRV_UART1_CONFIG_TX_BYTEQ_LENGTH
            #define DRV_UART1_CONFIG_TX_BYTEQ_LENGTH 4
    #endif
    #ifndef DRV_UART1_CONFIG_RX_BYTEQ_LENGTH
            #define DRV_UART1_CONFIG_RX_BYTEQ_LENGTH 4
    #endif
    static uint8_t uart1_txByteQ[DRV_UART1_CONFIG_TX_BYTEQ_LENGTH] ;
    static uint8_t uart1_rxByteQ[DRV_UART1_CONFIG_RX_BYTEQ_LENGTH] ;

    #define DRV_UART1_TX_FIFO_LENGTH 1
    #define DRV_UART1_RX_FIFO_LENGTH 1 

    DRV_UART_OBJECT drv_uart1_obj;
/**************************************************************************/
    void configure_dspic33_UART1(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0)
    {

                //pin configurations
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));//<<-----Bu satir sorgulanmali
                RPINR18bits.U1RXR = 0b1100100;  // U1RX fonksiyonu chipin 49ncu pinindeki RP100 pinine tanimlandi/RF4
                RPOR9bits.RP101R = 0b00001;     // chipin 50nci pinindeki RP101 pinine U1TX fonksiyonu tanimlandi/RF5
                __builtin_write_OSCCONL(OSCCON | (1<<6));//<<-----Bu satir sorgulanmali
                //lock registers

                switch(brghilo0){
                    case BRG_HI:
                        U1MODEbits.BRGH = 1;
                        U1BRG = (((FCY/baudrate0)/4)-1);
                        break;
                    case BRG_LO:
                        U1MODEbits.BRGH = 0;
                        U1BRG = (((FCY/baudrate0)/16)-1);
                    default:
                        break;
                }
                switch(stopbit0){
                    case STOPBIT_ONE:
                        U1MODEbits.STSEL = 0;
                        break;
                    case STOPBIT_TWO:
                        U1MODEbits.STSEL = 1;
                        break;
                    default:
                        break;
                }
                switch(paritydata0){
                    case _9BIT_NOPAR:
                        U1MODEbits.PDSEL=3; 
                        break;
                    case _8BIT_ODDPAR:
                        U1MODEbits.PDSEL=2;
                        break;
                    case _8BIT_EVENPAR:
                        U1MODEbits.PDSEL=1;
                        break;
                    case _8BIT_NOPAR:
                        U1MODEbits.PDSEL=0;
                        break;
                    default:
                        break;
                }
                switch(txintmode0){
                    case TX_INT_MODE_2:
                        U1STAbits.UTXISEL1 =1;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    case TX_INT_MODE_1:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =1;
                        break;
                    case TX_INT_MODE_0:
                        U1STAbits.UTXISEL1 =0;
                        U1STAbits.UTXISEL0 =0;
                        break;
                    default:
                        break;
                }
                switch(rxintmode0){
                    case RX_INT_MODE_3:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =1;
                        break;
                    case RX_INT_MODE_2:
                        U1STAbits.URXISEL1 =1;
                        U1STAbits.URXISEL0 =0;
                        break;
                    case RX_INT_MODE_0:
                        U1STAbits.URXISEL1 =0;
                        U1STAbits.URXISEL0 =0;
                        break;
                    default:
                        break;
                }

        U1MODEbits.UARTEN = 1;
        U1STAbits.UTXEN = 1;
        
        drv_uart1_obj.txHead = uart1_txByteQ;
        drv_uart1_obj.txTail = uart1_txByteQ;
        drv_uart1_obj.rxHead = uart1_rxByteQ;
        drv_uart1_obj.rxTail = uart1_rxByteQ;
        drv_uart1_obj.rxStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.empty = true;
        drv_uart1_obj.txStatus.s.full = false;
        drv_uart1_obj.rxStatus.s.full = false;
    }
// ***********************************************************
/* Function:
    void DRV_UART1_TasksTX ( void )

  Summary:
    Maintains the driver's transmitter state machine in a polled manner

*/
void DRV_UART1_TasksTX ( void )
{ 
    if(drv_uart1_obj.txStatus.s.empty)
    {
        return;
    }

    IFS0bits.U1TXIF = false;

    int count = 0;
    while((count < DRV_UART1_TX_FIFO_LENGTH)&& !(U1STAbits.UTXBF == 1))
    {
        count++;

        U1TXREG = *drv_uart1_obj.txHead;

        drv_uart1_obj.txHead++;

        if(drv_uart1_obj.txHead == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.txHead = uart1_txByteQ;
        }

        drv_uart1_obj.txStatus.s.full = false;

        if(drv_uart1_obj.txHead == drv_uart1_obj.txTail)
        {
            drv_uart1_obj.txStatus.s.empty = true;
            break;
        }
    }
}
// **************************************************
/* Function:
    void DRV_UART1_TasksRX ( void )

  Summary:
    Maintains the driver's receiver state machine in a polled manner.

*/
void DRV_UART1_TasksRX ( void )
{
    int count = 0;

    while((count < DRV_UART1_RX_FIFO_LENGTH) && (U1STAbits.URXDA == 1))
    {
        count++;

        *drv_uart1_obj.rxTail = U1RXREG;

        drv_uart1_obj.rxTail++;

        if(drv_uart1_obj.rxTail == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
        {
            drv_uart1_obj.rxTail = uart1_rxByteQ;
        }

        drv_uart1_obj.rxStatus.s.empty = false;
        
        if(drv_uart1_obj.rxTail == drv_uart1_obj.rxHead)
        {
            //Sets the flag RX full
            drv_uart1_obj.rxStatus.s.full = true;
            break;
        }
        
    }

    IFS0bits.U1RXIF = false;
   
}
// ***************************************************************
/* Function:
    void DRV_UART1_TasksError ( void );

  Summary:
    Maintains the driver's error-handling state machine in a polled manner.

*/
void DRV_UART1_TasksError ( void )
{
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }

    IFS4bits.U1EIF = false;
}
// *****************************************************************************
/* Function:
    uint8_t DRV_UART1_ReadByte( void)

  Summary:
    Reads a byte of data from the UART1

*/
uint8_t DRV_UART1_ReadByte( void)
{
    uint8_t data = 0;

    data = *drv_uart1_obj.rxHead;

    drv_uart1_obj.rxHead++;

    if (drv_uart1_obj.rxHead == (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
    {
        drv_uart1_obj.rxHead = uart1_rxByteQ;
    }

    if (drv_uart1_obj.rxHead == drv_uart1_obj.rxTail)
    {
        drv_uart1_obj.rxStatus.s.empty = true;
    }

    drv_uart1_obj.rxStatus.s.full = false;

    return data;
}
//*******************************************************************************
/*  Function:
    int DRV_UART1_Read(uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes read by the UART1 peripheral

*/
unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes)
{
    unsigned int numBytesRead = 0 ;
    while ( numBytesRead < ( numbytes ))
    {
        if( drv_uart1_obj.rxStatus.s.empty)
        {
            break;
        }
        else
        {
            buffer[numBytesRead++] = DRV_UART1_ReadByte () ;
        }
    }

    return numBytesRead ;
}
// *****************************************************************************
/* Function:
    void DRV_UART1_WriteByte( const uint8_t byte)

  Summary:
    Writes a byte of data to the UART1

*/
void DRV_UART1_WriteByte( const uint8_t byte)
{
    *drv_uart1_obj.txTail = byte;

    drv_uart1_obj.txTail++;
    
    if (drv_uart1_obj.txTail == (uart1_txByteQ + DRV_UART1_CONFIG_TX_BYTEQ_LENGTH))
    {
        drv_uart1_obj.txTail = uart1_txByteQ;
    }

    drv_uart1_obj.txStatus.s.empty = false;

    if (drv_uart1_obj.txHead == drv_uart1_obj.txTail)
    {
        drv_uart1_obj.txStatus.s.full = true;
    }

	
}
//*******************************************************************************
/*  Function:
    unsigned int DRV_UART1_Write( uint8_t *buffer, const unsigned int numbytes )

  Summary:
    Returns the number of bytes written into the internal buffer

*/
unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes )
{
    unsigned int numBytesWritten = 0 ;

    while ( numBytesWritten < ( numbytes ))
    {
        if((drv_uart1_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            DRV_UART1_WriteByte (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;

} 
// *****************************************************************************
/* Function:
    DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void)

  Summary:
    Returns the transmitter and receiver transfer status

*/
DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void )
{
    DRV_UART1_TRANSFER_STATUS status = 0;

    if(drv_uart1_obj.txStatus.s.full)
    {
        status |= DRV_UART1_TRANSFER_STATUS_TX_FULL;
    }

    if(drv_uart1_obj.txStatus.s.empty)
    {
        status |= DRV_UART1_TRANSFER_STATUS_TX_EMPTY;
    }

    if(drv_uart1_obj.rxStatus.s.full)
    {
        status |= DRV_UART1_TRANSFER_STATUS_RX_FULL;
    }

    if(drv_uart1_obj.rxStatus.s.empty)
    {
        status |= DRV_UART1_TRANSFER_STATUS_RX_EMPTY;
    }
    else
    {
        status |= DRV_UART1_TRANSFER_STATUS_RX_DATA_PRESENT;
    }
    return status;
}
// *****************************************************************************
/* Function:
  uint8_t DRV_UART1_Peek(uint16_t offset)

  Summary:
    Returns the character in the read sequence at the offset provided, without
    extracting it

*/
uint8_t DRV_UART1_Peek(uint16_t offset)
{
    if( (drv_uart1_obj.rxHead + offset) > (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH))
    {
      return uart1_rxByteQ[offset - (uart1_rxByteQ + DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - drv_uart1_obj.rxHead)];
    }
    else
    {
      return *(drv_uart1_obj.rxHead + offset);
    }
}
// *****************************************************************************
/* Function:
  unsigned int DRV_UART1_RXBufferSizeGet (void)

  Summary:
    Returns the size of the receive buffer

*/
unsigned int DRV_UART1_RXBufferSizeGet(void)
{
    if(drv_uart1_obj.rxHead > drv_uart1_obj.rxTail)
    {
        return(DRV_UART1_CONFIG_RX_BYTEQ_LENGTH - (int)(drv_uart1_obj.rxHead) - (int)(drv_uart1_obj.rxTail));
    }
    else
    {
        return(drv_uart1_obj.rxTail - drv_uart1_obj.rxHead);
    }
}
// *****************************************************************************
/* Function:
  unsigned int DRV_UART1_TXBufferSizeGet (void)

  Summary:
    Returns the size of the transmit buffer

*/
unsigned int DRV_UART1_TXBufferSizeGet(void)
{
     if(drv_uart1_obj.txHead > drv_uart1_obj.txTail)
    {
        return(DRV_UART1_CONFIG_TX_BYTEQ_LENGTH - (int)drv_uart1_obj.txHead - (int)drv_uart1_obj.txTail);
    }
    else
    {
        return(drv_uart1_obj.txTail - drv_uart1_obj.txHead);
    }
}
// *****************************************************************************
/* Function:
  bool DRV_UART1_RXBufferIsEmpty (void)

  Summary:
    Returns the status of the receive buffer

*/
bool DRV_UART1_RXBufferIsEmpty (void)
{
    return(drv_uart1_obj.rxStatus.s.empty);
}
bool DRV_UART1_RXBufferIsFull (void)
{
    return(drv_uart1_obj.rxStatus.s.full);
}
// *****************************************************************************
/* Function:
    bool DRV_UART1_TXBufferIsFull (void)

  Summary:
    Returns the status of the transmit buffer

*/
bool DRV_UART1_TXBufferIsFull (void)
{
    return(drv_uart1_obj.txStatus.s.full);
}
bool DRV_UART1_TXBufferIsEmpty (void)
{
    return(drv_uart1_obj.txStatus.s.full);
}
// *****************************************************************************
/* Function:
    DRV_UART1_STATUS DRV_UART1_Status (void)

  Summary:
    Returns the status of the transmit and receive

*/
DRV_UART1_STATUS DRV_UART1_Status (void)
{
    return U1STA;
}
//*******************************************************************************
#endif
/****************************UART2******************************/
#if defined (_UART2)& defined (UART2_TXINT_RXINT)
    
    #ifndef DRV_UART2_CONFIG_TX_BYTEQ_LENGTH
            #define DRV_UART2_CONFIG_TX_BYTEQ_LENGTH 4
    #endif
    #ifndef DRV_UART2_CONFIG_RX_BYTEQ_LENGTH
            #define DRV_UART2_CONFIG_RX_BYTEQ_LENGTH 4
    #endif
    static uint8_t uart2_txByteQ[DRV_UART2_CONFIG_TX_BYTEQ_LENGTH] ;
    static uint8_t uart2_rxByteQ[DRV_UART2_CONFIG_RX_BYTEQ_LENGTH] ;

    #define DRV_UART2_TX_FIFO_LENGTH 1
    #define DRV_UART2_RX_FIFO_LENGTH 1 

    DRV_UART_OBJECT drv_uart2_obj;
        void configure_dspic33_UART2(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0)
    {

                //pin configurations
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));//<<-----Bu satir sorgulanmali
                RPINR19bits.U2RXR = 109;     // U2RX fonksiyonu chipin 39ncu pinindeki RP109 pinine tanimlandi/RF4
                RPOR11bits.RP108R = 0b000011;// chipin 40nci pinindeki RP108 pinine U2TX fonksiyonu tanimlandi/RF5
                __builtin_write_OSCCONL(OSCCON | (1<<6));//<<-----Bu satir sorgulanmali
                //lock registers

                switch(brghilo0){
                    case BRG_HI:
                        U2MODEbits.BRGH = 1;
                        U2BRG = (((FCY/baudrate0)/4)-1);
                        break;
                    case BRG_LO:
                        U2MODEbits.BRGH = 0;
                        U2BRG = (((FCY/baudrate0)/16)-1);
                    default:
                        break;
                }
                switch(stopbit0){
                    case STOPBIT_ONE:
                        U2MODEbits.STSEL = 0;
                        break;
                    case STOPBIT_TWO:
                        U2MODEbits.STSEL = 1;
                        break;
                    default:
                        break;
                }
                switch(paritydata0){
                    case _9BIT_NOPAR:
                        U2MODEbits.PDSEL=3; 
                        break;
                    case _8BIT_ODDPAR:
                        U2MODEbits.PDSEL=2;
                        break;
                    case _8BIT_EVENPAR:
                        U2MODEbits.PDSEL=1;
                        break;
                    case _8BIT_NOPAR:
                        U2MODEbits.PDSEL=0;
                        break;
                    default:
                        break;
                }
                switch(txintmode0){
                    case TX_INT_MODE_2:
                        U2STAbits.UTXISEL1 =1;
                        U2STAbits.UTXISEL0 =0;
                        break;
                    case TX_INT_MODE_1:
                        U2STAbits.UTXISEL1 =0;
                        U2STAbits.UTXISEL0 =1;
                        break;
                    case TX_INT_MODE_0:
                        U2STAbits.UTXISEL1 =0;
                        U2STAbits.UTXISEL0 =0;
                        break;
                    default:
                        break;
                }
                switch(rxintmode0){
                    case RX_INT_MODE_3:
                        U2STAbits.URXISEL1 =1;
                        U2STAbits.URXISEL0 =1;
                        break;
                    case RX_INT_MODE_2:
                        U2STAbits.URXISEL1 =1;
                        U2STAbits.URXISEL0 =0;
                        break;
                    case RX_INT_MODE_0:
                        U2STAbits.URXISEL1 =0;
                        U2STAbits.URXISEL0 =0;
                        break;
                    default:
                        break;
                }

        U2MODEbits.UARTEN = 1;
        IEC1bits.U2RXIE = 1;
        U2STAbits.UTXEN = 1;
        
        drv_uart2_obj.txHead = uart2_txByteQ;
        drv_uart2_obj.txTail = uart2_txByteQ;
        drv_uart2_obj.rxHead = uart2_rxByteQ;
        drv_uart2_obj.rxTail = uart2_rxByteQ;
        drv_uart2_obj.rxStatus.s.empty = true;
        drv_uart2_obj.txStatus.s.empty = true;
        drv_uart2_obj.txStatus.s.full = false;
        drv_uart2_obj.rxStatus.s.full = false;
    }
/**************************************************************************/        
/*
 This ISR transmit the data in uart2_txByteQ through UART2 module. 
 * How many bytes does this ISR can transmit?
 * First of all DRV_UART2_TX_FIFO_LENGTH parameter is important.  
 * Because of the inequality condition of while loop 
 * if DRV_UART2_TX_FIFO_LENGTH = 1 then at each interrupt ISR can transmit
 * only 1 byte data. 
 * If DRV_UART2_TX_FIFO_LENGTH is bigger then 1 then size of the uart2_txByteQ
 * becomes important. ISR will transmit all the data in the uart2_txByteQ 
 * given that fifo length is at least equal to the size of uart2_txByteQ.
 */
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2TXInterrupt ( void )
    { 
        if(drv_uart2_obj.txStatus.s.empty)
        {
            IEC1bits.U2TXIE = false;
            return;
        }

        IFS1bits.U2TXIF = false;

        int count = 0;
        while((count < DRV_UART2_TX_FIFO_LENGTH)&& !(U2STAbits.UTXBF == 1))
        {
            count++;

            U2TXREG = *drv_uart2_obj.txHead;

            drv_uart2_obj.txHead++;

            if(drv_uart2_obj.txHead == (uart2_txByteQ + DRV_UART2_CONFIG_TX_BYTEQ_LENGTH))
            {
                drv_uart2_obj.txHead = uart2_txByteQ;
            }

            drv_uart2_obj.txStatus.s.full = false;

            if(drv_uart2_obj.txHead == drv_uart2_obj.txTail)
            {
                drv_uart2_obj.txStatus.s.empty = true;
                break;
            }
        }
    }
/**************************************************************************/
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2RXInterrupt ( void )
    {
        int count = 0;

        while((count < DRV_UART2_RX_FIFO_LENGTH) && (U2STAbits.URXDA == 1))
        {
            count++;

            *drv_uart2_obj.rxTail = U2RXREG;

            drv_uart2_obj.rxTail++;

            if(drv_uart2_obj.rxTail == (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
            {
                drv_uart2_obj.rxTail = uart2_rxByteQ;
            }

            drv_uart2_obj.rxStatus.s.empty = false;

            if(drv_uart2_obj.rxTail == drv_uart2_obj.rxHead)
            {
                //Sets the flag RX full
                drv_uart2_obj.rxStatus.s.full = true;
                break;
            }

        }

        IFS1bits.U2RXIF = false;

    }
/**************************************************************************/
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2ErrInterrupt ( void )
    {
        if ((U2STAbits.OERR == 1))
        {
            U2STAbits.OERR = 0;
        }

        IFS4bits.U2EIF = false;
    }
/**************************************************************************/    
    uint8_t DRV_UART2_ReadByte( void)
    {
        uint8_t data = 0;

        data = *drv_uart2_obj.rxHead;

        drv_uart2_obj.rxHead++;

        if (drv_uart2_obj.rxHead == (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
        {
            drv_uart2_obj.rxHead = uart2_rxByteQ;
        }

        if (drv_uart2_obj.rxHead == drv_uart2_obj.rxTail)
        {
            drv_uart2_obj.rxStatus.s.empty = true;
        }

        drv_uart2_obj.rxStatus.s.full = false;

        return data;
    }
/**************************************************************************/
    /*  Function:
        int DRV_UART2_Read(uint8_t *buffer, const unsigned int numbytes )

      Summary:
        Returns the number of bytes read by the UART2 peripheral

    */
    unsigned int DRV_UART2_Read( uint8_t *buffer ,  const unsigned int numbytes)
    {
        unsigned int numBytesRead = 0 ;
        while ( numBytesRead < ( numbytes ))
        {
            if( drv_uart2_obj.rxStatus.s.empty)
            {
                break;
            }
            else
            {
                buffer[numBytesRead++] = DRV_UART2_ReadByte () ;
            }
        }

        return numBytesRead ;
    }
// *****************************************************************************
    /* Function:
        void DRV_UART2_WriteByte( const uint8_t byte)

      Summary:
        Writes a byte of data to the UART2
     * This function writes 1 byte to the uart2_txByteQ. Than
     * sets the interrupt enable bit. This results in an interrupt
     * generation and program branches to the ISR. 

    */
    void DRV_UART2_WriteByte( const uint8_t byte)
    {
        *drv_uart2_obj.txTail = byte;

        drv_uart2_obj.txTail++;

        if (drv_uart2_obj.txTail == (uart2_txByteQ + DRV_UART2_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart2_obj.txTail = uart2_txByteQ;
        }

        drv_uart2_obj.txStatus.s.empty = false;

        if (drv_uart2_obj.txHead == drv_uart2_obj.txTail)
        {
            drv_uart2_obj.txStatus.s.full = true;
        }

        if (IEC1bits.U2TXIE  == false)
        {
            IEC1bits.U2TXIE = true ;
        }

    }
//*******************************************************************************
    /*  Function:
        unsigned int DRV_UART2_Write( uint8_t *buffer, const unsigned int numbytes )

      Summary:
        Returns the number of bytes written into the internal buffer

    */
    unsigned int DRV_UART2_Write( const uint8_t *buffer , const unsigned int numbytes )
    {
        unsigned int numBytesWritten = 0 ;

        while ( numBytesWritten < ( numbytes ))
        {
            if((drv_uart2_obj.txStatus.s.full))
            {
                break;
            }
            else
            {
                DRV_UART2_WriteByte (buffer[numBytesWritten++] ) ;
            }
        }

        return numBytesWritten ;

    } 
// *****************************************************************************
    /* Function:
        DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void)

      Summary:
        Returns the transmitter and receiver transfer status

    */
    DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void )
    {
        DRV_UART2_TRANSFER_STATUS status = 0;

        if(drv_uart2_obj.txStatus.s.full)
        {
            status |= DRV_UART2_TRANSFER_STATUS_TX_FULL;
        }

        if(drv_uart2_obj.txStatus.s.empty)
        {
            status |= DRV_UART2_TRANSFER_STATUS_TX_EMPTY;
        }

        if(drv_uart2_obj.rxStatus.s.full)
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_FULL;
        }

        if(drv_uart2_obj.rxStatus.s.empty)
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_EMPTY;
        }
        else
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_DATA_PRESENT;
        }
        return status;
    }
// *****************************************************************************
    /* Function:
      uint8_t DRV_UART2_Peek(uint16_t offset)

      Summary:
        Returns the character in the read sequence at the offset provided, without
        extracting it

    */
    uint8_t DRV_UART2_Peek(uint16_t offset)
    {
        if( (drv_uart2_obj.rxHead + offset) > (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
        {
          return uart2_rxByteQ[offset - (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH - drv_uart2_obj.rxHead)];
        }
        else
        {
          return *(drv_uart2_obj.rxHead + offset);
        }
    }
// *****************************************************************************
    /* Function:
      unsigned int DRV_UART2_RXBufferSizeGet (void)

      Summary:
        Returns the size of the receive buffer

    */
    unsigned int DRV_UART2_RXBufferSizeGet(void)
    {
        if(drv_uart2_obj.rxHead > drv_uart2_obj.rxTail)
        {
            return(DRV_UART2_CONFIG_RX_BYTEQ_LENGTH - (int)(drv_uart2_obj.rxHead) - (int)(drv_uart2_obj.rxTail));
        }
        else
        {
            return(drv_uart2_obj.rxTail - drv_uart2_obj.rxHead);
        }
    }
// *****************************************************************************
    /* Function:
      unsigned int DRV_UART2_TXBufferSizeGet (void)

      Summary:
        Returns the size of the transmit buffer

    */
    unsigned int DRV_UART2_TXBufferSizeGet(void)
    {
         if(drv_uart2_obj.txHead > drv_uart2_obj.txTail)
        {
            return(DRV_UART2_CONFIG_TX_BYTEQ_LENGTH - (int)drv_uart2_obj.txHead - (int)drv_uart2_obj.txTail);
        }
        else
        {
            return(drv_uart2_obj.txTail - drv_uart2_obj.txHead);
        }
    }
// *****************************************************************************
    /* Function:
      bool DRV_UART2_RXBufferIsEmpty (void)

      Summary:
        Returns the status of the receive buffer

    */
    bool DRV_UART2_RXBufferIsEmpty (void)
    {
        return(drv_uart2_obj.rxStatus.s.empty);
    }
// *****************************************************************************
    /* Function:
        bool DRV_UART2_TXBufferIsFull (void)

      Summary:
        Returns the status of the transmit buffer

    */
    bool DRV_UART2_TXBufferIsFull (void)
    {
        return(drv_uart2_obj.txStatus.s.full);
    }
// *****************************************************************************
    /* Function:
        DRV_UART2_STATUS DRV_UART2_Status (void)

      Summary:
        Returns the status of the transmit and receive

    */
    DRV_UART2_STATUS DRV_UART2_Status (void)
    {
        return U2STA;
    }
/******************************************************************************/

#endif    
#if defined (_UART2)& defined (UART2_TXPOLL_RXINT)
    
    #ifndef DRV_UART2_CONFIG_TX_BYTEQ_LENGTH
            #define DRV_UART2_CONFIG_TX_BYTEQ_LENGTH 4
    #endif
    #ifndef DRV_UART2_CONFIG_RX_BYTEQ_LENGTH
            #define DRV_UART2_CONFIG_RX_BYTEQ_LENGTH 4
    #endif
    static uint8_t uart2_txByteQ[DRV_UART2_CONFIG_TX_BYTEQ_LENGTH] ;
    static uint8_t uart2_rxByteQ[DRV_UART2_CONFIG_RX_BYTEQ_LENGTH] ;

    #define DRV_UART2_TX_FIFO_LENGTH 1
    #define DRV_UART2_RX_FIFO_LENGTH 1 

    DRV_UART_OBJECT drv_uart2_obj;
        void configure_dspic33_UART2(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0)
    {

                //pin configurations
                //unlock registers
                __builtin_write_OSCCONL(OSCCON & ~(1<<6));//<<-----Bu satir sorgulanmali
                RPINR19bits.U2RXR = 109;     // U2RX fonksiyonu chipin 39ncu pinindeki RP109 pinine tanimlandi/RF4
                RPOR11bits.RP108R = 0b000011;// chipin 40nci pinindeki RP108 pinine U2TX fonksiyonu tanimlandi/RF5
                __builtin_write_OSCCONL(OSCCON | (1<<6));//<<-----Bu satir sorgulanmali
                //lock registers

                switch(brghilo0){
                    case BRG_HI:
                        U2MODEbits.BRGH = 1;
                        U2BRG = (((FCY/baudrate0)/4)-1);
                        break;
                    case BRG_LO:
                        U2MODEbits.BRGH = 0;
                        U2BRG = (((FCY/baudrate0)/16)-1);
                    default:
                        break;
                }
                switch(stopbit0){
                    case STOPBIT_ONE:
                        U2MODEbits.STSEL = 0;
                        break;
                    case STOPBIT_TWO:
                        U2MODEbits.STSEL = 1;
                        break;
                    default:
                        break;
                }
                switch(paritydata0){
                    case _9BIT_NOPAR:
                        U2MODEbits.PDSEL=3; 
                        break;
                    case _8BIT_ODDPAR:
                        U2MODEbits.PDSEL=2;
                        break;
                    case _8BIT_EVENPAR:
                        U2MODEbits.PDSEL=1;
                        break;
                    case _8BIT_NOPAR:
                        U2MODEbits.PDSEL=0;
                        break;
                    default:
                        break;
                }
                switch(txintmode0){
                    case TX_INT_MODE_2:
                        U2STAbits.UTXISEL1 =1;
                        U2STAbits.UTXISEL0 =0;
                        break;
                    case TX_INT_MODE_1:
                        U2STAbits.UTXISEL1 =0;
                        U2STAbits.UTXISEL0 =1;
                        break;
                    case TX_INT_MODE_0:
                        U2STAbits.UTXISEL1 =0;
                        U2STAbits.UTXISEL0 =0;
                        break;
                    default:
                        break;
                }
                switch(rxintmode0){
                    case RX_INT_MODE_3:
                        U2STAbits.URXISEL1 =1;
                        U2STAbits.URXISEL0 =1;
                        break;
                    case RX_INT_MODE_2:
                        U2STAbits.URXISEL1 =1;
                        U2STAbits.URXISEL0 =0;
                        break;
                    case RX_INT_MODE_0:
                        U2STAbits.URXISEL1 =0;
                        U2STAbits.URXISEL0 =0;
                        break;
                    default:
                        break;
                }

        U2MODEbits.UARTEN = 1;
        IEC1bits.U2RXIE = 1;
        U2STAbits.UTXEN = 1;
        
        drv_uart2_obj.txHead = uart2_txByteQ;
        drv_uart2_obj.txTail = uart2_txByteQ;
        drv_uart2_obj.rxHead = uart2_rxByteQ;
        drv_uart2_obj.rxTail = uart2_rxByteQ;
        drv_uart2_obj.rxStatus.s.empty = true;
        drv_uart2_obj.txStatus.s.empty = true;
        drv_uart2_obj.txStatus.s.full = false;
        drv_uart2_obj.rxStatus.s.full = false;
    }
/**************************************************************************/
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2RXInterrupt ( void )
    {
        int count = 0;

        while((count < DRV_UART2_RX_FIFO_LENGTH) && (U2STAbits.URXDA == 1))
        {
            count++;

            *drv_uart2_obj.rxTail = U2RXREG;

            drv_uart2_obj.rxTail++;

            if(drv_uart2_obj.rxTail == (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
            {
                drv_uart2_obj.rxTail = uart2_rxByteQ;
            }

            drv_uart2_obj.rxStatus.s.empty = false;

            if(drv_uart2_obj.rxTail == drv_uart2_obj.rxHead)
            {
                //Sets the flag RX full
                drv_uart2_obj.rxStatus.s.full = true;
                break;
            }

        }

        IFS1bits.U2RXIF = false;

    }
/**************************************************************************/
    void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2ErrInterrupt ( void )
    {
        if ((U2STAbits.OERR == 1))
        {
            U2STAbits.OERR = 0;
        }

        IFS4bits.U2EIF = false;
    } 
/**************************************************************************/
    /* Function:
    void DRV_UART1_TasksTX ( void )

  Summary:
    Maintains the driver's transmitter state machine in a polled manner

*/
    void DRV_UART2_TasksTX ( void )
    { 
    if(drv_uart2_obj.txStatus.s.empty)
    {
        return;
    }

    IFS1bits.U2TXIF = false;

    int count = 0;
    while((count < DRV_UART2_TX_FIFO_LENGTH)&& !(U2STAbits.UTXBF == 1))
    {
        count++;

        U2TXREG = *drv_uart2_obj.txHead;

        drv_uart2_obj.txHead++;

        if(drv_uart2_obj.txHead == (uart2_txByteQ + DRV_UART2_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart2_obj.txHead = uart2_txByteQ;
        }

        drv_uart2_obj.txStatus.s.full = false;

        if(drv_uart2_obj.txHead == drv_uart2_obj.txTail)
        {
            drv_uart2_obj.txStatus.s.empty = true;
            break;
        }
    }
}
/**************************************************************************/
    uint8_t DRV_UART2_ReadByte( void)
    {
        uint8_t data = 0;

        data = *drv_uart2_obj.rxHead;

        drv_uart2_obj.rxHead++;

        if (drv_uart2_obj.rxHead == (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
        {
            drv_uart2_obj.rxHead = uart2_rxByteQ;
        }

        if (drv_uart2_obj.rxHead == drv_uart2_obj.rxTail)
        {
            drv_uart2_obj.rxStatus.s.empty = true;
        }

        drv_uart2_obj.rxStatus.s.full = false;

        return data;
    }
/**************************************************************************/
    /*  Function:
        int DRV_UART2_Read(uint8_t *buffer, const unsigned int numbytes )

      Summary:
        Returns the number of bytes read by the UART2 peripheral

    */
    unsigned int DRV_UART2_Read( uint8_t *buffer ,  const unsigned int numbytes)
    {
        unsigned int numBytesRead = 0 ;
        while ( numBytesRead < ( numbytes ))
        {
            if( drv_uart2_obj.rxStatus.s.empty)
            {
                break;
            }
            else
            {
                buffer[numBytesRead++] = DRV_UART2_ReadByte () ;
            }
        }

        return numBytesRead ;
    }
// *****************************************************************************
    /* Function:
        void DRV_UART2_WriteByte( const uint8_t byte)

      Summary:
        Writes a byte of data to the UART2
     * This function writes 1 byte to the uart2_txByteQ. Than
     * sets the interrupt enable bit. This results in an interrupt
     * generation and program branches to the ISR. 

    */
    void DRV_UART2_WriteByte( const uint8_t byte)
    {
        *drv_uart2_obj.txTail = byte;

        drv_uart2_obj.txTail++;

        if (drv_uart2_obj.txTail == (uart2_txByteQ + DRV_UART2_CONFIG_TX_BYTEQ_LENGTH))
        {
            drv_uart2_obj.txTail = uart2_txByteQ;
        }

        drv_uart2_obj.txStatus.s.empty = false;

        if (drv_uart2_obj.txHead == drv_uart2_obj.txTail)
        {
            drv_uart2_obj.txStatus.s.full = true;
        }

    }
//*******************************************************************************
    /*  Function:
        unsigned int DRV_UART2_Write( uint8_t *buffer, const unsigned int numbytes )

      Summary:
        Returns the number of bytes written into the internal buffer

    */
    unsigned int DRV_UART2_Write( const uint8_t *buffer , const unsigned int numbytes )
    {
        unsigned int numBytesWritten = 0 ;

        while ( numBytesWritten < ( numbytes ))
        {
            if((drv_uart2_obj.txStatus.s.full))
            {
                break;
            }
            else
            {
                DRV_UART2_WriteByte (buffer[numBytesWritten++] ) ;
            }
        }

        return numBytesWritten ;

    } 
// *****************************************************************************
    /* Function:
        DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void)

      Summary:
        Returns the transmitter and receiver transfer status

    */
    DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void )
    {
        DRV_UART2_TRANSFER_STATUS status = 0;

        if(drv_uart2_obj.txStatus.s.full)
        {
            status |= DRV_UART2_TRANSFER_STATUS_TX_FULL;
        }

        if(drv_uart2_obj.txStatus.s.empty)
        {
            status |= DRV_UART2_TRANSFER_STATUS_TX_EMPTY;
        }

        if(drv_uart2_obj.rxStatus.s.full)
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_FULL;
        }

        if(drv_uart2_obj.rxStatus.s.empty)
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_EMPTY;
        }
        else
        {
            status |= DRV_UART2_TRANSFER_STATUS_RX_DATA_PRESENT;
        }
        return status;
    }
// *****************************************************************************
    /* Function:
      uint8_t DRV_UART2_Peek(uint16_t offset)

      Summary:
        Returns the character in the read sequence at the offset provided, without
        extracting it

    */
    uint8_t DRV_UART2_Peek(uint16_t offset)
    {
        if( (drv_uart2_obj.rxHead + offset) > (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH))
        {
          return uart2_rxByteQ[offset - (uart2_rxByteQ + DRV_UART2_CONFIG_RX_BYTEQ_LENGTH - drv_uart2_obj.rxHead)];
        }
        else
        {
          return *(drv_uart2_obj.rxHead + offset);
        }
    }
// *****************************************************************************
    /* Function:
      unsigned int DRV_UART2_RXBufferSizeGet (void)

      Summary:
        Returns the size of the receive buffer

    */
    unsigned int DRV_UART2_RXBufferSizeGet(void)
    {
        if(drv_uart2_obj.rxHead > drv_uart2_obj.rxTail)
        {
            return(DRV_UART2_CONFIG_RX_BYTEQ_LENGTH - (int)(drv_uart2_obj.rxHead) - (int)(drv_uart2_obj.rxTail));
        }
        else
        {
            return(drv_uart2_obj.rxTail - drv_uart2_obj.rxHead);
        }
    }
// *****************************************************************************
    /* Function:
      unsigned int DRV_UART2_TXBufferSizeGet (void)

      Summary:
        Returns the size of the transmit buffer

    */
    unsigned int DRV_UART2_TXBufferSizeGet(void)
    {
         if(drv_uart2_obj.txHead > drv_uart2_obj.txTail)
        {
            return(DRV_UART2_CONFIG_TX_BYTEQ_LENGTH - (int)drv_uart2_obj.txHead - (int)drv_uart2_obj.txTail);
        }
        else
        {
            return(drv_uart2_obj.txTail - drv_uart2_obj.txHead);
        }
    }
// *****************************************************************************
    /* Function:
      bool DRV_UART2_RXBufferIsEmpty (void)

      Summary:
        Returns the status of the receive buffer

    */
    bool DRV_UART2_RXBufferIsEmpty (void)
    {
        return(drv_uart2_obj.rxStatus.s.empty);
    }
// *****************************************************************************
    /* Function:
        bool DRV_UART2_TXBufferIsFull (void)

      Summary:
        Returns the status of the transmit buffer

    */
    bool DRV_UART2_TXBufferIsFull (void)
    {
        return(drv_uart2_obj.txStatus.s.full);
    }
// *****************************************************************************
    /* Function:
        DRV_UART2_STATUS DRV_UART2_Status (void)

      Summary:
        Returns the status of the transmit and receive

    */
    DRV_UART2_STATUS DRV_UART2_Status (void)
    {
        return U2STA;
    }
/******************************************************************************/

#endif    


#endif
