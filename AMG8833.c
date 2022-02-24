//mylibraries

#include "../my_headers/AMG8833.h"



#define AMG_I2C_CHUNKSIZE 32
#define ADAFRUIT
#define MY_ADAFRUIT


//uint8_t tempr[22][22];                                                                                                          
//uint8_t tempg[22][22];                                                                                                          
//uint8_t tempb[22][22];                                                                                                          
uint16_t my22x22[22][22];
uint16_t final_my22x22[22][22];
uint8_t R_G_B[64][3];
uint8_t RR_GG_BB[22][22][3];
uint8_t R_22x22[22][22];
uint8_t G_22x22[22][22];
uint8_t B_22x22[22][22];

static uint16_t max_temp,max_temp_index;

uint8_t get_pctl (const struct pctl  *p){       
      return p->PCTL;  
  }
uint8_t get_rst  (const struct rst   *p){
  return p->ReSeT;
  }
uint8_t get_fpsc (const struct fpsc  *p){
return p->FPS & 0x01 ;
}
uint8_t get_intc (const struct intc  *p){
      return (p->INTMOD<<1 | p->INTEN) & 0x03;
  }
uint8_t get_stat (const struct stat  *p){
      return ((p->OVF_THS << 3) | (p->OVF_IRS << 2) | (p->INTF << 1)) & 0x0E;
  }
uint8_t get_sclr (const struct sclr  *p){
      return ((p->OVT_CLR << 3) | (p->OVS_CLR << 2) | (p->INTCLR << 1)) & 0x0E;
  }
uint8_t get_ave  (const struct ave   *p){
  return (p->MAMOD << 5);
  }
uint8_t get_inthl(const struct inthl *p){
  return (p->INT_LVL_H);
  }
uint8_t get_inthh(const struct inthh *p){
  return p->INT_LVL_H;
  }
uint8_t get_intll(const struct intll *p){
  return p->INT_LVL_L;
  }
uint8_t get_intlh(const struct intlh *p){
      return (p->INT_LVL_L & 0xF);
  }
uint8_t get_ihysl(const struct ihysl *p){
  return p->INT_HYS; 
  }
uint8_t get_ihysh(const struct ihysh *p){
  return (p->INT_HYS & 0xF);
  }
uint8_t get_tthl (const struct tthl  *p){
      return p->TEMP;
  }
uint8_t get_tthh (const struct tthh  *p){
  return ((p->SIGN << 3) | p->TEMP) & 0xF;
  }

struct rst _rst = {AMG88xx_INITIAL_RESET,get_rst};
struct pctl _pctl = {AMG88xx_NORMAL_MODE,get_pctl};
struct fpsc _fpsc = {AMG88xx_FPS_10,get_fpsc};
struct intc _intc = {0,0,get_intc};


/*
 * POWER CONTROL REGISTER : NORMAL MODE
 * SOFTWARE RESET : INITIAL RESET
 * INTERRUPTS : DISABLE
 * FRAME RATE : 10fps
 */
bool begin_AMG88xx() {
//  _pctl.PCTL = AMG88xx_NORMAL_MODE;
//  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_PCTL,_pctl.get(&_pctl));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_PCTL,AMG88xx_NORMAL_MODE);
  // software reset
//  _rst.RST = AMG88xx_INITIAL_RESET;
//  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_RST,_rst.get(&_rst));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_RST,AMG88xx_INITIAL_RESET);
  // disable interrupts by default
  disableInterrupt();
  // set to 10 FPS
//  _fpsc.FPS = AMG88xx_FPS_10;
//  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_FPSC,_fpsc.get(&_fpsc));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_FPSC,AMG88xx_FPS_10);
    __delay_ms(100);
  return true;
}
/***************************************************************************/
void setMovingAverageMode_ON(){
    startI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x50);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x45);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x57);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));    
    putI2C1(0x07); // register address according to I2C comm. format document
    putI2C1(0x20); // command code that enables moving average mode
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x00);
    stopI2C1();
}
void setMovingAverageMode_OFF(){
    startI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x50);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x45);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x57);
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));    
    putI2C1(0x07); // register address according to I2C comm. format document
    putI2C1(0x00); // command code that disables moving average mode
    rstartI2C1();
    putI2C1(I2C_WADDR(AMG88xx_ADDRESS));
    putI2C1(0x1F); // register address according to I2C comm. format document
    putI2C1(0x00);
    stopI2C1();
}
/**************************************************************************/
/*!
    @brief  Set the interrupt levels. The hysteresis value defaults to .95 *
   high
    @param  high the value above which an interrupt will be triggered
    @param  low the value below which an interrupt will be triggered
*/
void setInterruptLevels_95(float high, float low) {
  setInterruptLevels(high, low, high * .95);
}
/**************************************************************************/
/*!
    @brief  Set the interrupt levels
    @param  high the value above which an interrupt will be triggered
    @param  low the value below which an interrupt will be triggered
    @param hysteresis the hysteresis value for interrupt detection
*/
void setInterruptLevels(float high, float low, float hysteresis) {
  int highConv = high / AMG88xx_PIXEL_TEMP_CONVERSION;
  
  if (highConv < -4095){highConv = -4095;}
  else if (highConv > 4095){highConv = 4095;}
  
  struct inthl _inthl = {highConv & 0xFF,get_inthl};
  struct inthh _inthh = {(highConv & 0xF)>>4,get_inthh};
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTHL,_inthl.get(&_inthl));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTHH,_inthh.get(&_inthh));

  int lowConv = low / AMG88xx_PIXEL_TEMP_CONVERSION;
  if (lowConv < -4095){lowConv = -4095;}
  else if (lowConv > 4095){lowConv = 4095;}
  
  struct intll _intll = {lowConv & 0xFF,get_intll};
  struct intlh _intlh = {(lowConv & 0xF)>>4,get_intlh};
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTLL,_intll.get(&_intll));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTLH,_intlh.get(&_intlh));
 

  int hysConv = hysteresis / AMG88xx_PIXEL_TEMP_CONVERSION;
  if (hysConv < -4095){hysConv = -4095;}
  else if (hysConv > 4095){hysConv = 4095;}
  
  struct ihysl _ihysl = {hysConv & 0xFF,get_ihysl};
  struct ihysh _ihysh = {(hysConv & 0xF)>>4,get_ihysh};
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_IHYSL,_ihysl.get(&_ihysl));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_IHYSH,_ihysh.get(&_ihysh));

}
/**************************************************************************/
void enableInterrupt() {
  _intc.INTEN = 1;
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTC,_intc.get(&_intc));
            
}
/**************************************************************************/
void disableInterrupt() {
//  _intc.INTEN = 0;
//  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTC,_intc.get(&_intc));
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTC,0);
}
/**************************************************************************/
/*!
    @brief  Set the interrupt to either absolute value or difference mode
    @param  mode passing AMG88xx_DIFFERENCE sets the device to difference mode,
   AMG88xx_ABSOLUTE_VALUE sets to absolute value mode.
*/
void setInterruptMode(uint8_t mode) {
  _intc.INTMOD = mode;
  write_AMG88xx_8bit(AMG88xx_ADDRESS,AMG88xx_INTC,_intc.get(&_intc));
}
/**************************************************************************/
/*!
    @brief  Read the state of The full interrupt register is 8 bytes in length.
    @returns 8 bytes of data in buf
 * @my_brief: i got a tool which can read 1 byte at a time --> read_AMG88xx_8bit 
 * i use that tool 8 times to read 8 bytes of data.  
 * read_AMG88xx_8bit function
*/
void get_all_interrupt_table(uint8_t *buf) {
  
    uint8_t i;
    uint8_t buf_to_read_AMG88xx_8bit[8];

    for (i=0;i<8;i++){
        read_AMG88xx_8bit(AMG88xx_ADDRESS,(AMG88xx_INT_OFFSET+i),buf_to_read_AMG88xx_8bit);
        *buf = buf_to_read_AMG88xx_8bit[0];
        buf++;
    
    }
}
/**************************************************************************/
/*!
    @brief  Clear any triggered interrupts
*/
/**************************************************************************/
void clearInterrupt() {
  _rst.ReSeT = AMG88xx_FLAG_RESET;
  write_AMG88xx_8bit(AMG88xx_ADDRESS, AMG88xx_RST, _rst.get(&_rst));
}
/**************************************************************************/
uint16_t readThermistor() {
    //thermistor data is 12 bit including sign bit(SB). 
    //The last 4 bits are fraction, subsequent 8 bits are decimal part 
    //of thermistor data same as pixel temperature data
    // |X|X|X|X|SB|T10|T9|T8|T7|T6|T5|T4|T3|T2|T1|T0|
    // |--------TTHH--------|---------TTHL----------|
    // |      HIGH BYTE     |       LOW BYTE        |
  uint8_t raw[2];
  uint16_t raw_16 = 0;  
  read_AMG88xx_nbyte(AMG88xx_ADDRESS,AMG88xx_TTHL,raw,2);
//    /*Thermistor output is 12 bit wide which is placed in a 2 byte data.
//     So the first 4 bits are always ZERO. The last 4 bits represent the fractional part
//     and the 8 bits in the middle are decimal part of the thermistor value.
//     The below code strips the decimal part*/
//    temp1 = (raw[1]<<4)&(0xF0);
//    temp0 = (raw[0]>>4)&(0x0F);
//    temp1 = temp1|temp0;

//  return signedMag12ToFloat(recast) * AMG88xx_THERMISTOR_CONVERSION;
  raw_16 = (raw_16 | raw[1])<<8;
  raw_16 = raw_16 | raw[0];
  return (raw_16) ;
}
/**************************************************************************/
#if defined LCD
uint16_t readThermistor_sendLCD() {
  uint8_t raw[2],temp,highofraw16,lowofraw16,dec_high4,dec_low4;
  uint8_t dec,*ptr,frac;
  uint16_t raw_16 = 0;  
  read_AMG88xx_nbyte(AMG88xx_ADDRESS,AMG88xx_TTHL,raw,2);
//    /*Thermistor output is 12 bit wide which is placed in a 2 byte data place.
//     So the first 4 bits are always ZERO. The last 4 bits represent the fractional part
//     and the 8 bits in the middle are decimal part of the thermistor value.
  
//     The below code strips the decimal part*/
//    temp1 = (raw[1]<<4)&(0xF0);
//    temp0 = (raw[0]>>4)&(0x0F);
//    temp1 = temp1|temp0;

//  return signedMag12ToFloat(recast) * AMG88xx_THERMISTOR_CONVERSION;
       
    raw_16 = (raw_16 | raw[1])<<8;
    raw_16 = raw_16 | raw[0];
  
        temp = 0;
        highofraw16 = 0;
        lowofraw16 = 0;
        frac = 0;
        
        highofraw16 = highofraw16 | raw_16 >>8 ;       
        lowofraw16 = lowofraw16 | raw_16 ;  
        
        dec_high4 = (highofraw16<<4)&(0xF0);
        dec_low4 = (lowofraw16>>4)&(0x0F);
        dec = dec_high4 | dec_low4 ;
        ptr =  dectoascii(dec);
        frac = (0X0F) & lowofraw16;
       
        LCD_PutString("thermistor value",16);
        LCD_PutChar (*ptr);//digit_hundreds  
//        send_data_MPLABVis(*ptr);
        ptr++;
        LCD_PutChar (*ptr);//digit_tens  
//        send_data_MPLABVis(*ptr);
        ptr++;
        LCD_PutChar (*ptr); //digit_ones
//        send_data_MPLABVis(*ptr);
        LCD_PutChar (44); //,
//        outString_to_MPLABVis(",");
        switch(frac){
            case 0:
                LCD_PutString("0000",4);
//                outString_to_MPLABVis("0000");
                break;
            case 1:
                LCD_PutString("0625",4);
//                outString_to_MPLABVis("0625");
                break;
            case 2:
                LCD_PutString("1250",4);
//                outString_to_MPLABVis("1250");
                break;
            case 3:
                LCD_PutString("1875",4);
//                outString_to_MPLABVis("1875");
                break;
            case 4:
                LCD_PutString("2500",4);
//                outString_to_MPLABVis("2500");
                break;
            case 5:
                LCD_PutString("3125",4);
//                outString_to_MPLABVis("3125");
                break;
            case 6:
                LCD_PutString("3750",4);
//                outString_to_MPLABVis("3750");
                break;
            case 7:
                LCD_PutString("4375",4);
//                outString_to_MPLABVis("4375");
                break;
            case 8:
                LCD_PutString("5000",4);
//                outString_to_MPLABVis("5000");
                break;
            case 9:
                LCD_PutString("5625",4);
//                outString_to_MPLABVis("5625");
                break;
            case 10:
                LCD_PutString("6250",4);
//                outString_to_MPLABVis("6250");
                break;
            case 11:
                LCD_PutString("6875",4);
//                outString_to_MPLABVis("6875");
                break;
            case 12:
                LCD_PutString("7500",4);
//                outString_to_MPLABVis("7500");
                break;
            case 13:
                LCD_PutString("8125",4);
//                outString_to_MPLABVis("8125");
                break;
            case 14:
                LCD_PutString("8750",4);
//                outString_to_MPLABVis("8750");
                break;
            case 15:
                LCD_PutString("9375",4);
//                outString_to_MPLABVis("9375");
                break;
        }
        LCD_PutChar(223); //degree sign
        LCD_PutString("C",16);
//        send_data_MPLABVis(176);
//        outString_to_MPLABVis("C\n");
  return (raw_16) ;
}
#endif
/*************************************************************************/
void readPixels(uint16_t *buf) {
    
    //pixel temperature data of each pixel is 12 bit including sign bit(SB). 
    //The last 2 bits are fraction, subsequent 8 bits are decimal part 
    //of temperature data same as thermistor data
    // |X|X|X|X|SB|T10|T9|T8|T7|T6|T5|T4|T3|T2|T1|T0|
    // |--------T01H--------|---------T01L----------|
    // |      HIGH BYTE     |       LOW BYTE        |
    // 64 x 16 size pixel value is going to be stored in *buf
    // buf is defined in main as uint16_t pixelbuffer[64]
  uint8_t i, index;
  uint8_t rawArray[128];
  uint16_t rawpixel;
 
  // 128byte pixel data is read into the rawArray 
 read_AMG88xx_nbyte(AMG88xx_ADDRESS, AMG88xx_PIXEL_OFFSET ,rawArray, 128);
 
  //In the below for loop at each iteration, we combine 2 members of rawArray
  //into one and load it into the buf after an index arrangement for buf.
  for (i = 0; i <128 ; i+=2) {
    rawpixel = (rawArray[i+1] << 8) | (rawArray[i]);
    index=i>>1;
    buf[index] = rawpixel;
  }
}
/*************************************************************************/
void pixelvalues_2_MPLABVis(uint16_t *buf){
    uint8_t col,i,dec,frac,frac_dig_0,frac_dig_1,*ptr,index;
    uint8_t pixelasciitable[64][5];
    
 col = 0; // col is for printing issues
 
 // Now we have an array of 64 elements each stores 2 byte data of pixel value
 // named as buf.
  for (i = 0; i<64; i++){
      // check pixel value for negativity/positivity
      if ((buf[i] & 0x0800) != 0){
      /*pixel value is negative*/
          ;
      }else{
      /*pixel value is positive*/
          
      // Each pixel value is comprised of 12 bits.  According to AMG8833 datasheet , The least 
      // significant 2 bits (T1-T0) are fractional bits. The other 10 bits (T9-T2) are for decimal value. 
      // The most significant 4 bits are not used.    
      // strip 8 bits (T9~T2) from related buffer place for decimal interpretation

          dec = 0;
          frac = 0;
          dec = (buf[i]>>2) | dec;
          frac = buf[i] & 0x0003; // strip fractional part comprised of 2 bits T1:T0
          /*convert fractional part into 2 ascii digits*/
          switch(frac){
              case 0:
                  frac_dig_0 = 48; // 0
                  frac_dig_1 = 48; // 0
                  break;
              case 1:
                  frac_dig_0 = 53; // 5
                  frac_dig_1 = 50; // 2
                  break;
              case 2:
                  frac_dig_0 = 48; // 0
                  frac_dig_1 = 53; // 5
                  break;
              case 3:
                  frac_dig_0 = 53; // 5
                  frac_dig_1 = 55; // 7
                  break; 
          }
          /*convert decimal part into 3 ascii digits*/
          ptr = dectoascii(dec);
          /*load ascii values into the pixelasciitable*/
          for (index = 0 ; index < 3 ; index++){
              pixelasciitable[i][index] = *ptr;
              ptr++;
          }
          pixelasciitable[i][3] = frac_dig_1;
          pixelasciitable[i][4] = frac_dig_0;
          

          
          send_data_MPLABVis(pixelasciitable[i][0]);
          send_data_MPLABVis(pixelasciitable[i][1]);
          send_data_MPLABVis(pixelasciitable[i][2]);
          outString_to_MPLABVis(",");
          send_data_MPLABVis(pixelasciitable[i][3]);
          send_data_MPLABVis(pixelasciitable[i][4]);
          
          
//          send_data_MPLABVis(*ptr); // hundreds
//          ptr++;
//          send_data_MPLABVis(*ptr); //tens
//          ptr++;
//          send_data_MPLABVis(*ptr); //ones
//          ptr++;
//          outString_to_MPLABVis(",");
//          send_data_MPLABVis(frac_dig_1);
//          send_data_MPLABVis(frac_dig_0);

          
          send_data_MPLABVis(176); // degree sign
          outString_to_MPLABVis("C");
          outString_to_MPLABVis("\t");
          col +=1;
          if (col == 8){
              col = 0 ; 
              outString_to_MPLABVis("\n");
          }
          if (i==63){outString_to_MPLABVis("\n\n");}
      //strip 2 bits (T1:T0) for fractional interpretation    
          frac = (buf[i]& (0x0003)) | frac;
      }
      
  }
}
/**************************************************************************/
/*!
    @brief  convert a 12-bit signed magnitude value to a floating point number
    @param  val the 12-bit signed magnitude value to be converted
    @returns the converted floating point value
*/
uint16_t signedMag12ToFloat(uint16_t val) {
  // take first 11 bits as absolute val
  uint16_t absVal = (val & 0x7FF);

  return (val & 0x800) ? 0 - (uint16_t)absVal : (uint16_t)absVal;
  // if (val & 0x800) is true then return (0 - (float)absVal)
  // if (val & 0x800) is false then return ((float)absVal)
}
/**************************************************************************/
/*!
    @brief  convert a 12-bit integer two's complement value to a floating point
   number
    @param  val the 12-bit integer  two's complement value to be converted
    @returns the converted floating point value
*/
uint16_t int12ToFloat(uint16_t val) {
  uint16_t sVal =
      (val << 4); // shift to left so that sign bit of 12 bit integer number is
                  // placed on sign bit of 16 bit signed integer number
  return sVal >> 4; // shift back the signed number, return converts to float
}



void write_AMG88xx_8bit(uint8_t device_address, uint8_t reg_address, uint8_t data){
startI2C1();
putI2C1(I2C_WADDR(device_address));
putI2C1(reg_address);
putI2C1(data);
stopI2C1();
}
void write_AMG88xx_16bit(uint8_t device_address, uint8_t reg_address, uint8_t data_l, uint8_t data_h){
startI2C1();
putI2C1(I2C_WADDR(device_address));
putI2C1(reg_address);
putI2C1(data_l);
rstartI2C1();
putI2C1(I2C_WADDR(device_address));
putI2C1(reg_address);
putI2C1(data_h);
stopI2C1();
}
void read_AMG88xx_8bit(uint8_t device_address, uint8_t reg_address,uint8_t *buf){
    startI2C1();
    putI2C1(I2C_WADDR(device_address));
    putI2C1(reg_address);
    putI2C1(I2C_RADDR(device_address));
    buf[0] = getI2C1(I2C_NAK);
    stopI2C1();
}
void read_AMG88xx_nbyte(uint8_t device_address, uint8_t reg_address,uint8_t *buf, uint8_t nbyte){
    /*How to use this function from main: 
     * ....
     * uint8_t mybuffer[64],my_address,my_regaddress,my_nbyte;
     * read_AMG88xx_nbyte(my_address,my_regaddress,mybuffer,my_nbyte)
     * ....
     * 
     * From inside main we are going to send start of an array(mybuffer) and its size(my_nbyte)
     * This function fills mybuffer with data. Because we define mybuffer inside the main we can use it there
     without a problem. By this way we do not need to return an array.*/
    /*What does this function do?
     we need to fill nbyte data to the buffer. I2C bus reads one byte at a time. 
     To continue the I2C reading we need to send an ACK
     at the end of each byte transfer except the last one. At the last byte transfer we must send a NACK
     to stop the I2C reading action.*/
    uint8_t i;
    startI2C1();
    putI2C1(I2C_WADDR(device_address));
    putI2C1(reg_address);
    rstartI2C1();
    putI2C1(I2C_RADDR(device_address));
    
    for (i=0;i<nbyte-1;i++)
    {
        *buf = getI2C1(I2C_ACK);
        
        buf++;
    }
    
    *buf = getI2C1(I2C_NAK);
    stopI2C1();
}





uint8_t     *dectoascii(uint8_t dec){
    // Takes 8 bit binary data as argument
    // Returns ascii code of 3 digits (hundreds/tenths/ones))
    uint8_t temp;
    static uint8_t mem_arr[3];
                                            //dec = 123;
     mem_arr[2] = (dec%10);                 //mem_arr[2] = 3
        temp = (dec - mem_arr[2] ) / 10;    //temp = (123-3)/10 = 12
        if (temp>=10) {
            mem_arr[1] = temp%10;           //mem_arr[1] = 12%10 = 2
            mem_arr[0] = (temp-mem_arr[1])/10; //mem_arr[0] = (12-2)/10 = 1
        } else {
            mem_arr[1] = temp;
            mem_arr[0] = 0;
        }
        
        mem_arr[0] = mem_arr[0] + 48; //hundreds
        mem_arr[1] = mem_arr[1] + 48; //tens
        mem_arr[2] = mem_arr[2] + 48; //ones
    return mem_arr;
    }
uint8_t     get_thermistor_dec_from_raw(uint16_t raw){
    // this function takes 16bit raw thermistor value from the output of readThermistor() function
    // |X|X|X|X|SB|T10|T9|T8|T7|T6|T5|T4|T3|T2|T1|T0|
    // then strips decimal part and sign bit (which is SB-T10:T4) and return it
    uint8_t dec;
    dec = 0;
    dec = dec | (raw>>4);
    return (dec);   
}
uint16_t    get_thermistor_frac_from_raw(uint16_t raw){
    //least 4 bits of readThermistor() function are fractional bits. 
    // |X|X|X|X|SB|T10|T9|T8|T7|T6|T5|T4|T3|T2|T1|T0|
    // T3:T0 are fractional bits
    // 4 bits of fractional provides us a resolution 0,625
    // this function returns decimal value of fraction bits(T3:T0) 
    uint8_t frac;
    frac = 0x0F;
    frac = frac & raw;
    switch(frac){
    case 0: return 0;
    break;
    case 1: return 625;
    break;
    case 2: return 1250;
    break;
    case 3: return 1875;
    break;
    case 4: return 2500;
    break;
    case 5: return 3125;
    break;
    case 6: return 3750;
    break;
    case 7: return 4375;
    break;
    case 8: return 5000;
    break;
    case 9: return 5625;
    break;
    case 10: return 6250;
    break;
    case 11: return 6875;
    break;
    case 12: return 7500;
    break;
    case 13: return 8125;
    break;
    case 14: return 8750;
    break;
    case 15: return 9375;

    
    
    }
    return 0;

}
void        send_thermistor_value_2_uart(){
uint16_t thermistor_value;
uint8_t temp;
uint8_t *print_ptr;
        thermistor_value = readThermistor();
        temp = get_thermistor_dec_from_raw(thermistor_value);
        print_ptr = data8_2_ascii(temp);
        send_uart_8(print_ptr[0]);
        send_uart_8(print_ptr[1]);
        send_uart_8(print_ptr[2]);

}
uint8_t     * pixel_2_ascii (uint16_t *buf){
    //structure of *buf is :
    // |X|X|X|X|SB|T10|T9|T8|T7|T6|T5|T4|T3|T2|T1|T0|
    // |--------T01H--------|---------T01L----------|
    // |      HIGH BYTE     |       LOW BYTE        |
    //
    // CR_532 convert uint16_t *buf into ascii code
    //
    // 1) Question if *buf is negative. If negative nothing is done.
    // 2) Loads decimal part into uint8_t dec variable
    // 3) Strips fractional part (the first 2 bits) and convert it to 4 possible ascii codes
    // 4) Calls data8_2_ascii function in order to convert decimal part into ascii values 
    static uint8_t ascii_buffer[64][5];
    uint8_t i,dec,frac,frac_dig_0,frac_dig_1,*ptr;
    
    for (i=0;i<64;i++){
        if ((buf[i] & 0x0800) != 0) // check pixel value for negativity/positivity
            {;} /*pixel value is negative do nothing*/
        else {
          dec = 0;
          frac = 0;
          dec = (buf[i]>>2) | dec; //
          frac = buf[i] & 0x0003; // strip fractional part comprised of 2 bits T1:T0
          /*convert fractional part into 2 ascii digits*/
          switch(frac){
              case 0:
                  // if fractional part corresponds to 0,00
                  frac_dig_0 = 48; // 0
                  frac_dig_1 = 48; // 0 
                  break;
              case 1:
                  // if fractional part corresponds to 0,25
                  frac_dig_0 = 53; // 5
                  frac_dig_1 = 50; // 2
                  break;
              case 2:
                  // if fractional part corresponds to 0,50
                  frac_dig_0 = 48; // 0
                  frac_dig_1 = 53; // 5
                  break;
              case 3:
                  // if fractional part corresponds to 0,75
                  frac_dig_0 = 53; // 5
                  frac_dig_1 = 55; // 7
                  break; 
          }
          
          ptr = data8_2_ascii(dec);
          
          ascii_buffer[i][0] = *ptr;
          ptr++;
          ascii_buffer[i][1] = *ptr;
          ptr++;
          ascii_buffer[i][2] = *ptr;
          ascii_buffer[i][3] = frac_dig_1;
          ascii_buffer[i][4] = frac_dig_0;
    }

 }
    return &ascii_buffer[0][0];
    /*FORMAT OF ASCII_BUFFER*/
    /*Suppose the first pixel's temperature value is 19,5 degrees. Then;
     * ascii_buffer[0][0] = 48 (48 is ascii code of 0)
     * ascii_buffer[0][1] = 49 (49 is ascii code of 1)
     * ascii_buffer[0][2] = 57 (57 is ascii code of 9)
     * ascii_buffer[0][3] = 53 (53 is ascii code of 5)
     * ascii_buffer[0][4] = 48 (48 is ascii code of 0)
     */
}
uint8_t     * find_max(uint16_t *buf){
    /*This function will search the maximum pixel value 
     * then convert it into ascci and load those ascii code into 3 address locations 
     * and return a pointer it*/
    uint16_t i;
    uint16_t max_tmp;
    uint8_t max_tmp8;
    uint8_t *ptr_2_maxtmp_ascii;
    max_tmp=0;
    for(i=0;i<64;i++)
    {
        if (*buf>max_tmp)
        {
            max_tmp=*buf;
        }
        ++buf;
    }
    max_tmp8 = ((max_tmp>>2));
    ptr_2_maxtmp_ascii = data8_2_ascii(max_tmp8); 
    return ptr_2_maxtmp_ascii;
}
uint8_t     * find_min(uint16_t *buf){
    /*This function will search the maximum pixel value 
     * then convert it into ascci and load those ascii code into 3 address locations 
     * and return a pointer it*/
    uint16_t i;
    uint16_t min_tmp;
    uint8_t min_tmp8;
    uint8_t *ptr_2_mintmp_ascii;
    min_tmp=65535;
    
    for(i=0;i<64;i++)
    {
        if (*buf<min_tmp)
        {
            min_tmp = *buf;
        }
        ++buf;
    }
    min_tmp8 = ((min_tmp>>2));
    ptr_2_mintmp_ascii = data8_2_ascii(min_tmp8); 
    return ptr_2_mintmp_ascii;
}


//#define debug_hires //to understand what is going wrong in the interpolation process
void print_8x8_table_tft(void)
{
    int i,cell_col_index,cell_start_x,cell_start_y,cell_width,cell_height,cell_x,cell_y;
    uint16_t region_1_hi,region_1_lo,region_2_hi,region_2_lo,region_3_hi,region_3_lo,region_4_hi,region_4_lo,dec;
    float rgb_coef_reg_1,rgb_coef_reg_2,rgb_coef_reg_3,rgb_coef_reg_4;
    uint32_t R,G,B; 
    uint16_t color;
    uint16_t pixelbuffer[64];
    
    /*GENEL STRATEJ?*/
    /*thermal sensor'den her bir pixel icin 8 bitlik data geliyor. Asagidaki for 
     * loop'un her bir iterasyonunda temel amac bu 8bitlik data icin R-G-B degerlerini
     * hesaplamaktir. 
     * Bunun icin öncelikle 4 farkli sicaklik bolgesinin alt ve ust sinirlarini
     * tanimlad?k (region_1_lo, region_1_high gibi) akabinde ilk yaptigimiz is 
     * sensorden gelen datanin hangi bolgeye dustugunu tespit etmek. Bunu da yine 
     * for loop icindeki if sorgulari ile hallettik. 
     * Sonrada hangi if sorgusunun icine dustuysek orada R-G-B degerlerini ve buna bagli olarak 
     * RGB color parametresini hesapladik. RGB color parametresi; baslangicta sensorden gelen 
     * 8bit datanin ait oldugu sicaklik bilgisinin display'e aktarilmis halidir. 
     * RGB color parametresini hesabindan sonra bu veriyi displaye aktaracagiz.
     AMacimiz*/
    /*WHAT THE HELL IS ALL THOSE ">>" and ">>" OPERANDS*/
    /*As we know  from the data sheet of AMG8833 temperature sensors give an output of 16bit which the 
     LSB 2 bits are fractional. 
     The maximum temperature that AMG8833 can measure is 125 centgrad degree. With a 2 bit resolution
     125 centigrad degree corresponds to 125*4=125<<2=500*/
    /* BLUE----->CYAN*/
    region_1_lo = 27<<2;
    region_1_hi = 29<<2;
    /*CYAN----->GREEN*/
    region_2_lo = 29<<2;
    region_2_hi = 31<<2;
    /*GREEN----->YELLOW*/
    region_3_lo = 31<<2;
    region_3_hi = 35<<2;
    /*YELLOW--->RED*/
    region_4_lo = 35<<2;
    region_4_hi = 80<<2;
    
    cell_col_index = 0;
    cell_width = 15;
    cell_height = 15;
    cell_start_x=120;
    cell_start_y=120;
    cell_x = cell_start_x;
    cell_y = cell_start_y;
    
    rgb_coef_reg_1 = (255)/(region_1_hi-region_1_lo);
    rgb_coef_reg_2 = (127)/(region_2_hi-region_2_lo);
    rgb_coef_reg_3 = (127)/(region_3_hi-region_3_lo);
    rgb_coef_reg_4 = (255)/(region_4_hi-region_4_lo);
    
    readPixels(pixelbuffer);
    
    for (i=0;i<64;i++){
                dec = (pixelbuffer[i]);
                                  /* BLUE----->CYAN*/
                /*1st RGB REGION: (0,0,240)->(0,240,240)*/ 
                if (dec<region_1_hi){   
                    R = (uint8_t)(0);
                    G = (uint8_t)((dec * rgb_coef_reg_1));
                    B = (uint8_t)(255);
                color = Color565(R,G,B);
                                    /*CYAN----->GREEN*/
                /*2nd RGB REGION: (0,240,240)->(120,240,120)*/
                } else {
                    if ((dec>=region_2_lo) & (dec<region_2_hi)){   //20 -40
                        R = (uint8_t)((((dec-region_2_lo) * rgb_coef_reg_2)));
                        G = 255;
                        B = (uint8_t)(((255)-((dec-region_2_lo) * rgb_coef_reg_2)));
                    color = Color565(R,G,B);
                                        /*GREEN----->YELLOW*/
                    /*3rd RGB REGION: (120,240,120)->(240,240,0)*/
                    } else {
                        if ((dec>=region_3_lo) & (dec<region_3_hi)){ // 40 - 60 
                            R = (uint8_t)(((127)+((dec-region_3_lo) * rgb_coef_reg_3)));
                            G = (uint8_t)255;
                            B = (uint8_t)(((127)-((dec-region_3_lo) * rgb_coef_reg_3)));
                        color = Color565(R,G,B);
                                            /*YELLOW--->RED*/
                        /*4th RGB REGION: (240,240,0)->(240,0,0)*/
                        }else{
                            if ((dec>=region_4_lo) /*& (dec<region_4_hi)*/){
                                R = (uint8_t)255;
                                G = (uint8_t)(((255)-((dec-region_4_lo)*rgb_coef_reg_4)));
                                B = (uint8_t)0;
                            color = Color565(R,G,B);
                            }else{
                                  ;
                            }
                        }
                    }
                }
                /*Hesaplanan renk bilgisini display'e yollayalim*/        
                fillRect(cell_x,cell_y,cell_width,cell_height,color);
                cell_x+=cell_width;
                cell_col_index++;
                if(cell_col_index == 8)
                {
                    cell_y+=cell_height;
                    cell_x = cell_start_x;
                    cell_col_index = 0;
                }
    }
    cell_x = cell_start_x;
    cell_y+=cell_height;
}
/*************************************************************************/
/*print_hires_pixel_tft_v1 fonksiyonu icin yardimci fonksiyonlar*/
/*************************************************************************/
uint16_t * make22x22(uint16_t *ptr){
/* 
 * Input/Argument  :pointer to a [64] size array
 * Function         :Fills 2 dimensional array named as my22x22 with zeros and 
 *                   with the elements of source array
 * Output           :Returns a pointer which points to the filled array size of 
 *                   22x22   
 * my22x22
 * [00] 0 0 [01] 0 0 [02] 0 0 [03] 0 0 [04] 0 0 [05] 0 0 [06] 0 0 [07] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
   [08] 0 0 [09] 0 0 [10] 0 0 [11] 0 0 [12] 0 0 [13] 0 0 [14] 0 0 [15]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [16] 0 0 [17] 0 0 [18] 0 0 [19] 0 0 [20] 0 0 [21] 0 0 [22] 0 0 [23] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [24] 0 0 [25] 0 0 [26] 0 0 [27] 0 0 [28] 0 0 [29] 0 0 [30] 0 0 [31] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [32] 0 0 [33] 0 0 [34] 0 0 [35] 0 0 [36] 0 0 [37] 0 0 [38] 0 0 [39]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [40] 0 0 [41] 0 0 [42] 0 0 [43] 0 0 [44] 0 0 [45] 0 0 [46] 0 0 [47]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [48] 0 0 [49] 0 0 [50] 0 0 [51] 0 0 [52] 0 0 [53] 0 0 [54] 0 0 [55]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [56] 0 0 [57] 0 0 [58] 0 0 [59] 0 0 [60] 0 0 [61] 0 0 [62] 0 0 [63]  */  

    int i,j,k;
    
    k=0;
    
    while(k<64){
        
        for (i=0;i<22;i++){
            
            for(j=0;j<22;j++){
            
                if((i%3==0)&(j%3==0))
                {
                    my22x22[i][j] = *ptr;   
                    k++;
                    ptr++;
                }
                else
                {
                    my22x22[i][j]=0;
                }
            }
        }
    
    }
    
    return &my22x22[0][0];
}                                    
uint8_t * make_R_22x22(uint8_t *ptr){
/* creates a 22x22 array from elements of R_G_B[64][3] array 
 * The R values are stored in [x][0] indices. And at the start
 *of this function *ptr = R_G_B[0][0]
 * at the end of each loop increasing ptr by 3 will take us to the next 
 * R value from R_G_B[64][3]
 */
    int i,j,k;
    
    k=0;
    
    while(k<64){
        
        for (i=0;i<22;i++){
            
            for(j=0;j<22;j++){
            
                if((i%3==0)&(j%3==0))
                {
                    R_22x22[i][j] = *ptr;   
                    k++;
                    ptr+=3;
                }
                else
                {
                    R_22x22[i][j]=0;
                }
            }
        }
    
    }
    
    return &R_22x22[0][0];
}                                    
uint8_t * make_G_22x22(uint8_t *ptr){
/* creates a 22x22 array from elements of R_G_B[64][3] array 
 * The G values are stored in [x][1] indices. And at the start
 *of this function *ptr = R_G_B[0][0]. Then we must increase ptr just by one 
 * in the beginning to be able to reach R_G_B[0][1]. Then 
 * at the end of each loop increasing ptr by 3 will take us to the next 
 * G value from R_G_B[64][3]
 */
    int i,j,k;
    
    k=0;
    ptr++;
    while(k<64){
        
        for (i=0;i<22;i++){
            
            for(j=0;j<22;j++){
            
                if((i%3==0)&(j%3==0))
                {
                    G_22x22[i][j] = *ptr;   
                    k++;
                    ptr+=3;
                }
                else
                {
                    G_22x22[i][j]=0;
                }
            }
        }
    
    }
    
    return &G_22x22[0][0];
}                                    
uint8_t * make_B_22x22(uint8_t *ptr){
/* creates a 22x22 array from elements of R_G_B[64][3] array 
 * The B values are stored in [x][2] indices. And at the start
 * of this function *ptr = R_G_B[0][0]. Then we must increase ptr by 2. 
 * in the beginning to be able to reach R_G_B[0][1]. Then 
 * At the end of each loop increasing ptr by 3 will take us to the next 
 * B value from R_G_B[64][3]
 */
    int i,j,k;
    
    k=0;
    ptr+=2;
    while(k<64){
        
        for (i=0;i<22;i++){
            
            for(j=0;j<22;j++){
            
                if((i%3==0)&(j%3==0))
                {
                    B_22x22[i][j] = *ptr;   
                    k++;
                    ptr+=3;
                }
                else
                {
                    B_22x22[i][j]=0;
                }
            }
        }
    
    }
    
    return &B_22x22[0][0];
}
void interp_x_8(uint8_t *ptr){
/*
 * print_hires_pixel_tft_v1 fonksiyonu tarafindan kullanilir
 * 
 * Satirlarinda 8bitlik veriler olan bir matrisin satirlarinda interpolasyon yaparak ara 
 * degerleri bulur.
 Input/Argument     : pointer to a sparse matrix of 22x22 which is filled with elements of 8bit
 Function           : Executes 1D interpolation at the rows filled with values
 Output             : - 
 * Interpolated values are x
  [00] x x [01] x x [02] x x [03] x x [04] x x [05] x x [06] x x [07] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
   [08] x x [09] x x [10] x x [11] x x [12] x x [13] x x [14] x x [15]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [16] x x [17] x x [18] x x [19] x x [20] x x [21] x x [22] x x [23] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [24] x x [25] x x [26] x x [27] x x [28] x x [29] x x [30] x x [31] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [32] x x [33] x x [34] x x [35] x x [36] x x [37] x x [38] x x [39]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [40] x x [41] x x [42] x x [43] x x [44] x x [45] x x [46] x x [47]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [48] x x [49] x x [50] x x [51] x x [52] x x [53] x x [54] x x [55]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [56] x x [57] x x [58] x x [59] x x [60] x x [61] x x [62] x x [63]
 */
    int k,i,dx,temp2,temp1;
    k=0;//start to search from 1st column
    for(i=0;i<22;i+=3){         // i = 0,3,6,9,12,15,18,21 -> These are row numbers
        while(k<19){            //try to interpolate values in the first 19 columns(=don't use 21st(=last) column)
            if(k%3==0){         //if there is a value in the column k-> 0,3,6,9,12,15,18 -> these are column numbers
                temp1 = *ptr;   //take the first value
                ptr+=3;         //3 steps forward , point to the next column
                temp2=*ptr;     //take the second value from the next column
                    if(temp1<temp2){
                        dx=(temp2-temp1)/3;
                        ptr--;  // one column back
                        *ptr = temp2-dx; //assign the value to the current column
                        ptr--; // one column back
                        *ptr = temp1+dx; //assign the value to the current colum
                    }else{
                        dx=(temp1-temp2)/3;
                        ptr--;
                        *ptr = temp2+dx;
                        ptr--;
                        *ptr = temp1-dx;
                    }
                ptr+=2;//send pointer to the next column that has a value
                k++;//move next column 
            }
            else{
                k++;
            }
        } // here completes interpolation of current row
        k=0;
        ptr+=45; // pointer needs to skip sparse rows (the 2 rows below)
    }
}   
void interp_x_16(uint16_t *ptr){
/*
 * print_hires_pixel_tft_v2 fonksiyonu tarafindan kullanilir
 * 
 * Satirlarinda 16 bitlik veriler olan bir matrisin satirlarinda interpolasyon yaparak ara 
 * degerleri bulur.
 Input/Argument     : pointer to a sparse matrix of 22x22 which is filled with elements of 16bit
 Function           : Executes 1D interpolation at the rows filled with values
 Output             : - 
 * Interpolated values are x
  [00] x x [01] x x [02] x x [03] x x [04] x x [05] x x [06] x x [07] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
   [08] x x [09] x x [10] x x [11] x x [12] x x [13] x x [14] x x [15]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [16] x x [17] x x [18] x x [19] x x [20] x x [21] x x [22] x x [23] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [24] x x [25] x x [26] x x [27] x x [28] x x [29] x x [30] x x [31] 
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [32] x x [33] x x [34] x x [35] x x [36] x x [37] x x [38] x x [39]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [40] x x [41] x x [42] x x [43] x x [44] x x [45] x x [46] x x [47]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [48] x x [49] x x [50] x x [51] x x [52] x x [53] x x [54] x x [55]
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   
    0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0   0 0  0 
   [56] x x [57] x x [58] x x [59] x x [60] x x [61] x x [62] x x [63]
 */
    int k,i,dx,temp2,temp1;
    k=0;//start to search from 1st column
    for(i=0;i<22;i+=3){         // i = 0,3,6,9,12,15,18,21 -> These are row numbers
        while(k<19){            //try to interpolate values in the first 19 columns(=don't use 21st(=last) column)
            if(k%3==0){         //if there is a value in the column k-> 0,3,6,9,12,15,18 -> these are column numbers
                temp1 = *ptr;   //take the first value
                ptr+=3;         //3 steps forward , point to the next column
                temp2=*ptr;     //take the second value from the next column
                    if(temp1<temp2){
                        dx=(temp2-temp1)/3;
                        ptr--;  // one column back
                        *ptr = temp2-dx; //assign the value to the current column
                        ptr--; // one column back
                        *ptr = temp1+dx; //assign the value to the current colum
                    }else{
                        dx=(temp1-temp2)/3;
                        ptr--;
                        *ptr = temp2+dx;
                        ptr--;
                        *ptr = temp1-dx;
                    }
                ptr+=2;//send pointer to the next column that has a value
                k++;//move next column 
            }
            else{
                k++;
            }
        } // here completes interpolation of current row
        k=0;
        ptr+=45; // pointer needs to skip sparse rows (the 2 rows below)
    }
}       
void interp_YY_8(uint8_t *ptr){
/*
 * print_hires_pixel_tft_v1 fonksiyonu tarafindan cagirilir. 
 * 
 * sutunlarinda 8bitlik veri bulunan bir matriste sutun interpolasyonu yapar. 
 * Yani sutunlardaki verileri kullanarak bu veriler arasindaki ara degerleri hesaplar. 
 * This function finds the values of intermediate pixels (xs) via linear interpolation between */
    
/* 
 * 
 * [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     1   
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     2
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     4
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     5
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     7
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     8
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    10
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    11
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    13
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    14
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21] 
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    16
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    17 
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    19
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    20
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
 */
    int k,i,dx,temp2,temp1;
    uint8_t *ptr_start;
    ptr_start = ptr;
    k=0;//start to search from 1st column
    i=0;//start to search from 1st row
    for(k=0;k<22;k++){         // k = 0,1,2,3....,21 -> These are column numbers
        ptr = ptr_start + k ;  // take pointer to the beginning of the column 
        while(i<19){            //try to interpolate values in the first 19 rows(=don't use 21st(=last) row)
            if(i%3==0){         //if there is a value in the row i-> 0,3,6,9,12,15,18 -> these are row numbers
                temp1 = *ptr;   //take the first value
                ptr+=66;         //3 rows downward , point to the next row with a value
                temp2=*ptr;     //take the second value from the next row
                    if(temp1<temp2){
                        dx=(temp2-temp1)/3;
                        ptr-=22;  // one column back
                        *ptr = temp2-dx; //assign the value to the current column
                        ptr-=22; // one column back
                        *ptr = temp1+dx; //assign the value to the current colum
                    }else{
                        dx=(temp1-temp2)/3;
                        ptr-=22;
                        *ptr = temp2+dx;
                        ptr-=22;
                        *ptr = temp1-dx;
                    }
                ptr+=44;//send pointer to the next column that has a value
                i++;//move 
            }
            else{
                i++;
            }
        } // here completes interpolation of current column
        i=0; // return to the first row
    }
}    
void interp_YY_16(uint16_t *ptr){
/*
 *  * print_hires_pixel_tft_v2 fonksiyonu tarafindan cagirilir. 
 * 
 * sutunlarinda 16bitlik veri bulunan bir matriste sutun interpolasyonu yapar. 
 * Yani sutunlardaki verileri kullanarak bu veriler arasindaki ara degerleri hesaplar. 
 * This function finds the values of intermediate pixels (xs) via linear interpolation between 
 * This function finds the values of intermediate pixels (xs) via linear interpolation between */ 
/* [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     1   
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     2
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     4
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     5
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     7
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0     8
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    10
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    11
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    13
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    14
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21] 
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    16
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    17 
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    19
    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    20
   [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21]
 */
    int k,i,dx,temp2,temp1;
    uint16_t *ptr_start;
    ptr_start = ptr;
    k=0;//start to search from 1st column
    i=0;//start to search from 1st row
    for(k=0;k<22;k++){         // k = 0,1,2,3....,21 -> These are column numbers
        ptr = ptr_start + k ;  // take pointer to the beginning of the column 
        while(i<19){            //try to interpolate values in the first 19 rows(=don't use 21st(=last) row)
            if(i%3==0){         //if there is a value in the row i-> 0,3,6,9,12,15,18 -> these are row numbers
                temp1 = *ptr;   //take the first value
                ptr+=66;         //3 rows downward , point to the next row with a value
                temp2=*ptr;     //take the second value from the next row
                    if(temp1<temp2){
                        dx=(temp2-temp1)/3;
                        ptr-=22;  // one column back
                        *ptr = temp2-dx; //assign the value to the current column
                        ptr-=22; // one column back
                        *ptr = temp1+dx; //assign the value to the current colum
                    }else{
                        dx=(temp1-temp2)/3;
                        ptr-=22;
                        *ptr = temp2+dx;
                        ptr-=22;
                        *ptr = temp1-dx;
                    }
                ptr+=44;//send pointer to the next column that has a value
                i++;//move 
            }
            else{
                i++;
            }
        } // here completes interpolation of current column
        i=0; // return to the first row
    }
}    
void interp_y_8(uint8_t *ptr){
    /*print_hires_pixel_tft_v1 fonksiyonu icindeki eski kod tarafindan kullaniliyordu. 
     Yeni kod interp_YY_8 'i cagiriyor. */
    int k,i,dx,temp2,temp1;
    k=0;//start to search from 1st column
    for(i=0;i<22;i++){
        while(k<19){            //try to interpolate values in the first 19 columns(=don't use 21st(=last) column)
            if(k%3==0){         //if there is a value in the column
                temp1 = *ptr;   //take the first value
                ptr+=3;         //3 steps forward
                temp2=*ptr;     //take the second value
                    if(temp1<temp2){
                        dx=(temp2-temp1)/3;
                        ptr--;  
                        *ptr = temp2-dx;
                        ptr--;
                        *ptr = temp1+dx;
                    }else{
                        dx=(temp1-temp2)/3;
                        ptr--;
                        *ptr = temp2+dx;
                        ptr--;
                        *ptr = temp1-dx;
                    }
                ptr+=2;//send pointer to the next column that has a value
                k++;//move next column 
            }
            else{
                k++;
            }
        } // here completes interpolation of current row
        k=0;
        ptr++;
    }
}   
uint8_t * get_R_G_B_of_pixel_v0(uint16_t *ptr){
    /*This function calculates R-G-B equivalents of each 64 output of thermal sensor.
     * Argument of function: *ptr points to the output of thermal sensor.
     * Output of function: Returns a pointer which points to the first element of [64][3] sized 
     *                      array which is R_G_B[64][3];
     * 
     * HOW THIS FUNCTION WORKS?
     * 
     * Thermal sensor's maximum output is 125 centigrad degree with a resolution of 0,25.
     * According to AMG8833 data sheet  maximum hex output is 1F4(=500). (This is consitent 
     * with 125 centigrad degree) . We part dynamic range of thermal sensor into 4 parts. 
     * [0-125)-[125-250)-[250-375)-[375-500]
     * We define high and low limits of each parts. This 4 part also corresponds
     * to the 4 parts of RGB color pallete from cold to hot. 
     * Then first we determine in which bin is thermal sensor output included . According to 
     * that bin R and G and B values are calculated for the related pixel . 
     */
        
    float region_1_hi,region_1_lo,region_2_hi,region_2_lo,region_3_hi,region_3_lo,region_4_hi,region_4_lo;
    float rgb_coef_reg_1,rgb_coef_reg_2,rgb_coef_reg_3,rgb_coef_reg_4;
    uint16_t i;
    

        /*FIRST we need to determine start-end limits of color regions which pixel value belongs to*/
        /*For thermal values between zero and 125 
         * the smallest pixel value(dec) is 0 and the maximum pixel value is 500*/
        /* BLUE----->CYAN*/
        region_1_lo = 27<<2; //0
        region_1_hi = 29<<2;//125
        /*CYAN----->GREEN*/
        region_2_lo = 29<<2;//125
        region_2_hi = 31<<2;//250
        /*GREEN----->YELLOW*/
        region_3_lo = 31<<2;//250
        region_3_hi = 35<<2;//375
        /*YELLOW--->RED*/
        region_4_lo = 35<<2;//375
        region_4_hi = 80<<2;//500
        
        rgb_coef_reg_1 = (255)/(region_1_hi-region_1_lo);
        rgb_coef_reg_2 = (255)/(region_2_hi-region_2_lo);
        rgb_coef_reg_3 = (255)/(region_3_hi-region_3_lo);
        rgb_coef_reg_4 = (255)/(region_4_hi-region_4_lo);
        
        for(i=0;i<64;i++) //for loop iterates 64 times . 1 iteration for 1 sensor cell
        {
                                /* BLUE----->CYAN*/
            /*If thermal sensor output is in the 1st part*/
            /*1st RGB REGION: (0,0,255)->(0,255,255)*/ //----------------G(0->255)
        if (*ptr<region_1_hi)
        {   
            R_G_B[i][0] = (uint8_t)(0);
            R_G_B[i][1] = (uint8_t)((*ptr * rgb_coef_reg_1));
            R_G_B[i][2] = (uint8_t)(255);
            ptr++;        
        /*2nd RGB REGION: (0,255,255)->(0,255,0)*/ //-------------------B(255->0)
        } else{ 
            if ((*ptr>=region_2_lo) & (*ptr<region_2_hi)){   
                R_G_B[i][0] = 0;
                R_G_B[i][1] = 255;
                R_G_B[i][2] = (uint8_t)(((255)-((*ptr-region_2_lo) * rgb_coef_reg_2)));
                ptr++;
            /*3rd RGB REGION: (0,255,0)->(255,255,0)*/ //----------------R(0->255)
                }else{ 
                if ((*ptr>=region_3_lo) & (*ptr<region_3_hi)){ 
                    R_G_B[i][0] = (uint8_t)((((*ptr-region_3_lo) * rgb_coef_reg_3)));
                    R_G_B[i][1] = (uint8_t)255;
                    R_G_B[i][2] = (uint8_t)0;
                    ptr++;
                /*4th RGB REGION: (255,255,0)->(255,0,0)*/ //------------G(255->0)
                }else{
                    if ((*ptr>=region_4_lo) ){
                        R_G_B[i][0] = (uint8_t)255;
                        R_G_B[i][1] = (uint8_t)(((255)-((*ptr-region_4_lo)*rgb_coef_reg_4)));
                        R_G_B[i][2] = (uint8_t)0;
                        ptr++;
//                    printf("pixel value = %d R=%d G=%d B=%d RGB565 = %d\n",dec,R,G,B,color);
                    }else{
                          ;
                    }
                }
            }
        }

    }  
        return &R_G_B[0][0];
    }
uint8_t * get_R_G_B_of_pixel(uint16_t *ptr){
    
    /*print_hires_pixel_tft_v1 fonksiyonunda kullaniliyor
     * This function calculates R-G-B equivalents of each 64 output of thermal sensor.
     * Argument of function: *ptr points to the output of thermal sensor.
     * Output of function: Returns a pointer which points to the first element of [64][3] sized 
     *                      array which is R_G_B[64][3];
     * 
     * HOW THIS FUNCTION WORKS?
     * 
     * Thermal sensor's maximum output is 125 centigrad degree with a resolution of 0,25.
     * According to AMG8833 data sheet  maximum hex output is 1F4(=500). (This is consitent 
     * with 125 centigrad degree) . We part dynamic range of thermal sensor into 4 parts. 
     * [0-125)-[125-250)-[250-375)-[375-500]
     * We define high and low limits of each parts. This 4 part also corresponds
     * to the 4 parts of RGB color pallete from cold to hot. 
     * Then first we determine in which bin is thermal sensor output included . According to 
     * that bin R and G and B values are calculated for the related pixel . 
     * 
     * MEVZU NE ? 
     * 4 renk bolgesi tanimladik ve tüm kod bu tanimlamalara gore sekillendi. 
     *  BLUE---->CYAN
     *  CYAN----->GREEN
     *  GREEN----->YELLOW
     *  YELLOW--->RED
     * 1nci bolgede Blue'dan baslayip   (R=0    G=0     B=255) cyan'da (R=0 G=255 B=255)biter
     * 2nci bolgede Cyan'dan baslayip   (R=0    G=255   B=255) green'da (R=0 G=255 B=0)biter
     * 3nci bolgede Green'dan baslayip  (R=0    G=255   B=0) yellow'da (R=255 G=255 B=0)biter
     * 4nci bolgede Yellow'dan baslayip (R=255  G=255   B=0) red'da (R=255 G=0 B=0)biter
     * Dikkat edelim her bir renk bolgesinde 255 birimlik degisim soz konusudur. Yani 1nci bolge
     * oynayabilecegimiz yada olusturabilecegimiz 255 farkl? renk vardir. Diger bolgeler icin de 
     * aynisi soz konusudur.
     * 
     * Elimizde 4 renk bolgesi oldugu icin thermal sensorun pixellerinden gelen sicaklik bil-
     * gilerini de 4 bolgeye ayirmaliyiz. 
     * sens_1_lo --> 1nci bolgenin alt siniri
     * sens_1_hi --> 1nci bolgenin ust siniri
     * sens_2_lo
     * sens_2_hi
     * sens_3_lo
     * sens_3_hi
     * sens_4_lo
     * sens_4_hi
     * 
     * sicaklik bilgilerini neye gore ayirdik ? 
     * ozellikle ilgilendigimiz bir sicaklik alani yoksa yani sicaklik skalasinin tamamiyla 
     * ilgileniyorsak;  sensorumuzden 0-500(=125derece) arasi bilgi gelecegi 
     * icin 0-125 / 125-250 / 250-375 / 375-500 seklinde gruplandirma yapabilirdik
     * ama diyelim ki 24 derece ile 35 derece arasi sicakliklari daha iyi goruntulemek istiyoruz 
     * o zaman da sinirlari 96-108 / 108-120 / 120-124 / 124-140 seklinde belirleriz 
     * Sinirlarimizi boyle belirledigimizi varsayarsak;
     * 96-108 arasindaki 12 farkli sicaklik bilgisini 1nci renk bolgesine projekte etmemiz gerekir. 
     * 1nci renk bolgesinde toplam 255 farkli renk olduguna gore her bir sicaklik icin 
     * renkte yaratmamiz gereken degisim 255/12 olmalidir. Bunu color_step_1 = 255 / (sens_1_hi - sens_1_lo);
     * kod satiri ile gercekledik.
     * Yukarida tek bir adimda yaratmamiz gereken degisimi bulduk. simdi sira kac adim atmamiz gerektigini bulmakta
     * Bunun icin sicaklik bilgisinin ait oldugu araliktaki kacinci sicaklik bilgisi oldugunu 
     * bulmamiz gerekir. (*ptr * sens_1_lo) ve diger kodlar ile de adim sayisini bulduk. 
     * Sonra da bunlari carptik. 
     * (*ptr * sens_1_lo)*color_step_1)
     * 255 - (*ptr * sens_2_lo)*color_step_2)
     * (*ptr * sens_3_lo)*color_step_3)
     * 255 - (*ptr * sens_4_lo)*color_step_4)
     * 2nci ve 4ncu renk bolgesinde bolge baslangici 255 bolge sonu 0 oldugu icin renk kodunu 255'ten cikardik.
     */   
    float sens_1_lo, sens_1_hi, sens_2_lo, sens_2_hi, sens_3_lo, sens_3_hi, sens_4_lo,sens_4_hi;
    float color_step_1, color_step_2, color_step_3, color_step_4 ;
    uint16_t i;

        max_temp = 0;
        max_temp_index = 0;   
//        sens_1_lo = 0<<2;  
//        sens_1_hi = 30<<2; 
//        
//        sens_2_lo = 30<<2;   
//        sens_2_hi = 45<<2; 
//        
//        sens_3_lo = 45<<2;   
//        sens_3_hi = 90<<2; 
//        
//        sens_4_lo = 90<<2;   
//        sens_4_hi = 125<<2; 
        
        sens_1_lo = 24<<2;  
        sens_1_hi = 27<<2; 
        
        sens_2_lo = 27<<2;   
        sens_2_hi = 30<<2; 
        
        sens_3_lo = 30<<2;   
        sens_3_hi = 31<<2; 
        
        sens_4_lo = 31<<2;   
        sens_4_hi = 35<<2; 
        
        /*BLUE---->CYAN*/
        /*CYAN----->GREEN*/
        /*GREEN----->YELLOW*/
        /*YELLOW--->RED*/
        
        color_step_1 = 255 / (sens_1_hi - sens_1_lo);
        color_step_2 = 255 / (sens_2_hi - sens_2_lo);
        color_step_3 = 255 / (sens_3_hi - sens_3_lo);
        color_step_4 = 255 / (sens_4_hi - sens_4_lo);

        for(i=0;i<64;i++) //for loop iterates 64 times . 1 iteration for 1 sensor cell
        {
            if (*ptr > max_temp ){
                max_temp = *ptr;
                max_temp_index = i;
            }
            
            /* BLUE----->CYAN*/
            /*If thermal sensor output is in the 1st part*/
            /*1st RGB REGION: (0,0,255)->(0,255,255)*/ //----------------G(0->255)
        if (*ptr < sens_1_lo){
            R_G_B[i][0] = (uint8_t)(0);
            R_G_B[i][1] = (uint8_t)(0);
            R_G_B[i][2] = (uint8_t)(255);
            ptr++;        
        }else{
              if ((*ptr >= sens_1_lo) & (*ptr < sens_1_hi)){
                R_G_B[i][0] = (uint8_t)(0) ;
                R_G_B[i][1] = (uint8_t)((*ptr * sens_1_lo)*color_step_1);
                R_G_B[i][2] = (uint8_t)(255);
                ptr++;        
                    }else{
                          if ((*ptr >= sens_2_lo)&(*ptr<sens_2_hi)){   
                            R_G_B[i][0] = (uint8_t)(0);
                            R_G_B[i][1] = (uint8_t)(255);
                            R_G_B[i][2] = (uint8_t)(255) - (uint8_t)((*ptr-sens_2_lo) * color_step_2);
                            ptr++; 
                            }else{
                                 if ((*ptr >= sens_3_lo)&(*ptr<sens_3_hi)){
                                    R_G_B [i][0] = (uint8_t)((*ptr-sens_3_lo)* color_step_3);
                                    R_G_B [i][1] = (uint8_t)(255);
                                    R_G_B [i][2] = (uint8_t)(0);
                                    ptr++; 
                                    }else{
                                         if ((*ptr >= sens_4_lo)&(*ptr<sens_4_hi)){
                                            R_G_B[i][0] = (uint8_t)(255); 
                                            R_G_B[i][1] = (uint8_t)(255) - (uint8_t)((*ptr - sens_4_lo)*color_step_4);
                                            R_G_B[i][2] = (uint8_t)(0);
                                            ptr++; 
                                                   }else{
                                                        if (*ptr > sens_4_hi){
                                                            R_G_B[i][0] = (uint8_t)(255); 
                                                            R_G_B[i][1] = (uint8_t)(0);
                                                            R_G_B[i][2] = (uint8_t)(0);
                                                            ptr++; 
                                                        }else{
                                                        ;
                                                        }
                                                   }
                                    }    
                            }                   
                    }           
        }                   
                            
                   

    }  
        return &R_G_B[0][0];
    }
uint8_t * get_RR_GG_BB_of_pixel(uint16_t *ptr){
    
/* print_hires_pixel_tft_v2 fonksiyonu icinde kullaniliyor
 * Diyelim ki sicaklik sensoru
 * bize ortamin 32derece oldugu bilgisini verdi. Ne yapmak istiyoruz ? 32dereceyi gorsellestimek
 * istiyoruz. Yani 32dereceye tekabul eden bir renk uretmek istiyoruz. Sar? renk mesela. 
 * Sari Rengi nasil uretecegiz ? RGB kodlariyla uretecegiz. Yani saiya tekabul eden R bilgisini 
 * G bilgisini ve B bilgisini hesaplamamiz gerekir. ?ste bu program o isi yapiyor. 
 * 
 *  22x22 matris icindeki sicaklik sensor bilgileri icin R-G-B degerlerini uretecegiz
 */
    float sens_1_lo, sens_1_hi, sens_2_lo, sens_2_hi, sens_3_lo, sens_3_hi, sens_4_lo,sens_4_hi;
    float color_step_1, color_step_2, color_step_3, color_step_4 ;
    uint16_t i,j;

        max_temp = 0;
        max_temp_index = 0;   
//        sens_1_lo = 0<<2;  
//        sens_1_hi = 30<<2; 
//        
//        sens_2_lo = 30<<2;   
//        sens_2_hi = 45<<2; 
//        
//        sens_3_lo = 45<<2;   
//        sens_3_hi = 90<<2; 
//        
//        sens_4_lo = 90<<2;   
//        sens_4_hi = 125<<2; 
        
        sens_1_lo = 24<<2;  
        sens_1_hi = 27<<2; 
        
        sens_2_lo = 27<<2;   
        sens_2_hi = 30<<2; 
        
        sens_3_lo = 30<<2;   
        sens_3_hi = 31<<2; 
        
        sens_4_lo = 31<<2;   
        sens_4_hi = 35<<2; 
        
        /*BLUE---->CYAN*/
        /*CYAN----->GREEN*/
        /*GREEN----->YELLOW*/
        /*YELLOW--->RED*/
        
        color_step_1 = 255 / (sens_1_hi - sens_1_lo);
        color_step_2 = 255 / (sens_2_hi - sens_2_lo);
        color_step_3 = 255 / (sens_3_hi - sens_3_lo);
        color_step_4 = 255 / (sens_4_hi - sens_4_lo);

        for(i=0;i<22;i++) //for loop iterates 64 times . 1 iteration for 1 sensor cell
        {
            for (j=0;j<22;j++){
            /* BLUE----->CYAN*/
            /*If thermal sensor output is in the 1st part*/
            /*1st RGB REGION: (0,0,255)->(0,255,255)*/ //----------------G(0->255)
                if (*ptr < sens_1_lo){
                    RR_GG_BB[i][j][0] = (uint8_t)(0);
                    RR_GG_BB[i][j][1] = (uint8_t)(0);
                    RR_GG_BB[i][j][2] = (uint8_t)(255);
                    ptr++;        
                }else{
                    if ((*ptr >= sens_1_lo) & (*ptr < sens_1_hi)){
                        RR_GG_BB[i][j][0] = (uint8_t)(0) ;
                        RR_GG_BB[i][j][1] = (uint8_t)((*ptr * sens_1_lo)*color_step_1);
                        RR_GG_BB[i][j][2] = (uint8_t)(255);
                        ptr++;        
                    }else{
                            if ((*ptr >= sens_2_lo)&(*ptr<sens_2_hi)){   
                                RR_GG_BB[i][j][0] = (uint8_t)(0);
                                RR_GG_BB[i][j][1] = (uint8_t)(255);
                                RR_GG_BB[i][j][2] = (uint8_t)(255) - (uint8_t)((*ptr-sens_2_lo) * color_step_2);
                                ptr++; 
                            }else{
                                 if ((*ptr >= sens_3_lo)&(*ptr<sens_3_hi)){
                                        RR_GG_BB[i][j][0] = (uint8_t)((*ptr-sens_3_lo)* color_step_3);
                                        RR_GG_BB[i][j][1] = (uint8_t)(255);
                                        RR_GG_BB[i][j][2] = (uint8_t)(0);
                                        ptr++; 
                                 }else{
                                         if ((*ptr >= sens_4_lo)&(*ptr<sens_4_hi)){
                                                RR_GG_BB[i][j][0] = (uint8_t)(255); 
                                                RR_GG_BB[i][j][1] = (uint8_t)(255) - (uint8_t)((*ptr - sens_4_lo)*color_step_4);
                                                RR_GG_BB[i][j][2] = (uint8_t)(0);
                                                ptr++; 
                                         }else{
                                               if (*ptr > sens_4_hi){
                                                    RR_GG_BB[i][j][0] = (uint8_t)(255); 
                                                    RR_GG_BB[i][j][1] = (uint8_t)(0);
                                                    RR_GG_BB[i][j][2] = (uint8_t)(0);
                                                            ptr++; 
                                                }else{
                                                        ;
                                                        }
                                                   }
                                    }    
                            }                   
                    }           
        }                   
                            
                   

    } 
            }
            
            
 
        return &RR_GG_BB[0][0][0];
    }
/*************************************************************************/
/*DEBUG DEFINITIONS*/
//#define debug_hires
#define debug_hires_RGB
#define debug_hires_pixelbuffer
//#define debug_hires_R
//#define debug_hires_G
//#define debug_hires_B
//#define debug_hires_final
//#define debug_2_python
void print_hires_pixel_tft_v1(void){
    /*MOTIVATION-IDEA*/
// AMG8833 sensoru 8x8 termal pixelde olusmakta. Yani 64 pixellik bir   cozunurluk 
// sozkonusu. Cozunurlugu. Bu fonksiyon cozunurlugu 22x22 ye cikarmaktad?r. Ozetle soyle 
// yapildi. 
    
//1-) Oncelikle 64 elemandan olusan pixelbuffer'dan veriler alindi
//2-) get_R_G_B_of_pixel fonksiyonuyla her bir sicaklik verisinin karsiligi olan 
//    R-G-B degerleri hesaplandi ve R_G_B[64][3] dizisine kaydedildi.
//3-) make_R_22x22 fonksiyonu ile R_22x22[22][22] matrisi olsuturuldu. Bu matriste 
//bir onceki adimda hesaplanan 64 adet R degeri ve geri kalani da 0 kaydedildi
//4-) make_G_22x22 fonksiyonu calistirildi ve G_22x22[22][22] matrisi olusturuldu
//5-) make_B_22x22 fonksiyonu calistirildi ve B_22x22[22][22] matrisi olusturuldu
//6-) R_22x22[22][22] matrisinin sirayla satir ve sutunlari icin interpolasyon yapilarak
//    0 degerli elemanlarinin gercek degerleri hesaplandi. 
//7-) G_22x22[22][22] matrisinin sirayla satir ve sutunlari icin interpolasyon yapilarak
//    0 degerli elemanlarinin gercek degerleri hesaplandi. 
//8-) B_22x22[22][22] matrisinin sirayla satir ve sutunlari icin interpolasyon yapilarak
//    0 degerli elemanlarinin gercek degerleri hesaplandi. 
//9-) Kodun final my22x22 baslikli kisminda R_22x22 , G_22x22, B_22x22 matrislerinden 
//    sirayla alinan R-G-B degerlerinden ST7789 kutuphanesindeki Color565 fonksiyonu 
//    yardimiyla LCD displayin gosterebilecegi RGB degeri hesaplanarak my22x22 matrisine depolandi
//10-) my22x22 matrisindeki veriler ST7789 kutuphanesindeki fillRect komutuyla displayde goruntulendi
    
        
        
//     I have 64 IR temp sensor configured as 8x8. 
//     In the function print_8x8_table_tft:
//        1) I drawed a grid comprised of 64 cells which are configured as 8x8 
//     *      (each cell is assigned to the relative sensor) and 
//     *  2) I assigned RGB value to each grid cell the value that i calculated from the temperature value 
//     *      of related temperature sensor. 
//     (So suppose a cell is comprised of 15x15 = 165 pixel then this comes to a meaning 
//     * that i assigned the same RGB value to all of that 165 pixels.) 
//     BUT WHATIF if i use each sensor value to determine RGB value of JUST THE CENTER PIXEL of 
//     * relative cell instead of all the pixels belongs to that grid?
//     This wil give me the opportunity to interpolate adjacent sensor'S values and project the outcomes of interpolation
//     (intermediate values) over the pixels of adjacent cell grids.*/
    
//    /*FIRST TRY(FAILED)*/
//    /*Suppose width of a cell is 16pixels then there should be 8+8=16pixels 
//             -------- -------
//             |       |       |
//             |   .   |   .   |      (.-> center pixels)
//             |       |       |
//             -------- -------
//     between the center pixels of adjacent grid cells.I must calculate the intermediate temperature values for this 16 pixels.
//     The center pixel of first  grid cell will have the exact value coming from the related sensor
//     The center pixel of second grid cell will have the exact value coming from the related sensor
//     but the 16 pixels that are laying between 2 center pixels will have the intermediate values 
//     * that i will calculate from the 2 sensors values.
//     If i use the temperature value for center pixels then this forces me to make interpolation between the 2 temperature
//     value. BUT; According to the sensor data sheet sensor resolution is 0,25 degree. So adjacent 2 pixels should have 
//     values with a minimum difference of 0,25 degree. Then if only 2 adjacent sensors have a temperature difference 
//     (18*0,25 = 4,5) of minimum 4,5 degree then this difference can be interpolated over the pixels 
//     that are laying between 2 center pixels. This kind of attempt make it impossible to represent temperature differences lower 
//     * then 4,5 degrees. 
//     */
//    /* SECOND TRY(FAILED)*/
//    /*if i take lesson from the first try then i should not use real temperature values for center pixels. Instead;
//     i will try to convert real temperature values to RGB and then make interpolation between those RGB values.
//     .... after some hard work...
//     suppose 2 adjacent sensor cells have values of 33degree and 36degree.
//     i generate combined RGB values respectively such as 500 and 800. And suppose i try to increase resolution 
//     by adding 2 extra virtual pixel between 2 adjacent sensors. Then i must calculate RGB values for those 
//     virtual pixels. And according to real values of 500 and 800, the intermediate pixels must have values 
//     of 600 and 700. I did all those calculations. And then send RGB values to display. But i witnessed color
//     discontinuties at the pixel locations. After some research i found out that although result of interpolation 
//     for intermediate pixels are 600 and 700; those values don't cause  a smooth transition in color.
//     Why ? because combined RGB formation formula Color565(R,G,B); function does not behave as a linear function. 
//     That process is a non linear process. For example while R=255 G=120 B=80 results in a combined value of 500
//     close R,G,B values such as R=250 G=100 B=60 results in 950. I mean i understood that as color values 500 is
//     not followed by 600.
//     */
//    /* THIRD TRY(SUCCESS)*/
//    /*After i attain 64 pixel values from sensor. I generate individual R-G-B values
//     for each pixel point with the help of uint8_t * get_R_G_B_of_pixel and then 
//     load results into the specific R, G, and B arrays. Then 
//     i expand all those arrays to the size of 22x22 respectively with make_R_22x22, make_G_22x22 and
//     * make_B_22x22 functions. Then i made interpolations on 
//     each array (R_22x22,G_22x22,B_22x22). After interpolation process i draw 3 distinct RGB values for a pixel point
//     and generate combined RGB values for that pixel point and load it into my22x22*/
    uint16_t color;
    uint16_t pixelbuffer[64];
    uint8_t *R_G_B_ptr,*temp_R_G_B_ptr,*R_22x22_ptr,*G_22x22_ptr,*B_22x22_ptr;
    int i,j,cell_start_x,cell_start_y,cell_x,cell_y,h,w;

/*1-)************fill pixelbuffer[64] with thermal sensor outputs*******************/    
    readPixels(pixelbuffer);
    #ifdef debug_hires_pixelbuffer
        outString("Real pixel values\n");
        for (i=0;i<64;i++)
        {
            data16_2_dec_ascii_print(pixelbuffer[i]);
            if(((i+1)%8==0)){new_line();}
        }
    new_line();
    #endif

/*2-)*********decompose each pixel value into its R,G,B components*****************/
/*   ******************and fill R_G_B[64][3]**********************************    */
    /*This part of code is filling R_G_B[64][3] array. */
    R_G_B_ptr = get_R_G_B_of_pixel(pixelbuffer);
    temp_R_G_B_ptr = R_G_B_ptr;
    #ifdef debug_hires_RGB
    outString("R_G_B[64][3] Values\n");
        for (i=0;i<64;i++)
        {
            outString("...Pixel...R_G_B ");
            for(j=0;j<3;j++)
            {
                data16_2_dec_ascii_print(R_G_B[i][j]);
                print_space();
            }
            new_line();
        }
    new_line();
    #endif
/*3-)*************************create R_22x22 with sparse values *******************/
    R_G_B_ptr = &R_G_B[0][0];
    R_22x22_ptr=make_R_22x22(R_G_B_ptr);
    #ifdef debug_hires_R
    outString("R_22x22_sparse Values\n");
        for (i=0;i<22;i++)
        {
            for(j=0;j<22;j++)
            {
                data16_2_dec_ascii_print(R_22x22[i][j]);
                print_space();
                #ifdef debug_2_python
                    send_uart2_8((R_22x22[i][j])>>8);
                    send_uart2_8(R_22x22[i][j]);
                #endif

            }
            new_line();
        }
    new_line();
    #endif
/*4-)*********************create G_22x22 with sparse values ***********************/
    R_G_B_ptr = temp_R_G_B_ptr;
    G_22x22_ptr=make_G_22x22(R_G_B_ptr); 
    #ifdef debug_hires_G
    outString("G_22x22 Values\n");
        for (i=0;i<22;i++)
        {
            for(j=0;j<22;j++)
            {
                data16_2_dec_ascii_print(G_22x22[i][j]);
                #ifdef debug_2_python
                    send_uart2_8((G_22x22[i][j])>>8);
                    send_uart2_8(G_22x22[i][j]);
                #endif

                print_space();
            }
            new_line();
        }
    new_line();
    #endif
/*5-)********************create B_22x22 with sparse values**************************/    
    R_G_B_ptr = temp_R_G_B_ptr;
    B_22x22_ptr=make_B_22x22(R_G_B_ptr);    
    #ifdef debug_hires_B
    outString("B_22x22 Values\n");
        for (i=0;i<22;i++)
        {
            for(j=0;j<22;j++)
            {
                data16_2_dec_ascii_print(B_22x22[i][j]);
                #ifdef debug_2_python
                    send_uart2_8((B_22x22[i][j])>>8);
                    send_uart2_8(B_22x22[i][j]);
                #endif
                print_space();
            }
            new_line();
        }
    new_line();
    #endif

/*6-)************************interpolation of R_22x22**************************/
    
/*6.1)X interpolation of R*/
#ifdef debug_hires_R

    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(R_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
    interp_x_8(R_22x22_ptr);
    interp_YY_8(R_22x22_ptr);
#ifdef debug_hires_R
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(R_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
    
/****ESKI KOD *****************************************************************************************************************/
//    #ifdef debug_hires_R
//    outString("R values [X-interpolation]\n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(R_22x22[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((R_22x22[i][j])>>8);
//                    send_uart2_8(R_22x22[i][j]);
//                #endif
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//
///*6.2)Transpose R_22x22 */      
//    #ifdef debug_hires_R
//        outString("R Values [X interpolation-transposed]\n");
//    #endif    
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            tempr[j][i] = R_22x22[i][j];    
//            #ifdef debug_hires_R
//                data16_2_dec_ascii_print(tempr[i][j]);
//                print_space();
//            #endif   
//        }
//        #ifdef debug_hires_R
//            new_line();
//        #endif
//    }
//    #ifdef debug_hires_R
//        new_line();
//    #endif       
//
///*6.3)Y interpolation of R */
//    R_22x22_ptr = &tempr[0][0]; //dikkat edelim pointer burada tempi'ye ayarlandi
//    interp_y_8(R_22x22_ptr);
//    #ifdef debug_hires_R
//    outString("R Values [X interpolation-transposed-Y interpolation ] \n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(tempr[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((tempi[i][j])>>8);
//                    send_uart2_8(tempi[i][j]);
//                #endif
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//
///*6.4)Re-transpose of R*/ 
//    #ifdef debug_hires_R
//        outString("Final R Values\n");
//    #endif    
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            R_22x22[j][i] = tempr[i][j];  
//            #ifdef debug_hires_R
//                data16_2_dec_ascii_print(R_22x22[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((R_22x22[i][j])>>8);
//                    send_uart2_8(R_22x22[i][j]);
//                #endif
//            #endif
//        }         
//        #ifdef debug_hires_R
//               new_line();
//        #endif
//    }
//    #ifdef debug_hires_R
//        new_line();
//    #endif
/******************************************************************************************************************************/

/*7-)*********************interpolation of G_22x22****************************/
        
/*7.1)X Interpolation of G*/
#ifdef debug_hires_G
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(G_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif 
    interp_x_8(G_22x22_ptr);
    interp_YY_8(G_22x22_ptr);
#ifdef debug_hires_G
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(G_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
/*****ESKI KOD*****************************************************************************************************************/
//    #ifdef debug_hires_G
//    outString("G values [X-interpolation]\n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(G_22x22[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((G_22x22[i][j])>>8);
//                    send_uart2_8(G_22x22[i][j]);
//                #endif
//                /**************************************************************************/
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//
///*7.2)Transpose of G*/   
//    #ifdef debug_hires_G
//        outString("G Values [X interpolated-transposed]\n");
//    #endif  
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            tempg[j][i] = G_22x22[i][j];  
//            #ifdef debug_hires_G
//                data16_2_dec_ascii_print(tempg[i][j]);
//                print_space();
//            #endif   
//        }   
//        #ifdef debug_hires_G
//            new_line();
//        #endif
//    }
//    #ifdef debug_hires_G
//        new_line();
//    #endif
//
///*7.3) Y interpolation of G*/
//    G_22x22_ptr = &tempg[0][0]; //dikkat edelim pointer burada tempi'ye ayarlandi
//    interp_y_8(G_22x22_ptr);
//    #ifdef debug_hires_G
//    outString("G Values [X interpolation-transposed-Y interpolation ] \n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(tempi[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((tempg[i][j])>>8);
//                    send_uart2_8(tempg[i][j]);
//                #endif
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//
///*7.4) Re-transpose of G*/
//    /*Transpose temp[22][22]*/  
//    #ifdef debug_hires_G
//    outString("Final G Values\n");
//    #endif
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            G_22x22[j][i] = tempg[i][j];   
//            #ifdef debug_hires_G
//                data16_2_dec_ascii_print(G_22x22[i][j]);
//                #ifdef debug_2_python
//                    send_uart2_8((G_22x22[i][j])>>8);
//                    send_uart2_8(G_22x22[i][j]);
//                #endif
//                print_space();
//            #endif
//        }       
//        #ifdef debug_hires_G
//            new_line();
//        #endif
//    } 
//    #ifdef debug_hires_G
//        new_line();
//    #endif
/******************************************************************************************************************************/
/*8-)*************************interpolation of B_22x22*****************************/
        
/*8.1)X interpolation of B*/
#ifdef debug_hires_B
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(B_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
    interp_x_8(B_22x22_ptr);
    interp_YY_8(B_22x22_ptr);
#ifdef debug_hires_B
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(B_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
/*****ESKI KOD*****************************************************************************************************************/
//    #ifdef debug_hires_B
//    outString("B values [X-interpolation]\n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(B_22x22[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((B_22x22[i][j])>>8);
//                    send_uart2_8(B_22x22[i][j]);
//                #endif
//                /**************************************************************************/
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//
///*8.2)Transpose of B*/  
//    #ifdef debug_hires_B
//        outString("B Values [X interpolated-transposed]\n");
//    #endif  
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            tempb[j][i] = B_22x22[i][j];  
//            #ifdef debug_hires_B
//                data16_2_dec_ascii_print(tempb[i][j]);
//                print_space();
//            #endif   
//        }  
//        #ifdef debug_hires_B
//            new_line();
//        #endif
//    } 
//    #ifdef debug_hires_B
//        new_line();
//    #endif
//
///*8.3) Y interpolation of B*/
//    B_22x22_ptr = &tempb[0][0]; //dikkat edelim pointer burada tempi'ye ayarlandi
//    interp_y_8(B_22x22_ptr);
//    #ifdef debug_hires_B
//    outString("B Values [X interpolation-transposed-Y interpolation ] \n");
//        for (i=0;i<22;i++)
//        {
//            for(j=0;j<22;j++)
//            {
//                data16_2_dec_ascii_print(tempi[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((tempb[i][j])>>8);
//                    send_uart2_8(tempb[i][j]);
//                #endif
//            }
//            new_line();
//        }
//    new_line();
//    #endif
//    
///*8.4) Re-Transpose of B*/   
//    #ifdef debug_hires_B
//    outString("Final B Values\n");
//    #endif
//    for(i=0;i<22;i++)
//    {                                              
//        for(j=0;j<22;j++)
//        {                                          
//            B_22x22[j][i] = tempb[i][j];  
//            #ifdef debug_hires_B
//                data16_2_dec_ascii_print(B_22x22[i][j]);
//                print_space();
//                #ifdef debug_2_python
//                    send_uart2_8((B_22x22[i][j])>>8);
//                    send_uart2_8(B_22x22[i][j]);
//                #endif
//            #endif
//        }        
//        #ifdef debug_hires_B
//            new_line();
//        #endif
//    } 
//    #ifdef debug_hires_B
//        new_line();
//    #endif
/******************************************************************************************************************************/
/*9-)************************final my22x22*****************************************/    
    
    /*For each point in the hi_res matrix we take corresponding R , G and B values 
     from their arrays. And produce combined RGB565 values from them.*/
#ifdef debug_hires_final
    outString("Final my22x22 Values\n");
    #endif
    for(i=0;i<22;i++)
    {                                              
        for(j=0;j<22;j++)
        {                                          
            my22x22[i][j] = Color565(R_22x22[i][j],G_22x22[i][j],B_22x22[i][j]);   
#ifdef debug_hires_final
                data16_2_dec_ascii_print(my22x22[i][j]);
                print_space();
                #ifdef debug_2_python
                    send_uart2_8((my22x22[i][j])>>8);
                    send_uart2_8(my22x22[i][j]);
                #endif
            #endif
        } 
#ifdef debug_hires_final
            new_line();
        #endif
    } 
#ifdef debug_hires_final
        new_line();
    #endif

/*10-)*********************send hires data to the lcd*******************************/
    #define send_to_display
    #ifdef send_to_display
//    w = 4;
//    h = 4;
//    cell_start_x=25;
//    cell_start_y=15;
    w = 8;
    h = 8;
    cell_start_x=50;
    cell_start_y=30;
    cell_x = cell_start_x;
    cell_y = cell_start_y;
    for(i=0;i<22;i++)
        {
        for(j=0;j<22;j++)
            {
                color = my22x22[i][j];
                fillRect(cell_x,cell_y,w,h,color);
                cell_x+=w;
            }
            cell_x=cell_start_x;
            cell_y=cell_start_y+(i+1)*h;                    
        }
    #endif
    //#define send_to_python
    #ifdef send_to_python
    for(i=0;i<22;i++)
        {
        for(j=0;j<22;j++)
            {
                send_uart2_8((my22x22[i][j])>>8);   //python
                send_uart2_8(my22x22[i][j]);        //python
            }                
        }
    #endif


}
void print_hires_pixel_tft_v2(void){
    /*MOTIVATION-IDEA*/
    /*
     * print_hires_pixel_tft_v1'de once 64 adet termal sensor verisinin R-G-B degerleri uretiliyor
     * sonra bu R-G-B degerlerinde sparse matrisler olusutulup sonra da sparse matrislerde 
     * interpolasyon aypiliyordu. 
     * print_hires_pixel_tft_v2'de ise 64 adet termal sensor verisinden sparse matris olusuturuluyor.
     * sparse matriste interpolasyon uygulanarak ara sicaklik verileri hesaplaniyor.
     * Akabinde ise herbir sicaklik verisine dair R-G-B verileri hesaplaniyor. 
     * 
     * 1-)8x8 = 64 adet sensor verisi alinacak
     * 2-) 64 sensor verisi 22x22 boyutlarinda matrise dizilecek. Bu matris sparse
     * matris olacak. Ve ilk 2 satiri ornek olarak asagidaki gibi olacak
     * 
     * S1  0  0  S2   0  0  S3  0  0  S4   0  0  S5   0  0  S6   0   0  S7   0   0   S8
     * S9  0  0  S10  0  0  S11 0  0  S12  0  0  S13  0  0  S14  0   0  S15  0   0   S16
     * 
     * 3-) interpolasyon yapilarak sparse matris doldurulacak
     * 4-) 22x22 matrisin her bir hucresindeki sicaklik degeri icin RGB degerleri bulunacak
     * 5-) combined RGB degerleri bulunarak displaye yollanacak.
     */
    uint16_t color;
    uint16_t pixelbuffer[64], *pixelbuffer_ptr,*sparse_22x22_ptr,*temp_sparse_22x22_ptr;
    uint8_t *R_G_B_ptr,*temp_R_G_B_ptr,*R_22x22_ptr,*G_22x22_ptr,*B_22x22_ptr,*RR_GG_BB_ptr;
    int i,j,cell_start_x,cell_start_y,cell_x,cell_y,h,w;

/*1-)************fill pixelbuffer[64] with thermal sensor outputs*******************/    
    readPixels(pixelbuffer);
    #ifdef debug_hiresV2_pixelbuffer
        outString("Real pixel values\n");
        for (i=0;i<64;i++)
        {
            data16_2_dec_ascii_print(pixelbuffer[i]);
            if(((i+1)%8==0)){new_line();}
        }
    new_line();
    #endif

/*2-)*************************create 22x22 with sparse values *******************/
    pixelbuffer_ptr = &pixelbuffer[0];
    sparse_22x22_ptr=make22x22(pixelbuffer_ptr);
    temp_sparse_22x22_ptr = sparse_22x22_ptr;
    #ifdef debug_hiresV2_sparse
    outString("22x22_sparse Values\n");
        for (i=0;i<22;i++)
        {
            for(j=0;j<22;j++)
            {
                data16_2_dec_ascii_print(my22x22[i][j]);
                print_space();
                #ifdef debug_2_python
                    send_uart2_8((my22x22[i][j])>>8);
                    send_uart2_8(my22x22[i][j]);
                #endif

            }
            new_line();
        }
    new_line();
    #endif

/*3-)************************interpolation of my22x22**************************/
    
#ifdef debug_hires_R

    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(R_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
    interp_x_16(sparse_22x22_ptr);
    sparse_22x22_ptr = temp_sparse_22x22_ptr;
    interp_YY_16(sparse_22x22_ptr);
#ifdef debug_hires_R
    for (i=0;i<22;i++){
        for (j=0;j<22;j++){
            data16_2_dec_ascii_print(R_22x22[i][j]);
            print_space();
        }
        new_line();
    }
    new_line();
#endif
    
/*4-) my22x22'den RGB value'lar uretilecek*/
    sparse_22x22_ptr = temp_sparse_22x22_ptr;
    RR_GG_BB_ptr = get_RR_GG_BB_of_pixel(sparse_22x22_ptr);
    
/*5-)************************final my22x22*****************************************/    
    
    /*For each point in the hi_res matrix we take corresponding R , G and B values 
     from their arrays. And produce combined RGB565 values from them.*/
#ifdef debug_hires_final
    outString("Final my22x22 Values\n");
    #endif
    for(i=0;i<22;i++)
    {                                              
        for(j=0;j<22;j++)
        {                                          
            final_my22x22[i][j] = Color565(RR_GG_BB[i][j][0],RR_GG_BB[i][j][1],RR_GG_BB[i][j][2]);   
#ifdef debug_hires_final
                data16_2_dec_ascii_print(my22x22[i][j]);
                print_space();
                #ifdef debug_2_python
                    send_uart2_8((my22x22[i][j])>>8);
                    send_uart2_8(my22x22[i][j]);
                #endif
            #endif
        } 
#ifdef debug_hires_final
            new_line();
        #endif
    } 
#ifdef debug_hires_final
        new_line();
    #endif

/*10-)*********************send hires data to the lcd*******************************/
    #define send_to_display
    #ifdef send_to_display
//    w = 4;
//    h = 4;
//    cell_start_x=25;
//    cell_start_y=15;
    w = 8;
    h = 8;
    cell_start_x=50;
    cell_start_y=30;
    cell_x = cell_start_x;
    cell_y = cell_start_y;
    for(i=0;i<22;i++)
        {
        for(j=0;j<22;j++)
            {
                color = final_my22x22[i][j];
                fillRect(cell_x,cell_y,w,h,color);
                cell_x+=w;
            }
            cell_x=cell_start_x;
            cell_y=cell_start_y+(i+1)*h;                    
        }
    #endif
    //#define send_to_python
    #ifdef send_to_python
    for(i=0;i<22;i++)
        {
        for(j=0;j<22;j++)
            {
                send_uart2_8((my22x22[i][j])>>8);   //python
                send_uart2_8(my22x22[i][j]);        //python
            }                
        }
    #endif


}
/*************************************************************************/
/*************************************************************************/
void set_colorBar (void){
    int R,G,B;
    uint8_t x,y;
    uint8_t w,h;
    float coef;
    x = 2;
    w = 25;
    h = 1;  
    /*1st attempt*/
    /*1st RGB REGION: (255,0,0)->(255,255,0)*/
//    R = 0; G = 0; B = 240; 
//    R = 0; G = 0; B = 240; 
    R = 255; G = 0; B = 0; 
    coef = 255/60;
    for (y=30;y<90;y+=1){
        fillRect(x,y,w,h,Color565(R,G,B));
        G+=coef;
    }
//    /*2nd RGB REGION: (255,255,0)->(0,255,0)*/
//    R = 255; G = 255; B = 0; 
//    coef = 255/60;
//    for (y=60;y<120;y++){
//        fillRect(x,y,w,h,Color565(R,G,B));
//        R-=(coef);
//    }                        
//    /*3rd RGB REGION: (0,255,0)->(0,255,255)*/
//    R = 0; G = 255; B = 0;
//    coef = 255/60;
//    for (y=120;y<180;y++){
//        fillRect(x,y,w,h,Color565(R,G,B));
//        B+=(coef);
//    }     
    /*2nd + 3rd RGB REGION: (255,255,0)->(0,255,255)*/
    R = 255; G = 255; B = 0; 
    coef = 255/60;
    for (y=90;y<150;y++){
        fillRect(x,y,w,h,Color565(R,G,B));
        R-=(coef);
        B+=(coef);
    }   
    /*4th RGB REGION: (0,255,255)->(0,0,255)*/
    R = 0; G = 255; B = 255; 
    coef = 255/60;
    for (y=150;y<210;y++){
        fillRect(x,y,w,h,Color565(R,G,B));
        G-=coef;
    }   
//    /*4th RGB REGION: (0,255,255)->(0,0,255)*/
//    R = 0; G = 255; B = 255; 
//    coef = 255/60;
//    for (y=180;y<240;y++){
//        fillRect(x,y,w,h,Color565(R,G,B));
//        G-=coef;
//    }   
}
