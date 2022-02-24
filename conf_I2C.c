//mylibraries
#include <stdio.h>  
#include "../my_headers/conf_I2C.h"
#include "../../my_libraries/my_headers/conf_uart.h"




#ifdef LCD
#include "../my_headers/conf_lcd.h"
#endif

//I2C1BRG formulunu kontrol et


#if defined LCD
void report_write_Error_to_LCD() {
    LCD_PutString("ERROR IN I2C WRITE",18 );
  }
void report_read_Error_to_LCD() {
    LCD_PutString("ERROR IN I2C READ",17 );
  }
#endif
//PRIMITIVE COMMANDS
void configI2C1(uint16_t u16_FkHZ) {
    #ifdef PIC24F_I2C1_MODULE
         I2C1BRG = (((FCY/1000)/u16_FkHZ)- (((FCY/10000000))))-1;
//        I2C1BRG = 9; //FCY=4MHZ; Fscl = 400khz
     I2C1CONbits.I2CEN = 1;    
    #endif
    #ifdef AI2C1_MODULE
        I2C1BRG = (FCY/1000L)/((uint16_t) u16_FkHZ);
        I2C1CONbits.I2CEN = 1;
    #endif
    #ifdef PIC24F16KA102_I2C1
        I2C1BRG = (((FCY/1000)/u16_FkHZ)- (((FCY/1000000))))-1;
        I2C1CONbits.I2CEN = 1;
    #endif
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
            #pragma config ALTI2C1 = ON            // Alternate I2C pins for I2C1 (ASDA1/ASCK1 pins are selected as the I/O pins for I2C1)
            #pragma config ALTI2C2 = OFF            // Alternate I2C pins for I2C2 (SDA2/SCK2 pins are selected as the I/O pins for I2C2)
              I2C1BRG = ((FCY/1000)/u16_FkHZ)- (((FCY/1000000)-130)/1000)-2;
              I2C1CONbits.I2CEN = 1;
        #endif
        #ifdef I2C2_MODULE
            uint16_t u16_temp;
            u16_temp = (FCY/1000L)/((uint16_t) u16_FkHZ);
            I2C2BRG = u16_temp;
            I2C2CONbits.I2CEN = 1;
        #endif
        #ifdef AI2C1_MODULE
            uint16_t u16_temp;
            u16_temp = (FCY/1000L)/((uint16_t) u16_FkHZ);
            I2C1BRG = u16_temp;
            I2C1CONbits.I2CEN = 1;
        #endif
    #endif
    }
void startI2C1(void) {
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
            uint8_t u8_wdtState;
            u8_wdtState = _SWDTEN;  //save WDT state
            _SWDTEN = 1; //enable WDT--because we didnt enable WDT from configuration bits this part does not have any effect
            I2C1CONbits.SEN = 1; // initiate start
            while (I2C1CONbits.SEN);  // wait until start finished
            _SWDTEN = u8_wdtState;  //restore WDT
            sz_lastTimeoutError = NULL;
        #endif
        #ifdef I2C2_MODULE
            I2C2CONbits.SEN = 1;        // initiate start
            while (I2C2CONbits.SEN);    // wait until start finished
                                         //In addition to control I2C2CON<SEN> bit to ensure if start process completed 
                                         //we can poll also MI2C2IF interrupt
                                         //After Start SDA->LOW SCL->LOW
        #endif
        #ifdef AI2C1_MODULE
            I2C1CONbits.SEN = 1;        // initiate start
            while (I2C1CONbits.SEN);    // wait until start finished
                                         //In addition to control I2C2CON<SEN> bit to ensure if start process completed 
                                         //we can poll also MI2C2IF interrupt
                                         //After Start SDA->LOW SCL->LOW
            //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
            //IFS1bits.MI2C1IF = 0;
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
            I2C1CONbits.SEN = 1;        // initiate start
            while (I2C1CONbits.SEN);    // wait until start finished
                                         //In addition to control I2C2CON<SEN> bit to ensure if start process completed 
                                         //we can poll also MI2C2IF interrupt
                                         //After Start SDA->LOW SCL->LOW
            //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
            //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef AI2C1_MODULE
        I2C1CONbits.SEN = 1;        // initiate start
        while (I2C1CONbits.SEN);    // wait until start finished
                         //In addition to control I2C2CON<SEN> bit to ensure if start process completed 
                         //we can poll also MI2C2IF interrupt
                         //After Start SDA->LOW SCL->LOW
        //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef PIC24F_I2C1_MODULE
        I2C1CONbits.SEN = 1;        // initiate start
        while (I2C1CONbits.SEN);    // wait until start finished
                             //In addition to control I2C2CON<SEN> bit to ensure if start process completed 
                             //we can poll also MI2C2IF interrupt
                             //After Start SDA->LOW SCL->LOW
        //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif
    }
void rstartI2C1(void) { 
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
            uint8_t u8_wdtState;
            sz_lastTimeoutError = "I2C1 RStart";
            u8_wdtState = _SWDTEN;  //save WDT state
            _SWDTEN = 1;  //enable WDT
            I2C1CONbits.RSEN = 1; // initiate start
             wait until start finished
            while (I2C1CONbits.RSEN);
            _SWDTEN = u8_wdtState;  //restore WDT
            sz_lastTimeoutError = NULL;
        #endif
        #ifdef I2C2_MODULE
            I2C2CONbits.RSEN = 1; // initiate start
            while (I2C2CONbits.RSEN);  // wait until start finished  
        #endif
        #ifdef AI2C1_MODULE
            I2C1CONbits.RSEN = 1; // initiate start
            while (I2C1CONbits.RSEN);  // wait until start finished  
                //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
              //IFS1bits.MI2C1IF = 0;
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
        I2C1CONbits.RSEN = 1; // initiate start
        while (I2C1CONbits.RSEN);  // wait until start finished  
        //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef AI2C1_MODULE
        I2C1CONbits.RSEN = 1; // initiate start
        while (I2C1CONbits.RSEN);  // wait until start finished  
          //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef PIC24F_I2C1_MODULE
        // repeated start
        I2C1CONbits.RSEN = 1; // initiate start
        while (I2C1CONbits.RSEN);  // wait until start finished  
          //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif        
    }
void stopI2C1(void) {     
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
              uint8_t u8_wdtState;

              sz_lastTimeoutError = "I2C1 Stop";
              u8_wdtState = _SWDTEN;  //save WDT state
              _SWDTEN = 1;  //enable WDT
              I2C1CONbits.PEN=1;   // initiate stop, PEN=1
              wait until stop finished
              while (I2C1CONbits.PEN);
              _SWDTEN = u8_wdtState;  //restore WDT
              sz_lastTimeoutError = NULL;
        #endif
        #ifdef I2C2_MODULE
               I2C2CONbits.PEN=1;              // initiate stop, PEN=1
               while (I2C2CONbits.PEN);        //wait until stop finished
           
        #endif
        #ifdef AI2C1_MODULE
               I2C1CONbits.PEN=1;              // initiate stop, PEN=1
               while (I2C1CONbits.PEN);        //wait until stop finished
                   //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
               //IFS1bits.MI2C1IF = 0;
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
            I2C1CONbits.PEN=1;              // initiate stop, PEN=1
            while (I2C1CONbits.PEN);        //wait until stop finished
            //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
            //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef AI2C1_MODULE
        I2C1CONbits.PEN=1;              // initiate stop, PEN=1
        while (I2C1CONbits.PEN);        //wait until stop finished
            //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
        //IFS1bits.MI2C1IF = 0;
    #endif
    #ifdef PIC24F_I2C1_MODULE
            I2C1CONbits.PEN=1;              // initiate stop, PEN=1
            while (I2C1CONbits.PEN);        //wait until stop finished
            //while (!IFS1bits.MI2C1IF); //I2C.odt dokumaninin YOUTUBE bolumundeki DEMO programdan alindi. Denenmeli??
            //IFS1bits.MI2C1IF = 0;
    #endif
    }
void putI2C1(uint8_t u8_val) {
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
          uint8_t u8_wdtState;

          sz_lastTimeoutError = "I2C1 Put";
          u8_wdtState = _SWDTEN;  //save WDT state
          _SWDTEN = 1;       //enable WDT
          I2C1TRN = u8_val;  // write byte
          while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
          _SWDTEN = u8_wdtState;  //restore WDT
          sz_lastTimeoutError = NULL;
          if (I2C1STATbits.ACKSTAT != I2C_ACK) {
            //NAK returned
            reportError();
          }
        #endif
        #ifdef I2C2_MODULE
            I2C2TRN = u8_val;                         // this starts the transmission, during 8 SCL clock time transmission continues
                                                       //Check I2C2STAT<TBF> to see if I2C2TRN is full or empty. 
                                                       //On the falling edge of 8th clock TBF automatically is cleared
                                                       //and master releases SDA line (SDA gets high))

            while (I2C2STATbits.TRSTAT);              // wait for 8bits+ACK bit to complete their times 

            if (I2C2STATbits.ACKSTAT != I2C_ACK) {
              reportError();                          //NAK returned
            }
        #endif
        #ifdef AI2C1_MODULE
            I2C1TRN = u8_val;                         // this starts the transmission, during 8 SCL clock time transmission continues
                                                       //Check I2C2STAT<TBF> to see if I2C2TRN is full or empty. 
                                                       //On the falling edge of 8th clock TBF automatically is cleared
                                                       //and master releases SDA line (SDA gets high))

            while (I2C1STATbits.TRSTAT);              // wait for 8bits+ACK bit to complete their times 

            if (I2C1STATbits.ACKSTAT != I2C_ACK) {
                stopI2C1();
              report_write_Error();                          //NAK returned
            }
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
        I2C1TRN = u8_val;                         // this starts the transmission, during 8 SCL clock time transmission continues
                                                   //Check I2C2STAT<TBF> to see if I2C2TRN is full or empty. 
                                                   //On the falling edge of 8th clock TBF automatically is cleared
                                                   //and master releases SDA line (SDA gets high))
        while (I2C1STATbits.TRSTAT);              // wait for 8bits+ACK bit to complete their times 
        if (I2C1STATbits.ACKSTAT != I2C_ACK) {
            stopI2C1();
        #if defined LCD
                report_write_Error();                   //NAK returned
        #endif
        }
    
    #endif
    #ifdef AI2C1_MODULE
        I2C1TRN = u8_val;                         // this starts the transmission, during 8 SCL clock time transmission continues
                                                   //Check I2C2STAT<TBF> to see if I2C2TRN is full or empty. 
                                                   //On the falling edge of 8th clock TBF automatically is cleared
                                                   //and master releases SDA line (SDA gets high))
        while (I2C1STATbits.TRSTAT);              // wait for 8bits+ACK bit to complete their times 
        if (I2C1STATbits.ACKSTAT != I2C_ACK) {
            stopI2C1();
          report_write_Error();                          //NAK returned
        }

    #endif
    #ifdef PIC24F_I2C1_MODULE
        I2C1TRN = u8_val;                         // this starts the transmission, during 8 SCL clock time transmission continues
                                                 //Check I2C2STAT<TBF> to see if I2C2TRN is full or empty. 
                                                 //On the falling edge of 8th clock TBF automatically is cleared
                                                 //and master releases SDA line (SDA gets high))
        while (I2C1STATbits.TRSTAT);              // wait for 8bits+ACK bit to complete their times 
        if (I2C1STATbits.ACKSTAT != I2C_ACK) {
          stopI2C1();
        #if defined LCD
                report_write_Error();                   //NAK returned
        #endif
        #if defined uart_for_debug
                outString("I2C write error\n");                   //NAK returned
        #endif
        }
    #endif

                                                //now module is in IDLE mode until the next data is loaded into the I2C2TRN.
    }
uint8_t putNoAckCheckI2C1(uint8_t u8_val) {
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
            uint8_t u8_wdtState;

            sz_lastTimeoutError = "I2C1 Put";
            u8_wdtState = _SWDTEN;  //save WDT state
            _SWDTEN = 1;       //enable WDT
            I2C1TRN = u8_val;  // write byte
            while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
            _SWDTEN = u8_wdtState;  //restore WDT
            sz_lastTimeoutError = NULL;
            return(I2C1STATbits.ACKSTAT);
        #endif
        #ifdef I2C2_MODULE
            I2C2TRN = u8_val;  // write byte
            while (I2C2STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
            return(I2C2STATbits.ACKSTAT);
        #endif
        #ifdef AI2C1_MODULE
            I2C1TRN = u8_val;  // write byte
            while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
            return(I2C1STATbits.ACKSTAT);
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
          I2C1TRN = u8_val;  // write byte
          while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
          return(I2C1STATbits.ACKSTAT);
    #endif
    #ifdef AI2C1_MODULE
        I2C1TRN = u8_val;  // write byte
        while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
        return(I2C1STATbits.ACKSTAT);
    #endif
    #ifdef PIC24F_I2C1_MODULE
          I2C1TRN = u8_val;  // write byte
          while (I2C1STATbits.TRSTAT); // wait for 8bits+ ack bit to finish
          return(I2C1STATbits.ACKSTAT);
    #endif
    }
uint8_t getI2C1(uint8_t u8_ack2Send) {
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef I2C1_MODULE
          uint8_t u8_wdtState;
          uint8_t u8_inByte;

          sz_lastTimeoutError = "I2C1 Get";
          u8_wdtState = _SWDTEN;              //save WDT state
          _SWDTEN = 1;                        //enable WDT
          while (I2C1CON & 0x1F);         //wait for idle condition
          I2C1CONbits.RCEN = 1;           //enable receive
          while (!I2C1STATbits.RBF);      //wait for receive byte
          CLRWDT();
          __builtin_clrwdt();
          u8_inByte = I2C1RCV;            //read byte;
          wait for idle condition before attempting ACK
          while (I2C1CON & 0x1F);         //lower 5 bits must be 0
          I2C1CONbits.ACKDT = u8_ack2Send; //ACK bit to send back on receive
          I2C1CONbits.ACKEN = 1;          //enable ACKbit transmittion
          while (I2C1CONbits.ACKEN);      //wait for completion
          _SWDTEN = u8_wdtState;              //restore WDT
          sz_lastTimeoutError = NULL;
          return(u8_inByte);                  //return the value
        #endif
        #ifdef I2C2_MODULE
           uint8_t u8_inByte;

           //-------------------------------------->>ENABLE WATCHDOG here
           while (I2C2CON & 0x1F);                 // NoSTART & NoREP.START & NoSTOP & NoRECEIVE & NoACK == IDLE
           I2C2CONbits.RCEN = 1;                   //enable receive
           while (!I2C2STATbits.RBF);              //Receive completes, I2C2RCV buffer is full
           u8_inByte = I2C2RCV;                    //read byte;
                                                   //wait for idle condition before attempting ACK
           while (I2C2CON & 0x1F);                 //lower 5 bits must be 0
           I2C2CONbits.ACKDT = u8_ack2Send;        //ACK bit to send back on receive
           I2C2CONbits.ACKEN = 1;                  //enable ACKbit transmission
           while (I2C2CONbits.ACKEN);              //After 2 baud periods ACKEN bit automatically clears 
           return(u8_inByte);                      //return the value
        #endif
        #ifdef AI2C1_MODULE
           uint8_t u8_inByte;

           //-------------------------------------->>ENABLE WATCHDOG here
           while (I2C1CON & 0x1F);                 // NoSTART & NoREP.START & NoSTOP & NoRECEIVE & NoACK == IDLE
           I2C1CONbits.RCEN = 1;                   //enable receive
           while (!I2C1STATbits.RBF);              //Receive completes, I2C2RCV buffer is full
           u8_inByte = I2C1RCV;                    //read byte;
                                                   //wait for idle condition before attempting ACK
           while (I2C1CON & 0x1F);                 //lower 5 bits must be 0
           I2C1CONbits.ACKDT = u8_ack2Send;        //ACK bit to send back on receive
           I2C1CONbits.ACKEN = 1;                  //enable ACKbit transmission
           while (I2C1CONbits.ACKEN);              //After 2 baud periods ACKEN bit automatically clears 
           return(u8_inByte);                      //return the value
        #endif
    #endif
    #ifdef PIC24F16KA102_I2C1
        uint8_t u8_inByte;
        //-------------------------------------->>ENABLE WATCHDOG here
        while (I2C1CON & 0x1F);                 // NoSTART & NoREP.START & NoSTOP & NoRECEIVE & NoACK == IDLE
        I2C1CONbits.RCEN = 1;                   //enable receive
        while (!I2C1STATbits.RBF);              //Receive completes, I2C2RCV buffer is full
        u8_inByte = I2C1RCV;                    //read byte;
                                                //wait for idle condition before attempting ACK
        while (I2C1CON & 0x1F);                 //lower 5 bits must be 0
        I2C1CONbits.ACKDT = u8_ack2Send;        //ACK bit to send back on receive
        I2C1CONbits.ACKEN = 1;                  //enable ACKbit transmission
        while (I2C1CONbits.ACKEN);              //After 2 baud periods ACKEN bit automatically clears 
        return(u8_inByte);                      //return the value
    #endif
    #ifdef AI2C1_MODULE
        uint8_t u8_inByte;
        //-------------------------------------->>ENABLE WATCHDOG here
        while (I2C1CON & 0x1F);                 // NoSTART & NoREP.START & NoSTOP & NoRECEIVE & NoACK == IDLE
        I2C1CONbits.RCEN = 1;                   //enable receive
        while (!I2C1STATbits.RBF);              //Receive completes, I2C2RCV buffer is full
        u8_inByte = I2C1RCV;                    //read byte;
                                                //wait for idle condition before attempting ACK
        while (I2C1CON & 0x1F);                 //lower 5 bits must be 0
        I2C1CONbits.ACKDT = u8_ack2Send;        //ACK bit to send back on receive
        I2C1CONbits.ACKEN = 1;                  //enable ACKbit transmission
        while (I2C1CONbits.ACKEN);              //After 2 baud periods ACKEN bit automatically clears 
        return(u8_inByte);                      //return the value
    #endif
    #ifdef PIC24F_I2C1_MODULE
        uint8_t u8_inByte;
        //-------------------------------------->>ENABLE WATCHDOG here
        while (I2C1CON & 0x1F);                 // NoSTART & NoREP.START & NoSTOP & NoRECEIVE & NoACK == IDLE
        I2C1CONbits.RCEN = 1;                   //enable receive 
 /*-error--->*/       while (!I2C1STATbits.RBF);              //Receive completes, I2C2RCV buffer is full
        u8_inByte = I2C1RCV;                    //read byte;
                                               //wait for idle condition before attempting ACK
        while (I2C1CON & 0x1F);                 //lower 5 bits must be 0
        I2C1CONbits.ACKDT = u8_ack2Send;        //ACK bit to send back on receive
        I2C1CONbits.ACKEN = 1;                  //enable ACKbit transmission
        while (I2C1CONbits.ACKEN);              //After 2 baud periods ACKEN bit automatically clears 
        return(u8_inByte);                      //return the value 
    #endif
                    
    }
//I2C FUNCTIONS
#if  (defined (I2C1_MODULE)||defined (AI2C1_MODULE)||defined (PIC24F16KA102_I2C1)||defined (PIC24F_I2C1_MODULE))
    void write1I2C1(uint8_t u8_addr,uint8_t u8_d1) {
      startI2C1();
      putI2C1(I2C_WADDR(u8_addr)); //we put the address where we want to write
      putI2C1(u8_d1); // we send the data that is to be written
      stopI2C1();
    }
    void write2I2C1(uint8_t u8_addr,uint8_t u8_d1, uint8_t u8_d2) {
      startI2C1();
      putI2C1(I2C_WADDR(u8_addr)); //we send the address
      putI2C1(u8_d1); //we send the first byte of data
      putI2C1(u8_d2); //we send the 2nd byte of data
      stopI2C1();
    }
    void writeNI2C1(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt) {
      uint16_t u16_i;
      startI2C1();
      putI2C1(I2C_WADDR(u8_addr));
      for (u16_i=0; u16_i < u16_cnt; u16_i++) {
        putI2C1(*pu8_data);
        pu8_data++;
      }
      stopI2C1();
    }
    void read1I2C1(uint8_t u8_addr,uint8_t* pu8_d1) {
      startI2C1();
      putI2C1(I2C_RADDR(u8_addr));
      *pu8_d1 = getI2C1(I2C_NAK); //last ack bit from master to slave during read must be a NAK
      stopI2C1();
    }
    void read2I2C1(uint8_t u8_addr,uint8_t* pu8_d1, uint8_t* pu8_d2) {
      startI2C1();
      putI2C1(I2C_RADDR(u8_addr));
      *pu8_d1 = getI2C1(I2C_ACK);
      *pu8_d2 = getI2C1(I2C_NAK);
      stopI2C1();
    }
    void readNI2C1(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt) {
      uint16_t u16_i;
      startI2C1();
      putI2C1(I2C_RADDR(u8_addr));
      for (u16_i=0; u16_i < u16_cnt; u16_i++) {
        if (u16_i != u16_cnt-1) *pu8_data = getI2C1(I2C_ACK);
        else *pu8_data = getI2C1(I2C_NAK);
        pu8_data++;
      }
      stopI2C1();
    }
#endif
#if defined  (I2C2_MODULE)
       void write1I2C2(uint8_t u8_addr,uint8_t u8_d1) {
         startI2C2();
         putI2C2(I2C_WADDR(u8_addr));
         putI2C2(u8_d1);
         stopI2C2();
       }
       void write2I2C2(uint8_t u8_addr,uint8_t u8_d1, uint8_t u8_d2) {
         startI2C2();
         putI2C2(I2C_WADDR(u8_addr));
         putI2C2(u8_d1);
         putI2C2(u8_d2);
         stopI2C2();
       }
       void writeNI2C2(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt) {
         uint16_t u16_i;
         startI2C2();
         putI2C2(I2C_WADDR(u8_addr));
         for (u16_i=0; u16_i < u16_cnt; u16_i++) {
           putI2C2(*pu8_data);
           pu8_data++;
         }
         stopI2C2();
       }
       void read1I2C2(uint8_t u8_addr,uint8_t* pu8_d1) {
         startI2C2();
         putI2C2(I2C_RADDR(u8_addr));
         *pu8_d1 = getI2C2(I2C_NAK); //last ack bit from master to slave during read must be a NAK
         stopI2C2();
       }
       void read2I2C2(uint8_t u8_addr,uint8_t* pu8_d1, uint8_t* pu8_d2) {
         startI2C2();
         putI2C2(I2C_RADDR(u8_addr));
         *pu8_d1 = getI2C2(I2C_ACK);
         *pu8_d2 = getI2C2(I2C_NAK);
         stopI2C2();
       }
       void readNI2C2(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt) {
      uint16_t u16_i;
      startI2C2();
      putI2C2(I2C_RADDR(u8_addr));
      for (u16_i=0; u16_i < u16_cnt; u16_i++) {
        if (u16_i != u16_cnt-1) *pu8_data = getI2C2(I2C_ACK);
        else *pu8_data = getI2C2(I2C_NAK);
        pu8_data++;
      }
      stopI2C2();
    }
#endif
    
