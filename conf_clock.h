//mylibraires
#ifndef CONF_CLOCK_H
#define CONF_CLOCK_H

#define project_includes
#ifdef  project_includes
    #include "../my_headers/header_definition.h"
    #ifdef dspic33_deneme
    #include "../../dspic33_deneme.X/project_specific.h"
    #endif
    #ifdef AMG8833_1
    #include "../../AMG8833_1.X/project_specific.h"
    #endif
    #ifdef pic24f_deneme
    #include "../../pic24f_deneme.X/project_specific.h"
    #endif
    #ifdef IR_cam_PIC24f
    #include "../../IR_cam_PIC24f.X/project_specific.h"
    #endif
    #ifdef pic24f_deneme_2
    #include "../../pic24f_deneme_2.X/project_specific.h"
    #endif
    #ifdef BlueTooth
    #include "../../BlueTooth.X/project_specific.h"
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
    #ifdef auo_lcd
    #include "../../auo_lcd.X/project_specific.h" 
    #endif
    #ifdef _93C46_eprom
    #include "../../_93C46_eprom.X/project_specific.h" 
    #endif


/*clock konfigurasyonu project_specifics.h icinden yapilacak*/
#ifdef CLK_FRC_8MHZ //pic24f
#define FCY 4000000L
#elif defined CLK_FRC_7_37_MHZ //dspic33e
#define FCY 3685000L // 9600baud rate uart high time =104us
#elif defined CLK_XT_8MHZ
#define FCY 4000000L // 9600baud rate uart high time =104us
#elif defined CLK_XT_8MHZ_WITH_PLL_32MHZ
#define FCY 17000000L //explorer16/32 board's external 8MHz cyrstal's instruction cycle // 9600baud rate uart high time =104us
#elif defined CLK_XT_8MHZ_WITH_PLL_40MHZ
#define FCY 20000000L
#elif defined CLK_XT_8MHZ_WITH_PLL_60MHZ
#define FCY 30000000L
#elif defined CLK_XT_4MHZ
#define FCY 2000000L
#elif defined CLK_XT_20MHZ
#define FCY 10000000UL
#elif defined CLK_XT_4MHZ_WITH_PLL_16MHZ
#define FCY 8000000L
#elif defined CLK_FRC_WITH_PLL_32MHZ_with_ClockSwitching
#define FCY 16000000L
#elif defined CLK_FRC_WITH_PLL_32MHZ_without_ClockSwitching
#define FCY 16000000L
#elif defined CLK_FRC_WITH_PLL_16MHZ
#define FCY 8000000L
#elif defined CLK_FRC_DEFAULT_FRCDIV_4MHZ
#define FCY 20000000L
#elif defined CLK_XT_8MHZ_WITH_PLL_140MHZ
#define FCY 70000000L
#elif defined CLK_FRC_7_37_MHZ_WITH_PLL_140MHZ
#define FCY 70000000L 
#elif defined CLK_FRC_7_37_MHZ_WITH_PLL_120MHZ
#define FCY 60000000L
#else 
#endif

void configure_clock(void);
void test_clock(void);/*CLK FREKANSINI TEYIT ETMEK ICIN KULLANILACAK*/
/*BU FONKSIYON PROGRAMLAMANIN ILK ASAMASINDA ; YANI UYGULAMAYA DAIR BIRSEY YAZMADAN
 * ONCE CLOCK AYARLARINI YAPTIKTAN HEMEN SONRA  YAPILAN AYARLARIN ISTEDIGIMIZ 
 * SONUCU VERIP VERMEDIGINI ANLAMAK ICIN 1 SEFERLIGINE KULLANILMALI. 
 * EGER ISTEDIGIMIZ SONUCU ALDIYSAK UYGULAMAYI YAZMAYA GECMELIYIZ VE BU FONKSIYONU
 *  PROGRAMDAN CIKARMALIYIZ*/

#endif

#endif

