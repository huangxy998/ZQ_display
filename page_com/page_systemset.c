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

static void pageSystemSetInit(void);
static void pageSystemSetUpdate(void);

///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_SystemSet_item[] =
{	
	           //b0控件
	{
		1,     //id
		1,      //支持触控
		
		60,62,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x01,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b1控件
	{
		2,     //id
		1,      //支持触控
		
		60,120,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x02,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b2控件
	{
		3,     //id
		1,      //支持触控
		
		222,62,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x03,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b3控件
	{
		4,     //id
		1,      //支持触控
		
		222,120,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x04,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	          //b4控件
	{
		5,     //id
		1,      //支持触控
		
		60,174,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b5控件
	{
		6,     //id
		1,      //支持触控
		
		222,174,    //开始坐标
		112,32, //宽高
		
		{0x65,0x0c,0x06,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_SystemSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_SystemSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageSystemSetInit,	
 	pageSystemSetUpdate
};

const _bmp_info bmp_system_Page =
{
	BASIC_PAGE_SYSTEM_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageSystemSetInit(void)
{
	show_bmp_in_flash(0,0,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
}

static void pageSystemSetUpdate(void)
{
#if 0
	LCD_SetFrontColor(WHITE);  //字颜色
	LCD_SetBackColor(BLACK); 
//	LCD_ShowString_hz16x16(10,100,200,16,16,"菜单子页面演示");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MAIN;
	}
#endif
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_SystemSet.page_item_num; item++)
		{
			if((page_SystemSet_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_SystemSet_item[item].start_pos_x ) && ( touch_up_pos.x < page_SystemSet_item[item].start_pos_x + page_SystemSet_item[item].width)  && \
					( touch_up_pos.y >= page_SystemSet_item[item].start_pos_y ) && ( touch_up_pos.y < page_SystemSet_item[item].start_pos_y + page_SystemSet_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_SystemSet_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
}

