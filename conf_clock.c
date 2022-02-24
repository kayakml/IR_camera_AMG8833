//mylibraries 




#include "../my_headers/conf_clock.h"

#ifdef PIM_dsPIC33EP512MU810 
    void configure_clock(void){
        #if defined CLK_XT_4MHZ
            // According to related Configuration bits clock switching is enabled and device
            // is first started with FRC. With the below code we switch to primary XT oscillator.
                asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x02); // NewOSC = 010 XT  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
                while(OSCCONbits.COSC!=2){;} // wait for clock switch to occur - COSC = 2 -> current osc is XT
                 asm("DISI #0");

            #endif
        #if defined CLK_XT_4MHZ_WITH_PLL_16MHZ
                  asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
                while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - 
                                             // when switching happens COSC value become 3 
                                             // which means current osc is XT with PLL
                while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
                 asm("DISI #0");
            #endif
        #if defined CLK_XT_8MHZ/*START WITH FRC THAN SWITCH TO XT*/
            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x02); // NewOSC = 010 XT  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=2){;} // wait for clock switch to occur - COSC = 2 -> current osc is XT
             asm("DISI #0");
        #endif
        #if defined CLK_XT_8MHZ_WITH_PLL_32MHZ
             PLLFBD = 32 ;
             CLKDIVbits.PLLPOST = 4 ;
             CLKDIVbits.PLLPRE = 2 ;
                  asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
                while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - 
                                             // when switching happens COSC value become 3 
                                             // which means current osc is XT with PLL
                while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
                 asm("DISI #0");
            #endif
        #if defined CLK_XT_8MHZ_WITH_PLL_40MHZ
             PLLFBD = 40 ;
             CLKDIVbits.PLLPOST = 4 ;
             CLKDIVbits.PLLPRE = 2 ;

              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - COSC = 3 -> current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif
        #if defined CLK_XT_8MHZ_WITH_PLL_60MHZ
             PLLFBD = 60 ;
             CLKDIVbits.PLLPOST =4 ;
             CLKDIVbits.PLLPRE = 2 ;

              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - COSC = 3 -> current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif    
        #if defined CLK_XT_8MHZ_WITH_PLL_140MHZ
             PLLFBD = 68 ;
             CLKDIVbits.PLLPOST =0 ;
             CLKDIVbits.PLLPRE = 0 ;

            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - COSC = 3 -> current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
            asm("DISI #0");
        #endif    
        #if defined CLK_FRC_7_37_MHZ
                 ;
            #endif
        #if defined CLK_FRC_7_37_MHZ_WITH_PLL_140MHZ
             PLLFBD = 74 ;
             CLKDIVbits.PLLPOST =0 ;
             CLKDIVbits.PLLPRE = 0 ;

            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x01); // NewOSC = 001 FRCPLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - COSC = 1 -> current osc is FRCPLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
            asm("DISI #0");
        #endif
        #if defined CLK_FRC_7_37_MHZ_WITH_PLL_120MHZ
             PLLFBD = 65 ;
             CLKDIVbits.PLLPOST =0 ;
             CLKDIVbits.PLLPRE = 0 ;

            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x01); // NewOSC = 001 FRCPLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - COSC = 1 -> current osc is FRCPLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
            asm("DISI #0");
        #endif
        #if defined CLK_FRC_7_37_MHZ_WITH_PLL_80MHZ
             PLLFBD = 42 ; // deneme yanilma ile Fosc = 81.2Mhz olarak goruldu
              CLKDIVbits.PLLPOST =0 ;
             CLKDIVbits.PLLPRE = 0 ;

            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x01); // NewOSC = 001 FRCPLL  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - COSC = 1 -> current osc is FRCPLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
            asm("DISI #0");
        #endif
}
    /*TEST ROUTINES FOR CLOCK*/
    /*START*/   
//    void test_clock(){
//        T1CONbits.TON = 0; //disable timer
//        T1CONbits.TCS = 0; //internal instruction clock cycle
//        T1CONbits.TGATE = 0; //disable gated timer
//        T1CONbits.TCKPS = 0b11; //select 1:8
//        TMR1 = 0; // HER CLK CYCLEDA TMR1 REGISTERI 1 ARTACAK
//        PR1 = 1; // TMR1=PR1 OLDUGUNDA INTERRUPT FLAG CEKILECEK
//        
//        IPC0bits.T1IP = 0x01; //set timer1 interrupt priority level
//        IFS0bits.T1IF = 0;      // clear timer1 interrupt flag
//        IEC0bits.IC1IE = 1; //enable timer1 interrupt
//        
//        ANSELEbits.ANSE4 = 0;   //RE4 PINI DIGITAL OLARAK AYARLANDI
//        TRISEbits.TRISE4 = 0;   //RE4 PINI OUTPUT OLARAK AYARLANDI
//        LATEbits.LATE4 = 0;
//        
//        T1CONbits.TON = 1; // start timer
//    }
//    void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
//    {
//        /* Interrupt Service Routine code goes here */
//        IFS0bits.T1IF = 0; //Clear Timer1 interrupt flag
//        LATEbits.LATE4^=1; // LATE4 TEKI SINYAL SEVIYESINI TERSLIYOR
//    }
    /*END*/

#endif
#ifdef PIC24F16KA102 
    void configure_clock(void){
        #if defined CLK_FRC_8MHZ
             ;
        #endif
        #if defined CLK_FRC_WITH_PLL_32MHZ
        CLKDIVbits.RCDIV = 0; //8MHZ (divide by 1)
              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x01); // NewOSC = FRC with Postscaler and PLL
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - 
                                         // when switching happens COSC value become 3 
                                         // which means current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif
        #if defined CLK_FRC_WITH_PLL_16MHZ
             CLKDIVbits.RCDIV = 1; //4MHZ (divide by 2)
              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x01); // NewOSC = FRC with Postscaler and PLL
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - 
                                         // when switching happens COSC value become 1 
                                         // which means current osc is FRC with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif
        #if defined CLK_XT_4MHZ
        // According to related Configuration bits clock switching is enabled and device
        // is first started with FRC. With the below code we switch to primary XT oscillator.
            asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x02); // NewOSC = 010 XT  
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=2){;} // wait for clock switch to occur - COSC = 2 -> current osc is XT
             asm("DISI #0");

        #endif
        #if defined CLK_XT_4MHZ_WITH_PLL_16MHZ
              asm("DISI #0x3FFF");
               if(OSCCONbits.CLKLOCK == 0){
               
                __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
                __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
                while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - 
                                         // when switching happens COSC value become 3 
                                         // which means current osc is XT with PLL
                while(OSCCONbits.LOCK!=1); // wait for PLL to lock
                   
               }
             asm("DISI #0");
        #endif

        #if defined CLK_XT_8MHZ

            asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x02); // NewOSC = 010 XT  
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=2){;} // wait for clock switch to occur - COSC = 2 -> current osc is XT
             asm("DISI #0");

        #endif
        #if defined CLK_XT_8MHZ_WITH_PLL_32MHZ
              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x03); // NewOSC = 011 XT with PLL  
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=3){;} // wait for clock switch to occur - 
                                         // when switching happens COSC value become 3 
                                         // which means current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif

}
#endif
#ifdef PIC24FJ64GA004 
    void configure_clock(void){
        #if defined CLK_FRC_8MHZ
            //According to PIC24F Oscillator ref manual default clock configuration
            //in which the user does nothing the clock is configured to FOSC = 4MHZ because of
            //default settings of FNOSC. At the beginning it is configured as (FRCDIV). 
            //So if we want to use FRC so as to get FOSC=8MHZ
            //then we have to change default FRCDIV to FRC ;
            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x00); // NewOSC = 000 FRC  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=0){;} // wait for clock switch to occur - COSC = 0 -> current osc is FRC
            asm("DISI #0");
        #endif
        #if defined CLK_XT_8MHZ
            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x02); // NewOSC = 010 XT  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=2){;} // wait for clock switch to occur - COSC = 2 -> current osc is XT
            asm("DISI #0");
        #endif
        #if defined CLK_FRC_DEFAULT_FRCDIV_4MHZ
            ; // DO NOTHING
        #endif 

}
#endif
#ifdef PIC24FJ128GA306 
    void configure_clock(void){
        #if defined CLK_FRC_8MHZ
            //According to PIC24F Oscillator ref manual default clock configuration
            //in which the user does nothing the clock is configured to FOSC = 4MHZ thanks to
            //default postscaler(FRCDIV) bits. So if we want to use FRC so as to get FOSC=8MHZ
            //then we have to change default FRCDIV bit values;
            asm("DISI #0x3FFF");
            __builtin_write_OSCCONH(0x00); // NewOSC = 000 FRC  
            __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=0){;} // wait for clock switch to occur - COSC = 0 -> current osc is FRC
            asm("DISI #0");
        #endif
        #if defined CLK_FRC_WITH_PLL_32MHZ_with_ClockSwitching
        CLKDIVbits.RCDIV = 0; //8MHZ (divide by 1)
              asm("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x01); // NewOSC = FRC with Postscaler and PLL
        __builtin_write_OSCCONL(OSCCON | 0x01); // request oscillator switch 
            while(OSCCONbits.COSC!=1){;} // wait for clock switch to occur - 
                                         // when switching happens COSC value become 3 
                                         // which means current osc is XT with PLL
            while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
             asm("DISI #0");
        #endif
        #if defined CLK_FRC_WITH_PLL_32MHZ_without_ClockSwitching
        CLKDIVbits.RCDIV = 0; //8MHZ (divide by 1)
            asm("DISI #0x3FFF");
                while(OSCCONbits.LOCK!=1){;} // wait for PLL to lock
            asm("DISI #0");
        #endif

}
#endif
#ifdef PIC18F
    #ifdef Bedheater_LCD
        void configure_clock(void){
        #ifdef InternalClock_8Mhz
            OSCCON = 0x72;
        #endif 
        }
    #endif
#endif
    




