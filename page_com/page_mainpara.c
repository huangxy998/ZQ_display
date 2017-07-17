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


#define PAGE_SENSOR_L1			2
#define PAGE_SENSOR_L2			57
#define PAGE_SENSOR_L3			140
#define PAGE_SENSOR_L4			195
#define PAGE_SENSOR_L5			272
#define PAGE_SENSOR_L6			327
#define PAGE_SENSOR_H1			33
#define PAGE_SENSOR_H2			56
#define PAGE_SENSOR_H3			80
#define PAGE_SENSOR_H4			102
#define PAGE_SENSOR_H5			125
#define PAGE_SENSOR_H6			149
#define PAGE_SENSOR_H7			172
#define PAGE_SENSOR_H8			195
#define PAGE_SENSOR_WT     45
#define PAGE_SENSOR_WD     80
#define PAGE_SENSOR_H          19

#define PAGE_PARA_LIE1_X			4
#define PAGE_PARA_LIE2_X			90
#define PAGE_PARA_LIE3_X			135
#define PAGE_PARA_LIE4_X			216
#define PAGE_PARA_LIE5_X			264
#define PAGE_PARA_LIE6_X			350
#define PAGE_PARA_HANG1_Y		6
#define PAGE_PARA_HANG2_Y		31
#define PAGE_PARA_HANG3_Y		56
#define PAGE_PARA_HANG4_Y		81
#define PAGE_PARA_HANG5_Y		106
#define PAGE_PARA_HANG6_Y		131
#define PAGE_PARA_HANG7_Y		156
#define PAGE_PARA_HANG8_Y		181
#define PAGE_PARA_KEY_WIDTH    82
#define PAGE_PARA_KEY_HIGH     22
#define PAGE_PARA_DATA_WIDTH   42
#define PAGE_PARA_DATA_HIGH    20


static void pageMainParaInit(void);
static void pageMainParaUpdate(void);
static void pageMainParaItemUpdate(void);

///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_mainpara_item[] =
{
		             //b0�ؼ�
	{
		20,     //id
		1,      //֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG1_Y,        //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x02, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	            //b1�ؼ�
	{
		21,     //id
		1,      //֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG2_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x03, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //b2�ؼ�
	{
		22,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG3_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x04, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	            //b3�ؼ�
	{
		23,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG4_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x05, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //b4�ؼ�
	{
		24,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG5_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x06, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //b5�ؼ�
	{
		25,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG6_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x07, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	            //b6�ؼ�
	{
		26,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG7_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x08, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	{
		26,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE1_X,PAGE_PARA_HANG8_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x09, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //b7�ؼ�
	{
		27,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG1_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0a, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //b8�ؼ�
	{
		28,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG2_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0b, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //b9�ؼ�
	{
		29,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG3_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0c, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //n10�ؼ�
	{
		30,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG4_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0d, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	            //n11�ؼ�
	{
		31,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG5_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0e, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //n12�ؼ�
	{
		32,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG6_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x0f, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	             //n13�ؼ�
	{
		33,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG7_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x10, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	{
		33,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE3_X,PAGE_PARA_HANG8_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x11, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},
	             //n14�ؼ�
	{
		34,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG1_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x12, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //n15�ؼ�
	{
		35,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG2_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x13, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //n16�ؼ�
	{
		36,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG3_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x14, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //n17�ؼ�
	{
		37,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG4_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x15, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //n18�ؼ�
	{
		38,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG5_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x16, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},


	             //n19�ؼ�
	{
		39,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG6_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x17, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	{
		39,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG7_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x18, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},

	{
		39,     //id
		1,      //��֧�ִ���
		
		PAGE_PARA_LIE5_X,PAGE_PARA_HANG8_Y,    //��ʼ����
		PAGE_PARA_KEY_WIDTH,PAGE_PARA_KEY_HIGH , //���
		
		{0x65, 0x0e, 0x19, 0x00, 0xff, 0xff, 0xff},
		0       //Ĭ��0
	},
	             //
	{
		42,     //id
		1,      //֧�ִ���
		
		32,202,    //��ʼ����
		74,32 , //���
		
		{0x65,0x0e,0x32,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //�ؼ�
	{
		44,     //id
			1,      //֧�ִ���
		
		130,202,    //��ʼ����
		138,32 , //���
		
		{0x65,0x0e,0x33,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	      //�ؼ�
	{
		45,     //id
		1,      //֧�ִ���
		
		294,202,    //��ʼ����
		80,32 , //���
		
		{0x65,0x0e,0x34,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	}
};

//ҳ��ṹ��
const PAGE_T page_mainpara =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_mainpara_item)/sizeof(PAGE_ITEM_T),
	
 	pageMainParaInit,	
 	pageMainParaUpdate
};

const _bmp_info bmp_mainpara_Page =
{
	BASIC_PAGE_MAIN_PARA_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};


static void pageMainParaInit(void)
{
	show_bmp_in_flash(0,0,bmp_mainpara_Page.width,bmp_mainpara_Page.height,bmp_mainpara_Page.addr);
}

//�汾ҳ��ˢ��
static void pageMainParaUpdate(void)
{
	
	u8 item;
	u8 cmdLen = TOUCH_CMD_LEN;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_mainpara.page_item_num; item++)
		{
			if(page_mainpara_item[item].touch_en)  //��鴥��
			{
				if( ( touch_up_pos.x >= page_mainpara_item[item].start_pos_x ) && ( touch_up_pos.x < page_mainpara_item[item].start_pos_x + page_mainpara_item[item].width)  && \
					( touch_up_pos.y >= page_mainpara_item[item].start_pos_y ) && ( touch_up_pos.y < page_mainpara_item[item].start_pos_y + page_mainpara_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_mainpara_item[item].com_data[0], cmdLen);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageMainParaItemUpdate();   //ҳ��ˢ��
	}
}

///////////////////////////////////////////////////////////
//��ʾ����
static void pageMainParaItemUpdate(void)
{
	int item;

	for(item = 0; item < 24; item++)
	{
		LCD_Fill(page_mainpara_item[item].start_pos_x, page_mainpara_item[item].start_pos_y,
			     page_mainpara_item[item].start_pos_x+page_mainpara_item[item].width-12,
			     page_mainpara_item[item].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_mainpara_item[item].start_pos_x, 
					page_mainpara_item[item].start_pos_y, page_mainpara_item[item].width, 16, 16, gPagePara.b_str[item]);
		LCD_Fill(page_mainpara_item[item].start_pos_x+86, page_mainpara_item[item].start_pos_y,
			     page_mainpara_item[item].start_pos_x+86+32,
			     page_mainpara_item[item].start_pos_y+16, BLACK);
		LCD_ShowString_hz16x16(page_mainpara_item[item].start_pos_x+86, 
					page_mainpara_item[item].start_pos_y, 32, 16, 16, gPagePara.n_val[item]);
	}
}

