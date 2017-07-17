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

///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_SystemSet_item[] =
{	
	           //b0�ؼ�
	{
		1,     //id
		1,      //֧�ִ���
		
		60,62,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x01,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b1�ؼ�
	{
		2,     //id
		1,      //֧�ִ���
		
		60,120,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x02,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b2�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		222,62,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x03,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	              //b3�ؼ�
	{
		4,     //id
		1,      //֧�ִ���
		
		222,120,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x04,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	          //b4�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
		60,174,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x05,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b5�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
		222,174,    //��ʼ����
		112,32, //���
		
		{0x65,0x0c,0x06,0x00,0xff,0xff,0xff},
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

const _bmp_info bmp_system_Page =
{
	BASIC_PAGE_SYSTEM_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageSystemSetInit(void)
{
	show_bmp_in_flash(0,0,bmp_system_Page.width,bmp_system_Page.height,bmp_system_Page.addr);
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

