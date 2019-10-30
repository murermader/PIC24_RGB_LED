/*
 * File:   newMainFile.c
 * Author: luisj
 *
 * Created on 15. Oktober 2019, 15:33
 */
#include <stdbool.h>



int ADC_ReadPercentage();
int ADC_Read10bit();
bool ADC_ChannelEnable();
bool ADC_SetConfiguration();
float mapping(float,float,float, bool);
int get_red(float);
int get_green(float);
int get_blue(float);
float normalize(int);


#include <xc.h>
#include <stdio.h>
#include <math.h>


#define FCY 1600000UL // Wird benötigt, damit __delay_ms() funktioniert.
//#define _XTAL_FREQ 4000000
#include <libpic30.h>

#define port_POT1 




void main(void) {
    
    uint16_t potentiometer;
    
    ADC_SetConfiguration();
    ADC_ChannelEnable();
    
    TRISAbits.TRISA0 = 0;

    TRISAbits.TRISA1 = 0;

    TRISCbits.TRISC7 = 0;
    
    TRISBbits.TRISB12 = 0;
    
    
    int rV, rD, gV, gD, bV, bD, current_color;
    
    
    
    
    

    while (1){
        
        potentiometer = ADC_Read10bit();
        
        rV = get_red(potentiometer);
        
        gV = get_green(potentiometer);
        
        bV = get_blue(potentiometer);
        
        int j;
        for (j=1;j<=255;j++){
            
            if (j>rV){

                PORTAbits.RA0 = 0; //Rot
                
            } else {
                
                PORTAbits.RA0 = 1; //Rot
            }

            if (j>gV){

                PORTAbits.RA1 = 0; //Grün
                

            } else {

                PORTAbits.RA1 = 1; //Grün

            }               

            if (j>bV){

                PORTCbits.RC7 = 0; //Blau
                

            } else {

                PORTCbits.RC7 = 1; //Blau

            }
        }
    }

   

    Nop();

    return;

}


float normalize(int poti) {
    float xOne = pow(57,4.0/5.0);
    return (float)pow(poti,1.0/5.0) * xOne;
}

float mapping(float value, float start1, float stop1, bool test) {
    int rgb_min;
    int rgb_max;
    if(test) {
        rgb_min = 0.0;
        rgb_max = 255.0;
    } else {
        rgb_min = 255.0;
        rgb_max = 0.0;
    }
    if((stop1 - start1) == 0 ) {
        return 0.0;
    } else {
        return (rgb_min + (rgb_max - rgb_min) * ((value - start1) / (stop1 - start1)));
    }
}

int get_red(float pv) {
    int red_value;
    if(pv <= 10) {
        return 255;
    } else if(pv <= 20) {
        return mapping(pv, 10, 20, false);
    } else if(pv <= 40) {
        return 0;
    } else if(pv <= 50) {
        return mapping(pv, 40, 50, true);
    } else {
        return 255;
    }
}

int get_green(float pv) {
    int green_value;
    if(pv <= 10) {
        return mapping(pv, 0, 10, true);
    } else if(pv <= 30) {
        return 50;
    } else if(pv <= 40) {
        return mapping(pv, 30, 40, false);
    } else {
        return 0;
    }
}

int get_blue(float pv) {
    int blue_value;
    if(pv <= 20) {
        return 0;
    } else if(pv <= 30) {
        return mapping(pv, 20, 30, true);
    } else if(pv <= 50) {
        return 255;
    } else {
        return mapping(pv, 50, 60, false);
    }
}

int ADC_Read10bit () {
    int i ;

    AD1CHS = 8;

    // Get an ADC sample
    AD1CON1bits.SAMP = 1 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically

    AD1CON1bits.SAMP = 0 ;           //Start sampling
    for (i = 0 ; i < 1000 ; i++) ; //Sample delay, conversion start automatically

    while (!AD1CON1bits.DONE) ;       //Wait for conversion to complete

    return ADC1BUF0;
}

int ADC_ReadPercentage() {
    int percent ;

    //A very crude percentage calculation
    percent = ( ADC_Read10bit ( 8 ) / 10 ) ;

    if (percent > 100)
    {
        percent = 100 ;
    }
    return percent ;
}



bool ADC_ChannelEnable() {
    ANSCbits.ANSC0 = 1;
    return true ;
    }

bool ADC_SetConfiguration() {

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

void blink_amount(int amount) {
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    PORTCbits.RC7 = 0;
    int i;
    __delay_ms(500);
    
    for(i = 0; i < amount; i++) {
        PORTCbits.RC7 = 1;
        __delay_ms(500);
        PORTCbits.RC7 = 0;
        __delay_ms(500);
    }
}


int root(int input, int n) {
  return (int)pow(input, 1./n);
}
