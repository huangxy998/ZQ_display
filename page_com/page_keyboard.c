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

// '<' ºóÍËÉ¾³ý
// '>' È·¶¨
// '#' ÖØÊä
// '*' ·µ»Ø
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
static u8 pageKeyBoardMakeReplyFrame(u8* buff);

#ifdef LCD_SIZE_480X320
	#define PAGE_KEY_TXTL		98
	#define PAGE_KEY_TXTH1	30
	#define PAGE_KEY_TXTW		300
	#define PAGE_KEY_TXTH		40
	
	#define PAGE_KEY_LINE1    90
	#define PAGE_KEY_L1K1	    24
	#define PAGE_KEY_L1K2	    68
	#define PAGE_KEY_L1K3     110
	#define PAGE_KEY_L1K4     154
	#define PAGE_KEY_L1K5	    196
	#define PAGE_KEY_L1K6	    236
	#define PAGE_KEY_L1K7	    282
	#define PAGE_KEY_L1K8     326
	#define PAGE_KEY_L1K9	    370
	#define PAGE_KEY_L1KA     414
	#define PAGE_KEY_LINE2    140
	#define PAGE_KEY_L2K1	    0
	#define PAGE_KEY_L2K2	    44
	#define PAGE_KEY_L2K3	    88
	#define PAGE_KEY_L2K4     132
	#define PAGE_KEY_L2K5	    176
	#define PAGE_KEY_L2K6	    220
	#define PAGE_KEY_L2K7	    262
	#define PAGE_KEY_L2K8     306
	#define PAGE_KEY_L2K9	    350
	#define PAGE_KEY_L2KA     394
	#define PAGE_KEY_L2KB     438
	#define PAGE_KEY_LINE3    184
	#define PAGE_KEY_L3K1	    20
	#define PAGE_KEY_L3K2	    64
	#define PAGE_KEY_L3K3	    106
	#define PAGE_KEY_L3K4     150
	#define PAGE_KEY_L3K5	    194
	#define PAGE_KEY_L3K6	    236
	#define PAGE_KEY_L3K7	    278
	#define PAGE_KEY_L3K8     322
	#define PAGE_KEY_L3K9	    366
	#define PAGE_KEY_L3KA     408
	#define PAGE_KEY_LINE4    228
	#define PAGE_KEY_L4K1	    0
	#define PAGE_KEY_L4K2	    44
	#define PAGE_KEY_L4K3	    86
	#define PAGE_KEY_L4K4     130
	#define PAGE_KEY_L4K5	    172
	#define PAGE_KEY_L4K6	    214
	#define PAGE_KEY_L4K7	    258
	#define PAGE_KEY_L4K8     300
	#define PAGE_KEY_L4K9	    342
	#define PAGE_KEY_L4KA     384
	#define PAGE_KEY_L4KB     426
	#define PAGE_KEY_LINE5    274
	#define PAGE_KEY_L5K1	    0
	#define PAGE_KEY_L5K2	    132
	#define PAGE_KEY_L5K3	    342
	#define PAGE_KEY_L5K4     438
	
	#define PAGE_KEY_W        40
	#define PAGE_KEY_H        40
	
	#define PAGE_KEY_CW       70
	#define PAGE_KEY_RW       120
	#define PAGE_KEY_NW       202
	#define PAGE_KEY_BW       92
#else
	#define PAGE_KEY_TXTL		82
	#define PAGE_KEY_TXTH1	    24
	#define PAGE_KEY_TXTW		250
	#define PAGE_KEY_TXTH		30
	
	#define PAGE_KEY_LINE1    90
	#define PAGE_KEY_L1K1	    24
	#define PAGE_KEY_L1K2	    68
	#define PAGE_KEY_L1K3     110
	#define PAGE_KEY_L1K4     154
	#define PAGE_KEY_L1K5	    196
	#define PAGE_KEY_L1K6	    236
	#define PAGE_KEY_L1K7	    282
	#define PAGE_KEY_L1K8     326
	#define PAGE_KEY_L1K9	    370
	#define PAGE_KEY_L1KA     414
	#define PAGE_KEY_LINE2    140
	#define PAGE_KEY_L2K1	    0
	#define PAGE_KEY_L2K2	    44
	#define PAGE_KEY_L2K3	    88
	#define PAGE_KEY_L2K4     132
	#define PAGE_KEY_L2K5	    176
	#define PAGE_KEY_L2K6	    220
	#define PAGE_KEY_L2K7	    262
	#define PAGE_KEY_L2K8     306
	#define PAGE_KEY_L2K9	    350
	#define PAGE_KEY_L2KA     394
	#define PAGE_KEY_L2KB     438
	#define PAGE_KEY_LINE3    184
	#define PAGE_KEY_L3K1	    20
	#define PAGE_KEY_L3K2	    64
	#define PAGE_KEY_L3K3	    106
	#define PAGE_KEY_L3K4     150
	#define PAGE_KEY_L3K5	    194
	#define PAGE_KEY_L3K6	    236
	#define PAGE_KEY_L3K7	    278
	#define PAGE_KEY_L3K8     322
	#define PAGE_KEY_L3K9	    366
	#define PAGE_KEY_L3KA     408
	#define PAGE_KEY_LINE4    228
	#define PAGE_KEY_L4K1	    0
	#define PAGE_KEY_L4K2	    44
	#define PAGE_KEY_L4K3	    86
	#define PAGE_KEY_L4K4     130
	#define PAGE_KEY_L4K5	    172
	#define PAGE_KEY_L4K6	    214
	#define PAGE_KEY_L4K7	    258
	#define PAGE_KEY_L4K8     300
	#define PAGE_KEY_L4K9	    342
	#define PAGE_KEY_L4KA     384
	#define PAGE_KEY_L4KB     426
	#define PAGE_KEY_LINE5    274
	#define PAGE_KEY_L5K1	    0
	#define PAGE_KEY_L5K2	    132
	#define PAGE_KEY_L5K3	    342
	#define PAGE_KEY_L5K4     438
	
	#define PAGE_KEY_W        40
	#define PAGE_KEY_H        40
	
	#define PAGE_KEY_CW       70
	#define PAGE_KEY_RW       120
	#define PAGE_KEY_NW       202
	#define PAGE_KEY_BW       92													
#endif

///////////////////////////////////////////////////////////
//Ò³Ãæ×ÓÏîÄ¿½á¹¹Ìå
const PAGE_ITEM_T page_KeyBoard_item[] =  //°´¼üÅÅÐò´Ó×óÖÁÓÒ£¬´ÓÉÏµ½ÏÂ
{
	{ 
		'1',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K1,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'2',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K2,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'3',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K3,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'4',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K4, PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'5',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K5,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'6',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K6,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'7',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K7,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'8',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K8, PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'9',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1K9,	PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'0',	
		1,			//´¥¿Ø							
		PAGE_KEY_L1KA, PAGE_KEY_LINE1,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'q',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K1,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'w',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K2,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'e',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K3,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'r',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K4, PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		't',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K5,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'y',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K6,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'u',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K7,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'i',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K8, PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'o',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2K9,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'p',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2KA, PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'<',	
		1,			//´¥¿Ø							
		PAGE_KEY_L2KB,	PAGE_KEY_LINE2,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'a',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K1,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		's',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K2,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'd',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K3, PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'f',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K4,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'g',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K5,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'h',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K6,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'j',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K7, PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'k',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K8,	PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'l',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3K9, PAGE_KEY_LINE3,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'>',	
		1,			//´¥¿Ø							
		PAGE_KEY_L3KA,	PAGE_KEY_LINE3,
		PAGE_KEY_CW, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'.',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K1,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'z',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K2,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'x',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K3, PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'c',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K4,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'v',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K5,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'b',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K6,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'n',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K7, PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'm',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K8,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'!',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4K9, PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'?',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4KA,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'@',	
		1,			//´¥¿Ø							
		PAGE_KEY_L4KB,	PAGE_KEY_LINE4,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'#',	
		1,			//´¥¿Ø							
		PAGE_KEY_L5K1,	PAGE_KEY_LINE5,
		PAGE_KEY_RW, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		' ',	
		1,			//´¥¿Ø							
		PAGE_KEY_L5K2, PAGE_KEY_LINE5,
		PAGE_KEY_NW, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'*',	
		1,			//´¥¿Ø							
		PAGE_KEY_L5K3,	PAGE_KEY_LINE5,
		PAGE_KEY_BW, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		'\\',	
		0,			//´¥¿Ø							
		PAGE_KEY_L5K4,	PAGE_KEY_LINE5,
		PAGE_KEY_W, PAGE_KEY_H,
		{0},
		0	
	},

	{ 
		0,	
		0,			//t0						
		PAGE_KEY_TXTL,	PAGE_KEY_TXTH1,
		PAGE_KEY_TXTW, PAGE_KEY_TXTH,
		{0},
		0	
	},
};

//Ò³Ãæ½á¹¹Ìå
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
			if((page_KeyBoard_item[item].touch_en))  //¼ì²é´¥¿Ø
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
		pageKeyBoardItemUpdate();   //Ò³ÃæË¢ÐÂ
	}
}

static void pageKeyBoardItemUpdate(void)
{
	LCD_Fill(page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y,
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x+100, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y+20, WHITE);
	
	LCD_ShowString_hz16x16(page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_x, 
				page_KeyBoard_item[page_KeyBoard.page_item_num-1].start_pos_y, 100, 16, 16, keyBoardInfo.buff);
}


static void pageKeyBoardTPUpdate(u8 item)
{
	switch(letter_table[item])
	{
		case '<': //É¾³ý×îºóÒ»¸ö×Ö·û
			if (keyBoardInfo.buffLen > 0)
				keyBoardInfo.buffLen--;
			keyBoardInfo.buff[keyBoardInfo.buffLen] = 0;
			break;
		case '#': //É¾³ýÈ«²¿×Ö·û
			keyBoardInfo.buff[0] = 0;
			keyBoardInfo.buffLen = 0;
			break;
		case '*'://Ö±½Ó·µ»Ø
			memset(&keyBoardInfo, 0, sizeof(KEYBOARD_INFO));	
			//´Ë´¦ÇÐ»»Ò³Ãæ
			gPageInfo.cur_page_idx = prePage;
//			memset(&gPagePara, 0, sizeof(page_para));
//			break;
		case '>': //È·ÈÏÍË³ö
			if (keyBoardInfo.buffLen > 0)
			{
				u8 buff[14];
				u8 len = 0;
				
				keyBoardInfo.strUpdate = 1;
				len = pageKeyBoardMakeReplyFrame(buff);
				uartSendbuffer(buff, len);
			}
			//´Ë´¦ÇÐ»»Ò³Ãæ
			gPageInfo.cur_page_idx = prePage;
			break;
		default://×Ö·û´¦Àí
			keyBoardInfo.buff[keyBoardInfo.buffLen] = letter_table[item];
			if (keyBoardInfo.buffLen < 12) //×î¶àÊäÈë12¸ö×Ö·û
			{
				keyBoardInfo.buffLen++;
				keyBoardInfo.buff[keyBoardInfo.buffLen] = 0; //Ìí¼Ó×Ö·û´®½áÊø·û
			}
			break;
	}
}

static u8 pageKeyBoardMakeReplyFrame(u8* buff)
{
	u8 i = 0;
	u8 k = 0;
	
	buff[i] = 0x90;   //Ö¡Í·
	i++;
	buff[i] = 0x0a;   //Ò³ÃæID
	i++;
	buff[i] = 0x01;   //ÉèÖÃÏî
	i++;
	buff[i] = '"';
	i++;
	while(keyBoardInfo.buff[k] != 0)  //¿½±´×Ö·û´®
	{
		buff[i] = keyBoardInfo.buff[k];
		i++;
		k++;
	}
	buff[i] = '"';
	i++;
	buff[i] = 0xff;
	i++;
	buff[i] = 0xff;
	i++;
	buff[i] = 0xff;
	i++;
	return i;
}

