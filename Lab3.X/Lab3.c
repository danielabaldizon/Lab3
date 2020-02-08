/* 
 * File:   Lab3.c
 * Author: Daniela Baldizon
 *
 * Created on 4 de febrero de 2020, 10:28 PM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "LCD.h"
#include "ADC.h"
//
#define _XTAL_FREQ 4000000

#define RS RC1 //DEFINIR VARIABLES MÁS SENCILLAS PARA LOS PINES
#define EN RC0
#define D0 RA0
#define D1 RA1
#define D2 RA2
#define D3 RA3
#define D4 RA4
#define D5 RA5
#define D6 RA6
#define D7 RA7
#define P1 RD0
#define P2 RD1

uint8_t adc1 = 0;
uint8_t adc2 = 0;
uint8_t ctrl = 0;
uint8_t ctrl2 = 0;
float adc11;
float adc22;


void main(void){
    unsigned int a;
    ANSELH = 0;
    ANSEL = 0;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    
    //ADC
    ADC_CONFIG(12,0); //CANAL 12 JUSTIFIACION A LA IZQUIERDA
    ADC_CONFIG(10,0); //CANAL 10 JUSTIFICACION A LA IZQUIERDA
    
    Lcd_Init();
    
    // VARIABLES
    char s1[7];
    char s2[7];
    
    
    
    while(1){
        ADCON0bits.CHS = 10;    //CANAL 10
        __delay_us(500);
        ADCON0bits.GO = 1;      //INICIA EL ADC
        while(ADCON0bits.GO == 1){};
        adc1 = ADRESH;
        adc11 = adc1/51.0;
        PIR1bits.ADIF = 0;
        ADCON0bits.CHS = 12;    //CANAL 12
        __delay_us(500);
        ADCON0bits.GO = 1;      //INICIA EL ADC
        while(ADCON0bits.GO == 1){};
        adc2 = ADRESH;
        adc22 = adc2/51.0;
        PIR1bits.ADIF = 0;
        Lcd_Clear();
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("P1:");
        Lcd_Set_Cursor(1,7);
        Lcd_Write_String("P2:");
        Lcd_Set_Cursor(1,12);
        Lcd_Write_String("P3:");
        sprintf(s1,"%.2f",adc11);
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(s1);
        sprintf(s2,"%.2f",adc22);
        Lcd_Set_Cursor(2,6);
        Lcd_Write_String(s2);
        __delay_ms(2000);
    }
     
}