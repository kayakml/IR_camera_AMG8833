//mylibraries


#include "../../my_libraries/my_headers/conf_SPI.h"





uint8_t configure_SPI_port_pins(uint8_t module_number){
    #ifdef PIC24FJ128GA306
        switch(module_number){
            case spi1_module:
            __builtin_write_OSCCONL(OSCCON & 0xbf);
            RPINR20bits.SDI1R = 16; //RP16 as SDI1 ------->PIN33
            RPINR20bits.SCK1R = 30; //RP30 as SCK1Input--->PIN34
            RPOR15bits.RP30R = 8;   //RP30 as SCK1Output-->PIN34
            RPOR1bits.RP2R = 7;     //RP2 as SDO1--------->PIN42
            __builtin_write_OSCCONL(OSCCON | 0x40);
            break;
        }
        return 1;

    #endif
    #ifdef PIC24FJ64GA004
        switch(module_number){
            case spi1_module:


                AD1PCFGbits.PCFG7 = 1;  // AN7/RP17(=SDI1)/CN9/RC1 is configured as digital
                TRISCbits.TRISC1 = 1;   // pin54 of explorer 16/32

                AD1PCFGbits.PCFG6 = 1;  // AN6/RP16(=SDO1)/CN8/RC0 is configured as digital            
                TRISCbits.TRISC0 = 1;   // pin53 of explorer 16/32

                AD1PCFGbits.PCFG9 = 1;  // AN9/RP15(=SCK1)/C11/PMPCS1/RB15 is configured as digital
                TRISBbits.TRISB15 = 0;  // pin55 of explorer 16/32

                                        //RP15,RP16,RP17 are selected because in PIM _ PIC24FJ64GA004.pdf table2 it is stated that
        /*RP15*/RPINR20bits.SCK1R = 15; //RP15  |SCK1input->PIN15(pf pic)---->PIN55(of explorer16/32 board)
        /*RP15*/RPOR7bits.RP15R = 8;    //RP15  |SCK1output
        /*RP16*/RPOR8bits.RP16R = 7;    //RP16  |SDO1->PIN25(of pic)---->pin53(of explorer16/32 board)
        /*RP17*/RPINR20bits.SDI1R = 26; //RP17  |SDI1->PIN26(of pic)---->PIN54(of explorer16/32 board) 
                break;
        }
        return 1;

        #endif     
    #ifdef PIM_dsPIC33EP512MU810
        switch(module_number){
            case spi1_module:

    //            TRISFbits.TRISF3 = 1;   //USBID/RP99(=SDI1)/RF3 is configured as digital input
    //            RPINR20bits.SDI1R = 99; //RP99  |SDI1->PIN51(of pic)---->PIN54(of explorer16/32 board) 

                 /*unlock registers*/__builtin_write_OSCCONL(OSCCON & ~(1<<6));
                TRISFbits.TRISF2 = 0;    // RP98(=SDO1)/RF2 is configured as digital output
                RPOR8bits.RP98R = 5;     // pin52 of dspic33EP512MU810---pin52 of explorer16/32 board

                TRISFbits.TRISF3 = 1;    // USBID/RP99(=SDI1)/RF3
                RPINR20bits.SDI1R = 99;  // pin51 of dspic33EP512MU810---pin51 of explorer16/32 board   

                TRISFbits.TRISF8 = 0;    //RP104(=SCK1)/RF8
                RPINR20bits.SCK1R = 104; //pin53 of dspic33EP512MU810---pin53 of explorer16/32 board
                RPOR11bits.RP104R = 6;
                /*lock registers*/__builtin_write_OSCCONL(OSCCON | ~(1<<6));

                break;
        }
        return 1;

        #endif     
}
void configure_SPI_data_transmission(uint8_t trans_type){
    #ifdef PIC24FJ128GA306
    switch(trans_type){
        case _8bit_data_transmission:
            SPI1CON1bits.MODE16 = 0; 
            break;
        case _16bit_data_transmission:
            SPI1CON1bits.MODE16 = 1;
            break;
    }
    #endif
    #ifdef PIC24FJ64GA004
    switch(trans_type){
        case _8bit_data_transmission:
            SPI1CON1bits.MODE16 = 0; 
            break;
        case _16bit_data_transmission:
            SPI1CON1bits.MODE16 = 1;
            break;
    }
    #endif
    #ifdef PIM_dsPIC33EP512MU810
    switch(trans_type){
        case _8bit_data_transmission:
            SPI1CON1bits.MODE16 = 0; 
            break;
        case _16bit_data_transmission:
            SPI1CON1bits.MODE16 = 1;
            break;
    }
    #endif
}
void configure_SPI_clock_frequency(void){
    #ifdef PIC24FJ128GA306
        //FCY = 4 MHZ
        SPI1CON1bits.PPRE = 3; //3->1:1,2->4:1,1->16:1,0->64:1
        SPI1CON1bits.SPRE = 7 ; //7->1:1,6->2:1,5->3:1,4->4:1,3->5:1,2->6:1,1->7:1,0->8:1,
        //SCK = 1MHZ        
    #endif
    #ifdef PIC24FJ64GA004
        //FCY = 4 MHZ
        SPI1CON1bits.PPRE = 2; //4:1
        SPI1CON1bits.SPRE = 5 ; //4:1
        //SCK = 250KHz        
    #endif
    #ifdef PIM_dsPIC33EP512MU810
        #ifdef dspic33_deneme
                //FCY = 4 MHZ
                SPI1CON1bits.PPRE = 1; 
                SPI1CON1bits.SPRE = 3; 
                //SCK = 250KHz     
        #endif
        #ifdef myOV7670
                //FCY = 70Mhz
                SPI1CON1bits.PPRE = 1; //16:1
                SPI1CON1bits.SPRE = 6; //2:1
                //SCK = 250KHz     
        #endif
    #endif
}
void configure_clk_polarity_edge(uint8_t polarity, uint8_t edge){
    #ifdef PIC24FJ128GA306
    switch (polarity){ 
        case high_level_idle: 
            SPI1CON1bits.CKP = 1;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 0;
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 1; // if master mode , 4 wire transmission is mandatory according to ref.manual
                    break;
            }
            break;
        case low_level_idle:
            SPI1CON1bits.CKP = 0;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 1; // if master mode , 4 wire transmission is mandatory according to ref.manual
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 0;
                    break;
            }
            break;
    
    }
#endif
    #ifdef PIC24FJ64GA004
    switch (polarity){ 
        case high_level_idle: 
            SPI1CON1bits.CKP = 1;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 0;
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 1;
                    break;
            }
            break;
        case low_level_idle:
            SPI1CON1bits.CKP = 0;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 1;
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 0;
                    break;
            }
            break;
    
    }
#endif
    #ifdef PIM_dsPIC33EP512MU810
    switch (polarity){ 
        case high_level_idle: 
            SPI1CON1bits.CKP = 1;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 0;
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 1;
                    break;
            }
            break;
        case low_level_idle:
            SPI1CON1bits.CKP = 0;
            switch(edge){
                case high_to_low:
                    SPI1CON1bits.CKE = 1;
                    break;
                case low_to_high:
                    SPI1CON1bits.CKE = 0;
                    break;
            }
            break;
    
    }
#endif
}
void complete_SPI_configuration (uint8_t transmission_wire, uint8_t module_mode){
    #ifdef PIC24FJ128GA306
        switch(transmission_wire){
            case _2_wire_transmmission:
                SPI1CON1bits.DISSDO = 1 ;   // SDOx pin is not used by the module; 
                break;                      // pin functions as I/O  SDOx pin is controlled by the module
            case _3_wire_transmmission:
                // SPI1CON1bits.DISSDO = 0 /*Default Value*/ It is not 2 wire transmission
                // SPI1CON2bits.FRMEN = 0 /*Default Value*/ It is not 4 wire transmission
                // SPI1CON1bits.SSEN = 0  /*Default Value*/ It is not 4 wire transmission
                break;
            case _4_wire_transmmission:
                // When do we use 4 of the SPI pins ? /*PIC24f SPI Reference Manual */
                // when frame spi mode is enabled
                // when slave select feature is used
                // when standard spi mode is used with CKE = 1 
                break;
            default:
                break;
        }
        switch (module_mode){
            case master_mode:
                SPI1CON1bits.MSTEN = 1;
                break;
            case slave_mode:
                SPI1CON1bits.MSTEN = 0;
                break;
            default:
                break;

        }
        SPI1STATbits.SPIEN = 1;
    #endif
    #ifdef PIC24FJ64GA004
        switch(transmission_wire){
            case _2_wire_transmmission:
                SPI1CON1bits.DISSDO = 1 ; // SDOx pin is not used by the module; pin functions as I/O  SDOx pin is controlled by the module
                break;
            case _3_wire_transmmission:
                break;
            case _4_wire_transmmission:
                // When do we use 4 of the SPI pins ? /*PIC24f SPI Reference Manual */
                // when frame spi mode is enabled
                // when slave select feature is used
                // when standard spi mode is used with CKE = 1 
                break;
            default:
                break;
        }
        switch (module_mode){
            case master_mode:
                SPI1CON1bits.MSTEN = 1;
                break;
            case slave_mode:
                SPI1CON1bits.MSTEN = 0;
                break;
            default:
                break;
        }
        SPI1STATbits.SPIEN = 1;
    #endif
    #ifdef PIM_dsPIC33EP512MU810
        switch(transmission_wire){
            case _2_wire_transmmission:
                SPI1CON1bits.DISSDO = 1 ; // SDOx pin is not used by the module; pin functions as I/O  SDOx pin is controlled by the module
                break;
            case _3_wire_transmmission:
                break;
            case _4_wire_transmmission:
                // When do we use 4 of the SPI pins ? /*PIC24f SPI Reference Manual */
                // when frame spi mode is enabled
                // when slave select feature is used
                // when standard spi mode is used with CKE = 1 
                break;
            default:
                break;
        }
        switch (module_mode){
            case master_mode:
                SPI1CON1bits.MSTEN = 1;
                break;
            case slave_mode:
                SPI1CON1bits.MSTEN = 0;
                break;
            default:
                break;
        }
        SPI1STATbits.SPIEN = 1;
    #endif
}


void checkRxErrorSPI(void){
        if(SPI1STATbits.SPIROV){
        SPI1STATbits.SPIROV = 0;
    }
}
void configure_SPI(void){
    configure_SPI_port_pins(spi1_module);
    configure_SPI_data_transmission(_8bit_data_transmission);
    configure_SPI_clock_frequency();
    configure_clk_polarity_edge(high_level_idle,low_to_high);/*working on pic24fj128ga306*/
    complete_SPI_configuration(_3_wire_transmmission,master_mode);
}
uint8_t send_SPI_data(uint8_t data){
    #ifdef PIC24FJ64GA004
    checkRxErrorSPI();
    _SPI1IF = 0; 
    SPI1BUF = data;
    while(!_SPI1IF); //SPI1STATbits.SPITBF = 0 => transmit has started, SPI1TXB is empty
    return 1;
#endif
    #ifdef PIC24FJ128GA306
    checkRxErrorSPI();
    _SPI1IF = 0; 
    SPI1BUF = data;
    while(!_SPI1IF); //SPI1STATbits.SPITBF = 0 => transmit has started, SPI1TXB is empty
    return 1;
#endif
    #ifdef PIM_dsPIC33EP512MU810
    checkRxErrorSPI();
    _SPI1IF = 0; 
    SPI1BUF = data;
    while(!_SPI1IF); //SPI1STATbits.SPITBF = 0 => transmit has started, SPI1TXB is empty
    return 1;
#endif
}
uint8_t test_SPI(){
    uint8_t i;
    for(i=0;i<1000;i++){
        send_SPI_data(0xA3);
    }
    return 0;
}
