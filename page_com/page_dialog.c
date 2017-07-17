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

static void pageDialogInit(void);
static void pageDialogUpdate(void);
static void pageDialogItemUpdate(void);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_Dialog_item[] =
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//GEARset2
	/////////////////////////////////////////////
	
	 //p0�ؼ�
	{
		1,	   //id
		0,		//��֧�ִ���
		
		68,70,	  //��ʼ����
		280,106, //���
		
		{0},
		0		//Ĭ��0
	},
	      //b0�ؼ�
	{
		2,	   //id
		1,		//֧�ִ���
		
		80,96,	  //��ʼ����
		45,30, //���
		
	{0x65,0x0f,0x02,0x00,0xff,0xff,0xff},
		0		//Ĭ��0
	},
	  			   //b1�ؼ�
	{
		3,	   //id
		1,		//֧�ִ���
		
		80,134,    //��ʼ����
		45,30, //���
		
	{0x65,0x0f,0x03,0x00,0xff,0xff,0xff},
		0		//Ĭ��0
	},
	  			   //b2�ؼ�
	{
		4,	   //id
		1,		//֧�ִ���
		
		262,102,	//��ʼ����
		68,56, //���
		
	{0x65,0x0f,0x04,0x00,0xff,0xff,0xff},
		0		//Ĭ��0
	},
	  			   //n0�ؼ�
	{
		5,	   //id
		0,		//��֧�ִ���
		
		150,114,	//��ʼ����
		100,30, //���
		
		{0},
		0		//Ĭ��0
	}

};

//ҳ��ṹ��
const PAGE_T page_dialog =
{ 
	PAGE_ID_CONFIRM,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Dialog_item)/sizeof(PAGE_ITEM_T),
	
 	pageDialogInit,	
 	pageDialogUpdate
};

const _bmp_info bmp_Dialog_Page =
{
	BASIC_PAGE_DIALOG_OFFSET,
	280,
	106
};

static void pageDialogInit(void)
{
	u16 color;
	u16 i;
	show_bmp_in_flash(page_Dialog_item[0].start_pos_x, page_Dialog_item[0].start_pos_y,
		              bmp_Dialog_Page.width,bmp_Dialog_Page.height,bmp_Dialog_Page.addr);
	//������b0��b1��b2
	color = POINT_COLOR;
	POINT_COLOR = BLACK;
	for(i = 1; i < 4; i++)
	{
		LCD_Fill(page_Dialog_item[i].start_pos_x,page_Dialog_item[i].start_pos_y,
			     page_Dialog_item[i].start_pos_x+page_Dialog_item[i].width,
			     page_Dialog_item[i].start_pos_y+page_Dialog_item[i].height, GRAY);
		
		LCD_DrawLine(page_Dialog_item[i].start_pos_x+page_Dialog_item[i].width,
				 page_Dialog_item[i].start_pos_y,
			     page_Dialog_item[i].start_pos_x+page_Dialog_item[i].width,
			     page_Dialog_item[i].start_pos_y+page_Dialog_item[i].height);
		LCD_DrawLine(page_Dialog_item[i].start_pos_x,
			page_Dialog_item[i].start_pos_y+page_Dialog_item[i].height,
			     page_Dialog_item[i].start_pos_x+page_Dialog_item[i].width,
			     page_Dialog_item[i].start_pos_y+page_Dialog_item[i].height);
	}
	//���м䷽��
	POINT_COLOR = BLUE;
	LCD_DrawRectangle(page_Dialog_item[i].start_pos_x, page_Dialog_item[i].start_pos_y,
			     page_Dialog_item[i].start_pos_x+page_Dialog_item[i].width,
			     page_Dialog_item[i].start_pos_y+page_Dialog_item[i].height);
	POINT_COLOR = color;
}

static void pageDialogUpdate(void)
{
#if 0
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(BLACK); 
//	LCD_ShowString_hz16x16(10,100,200,16,16,"�˵���ҳ����ʾ");
	if(gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_MENU;
		gIDInfo.cmdUpdate = 1;
		gIDInfo.cmdPage.touchStatus = PAGE_ID_CONFIRM;

	}
#endif
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_dialog.page_item_num; item++)
		{
			if((page_Dialog_item[item].touch_en))  //��鴥��
			{
			
				if( ( touch_up_pos.x >= page_Dialog_item[item].start_pos_x ) && ( touch_up_pos.x < page_Dialog_item[item].start_pos_x + page_Dialog_item[item].width)  && \
					( touch_up_pos.y >= page_Dialog_item[item].start_pos_y ) && ( touch_up_pos.y < page_Dialog_item[item].start_pos_y + page_Dialog_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_Dialog_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	pageDialogItemUpdate();   //ҳ��ˢ��
}

static void pageDialogItemUpdate(void)
{
	LCD_ShowString(page_Dialog_item[4].start_pos_x+2, 
					page_Dialog_item[4].start_pos_y+2, 100, 16, 16, gPagePara.n_val[0]);
}

