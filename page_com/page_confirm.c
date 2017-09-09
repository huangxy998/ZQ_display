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

#ifdef LCD_SIZE_480X320
	#define PAGE_ERROR_B1X     122 
	#define PAGE_ERROR_B1Y     172
	#define PAGE_ERROR_B1W     66
	#define PAGE_ERROR_B1H     30
	#define PAGE_ERROR_B2X     310 
	#define PAGE_ERROR_B2Y     172
	#define PAGE_ERROR_B2W     66
	#define PAGE_ERROR_B2H     30
	#define PAGE_ERROR_TX     170 
	#define PAGE_ERROR_TY     132
	#define PAGE_ERROR_TW     150
	#define PAGE_ERROR_TH     30
#else
	#define PAGE_ERROR_B1X     110 
	#define PAGE_ERROR_B1Y     132
	#define PAGE_ERROR_B1W     70
	#define PAGE_ERROR_B1H     30
	#define PAGE_ERROR_B2X     234 
	#define PAGE_ERROR_B2Y     132
	#define PAGE_ERROR_B2W     70
	#define PAGE_ERROR_B2H     30
	#define PAGE_ERROR_TX     110 
	#define PAGE_ERROR_TY     100
	#define PAGE_ERROR_TW     200
	#define PAGE_ERROR_TH     30
#endif

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
		
		PAGE_ERROR_B1X,PAGE_ERROR_B1Y,	  //开始坐标
		PAGE_ERROR_B1W,PAGE_ERROR_B1H, //宽高
		
		{0x65,0x17,0x03,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //b1控件
	{
		3,	   //id
		1,		//支持触控
		
		PAGE_ERROR_B2X,PAGE_ERROR_B2Y,    //开始坐标
		PAGE_ERROR_B2W,PAGE_ERROR_B2H, //宽高
		
		{0x65,0x17,0x04,0x00,0xff,0xff,0xff},
		0		//默认0
	},
	  			   //t0控件
	{
		4,	   //id
		0,		//不支持触控
		
		PAGE_ERROR_TX,PAGE_ERROR_TY, //开始坐标
		PAGE_ERROR_TW,PAGE_ERROR_TH, //宽高
		
		{0},
		0		//默认0
	}

};

const u8* dialogStr[] =
{
	"确认",
	"取消",
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
	u16 color, bccolor;
	u16 i;
	show_bmp_in_flash(page_Confirm_item[0].start_pos_x,page_Confirm_item[0].start_pos_y,
		              bmp_Dialog_Page.width,bmp_Dialog_Page.height,bmp_Dialog_Page.addr);
	//画按键b0，b1
	color = POINT_COLOR;
	bccolor = BACK_COLOR;
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
		BACK_COLOR = GRAY;
		LCD_ShowString_hz16x16(page_Confirm_item[i].start_pos_x+20, page_Confirm_item[i].start_pos_y+7, 300, 16, 16, dialogStr[i - 1]);
	}	
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
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
	u16 color, bccolor;

	color = POINT_COLOR;
	bccolor = BACK_COLOR;

	POINT_COLOR = BLACK;
	BACK_COLOR = WHITE;
	LCD_ShowString_hz16x16(page_Confirm_item[3].start_pos_x+2, 
					page_Confirm_item[3].start_pos_y+2, 300, 16, 16, gPagePara.g_string[0]);
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
}

