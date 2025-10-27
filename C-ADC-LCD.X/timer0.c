#include <xc.h>
#include "timer0.h"

/* Config Timer0 */
void TIMER0_Initialize(void)
{ 
	/* Timer0 disabled; 16-bit; no postscaler */
	/*  T0CON0 = 0x10; */
    T0CON0bits.MD16 = 1;
       
    /* HFINTOSC; counter not synchronized; prescaler 1:2 */
	/* T0CON1 = 0x71; */
    T0CON1bits.CS = 0b011;
    T0CON1bits.ASYNC = 1;
    T0CON1bits.CKPS = 0b0001;
    
    /* Load TMR0 with initial value (hex) */
    /* tCLK x counts  x prescaler = TMR0 counting time */
    /* 1/64MHz * (65535-33535) * 2 =  1 ms */
	TMR0H = 0x82;
	TMR0L = 0xFF;
}

/* Timer0 Delay = 1 ms x Time */
void TIMER0_Delay_ms(uint16_t Time)
{
    /* Timer0 enabled; 16-bit */
	/* T0CON0 |= 0x80; */
    T0CON0bits.EN = 1;
        
    while (Time != 0x00)
        {
    
    	/* Wait for TMR0IF = 1 */
        /* while ((PIR3 & 0x80) != 0x80) */
        while (PIR3bits.TMR0IF != 1)
            ;
        
        /* Clear TMR0IF bit */
        /* PIR3 &= 0x7F; */
        PIR3bits.TMR0IF = 0;
        
        /* Decrement Time variable */
        Time-=1;
        
        /* Reload TMR0 with value (hex) */
        /* tCLK1 x counts  x prescaler = TMR0 counting time */
        /* 1/64MHz * (65535-33535) * 1 =  1 ms */
	    TMR0H = 0x82;
	    TMR0L = 0xFF;
        }   
    
    /* Timer0 disabled; 16-bit */
	/* T0CON0 &= 0x7F; */
    T0CON0bits.EN = 0;
}