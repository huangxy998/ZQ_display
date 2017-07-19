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
#include "page_keyboard.h"

KEYBOARD_INFO keyBoardInfo;
static u8 prePage = 0;

// '<' ����ɾ��
// '>' ȷ��
// '#' ����
// '*' ����
const char letter_table[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                             'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '<',
                             'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '>',
                             '.', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '!', '?', '@',
                             '#', ' ', '*', '\\'
                            };


static void pageKeyBoardInit(void);
static void pageKeyBoardUpdate(void);
static void pageKeyBoardTPUpdate(u8 item);
static void pageKeyBoardItemUpdate(void);



///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_KeyBoard_item[] =  //��������������ң����ϵ���
{
	{ 
		'1',	
		1,			//����							
		20,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'2',	
		1,			//����							
		56,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'3',	
		1,			//����							
		92,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'4',	
		1,			//����							
		128, 66,
		34, 34,
		{0},
		0	
	},

	{ 
		'5',	
		1,			//����							
		164,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'6',	
		1,			//����							
		200,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'7',	
		1,			//����							
		234,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'8',	
		1,			//����							
		272, 66,
		34, 34,
		{0},
		0	
	},

	{ 
		'9',	
		1,			//����							
		308,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		'0',	
		1,			//����							
		346, 66,
		34, 34,
		{0},
		0	
	},

	{ 
		'q',	
		1,			//����							
		0,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'w',	
		1,			//����							
		36,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'e',	
		1,			//����							
		74,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'r',	
		1,			//����							
		110, 102,
		34, 34,
		{0},
		0	
	},

	{ 
		't',	
		1,			//����							
		146,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'y',	
		1,			//����							
		182,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'u',	
		1,			//����							
		218,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'i',	
		1,			//����							
		256, 102,
		34, 34,
		{0},
		0	
	},

	{ 
		'o',	
		1,			//����							
		292,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'p',	
		1,			//����							
		328, 102,
		34, 34,
		{0},
		0	
	},

	{ 
		'<',	
		1,			//����							
		364,	102,
		34, 34,
		{0},
		0	
	},

	{ 
		'a',	
		1,			//����							
		16,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		's',	
		1,			//����							
		52,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		'd',	
		1,			//����							
		88, 138,
		34, 32,
		{0},
		0	
	},

	{ 
		'f',	
		1,			//����							
		124,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		'g',	
		1,			//����							
		158,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		'h',	
		1,			//����							
		194,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		'j',	
		1,			//����							
		232, 138,
		34, 32,
		{0},
		0	
	},

	{ 
		'k',	
		1,			//����							
		266,	138,
		34, 32,
		{0},
		0	
	},

	{ 
		'l',	
		1,			//����							
		302, 138,
		34, 32,
		{0},
		0	
	},

	{ 
		'>',	
		1,			//����							
		342,	138,
		58, 32,
		{0},
		0	
	},

	{ 
		'.',	
		1,			//����							
		0,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'z',	
		1,			//����							
		36,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'x',	
		1,			//����							
		72, 170,
		34, 34,
		{0},
		0	
	},

	{ 
		'c',	
		1,			//����							
		108,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'v',	
		1,			//����							
		142,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'b',	
		1,			//����							
		178,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'n',	
		1,			//����							
		214, 170,
		34, 34,
		{0},
		0	
	},

	{ 
		'm',	
		1,			//����							
		248,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'!',	
		1,			//����							
		284, 170,
		34, 34,
		{0},
		0	
	},

	{ 
		'?',	
		1,			//����							
		318,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'@',	
		1,			//����							
		354,	170,
		34, 34,
		{0},
		0	
	},

	{ 
		'#',	
		1,			//����							
		2,	206,
		34, 34,
		{0},
		0	
	},

	{ 
		' ',	
		1,			//����							
		108, 206,
		174, 34,
		{0},
		0	
	},

	{ 
		'*',	
		1,			//����							
		284,	206,
		80, 34,
		{0},
		0	
	},

	{ 
		'\\',	
		0,			//����							
		200,	66,
		34, 34,
		{0},
		0	
	},

	{ 
		0,	
		0,			//t0						
		82,	24,
		250, 30,
		{0},
		0	
	},
};

//ҳ��ṹ��
const PAGE_T page_KeyBoard =
{ 
	PAGE_ID_BLACKKEY,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_KeyBoard_item)/sizeof(PAGE_ITEM_T),
	
 	pageKeyBoardInit,	
 	pageKeyBoardUpdate
};

const _bmp_info bmp_KeyBoard_Page =
{
	BASIC_PAGE_KEYBOARD_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageKeyBoardInit(void)
{
	prePage = gPageInfo.pre_page_idx;
	show_bmp_in_flash(0,0,bmp_KeyBoard_Page.width,bmp_KeyBoard_Page.height,bmp_KeyBoard_Page.addr);
	memset(&keyBoardInfo, 0, sizeof(KEYBOARD_INFO));	
}

static void pageKeyBoardUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_KeyBoard.page_item_num; item++)
		{
			if((page_KeyBoard_item[item].touch_en))  //��鴥��
			{
			
				if( ( touch_up_pos.x >= page_KeyBoard_item[item].start_pos_x ) && ( touch_up_pos.x < page_KeyBoard_item[item].start_pos_x + page_KeyBoard_item[item].width)  && \
					( touch_up_pos.y >= page_KeyBoard_item[item].start_pos_y ) && ( touch_up_pos.y < page_KeyBoard_item[item].start_pos_y + page_KeyBoard_item[item].height) )
				{
					gPageInfo.need_update = 1;
					pageKeyBoardTPUpdate(item);
					
//					gIDInfo.cmdUpdate = 1;
//					memcpy(&gIDInfo.cmdPage.start, &page_KeyBoard_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageKeyBoardItemUpdate();   //ҳ��ˢ��
	}
}

static void pageKeyBoardItemUpdate(void)
{
	LCD_Fill(page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y,
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x+100, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y+20, WHITE);
	
	LCD_ShowString_hz16x16(page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y, 100, 16, 16, gPagePara.t_string[0]);
}


static void pageKeyBoardTPUpdate(u8 item)
{
	switch(letter_table[item])
	{
		case '<': //ɾ�����һ���ַ�
			if (keyBoardInfo.buffLen > 0)
				keyBoardInfo.buffLen--;
			gPagePara.t_string[0][keyBoardInfo.buffLen] = 0;
			break;
		case '#': //ɾ��ȫ���ַ�
			gPagePara.t_string[0][0] = 0;
			keyBoardInfo.buffLen = 0;
			break;
		case '*'://ֱ�ӷ���
			memset(&keyBoardInfo, 0, sizeof(KEYBOARD_INFO));	
		case '>': //ȷ���˳�
			if (keyBoardInfo.buffLen > 0)
			{
				keyBoardInfo.strUpdate = 1;
				memcpy(keyBoardInfo.buff, gPagePara.t_string[0], keyBoardInfo.buffLen);
			}
			//�˴��л�ҳ��
			gPageInfo.cur_page_idx = prePage;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		default://�ַ�����
			gPagePara.t_string[0][keyBoardInfo.buffLen] = letter_table[item];
			if (keyBoardInfo.buffLen < 10) //�������15���ַ�������ip�����ʽ����
			{
				keyBoardInfo.buffLen++;
				gPagePara.t_string[0][keyBoardInfo.buffLen] = 0; //����ַ���������
			}
			break;
	}
}


