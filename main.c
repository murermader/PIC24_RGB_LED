/*
 * File:   newMainFile.c
 * Author: luisj
 *
 * Created on 15. Oktober 2019, 15:33
 */


#include <xc.h>
#include <stdio.h>
#include <stdbool.h>

#define FCY 1600000UL // Wird benötigt, damit __delay_ms() funktioniert.
//#define _XTAL_FREQ 4000000
#include <libpic30.h>

#define port_POT1 




void main(void) {
    
    
    TRISAbits.TRISA0 = 0;

    TRISAbits.TRISA1 = 0;

    TRISCbits.TRISC7 = 0;
    
    TRISBbits.TRISB12 = 0;
   

    Nop();

    

    int rW, rD, gW, gD, bW, bD;
    
   

    while (1){
        
        
        
        rW = 1;
        
        gW = 1;
        
        bW = 1;
        
        int j;
        for (j=1;j<=255;j++){
            
            if (j>rW){

                PORTAbits.RA0 = 0; //Rot
                
            } else {
                
                PORTAbits.RA0 = 1; //Rot
            }

            if (j>gW){

                PORTAbits.RA1 = 0; //Grün
                

            } else {

                PORTAbits.RA1 = 1; //Grün

            }               

            if (j>bW){

                PORTCbits.RC7 = 0; //Blau
                

            } else {

                PORTCbits.RC7 = 1; //Blau

            }

        }


    }

   

    Nop();

    return;

}

int map_color_scheme() {
    
    
    
    
}

uint8_t ADC_ReadPercentage() {
    uint8_t percent ;

    

    //A very crude percentage calculation
    percent = ( ADC_Read10bit ( 8 ) / 10 ) ;

    if (percent > 100)
    {
        percent = 100 ;
    }
    return percent ;
}

uint16_t ADC_Read10bit () {
    uint16_t i ;

    AD1CHS = 8;

    // Get an ADC sample
    AD1CON1bits.SAMP = 1 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically

    AD1CON1bits.SAMP = 0 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically

    while (!AD1CON1bits.DONE) ;       //Wait for conversion to complete

    return ADC1BUF0 ;
}

bool ADC_ChannelEnable () {
    ANSCbits.ANSC0 = 1;
    return true ;
    }

bool ADC_SetConfiguration () {

    AD1CON2bits.PVCFG = 0x00 ;
    AD1CON2bits.NVCFG0 = 0x0 ;
    AD1CON3bits.ADCS = 0xFF ;
    AD1CON1bits.SSRC = 0x0 ;
    AD1CON3bits.SAMC = 0b10000 ;
    AD1CON1bits.FORM = 0b00 ;
    AD1CON2bits.SMPI = 0x0 ;
    AD1CON1bits.MODE12 = 0 ;
    AD1CON1bits.ADON = 1 ;

    return true ;
}
