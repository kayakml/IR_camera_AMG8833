/*IRcampic24f*/
/*BU PROJE NE YAPIYOR*/
/*AMG8833 termal sensorunden 8x8 pixel formatinda gelen 64 adet sensor verisini 
 bir display uzerinde gorsellestirerek bir termal kamera cozumu sunuyor
 Ayrintili bilgiler /home/oleg/Documents/my_microchip/Calismalar içindeki Proje_Dosyasi.odt
 dosysi icinde*/

//http://www.vendian.org/mncharity/dir3/starcolor/details.html

#include "project_specific.h"
/*CONFIGURATION BITS*/
#ifdef PIC24FJ128GA306


// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68719476736 (25.7 Days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep BOR Enable bit (DSBOR Enabled)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable (DSWDT Enabled)
#pragma config DSSWEN = ON              // DSEN Bit Enable (Deep Sleep is controlled by the register bit DSEN)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config VBTBOR = ON              // VBAT BOR enable bit (VBAT BOR enabled)
#pragma config SOSCSEL = ON             // SOSC Selection bits (SOSC circuit selected)
#pragma config WDTWIN = PS25_0          // Watch Dog Timer Window Width (Watch Dog Timer Window Width is 25 percent)
#pragma config BOREN = ON               // Brown-out Reset Enable (Brown-out Reset Enable)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = NONE            // Primary Oscillator Select (Primary Oscillator Disabled)
#pragma config BOREN1 = EN              // BOR Override bit (BOR Enabled [When BOREN=1])
#pragma config IOL1WAY = OFF            // IOLOCK One-Way Set Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)
#pragma config OSCIOFCN = OFF           // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
#pragma config FNOSC = FRCPLL              // Initial Oscillator Select (Fast RC Oscillator (FRC))
#pragma config ALTVREF = DLT_AV_DLT_CV  // Alternate VREF/CVREF Pins Selection bit (Voltage reference input, ADC =RA9/RA10 Comparator =RA9,RA10)
#pragma config IESO = ON                // Internal External Switchover (Enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler Select (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config FWDTEN = WDT_HW          // Watchdog Timer Enable (WDT enabled in hardware)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled)
#pragma config GWRP = OFF               // General Segment Write Protect (Disabled)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (Disabled)


#endif
/*INCLUDE HEADERS*/

#include "../my_libraries/my_headers/conf_clock.h"
#include "../my_libraries/my_headers/conf_pin.h"
#include "../my_libraries/my_headers/conf_uart.h"
#include "../my_libraries/my_headers/conf_I2C.h"
#include "../my_libraries/my_headers/ST7789.h"
#include "../my_libraries/my_headers/conf_SPI.h"
#include "../my_libraries/my_headers/AMG8833.h"
#include "../my_libraries/my_headers/adafruit_gfx.h"

#include <libpic30.h>

//#define surface_mode
#define human_mode


    

    
int main(void) {
    uint8_t *ptr;
    uint16_t pixelbuffer[64];
    configure_clock();
    configure_digital_IO_ports();    
    configure_uart();
    configI2C1(400);
    configure_SPI();
    
    if(begin_AMG88xx()){outString ("begin_AMG88 sucessfull!!! \n");}
    else {outString ("begin_AMG88 failed!!! \n");}
    init(240,240);
//    init(128,128);
    fillScreen(Color565(0,0,0));
    set_colorBar();

    while(1)
    {
        if(INPUT_PIN43==0){ 
//            print_8x8_table_tft();
            print_hires_pixel_tft_v2();
            
            readPixels(pixelbuffer); 
            ptr = find_max(pixelbuffer);
            drawChar(172,220,*ptr,RED,BLACK,3,3);
            ptr++;
            drawChar(192,220,*ptr,RED,BLACK,3,3);
            ptr++;
            drawChar(212,220,*ptr,RED,BLACK,3,3);

            ptr = find_min(pixelbuffer);
            drawChar(50,220,*ptr,BLUE,BLACK,3,3);
            ptr++;
            drawChar(70,220,*ptr,BLUE,BLACK,3,3);
            ptr++;
            drawChar(90,220,*ptr,BLUE,BLACK,3,3);
          
        }
    }
    return 0;
}
