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

static void pageVersionInit(void);
static void pageVersionUpdate(void);

///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_version_item[] =
{
	{  //ģʽ
		0,	
		1,			//����							
		0,	0,
		LCD_HOR_SIZE, LCD_VER_SIZE,
		0	//��ʾ���º���	
	},
};

//ҳ��ṹ��
const PAGE_T page_version =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_version_item)/sizeof(PAGE_ITEM_T),
	
 	pageVersionInit,	
 	pageVersionUpdate
};

static void pageVersionInit(void)
{
	LCD_Clear(BLACK);
}

static void pageVersionUpdate(void)
{
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(BLACK); 
	LCD_ShowString_hz16x16(10,100,200,16,16,"�˵���ҳ����ʾ");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MENU;
	}
	
}



