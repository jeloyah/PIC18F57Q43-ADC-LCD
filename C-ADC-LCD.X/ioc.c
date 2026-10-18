
#include <xc.h>
#include "ioc.h"
#include "lcd.h"

void IOC_Initialize(void)
{
    /* Clear the bit IOCIF by clearing all bits in IOCxF register  */
    IOCBF = 0x00; 
        
    /* Interrupt-on-change enabled */
    PIE0 = 0x80;
    
    /* Interrupt on change enabled on RB4 (falling edge) */
    IOCBN = 0x10;
  
}

void __interrupt(__irq(IRQ_IOC)) IOC_ISR(void) 
{                
        /* Clear the bit IOCIF by clearing all bits in IOCxF register  */
        IOCBF = 0x00; 
        
        /* Check if RB4 = 0 */
        if ((PORTB&0x10) == 0x00)
        
        {
            /* Clear LCD screen*/
            LCD_CLEAR_DISPLAY();
            /* Row 1, column 1 */
            LCD_LOCATE(1,1);
            /* Turn off screen */
            LCD_screen_off();        
            
            /* Hard coded reset, since pin MCLR(RE3) is used by debugger */   
            RESET();
        }
            
}


