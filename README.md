# IR_camera_AMG8833
In this project I acquire 8x8 data from AMG8833 through I2C communication. 
Then with the help of 2 dimensional interpolation i increased 8x8 pixel resolution to 22x22 level. 
Then visualize that on a ST7789 LCD display.  

**main c file :** IR_cam_PIC24f.c 

**What is header_definition.h for ?**

I mainly used Microchip Explorer16/32 bit development card for my projects. And i made lots of projects and project trials with 2 different cpu types (dspic33E - PIC24F) . Instead of writing same configuration codes for peripherals repetitively I activate related parts of codes through preprocessor directives.  


![breadboard](https://user-images.githubusercontent.com/30715872/155534349-e0113c3f-cf0c-47fa-a4ec-55e7b6958651.jpg)
