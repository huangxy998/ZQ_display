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

static void pageParaSetInit(void);
static void pageParaSetUpdate(void);

///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_ParaSet_item[] =
{
	{ 
		0,	
		1,			//����							
		0,	0,
		LCD_HOR_SIZE, LCD_VER_SIZE,
		0	//��ʾ���º���	
	},
};

//ҳ��ṹ��
const PAGE_T page_ParaSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_ParaSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageParaSetInit,	
 	pageParaSetUpdate
};

const _bmp_info bmp_ParaSet_Page =
{
	BASIC_PAGE_PARA_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageParaSetInit(void)
{
	show_bmp_in_flash(0,0,bmp_ParaSet_Page.width,bmp_ParaSet_Page.height,bmp_ParaSet_Page.addr);
}

static void pageParaSetUpdate(void)
{
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(BLACK); 
//	LCD_ShowString_hz16x16(10,100,200,16,16,"�˵���ҳ����ʾ");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MAIN;
	}
	
}

