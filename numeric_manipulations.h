#ifndef NUMERIC_MANIPILATIONS_H
#define NUMERIC_MANIPILATIONS_H


#include <stdint.h>
uint8_t *data8_2_ascii(uint8_t dec);
uint8_t * data16_2_ascii(uint16_t data);
uint8_t * CR_532 (uint16_t *buf);
uint8_t * data16_2_dec_ascii(uint16_t);
void data16_2_dec_ascii_print(uint16_t dec);


#endif
