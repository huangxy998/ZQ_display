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


#include "page_define.h"
#include "char_model.h"
#include "page.h"
#include "touch.h"
#include "lcd_com.h"

#define PAGE_MAIN_BACK_COLOR    BLACK

PAGE_MAIN_PARA_T gPageMainPara;


static void pageBasicInit(void);
static void pageBasicUpdate(void);

static void pageBasicItemMode(void);
static void pageBasicItemSensity(void);



///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_basic_item[] =
{
	{  //模式
		0,	
		1,			//触控							
		160, 0,     //起始坐标
		96, 48,     //字符长宽
		pageBasicItemMode	//显示更新函数	
	},
	
	{  //灵敏度
		0,	
		1,			//触控							
		300, 0,     //起始坐标
		100, 22,    //字符长宽
		pageBasicItemMode	//显示更新函数	
	},
	
	{},
}

//页面结构体
const PAGE_S page_basic = 
{
		
	PAGE_ID_INIT,	
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_basic_item)/sizeof(PAGE_ITEM_T),
	
 	pageBasicInit,	
 	pageBasicUpdate
}

//////////////////////////////////////////////////////////
//智能 混点 分版 清点
const u8 page_item_func_name[4][2] = 
{
	{CM_48X48_ZHI40, CM_48X48_NENG20},
	{CM_48X48_HUN30, CM_48X48_DIAN30},
	{CM_48X48_FEN10, CM_48X48_BAN30},
	{CM_48X48_QING10,CM_48X48_DIAN30}	
};
//模式显示颜色
const u16 page_item_func_name_color[4] = 
{
	GREEN, BLUE, BROWN, RED 
};


//灵敏度颜色
const u16 page_item_sensity_color[3] =
{
	YELLOW, GREEN, RED
};

//低中高
const u8 page_item_DZG_name[4][3] = 
{
	{CM_16X16_SPACE, CM_16X16_SPACE,	CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_DI10,		CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_ZHONG10,  CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_GAO10,	CM_16X16_SPACE}
};

///////////////////////////////////////////////////////////
const _bmp_info bmp_mainPage =
{
	BASIC_PAGE_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

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

const _bmp_info bmp_menuPageProgressOn =
{
	MENU_PAGE_PROGRESSFULL_OFFSET - 5600,
	222,
	13
};

const _bmp_info bmp_menuPageSDOn =
{
	BASIC_PAGE_SD_ON_OFFSET - 5600,
	32,
	28
};

const _bmp_info bmp_menuPageSDOff =
{
	BASIC_PAGE_SD_OFF_OFFSET - 5600,
	32,
	28
};

const _bmp_info bmp_menuPageAddOn =
{
	BASIC_PAGE_ADD_ON_OFFSET - 5600,
	43,
	22
};

const _bmp_info bmp_menuPageAddOff =
{
	BASIC_PAGE_ADD_OFF_OFFSET - 5600,
	43,
	22
};


///////////////////////////////////////////////////////////
//基本页面初始化
static void pageBasicInit(void)
{
	show_bmp_in_flash(0,0,bmp_mainPage.width,bmp_mainPage.height,bmp_mainPage.addr);
}

//基本页面刷新
static void pageBasicUpdate(void)
{
	u8 item;

	for(item = 0; item < page_basic.page_item_num; item++)
	{
		if(page_basic_item.touch_en)
		{
			if(gPageInfo.toucged_down || gPageInfo.toucged_up)
			{
				if( ( touch_up_pos.x >= page_basic_item[item].start_pos_x ) && ( touch_up_pos.x < page_basic_item[item].start_pos_x + page_basic_item[item].width)  && \
					( touch_up_pos.y >= page_basic_item[item].start_pos_y ) && ( touch_up_pos.y < page_basic_item[item].start_pos_y + page_basic_item[item].height) )
				{
					page_basic_item.item_event();
				}
			}
		}
		else
		{
			page_basic_item.item_event();
		}
	}
}

///////////////////////////////////////////////////////////
//模式更新
static void pageBasicItemMode(void)
{
	if(gPageInfo.toucged_down)
	{
		LCD_Fill(page_basic_item[0].start_pos_x, page_basic_item[0].start_pos_y,
			page_basic_item[0].start_pos_x + page_basic_item[0].width, 
			page_basic_item[0].start_pos_y+ page_basic_item[0].height, PAGE_MAIN_BACK_COLOR);
	}
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.mode++;
		if(gPageMainPara.mode >= 4)
			gPageMainPara.mode = 0;
		LCD_SetFrontColor(page_item_func_name_color[gPageMainPara.mode]);  //字颜色
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);                            //背景颜色
		LCD_ShowHZ(	page_basic_item[0].start_pos_x, 
					page_basic_item[0].start_pos_y, 
					page_item_func_name[gPageMainPara.mode][0], 48, 0 );
		LCD_ShowHZ(	page_basic_item[0].start_pos_x, 
					page_basic_item[0].start_pos_y, 
					page_item_func_name[gPageMainPara.mode][1], 48, 0 );
	}
}

//灵敏度更新
static void pageBasicItemSensity(void)
{
	if(gPageInfo.toucged_down)
	{
		LCD_Fill(page_basic_item[1].start_pos_x + 45, page_basic_item[1].start_pos_y + 2,
			page_basic_item[1].start_pos_x + page_basic_item[1].width - 5, 
			page_basic_item[1].start_pos_y+ page_basic_item[1].height - 2, PAGE_MAIN_BACK_COLOR);
	}
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.sensity++;
		if(gPageMainPara.sensity >= 3)
			gPageMainPara.sensity = 0;

		LCD_Fill(page_basic_item[1].start_pos_x + 45, page_basic_item[1].start_pos_y + 2,
			page_basic_item[1].start_pos_x + page_basic_item[1].width - 5, 
			page_basic_item[1].start_pos_y+ page_basic_item[1].height - 2, page_item_sensity_color[gPageMainPara.sensity]);
	}
}

//预置数
static void pageBasicItemPreset(void)
{		
	u8 tmp_buff[8];
	
	if(gPageInfo.toucged_down)
	{
		if( gPageMainPara.pre_set >= 1000 )
		{
			sprintf(tmp_buff," %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 100 )
		{
			sprintf(tmp_buff,"  %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 10 )
		{
			sprintf(tmp_buff,"  %d  ", gPageMainPara.pre_set );
		}
		LCD_SetFrontColor(PAGE_MAIN_BACK_COLOR);  //字颜色
		LCD_SetBackColor(WHITE);                  //背景色
		LCD_SetFont(&Font8x16);
		LCD_DrawString(page_basic_item[2].start_pos_x + 45, page_basic_item[2].start_pos_y + 4, tmp_buff);
//		LCD_ShowString(page_basic_item[2].start_pos_x + 45, page_basic_item[2].start_pos_y + 4, 100, 16, 16, tmp_buff);
	}
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.pre_set += 10;
		if(gPageMainPara.sensity > 100)
			gPageMainPara.sensity = 0;
	
		if( gPageMainPara.pre_set >= 1000 )
		{
			sprintf(tmp_buff," %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 100 )
		{
			sprintf(tmp_buff,"  %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 10 )
		{
			sprintf(tmp_buff,"  %d  ", gPageMainPara.pre_set );
		}
		LCD_SetFrontColor(WHITE);  //字颜色
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
		
		LCD_SetFont(&Font8x16);
		LCD_DrawString(page_basic_item[2].start_pos_x + 45, page_basic_item[2].start_pos_y + 4, tmp_buff);
//		LCD_ShowString(page_basic_item[2].start_pos_x + 45, page_basic_item[1].start_pos_y + 4, 100, 16, 16, tmp_buff);
	}
}

//累加
static void pageBasicItemAdd(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.add_flg = !gPageMainPara.add_flg;
		if(gPageMainPara.add_flg)
		{
			show_bmp_in_flash(page_basic_item[3].start_pos_x, page_basic_item[3].start_pos_y, bmp_menuPageAddOn.width, bmp_menuPageAddOn.height, bmp_menuPageAddOn.addr);
		}
		else
		{
			show_bmp_in_flash(page_basic_item[3].start_pos_x, page_basic_item[3].start_pos_y, bmp_menuPageAddOff.width, bmp_menuPageAddOff.height, bmp_menuPageAddOff.addr);
		}
	}
}

//时间显示
static void pageBasicItemShowTime(void)
{
	u8 tmp_buff[24];
	
	sprintf(tmp_buff,"20%2d-%2d-%2d %2d:%2d:%2d", 
		calendar.w_year, calendar.w_month, calendar.w_date, 
		calendar.hour, calendar.min, calendar.sec);
	LCD_SetFont(&Font8x16);
	LCD_DrawString(page_basic_item[4].start_pos_x, page_basic_item[4].start_pos_y, tmp_buff);
}

//当触控logo时进入菜单界面
static void pageBasicItemEnterMenu(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MENU;     
	}
}

//当触控logo时进入菜单界面
static void pageBasicItemShowDenoCnt(void)
{

}


