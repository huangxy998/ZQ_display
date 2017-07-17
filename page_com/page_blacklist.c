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

#define PAGE_BLALKLIST_SH1      26
#define PAGE_BLALKLIST_SH2      52
#define PAGE_BLALKLIST_SH3      80
#define PAGE_BLALKLIST_SH4      108
#define PAGE_BLALKLIST_SH5      134
#define PAGE_BLALKLIST_SH6      160
#define PAGE_BLALKLIST_SH7      188
#define PAGE_BLALKLIST_SH8      214

#define PAGE_BLALKLIST_SW1      42
#define PAGE_BLALKLIST_SHH1     25

#define PAGE_BLALKLIST_SW2      110
#define PAGE_BLALKLIST_SHH2     25


typedef struct
{
	u8 curItem;
	u8 preItem;
	u8 totalItem;
	u8 blackList[16][14];
}BLACKLIST_INFO;

BLACKLIST_INFO blackListInfo;
static u8 prePage = 0;


static void pageBlacklistInit(void);
static void pageBlacklistUpdate(void);
static void pageBlackListItemUpdate(void);
static void pageBlackListTPUpdate(u8 item);



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
		{0},
		0	//显示更新函数	
	},

	//b1
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH2,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0},
		0	//显示更新函数	
	},

	//b2
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH3,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0},
		0	//显示更新函数	
	},

	//b3
	{ 
		0,	
		1,			//触控							
		PAGE_BLALKLIST_BL1,	PAGE_BLALKLIST_BH4,
		PAGE_BLALKLIST_BW, PAGE_BLALKLIST_BHH,
		{0},
		0	//显示更新函数	
	},

	//b4   //按空白处退出
	{ 
		0,	
		1,			//触控							
		0,	0,
		400, 16,
		{0},
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
	u8 i;
	if (gPageInfo.pre_page_idx != PAGE_ID_BLACKKEY)
	{
		memset(&keyBoardInfo, 0, sizeof(KEYBOARD_INFO));		
	}
	else if (blackListInfo.totalItem < 14)
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
			sprintf((char*)gPagePara.n_val[i], "%d", i);
		}
	}
	show_bmp_in_flash(0,0,bmp_Blacklist_Page.width,bmp_Blacklist_Page.height,bmp_Blacklist_Page.addr);
	prePage = gPageInfo.pre_page_idx;
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
					if (item < blackListInfo.totalItem )
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
		LCD_ShowString(page_Blacklist_item[j].start_pos_x, 
			page_Blacklist_item[j].start_pos_y, 100, 16, 16, gPagePara.n_val[j]);
		LCD_ShowString(page_Blacklist_item[j+16].start_pos_x-74, 
			page_Blacklist_item[j+16].start_pos_y, 100, 16, 16, gPagePara.t_string[j]);
	}
}

static void pageBlackListTPUpdate(u8 item)
{
	u8 i;
	switch(item)
	{
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-1://退出
			gPageInfo.cur_page_idx = PAGE_ID_MENU;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-2: //下页
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-3: //上页
			break;
		case sizeof(page_Blacklist_item)/sizeof(PAGE_ITEM_T)-4://删除
			if (blackListInfo.totalItem > 0)
			{
				if (blackListInfo.curItem < blackListInfo.totalItem - 1) //把后面的前移
				{
					for (i = blackListInfo.curItem; i < blackListInfo.totalItem; i++)
					{
						memcpy(gPagePara.t_string[blackListInfo.curItem], gPagePara.t_string[blackListInfo.curItem+1], 12);
						memcpy(blackListInfo.blackList[blackListInfo.curItem], gPagePara.t_string[blackListInfo.curItem], 12);
					}
					gPagePara.n_val[i][0] = 0;
					blackListInfo.totalItem--;
					pageBlacklistInit();
				}
			}
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

