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

#ifdef LCD_SIZE_480X320
	#define PAGE_SET_LINE1     84
	#define PAGE_SET_LINE2     158
	#define PAGE_SET_LINE3     228
	#define PAGE_SET_ROW1      62
	#define PAGE_SET_ROW2      260
	#define PAGE_SET_W         138
	#define PAGE_SET_H         40

	const u8* item_table[] =
	{
		"传感器检测",
		"显示屏亮度",
		"主板档位设置",
		"蜂鸣器设置",
		"系统参数导入",
		"系统参数导出",
	};
#else
	#define PAGE_SET_LINE1     62
	#define PAGE_SET_LINE2     120
	#define PAGE_SET_LINE3     174
	#define PAGE_SET_ROW1      60
	#define PAGE_SET_ROW2      222
	#define PAGE_SET_W         112
	#define PAGE_SET_H         32
#endif


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_SystemSet_item[] =
{	
	           //b0控件
	{
		1,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE1,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x01,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b1控件
	{
		2,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE2,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x02,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b2控件
	{
		3,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE1,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x03,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b3控件
	{
		4,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE2,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x04,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	          //b4控件
	{
		5,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE3,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b5控件
	{
		6,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE3,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,0x0c,0x06,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	
	{
		7,     //id
		1,      //支持触控
		
		0,0,    //开始坐标
		LCD_HOR_SIZE,40, //宽高
		
		{0x65,0x0c,0xfe,0x00,0xff,0xff,0xff},
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

#ifdef LCD_SIZE_480X320
	const _bmp_info bmp_system_Page =
	{
		BASIC_PAGE_SINGLE_BUTTON_OFFSET,
		152,
		52
	};
#else
	const _bmp_info bmp_system_Page =
	{
		BASIC_PAGE_SYSTEM_SET_OFFSET,
		LCD_HOR_SIZE,
		LCD_VER_SIZE
	};
#endif

static void pageSystemSetInit(void)
{
#ifdef LCD_SIZE_480X320
	u8 i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	LCD_Clear(BLACK);
	LCD_ShowString_hz24x24(192,26,100,24,24,"系统设置");
	POINT_COLOR = BRRED;
	BACK_COLOR = SEABLUE;
	for (i = 0; i < 6; i++)
	{
		show_bmp_in_flash(page_SystemSet_item[i].start_pos_x,page_SystemSet_item[i].start_pos_y,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
		LCD_ShowString_hz24x24(page_SystemSet_item[i].start_pos_x+5,page_SystemSet_item[i].start_pos_y+bmp_system_Page.height/2-12,
			bmp_system_Page.width,24,24,item_table[i]);
	}
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
#else
	show_bmp_in_flash(0,0,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
#endif
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

