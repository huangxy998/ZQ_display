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

#define PAGE_GZ_L1			3
#define PAGE_GZ_L2			56
#define PAGE_GZ_L3			108
#define PAGE_GZ_L4		    180
#define PAGE_GZ_L5		    316
#define PAGE_GZ_H1			26
#define PAGE_GZ_H2			50
#define PAGE_GZ_H3			73
#define PAGE_GZ_H4			96
#define PAGE_GZ_H5			119
#define PAGE_GZ_H6			142
#define PAGE_GZ_H7			165
#define PAGE_GZ_H8			189
#define PAGE_GZ_W1      49
#define PAGE_GZ_W2      43
#define PAGE_GZ_W3      63
#define PAGE_GZ_W4      134
#define PAGE_GZ_W5      76
#define PAGE_GZ_H       20


static void pageSerialInit(void);
static void pageSerialUpdate(void);
static void pageSerialItemUpdate(void);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_Serial_item[] =
{
	        //p0�ؼ�
	{
		1,     //id
		0,      //��֧�ִ���
		
		0,0,    //��ʼ����
		400,240, //���
		
		{0},
		0       //Ĭ��0
	},
	            //b0�ؼ�
	{
		2,     //id
		1,      //֧�ִ���
		
		22,210,    //��ʼ����
		80,26, //���
		
		{0x65,0x0b,0x04,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b1�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		160,210,    //��ʼ����
		80,26, //���
		
			{0x65,0x0b,0x05,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b2�ؼ�
	{
		4,     //id
		1,      //֧�ִ���
		
		290,210,    //��ʼ����
		80,26, //���
		
			{0x65,0x0b,0x06,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //t0�ؼ�
	{
		6,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H1,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t1�ؼ�
	{
		7,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H2,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t2�ؼ�
	{
		8,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H3,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t3�ؼ�
	{
		9,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H4,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t4�ؼ�
	{
		10,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H5,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	           //t5�ؼ�
	{
		11,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H6,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t6�ؼ�
	{
		12,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H7,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t7�ؼ�
	{
		13,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L1,PAGE_GZ_H8,    //��ʼ����
		PAGE_GZ_W1,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	         //t8�ؼ�
	{
		14,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H1,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	           //t9�ؼ�
	{
		15,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H2,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t10�ؼ�
	{
		16,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H3,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t11�ؼ�
	{
		17,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H4,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t12�ؼ�
	{
		18,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H5,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t13�ؼ�
	{
		19,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H6,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	           //t14�ؼ�
	{
		20,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H7,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t15�ؼ�
	{
		21,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L2,PAGE_GZ_H8,    //��ʼ����
		PAGE_GZ_W2,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t16�ؼ�
	{
		22,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L3,PAGE_GZ_H1,    //��ʼ����
		PAGE_GZ_W3,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t17�ؼ�
	{
		23,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H2,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t18�ؼ�
	{
		24,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H3,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t19�ؼ�
	{
		25,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H4,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		  
		{0},
		0       //Ĭ��0
	},
	            //t20�ؼ�
	{
		26,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H5,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		{0},
		0       //Ĭ��0
	},
	             //t21�ؼ�
	{
		27,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H6,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	          //t22�ؼ�
	{
		28,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H7,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		{0},
		0       //Ĭ��0
	},
	            //t23�ؼ�
	{
		29,     //id
		0,      //��֧�ִ���
		
			PAGE_GZ_L3,PAGE_GZ_H8,    //��ʼ����
		  PAGE_GZ_W3,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t24�ؼ�
	{
		30,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H1,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t25�ؼ�
	{
		31,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H2,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t26�ؼ�
	{
		32,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H3,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t27�ؼ�
	{
		33,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H4,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	         //t28�ؼ�
	{
		34,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H5,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t29�ؼ�
	{
		35,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H6,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t30�ؼ�
	{
		36,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H7,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t31�ؼ�
	{
		37,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L4,PAGE_GZ_H8,    //��ʼ����
		PAGE_GZ_W4,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t32�ؼ�
	{
		38,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H1,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t33�ؼ�
	{
		39,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H2,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t34�ؼ�
	{
		40,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H3,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	             //t35�ؼ�
	{
		41,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H4,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	            //t36�ؼ�
	{
		42,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H5,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		{0},
		0       //Ĭ��0
	},
	            //t37�ؼ�
	{
		43,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H6,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	         //t38�ؼ�
	{
		44,     //id
		0,      //��֧�ִ���
		PAGE_GZ_L5,PAGE_GZ_H7,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	},
	//t39�ؼ�
	{
		45,     //id
		0,      //��֧�ִ���
		
		PAGE_GZ_L5,PAGE_GZ_H8,    //��ʼ����
		PAGE_GZ_W5,PAGE_GZ_H, //���
		
		{0},
		0       //Ĭ��0
	}
};

//ҳ��ṹ��
const PAGE_T page_Serial =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_Serial_item)/sizeof(PAGE_ITEM_T),
	
 	pageSerialInit,	
 	pageSerialUpdate
};

const _bmp_info bmp_Serial_Page =
{
	BASIC_PAGE_SERAL_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageSerialInit(void)
{
	show_bmp_in_flash(0,0,bmp_Serial_Page.width,bmp_Serial_Page.height,bmp_Serial_Page.addr);
}

static void pageSerialUpdate(void)
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
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_Serial.page_item_num; item++)
		{
			if(page_Serial_item[item].touch_en)  //��鴥��
			{
				if( ( touch_up_pos.x >= page_Serial_item[item].start_pos_x ) && ( touch_up_pos.x < page_Serial_item[item].start_pos_x + page_Serial_item[item].width)  && \
					( touch_up_pos.y >= page_Serial_item[item].start_pos_y ) && ( touch_up_pos.y < page_Serial_item[item].start_pos_y + page_Serial_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_Serial_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageSerialItemUpdate();   //ҳ��ˢ��
	}
	
}

//��ʾ����
static void pageSerialItemUpdate(void)
{
	int item;
	LCD_SetBackColor(BLACK);
	for(item = 0; item < 40; item++)
	{
		LCD_Fill(page_Serial_item[item+4].start_pos_x, page_Serial_item[item+4].start_pos_y,
			     page_Serial_item[item+4].start_pos_x+page_Serial_item[item+4].width-4,
			     page_Serial_item[item+4].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_Serial_item[item+4].start_pos_x, 
					page_Serial_item[item+4].start_pos_y, page_Serial_item[item+4].width, 16, 16, gPagePara.t_string[item]);
		
	}
}


