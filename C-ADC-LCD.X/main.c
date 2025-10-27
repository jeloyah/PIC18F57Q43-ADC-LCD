
#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "adc.h"
#include "ioc.h"
#include "timer0.h"
#include "lcd.h"

void main(void) {
    
    char Vadc_string[12];
    float Vadc=0;
    
    /* System Clock Initialization */
	CLOCK_Initialize();
    
    /* Config PortA */
    PortA_Initialize();
    
    /* Config PortB */
    PortB_Initialize();

    /* Config PortC */
    PortC_Initialize();
    
    /* Config PortD */
    PortD_Initialize();
    
    /* Config PortE */
    PortE_Initialize();
    
    /* Config PortF */
    PortF_Initialize();
    
    /* Config ADC */
    ADC_Initialize();
    
    /* Config Timer0 */
    TIMER0_Initialize();
    
    /* Config LCD */
    LCD_Initialize();
    
    LCD_CLEAR_DISPLAY();
    
    /* Config IOC */
    IOC_Initialize();
        
    /* Enable interrupts */
    ei();
    
    /* infinite loop */
    while(1)
    {
     /* Start ADC conversion */
     ADC_Start();
        
     /* Wait for Go = 0 */
	 while (ADC_conversionComplete)
         ; /* while ADC */

    /* Calcular voltaje analogico */
    Vadc = ADRES * (float)1.22E-03;
    
    
    /* Convertir a string */
    sprintf(Vadc_string, "Vadc = %.2f V\n", Vadc);      
        
    /* Row 2, column 1 */
    LCD_LOCATE(1,1);            
    LCD_printstring(Vadc_string);
    
    /* Refresh every 500 ms */
    TIMER0_Delay_ms(500);
        
     } /* while */
        
    
    return;
} /* main*/
