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

static void pageSystemUpdateInit(void);
static void pageSystemUpdate(void);
static void pageSystemUpdateItemUpdate(void);


#ifdef LCD_SIZE_480X320
	#define PAGE_SET_LINE1     24
	#define PAGE_SET_LINE2     98
	#define PAGE_SET_LINE3     168
	#define PAGE_SET_ROW1      62
	#define PAGE_SET_ROW2      260
	#define PAGE_SET_W         138
	#define PAGE_SET_H         40
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
const PAGE_ITEM_T page_SystemUpdate_item[] =
{	
	           //b0控件
	{
		1,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE1,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x01,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b1控件
	{
		2,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE2,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x02,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b2控件
	{
		3,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE1,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x03,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	              //b3控件
	{
		4,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE2,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x04,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	          //b4控件
	{
		5,     //id
		1,      //支持触控
		
		PAGE_SET_ROW1,PAGE_SET_LINE3,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b5控件
	{
		6,     //id
		1,      //支持触控
		
		PAGE_SET_ROW2,PAGE_SET_LINE3,    //开始坐标
		PAGE_SET_W,PAGE_SET_H, //宽高
		
		{0x65,PAGE_ID_SYSUPDATA,0x06,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_SystemUpdate =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_SystemUpdate_item)/sizeof(PAGE_ITEM_T),
	
 	pageSystemUpdateInit,	
 	pageSystemUpdate
};


extern const _bmp_info bmp_system_Page;
static u8 progress_show = 0;

static void pageSystemUpdateInit(void)
{
#ifdef LCD_SIZE_480X320
	u8 i = 0;
	LCD_Clear(BLACK);
	for (i = 0; i < 6; i++)
	{
		show_bmp_in_flash(page_SystemUpdate_item[i].start_pos_x,page_SystemUpdate_item[i].start_pos_y,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
	}
	progress_show = 0;
#else
	show_bmp_in_flash(0,0,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
#endif
}

static void pageSystemUpdate(void)
{

	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_SystemUpdate.page_item_num; item++)
		{
			if((page_SystemUpdate_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_SystemUpdate_item[item].start_pos_x ) && ( touch_up_pos.x < page_SystemUpdate_item[item].start_pos_x + page_SystemUpdate_item[item].width)  && \
					( touch_up_pos.y >= page_SystemUpdate_item[item].start_pos_y ) && ( touch_up_pos.y < page_SystemUpdate_item[item].start_pos_y + page_SystemUpdate_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_SystemUpdate_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
#ifdef LCD_SIZE_480X320
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageSystemUpdateItemUpdate();   //页面刷新
	}
#endif
}

static void pageSystemUpdateItemUpdate(void)
{
	char i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	
	for (i = 0; i < 6; i++)
	{	
		POINT_COLOR = BRRED;
		BACK_COLOR = SEABLUE;
		LCD_ShowString_hz16x16(page_SystemUpdate_item[i].start_pos_x+32, page_SystemUpdate_item[i].start_pos_y+bmp_system_Page.height/2 -8, 300, 16, 16, gPagePara.t_string[i]);	
		POINT_COLOR = GREEN;
		BACK_COLOR = BLACK;
		LCD_ShowString_hz16x16(page_SystemUpdate_item[i].start_pos_x+4, page_SystemUpdate_item[i].start_pos_y+bmp_system_Page.height+2, 300, 16, 16, gPagePara.t_string[i+6]);
	}
	POINT_COLOR = BROWN;
	BACK_COLOR = BLACK;
	LCD_ShowString_hz16x16(page_SystemUpdate_item[i-2].start_pos_x, page_SystemUpdate_item[i-2].start_pos_y+bmp_system_Page.height+2+16+6, 300, 16, 16, "                               ");
	LCD_ShowString_hz16x16(page_SystemUpdate_item[i-2].start_pos_x, page_SystemUpdate_item[i-2].start_pos_y+bmp_system_Page.height+2+16+6, 300, 16, 16, gPagePara.t_string[i+6]);
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
	if(gPagePara.j_percent[0][1] != 0)
	{
		static int valtmp = 0;
		int value = 0;
		
		if(progress_show == 0)
		{
			progress_show = 1;
			valtmp = 0;
			LCD_Fill(page_SystemUpdate_item[4].start_pos_x, 292,
			     page_SystemUpdate_item[4].start_pos_x+354,
			     292+14, WHITE);
		}
		
		value = atoi((char*)&gPagePara.j_percent[0]);
		if(value < valtmp)
		{
			progress_show = 0;
		}
		else
		{
			if(value != valtmp)
			{
				valtmp = value;
				LCD_Fill(page_SystemUpdate_item[4].start_pos_x+2, 292+2,
			     page_SystemUpdate_item[4].start_pos_x+(350*value)/100,
			     292+14-2, GREEN);
			}
		}
	}
}

