// mylibraries
#ifndef AMG8833_H
#define AMG8833_H




#include "header_definition.h"
#ifdef AMG8833_1
#include "../../AMG8833_1.X/project_specific.h"
#endif
#ifdef pic24f_deneme
//#include "../../pic24f_deneme.X/project_specific.h"
#endif 
#ifdef IR_cam_PIC24f
#include "../../IR_cam_PIC24f.X/project_specific.h"
#endif
#ifdef dspic33_deneme
#include "../../dspic33_deneme.X/project_specific.h"
#endif
#include <stdbool.h>
#include "../my_headers/numeric_manipulations.h"
#include "../my_headers/conf_I2C.h"
#include "../my_headers/conf_uart.h"
#include "../my_headers/ST7789.h"
#include <libpic30.h>


#define ADAFRUIT
#define POWER_CONTROL_REGISTER        0x00
#define RESET_REGISTER                0x01
#define FRAMERATE_REGISTER            0x02
#define INT_CONTROL_REGISTER          0x03
#define STATUS_REGISTER               0x04
#define STATUS_CLEAR_REGISTER         0x05
#define AVERAGE_REGISTER              0x07
#define INT_LEVEL_REGISTER_UPPER_LSB  0x08
#define INT_LEVEL_REGISTER_UPPER_MSB  0x09
#define INT_LEVEL_REGISTER_LOWER_LSB  0x0A
#define INT_LEVEL_REGISTER_LOWER_MSB  0x0B
#define INT_LEVEL_REGISTER_HYST_LSB   0x0C
#define INT_LEVEL_REGISTER_HYST_MSB   0x0D
#define THERMISTOR_REGISTER_LSB       0x0E
#define THERMISTOR_REGISTER_MSB       0x0F
#define INT_TABLE_REGISTER_INT0       0x10
#define RESERVED_AVERAGE_REGISTER     0x1F
#define TEMPERATURE_REGISTER_START    0x80

#ifdef ADAFRUIT
/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define AMG88xx_ADDRESS (0x69)
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
enum {
  AMG88xx_PCTL = 0x00,
  AMG88xx_RST = 0x01,
  AMG88xx_FPSC = 0x02,
  AMG88xx_INTC = 0x03,
  AMG88xx_STAT = 0x04,
  AMG88xx_SCLR = 0x05,
  // 0x06 reserved
  AMG88xx_AVE = 0x07,
  AMG88xx_INTHL = 0x08,
  AMG88xx_INTHH = 0x09,
  AMG88xx_INTLL = 0x0A,
  AMG88xx_INTLH = 0x0B,
  AMG88xx_IHYSL = 0x0C,
  AMG88xx_IHYSH = 0x0D,
  AMG88xx_TTHL = 0x0E,
  AMG88xx_TTHH = 0x0F,
  AMG88xx_INT_OFFSET = 0x010,
  AMG88xx_PIXEL_OFFSET = 0x80
};
enum power_modes {
  AMG88xx_NORMAL_MODE = 0x00,
  AMG88xx_SLEEP_MODE = 0x01,
  AMG88xx_STAND_BY_60 = 0x20,
  AMG88xx_STAND_BY_10 = 0x21
};
enum sw_resets { AMG88xx_FLAG_RESET = 0x30, AMG88xx_INITIAL_RESET = 0x3F };
enum frame_rates { AMG88xx_FPS_10 = 0x00, AMG88xx_FPS_1 = 0x01 };
enum int_enables { AMG88xx_INT_DISABLED = 0x00, AMG88xx_INT_ENABLED = 0x01 };
enum int_modes { AMG88xx_DIFFERENCE = 0x00, AMG88xx_ABSOLUTE_VALUE = 0x01 };
/*=========================================================================*/

#define AMG88xx_PIXEL_ARRAY_SIZE 64
#define AMG88xx_PIXEL_TEMP_CONVERSION .25
#define AMG88xx_THERMISTOR_CONVERSION .0625
bool begin_AMG88xx(void);
//  void readPixels(float *buf, uint8_t size);
void readPixels(uint16_t *buf);
uint16_t readThermistor(void);
#ifdef LCD
  uint16_t readThermistor_sendLCD(void);
    #endif
//  void setMovingAverageMode(bool mode);
void setMovingAverageMode_ON(void);
void setMovingAverageMode_OFF(void);
void enableInterrupt();
void disableInterrupt();
void setInterruptMode(uint8_t mode);
//  void getInterrupt(uint8_t *buf, uint8_t size);
void get_all_interrupt_table(uint8_t *buf);
void clearInterrupt();
// this will automatically set hysteresis to 95% of the high value
void setInterruptLevels_95(float high, float low);
// this will manually set hysteresis
void setInterruptLevels(float high, float low, float hysteresis);
uint16_t signedMag12ToFloat(uint16_t val);
uint16_t int12ToFloat(uint16_t val);


  struct pctl {
    // 0x00 = Normal Mode
    // 0x01 = Sleep Mode
    // 0x20 = Stand-by mode (60 sec intermittence)
    // 0x21 = Stand-by mode (10 sec intermittence)

    uint8_t PCTL : 8;
    uint8_t (*get)(const struct pctl*);
  };  
/***********************************************************/
  // reset register
  struct rst {
    // 0x30 = flag reset (all clear status reg 0x04, interrupt flag and
    // interrupt table) 0x3F = initial reset (brings flag reset and returns to
    // initial setting)

    uint8_t ReSeT : 8;
    uint8_t (*get)(const struct rst*);
  };
/*****************************************************************/
  // frame rate register
  struct fpsc {
    // 0 = 10FPS
    // 1 = 1FPS
    uint8_t FPS : 1;

    uint8_t (*get)(const struct fpsc*);
  };
/*****************************************************/
  // interrupt control register
  struct intc {

    // 0 = INT output reactive (Hi-Z)
    // 1 = INT output active
    uint8_t INTEN : 1;

    // 0 = Difference interrupt mode
    // 1 = absolute value interrupt mode
    uint8_t INTMOD : 1;
//    C++ implementation 
//    uint8_t get() { return (INTMOD << 1 | INTEN) & 0x03; }
    uint8_t (*get)(const struct intc*);
  };
/******************************************************************/
  // status register
  struct stat {
    uint8_t unused : 1;
    // interrupt outbreak (val of interrupt table reg)
    uint8_t INTF : 1;

    // temperature output overflow (val of temperature reg)
    uint8_t OVF_IRS : 1;

    // thermistor temperature output overflow (value of thermistor)
    uint8_t OVF_THS : 1;

//    C++ implementation 
//    uint8_t get() {
//      return ((OVF_THS << 3) | (OVF_IRS << 2) | (INTF << 1)) & 0x0E;
      
      uint8_t (*get)(const struct stat*);
  };
/******************************************************************/
  // status clear register
  // write to clear overflow flag and interrupt flag
  // after writing automatically turns to 0x00
  struct sclr {
    uint8_t unused : 1;
    // interrupt flag clear
    uint8_t INTCLR : 1;
    // temp output overflow flag clear
    uint8_t OVS_CLR : 1;
    // thermistor temp output overflow flag clear
    uint8_t OVT_CLR : 1;
//    C++ implementation 
//    uint8_t get() {
//      return ((OVT_CLR << 3) | (OVS_CLR << 2) | (INTCLR << 1)) & 0x0E;
    uint8_t (*get)(const struct sclr*);
  };
  /***************************************************************/
  // average register
  // for setting moving average output mode
  struct ave {
    uint8_t unused : 5;
    // 1 = twice moving average mode
    uint8_t MAMOD : 1;
//    C++ implementation
//    uint8_t get() { return (MAMOD << 5); }
    uint8_t (*get)(const struct ave*);
  };
/*******************************************************************/
  // interrupt level registers
  // for setting upper / lower limit hysteresis on interrupt level

  // interrupt level upper limit setting. Interrupt output
  // and interrupt pixel table are set when value exceeds set value
  struct inthl {
    uint8_t INT_LVL_H : 8;
//    C++ implementation
//    uint8_t get() { return INT_LVL_H; }
    uint8_t (*get)(const struct inthl*);
  };
//  struct inthl _inthl = {0x08,get_inthl};
/**********************************************************************/
  struct inthh {
    uint8_t INT_LVL_H : 4;
   
//    C++ implementation
//    uint8_t get() { return INT_LVL_H; }
    uint8_t (*get)(const struct inthh*);
  };
  
//  struct inthh _inthh = {0x08,get_inthh};
  /*******************************************************************/
  // interrupt level lower limit. Interrupt output
  // and interrupt pixel table are set when value is lower than set value
  struct intll {
    uint8_t INT_LVL_L : 8;
//    C++ implementation
//    uint8_t get() { return INT_LVL_L; }
    uint8_t (*get)(const struct intll*);
  };
//  struct intll _intll = {0x08,get_intll};
  /*****************************************************/
  struct intlh {
    uint8_t INT_LVL_L : 4;
//    C++ implementation
//    uint8_t get() { return (INT_LVL_L & 0xF); }
    uint8_t (*get)(const struct intlh*);
  };
  
//  struct intlh _intlh = {0x08,get_intlh};
/************************************************************/
  // setting of interrupt hysteresis level when interrupt is generated.
  // should not be higher than interrupt level
  struct ihysl {
    uint8_t INT_HYS : 8;
//    C++ implementation
//    uint8_t get() { return INT_HYS; }
    uint8_t (*get)(const struct ihysl*);
  };
  
//  struct ihysl _ihysl {0x08,get_ihysl};
/****************************************************/
  struct ihysh {
    uint8_t INT_HYS : 4;
//    C++ implementation
//    uint8_t get() { return (INT_HYS & 0xF); }
    uint8_t (*get)(const struct ihysh*);
  };
  
//  struct ihysh _ihysh = {0x08,get_ihysh};
  /****************************************************/
  // thermistor register
  // SIGNED MAGNITUDE FORMAT
  struct tthl {
    uint8_t TEMP : 8;
//    C++ implementation
//    uint8_t get() { return TEMP; }
    uint8_t (*get)(const struct tthl*);
  };
  
//  struct tthl _tthl = {0x08,get_tthl};
/*********************************************************/
  struct tthh {
    uint8_t TEMP : 3;
    uint8_t SIGN : 1;
//    C++ implementation
//    uint8_t get() { return ((SIGN << 3) | TEMP) & 0xF; }
    uint8_t (*get)(const struct tthh*);
  };
  
//  struct tthh _tthh = {0x08,0x08,get_tthh};
/**************************************************************/
  // temperature registers 0x80 - 0xFF
  /*
  //read to indicate temperature data per 1 pixel
  //SIGNED MAGNITUDE FORMAT
  struct t01l {
          uint8_t TEMP : 8;
          uint8_t get(){
                  return TEMP;
          }
  };
  struct t01l _t01l;
  struct t01h {
          uint8_t TEMP : 3;
          uint8_t SIGN : 1;
          uint8_t get(){
                  return ( (SIGN << 3) | TEMP) & 0xF;
          }
  };
  struct t01h _t01h;
  */

#endif


void write_AMG88xx_8bit (uint8_t device_address, uint8_t reg_address, uint8_t data);
void write_AMG88xx_16bit(uint8_t device_address, uint8_t reg_address, uint8_t data_l, uint8_t data_h);
void read_AMG88xx_8bit  (uint8_t device_address, uint8_t reg_address,uint8_t *buf);
void read_AMG88xx_nbyte (uint8_t device_address, uint8_t reg_address,uint8_t *buf, uint8_t nbyte);
uint8_t *data8_2_ascii     (uint8_t dec);
void pixelvalues_2_MPLABVis  (uint16_t *buf);
uint8_t * find_max(uint16_t *buf);

uint8_t *dectoascii(uint8_t dec);
uint8_t get_thermistor_dec_from_raw(uint16_t raw);
uint16_t get_thermistor_frac_from_raw(uint16_t raw);
void send_thermistor_value_2_uart();
uint8_t * pixel_2_ascii (uint16_t *buf);

void print_8x8_table_tft(void);
uint16_t * make22x22(uint16_t *ptr);
uint8_t * make_R_22x22(uint8_t *ptr);
uint8_t * make_G_22x22(uint8_t *ptr);
uint8_t * make_B_22x22(uint8_t *ptr);
void interp_x_8(uint8_t *ptr);
void interp_y_8(uint8_t *ptr);
uint8_t * get_R_G_B_of_pixel(uint16_t *ptr);
void print_hires_pixel_tft_v1(void);
void print_hires_pixel_tft_v2(void);
void set_colorBar (void);



#endif
