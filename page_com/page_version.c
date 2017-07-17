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


#define PAGE_VER_LIE1_X		 180
#define PAGE_VER_KEY_WIDTH   230
#define PAGE_VER_KEY_HIGH    30


static void pageVersionInit(void);
static void pageVersionUpdate(void);
static void pageVersionItemUpdate(void);

///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_version_item[] =
{
	            //b0�ؼ�
	{
		1,     //id
		1,      //֧�ִ���
		
		74,4,    //��ʼ����
		243,30,//���
		
		{0x65,0x02,0x01,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //t1�ؼ�
	{
		2,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,42,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //t2�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,74,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //t3�ؼ�
	{
		4,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,108,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //t4�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,142,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //t5�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,178,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //t6�ؼ�
	{
		7,     //id
		1,      //֧�ִ���
		
		PAGE_VER_LIE1_X,210,    //��ʼ����
		PAGE_VER_KEY_WIDTH,PAGE_VER_KEY_HIGH,//���
		
		{0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	}
};

//ҳ��ṹ��
const PAGE_T page_version =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_version_item)/sizeof(PAGE_ITEM_T),
	
 	pageVersionInit,	
 	pageVersionUpdate
};

const _bmp_info bmp_version_Page =
{
	BASIC_PAGE_VERSION_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};


static void pageVersionInit(void)
{
	show_bmp_in_flash(0,0,bmp_version_Page.width,bmp_version_Page.height,bmp_version_Page.addr);
}

//�汾ҳ��ˢ��
static void pageVersionUpdate(void)
{
#if 0
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(BLACK); 
	LCD_ShowString_hz16x16(10,100,200,16,16,"�˵���ҳ����ʾ");
	if(gPageInfo.toucged_up)
	{
		gPageInfo.cur_page_idx = PAGE_ID_MAIN;
	}
#endif
	
	u8 item;
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_version.page_item_num; item++)
		{
			if(page_version_item[item].touch_en)  //��鴥��
			{
				if( ( touch_up_pos.x >= page_version_item[item].start_pos_x ) && ( touch_up_pos.x < page_version_item[item].start_pos_x + page_version_item[item].width)  && \
					( touch_up_pos.y >= page_version_item[item].start_pos_y ) && ( touch_up_pos.y < page_version_item[item].start_pos_y + page_version_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					if(page_version_item[item].id != 1)
						gIDInfo.cmdUpdate = 2;
					memcpy(&gIDInfo.cmdPage.start, &page_version_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageVersionItemUpdate();   //ҳ��ˢ��
	}
	
}

///////////////////////////////////////////////////////////
//��ʾ����
static void pageVersionItemUpdate(void)
{
	int item;

	for(item = 0; item < page_version.page_item_num; item++)
	{
		LCD_ShowString(page_version_item[item].start_pos_x, 
					page_version_item[item].start_pos_y, 100, 16, 16, gPagePara.t_string[item]);
	}
}



