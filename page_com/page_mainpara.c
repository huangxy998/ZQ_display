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


#define PAGE_SENSOR_L1			2
#define PAGE_SENSOR_L2			57
#define PAGE_SENSOR_L3			140
#define PAGE_SENSOR_L4			195
#define PAGE_SENSOR_L5			272
#define PAGE_SENSOR_L6			327
#define PAGE_SENSOR_H1			33
#define PAGE_SENSOR_H2			56
#define PAGE_SENSOR_H3			80
#define PAGE_SENSOR_H4			102
#define PAGE_SENSOR_H5			125
#define PAGE_SENSOR_H6			149
#define PAGE_SENSOR_H7			172
#define PAGE_SENSOR_H8			195
#define PAGE_SENSOR_WT     45
#define PAGE_SENSOR_WD     80
#define PAGE_SENSOR_H          19

#define PAGE_PARA_LIE1_X			4
#define PAGE_PARA_LIE2_X			90
#define PAGE_PARA_LIE3_X			135
#define PAGE_PARA_LIE4_X			216
#define PAGE_PARA_LIE5_X			264
#define PAGE_PARA_LIE6_X			350
#define PAGE_PARA_HANG1_Y		6
#define PAGE_PARA_HANG2_Y		31
#define PAGE_PARA_HANG3_Y		56
#define PAGE_PARA_HANG4_Y		81
#define PAGE_PARA_HANG5_Y		106
#define PAGE_PARA_HANG6_Y		131
#define PAGE_PARA_HANG7_Y		156
#define PAGE_PARA_HANG8_Y		181
#define PAGE_PARA_KEY_WIDTH    82
#define PAGE_PARA_KEY_HIGH     22
#define PAGE_PARA_DATA_WIDTH   42
#define PAGE_PARA_DATA_HIGH    20


static void pageMainParaInit(void);
static void pageMainParaUpdate(void);
static void pageMainParaItemUpdate(void);

///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_mainpara_item[] =
{
		             //b0控件
	{
		20,     //id
		1,      //支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG1_Y,        //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x02, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	            //b1控件
	{
		21,     //id
		1,      //支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG2_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x03, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //b2控件
	{
		22,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG3_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x04, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	            //b3控件
	{
		23,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG4_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x05, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //b4控件
	{
		24,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG5_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x06, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //b5控件
	{
		25,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG6_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x07, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	            //b6控件
	{
		26,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG7_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x08, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	{
		26,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG8_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x09, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //b7控件
	{
		27,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG1_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0a, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //b8控件
	{
		28,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG2_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0b, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //b9控件
	{
		29,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG3_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0c, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //n10控件
	{
		30,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG4_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0d, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	            //n11控件
	{
		31,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG5_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0e, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //n12控件
	{
		32,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG6_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x0f, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	             //n13控件
	{
		33,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG7_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x10, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	{
		33,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG8_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x11, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},
	             //n14控件
	{
		34,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG1_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x12, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //n15控件
	{
		35,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG2_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x13, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //n16控件
	{
		36,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG3_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x14, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //n17控件
	{
		37,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG4_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x15, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //n18控件
	{
		38,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG5_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x16, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},


	             //n19控件
	{
		39,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG6_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x17, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	{
		39,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG7_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x18, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},

	{
		39,     //id
		1,      //不支持触控
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG8_Y,    //开始坐标
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //宽高
		
		{0x65, 0x0e, 0x19, 0x00, 0xff, 0xff, 0xff},
		0       //默认0
	},
	             //
	{
		42,     //id
		1,      //支持触控
		
		32,202,    //开始坐标
		74,32 , //宽高
		
		{0x65,0x0e,0x32,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //控件
	{
		44,     //id
			1,      //支持触控
		
		130,202,    //开始坐标
		138,32 , //宽高
		
		{0x65,0x0e,0x33,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	      //控件
	{
		45,     //id
		1,      //支持触控
		
		294,202,    //开始坐标
		80,32 , //宽高
		
		{0x65,0x0e,0x34,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_mainpara =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_mainpara_item)/sizeof(PAGE_ITEM_T),
	
 	pageMainParaInit,	
 	pageMainParaUpdate
};

const _bmp_info bmp_mainpara_Page =
{
	BASIC_PAGE_MAIN_PARA_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};


static void pageMainParaInit(void)
{
	show_bmp_in_flash(0,0,bmp_mainpara_Page.width,bmp_mainpara_Page.height,bmp_mainpara_Page.addr);
}

//版本页面刷新
static void pageMainParaUpdate(void)
{
	
	u8 item;
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_mainpara.page_item_num; item++)
		{
			if(page_mainpara_item[item].touch_en)  //检查触控
			{
				if( ( touch_up_pos.x >= page_mainpara_item[item].start_pos_x ) && ( touch_up_pos.x < page_mainpara_item[item].start_pos_x + page_mainpara_item[item].width)  && \
					( touch_up_pos.y >= page_mainpara_item[item].start_pos_y ) && ( touch_up_pos.y < page_mainpara_item[item].start_pos_y + page_mainpara_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_mainpara_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageMainParaItemUpdate();   //页面刷新
	}
}

///////////////////////////////////////////////////////////
//显示更新
static void pageMainParaItemUpdate(void)
{
	int item;

	for(item = 0; item < 24; item++)
	{
		LCD_Fill(page_mainpara_item[item].start_pos_x, page_mainpara_item[item].start_pos_y,
			     page_mainpara_item[item].start_pos_x+page_mainpara_item[item].width-12,
			     page_mainpara_item[item].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_mainpara_item[item].start_pos_x, 
					page_mainpara_item[item].start_pos_y, page_mainpara_item[item].width, 16, 16, gPagePara.b_str[item]);
		LCD_Fill(page_mainpara_item[item].start_pos_x+86, page_mainpara_item[item].start_pos_y,
			     page_mainpara_item[item].start_pos_x+86+32,
			     page_mainpara_item[item].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_mainpara_item[item].start_pos_x+86, 
					page_mainpara_item[item].start_pos_y, 32, 16, 16, gPagePara.n_val[item]);
	}
}

