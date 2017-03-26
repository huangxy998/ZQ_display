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

static void pageBlacklistInit(void);
static void pageBlacklistUpdate(void);

///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_Blacklist_item[] =
{
	{ 
		0,	
		1,			//触控							
		0,	0,
		LCD_HOR_SIZE, LCD_VER_SIZE,
		0	//显示更新函数	
	},
};

//页面结构体
const PAGE_T page_Blacklist =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T),
	
 	pageBlacklistInit,	
 	pageBlacklistUpdate
};

const _bmp_info bmp_Blacklist_Page =
{
	BASIC_PAGE_BLACK_LIST_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageBlacklistInit(void)
{
	show_bmp_in_flash(0,0,bmp_Blacklist_Page.width,bmp_Blacklist_Page.height,bmp_Blacklist_Page.addr);
}

static void pageBlacklistUpdate(void)
{
	LCD_SetFrontColor(WHITE);  //字颜色
	LCD_SetBackColor(BLACK); 
//	LCD_ShowString_hz16x16(10,100,200,16,16,"菜单子页面演示");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MENU;
	}
	
}

