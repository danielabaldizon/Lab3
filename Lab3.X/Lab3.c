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
#include "RXTX.h"
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
char int_stre(float n);
char int_strd(float n);
char int_strc(float n);
char num_case(uint8_t num);


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
    UART_Init(9600);
    
    // VARIABLES
    char s1[5] = "";
    char s2[5] = "";
    
    
    
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
        
        /////
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("P1:");
        Lcd_Set_Cursor(1,7);
        Lcd_Write_String("P2:");
        Lcd_Set_Cursor(1,12);
        Lcd_Write_String("P3:");
        Lcd_Set_Cursor(2,1);
        s1[0] = int_stre(adc11);
        s1[1]='.';
        s1[2] = int_strd(adc11);
        s1[3] = int_strc(adc11);
        Lcd_Write_String(s1);
        Lcd_Set_Cursor(2,6);
        s2[0] = int_stre(adc22);
        s2[1]='.';
        s2[2] = int_strd(adc22);
        s2[3] = int_strc(adc22);
        Lcd_Write_String(s2);
        __delay_ms(2000);
        
        ///
        UART_Write(adc11);
        UART_Write(adc2);
    }
     
}
char int_stre(float n){
    uint8_t e;
    uint8_t d;
    uint8_t c;
    uint8_t loca;
    char c1;
    char c2;
    char c3;
    
    e = n;
    c1 = num_case(e);
    loca = (n - e)*10;
    d = loca;
    c2 = num_case(d);
    loca = (loca-d)*10;
    c = loca;
    c3 = num_case(c);
    return c1;
}

char int_strd(float n){
    uint8_t e;
    uint8_t d;
    uint8_t c;
    uint8_t loca;
    char c1;
    char c2;
    char c3;
    
    e = n;
    c1 = num_case(e);
    loca = (n - e)*10;
    d = loca;
    c2 = num_case(d);
    loca = (loca-d)*10;
    c = loca;
    c3 = num_case(c);
    return c2;
}
char int_strc(float n){
    uint8_t e;
    uint8_t d;
    uint8_t c;
    float loca;
    char c1;
    char c2;
    char c3;
    
    e = n;
    c1 = num_case(e);
    loca = (n - e)*10;
    d = loca;
    c2 = num_case(d);
    loca = (loca-d)*10;
    c = loca;
    c3 = num_case(c);
    return c3;
}

char num_case(uint8_t num){
    char r;
    switch(num){
        case 0:
            r = '0';
            break;
        case 1:
            r = '1';
            break;
        case 2:
            r = '2';
            break;
        case 3:
            r = '3';
            break;
        case 4:
            r = '4';
            break;
        case 5:
            r = '5';
            break;
        case 6:
            r = '6';
            break;
        case 7:
            r = '7';
            break;
        case 8:
            r = '8';
            break;
        case 9:
            r = '9';
            break;
    }
    return r;
}
