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
#include "page_timeset.h"

static void pageTimeSetInit(void);
static void pageTimeSetUpdate(void);
static void pageTimeItemUpdate(void);

///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_TimeSet_item[] =
{
	             //t0控件
	{
		2,     //id
		0,      //不支持触控
		
		107,10,    //开始坐标
		191,41, //宽高
		
		{0},
		0       //默认0
	},
	             //b0控件
	{
		3,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H1,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x03,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b1控件
	{
	  4,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H1,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x04,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b2控件
	{
		5,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H1,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b3控件
	{
		6,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H2,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x06,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b4控件
	{
		7,     //id
		1,      //支持触控
		
	   PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H2,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x07,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b5控件
	{
		8,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H2,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x08,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b6控件
	{
		9,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H3,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x09,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b7控件
	{
		10,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H3,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0a,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b8控件
	{
		11,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H3,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0b,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b9控件
	{
	12,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H4,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0c,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b10控件
	{
		13,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H1,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0d,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b11控件
	{
		14,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H2,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0e,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b12控件
	{
		15,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H3,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x0f,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b13控件
	{
		16,     //id
		1,      //支持触控
		
	  PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H1,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x10,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b14控件
	{
		17,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H2,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,011,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b15控件
	{
		18,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H3,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x12,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b16控件
	{
		19,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H4,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x13,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b17控件
	{
	20,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H4,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
		{0x65,0x12,0x14,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b18控件
	{
		21,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H4,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		{0x65,0x12,0x15,0x00,0xff,0xff,0xff},
		0       //默认0
	},
		//b19控件
	{
		22,     //id
		1,      //支持触控
		
	 PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H4,    //开始坐标
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //宽高
		
	{0x65,0x12,0x16,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_TimeSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_TimeSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageTimeSetInit,	
 	pageTimeSetUpdate
};

const _bmp_info bmp_TimeSet_Page =
{
	BASIC_PAGE_TIME_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageTimeSetInit(void)
{
	show_bmp_in_flash(0,0,bmp_TimeSet_Page.width,bmp_TimeSet_Page.height,bmp_TimeSet_Page.addr);
}

static void pageTimeSetUpdate(void)
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
		for(item = 0; item < page_TimeSet.page_item_num; item++)
		{
			if((page_TimeSet_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_TimeSet_item[item].start_pos_x ) && ( touch_up_pos.x < page_TimeSet_item[item].start_pos_x + page_TimeSet_item[item].width)  && \
					( touch_up_pos.y >= page_TimeSet_item[item].start_pos_y ) && ( touch_up_pos.y < page_TimeSet_item[item].start_pos_y + page_TimeSet_item[item].height) )
				{
//					gIDInfo.cmdUpdate = 1;
//					memcpy(&gIDInfo.cmdPage.start, &page_TimeSet_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageTimeItemUpdate();   //页面刷新 
	}
	
}

static void pageTimeItemUpdate(void)
{
	LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 100, 16, 16, gPagePara.t_string[0]);
}


