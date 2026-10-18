#include <xc.h>
#include "adc.h"

void ADC_Initialize(void)
{
    /* ADC enabled, ADC single conversion, ADC clock is Fosc, Result right justified */
    ADCON0 = 0x84;
    
    /* ADC clock frequency = Fosc / (2*(19+1)) = 1.6 MHz */
    ADCLK = 0x13;
	
    /* ADC Input channel is RA0/ANA0 */
    ADPCH = 0x00;
}


void ADC_Start(void)
{   
    /* GO = 1 */
    ADCON0 |= 0x01;
}

