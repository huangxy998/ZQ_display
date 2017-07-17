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

u8 pressed = 0;

const _bmp_info bmp_menuPageOff =
{
	MENU_PAGE_UP_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

const _bmp_info bmp_menuPageOn =
{
	MENU_PAGE_DOWN_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageMenuInit(void);
static void pageMenuUpdate(void);
static void pageMenuItemVersion(void);
static void pageMenuItemBlacklist(void);
static void pageMenuItemPictureSet(void);
static void pageMenuItemSerial(void);
static void pageMenuItemSystem(void);
static void pageMenuItemTime(void);
static void pageMenuItemUpdate(void);
static void pageMenuItemNetSet(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_menu_item[] =
{
	{  //模式
		0,	
		1,			//触控							
		6, 22,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x01,0x00,0xff,0xff,0xff},
		pageMenuItemVersion	//显示更新函数	
	},

	{  //模式
		1,	
		1,			//触控							
		110, 22,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x02,0x00,0xff,0xff,0xff},
		pageMenuItemBlacklist//显示更新函数	
	},

	{  //模式
		2,	
		1,			//触控							
		214, 22,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x04,0x00,0xff,0xff,0xff},
		pageMenuItemPictureSet//显示更新函数	
	},

	{  //模式
		3,	
		1,			//触控							
		320, 22,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x05,0x00,0xff,0xff,0xff},
		pageMenuItemUpdate//显示更新函数	
	},

	{  //模式
		4,	
		1,			//触控							
		6, 128,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x03,0x00,0xff,0xff,0xff},
		pageMenuItemNetSet//显示更新函数	
	},

	{  //模式
		5,	
		1,			//触控							
		110, 128,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x06,0x00,0xff,0xff,0xff},
		pageMenuItemSerial//显示更新函数	
	},

	{  //模式
		6,	
		1,			//触控							
		214, 128,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x07,0x00,0xff,0xff,0xff},
		pageMenuItemSystem//显示更新函数	
	},

	{  //模式
		7,	
		1,			//触控							
		320, 128,     //起始坐标
		76, 92,     //字符长宽
		{0x65,0x03,0x08,0x00,0xff,0xff,0xff},
		pageMenuItemTime//显示更新函数	
	},
};

const PAGE_ITEM_T g0=             //g0控件
{
	9,     //id
	0,      //不支持触控
  0,220,   //开始坐标
	400,20,//宽高
	
	{0},
	0       //默认0
};


//页面结构体
const PAGE_T page_menu =
{ 
	PAGE_ID_MAIN,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_menu_item)/sizeof(PAGE_ITEM_T),
	
 	pageMenuInit,	
 	pageMenuUpdate
};

static void pageMenuInit(void)
{
	show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
}

static void pageMenuUpdate(void)
{
	u8 item;
	u8 pressvalid = 0;
	static u8 preitem = 0xff; //解决按下反复刷新闪烁问题

	for(item = 0; item < page_menu.page_item_num; item++)
	{
		if(page_menu_item[item].touch_en)
		{
			if(gPageInfo.toucged_down || gPageInfo.toucged_up)
			{
				if( ( touch_up_pos.x >= page_menu_item[item].start_pos_x ) && ( touch_up_pos.x < page_menu_item[item].start_pos_x + page_menu_item[item].width)  && \
					( touch_up_pos.y >= page_menu_item[item].start_pos_y ) && ( touch_up_pos.y < page_menu_item[item].start_pos_y + page_menu_item[item].height) )
				{
					if(preitem != item)
					{
						preitem = item;
						pressed = 0;
					}
					page_menu_item[item].item_event();
					pressvalid = 1;
					break;
				}
			}
		}
		else
		{
			page_menu_item[item].item_event();
		}
	}
	if(gPageInfo.toucged_up) 
	{
		if(pressvalid == 0)//按空白处退出菜单
		{
//			gPageInfo.cur_page_idx = PAGE_ID_STANDTIME;
				gIDInfo.cmdUpdate = 1;
				gIDInfo.cmdPage.touchStatus = 0;
				gIDInfo.cmdPage.btnID = 0;
				gIDInfo.cmdPage.pageID = PAGE_ID_MAIN;
		}
		pressed = 0;
		preitem = 0xff;
	}
	LCD_ShowString(g0.start_pos_x, g0.start_pos_y, 300, 16, 16, gPagePara.g_string[0]);
}

static void pageMenuItemVersion(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
			pressed = 1;
			show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
			show_pressed_icon_in_flash( page_menu_item[0].start_pos_x, page_menu_item[0].start_pos_y,
			page_menu_item[0].width,  page_menu_item[0].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[0].com_data[0], TOUCH_CMD_LEN);

	}	
}

static void pageMenuItemBlacklist(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[1].start_pos_x, page_menu_item[1].start_pos_y,
			 page_menu_item[1].width,  page_menu_item[1].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_BLACKLIST;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_BLACKLIST;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[1].com_data[0], TOUCH_CMD_LEN);
		gPageInfo.cur_page_idx = PAGE_ID_BLACKLIST;
		memset(&gPagePara, 0, sizeof(page_para));


	}	
}

static void pageMenuItemPictureSet(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[2].start_pos_x, page_menu_item[2].start_pos_y,
			 page_menu_item[2].width,  page_menu_item[2].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
	gIDInfo.cmdUpdate = 1;
//	gIDInfo.cmdPage.touchStatus = PAGE_ID_BLACKLIST;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[2].com_data[0], TOUCH_CMD_LEN);

	}	
}

static void pageMenuItemUpdate(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[3].start_pos_x, page_menu_item[3].start_pos_y,
			 page_menu_item[3].width,  page_menu_item[3].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_SYSUPDATA;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[3].com_data[0], TOUCH_CMD_LEN);

	}	
}

static void pageMenuItemNetSet(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[4].start_pos_x, page_menu_item[4].start_pos_y,
			 page_menu_item[4].width,  page_menu_item[4].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_NETSET;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[4].com_data[0], TOUCH_CMD_LEN);
		gPageInfo.cur_page_idx = PAGE_ID_NETSET;
		memset(&gPagePara, 0, sizeof(page_para));

	}	
}

static void pageMenuItemSerial(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[5].start_pos_x, page_menu_item[5].start_pos_y,
			 page_menu_item[5].width,  page_menu_item[5].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_GZHMDIS;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[5].com_data[0], TOUCH_CMD_LEN);

	}	
}

static void pageMenuItemSystem(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[6].start_pos_x, page_menu_item[6].start_pos_y,
			 page_menu_item[6].width,  page_menu_item[6].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_SYSEMSET;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[6].com_data[0], TOUCH_CMD_LEN);

	}	
}

static void pageMenuItemTime(void)
{
	if ((gPageInfo.toucged_down) && (pressed == 0))
	{
		pressed = 1;
		show_bmp_in_flash(0,0,bmp_menuPageOff.width,bmp_menuPageOff.height,bmp_menuPageOff.addr);
		show_pressed_icon_in_flash( page_menu_item[7].start_pos_x, page_menu_item[7].start_pos_y,
			 page_menu_item[7].width,  page_menu_item[7].height, MENU_PAGE_DOWN_OFFSET );
	}
	else if (gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_VERSION;
		gIDInfo.cmdUpdate = 1;
//		gIDInfo.cmdPage.touchStatus = PAGE_ID_CLOCKDISP;
		memcpy(&gIDInfo.cmdPage.start, &page_menu_item[7].com_data[0], TOUCH_CMD_LEN);
	}	
}



