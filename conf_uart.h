//mylibraries
/**********************************************/
/**********************************************/
/**********************************************/
/*DEFINE THE APPROPRIATES THE PROJECT SPECIFIC*/
/* #define _UART1
 * #define UART1_TXPOLL_RXINT
 * #define UART1_TXPOLL_RXPOLL
 * #define UART1_TXINT_RXINT
 * #define _UART2
 * #define UART2_TXPOLL_RXINT
 * #define UART2_TXINT_RXINT
 * #define _UART3 3
 * #define _UART4 4
 * #define UART_VER_2
 */
/**********************************************/
/**********************************************/
/**********************************************/



#ifndef CONF_UART_H
#define	CONF_UART_H


#include "../my_headers/header_definition.h"
#include "../../my_libraries/my_headers/conf_clock.h"
#include <stdbool.h>

#define project_includes
#ifdef  project_includes
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
    #ifdef dspic33E_ADC
    #include "../../dspic33E_ADC.X/project_specific.h"
    #endif
    #ifdef my_OV7670
    #include "../../my_OV7670.X/project_specific.h"
    #endif
    #ifdef _93C46_eprom
    #include "../../_93C46_eprom.X/project_specific.h"
    #endif
#endif




#define LINE_FEED 0x0A
#define UART1_MODULE_ENABLE (U1MODEbits.UARTEN = 1)
#define UART1_TRANSMIT_ENABLE (U1STAbits.UTXEN = 1)
#define UART2_MODULE_ENABLE (U2MODEbits.UARTEN = 1)
#define UART2_TRANSMIT_ENABLE (U2STAbits.UTXEN = 1)
#define TRANSMIT_NOT_READY() (!U1STAbits.TRMT)
#define TRANSMIT_NOT_READY_uart2() (!U2STAbits.TRMT)
//#define TRANSMIT_NOT_READY() (!U1STAbits.TRMT ||U1STAbits.UTXBF)
//U1STAbits.TRMT = 0 --> TransmitShiftRegister is not empty a transmission is in progress or queued in transmitbuffer
//U1STAbits.UTXBF = 1 --> Transmitbuffer is full
#define IS_CHAR_READY_UART1() U1STAbits.URXDA
#define IS_CHAR_READY_UART2() U2STAbits.URXDA
#define MESSAGE1 "KEMAL KAYA IYI GUNLER DILER\n"
#define MESSAGE2 "\n GORUNTU ISLEME YAZILIMI \n"

#ifndef UART_VER_2
    void configure_uart(void);
    void send_uart_8(uint8_t send_data);
    void send_data_MPLABVis(uint8_t data);
    void outString_to_MPLABVis (const char* message);
    void outString (const char* message);
    uint8_t inChar(void);
    void send_float_MPLABVis(float data);
    void print_8x8_table_MPLABVis(uint8_t *ptr);
    void print_space(void);
    void new_line(void);
    uint8_t test_uart(void);
    //#define BRGH_VALUE_HIGH  --> placed in project_specific.h
    //#define BAUDRATE 9600 --> placed in project_specific.h
    #ifdef BRGH_VALUE_HIGH
        #define BRGVAL1 ((FCY/BAUDRATE1)/4)-1 //BRGH = 1
        #define BRGVAL2 ((FCY/BAUDRATE2)/4)-1 //BRGH = 1
    #endif
    #ifdef BRGH_VALUE_LOW
        #define BRGVAL1 ((FCY/BAUDRATE1)/16)-1 //BRGH = 0
        #define BRGVAL2 ((FCY/BAUDRATE2)/16)-1 //BRGH = 0
    #endif
#endif
#ifdef  UART_VER_2
    #define DEFAULT 0
    #define TX_Interrupt 5
    #define RX_Interrupt 6
    #define Interrupt_Flag_Poll 6
    #define Control_Register_Bit_Poll 7
    #define BRG_HI 8
    #define BRG_LO 9
    #define STOPBIT_ONE 10
    #define STOPBIT_TWO 11
    #define _9BIT_NOPAR 12
    #define _8BIT_ODDPAR 13 
    #define _8BIT_EVENPAR 14 
    #define _8BIT_NOPAR 15

    #define TX_INT_MODE_2 16 // Transmit buffer tamamiyle bosaldiginda interrupt olussun 
                             // (TSR icinde gonderilmekte olan data olabilir)
    #define TX_INT_MODE_1 17 // Tum transmit islemleri tamamlandiginde interrupt olussun
                             // 
    #define TX_INT_MODE_0 18 // Transmit bufferda en az 1 yer bos oldugunda interrupt olussun
                             // 1 deep transmit fifo. 
                             // Interrupt after one TX character is transmitted
    
    #define RX_INT_MODE_3 19 // Receive bufferda 4 tane veri oldugunda interrupt olussun
    #define RX_INT_MODE_2 20 // Receive bufferda 3 veya daha fazla sayida veri oldu?unda int. olussun
    #define RX_INT_MODE_0 21 //Receive bufferda 1 veya daha fazla sayida veri oldugunda int. olussun




    
    static uint8_t mybyte;

#ifdef _UART1
typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}DRV_UART_BYTEQ_STATUS;
typedef struct
{
    /* RX Byte Q */
    uint8_t                                      *rxTail ;

    uint8_t                                      *rxHead ;

    /* TX Byte Q */
    uint8_t                                      *txTail ;

    uint8_t                                      *txHead ;

    DRV_UART_BYTEQ_STATUS                        rxStatus ;

    DRV_UART_BYTEQ_STATUS                        txStatus ;

} DRV_UART_OBJECT ;
typedef enum
{
/* Indicates that Receive buffer has data, at least one more character can be read */
DRV_UART1_RX_DATA_AVAILABLE
    /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

/* Indicates that Receive buffer has overflowed */
DRV_UART1_RX_OVERRUN_ERROR
    /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

/* Indicates that Framing error has been detected for the current character */
DRV_UART1_FRAMING_ERROR
    /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

/* Indicates that Parity error has been detected for the current character */
DRV_UART1_PARITY_ERROR
    /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

/* Indicates that Receiver is Idle */
DRV_UART1_RECEIVER_IDLE
    /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

/* Indicates that the last transmission has completed */
DRV_UART1_TX_COMPLETE
    /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

/* Indicates that Transmit buffer is full */
DRV_UART1_TX_FULL
    /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

}DRV_UART1_STATUS;
typedef enum
{
/* Indicates that the core driver buffer is full */
DRV_UART1_TRANSFER_STATUS_RX_FULL
    /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

/* Indicates that at least one byte of Data has been received */
DRV_UART1_TRANSFER_STATUS_RX_DATA_PRESENT
    /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

/* Indicates that the core driver receiver buffer is empty */
DRV_UART1_TRANSFER_STATUS_RX_EMPTY
    /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

/* Indicates that the core driver transmitter buffer is full */
DRV_UART1_TRANSFER_STATUS_TX_FULL
    /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

/* Indicates that the core driver transmitter buffer is empty */
DRV_UART1_TRANSFER_STATUS_TX_EMPTY
    /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

} DRV_UART1_TRANSFER_STATUS;


    
#ifndef DRV_UART1_CONFIG_TX_BYTEQ_LENGTH
        #define DRV_UART1_CONFIG_TX_BYTEQ_LENGTH 4
#endif
#ifndef DRV_UART1_CONFIG_RX_BYTEQ_LENGTH
        #define DRV_UART1_CONFIG_RX_BYTEQ_LENGTH 4
#endif

#define DRV_UART1_TX_FIFO_LENGTH 4 //hardware fifo length
#define DRV_UART1_RX_FIFO_LENGTH 4 //hardware fifo length

static uint8_t uart1_txByteQ[DRV_UART1_CONFIG_TX_BYTEQ_LENGTH] ;
static uint8_t uart1_rxByteQ[DRV_UART1_CONFIG_RX_BYTEQ_LENGTH] ; 
#endif
#ifdef _UART2
        typedef enum
        {
            /* Indicates that Receive buffer has data, at least one more character can be read */
            DRV_UART2_RX_DATA_AVAILABLE
                /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

            /* Indicates that Receive buffer has overflowed */
            DRV_UART2_RX_OVERRUN_ERROR
                /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

            /* Indicates that Framing error has been detected for the current character */
            DRV_UART2_FRAMING_ERROR
                /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

            /* Indicates that Parity error has been detected for the current character */
            DRV_UART2_PARITY_ERROR
                /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

            /* Indicates that Receiver is Idle */
            DRV_UART2_RECEIVER_IDLE
                /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

            /* Indicates that the last transmission has completed */
            DRV_UART2_TX_COMPLETE
                /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

            /* Indicates that Transmit buffer is full */
            DRV_UART2_TX_FULL
                /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

        }DRV_UART2_STATUS;
        typedef enum
        {
            /* Indicates that the core driver buffer is full */
            DRV_UART2_TRANSFER_STATUS_RX_FULL
                /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

            /* Indicates that at least one byte of Data has been received */
            DRV_UART2_TRANSFER_STATUS_RX_DATA_PRESENT
                /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

            /* Indicates that the core driver receiver buffer is empty */
            DRV_UART2_TRANSFER_STATUS_RX_EMPTY
                /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

            /* Indicates that the core driver transmitter buffer is full */
            DRV_UART2_TRANSFER_STATUS_TX_FULL
                /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

            /* Indicates that the core driver transmitter buffer is empty */
            DRV_UART2_TRANSFER_STATUS_TX_EMPTY
                /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

        } DRV_UART2_TRANSFER_STATUS;      
#endif
#if defined (_UART1)& defined (UART1_TXINT_RXINT)
        void configure_dspic33_UART1(uint8_t brghilo0,\
                                        unsigned long baudrate0, uint8_t stopbit0,\
                                        uint8_t paritydata0,\
                                        uint8_t txintmode0, uint8_t rxintmode0);
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void );
        void DRV_UART1_TasksTX ( void );
        void DRV_UART1_TasksRX ( void );
        void DRV_UART1_TasksError ( void );
        void DRV_UART1_WriteByte(const uint8_t byte);
        uint8_t DRV_UART1_ReadByte( void);
        unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes);
        unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes );
        DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void );
        uint8_t DRV_UART1_Peek(uint16_t offset);
        unsigned int DRV_UART1_RXBufferSizeGet(void);
        unsigned int DRV_UART1_TXBufferSizeGet(void);
        bool DRV_UART1_RXBufferIsEmpty (void);
        bool DRV_UART1_TXBufferIsFull (void);
        DRV_UART1_STATUS DRV_UART1_Status (void );
    #endif
#if defined (_UART1)& defined (UART1_TXPOLL_RXINT)
        void configure_dspic33_UART1(uint8_t brghilo0,\
                                        unsigned long baudrate0, uint8_t stopbit0,\
                                        uint8_t paritydata0,\
                                        uint8_t txintmode0, uint8_t rxintmode0);
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void );
        void DRV_UART1_TasksTX ( void );
        void DRV_UART1_TasksRX ( void );
        void DRV_UART1_TasksError ( void );
        void DRV_UART1_WriteByte(const uint8_t byte);
        uint8_t DRV_UART1_ReadByte( void);
        unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes);
        unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes );
        DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void );
        uint8_t DRV_UART1_Peek(uint16_t offset);
        unsigned int DRV_UART1_RXBufferSizeGet(void);
        unsigned int DRV_UART1_TXBufferSizeGet(void);
        bool DRV_UART1_RXBufferIsEmpty (void);
        bool DRV_UART1_TXBufferIsFull (void);
        DRV_UART1_STATUS DRV_UART1_Status (void );
    #endif
#if defined (_UART1)& defined (UART1_TXPOLL_RXPOLL)
        void configure_dspic33_UART1(uint8_t brghilo0,\
                                        unsigned long baudrate0, uint8_t stopbit0,\
                                        uint8_t paritydata0,\
                                        uint8_t txintmode0, uint8_t rxintmode0);
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt ( void );
        void DRV_UART1_TasksTX ( void );
        void DRV_UART1_TasksRX ( void );
        void DRV_UART1_TasksError ( void );
        void DRV_UART1_WriteByte(const uint8_t byte);
        uint8_t DRV_UART1_ReadByte( void);
        unsigned int DRV_UART1_Read( uint8_t *buffer ,  const unsigned int numbytes);
        unsigned int DRV_UART1_Write( const uint8_t *buffer , const unsigned int numbytes );
        DRV_UART1_TRANSFER_STATUS DRV_UART1_TransferStatus (void );
        uint8_t DRV_UART1_Peek(uint16_t offset);
        unsigned int DRV_UART1_RXBufferSizeGet(void);
        unsigned int DRV_UART1_TXBufferSizeGet(void);
        bool DRV_UART1_RXBufferIsEmpty (void);
        bool DRV_UART1_TXBufferIsFull (void);
        bool DRV_UART1_RXBufferIsFull (void);
        bool DRV_UART1_TXBufferIsEmpty (void);
        DRV_UART1_STATUS DRV_UART1_Status (void );
    #endif
#if defined (_UART2)& defined (UART2_TXINT_RXINT)
        void configure_dspic33_UART2(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0);
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2TXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2RXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2ErrInterrupt ( void );
        void DRV_UART2_TasksTX ( void );
        void DRV_UART2_TasksRX ( void );
        void DRV_UART2_TasksError ( void );
        void DRV_UART2_WriteByte(const uint8_t byte);
        uint8_t DRV_UART2_ReadByte( void);
        unsigned int DRV_UART2_Read( uint8_t *buffer ,  const unsigned int numbytes);
        unsigned int DRV_UART2_Write( const uint8_t *buffer , const unsigned int numbytes );
        DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void );
        uint8_t DRV_UART2_Peek(uint16_t offset);
        unsigned int DRV_UART2_RXBufferSizeGet(void);
        unsigned int DRV_UART2_TXBufferSizeGet(void);
        bool DRV_UART2_RXBufferIsEmpty (void);
        bool DRV_UART2_TXBufferIsFull (void);
        DRV_UART2_STATUS DRV_UART2_Status (void );
    #endif
#if defined (_UART2)& defined (UART2_TXPOLL_RXINT)
        void configure_dspic33_UART2(uint8_t brghilo0,\
                                    unsigned long baudrate0, uint8_t stopbit0,\
                                    uint8_t paritydata0,\
                                    uint8_t txintmode0, uint8_t rxintmode0);
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2TXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2RXInterrupt ( void );
        void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2ErrInterrupt ( void );
        void DRV_UART2_TasksTX ( void );
        void DRV_UART2_TasksRX ( void );
        void DRV_UART2_TasksError ( void );
        void DRV_UART2_WriteByte(const uint8_t byte);
        uint8_t DRV_UART2_ReadByte( void);
        unsigned int DRV_UART2_Read( uint8_t *buffer ,  const unsigned int numbytes);
        unsigned int DRV_UART2_Write( const uint8_t *buffer , const unsigned int numbytes );
        DRV_UART2_TRANSFER_STATUS DRV_UART2_TransferStatus (void );
        uint8_t DRV_UART2_Peek(uint16_t offset);
        unsigned int DRV_UART2_RXBufferSizeGet(void);
        unsigned int DRV_UART2_TXBufferSizeGet(void);
        bool DRV_UART2_RXBufferIsEmpty (void);
        bool DRV_UART2_TXBufferIsFull (void);
        DRV_UART2_STATUS DRV_UART2_Status (void );
    #endif

#endif /*#ifdef UART_VER_2*/

#endif/*#ifndef CONF_UART_H*/
