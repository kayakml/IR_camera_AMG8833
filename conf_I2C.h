//mylibraries

#ifndef CONF_I2C_H
#define CONF_I2C_H


#include "../my_headers/header_definition.h"
#ifndef __PROJECT_SPECIFIC_H
#ifdef AMG8833 
#include "../../AMG8833.X/project_specific.h"
#endif
#ifdef AMG8833_1
#include "../../AMG8833_1.X/project_specific.h"
#endif
#ifdef dspic33_deneme
#include "../../dspic33_deneme.X/project_specific.h"
#endif
#ifdef pic24f_deneme
#include "../../pic24f_deneme.X/project_specific.h"
#endif
#ifdef IR_cam_PIC24f
#include "../../IR_cam_PIC24f.X/project_specific.h"
#endif
#endif

#include <stdint.h>



#define I2C_WADDR(x) ((x<<1) & 0xFE) //clear R/W bit of I2C addr
#define I2C_RADDR(x) ((x<<1) | 0x01) //set R/W bit of I2C addr

// #define DEFAULT_BUS_SPEED 400 --> located in project_specific.h

#ifndef I2C_ACK
# define I2C_ACK 0
#endif

#ifndef I2C_NAK
# define I2C_NAK 1
#endif


//#define I2C2_MODULE
//#define I2C1_MODULE



//I2C Operations
void configI2C1(uint16_t u16_FkHZ);
void startI2C1(void);
void rstartI2C1(void);
void stopI2C1(void);
void putI2C1(uint8_t u8_val);
uint8_t putNoAckCheckI2C1(uint8_t u8_val);
uint8_t getI2C1(uint8_t u8_ack2Send);


#if  (defined (I2C1_MODULE)||defined (AI2C1_MODULE)||defined (PIC24F16KA102_I2C1)||defined (PIC24F_I2C1_MODULE))
//I2C Transactions
void write1I2C1(uint8_t u8_addr,uint8_t u8_d1);
void write2I2C1(uint8_t u8_addr,uint8_t u8_d1, uint8_t u8_d2);
void writeNI2C1(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt);
void read1I2C1(uint8_t u8_addr,uint8_t* pu8_d1);
void read2I2C1(uint8_t u8_addr,uint8_t* pu8_d1, uint8_t* pu8_d2);
void readNI2C1(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt);
#endif 
#if defined  (I2C2_MODULE)
//I2C Transactions
void write1I2C2(uint8_t u8_addr,uint8_t u8_d1);
void write2I2C2(uint8_t u8_addr,uint8_t u8_d1, uint8_t u8_d2);
void writeNI2C2(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt);
void read1I2C2(uint8_t u8_addr,uint8_t* pu8_d1);
void read2I2C2(uint8_t u8_addr,uint8_t* pu8_d1, uint8_t* pu8_d2);
void readNI2C2(uint8_t u8_addr,uint8_t* pu8_data, uint16_t u16_cnt);
#endif

#if defined LCD
    void report_write_Error_to_LCD(void);
    void report_read_Error_to_LCD(void);
#endif


#endif 
