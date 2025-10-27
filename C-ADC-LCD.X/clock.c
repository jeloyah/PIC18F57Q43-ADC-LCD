#include <xc.h>
#include "clock.h"

void CLOCK_Initialize(void)
{
	/* HFINTOSC enabled */
    /* OSCEN = 0x40; */
    OSCENbits.HFOEN = 1;
    
    /* HFINTOSC = 64 MHz */
	/* OSCFRQ = 0x08; */
    OSCFRQbits.HFFRQ = 0b1000;
    
    /* Clock source = HFINTOSC, Clock Divider = 0 */
    /* OSCCON1 = 0x60; */
    OSCCON1bits.NOSC = 0b0110;
    
    OSCCON1bits.NDIV = 0b000;

    /* Clear clock switch flag */
    /* PIR0 &= 0xF7; */
    PIR0bits.CSWIF = 0;
    
}
