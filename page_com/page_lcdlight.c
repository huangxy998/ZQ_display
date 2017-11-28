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
#include "timer.h"

#include "char_model.h"
#include "page.h"
#include "touch.h"
#include "lcd_com.h"

static void pageLcdInit(void);
static void pageLcdUpdate(void);
static void pageLcdItemUpdate(void);

#ifdef LCD_SIZE_480X320
	#define PAGE_DIALOG_ADD_X 40
	#define PAGE_DIALOG_ADD_Y 4
#else
	#define PAGE_DIALOG_ADD_X 0
	#define PAGE_DIALOG_ADD_Y 0
#endif

static u8 lightstr[4] = {0};
static u8 light = 0;
static const char keyback[] = {0x65,0x10,0xfd,0x00,0xff,0xff,0xff};


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_Lcd_item[] =
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//GEARset2
	/////////////////////////////////////////////
	
	 //p0控件
	{
		1,	   //id
		0,		//不支持触控
		
		68,70,	  //开始坐标
		280,106, //宽高
		
		{0},
		0		//默认0
	},
	      //b0控件
	{
		2,	   //id
		1,		//支持触控
		
		80+PAGE_DIALOG_ADD_X,86+PAGE_DIALOG_ADD_Y,	  //开始坐标
		45,40, //宽高
		
	{0x65,0x0f,0x02,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //b1控件
	{
		3,	   //id
		1,		//支持触控
		
		80+PAGE_DIALOG_ADD_X,134+PAGE_DIALOG_ADD_Y,    //开始坐标
		45,40, //宽高
		
	{0x65,0x0f,0x03,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //b2控件
	{
		4,	   //id
		1,		//支持触控
		
		262+PAGE_DIALOG_ADD_X,102+PAGE_DIALOG_ADD_Y,	//开始坐标
		68,56, //宽高
		
	{0x65,0x0f,0x04,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //n0控件
	{
		5,	   //id
		0,		//不支持触控
		
		150+PAGE_DIALOG_ADD_X,114+PAGE_DIALOG_ADD_Y,	//开始坐标
		100,30, //宽高
		
		{0},
		0		//默认0
	},
	
	{
		6,	   //id
		1,		//支持触控
		
		0,250,	//开始坐标
		480,320, //宽高
		
	{0x65,0x0f,0x04,0x00,0xff,0xff,0xff},
		0		//默认0
	},

};

extern const u8* d_str[];

//页面结构体
const PAGE_T page_Lcd =
{ 
	PAGE_ID_CONFIRM,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Lcd_item)/sizeof(PAGE_ITEM_T),
	
 	pageLcdInit,	
 	pageLcdUpdate
};

static u8 prePage = 0;
u8 prelight = 0;

static void pageLcdInit(void)
{
	u16 color, bccolor;
	u16 i;
	
	prePage = gPageInfo.pre_page_idx;
	LCD_Clear(WHITE);
	//画按键b0，b1，b2
	color = POINT_COLOR;
	bccolor = BACK_COLOR;
	POINT_COLOR = BLACK;
	for(i = 1; i < 4; i++)
	{
		LCD_Fill(page_Lcd_item[i].start_pos_x,page_Lcd_item[i].start_pos_y,
			     page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width,
			     page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height, LGRAY);
		
		LCD_DrawLine(page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width,
				 page_Lcd_item[i].start_pos_y,
			     page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width,
			     page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height);
		LCD_DrawLine(page_Lcd_item[i].start_pos_x,
			page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height,
			     page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width,
			     page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height);
		BACK_COLOR = LGRAY;
		LCD_ShowString_hz16x16(page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width/2 -4, page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height/2-8, 300, 16, 16, d_str[i - 1]);
	}
	//画中间方框
	POINT_COLOR = BLUE;
	LCD_DrawRectangle(page_Lcd_item[i].start_pos_x, page_Lcd_item[i].start_pos_y,
			     page_Lcd_item[i].start_pos_x+page_Lcd_item[i].width,
			     page_Lcd_item[i].start_pos_y+page_Lcd_item[i].height);
	BACK_COLOR = WHITE;
	LCD_ShowString_hz16x16(352,280,100,16,16,"按屏幕下方返回");
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
	SPI_Flash_Read(&light,LCD_LIGHT_PARAM_OFFSET,1);
	if (light >10)
		 light = 8;
	prelight = light;
}

static void pageLcdUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_Lcd.page_item_num; item++)
		{
			if((page_Lcd_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_Lcd_item[item].start_pos_x ) && ( touch_up_pos.x < page_Lcd_item[item].start_pos_x + page_Lcd_item[item].width)  && \
					( touch_up_pos.y >= page_Lcd_item[item].start_pos_y ) && ( touch_up_pos.y < page_Lcd_item[item].start_pos_y + page_Lcd_item[item].height) )
				{
					switch(item)
					{
						case 1:
							if (light < 10)
								light++;
							TIM2_PWM_duty(10*light);
							break;
						case 2:
							if (light > 1)
								light--;
							TIM2_PWM_duty(10*light);
							break;
						case 3:
							SPI_Flash_Write(&light,LCD_LIGHT_PARAM_OFFSET,1);
							gPageInfo.cur_page_idx = prePage;
							break;
						case 5:
							gPageInfo.cur_page_idx = prePage;
							TIM2_PWM_duty(10*prelight);
							break;
						default:
							break;
					}
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, keyback, TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	pageLcdItemUpdate();   //页面刷新
}

static void pageLcdItemUpdate(void)
{
	u16 bkcolor = BACK_COLOR; 
	u16 color = POINT_COLOR;
	POINT_COLOR = BLACK;
	BACK_COLOR = WHITE;
	sprintf((char*)lightstr, "%02d", light);
	LCD_ShowString_hz16x16(page_Lcd_item[4].start_pos_x+2, 
					page_Lcd_item[4].start_pos_y+2, 200, 16, 16, lightstr);
	BACK_COLOR = bkcolor;
	POINT_COLOR = color;
}

u8 getLcdLightParam(void)
{
	SPI_Flash_Read(&light,LCD_LIGHT_PARAM_OFFSET,1);
	return light;
}

