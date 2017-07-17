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

static void pageConfirmInit(void);
static void pageConfirmUpdate(void);
static void pageConfirmItemUpdate(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_Confirm_item[] =
{
	//p0控件
	{
		1,	   //id
		0,		//不支持触控
		
		68,72,	  //开始坐标
		280,106, //宽高
		
		{0},
		0		//默认0
	},
	      //b0控件
	{
		2,	   //id
		1,		//支持触控
		
		110,132,	  //开始坐标
		70,30, //宽高
		
	{0x65,0x16,0x03,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //b1控件
	{
		3,	   //id
		1,		//支持触控
		
		234,132,    //开始坐标
		70,30, //宽高
		
	{0x65,0x16,0x04,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //t0控件
	{
		4,	   //id
		0,		//不支持触控
		
		110,100,	//开始坐标
		200,30, //宽高
		
		{0},
		0		//默认0
	}

};

//页面结构体
const PAGE_T page_confirm =
{ 
	PAGE_ID_CONFIRM,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Confirm_item)/sizeof(PAGE_ITEM_T),
	
 	pageConfirmInit,	
 	pageConfirmUpdate
};

extern const _bmp_info bmp_Dialog_Page;

static void pageConfirmInit(void)
{
	u16 color;
	u16 i;
	show_bmp_in_flash(page_Confirm_item[0].start_pos_x,page_Confirm_item[0].start_pos_y,
		              bmp_Dialog_Page.width,bmp_Dialog_Page.height,bmp_Dialog_Page.addr);
	//画按键b0，b1
	color = POINT_COLOR;
	POINT_COLOR = BLACK;
	for(i = 1; i < 3; i++)
	{
		LCD_Fill(page_Confirm_item[i].start_pos_x,page_Confirm_item[i].start_pos_y,
			     page_Confirm_item[i].start_pos_x+page_Confirm_item[i].width,
			     page_Confirm_item[i].start_pos_y+page_Confirm_item[i].height, GRAY);
		
		LCD_DrawLine(page_Confirm_item[i].start_pos_x+page_Confirm_item[i].width,
				 page_Confirm_item[i].start_pos_y,
			     page_Confirm_item[i].start_pos_x+page_Confirm_item[i].width,
			     page_Confirm_item[i].start_pos_y+page_Confirm_item[i].height);
		LCD_DrawLine(page_Confirm_item[i].start_pos_x,page_Confirm_item[i].start_pos_y+page_Confirm_item[i].height,
			     page_Confirm_item[i].start_pos_x+page_Confirm_item[i].width,
			     page_Confirm_item[i].start_pos_y+page_Confirm_item[i].height);
	}	
	POINT_COLOR = color;
}

static void pageConfirmUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_confirm.page_item_num; item++)
		{
			if((page_Confirm_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_Confirm_item[item].start_pos_x ) && ( touch_up_pos.x < page_Confirm_item[item].start_pos_x + page_Confirm_item[item].width)  && \
					( touch_up_pos.y >= page_Confirm_item[item].start_pos_y ) && ( touch_up_pos.y < page_Confirm_item[item].start_pos_y + page_Confirm_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_Confirm_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	pageConfirmItemUpdate();   //页面刷新
}

static void pageConfirmItemUpdate(void)
{
	LCD_ShowString_hz16x16(page_Confirm_item[3].start_pos_x+2, 
					page_Confirm_item[3].start_pos_y+2, 100, 16, 16, gPagePara.t_string[0]);
}

