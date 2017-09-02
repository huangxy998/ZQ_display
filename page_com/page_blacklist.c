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
#include "page_keyboard.h"


#ifdef LCD_SIZE_480X320
	#define PAGE_BLALKLIST_BL1      400
	#define PAGE_BLALKLIST_BH1      38
	#define PAGE_BLALKLIST_BH2      112
	#define PAGE_BLALKLIST_BH3      182
	#define PAGE_BLALKLIST_BH4      252

	#define PAGE_BLALKLIST_BW      74
	#define PAGE_BLALKLIST_BHH     64


	#define PAGE_BLALKLIST_SL1      2
	#define PAGE_BLALKLIST_SL2      54
	#define PAGE_BLALKLIST_SL3      190 
	#define PAGE_BLALKLIST_SL4      244

	#define PAGE_BLALKLIST_SH1      40
	#define PAGE_BLALKLIST_SH2      74
	#define PAGE_BLALKLIST_SH3      112
	#define PAGE_BLALKLIST_SH4      146
	#define PAGE_BLALKLIST_SH5      182
	#define PAGE_BLALKLIST_SH6      218
	#define PAGE_BLALKLIST_SH7      252
	#define PAGE_BLALKLIST_SH8      288

	#define PAGE_BLALKLIST_SW1      50
	#define PAGE_BLALKLIST_SHH1     26

	#define PAGE_BLALKLIST_SW2      128
	#define PAGE_BLALKLIST_SHH2     26
#else
	#define PAGE_BLALKLIST_BL1      328
	#define PAGE_BLALKLIST_BH1      28
	#define PAGE_BLALKLIST_BH2      82
	#define PAGE_BLALKLIST_BH3      136
	#define PAGE_BLALKLIST_BH4      190

	#define PAGE_BLALKLIST_BW      62
	#define PAGE_BLALKLIST_BHH     44


	#define PAGE_BLALKLIST_SL1      1
	#define PAGE_BLALKLIST_SL2      45
	#define PAGE_BLALKLIST_SL3      157 
	#define PAGE_BLALKLIST_SL4      204

	#define PAGE_BLALKLIST_SH1      30
	#define PAGE_BLALKLIST_SH2      56
	#define PAGE_BLALKLIST_SH3      84
	#define PAGE_BLALKLIST_SH4      112
	#define PAGE_BLALKLIST_SH5      138
	#define PAGE_BLALKLIST_SH6      164
	#define PAGE_BLALKLIST_SH7      192
	#define PAGE_BLALKLIST_SH8      218

	#define PAGE_BLALKLIST_SW1      42
	#define PAGE_BLALKLIST_SHH1     25

	#define PAGE_BLALKLIST_SW2      110
	#define PAGE_BLALKLIST_SHH2     25
#endif

typedef struct
{
	u8 curItem;
#if 0
	u8 preItem;
	u8 totalItem;
	u8 blackList[16][14];
#endif
}BLACKLIST_INFO;

BLACKLIST_INFO blackListInfo;
//static u8 prePage = 0;


static void pageBlacklistInit(void);
static void pageBlacklistUpdate(void);
static void pageBlackListItemUpdate(void);
static void pageBlackListTPUpdate(u8 item);
static u8 pageBlackListMakeReplyFrame(u8* buff);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_Blacklist_item[] =
{
	//n0
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH1,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n1
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH2,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n2
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH3,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n3
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH4,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n4
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH5,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n5
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH6,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n6
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH7,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n7
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL1,	PAGE_BLALKLIST_SH8,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n8
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH1,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n9
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH2,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n10
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH3,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n11
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH4,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n12
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH5,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n13
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH6,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n14
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH7,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//n15
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_SL3,	PAGE_BLALKLIST_SH8,
		PAGE_BLALKLIST_SW1, PAGE_BLALKLIST_SHH1,
		{0},
		0	//显示更新函数	
	},

	//t0
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH1,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t1
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH2,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t2
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH3,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t3
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH4,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t4
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH5,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t5
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH6,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t6
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH7,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		0	//显示更新函数	
	},

	//t7
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL2,	PAGE_BLALKLIST_SH8,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t8
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH1,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t9
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH2,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t10
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH3,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t11
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH4,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t12
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH5,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t13
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH6,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t14
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH7,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//t15
	{ 
		0,	
		0,			//触控							
		PAGE_BLALKLIST_SL4,	PAGE_BLALKLIST_SH8,
		PAGE_BLALKLIST_SW2, PAGE_BLALKLIST_SHH2,
		{0},
		0	//显示更新函数	
	},

	//b0
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH1,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0x65,0x04,0x02,0x00,0xff,0xff,0xff},
		0	//显示更新函数	
	},

	//b1
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH2,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0x65,0x04,0x23,0x00,0xff,0xff,0xff},
		0	//显示更新函数	
	},

	//b2
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH3,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0x65,0x04,0x22,0x00,0xff,0xff,0xff},
		0	//显示更新函数	
	},

	//b3
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH4,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0x65,0x04,0x24,0x00,0xff,0xff,0xff},
		0	//显示更新函数	
	},

	//g0   //按空白处退出
	{ 
		0,	
		1,			//触控							
		0,	0,
		LCD_HOR_SIZE, 35,
		{0x65,0x04,0x27,0x00,0xff,0xff,0xff},
		0	//显示更新函数	
	},
	
};

//页面结构体
const PAGE_T page_Blacklist =
{ 
	PAGE_ID_BLACKLIST,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T),
	
 	pageBlacklistInit,	
 	pageBlacklistUpdate
};

const _bmp_info bmp_Blacklist_Page =
{
	BASIC_PAGE_BLACK_LIST_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageBlacklistInit(void)
{

#if 0
	u8 i;
	if (gPageInfo.pre_page_idx != PAGE_ID_BLACKKEY)
	{
		memset(&keyBoardInfo, 0, sizeof(KEYBOARD_INFO));		
	}
	else if (blackListInfo.totalItem < 16)
	{
		if (keyBoardInfo.strUpdate == 1)
		{
			if (keyBoardInfo.buffLen > 12)
				keyBoardInfo.buffLen = 12;
			memcpy(gPagePara.t_string[blackListInfo.totalItem], keyBoardInfo.buff, keyBoardInfo.buffLen);
			gPagePara.t_string[blackListInfo.totalItem][keyBoardInfo.buffLen] = 0;
			memcpy(blackListInfo.blackList[blackListInfo.totalItem], keyBoardInfo.buff, keyBoardInfo.buffLen);
			blackListInfo.blackList[blackListInfo.totalItem][keyBoardInfo.buffLen] = 0;
			blackListInfo.totalItem++;
		}
	}
	if (blackListInfo.totalItem > 0)
	{
		for (i = 0; i < blackListInfo.totalItem; i++)
		{
			memcpy(gPagePara.t_string[i], blackListInfo.blackList[i], 12);
			sprintf((char*)gPagePara.n_val[i], "%d", i+1);
		}
		gPageInfo.need_update = 1;
	}
#endif
	show_bmp_in_flash(0,0,bmp_Blacklist_Page.width,bmp_Blacklist_Page.height,bmp_Blacklist_Page.addr);
//	prePage = gPageInfo.pre_page_idx;
}

static void pageBlacklistUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_Blacklist.page_item_num; item++)
		{
			if((page_Blacklist_item[item].touch_en))  //检查触控
			{			
				if( ( touch_up_pos.x >= page_Blacklist_item[item].start_pos_x ) && ( touch_up_pos.x < page_Blacklist_item[item].start_pos_x + page_Blacklist_item[item].width)	&& \
					( touch_up_pos.y >= page_Blacklist_item[item].start_pos_y ) && ( touch_up_pos.y < page_Blacklist_item[item].start_pos_y + page_Blacklist_item[item].height) )
				{
//					gIDInfo.cmdUpdate = 1;
//					memcpy(&gIDInfo.cmdPage.start, &page_Blacklist_item[item].com_data[0], TOUCH_CMD_LEN);
//					if (item < blackListInfo.totalItem )
					if (gPagePara.t_string[item][0] != 0)
					{
						blackListInfo.curItem = item;
					}
					pageBlackListTPUpdate(item);
					gPageInfo.need_update = 1;
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1) 
	{
		gPageInfo.need_update = 0;
		pageBlackListItemUpdate();	 //页面刷新
	}

	
}

static void pageBlackListItemUpdate(void)
{
	int j;
	for( j = 0; j < 16; j++ )
	{
		if (j == blackListInfo.curItem)
		{
			LCD_SetFrontColor(BLACK);
			LCD_SetBackColor(WHITE);
		}
		else
		{
			LCD_SetFrontColor(WHITE);
			LCD_SetBackColor(BLACK);
		}
		LCD_Fill(page_Blacklist_item[j].start_pos_x, page_Blacklist_item[j].start_pos_y,
				 page_Blacklist_item[j].start_pos_x+page_Blacklist_item[j].width-4,
				 page_Blacklist_item[j].start_pos_y+16, BLACK);
		LCD_ShowString(page_Blacklist_item[j].start_pos_x, 
			page_Blacklist_item[j].start_pos_y, 100, 16, 16, gPagePara.n_val[j]);
		LCD_Fill(page_Blacklist_item[j+16].start_pos_x, page_Blacklist_item[j+16].start_pos_y,
				 page_Blacklist_item[j+16].start_pos_x+page_Blacklist_item[j+16].width-4,
				 page_Blacklist_item[j+16].start_pos_y+16, BLACK);
		LCD_ShowString(page_Blacklist_item[j+16].start_pos_x, 
			page_Blacklist_item[j+16].start_pos_y, 100, 16, 16, gPagePara.t_string[j]);
	}
	LCD_SetFrontColor(WHITE);
	LCD_SetBackColor(BLACK);
}

static u8 buff[20];
static void pageBlackListTPUpdate(u8 item)
{
//	u8 i;
	switch(item)
	{
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-1://退出
			gPageInfo.cur_page_idx = PAGE_ID_MENU;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-2: //下页
			//继续执行
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-3: //上页
			gIDInfo.cmdUpdate = 1;
			memcpy(&gIDInfo.cmdPage.start, &page_Blacklist_item[item].com_data[0], TOUCH_CMD_LEN);
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-4://删除
		{
			u8 len;
			len = pageBlackListMakeReplyFrame(buff);
			uartSendbuffer(buff, len);
		}
		#if 0
			if (blackListInfo.totalItem > 0)
			{
				if (blackListInfo.curItem < blackListInfo.totalItem) //把后面的前移
				{
					for (i = blackListInfo.curItem; i < blackListInfo.totalItem; i++)
					{
						memcpy(gPagePara.t_string[i], gPagePara.t_string[i+1], 12);
						memcpy(blackListInfo.blackList[i], gPagePara.t_string[i], 12);
					}
					gPagePara.n_val[i-1][0] = 0;
					blackListInfo.totalItem--;
					if ((blackListInfo.totalItem > 0) && (blackListInfo.curItem >= blackListInfo.totalItem))
					{
						blackListInfo.curItem = blackListInfo.totalItem - 1;
					}
					pageBlacklistInit();
				}
			}
		#endif
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-5: //增加	
			{
				gPageInfo.cur_page_idx = PAGE_ID_BLACKKEY;
				memset(&gPagePara, 0, sizeof(page_para));
			}
			break;
		default:
			break;
	}
}

static u8 pageBlackListMakeReplyFrame(u8* buff)
{
	u8 i = 0;
	
	buff[i] = 0x90;   //帧头
	i++;
	buff[i] = 0x04;   //页面ID
	i++;
	buff[i] = 0x02;   //设置项
	i++;
	buff[i] = (u8)atoi((char*)gPagePara.n_val[blackListInfo.curItem]);
	i++;
	buff[i] = 0xff;
	i++;
	buff[i] = 0xff;
	i++;
	buff[i] = 0xff;
	i++;
	return i;
}


