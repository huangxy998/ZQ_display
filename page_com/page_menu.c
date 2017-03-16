#include<string.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "flash.h"  
#include "rtc.h" 

#include "char_model.h"
#include "page.h"
#include "touch.h"
#include "lcd_com.h"


static void pageMenuInit(void);
static void pageMenuUpdate(void);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_menu_item[] =
{
	
};

//ҳ��ṹ��
const PAGE_T page_menu =
{ 
	PAGE_ID_MENU,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_menu_item)/sizeof(PAGE_ITEM_T),
	
 	pageMenuInit(),	
 	pageMenuUpdate()
};


