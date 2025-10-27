#include <xc.h>
#include "lcd.h"
#include "timer0.h"


unsigned char bateria_pattern[8]={0x04,0x1F,0x11,0x13,0x17,0x1F,0x1F,0xFF}; /* Character to be stored at address 0x00 */
unsigned char frente_de_onda_pattern[8]={0x02,0x09,0x05,0x15,0x15,0x05,0x09,0x02}; /* Character to be stored at address 0x01 */
unsigned char clavija_pattern[8]={0x0A,0x0A,0x1F,0x11,0x11,0x0E,0x04,0x04}; /* Character to be stored at address 0x02 */
unsigned char campana_pattern[8]={0x04,0x0E,0x0E,0x0E,0x1F,0x1F,0x00,0x04}; /* Character to be stored at address 0x03 */
unsigned char reloj_pattern[8]={0x1F,0x11,0x0A,0x04,0x04,0x0A,0x15,0x1F}; /* Character to be stored at address 0x04 */
unsigned char llave_pattern[8]={0x04,0x0E,0x0C,0x0E,0x0C,0x1F,0x11,0x1F}; /* Character to be stored at address 0x05 */
unsigned char bocina_pattern[8]={0x01,0x03,0x07,0x1F,0x1F,0x07,0x03,0x01}; /* Character to be stored at address 0x06 */
unsigned char nota_musical_pattern[8]={0x03,0x05,0x09,0x09,0x0B,0x0B,0x18,0x18}; /* Character to be stored at address 0x07 */

/* Config LCD */
void LCD_Initialize(void)
{
    /* 4-bit operation */
	LCD_CMD(0x02);
    TIMER0_Delay_ms(1);
      
    /* 2-line display, display on */
    LCD_CMD(0x28);
    TIMER0_Delay_ms(1);
    
    /* Display On, cursor off, blink off */
    LCD_CMD(0x0C);
    TIMER0_Delay_ms(1);
  
    /* Entry mode set, increment mode */
    LCD_CMD(0x06);
    TIMER0_Delay_ms(1);
}

void LCD_printchar(char ascode)
{
        LCD_RS_High;
        LCD_Port = (ascode & 0xF0);
        LCD_ENABLE();
        LCD_Port = ((ascode << 4) & 0xF0);
        LCD_ENABLE();
}

void LCD_printstring(char *text)
{
        do
        {
          LCD_printchar(*text++);
        }
        while (*text != '\n');
}

/* Place LCD cursor in (row, column) */
void LCD_LOCATE(char row, char column)
{
      column--;
      switch (row)
      {
        case 1:
              /* Set cursor to 1st row address and add index*/
              LCD_CMD(column |= 0x80);
              break;
        case 2:
              /* Set cursor to 2nd row address and add index*/
              LCD_CMD(column |= 0x40 | 0x80);
              break;
        case 3:
              /* Set cursor to 2nd row address and add index*/
              LCD_CMD(column |= 0x10 | 0x80);
              break;
        case 4:
              /* Set cursor to 2nd row address and add index*/
              LCD_CMD(column |= 0x50 | 0x80);
              break;
        default:
              break;
  }
}

/* Send a LCD command */
void LCD_CMD(char cmd_data)
{
      LCD_RS_Low;
      LCD_RW_Low;
      
      LCD_Port = (cmd_data  & 0xF0);  // 1111 0000
      LCD_ENABLE();
      LCD_Port = ((cmd_data << 4) & 0xF0);
      LCD_ENABLE();
      TIMER0_Delay_ms(2);
}

/* Toggle Enable */
void LCD_ENABLE (void)
{
      LCD_Enable_High;
      TIMER0_Delay_ms(1);
      LCD_Enable_Low;
}

/* Clear LCD screen */
void LCD_CLEAR_DISPLAY(void)
{
      LCD_CMD(0x01);
      TIMER0_Delay_ms(2);
}

/* Sets Character Generator RAM address */
void LCD_setCGRAM_address(void)
{
        LCD_RS_Low;
        LCD_RW_Low;
        //LCD_Port = (CGRAM_address & 0xF0);
        LCD_Port = 0x40;
        LCD_ENABLE();
        //LCD_Port = ((CGRAM_address << 4) & 0xF0);;
        LCD_Port = 0x00;
        LCD_ENABLE();
        TIMER0_Delay_ms(1);
}

/* Store new characters in CGRAM */
 void LCD_writeCGRAM(void)
{
      unsigned char j;
      
      LCD_setCGRAM_address();
            
      for (j=0; j<8; j++)
      {
        LCD_printchar(frente_de_onda_pattern[j]);
      }   
                
      for (j=0; j<8; j++)
      {
        LCD_printchar(bateria_pattern[j]);
      }   
                 
      for (j=0; j<8; j++)
      {
        LCD_printchar(clavija_pattern[j]);
      }   
              
      for (j=0; j<8; j++)
      {
        LCD_printchar(campana_pattern[j]);
      }   
            
      for (j=0; j<8; j++)
      {
        LCD_printchar(reloj_pattern[j]);
      }   
            
      for (j=0; j<8; j++)
      {
        LCD_printchar(llave_pattern[j]);
      }   
            
      for (j=0; j<8; j++)
      {
        LCD_printchar(bocina_pattern[j]);
      }   
            
      for (j=0; j<8; j++)
      {
        LCD_printchar(nota_musical_pattern[j]);
      }   
      
}

/* Turn off LCD screen */
void LCD_screen_off(void)
{
    /* Display Off, cursor off, blink off */
    LCD_CMD(0x08);
    TIMER0_Delay_ms(1);
}