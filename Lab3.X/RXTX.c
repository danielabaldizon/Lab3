/* 
 * File:   RXTX.c
 * Author: Daniela Baldizon
 *
 * Created on 8 de febrero de 2020, 02:56 PM
 */

#include <stdint.h>
#include <stdlib.h>
#include "RXTX.h"
#include <pic16f887.h>
#define _XTAL_FREQ 4000000

char UART_Init(const long int baudrate) //TOMADO DE ELECTROSOME https://electrosome.com/uart-pic-microcontroller-mplab-xc8/
{
  unsigned int x;
  x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);   //SPBRG for Low Baud Rate
  if(x>255)                                       //If High Baud Rage Required
  {
    x = (_XTAL_FREQ - baudrate*16)/(baudrate*16); //SPBRG for High Baud Rate
    BRGH = 1;                                     //Setting High Baud Rate
  }
  if(x<256)
  {
    SPBRG = x;                                    //Writing SPBRG Register
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port
    TRISC7 = 1;                                   //As Prescribed in Datasheet
    TRISC6 = 1;                                   //As Prescribed in Datasheet
    CREN = 1;                                     //Enables Continuous Reception
    TXEN = 1;                                     //Enables Transmission
    return 1;                                     //Returns 1 to indicate Successful Completion
  }
  return 0;                                       //Returns 0 to indicate UART initialization failed
}

void UART_Write(char data)
{
  while(!TRMT);
  TXREG = data;
  __delay_ms(100);
}

char UART_TX_Empty()
{
  return TRMT;
}

char UART_Data_Ready()
{
  return RCIF;
}

char UART_Read()
{
    return RCREG;
  while(!RCIF);
 // return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length)
{
  unsigned int i;
  for(int i=0;i<length;i++)
  Output[i] = UART_Read();
}