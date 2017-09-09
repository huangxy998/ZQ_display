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
#include "page_timeset.h"

static char showtime = 1;//�����༭ʱ��ʱ����ʱ��ʵʱ��ʾ
_calendar_obj datetime;


const u8 keytable[] = {
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
'Y', 'M', 'D', 'H', 'N', 'S', '<', 'B', 'C', '*',
};

const u8 xpos[] = {0, 12, 36, 48, 72, 84, 108, 120, 144, 156, 180, 192};

u8 buff[6][3] = {0};  //����ʱ������
u8 code[13] = {0};    //��������
u8 buffIdx = 0xff;    //ָ���������õ���
u8 dataIdx = 0;       //������������õ��ַ�


#ifdef LCD_SIZE_480X320
	#define PAGE_CLOCKSET_L1		56
	#define PAGE_CLOCKSET_L2		124
	#define PAGE_CLOCKSET_L3		190
	#define PAGE_CLOCKSET_L4		300
	#define PAGE_CLOCKSET_L5		366

	#define PAGE_CLOCKSET_H1	  90
	#define PAGE_CLOCKSET_H2	  146
	#define PAGE_CLOCKSET_H3	  200
	#define PAGE_CLOCKSET_H4	  252

	#define PAGE_CLOCKSET_W     60
	#define PAGE_CLOCKSET_H     54
#else
	#define PAGE_CLOCKSET_L1		56
	#define PAGE_CLOCKSET_L2		110
	#define PAGE_CLOCKSET_L3		164
	#define PAGE_CLOCKSET_L4		251
	#define PAGE_CLOCKSET_L5		306

	#define PAGE_CLOCKSET_H1	  64
	#define PAGE_CLOCKSET_H2	  106
	#define PAGE_CLOCKSET_H3	  147
	#define PAGE_CLOCKSET_H4	  189

	#define PAGE_CLOCKSET_W     36
	#define PAGE_CLOCKSET_H     30
#endif

static void pageTimeSetInit(void);
static void pageTimeSetUpdate(void);
static void pageTimeItemUpdate(void);
static void pageTimeSetTouchUpdate(char item);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_TimeSet_item[] =
{
	             //t0�ؼ�
	{
		2,     //id
		0,      //��֧�ִ���
		
		107,30,    //��ʼ����
		191,41, //���
		
		{0},
		0       //Ĭ��0
	},
	             //b0�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H1,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x03,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b1�ؼ�
	{
	  4,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H1,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x04,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b2�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H1,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x05,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b3�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H2,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x06,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b4�ؼ�
	{
		7,     //id
		1,      //֧�ִ���
		
	   PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H2,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x07,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b5�ؼ�
	{
		8,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H2,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x08,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b6�ؼ�
	{
		9,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H3,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x09,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b7�ؼ�
	{
		10,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H3,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0a,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b8�ؼ�
	{
		11,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H3,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0b,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b9�ؼ�
	{
	12,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L2,PAGE_CLOCKSET_H4,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0c,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b10�ؼ�
	{
		13,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H1,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0d,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b11�ؼ�
	{
		14,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H2,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0e,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b12�ؼ�
	{
		15,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H3,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x0f,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b13�ؼ�
	{
		16,     //id
		1,      //֧�ִ���
		
	  PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H1,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x10,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b14�ؼ�
	{
		17,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H2,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,011,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b15�ؼ�
	{
		18,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H3,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x12,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b16�ؼ�
	{
		19,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L1,PAGE_CLOCKSET_H4,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x13,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b17�ؼ�
	{
	20,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L5,PAGE_CLOCKSET_H4,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
		{0x65,0x12,0x14,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b18�ؼ�
	{
		21,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L3,PAGE_CLOCKSET_H4,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		{0x65,0x12,0x15,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
		//b19�ؼ�
	{
		22,     //id
		1,      //֧�ִ���
		
	 PAGE_CLOCKSET_L4,PAGE_CLOCKSET_H4,    //��ʼ����
		PAGE_CLOCKSET_W,PAGE_CLOCKSET_H , //���
		
	{0x65,0x12,0x16,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	}
};

//ҳ��ṹ��
const PAGE_T page_TimeSet =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_TimeSet_item)/sizeof(PAGE_ITEM_T),
	
 	pageTimeSetInit,	
 	pageTimeSetUpdate
};

const _bmp_info bmp_TimeSet_Page =
{
	BASIC_PAGE_TIME_SET_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageTimeSetInit(void)
{
	showtime = 1;
	buffIdx = 0xff;
	show_bmp_in_flash(0,0,bmp_TimeSet_Page.width,bmp_TimeSet_Page.height,bmp_TimeSet_Page.addr);
}

static void pageTimeSetUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_TimeSet.page_item_num; item++)
		{
			if((page_TimeSet_item[item].touch_en))  //��鴥��
			{
			
				if( ( touch_up_pos.x >= page_TimeSet_item[item].start_pos_x ) && ( touch_up_pos.x < page_TimeSet_item[item].start_pos_x + page_TimeSet_item[item].width)  && \
					( touch_up_pos.y >= page_TimeSet_item[item].start_pos_y ) && ( touch_up_pos.y < page_TimeSet_item[item].start_pos_y + page_TimeSet_item[item].height) )
				{
					gPageInfo.need_update = 1;
					pageTimeSetTouchUpdate(item - 1);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageTimeItemUpdate();   //ҳ��ˢ�� 
	}
	
}

static void pageTimeSetTouchUpdate(char item)
{
	u16 bccolor = BACK_COLOR;
	if(item < 10) //Ϊ����
	{
		if(buffIdx < 7)
		{
			if(buffIdx < 6)
			{
				if(dataIdx < 2)
				{
					buff[buffIdx][dataIdx] = keytable[item];
					dataIdx++;
				}
				switch(buffIdx)
				{
					case 0:datetime.w_year = 2000+atoi((char*)buff[0]);
						break;
					case 1:datetime.w_month = atoi((char*)buff[1]);
						break;
					case 2:datetime.w_date = atoi((char*)buff[2]);
						break;
					case 3:datetime.hour = atoi((char*)buff[3]);
						break;
					case 4:datetime.min = atoi((char*)buff[4]);
						break;
					case 5:datetime.sec = atoi((char*)buff[5]);
						break;
					default:break;
				}			
			}
			else
			{
				if(dataIdx < 12)
				{
					code[dataIdx] = keytable[item];
					dataIdx++;
				}
			}
		}
	}
	switch(keytable[item])
	{
		case 'Y':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 0;
			break;
		case 'M':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 1;
			break;
		case 'D':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 2;
			break;
		case 'H':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 3;
			break;
		case 'N':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 4;
			break;
		case 'S':
			dataIdx = 0;
			showtime = 0;
			buffIdx = 5;
			break;
		case '<'://�˸�
			if(dataIdx > 0)
				dataIdx--;
			if(buffIdx == 6)
			{
				code[dataIdx] = 0;
			}
			break;
		case 'B'://����
			gPageInfo.cur_page_idx = PAGE_ID_MAIN;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		case 'C'://ȷ��
			if (buffIdx != 6)
			{
				showtime = 1;
				RTC_Set(datetime.w_year, datetime.w_month, datetime.w_date, 
					datetime.hour, datetime.min, datetime.sec);
			}
			break;
		case '*'://����
			dataIdx = 0;
			buffIdx = 6;
			BACK_COLOR = WHITE;
			LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, "                    ");
			BACK_COLOR = bccolor;
			break;
		default:
			break;
	}
}

static void pageTimeItemUpdate(void)
{
	u8 i = 0;
	u16 color = POINT_COLOR;
	u16 bccolor = BACK_COLOR;
	POINT_COLOR = BLACK;
	BACK_COLOR = LIGHTBLUE;
	if(buffIdx == 6)
	{
		showtime = 1;
		LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, "                    ");
		LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, code);
	}
	else
	{
		if(showtime)
		{
			Get_TimeStr(gPagePara.t_string[0]);
			buff[0][0] = gPagePara.t_string[0][2];
			buff[0][1] = gPagePara.t_string[0][3];
			buff[1][0] = gPagePara.t_string[0][5];
			buff[1][1] = gPagePara.t_string[0][6];
			buff[2][0] = gPagePara.t_string[0][8];
			buff[2][1] = gPagePara.t_string[0][9];
			buff[3][0] = gPagePara.t_string[0][11];
			buff[3][1] = gPagePara.t_string[0][12];
			buff[4][0] = gPagePara.t_string[0][14];
			buff[4][1] = gPagePara.t_string[0][15];
			buff[5][0] = gPagePara.t_string[0][17];
			buff[5][1] = gPagePara.t_string[0][18];	
			datetime.w_year = 2000+atoi((char*)buff[0]);
			datetime.w_month = atoi((char*)buff[1]);
			datetime.w_date = atoi((char*)buff[2]);
			datetime.hour = atoi((char*)buff[3]);
			datetime.min = atoi((char*)buff[4]);
			datetime.sec = atoi((char*)buff[5]);
			LCD_ShowString(page_TimeSet_item[0].start_pos_x, 
					page_TimeSet_item[0].start_pos_y, 300, 24, 24, gPagePara.t_string[0]);
		}
		else
		{
			for(i = 0; i < 12; i++)
			{
				if (((i>>1) == buffIdx) && (i%2 == dataIdx)) //ѡ�е��ַ���ɫ��ʾ
				{
					POINT_COLOR = WHITE;
					BACK_COLOR = BLACK;
				}
				else
				{
					POINT_COLOR = BLACK;
					BACK_COLOR = LIGHTBLUE;
				}
				
				LCD_ShowChar(page_TimeSet_item[0].start_pos_x+24+xpos[i], page_TimeSet_item[0].start_pos_y,
					buff[i/2][i%2], 24, 0);
			}
		}
	}
	POINT_COLOR = color;
	BACK_COLOR = bccolor;
}


