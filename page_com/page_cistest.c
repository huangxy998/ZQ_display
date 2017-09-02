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
	#define PAGE_CIS_TEST_L1    62
	#define PAGE_CIS_TEST_L2    260

	#define PAGE_CIS_TEST_H1    84
	#define PAGE_CIS_TEST_H2    158
	#define PAGE_CIS_TEST_H3    228

	#define PAGE_CIS_TEST_LW    138
	#define PAGE_CIS_TEST_HH    40

	const u8 *test_table[] =
	{
		"红光检测",
		"紫外检测",
		"绿光检测",
		"红外检测",
		"蓝光检测",
		"CIS校正",
	};
#else
	#define PAGE_CIS_TEST_L1    42
	#define PAGE_CIS_TEST_L2    224

	#define PAGE_CIS_TEST_H1    58
	#define PAGE_CIS_TEST_H2    120
	#define PAGE_CIS_TEST_H3    180

	#define PAGE_CIS_TEST_LW    134
	#define PAGE_CIS_TEST_HH    38
#endif
static void page_CISTestInit(void);
static void page_CISTestUpdate(void);

//////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_CISTest_item[] =
{
	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L1,	PAGE_CIS_TEST_H1,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x01, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},

	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L2,	PAGE_CIS_TEST_H1,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x02, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},

	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L1,	PAGE_CIS_TEST_H2,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x03, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},

	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L2,	PAGE_CIS_TEST_H2,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x04, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},

	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L1,	PAGE_CIS_TEST_H3,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x05, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},

	{ 
		0,	
		1,			//触控							
		PAGE_CIS_TEST_L2,	PAGE_CIS_TEST_H3,
		PAGE_CIS_TEST_LW, PAGE_CIS_TEST_HH,
		{0x65, 0x06, 0x06, 0x00, 0xff, 0xff, 0xff },
		0	//显示更新函数	
	},
};

//页面结构体
const PAGE_T page_CISTest =
{ 
	PAGE_ID_CISCHEK,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_CISTest_item)/sizeof(PAGE_ITEM_T),
	
 	page_CISTestInit,	
 	page_CISTestUpdate
};

#ifdef LCD_SIZE_480X320
	const _bmp_info bmp_CISTest_Page =
	{
		BASIC_PAGE_SINGLE_BUTTON_OFFSET,
		152,
		52
	};
#else
	const _bmp_info bmp_CISTest_Page =
	{
		BASIC_PAGE_CIS_TEST_OFFSET,
		LCD_HOR_SIZE,
		LCD_VER_SIZE
	};
#endif

static void page_CISTestInit(void)
{
#ifdef LCD_SIZE_480X320
	u8 i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	LCD_Clear(BLACK);
	LCD_ShowString_hz24x24(174,26,200,24,24,"CIS光源检测");
	POINT_COLOR = BRRED;
	BACK_COLOR = SEABLUE;
	for (i = 0; i < 6; i++)
	{
		show_bmp_in_flash(page_CISTest_item[i].start_pos_x,page_CISTest_item[i].start_pos_y,bmp_CISTest_Page.width,bmp_CISTest_Page.height,bmp_CISTest_Page.addr);
		LCD_ShowString_hz24x24(page_CISTest_item[i].start_pos_x+5,page_CISTest_item[i].start_pos_y+page_CISTest_item[i].height/2-16,
			bmp_CISTest_Page.width,24,24,test_table[i]);
	}
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
#else
	show_bmp_in_flash(0,0,bmp_CISTest_Page.width,bmp_CISTest_Page.height,bmp_CISTest_Page.addr);
#endif
}

static void page_CISTestUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_CISTest.page_item_num; item++)
		{
			if((page_CISTest_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_CISTest_item[item].start_pos_x ) && ( touch_up_pos.x < page_CISTest_item[item].start_pos_x + page_CISTest_item[item].width)	&& \
					( touch_up_pos.y >= page_CISTest_item[item].start_pos_y ) && ( touch_up_pos.y < page_CISTest_item[item].start_pos_y + page_CISTest_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_CISTest_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}	
}

