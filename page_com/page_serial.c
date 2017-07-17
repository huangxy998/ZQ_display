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

#define PAGE_GZ_L1			3
#define PAGE_GZ_L2			56
#define PAGE_GZ_L3			108
#define PAGE_GZ_L4		    180
#define PAGE_GZ_L5		    316
#define PAGE_GZ_H1			26
#define PAGE_GZ_H2			50
#define PAGE_GZ_H3			73
#define PAGE_GZ_H4			96
#define PAGE_GZ_H5			119
#define PAGE_GZ_H6			142
#define PAGE_GZ_H7			165
#define PAGE_GZ_H8			189
#define PAGE_GZ_W1      49
#define PAGE_GZ_W2      43
#define PAGE_GZ_W3      63
#define PAGE_GZ_W4      134
#define PAGE_GZ_W5      76
#define PAGE_GZ_H       20


static void pageSerialInit(void);
static void pageSerialUpdate(void);
static void pageSerialItemUpdate(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_Serial_item[] =
{
	        //p0控件
	{
		1,     //id
		0,      //不支持触控
		
		0,0,    //开始坐标
		400,240, //宽高
		
		{0},
		0       //默认0
	},
	            //b0控件
	{
		2,     //id
		1,      //支持触控
		
		22,210,    //开始坐标
		80,26, //宽高
		
		{0x65,0x0b,0x04,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b1控件
	{
		3,     //id
		1,      //支持触控
		
		160,210,    //开始坐标
		80,26, //宽高
		
			{0x65,0x0b,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b2控件
	{
		4,     //id
		1,      //支持触控
		
		290,210,    //开始坐标
		80,26, //宽高
		
			{0x65,0x0b,0x06,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //t0控件
	{
		6,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H1,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t1控件
	{
		7,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H2,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t2控件
	{
		8,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H3,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t3控件
	{
		9,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H4,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t4控件
	{
		10,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H5,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	           //t5控件
	{
		11,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H6,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t6控件
	{
		12,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H7,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t7控件
	{
		13,     //id
		0,      //不支持触控
		
		PAGE_GZ_L1,PAGE_GZ_H8,    //开始坐标
		PAGE_GZ_W1,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	         //t8控件
	{
		14,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H1,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	           //t9控件
	{
		15,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H2,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t10控件
	{
		16,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H3,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t11控件
	{
		17,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H4,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t12控件
	{
		18,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H5,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t13控件
	{
		19,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H6,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	           //t14控件
	{
		20,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H7,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t15控件
	{
		21,     //id
		0,      //不支持触控
		
		PAGE_GZ_L2,PAGE_GZ_H8,    //开始坐标
		PAGE_GZ_W2,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t16控件
	{
		22,     //id
		0,      //不支持触控
		
		PAGE_GZ_L3,PAGE_GZ_H1,    //开始坐标
		PAGE_GZ_W3,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t17控件
	{
		23,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H2,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t18控件
	{
		24,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H3,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t19控件
	{
		25,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H4,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		  
		{0},
		0       //默认0
	},
	            //t20控件
	{
		26,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H5,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		{0},
		0       //默认0
	},
	             //t21控件
	{
		27,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H6,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	          //t22控件
	{
		28,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H7,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		{0},
		0       //默认0
	},
	            //t23控件
	{
		29,     //id
		0,      //不支持触控
		
			PAGE_GZ_L3,PAGE_GZ_H8,    //开始坐标
		  PAGE_GZ_W3,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t24控件
	{
		30,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H1,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t25控件
	{
		31,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H2,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t26控件
	{
		32,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H3,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t27控件
	{
		33,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H4,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	         //t28控件
	{
		34,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H5,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t29控件
	{
		35,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H6,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t30控件
	{
		36,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H7,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t31控件
	{
		37,     //id
		0,      //不支持触控
		
		PAGE_GZ_L4,PAGE_GZ_H8,    //开始坐标
		PAGE_GZ_W4,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t32控件
	{
		38,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H1,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t33控件
	{
		39,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H2,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t34控件
	{
		40,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H3,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	             //t35控件
	{
		41,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H4,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	            //t36控件
	{
		42,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H5,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		{0},
		0       //默认0
	},
	            //t37控件
	{
		43,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H6,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	         //t38控件
	{
		44,     //id
		0,      //不支持触控
		PAGE_GZ_L5,PAGE_GZ_H7,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	},
	//t39控件
	{
		45,     //id
		0,      //不支持触控
		
		PAGE_GZ_L5,PAGE_GZ_H8,    //开始坐标
		PAGE_GZ_W5,PAGE_GZ_H, //宽高
		
		{0},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_Serial =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Serial_item)/sizeof(PAGE_ITEM_T),
	
 	pageSerialInit,	
 	pageSerialUpdate
};

const _bmp_info bmp_Serial_Page =
{
	BASIC_PAGE_SERAL_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageSerialInit(void)
{
	show_bmp_in_flash(0,0,bmp_Serial_Page.width,bmp_Serial_Page.height,bmp_Serial_Page.addr);
}

static void pageSerialUpdate(void)
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
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_Serial.page_item_num; item++)
		{
			if(page_Serial_item[item].touch_en)  //检查触控
			{
				if( ( touch_up_pos.x >= page_Serial_item[item].start_pos_x ) && ( touch_up_pos.x < page_Serial_item[item].start_pos_x + page_Serial_item[item].width)  && \
					( touch_up_pos.y >= page_Serial_item[item].start_pos_y ) && ( touch_up_pos.y < page_Serial_item[item].start_pos_y + page_Serial_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_Serial_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageSerialItemUpdate();   //页面刷新
	}
	
}

//显示更新
static void pageSerialItemUpdate(void)
{
	int item;
	LCD_SetBackColor(BLACK);
	for(item = 0; item < 40; item++)
	{
		LCD_Fill(page_Serial_item[item+4].start_pos_x, page_Serial_item[item+4].start_pos_y,
			     page_Serial_item[item+4].start_pos_x+page_Serial_item[item+4].width-4,
			     page_Serial_item[item+4].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_Serial_item[item+4].start_pos_x, 
					page_Serial_item[item+4].start_pos_y, page_Serial_item[item+4].width, 16, 16, gPagePara.t_string[item]);
		
	}
}


