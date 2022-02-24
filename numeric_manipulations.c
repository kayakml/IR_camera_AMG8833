#include "../my_headers/numeric_manipulations.h"
#include "../../my_libraries/my_headers/conf_uart.h"

uint8_t * data8_2_ascii(uint8_t dec){
    /*This function genrates decimal value of  its 8 bit argument 
     * and then convert each digit into ascii and then load those digits 
     into the mem_arr
     if dec = 126 then 
     mem_arr[2] = 6
     mem_arr[1] = 2
     mem_arr[0] = 1*/
    uint8_t temp;
    static uint8_t mem_arr[3];
    
     mem_arr[2] = (dec%10);
        temp = (dec - mem_arr[2] ) / 10;
        if (temp>=10) {
            mem_arr[1] = temp%10;
            mem_arr[0] = (temp-mem_arr[1])/10;
        } else {
            mem_arr[1] = temp;
            mem_arr[0] = 0;
        }
        
        mem_arr[0] = mem_arr[0] + 48; // hundreds
        mem_arr[1] = mem_arr[1] + 48; //tens
        mem_arr[2] = mem_arr[2] + 48; //ones
    return mem_arr;
    }
uint8_t * data16_2_dec_ascii(uint16_t dec){
    /* converts decimal value of argument then transform each digit 
     into ascii value and then store ascii values in an array
     if dec = 12345 then 
    
     mem_arr[4] = 1 
     mem_arr[3] = 2 
     mem_arr[2] = 3
     mem_arr[1] = 4
     mem_arr[0] = 5 
     
     * USAGE
        uint8_t *ptr;
        ptr = data16_2_dec_ascii(dec); 
        ptr+=4;
        send_uart_8(*ptr);
        ptr--;
        send_uart_8(*ptr);
        ptr--;
        send_uart_8(*ptr);
        ptr--;
        send_uart_8(*ptr);
        ptr--;
        send_uart_8(*ptr);     
     */
    
    
    static uint8_t mem_arr[5];

    mem_arr[4] = ((dec - (dec % 10000))/10000)+48;
    mem_arr[3] = (((dec % 10000) - ((dec % 10000) % 1000)) / 1000)+48; 
    mem_arr[2] = ((((dec % 10000) % 1000) - ((dec % 10000) % 1000)%100)/100)+48;
    mem_arr[1] = ((((dec % 10000) % 1000)%100 - (((dec % 10000) % 1000)%100)%10)/10)+48;
    mem_arr[0] = ((((dec % 10000) % 1000)%100)%10)+48;
        
    return mem_arr;}
void data16_2_dec_ascii_print(uint16_t dec){
    /* converts decimal value of argument then transform each digit 
     into ascii value and then store ascii values in an array
     if dec = 12345 then ...
    
     mem_arr[4] = 1 
     mem_arr[3] = 2 
     mem_arr[2] = 3
     mem_arr[1] = 4
     mem_arr[0] = 5 
     
     ....send each digit value to uart
     * NOTE: This code is based on   data16_2_dec_ascii function. Because this function 
     * does not have an intention of saving data i omitted mem_arr array..
     */
    
    

    send_uart_8(((dec - (dec % 10000))/10000)+48); //ten thousand digit
    send_uart_8((((dec % 10000) - ((dec % 10000) % 1000)) / 1000)+48);//thousand digit
    send_uart_8(((((dec % 10000) % 1000) - ((dec % 10000) % 1000)%100)/100)+48);//hundred digit
    send_uart_8(((((dec % 10000) % 1000)%100 - (((dec % 10000) % 1000)%100)%10)/10)+48);//tens digit
    send_uart_8(((((dec % 10000) % 1000)%100)%10)+48);//ones digit
    outString(" ");
}
uint8_t * data16_2_ascii(uint16_t data){
    /*This function takes uint16_t variable as argument and convert each 4 digit of hex value into the ascii equivalent
     and loads those equivalents into ascii_array and returns address of that array
     if data = 0x68C5 then
     ascii_array[3] = 6+48
     ascii_array[2] = 8+48
     ascii_array[1] = 12+55
     ascii_array[0] = 5+48
     */
    unsigned char i; 
    static uint8_t ascii_array[4];
    uint16_t temp;
    for (i=0;i<4;i++){
        temp = (data>>(i*4) & 0x000F);
        if (temp>=0 && temp<=9){
            ascii_array[i] = 48 + temp;
        }
        else if (temp>=10 && temp<=15){
            ascii_array[i] = 55 + temp;
        }
    }
    return ascii_array;
}
uint8_t * CR_532 (uint16_t *buf){
    // CR
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
