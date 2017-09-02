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
	#define PAGE_SENSOR_L1			4
	#define PAGE_SENSOR_L2			72
	#define PAGE_SENSOR_L3			176
	#define PAGE_SENSOR_L4			236
	#define PAGE_SENSOR_L5			332
	#define PAGE_SENSOR_L6			396
	#define PAGE_SENSOR_H1			44
	#define PAGE_SENSOR_H2			76
	#define PAGE_SENSOR_H3			106
	#define PAGE_SENSOR_H4			136
	#define PAGE_SENSOR_H5			166
	#define PAGE_SENSOR_H6			196
	#define PAGE_SENSOR_H7			228
	#define PAGE_SENSOR_H8			258
	#define PAGE_SENSOR_WT     62
	#define PAGE_SENSOR_WD     96
	#define PAGE_SENSOR_H      24
	
	#define PAGE_SENSOR_BH1      264
	#define PAGE_SENSOR_BL1      196
	#define PAGE_SENSOR_BL2      332
	#define PAGE_SENSOR_BW       114
	#define PAGE_SENSOR_BH       48
	
#else
	#define PAGE_SENSOR_L1			8
	#define PAGE_SENSOR_L2			57
	#define PAGE_SENSOR_L3			140
	#define PAGE_SENSOR_L4			195
	#define PAGE_SENSOR_L5			272
	#define PAGE_SENSOR_L6			326
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
	
	#define PAGE_SENSOR_BH1      198
	#define PAGE_SENSOR_BL1      169
	#define PAGE_SENSOR_BL2      279
	#define PAGE_SENSOR_BW       88
	#define PAGE_SENSOR_BH       34
#endif

static void pageParaSetInit(void);
static void pageParaSetUpdate(void);
static void pageParaSetItemUpdate(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_ParaSet_item[] =
{
	             //t0控件
	{
		2,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H1,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t1控件
	{
		3,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H2,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	             //t2控件
	{
		4,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H3,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t3控件
	{
		5,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H4,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	             //t4控件
	{
		6,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H5,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	           //t5控件
	{
		7,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H6,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	            //t6控件
	{
		8,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H7,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t7控件
	{
		9,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L2,PAGE_SENSOR_H8,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t8控件
	{
		10,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H1,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	             //t9控件
	{
		11,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H2,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	             //t10控件
	{
		12,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H3,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t11控件
	{
		13,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H4,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t12控件
	{
		14,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H5,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t13控件
	{
		15,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H6,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t14控件
	{
		16,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L4,PAGE_SENSOR_H7,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t15控件
	{
		17,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H1,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t16控件
	{
		18,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H2,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t17控件
	{
		19,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H3,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t18控件
	{
		20,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H4,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t19控件
	{
		21,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H5,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t20控件
	{
		22,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H6,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //t21控件
	{
		23,     //id
		0,      //不支持触控
		
		PAGE_SENSOR_L6,PAGE_SENSOR_H7,    //开始坐标
		PAGE_SENSOR_WD,PAGE_SENSOR_H , //宽高
		
		{0},
		0       //默认0
	},
	              //b0控件
	{
		46,     //id
		1,      //支持触控
		
		PAGE_SENSOR_BL1,PAGE_SENSOR_BH1,    //开始坐标
		PAGE_SENSOR_BW,PAGE_SENSOR_BH, //宽高
		
		{0x65,0x0d,0x2e,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	          //b1控件
	{
		47,     //id
		1,      //支持触控
		
		PAGE_SENSOR_BL2,PAGE_SENSOR_BH1,    //开始坐标
		PAGE_SENSOR_BW,PAGE_SENSOR_BH, //宽高
		
		{0x65,0x0d,0x2f,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_ParaSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_ParaSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageParaSetInit,	
 	pageParaSetUpdate
};

const _bmp_info bmp_ParaSet_Page =
{
	BASIC_PAGE_PARA_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageParaSetInit(void)
{
	show_bmp_in_flash(0,0,bmp_ParaSet_Page.width,bmp_ParaSet_Page.height,bmp_ParaSet_Page.addr);
}

static void pageParaSetUpdate(void)
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
		for(item = 0; item < page_ParaSet.page_item_num; item++)
		{
			if((page_ParaSet_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_ParaSet_item[item].start_pos_x ) && ( touch_up_pos.x < page_ParaSet_item[item].start_pos_x + page_ParaSet_item[item].width)  && \
					( touch_up_pos.y >= page_ParaSet_item[item].start_pos_y ) && ( touch_up_pos.y < page_ParaSet_item[item].start_pos_y + page_ParaSet_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_ParaSet_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageParaSetItemUpdate();   //页面刷新
	}
	
}

static void pageParaSetItemUpdate(void)
{
	int item = 0;

	for(item = 0; item < 22; item++)
	{
		LCD_ShowString(page_ParaSet_item[item].start_pos_x, 
					page_ParaSet_item[item].start_pos_y, 100, 16, 16, gPagePara.t_string[item]);
	}
	for(; item < 44; item++)
	{
		LCD_ShowString(page_ParaSet_item[item-22].start_pos_x - (PAGE_SENSOR_WT+8), 
					page_ParaSet_item[item-22].start_pos_y, 100, 16, 16, gPagePara.t_string[item]);
	}
}


