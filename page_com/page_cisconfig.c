#include<string.h>
#include <stdlib.h>

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
	#define PAGE_CISS_LIE1_X			6
	#define PAGE_CISS_LIE2_X			96
	#define PAGE_CISS_LIE3_X			172
	#define PAGE_CISS_LIE4_X			256
	#define PAGE_CISS_LIE5_X			330
	#define PAGE_CISS_LIE6_X			414
	#define PAGE_CISS_HANG1_Y		32
	#define PAGE_CISS_HANG2_Y		60
	#define PAGE_CISS_HANG3_Y		86
	#define PAGE_CISS_HANG4_Y		112
	#define PAGE_CISS_HANG5_Y		138
	#define PAGE_CISS_HANG6_Y		166
	#define PAGE_CISS_HANG7_Y		190
	#define PAGE_CISS_HANG8_Y		218
	#define PAGE_CISS_KEY_WIDTH    78
	#define PAGE_CISS_KEY_HIGH     22
	#define PAGE_CISS_DATA_WIDTH   68
	#define PAGE_CISS_DATA_HIGH    22
	
	#define PAGE_CISS_BH1          278
	#define PAGE_CISS_BL1          64
	#define PAGE_CISS_BL2          198
	#define PAGE_CISS_BL3          338	
	#define PAGE_CISS_BW           82
	#define PAGE_CISS_BH           40
	
	#define PAGE_CISS_BJX          104
	#define PAGE_CISS_BJY          249	
	#define PAGE_CISS_BJW           261
	#define PAGE_CISS_BJH           14
	
	#define PAGE_CISS_BTX          380
	#define PAGE_CISS_BTY          242	
	#define PAGE_CISS_BTW           95
	#define PAGE_CISS_BTH           24
#else
	#define PAGE_CISS_LIE1_X			4
	#define PAGE_CISS_LIE2_X			80
	#define PAGE_CISS_LIE3_X			135
	#define PAGE_CISS_LIE4_X			212
	#define PAGE_CISS_LIE5_X			267
	#define PAGE_CISS_LIE6_X			345
	#define PAGE_CISS_HANG1_Y		22
	#define PAGE_CISS_HANG2_Y		42
	#define PAGE_CISS_HANG3_Y		62
	#define PAGE_CISS_HANG4_Y		82
	#define PAGE_CISS_HANG5_Y		102
	#define PAGE_CISS_HANG6_Y		122
	#define PAGE_CISS_HANG7_Y		142
	#define PAGE_CISS_HANG8_Y		162
	#define PAGE_CISS_KEY_WIDTH    70
	#define PAGE_CISS_KEY_HIGH     20
	#define PAGE_CISS_DATA_WIDTH   52
	#define PAGE_CISS_DATA_HIGH    20
	
	#define PAGE_CISS_BH1          209		
	#define PAGE_CISS_BL1          61
	#define PAGE_CISS_BL2          166
	#define PAGE_CISS_BL3          279	
	#define PAGE_CISS_BW           66
	#define PAGE_CISS_BH           30
	
	#define PAGE_CISS_BJX          104
	#define PAGE_CISS_BJY          179	
	#define PAGE_CISS_BJW           222
	#define PAGE_CISS_BJH           13
	
	#define PAGE_CISS_BTX          310
	#define PAGE_CISS_BTY          185	
	#define PAGE_CISS_BTW           85
	#define PAGE_CISS_BTH           17

#endif

static void pageCISConfigInit(void);
static void pageCISConfigUpdate(void);
static void pageCISConfigItemUpdate(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_CISConfig_item[] =
{
	             //n0控件
	{
		20,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG1_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	            //n1控件
	{
		21,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG2_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n2控件
	{
		22,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG3_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	            //n3控件
	{
		23,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG4_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n4控件
	{
		24,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG5_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n5控件
	{
		25,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG6_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	            //n6控件
	{
		26,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG7_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	{
		26,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE2_X,PAGE_CISS_HANG8_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n7控件
	{
		27,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG1_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n8控件
	{
		28,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG2_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n9控件
	{
		29,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG3_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n10控件
	{
		30,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG4_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	            //n11控件
	{
		31,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG5_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n12控件
	{
		32,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG6_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	             //n13控件
	{
		33,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG7_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	{
		33,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE4_X,PAGE_CISS_HANG8_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},
	             //n14控件
	{
		34,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG1_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n15控件
	{
		35,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG2_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n16控件
	{
		36,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG3_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n17控件
	{
		37,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG4_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n18控件
	{
		38,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG5_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},


	             //n19控件
	{
		39,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG6_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	{
		39,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG7_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},

	{
		39,     //id
		0,      //不支持触控
		
		PAGE_CISS_LIE6_X,PAGE_CISS_HANG8_Y,    //开始坐标
		PAGE_CISS_DATA_WIDTH,PAGE_CISS_DATA_HIGH , //宽高
		
		{0},
		0       //默认0
	},
	            //j0控件
	{
		40,     //id
		0,      //不支持触控
		
		PAGE_CISS_BJX,PAGE_CISS_BJY,    //开始坐标
		PAGE_CISS_BJW,PAGE_CISS_BJH , //宽高
		
		{0},
		0       //默认0
	},

	             //t0控件
	{
		41,     //id
		0,      //不支持触控
		
		PAGE_CISS_BTX,PAGE_CISS_BTY,    //开始坐标
		PAGE_CISS_BTW,PAGE_CISS_BTH , //宽高
		
		{0},
		0       //默认0
	},

	             //b1控件
	{
		42,     //id
		1,      //支持触控
		
		PAGE_CISS_BL1,PAGE_CISS_BH1,    //开始坐标
		PAGE_CISS_BW,PAGE_CISS_BH , //宽高
		
		{0x65,0x07,0x03,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //b3控件
	{
		44,     //id
			1,      //支持触控
		
		PAGE_CISS_BL2,PAGE_CISS_BH1,    //开始坐标
		PAGE_CISS_BW,PAGE_CISS_BH , //宽高
		
		{0x65,0x07,0x05,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //b0控件
	{
		45,     //id
		1,      //支持触控
		
		PAGE_CISS_BL3,PAGE_CISS_BH1,    //开始坐标
		PAGE_CISS_BW,PAGE_CISS_BH , //宽高
		
		{0x65,0x07,0x01,0x00,0xff,0xff,0xff},
		0       //默认0
	}
};

//页面结构体
const PAGE_T page_CISConfig =
{ 
	PAGE_ID_CISSET1,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_CISConfig_item)/sizeof(PAGE_ITEM_T),
	
 	pageCISConfigInit,	
 	pageCISConfigUpdate
};

const _bmp_info bmp_CISConfig_Page =
{
	BASIC_PAGE_CIS_PARA_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};
#ifndef LCD_SIZE_480X320
const _bmp_info bmp_progress_none =
{
	MENU_PAGE_PROGRESS_OFFSET,
	222,
	13
};

const _bmp_info bmp_progress_percent =
{
	MENU_PAGE_PROGRESSFULL_OFFSET,
	222,
	13
};
#endif
static u8 progress_show = 0;

static void pageCISConfigInit(void)
{
	show_bmp_in_flash(0,0,bmp_CISConfig_Page.width,bmp_CISConfig_Page.height,bmp_CISConfig_Page.addr);
	progress_show = 0;
}

static void pageCISConfigUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_CISConfig.page_item_num; item++)
		{
			if((page_CISConfig_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_CISConfig_item[item].start_pos_x ) && ( touch_up_pos.x < page_CISConfig_item[item].start_pos_x + page_CISConfig_item[item].width)  && \
					( touch_up_pos.y >= page_CISConfig_item[item].start_pos_y ) && ( touch_up_pos.y < page_CISConfig_item[item].start_pos_y + page_CISConfig_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_CISConfig_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1) 
	{
		gPageInfo.need_update = 0;
		pageCISConfigItemUpdate();   //页面刷新
	}
	
}

///////////////////////////////////////////////////////////
//显示更新
static void pageCISConfigItemUpdate(void)
{	
	int j = 0;
	
	for( j = 0; j < 24; j++ )
	{
		LCD_ShowString(page_CISConfig_item[j].start_pos_x, 
			page_CISConfig_item[j].start_pos_y, 100, 16, 16, "    ");
		LCD_ShowString(page_CISConfig_item[j].start_pos_x, 
			page_CISConfig_item[j].start_pos_y, 100, 16, 16, gPagePara.n_val[j]);
		LCD_ShowString_hz16x16(page_CISConfig_item[j].start_pos_x-74, 
			page_CISConfig_item[j].start_pos_y, 100, 16, 16, gPagePara.b_str[j+4]);
	}
	LCD_Fill(page_CISConfig_item[25].start_pos_x, page_CISConfig_item[25].start_pos_y,
			     page_CISConfig_item[25].start_pos_x+page_CISConfig_item[25].width-4,
			     page_CISConfig_item[25].start_pos_y+16, BLACK);
	LCD_ShowString_hz16x16(page_CISConfig_item[25].start_pos_x, 
			page_CISConfig_item[25].start_pos_y, page_CISConfig_item[25].width, 16, 16, gPagePara.t_string[0]);
	if(gPagePara.j_percent[0][1] != 0)
	{
		static int valtmp = 0;
		int value = 0;
		
		if(progress_show == 0)
		{
			progress_show = 1;
			valtmp = 0;
		#ifdef LCD_SIZE_480X320
			LCD_Fill(page_CISConfig_item[24].start_pos_x, page_CISConfig_item[24].start_pos_y,
			     page_CISConfig_item[24].start_pos_x+page_CISConfig_item[24].width,
			     page_CISConfig_item[24].start_pos_y+page_CISConfig_item[24].height, WHITE);
		#else
			show_bmp_in_flash(84,187,bmp_progress_none.width,bmp_progress_none.height,bmp_progress_none.addr);
		#endif
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
			#ifdef LCD_SIZE_480X320
				LCD_Fill(page_CISConfig_item[24].start_pos_x, page_CISConfig_item[24].start_pos_y+2,
			     page_CISConfig_item[24].start_pos_x+(page_CISConfig_item[24].width*value)/100,
			     page_CISConfig_item[24].start_pos_y+page_CISConfig_item[24].height-2, GREEN);
			#else
				show_bmp_in_flash(84,187,(bmp_progress_percent.width*value)/100,bmp_progress_percent.height,bmp_progress_percent.addr);
			#endif
			}
		}
	}
}

