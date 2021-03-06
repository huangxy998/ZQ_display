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

static u8 progress_show = 0;

static void pageStartInit(void);
static void pageStartUpdate(void);
static void pageStartItemUpdate(void);

//页面结构体
const PAGE_T page_start =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	0,
	
 	pageStartInit,	
 	pageStartUpdate
};

const _bmp_info bmp_start_Page =
{
	BASIC_PAGE_START_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};
#ifndef LCD_SIZE_480X320
extern const _bmp_info bmp_progress_none;

extern const _bmp_info bmp_progress_percent;
#endif

static void pageStartInit(void)
{
	show_bmp_in_flash(0,0,bmp_start_Page.width,bmp_start_Page.height,bmp_start_Page.addr);
	progress_show = 0;
}

//版本页面刷新
static void pageStartUpdate(void)
{

		pageStartItemUpdate();   //页面刷新
	
}

///////////////////////////////////////////////////////////
//显示更新
static void pageStartItemUpdate(void)
{
	static u8 touchFlg = 0;
	if(gPagePara.j_percent[0][0] != 0)
	{
		static int valtmp = 0;
		int value = 0;
		
		if(progress_show == 0)
		{
			progress_show = 1;
			valtmp = 0;
			#ifndef LCD_SIZE_480X320
			show_bmp_in_flash(86,210,bmp_progress_none.width,bmp_progress_none.height,bmp_progress_none.addr);
			#endif
		}
		
		value = atoi((char*)&gPagePara.j_percent[0][0]);
		if(value < valtmp)
		{
			progress_show = 0;
		}
		else
		{
			if(value != valtmp)
			{
				valtmp = value;
			#ifndef LCD_SIZE_480X320
				show_bmp_in_flash(86,210,(bmp_progress_percent.width*value)/100,bmp_progress_percent.height,bmp_progress_percent.addr);
			#endif
			}
		}
	}
	if (( strcmp((char *)gPagePara.t_string[0], "adjust lcd") == 0) && (touchFlg == 0))
	{
		touchFlg = 1;
		LCD_Clear(WHITE);//清屏
		TP_Adjust();  	 //屏幕校准 
		TP_Save_Adjdata();
	}
}




