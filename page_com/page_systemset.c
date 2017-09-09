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

static void pageSystemSetInit(void);
static void pageSystemSetUpdate(void);

#ifdef LCD_SIZE_480X320
	#define PAGE_SET_LINE1     84
	#define PAGE_SET_LINE2     158
	#define PAGE_SET_LINE3     228
	#define PAGE_SET_ROW1      62
	#define PAGE_SET_ROW2      260
	#define PAGE_SET_W         138
	#define PAGE_SET_H         40

	const u8* item_table[] =
	{
		"���������",
		"��ʾ������",
		"���嵵λ����",
		"����������",
		"ϵͳ��������",
		"ϵͳ��������",
	};
#else
	#define PAGE_SET_LINE1     62
	#define PAGE_SET_LINE2     120
	#define PAGE_SET_LINE3     174
	#define PAGE_SET_ROW1      60
	#define PAGE_SET_ROW2      222
	#define PAGE_SET_W         112
	#define PAGE_SET_H         32
#endif


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_SystemSet_item[] =
{	
	           //b0�ؼ�
	{
		1,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW1,PAGE_SET_LINE1,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x01,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b1�ؼ�
	{
		2,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW1,PAGE_SET_LINE2,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x02,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b2�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW2,PAGE_SET_LINE1,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x03,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b3�ؼ�
	{
		4,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW2,PAGE_SET_LINE2,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x04,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	          //b4�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW1,PAGE_SET_LINE3,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x05,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b5�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
		PAGE_SET_ROW2,PAGE_SET_LINE3,    //��ʼ����
		PAGE_SET_W,PAGE_SET_H, //���
		
		{0x65,0x0c,0x06,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	
	{
		7,     //id
		1,      //֧�ִ���
		
		0,0,    //��ʼ����
		LCD_HOR_SIZE,40, //���
		
		{0x65,0x0c,0xfe,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	}
};

//ҳ��ṹ��
const PAGE_T page_SystemSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_SystemSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageSystemSetInit,	
 	pageSystemSetUpdate
};

#ifdef LCD_SIZE_480X320
	const _bmp_info bmp_system_Page =
	{
		BASIC_PAGE_SINGLE_BUTTON_OFFSET,
		152,
		52
	};
#else
	const _bmp_info bmp_system_Page =
	{
		BASIC_PAGE_SYSTEM_SET_OFFSET,
		LCD_HOR_SIZE,
		LCD_VER_SIZE
	};
#endif

static void pageSystemSetInit(void)
{
#ifdef LCD_SIZE_480X320
	u8 i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	LCD_Clear(BLACK);
	LCD_ShowString_hz24x24(192,26,100,24,24,"ϵͳ����");
	POINT_COLOR = BRRED;
	BACK_COLOR = SEABLUE;
	for (i = 0; i < 6; i++)
	{
		show_bmp_in_flash(page_SystemSet_item[i].start_pos_x,page_SystemSet_item[i].start_pos_y,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
		LCD_ShowString_hz24x24(page_SystemSet_item[i].start_pos_x+5,page_SystemSet_item[i].start_pos_y+bmp_system_Page.height/2-12,
			bmp_system_Page.width,24,24,item_table[i]);
	}
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
#else
	show_bmp_in_flash(0,0,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
#endif
}

static void pageSystemSetUpdate(void)
{
#if 0
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(BLACK); 
//	LCD_ShowString_hz16x16(10,100,200,16,16,"�˵���ҳ����ʾ");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MAIN;
	}
#endif
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_SystemSet.page_item_num; item++)
		{
			if((page_SystemSet_item[item].touch_en))  //��鴥��
			{
			
				if( ( touch_up_pos.x >= page_SystemSet_item[item].start_pos_x ) && ( touch_up_pos.x < page_SystemSet_item[item].start_pos_x + page_SystemSet_item[item].width)  && \
					( touch_up_pos.y >= page_SystemSet_item[item].start_pos_y ) && ( touch_up_pos.y < page_SystemSet_item[item].start_pos_y + page_SystemSet_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_SystemSet_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
}

