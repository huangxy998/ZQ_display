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

static void pageErrorInit(void);
static void pageErrorUpdate(void);
static void pageErrorItemUpdate(void);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_Error_item[] =
{
	//p0�ؼ�
	{
		1,	   //id
		0,		//��֧�ִ���
		
		68,78,	  //��ʼ����
		280,106, //���
		
		{0},
		0		//Ĭ��0
	},
	      //b0�ؼ�
	{
		2,	   //id
		1,		//֧�ִ���
		
		270,100,	  //��ʼ����
		64,30, //���
		
	{0x65,0x19,0x02,0x00,0xff,0xff,0xff},
		0		//Ĭ��0
	},
	  			   //t0�ؼ�
	{
		3,	   //id
		0,		//��֧�ִ���
		
		98,100,	//��ʼ����
		166,30, //���
		
		{0},
		0		//Ĭ��0
	},

	 			   //t1�ؼ�
	{
		4,	   //id
		0,		//��֧�ִ���
		
		74,136,	//��ʼ����
		260,30, //���
		
		{0},
		0		//Ĭ��0
	}

};

//ҳ��ṹ��
const PAGE_T page_error =
{ 
	PAGE_ID_CONFIRM,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Error_item)/sizeof(PAGE_ITEM_T),
	
 	pageErrorInit,	
 	pageErrorUpdate
};

extern const _bmp_info bmp_Dialog_Page;

static void pageErrorInit(void)
{
	u16 color;
	u16 i = 1;
	show_bmp_in_flash(page_Error_item[0].start_pos_x,page_Error_item[0].start_pos_y,
		              bmp_Dialog_Page.width,bmp_Dialog_Page.height,bmp_Dialog_Page.addr);
	//������b0��b1
	color = POINT_COLOR;
	POINT_COLOR = BLACK;
	LCD_Fill(page_Error_item[i].start_pos_x,page_Error_item[i].start_pos_y,
		     page_Error_item[i].start_pos_x+page_Error_item[i].width,
		     page_Error_item[i].start_pos_y+page_Error_item[i].height, GRAY);
	
	LCD_DrawLine(page_Error_item[i].start_pos_x+page_Error_item[i].width,
			 page_Error_item[i].start_pos_y,
		     page_Error_item[i].start_pos_x+page_Error_item[i].width,
		     page_Error_item[i].start_pos_y+page_Error_item[i].height);
	LCD_DrawLine(page_Error_item[i].start_pos_x,page_Error_item[i].start_pos_y+page_Error_item[i].height,
		     page_Error_item[i].start_pos_x+page_Error_item[i].width,
		     page_Error_item[i].start_pos_y+page_Error_item[i].height);
	POINT_COLOR = color;
}

static void pageErrorUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_error.page_item_num; item++)
		{
			if((page_Error_item[item].touch_en))  //��鴥��
			{	
				if( ( touch_up_pos.x >= page_Error_item[item].start_pos_x ) && ( touch_up_pos.x < page_Error_item[item].start_pos_x + page_Error_item[item].width)  && \
					( touch_up_pos.y >= page_Error_item[item].start_pos_y ) && ( touch_up_pos.y < page_Error_item[item].start_pos_y + page_Error_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_Error_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	pageErrorItemUpdate();   //ҳ��ˢ��
}

static void pageErrorItemUpdate(void)
{
	u8 i = 0;
	for(; i < 2; i++)
	{
		LCD_ShowString_hz16x16(page_Error_item[i+2].start_pos_x+2, 
					page_Error_item[i+2].start_pos_y+2, 100, 16, 16, gPagePara.t_string[i]);
	}
}

