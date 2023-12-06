#include "derivative.h"
#include "lcd.h"
#include "pit.h"

void lcd_Init(void)
{
  DDRH = 0xFF;

  DDRK |= 0b00000111;

  PIT_Sleep(PIT_CH2, 45);

  PTH = 0b00111000;

  PORTK_PK1 = 0;
  PORTK_PK2 = 0;

  lcd_Latch;

  PIT_Sleep(PIT_CH2, 5);

  lcd_Latch;

  PIT_Delay_us(PIT_CH3, 150);

  lcd_Latch;

  lcd_Ins(0b00111000);

  lcd_Ins(0b00001110);

  lcd_Ins(0b00000001);

  lcd_Ins(0b00000110);
}
void lcd_Ins(unsigned char val)
{
  while (lcd_Busy())
    ;
  PORTK_PK1 = 0;
  PORTK_PK2 = 0;
  PTH = val;
  lcd_Latch;
}
char lcd_Busy(void)
{
  unsigned int val = 0;
  DDRH = 0;
  PORTK_PK1 = 1;
  PORTK_PK2 = 0;
  lcd_Latch;
  val = PTH & 0x80;
  DDRH = 0xFF;
  return val;
}
char lcd_GetAddr(void)
{
  DDRH = 0x00; 

  PORTK_PK1 = 1; 
  PORTK_PK2 = 0;

  lcd_Latch 

  DDRH = 0xFF; 

  return  PTH & 0x7F;
}

void lcd_Data(unsigned char val)
{
  while (lcd_Busy());
  DDRH = 0xFF;
  PTH = val;
  PORTK_PK1 = 0;
  PORTK_PK2 = 1;
  lcd_Latch;
}
void lcd_Addr(unsigned char addr)
{
  lcd_Ins(addr | 0x80);
}
void lcd_AddrXY(unsigned char ix, unsigned char iy)
{
  if(iy == 0)
  {
    lcd_Addr(LCD_ROW0 + ix);
  }
  else if (iy == 1)
  {
    lcd_Addr(LCD_ROW1 + ix);
  }
  else if (iy == 2)
  {
    lcd_Addr(LCD_ROW2 + ix);
  }
  else if (iy == 3)
  {
    lcd_Addr(LCD_ROW3 + ix);
  }
  
}
void lcd_String(char const *straddr)
{
  unsigned int i;
  for (i = 0; straddr[i] != null; i++)
  {
    lcd_Data(straddr[i]);
  }
}
void lcdSmartString(char const *straddr, unsigned int delay);
void lcd_StringXY(unsigned char ix, unsigned char iy, char const *const straddr)
{
  lcd_AddrXY(ix, iy);
  lcd_String(straddr);
}

void lcd_DispControl(unsigned char curon, unsigned char blinkon);
void lcd_Clear(void)
{
  lcd_Ins(0b00000001);
}
void lcd_Home(void)
{
  lcd_Ins(0b00000010);
}
void lcd_ShiftL(char);
void lcd_ShiftR(char);
void lcd_CGAddr(unsigned char addr);
void lcd_CGChar(unsigned char cgAddr, unsigned const char *cgData, int size);