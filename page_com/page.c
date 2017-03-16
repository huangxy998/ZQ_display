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

#define PAGE_MAIN_BACK_COLOR    BLACK

PAGE_MAIN_PARA_T gPageMainPara;


static void pageBasicInit(void);
static void pageBasicUpdate(void);

static void pageBasicItemMode(void);
static void pageBasicItemSensity(void);
static void pageBasicItemPreset(void);
static void pageBasicItemAdd(void);
static void pageBasicItemShowDenoCnt(void);
static void pageBasicItemEnterMenu(void);
static void pageBasicItemShowTime(void);
static void pageBasicItemShowCurCnt(void);
static void pageBasicItemShowCnt(void);
static void pageBasicItemShowSum(void);
static void pageBasicItemShowSDStatus(void);
static void pageBasicItemShowNetStatus(void);
static void pageBasicItemShowSerialNum(void);


///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_basic_item[] =
{
	{  //模式
		BASIC_ITEM_MODE,	
		1,			//触控							
		160, 0,     //起始坐标
		96, 48,     //字符长宽
		pageBasicItemMode	//显示更新函数	
	},
	
	{  //灵敏度
		BASIC_ITEM_SENSITY,	
		1,			//触控							
		300, 0,     //起始坐标
		100, 22,    //字符长宽
		pageBasicItemSensity	//显示更新函数	
	},

	{  //预置
		BASIC_ITEM_PRESET,	
		1,			//触控							
		300, 25,     //起始坐标
		100, 22,    //字符长宽
		pageBasicItemPreset	//显示更新函数	
	},
	
	{
		//累加开关
		BASIC_ITEM_ADD,	
		1,			//触控							
		5, 124,     //起始坐标
		43, 22,     //字符长宽
		pageBasicItemAdd //显示更新函数
	},

	{
		//进入菜单
		BASIC_ITEM_MENU,	
		1,			//触控							
		0, 0,     //起始坐标
		120, 50,     //字符长宽
		pageBasicItemEnterMenu //显示更新函数
	},

	{
		//时间显示
		BASIC_ITEM_TIME,	
		0,			//触控无							
		56, 218,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowTime //显示更新函数
	},

	{
		//面额计数
		BASIC_ITEM_DENO,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowDenoCnt //显示更新函数
	},

	{
		//当前计数
		BASIC_ITEM_CUR_CNT,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowCurCnt //显示更新函数
	},

	{
		//上次计数
		BASIC_ITEM_CNT,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowCnt //显示更新函数
	},

	{
		//金额
		BASIC_ITEM_SUM,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowSum //显示更新函数
	},

	{
		//金额
		BASIC_ITEM_SERIAL,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowSerialNum //显示更新函数
	},

	{
		//金额
		BASIC_ITEM_NET,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowNetStatus //显示更新函数
	},

	{
		//金额
		BASIC_ITEM_SD,	
		0,			//触控无							
		42, 52,     //起始坐标
		400, 20,     //字符长宽
		pageBasicItemShowSDStatus //显示更新函数
	},
	
};

//页面结构体
const PAGE_T page_basic = 
{
		
	PAGE_ID_BASIC,	
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_basic_item)/sizeof(PAGE_ITEM_T),
	
 	pageBasicInit,	
 	pageBasicUpdate
};

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
		if(page_basic_item[item].touch_en)
		{
			if(gPageInfo.toucged_down || gPageInfo.toucged_up)
			{
				if( ( touch_up_pos.x >= page_basic_item[item].start_pos_x ) && ( touch_up_pos.x < page_basic_item[item].start_pos_x + page_basic_item[item].width)  && \
					( touch_up_pos.y >= page_basic_item[item].start_pos_y ) && ( touch_up_pos.y < page_basic_item[item].start_pos_y + page_basic_item[item].height) )
				{
					page_basic_item[item].item_event();
				}
			}
		}
		else
		{
			page_basic_item[item].item_event();
		}
	}
}

///////////////////////////////////////////////////////////
//模式更新
static void pageBasicItemMode(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.mode++;
		if(gPageMainPara.mode >= 4)
			gPageMainPara.mode = 0;
		LCD_SetFrontColor(page_item_func_name_color[gPageMainPara.mode]);  //字颜色
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);                            //背景颜色
		LCD_ShowHZ(	page_basic_item[BASIC_ITEM_MODE].start_pos_x, 
					page_basic_item[BASIC_ITEM_MODE].start_pos_y, 
					page_item_func_name[gPageMainPara.mode][0], 48, 0 );
		LCD_ShowHZ(	page_basic_item[BASIC_ITEM_MODE].start_pos_x+48, 
					page_basic_item[BASIC_ITEM_MODE].start_pos_y, 
					page_item_func_name[gPageMainPara.mode][1], 48, 0 );
	}
}

//灵敏度更新
static void pageBasicItemSensity(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.sensity++;
		if(gPageMainPara.sensity >= 3)
			gPageMainPara.sensity = 0;

		LCD_Fill(page_basic_item[BASIC_ITEM_SENSITY].start_pos_x + 45, page_basic_item[BASIC_ITEM_SENSITY].start_pos_y + 2,
			page_basic_item[BASIC_ITEM_SENSITY].start_pos_x + page_basic_item[BASIC_ITEM_SENSITY].width - 5, 
			page_basic_item[BASIC_ITEM_SENSITY].start_pos_y+ page_basic_item[BASIC_ITEM_SENSITY].height - 2, page_item_sensity_color[gPageMainPara.sensity]);
	}
}

//预置数
static void pageBasicItemPreset(void)
{		
	u8 tmp_buff[8];
	
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.pre_set += 10;
		if(gPageMainPara.pre_set > 100)
			gPageMainPara.pre_set = 0;
	
		if( gPageMainPara.pre_set >= 1000 )
		{
			sprintf((char*)tmp_buff," %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 100 )
		{
			sprintf((char*)tmp_buff,"  %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 10 )
		{
			sprintf((char*)tmp_buff,"  %d  ", gPageMainPara.pre_set );
		}
		LCD_SetFrontColor(WHITE);  //字颜色
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
		
//		LCD_SetFont(&Font8x16);
//		LCD_DrawString(page_basic_item[2].start_pos_x + 45, page_basic_item[2].start_pos_y + 4, tmp_buff);
		LCD_ShowString(page_basic_item[BASIC_ITEM_PRESET].start_pos_x + 45, page_basic_item[BASIC_ITEM_PRESET].start_pos_y + 4, 100, 16, 16, tmp_buff);
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
			show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOn.width, bmp_menuPageAddOn.height, bmp_menuPageAddOn.addr);
		}
		else
		{
			show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOff.width, bmp_menuPageAddOff.height, bmp_menuPageAddOff.addr);
		}
	}
}

//时间显示
static void pageBasicItemShowTime(void)
{
	LCD_SetFrontColor(WHITE);  //字颜色
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 16, 16, 16, "20");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+16, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+32, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, "-");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+40, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+56, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, "-");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+64, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+80, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, " ");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+88, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+104, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, ":");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+112, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+128, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, ":");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+136, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
}

//当触控logo时进入菜单界面
static void pageBasicItemEnterMenu(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MENU;     
	}
}

//面额显示
static void pageBasicItemShowDenoCnt(void)
{
	u16 tmp;
	
	LCD_SetFrontColor(WHITE);  //字颜色
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
	tmp = gPageMainPara.hundred_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.fifty_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+68, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.twenty_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+138, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.ten_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+200, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.five_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+258, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.error_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+328, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);	
}

//显示当前张数
static void pageBasicItemShowCurCnt(void)
{
	LCD_SetFrontColor(LIGHTBLUE);  //字颜色
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNum(page_basic_item[BASIC_ITEM_CUR_CNT].start_pos_x, page_basic_item[BASIC_ITEM_CUR_CNT].start_pos_y,gPageMainPara.cur_cnt%10000,5,128);
}

//显示张数
static void pageBasicItemShowCnt(void)
{
	LCD_SetFrontColor(LIGHTBLUE);  //字颜色
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNum(page_basic_item[BASIC_ITEM_CNT].start_pos_x, page_basic_item[BASIC_ITEM_CNT].start_pos_y,gPageMainPara.total_cnt%10000,5,24);	
}

//显示金额
static void pageBasicItemShowSum(void)
{
	
	LCD_SetFrontColor(LIGHTBLUE);  //字颜色
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNum(page_basic_item[BASIC_ITEM_SUM].start_pos_x, page_basic_item[BASIC_ITEM_SUM].start_pos_y,gPageMainPara.sum%10000,5,24);	
}

//显示SD卡状态
static void pageBasicItemShowSDStatus(void)
{
	if (gPageMainPara.sd_flg)
	{
		show_bmp_in_flash(page_basic_item[BASIC_ITEM_SD].start_pos_x, page_basic_item[BASIC_ITEM_SD].start_pos_y,bmp_menuPageSDOn.width,bmp_menuPageSDOn.height,bmp_menuPageSDOn.addr);
	}
	else
	{
		show_bmp_in_flash(page_basic_item[BASIC_ITEM_SD].start_pos_x, page_basic_item[BASIC_ITEM_SD].start_pos_y,bmp_menuPageSDOff.width,bmp_menuPageSDOff.height,bmp_menuPageSDOff.addr);
	}
}

//显示网络状态
static void pageBasicItemShowNetStatus(void)
{
	if (gPageMainPara.net_flg)
	{
		;
	}
	else
	{
		;
	}
}

//显示冠字号
static void pageBasicItemShowSerialNum(void)
{
	LCD_ShowString(page_basic_item[BASIC_ITEM_SERIAL].start_pos_x, page_basic_item[BASIC_ITEM_SERIAL].start_pos_y, 144, 24, 24, gPageMainPara.serial);
}

