//mylibraries

#ifndef CONF_SPI_H
#define	CONF_SPI_H



#include "header_definition.h"
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



#define spi1_module 1
#define spi2_module 2

#define _2_wire_transmmission 2
#define _3_wire_transmmission 3
#define _4_wire_transmmission 4

#define master_mode 255 
#define slave_mode 0

#define _8bit_data_transmission 8
#define _16bit_data_transmission 16

#define high_level_idle 1
#define low_level_idle 0
#define high_to_low 110
#define low_to_high 101


uint8_t configure_SPI_port_pins(uint8_t module_number);
void configure_SPI_data_transmission(uint8_t trans_type);
void configure_SPI_clock_frequency(void);
void configure_SPI_clk_polarity_edge(uint8_t polarity, uint8_t edge);
void complete_SPI_configuration (uint8_t transmission_wire, uint8_t module_mode);

void checkRxErrorSPI(void);
void configure_SPI(void);
uint8_t send_SPI_data(uint8_t data);
uint8_t test_SPI(void);

#endif
