/* 
 * File:   RXTX.h
 * Author: Daniela Baldizon
 *
 * Created on 8 de febrero de 2020, 02:56 PM
 */

#ifndef RXTX_H
#define	RXTX_H
#include <stdint.h>
#include <xc.h>

char UART_Init(const long int baudrate);
void UART_Write(char data);
char UART_TX_Empty();

#endif	/* RXTX_H */

