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


#define PAGE_VER_LIE1_X		 180
#define PAGE_VER_KEY_WIDTH   230
#define PAGE_VER_KEY_HIGH    30


static void pageVersionInit(void);
static void pageVersionUpdate(void);
static void pageVersionItemUpdate(void);

///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_version_item[] =
{
	            //b0控件
	{
		1,     //id
		1,      //支持触控
		
		74,4,    //开始坐标
		243,30,//宽高
		
		{0x65,0x02,0x01,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //t1控件
	{
		2,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,42,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //t2控件
	{
		3,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,74,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //t3控件
	{
		4,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,108,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //t4控件
	{
		5,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,142,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //t5控件
	{
		6,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,178,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //t6控件
	{
		7,     //id
		1,      //支持触控
		
		PAGE_VER_LIE1_X,210,    //开始坐标
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//宽高
		
		{0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_version =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_version_item)/sizeof(PAGE_ITEM_T),
	
 	pageVersionInit,	
 	pageVersionUpdate
};

const _bmp_info bmp_version_Page =
{
	BASIC_PAGE_VERSION_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};


static void pageVersionInit(void)
{
	show_bmp_in_flash(0,0,bmp_version_Page.width,bmp_version_Page.height,bmp_version_Page.addr);
}

//版本页面刷新
static void pageVersionUpdate(void)
{
#if 0
	LCD_SetFrontColor(WHITE);  //字颜色
	LCD_SetBackColor(BLACK); 
	LCD_ShowString_hz16x16(10,100,200,16,16,"菜单子页面演示");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MAIN;
	}
#endif
	
	u8 item;
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_version.page_item_num; item++)
		{
			if(page_version_item[item].touch_en)  //检查触控
			{
				if( ( touch_up_pos.x >= page_version_item[item].start_pos_x ) && ( touch_up_pos.x < page_version_item[item].start_pos_x + page_version_item[item].width)  && \
					( touch_up_pos.y >= page_version_item[item].start_pos_y ) && ( touch_up_pos.y < page_version_item[item].start_pos_y + page_version_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					if(page_version_item[item].id != 1)
						gIDInfo.cmdUpdate = 2;
					memcpy(&gIDInfo.cmdPage.start, &page_version_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageVersionItemUpdate();   //页面刷新
	}
	
}

///////////////////////////////////////////////////////////
//显示更新
static void pageVersionItemUpdate(void)
{
	int item;

	for(item = 0; item < page_version.page_item_num; item++)
	{
		LCD_ShowString(page_version_item[item].start_pos_x, 
					page_version_item[item].start_pos_y, 100, 16, 16, gPagePara.t_string[item]);
	}
}



