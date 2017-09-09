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

static char showtime = 1;//当不编辑时间时进行时间实时显示
_calendar_obj datetime;


const u8 keytable[] = {
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
'Y', 'M', 'D', 'H', 'N', 'S', '<', 'B', 'C', '*',
};

const u8 xpos[] = {0, 12, 36, 48, 72, 84, 108, 120, 144, 156, 180, 192};

u8 buff[6][3] = {0};  //用于时间设置
u8 code[13] = {0};    //密码设置
u8 buffIdx = 0xff;    //指向正在设置的项
u8 dataIdx = 0;       //该项的正在设置的字符


#ifdef LCD_SIZE_480X320
	#define PAGE_CLOCKSET_L1		56
	#define PAGE_CLOCKSET_L2		124
	#define PAGE_CLOCKSET_L3		190
	#define PAGE_CLOCKSET_L4		300
	#define PAGE_CLOCKSET_L5		366

	#define PAGE_CLOCKSET_H1	  90
	#define PAGE_CLOCKSET_H2	  146
	#define PAGE_CLOCKSET_H3	  200
	#define PAGE_CLOCKSET_H4	  252

	#define PAGE_CLOCKSET_W     60
	#define PAGE_CLOCKSET_H     54
#else
	#define PAGE_CLOCKSET_L1		56
	#define PAGE_CLOCKSET_L2		110
	#define PAGE_CLOCKSET_L3		164
	#define PAGE_CLOCKSET_L4		251
	#define PAGE_CLOCKSET_L5		306

	#define PAGE_CLOCKSET_H1	  64
	#define PAGE_CLOCKSET_H2	  106
	#define PAGE_CLOCKSET_H3	  147
	#define PAGE_CLOCKSET_H4	  189

	#define PAGE_CLOCKSET_W     36
	#define PAGE_CLOCKSET_H     30
#endif

static void pageTimeSetInit(void);
static void pageTimeSetUpdate(void);
static void pageTimeItemUpdate(void);
static void pageTimeSetTouchUpdate(char item);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_TimeSet_item[] =
{
	             //t0控件
	{
		2,     //id
		0,      //不支持触控
		
		107,30,    //开始坐标
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
	showtime = 1;
	buffIdx = 0xff;
	show_bmp_in_flash(0,0,bmp_TimeSet_Page.width,bmp_TimeSet_Page.height,bmp_TimeSet_Page.addr);
}

static void pageTimeSetUpdate(void)
{
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
					gPageInfo.need_update = 1;
					pageTimeSetTouchUpdate(item - 1);
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

static void pageTimeSetTouchUpdate(char item)
{
	u16 bccolor = BACK_COLOR;
	if(item < 10) //为数字
	{
		if(buffIdx < 7)
		{
			if(buffIdx < 6)
			{
				if(dataIdx < 2)
				{
					buff[buffIdx][dataIdx] = keytable[item];
					dataIdx++;
				}
				switch(buffIdx)
				{
					case 0:datetime.w_year = 2000+atoi((char*)buff[0]);
						break;
					case 1:datetime.w_month = atoi((char*)buff[1]);
						break;
					case 2:datetime.w_date = atoi((char*)buff[2]);
						break;
					case 3:datetime.hour = atoi((char*)buff[3]);
						break;
					case 4:datetime.min = atoi((char*)buff[4]);
						break;
					case 5:datetime.sec = atoi((char*)buff[5]);
						break;
					default:break;
				}			
			}
			else
			{
				if(dataIdx < 12)
				{
					code[dataIdx] = keytable[item];
					dataIdx++;
				}
			}
		}
	}
	switch(keytable[item])
	{
		case 'Y':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 0;
			break;
		case 'M':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 1;
			break;
		case 'D':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 2;
			break;
		case 'H':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 3;
			break;
		case 'N':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 4;
			break;
		case 'S':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 5;
			break;
		case '<'://退格
			if(dataIdx > 0)
				dataIdx--;
			if(buffIdx == 6)
			{
				code[dataIdx] = 0;
			}
			break;
		case 'B'://返回
			gPageInfo.cur_page_idx = PAGE_ID_MAIN;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		case 'C'://确认
			if (buffIdx != 6)
			{
				showtime = 1;
				RTC_Set(datetime.w_year, datetime.w_month, datetime.w_date, 
					datetime.hour, datetime.min, datetime.sec);
			}
			break;
		case '*'://密码
			dataIdx = 0;
			buffIdx = 6;
			BACK_COLOR = WHITE;
			LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, "                    ");
			BACK_COLOR = bccolor;
			break;
		default:
			break;
	}
}

static void pageTimeItemUpdate(void)
{
	u8 i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	POINT_COLOR = BLACK;
	BACK_COLOR = LIGHTBLUE;
	if(buffIdx == 6)
	{
		showtime = 1;
		LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, "                    ");
		LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, code);
	}
	else
	{
		if(showtime)
		{
			Get_TimeStr(gPagePara.t_string[0]);
			buff[0][0] = gPagePara.t_string[0][2];
			buff[0][1] = gPagePara.t_string[0][3];
			buff[1][0] = gPagePara.t_string[0][5];
			buff[1][1] = gPagePara.t_string[0][6];
			buff[2][0] = gPagePara.t_string[0][8];
			buff[2][1] = gPagePara.t_string[0][9];
			buff[3][0] = gPagePara.t_string[0][11];
			buff[3][1] = gPagePara.t_string[0][12];
			buff[4][0] = gPagePara.t_string[0][14];
			buff[4][1] = gPagePara.t_string[0][15];
			buff[5][0] = gPagePara.t_string[0][17];
			buff[5][1] = gPagePara.t_string[0][18];	
			datetime.w_year = 2000+atoi((char*)buff[0]);
			datetime.w_month = atoi((char*)buff[1]);
			datetime.w_date = atoi((char*)buff[2]);
			datetime.hour = atoi((char*)buff[3]);
			datetime.min = atoi((char*)buff[4]);
			datetime.sec = atoi((char*)buff[5]);
			LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, gPagePara.t_string[0]);
		}
		else
		{
			for(i = 0; i < 12; i++)
			{
				if (((i>>1) == buffIdx) && (i%2 == dataIdx)) //选中的字符反色显示
				{
					POINT_COLOR = WHITE;
					BACK_COLOR = BLACK;
				}
				else
				{
					POINT_COLOR = BLACK;
					BACK_COLOR = LIGHTBLUE;
				}
				
				LCD_ShowChar(page_TimeSet_item[0].start_pos_x+24+xpos[i], page_TimeSet_item[0].start_pos_y,
					buff[i/2][i%2], 24, 0);
			}
		}
	}
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
}


