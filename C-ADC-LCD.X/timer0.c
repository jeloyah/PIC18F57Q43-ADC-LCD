#include <xc.h>
#include "timer0.h"

/* Config Timer0 */
void TIMER0_Initialize(void)
{ 
	/* Timer0 disabled; 16-bit; no postscaler */
	T0CON0 = 0x10;
    
    /* HFINTOSC; counter not synchronized; prescaler 1:2 */
	T0CON1 = 0x71;
    
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
	T0CON0 |= 0x80;
        
    while (Time != 0x00)
        {
    
    	/* Wait for TMR0IF = 1 */
        while ((PIR3 & 0x80) != 0x80)
            ;
        
        /* Clear TMR0IF bit */
        PIR3 &= 0x7F; 
         
        /* Decrement Time variable */
        Time-=1;
        
        /* Reload TMR0 with value (hex) */
        /* tCLK1 x counts  x prescaler = TMR0 counting time */
        /* 1/64MHz * (65535-33535) * 1 =  1 ms */
	    TMR0H = 0x82;
	    TMR0L = 0xFF;
        }   
    
    /* Timer0 disabled; 16-bit */
	T0CON0 &= 0x7F;
 
}