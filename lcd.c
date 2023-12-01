#include "derivative.h"
#include "lcd.h"
#include "pit.h"



void lcd_Init (void)
{  /*LCD Initialization Start***************************/
  //Port Initialization-------------------------------------------
    //PH7-PH0 -> D7 - D0 (data Lines)
    DDRH = 0xFF;
    //PK2-PK0 -> Control Lines (output)
    DDRK |= 0b00000111;
    //1st delay - Delay 40+ [ms]
    PIT_Sleep(PIT_CH2, 45);
    //Present Data on PTH
    PTH  = 0b00111000;  
    
    PORTK_PK1 = 0;
    PORTK_PK2 = 0;

    //Latch Instruction
    PORTK_PK0 = 1;
    lcd_MicroDelay;
    PORTK_PK0 = 0;

    //2nd Delay, 4.1ms+   
    PIT_Sleep(PIT_CH2, 5);

    //Latch same Instruction again
    lcd_Latch;

    //third Delay  100uS+ 
    PIT_Delay_us(PIT_CH3, 150);//third Delay  100uS+ 

    //Latch same Instruction again
    lcd_Latch;



    //5x8 dots, 2 lines
    //lcd_Ins(0b00111000); 
    PIT_Sleep(PIT_CH3, 10);
    lcd_Latch;

    PTH = 0b00001110;
    PIT_Sleep(PIT_CH3, 10);
    lcd_Latch;


    //lcd_Ins(0b00000001);   //clear display, home position
    PTH = 0b00000001;
    PIT_Sleep(PIT_CH3, 10);
    lcd_Latch;
     
    PTH = 0b00000110;
    PIT_Sleep(PIT_CH3, 10);
    lcd_Latch;
}
void lcd_Ins (unsigned char); //LCD_Inst
char lcd_Busy (void); //LCD_Inst
char lcd_GetAddr(void);
void lcd_Data (unsigned char val);
void lcd_Addr (unsigned char addr);
void lcd_AddrXY (unsigned char ix, unsigned char iy);
void lcd_String (char const * straddr);
void lcdSmartString(char const * straddr, unsigned int delay);
void lcd_StringXY (unsigned char ix, unsigned char iy, char const * const straddr);

void lcd_DispControl (unsigned char curon, unsigned char blinkon);
void lcd_Clear (void);
void lcd_Home (void);
void lcd_ShiftL (char);
void lcd_ShiftR (char);
void lcd_CGAddr (unsigned char addr);
void lcd_CGChar (unsigned char cgAddr, unsigned const char* cgData, int size);