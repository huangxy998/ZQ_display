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

#define PAGE_MAIN_BACK_COLOR    BLACK


PAGE_MAIN_PARA_T gPageMainPara;
PARA_DEVICE_STATE gParaDeviceState;


static void pageBasicItemMode(void);

static void pageBasicInit(void);
static void pageBasicUpdate(void);
static void pageBasicItemUpdate(void);
static void pageBasicSendTime(u8 *buff);


///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��

///////////////////////////////////////////////////////////////////////////////////////////////////
//STANDtime
///////////////////////////////////////////////////////////////////////////////////////////////////

static const ITEM_IDX_T item_id2indx[] = 
{
	{ 14, 'n', 0},  //n0
	{ 8, 'n', 1},  //n1
	{ 9, 'n', 2},  //n2
	{ 10, 'n', 3},  //n3
	{ 11, 'n', 4},  //n4
	{ 12, 'n', 5}, //n5
	{ 13, 'n', 6}, //n6
	{ 7, 'n', 14}, //n14

	{ 16, 't', 0}, //t0
	{ 17, 't', 5}, //t5
	{ 15, 't', 6}, //t6
	{ 18, 't', 7}, //t7

	{ 23, 'x', 0}, 
	{ 3, 'f', 0}, 
};
#ifdef LCD_SIZE_480X320
const PAGE_ITEM_T page_basic_item[] =
{           //b0�ؼ�
	{
		0,     //id
		1,      //֧�ִ���
		
		0,0,    //��ʼ����
		132,67, //���
		
		{0x65,0x01,0x20,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

 //b5�ؼ�
	{
		1,     //id
		1,      //֧�ִ���
		
		136,3,    //��ʼ����
		165,62, //���
		
		{0x65,0x01,0x17,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //b4�ؼ�
	{
		2,	   //id
		1,		//֧�ִ���
		
		314,3,	  //��ʼ����
		68,28, //���
		
		{0x65,0x01,0x03,0x00,0xff,0xff,0xff},
		0  
	},

	             //b3�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		314,35,    //��ʼ����
		66,31, //���
		
		{0x65,0x01,0x02,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //b1�ؼ�
	{
		35,     //id
		1,      //֧�ִ���
		
	 	405,4,    //��ʼ����
		70,28, 	//���
		
		{0x65,0x01,0x23,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //bt1�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
		8,101,    //��ʼ����
		67,41,//���
		
		{0x65,0x01,0x1d,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //bt2�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
		10,150,    //��ʼ����
		64,36,//���
		
		{0x65,0x01,0x1e,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},


	            //n14�ؼ�
	{	
		7,      //id
		0,      //��֧�ִ���
		
		405,42,  //��ʼ����
		70,28,//���
		
		{0},
		0       //Ĭ��0
	},


	            //n1�ؼ�
	{	
		8,      //id
		0,      //��֧�ִ���
		
		42,74,  //��ʼ����
		50,25,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n2�ؼ�
	{	
		9,      //id
		0,      //��֧�ִ���
		
		126,74,  //��ʼ����
		54,25,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n3�ؼ�
	{	
		10,      //id
		0,      //��֧�ִ���
		
		196,74,  //��ʼ����
		52,25,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n4�ؼ�
	{	
		11,      //id
		0,      //��֧�ִ���
		
		272,74,  //��ʼ����
		47,24,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n5�ؼ�
	{	
		12,      //id
		0,      //��֧�ִ���
		
		336,74,  //��ʼ����
		49,24,//���
		
		{0},
		0       //Ĭ��0
	},


	            //n6�ؼ�
	{	
		13,      //id
		0,      //��֧�ִ���
	
		425,74,  //��ʼ����
		49,24,//���
		
		{0},
		0       //Ĭ��0
	},



	          //n0�ؼ�
	{	
		14,      //id
		0,      //��֧�ִ���
	
		87,110,  //��ʼ����
		330,128,//���
		
		{0},
		0       //Ĭ��0
	},

	            //t6�ؼ�
	{	
		15,      //id
		0,      //��֧�ִ���
	
		428,194,  //��ʼ����
		39,30,//���
		
		{0},
		0       //Ĭ��0
	},

	          //t0�ؼ�
	{	
		16,      //id
		0,      //��֧�ִ���
	
		66,248,  //��ʼ����
		260,37,//���
		
		{0},
		0       //Ĭ��0
	},

	          //t5�ؼ�
	{	
		17,      //id
		0,      //��֧�ִ���
	
		352,250,  //��ʼ����
		131,36,//���
		
		{0},
		0       //Ĭ��0
	},


	           //t7�ؼ�
	{	
		18,      //id
		0,      //��֧�ִ���
	
		352,290,  //��ʼ����
		128,32,//���
		
		{0},
		0       //Ĭ��0
	}
};

#else
const PAGE_ITEM_T page_basic_item[] =
{           //b0�ؼ�
	{
		0,     //id
		1,      //֧�ִ���
		
		0,0,    //��ʼ����
		95,48, //���
		
		{0x65,0x01,0x21,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

 //b5�ؼ�
	{
		1,     //id
		1,      //֧�ִ���
		
		142,4,    //��ʼ����
		110,46, //���
		
		{0x65,0x01,0x16,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //b4�ؼ�
	{
		2,     //id
		1,      //֧�ִ���
		
		260,1,    //��ʼ����
		64,24, //���
		
		{0x65,0x01,0x02,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //b3�ؼ�
	{
		3,     //id
		1,      //֧�ִ���
		
		260,28,    //��ʼ����
		64,24, //���
		
		{0x65,0x01,0x01,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //bt0�ؼ�
	{
		4,     //id
		1,      //֧�ִ���
		
		0,71,    //��ʼ����
		48,24,//���
		
		{0x65,0x01,0x1d,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //bt1�ؼ�
	{
		5,     //id
		1,      //֧�ִ���
		
		6,75,    //��ʼ����
		60,30,//���
		
		{0x65,0x01,0x1e,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //bt2�ؼ�
	{
		6,     //id
		1,      //֧�ִ���
		
		6,112,    //��ʼ����
		60,30,//���
		
		{0x65,0x01,0x1d,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},


	            //n14�ؼ�
	{	
		7,      //id
		0,      //��֧�ִ���
		
		330,34,  //��ʼ����
		66, 22,//���
		
		{0},
		0       //Ĭ��0
	},


	            //n1�ؼ�
	{	
		8,      //id
		0,      //��֧�ִ���
		
		30,54,  //��ʼ����
		45,16,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n2�ؼ�
	{	
		9,      //id
		0,      //��֧�ִ���
		
		96,54,  //��ʼ����
		45,16,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n3�ؼ�
	{	
		10,      //id
		0,      //��֧�ִ���
		
		162,54,  //��ʼ����
		45,16,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n4�ؼ�
	{	
		11,      //id
		0,      //��֧�ִ���
		
		224,54,  //��ʼ����
		40,16,//���
		
		{0},
		0       //Ĭ��0
	},


	           //n5�ؼ�
	{	
		12,      //id
		0,      //��֧�ִ���
		
		278,54,  //��ʼ����
		45,16,//���
		
		{0},
		0       //Ĭ��0
	},


	            //n6�ؼ�
	{	
		13,      //id
		0,      //��֧�ִ���
		
		354,54,  //��ʼ����
		29,16,//���
		
		{0},
		0       //Ĭ��0
	},



	          //n0�ؼ�
	{	
		14,      //id
		0,      //��֧�ִ���
		
		86,77,  //��ʼ����
		260,100,//���
		
		{0},
		0       //Ĭ��0
	},

	            //t6�ؼ�
	{	
		15,      //id
		0,      //��֧�ִ���
		
		351,132,  //��ʼ����
		39,30,//���
		
		{0},
		0       //Ĭ��0
	},

	          //t0�ؼ�
	{	
		16,      //id
		0,      //��֧�ִ���
		
		60,186,  //��ʼ����
		190,30,//���
		
		{0},
		0       //Ĭ��0
	},

	          //t5�ؼ�
	{	
		17,      //id
		0,      //��֧�ִ���
		
		292,186,  //��ʼ����
		104,26,//���
		
		{0},
		0       //Ĭ��0
	},


	           //t7�ؼ�
	{	
		18,      //id
		0,      //��֧�ִ���
		
		292,216,  //��ʼ����
		104,26,//���
		
		{0},
		0       //Ĭ��0
	}
};

#endif


//ҳ��ṹ��
const PAGE_T page_basic = 
{
		
	PAGE_ID_STANDTIME,	
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_basic_item)/sizeof(PAGE_ITEM_T),
	
 	pageBasicInit,	
 	pageBasicUpdate
};

//////////////////////////////////////////////////////////
//���� ��� �ְ� ���
const u8 page_item_func_name[4][2] = 
{
	{CM_48X48_ZHI40, CM_48X48_NENG20},
	{CM_48X48_HUN30, CM_48X48_DIAN30},
	{CM_48X48_FEN10, CM_48X48_BAN30},
	{CM_48X48_QING10,CM_48X48_DIAN30}	
};
//ģʽ��ʾ��ɫ
const u16 page_item_func_name_color[4] = 
{
	GREEN, BLUE, BROWN, RED 
};


//��������ɫ
const u16 page_item_sensity_color[3] =
{
	YELLOW, GREEN, RED
};

//���и�
const u8 page_item_DZG_name[4][3] = 
{
	{CM_16X16_SPACE, CM_16X16_SPACE,	CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_DI10,		CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_ZHONG10,  CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_GAO10,	CM_16X16_SPACE}
};

///////////////////////////////////////////////////////////
const _bmp_info bmp_mainPage =
{
	BASIC_PAGE_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};
#ifndef LCD_SIZE_480X320
const _bmp_info bmp_menuPageProgressOn =
{
	MENU_PAGE_PROGRESSFULL_OFFSET,
	222,
	13
};

const _bmp_info bmp_menuPageSDOn =
{
	BASIC_PAGE_SD_ON_OFFSET,
	32,
	28
};

const _bmp_info bmp_menuPageSDOff =
{
	BASIC_PAGE_SD_OFF_OFFSET,
	32,
	28
};

const _bmp_info bmp_menuPageAddOn =
{
	BASIC_PAGE_ADD_ON_OFFSET,
	43,
	22
};

const _bmp_info bmp_menuPageAddOff =
{
	BASIC_PAGE_ADD_OFF_OFFSET,
	43,
	22
};
#endif

///////////////////////////////////////////////////////////
//����ҳ���ʼ��
static void pageBasicInit(void)
{
//	u8 tmp_buff[8];
	show_bmp_in_flash(0,0,bmp_mainPage.width,bmp_mainPage.height,bmp_mainPage.addr);
//	if(gPageMainPara.add_flg)
//	{
//		show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOn.width, bmp_menuPageAddOn.height, bmp_menuPageAddOn.addr);
//	}
//	else
//	{
//		show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOff.width, bmp_menuPageAddOff.height, bmp_menuPageAddOff.addr);
//	}
}

//����ҳ��ˢ��
static void pageBasicUpdate(void)
{
	u8 item;

	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_basic.page_item_num; item++)
		{
			if(page_basic_item[item].touch_en)  //��鴥��
			{
				if( ( touch_up_pos.x >= page_basic_item[item].start_pos_x ) && ( touch_up_pos.x < page_basic_item[item].start_pos_x + page_basic_item[item].width)  && \
					( touch_up_pos.y >= page_basic_item[item].start_pos_y ) && ( touch_up_pos.y < page_basic_item[item].start_pos_y + page_basic_item[item].height) )
				{
					gIDInfo.cmdUpdate = 1;
					memcpy(&gIDInfo.cmdPage.start, &page_basic_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageBasicItemUpdate();   //ҳ��ˢ��
	}
}

const char* modeTable[] = {"�� ��", "�� ��", "�� ��", "�� ��"};
///////////////////////////////////////////////////////////
//��ʾ����
static void pageBasicItemUpdate(void)
{	
	int j = 0;
	u16 len = 0;
	u8 timebuff[22] = {0};
	
	LCD_SetFrontColor(GREEN);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);           //������ɫ
	for( j = 0; j < sizeof(item_id2indx)/sizeof(ITEM_IDX_T); j++ )
	{
		if(j == 0)
		{
			len = strlen((char*)&gPagePara.n_val[0][0]);
			LCD_Fill(page_basic_item[item_id2indx[j].id].start_pos_x, page_basic_item[item_id2indx[j].id].start_pos_y,
			page_basic_item[item_id2indx[j].id].start_pos_x + (5 - len)*64, 
			page_basic_item[item_id2indx[j].id].start_pos_y+ page_basic_item[item_id2indx[j].id].height, BLACK);
			LCD_ShowString(page_basic_item[item_id2indx[j].id].start_pos_x+(5 - len)*64, 
					page_basic_item[item_id2indx[j].id].start_pos_y, page_basic_item[item_id2indx[j].id].width, 128, 128, gPagePara.n_val[item_id2indx[j].itemIndx]);
			continue;
		}
		switch(item_id2indx[j].itemType)
		{
			case 'n':
				len = strlen((char*)gPagePara.n_val[item_id2indx[j].itemIndx]);
				if(len < 5)
					LCD_Fill(page_basic_item[item_id2indx[j].id].start_pos_x+len*8, page_basic_item[item_id2indx[j].id].start_pos_y,
						page_basic_item[item_id2indx[j].id].start_pos_x + 5*8, 
						page_basic_item[item_id2indx[j].id].start_pos_y+ 16, BLACK);
				LCD_ShowString(page_basic_item[item_id2indx[j].id].start_pos_x, 
					page_basic_item[item_id2indx[j].id].start_pos_y, 100, 16, 16, gPagePara.n_val[item_id2indx[j].itemIndx]);
				break;
			case 't':
				len = strlen((char*)gPagePara.t_string[item_id2indx[j].itemIndx]);
				if(len < 8)
					LCD_Fill(page_basic_item[item_id2indx[j].id].start_pos_x+len*12, page_basic_item[item_id2indx[j].id].start_pos_y,
						page_basic_item[item_id2indx[j].id].start_pos_x + 8*12, 
						page_basic_item[item_id2indx[j].id].start_pos_y+ 24, BLACK);
				LCD_ShowString(page_basic_item[item_id2indx[j].id].start_pos_x, 
					page_basic_item[item_id2indx[j].id].start_pos_y, 160, 24, 24, gPagePara.t_string[item_id2indx[j].itemIndx]);
				break;
			case 'x':
				break;
			case 'f':
				break;
			default:
				break;
		}
	} 
	pageBasicItemMode();
	LCD_Fill(page_basic_item[2].start_pos_x + 70, page_basic_item[2].start_pos_y + 2,
			page_basic_item[2].start_pos_x + page_basic_item[2].width + 70, 
			page_basic_item[2].start_pos_y+ page_basic_item[2].height - 2, atoi((const char *)gPagePara.b_bc[1]));
	LCD_SetFrontColor(GREEN);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);           //������ɫ
	Get_TimeStr(timebuff);
	LCD_ShowString(124, 286+6, 190, 16, 16, timebuff);
	pageBasicSendTime(timebuff);
#ifdef LCD_SIZE_480X320
	if(gPagePara.t_string[30][1] == 'n')  // U������
	{
		//ˢ����Ϣ	
		LCD_ShowString_hz16x16(32, 292, 64, 16, 16, "U �̴洢");
	}
	else if(gPagePara.t_string[31][1] == 'n')  //SD��״̬
	{
		//ˢ����Ϣ
		LCD_ShowString_hz16x16(32, 292, 64, 16, 16, "SD���洢");
	}
	else if((gPagePara.t_string[30][1] == 'f') || (gPagePara.t_string[31][1] == 'f'))//U�̻�SD��������
	{
		u16 color = POINT_COLOR;
		//ˢ����Ϣ
		POINT_COLOR = RED;
		LCD_ShowString_hz16x16(32, 292, 64, 16, 16, "�洢�쳣");
		POINT_COLOR = color;
	}
	if(gPagePara.t_string[32][1] == 'n')  //����״̬
	{
		//ˢ����Ϣ
		LCD_ShowString_hz16x16(10, 216, 64, 16, 16, "��������");
	}
	else if(gPagePara.t_string[32][1] == 'f')
	{
		u16 color = POINT_COLOR;
		//ˢ����Ϣ
		POINT_COLOR = RED;
		LCD_ShowString_hz16x16(10, 216, 64, 16, 16, "�����쳣");
		POINT_COLOR = color;
	}
	if (gPagePara.x_str[3][0] == '1')
	{
		LCD_ShowString_hz16x16(18, 188, 64, 16, 16, "�ۼӿ�");
	}
	else
	{
		u16 color = POINT_COLOR;
		POINT_COLOR = RED;
		LCD_ShowString_hz16x16(18, 188, 64, 16, 16, "�ۼӹ�");
		POINT_COLOR = color;
	}
#endif
}



///////////////////////////////////////////////////////////
//ģʽ����
static void pageBasicItemMode(void)
{
	u8 i;

	for(i = 0; i < 4; i++)
	{
		if(strcmp( (const char*)gPagePara.x_str, modeTable[i]) == 0)
		{
			break;
		}
	}
	if(i < 4)
	{
		LCD_SetFrontColor(page_item_func_name_color[i]);  //����ɫ
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);           //������ɫ
		LCD_ShowHZ(	page_basic_item[1].start_pos_x+32, 
					page_basic_item[1].start_pos_y+6, 
					page_item_func_name[i][0], 48, 0 );
		LCD_ShowHZ(	page_basic_item[1].start_pos_x+48+32, 
					page_basic_item[1].start_pos_y+6, 
					page_item_func_name[i][1], 48, 0 );
	}
}

static void pageBasicSendTime(u8 *buff)
{
	//2017-09-09 17:38:16
	static u8 updateFlg = 0;
	static u8 sec = 0;

	if(updateFlg == 0)
	{
		updateFlg = 1;
		sec = buff[18];
	}
	if(updateFlg == 1)
	{
		if (sec != buff[18])
		{
			u8 sbuff[27] = {0x90, 0x01, 0x01, '"', '2', '0', '1', '7', '-', '0', '8', 
				'-', '3', '0', ' ', '1', '1', ':', '2', '2', ':', '3', '3', '"', 0xff,0xff,0xff};
			updateFlg = 2;
			memcpy((char*)&sbuff[4], buff, 19);
			uartSendbuffer((u8*)&sbuff, sizeof(sbuff));
		}
	}
}

#if 0

//�����ȸ���
static void pageBasicItemSensity(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.sensity++;
		if(gPageMainPara.sensity >= 3)
			gPageMainPara.sensity = 0;

		LCD_Fill(page_basic_item[BASIC_ITEM_SENSITY].start_pos_x + 45, page_basic_item[BASIC_ITEM_SENSITY].start_pos_y + 2,
			page_basic_item[BASIC_ITEM_SENSITY].start_pos_x + page_basic_item[BASIC_ITEM_SENSITY].width - 5, 
			page_basic_item[BASIC_ITEM_SENSITY].start_pos_y+ page_basic_item[BASIC_ITEM_SENSITY].height - 2, page_item_sensity_color[gPageMainPara.sensity]);
		gIDInfo.cmdUpdate = 1;
		gIDInfo.cmdPage.start = 0x65;
		gIDInfo.cmdPage.touchStatus = 1;
		gIDInfo.cmdPage.btnID = 0x03;
		gIDInfo.cmdPage.pageID = PAGE_ID_STANDTIME;
	}
}

//Ԥ����
static void pageBasicItemPreset(void)
{		
	u8 tmp_buff[8];
	
	if(gPageInfo.toucged_up)
	{
		gIDInfo.cmdUpdate = 1;
		gIDInfo.cmdPage.start = 0x65;
		gIDInfo.cmdPage.touchStatus = 1;
		gIDInfo.cmdPage.btnID = 0x02;
		gIDInfo.cmdPage.pageID = PAGE_ID_STANDTIME;
		
		gPageMainPara.pre_set += 10;
		if(gPageMainPara.pre_set > 100)
			gPageMainPara.pre_set = 0;
	
		if( gPageMainPara.pre_set >= 1000 )
		{
			sprintf((char*)tmp_buff," %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 100 )
		{
			sprintf((char*)tmp_buff,"  %d ", gPageMainPara.pre_set );
		}
		else if( gPageMainPara.pre_set >= 10 )
		{
			sprintf((char*)tmp_buff,"  %d  ", gPageMainPara.pre_set );
		}
		LCD_SetFrontColor(WHITE);  //����ɫ
		LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
		
//		LCD_SetFont(&Font8x16);
//		LCD_DrawString(page_basic_item[2].start_pos_x + 45, page_basic_item[2].start_pos_y + 4, tmp_buff);
		LCD_ShowString(page_basic_item[BASIC_ITEM_PRESET].start_pos_x + 45, page_basic_item[BASIC_ITEM_PRESET].start_pos_y + 4, 100, 16, 16, tmp_buff);
	}
}

//�ۼ�
static void pageBasicItemAdd(void)
{
	if(gPageInfo.toucged_up)
	{
		gPageMainPara.add_flg = !gPageMainPara.add_flg;
		if(gPageMainPara.add_flg)
		{
			show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOn.width, bmp_menuPageAddOn.height, bmp_menuPageAddOn.addr);
		}
		else
		{
			show_bmp_in_flash(page_basic_item[BASIC_ITEM_ADD].start_pos_x, page_basic_item[BASIC_ITEM_ADD].start_pos_y, bmp_menuPageAddOff.width, bmp_menuPageAddOff.height, bmp_menuPageAddOff.addr);
		}
		gIDInfo.cmdUpdate = 1;
		gIDInfo.cmdPage.start = 0x65;
		gIDInfo.cmdPage.touchStatus = 1;
		gIDInfo.cmdPage.btnID = 0x1f;
		gIDInfo.cmdPage.pageID = PAGE_ID_STANDTIME;
	}
}

//ʱ����ʾ
static void pageBasicItemShowTime(void)
{
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 16, 16, 16, "20");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+16, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+32, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, "-");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+40, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+56, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, "-");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+64, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+80, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, " ");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+88, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+104, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, ":");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+112, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
	LCD_ShowString(page_basic_item[BASIC_ITEM_TIME].start_pos_x+128, page_basic_item[BASIC_ITEM_TIME].start_pos_y, 140, 16, 16, ":");
	LCD_ShowxNum(page_basic_item[BASIC_ITEM_TIME].start_pos_x+136, page_basic_item[BASIC_ITEM_TIME].start_pos_y,calendar.w_year,2,16);
}

//������logoʱ����˵�����
static void pageBasicItemEnterMenu(void)
{
	if(gPageInfo.toucged_up)
	{
//		gPageInfo.cur_page_idx = PAGE_ID_MENU;  
		gIDInfo.cmdUpdate = 1;
		gIDInfo.cmdPage.start = 0x65;
		gIDInfo.cmdPage.touchStatus = 1;
		gIDInfo.cmdPage.btnID = 0x21;
		gIDInfo.cmdPage.pageID = PAGE_ID_MAIN;
	}
}

//�����ʾ
static void pageBasicItemShowDenoCnt(void)
{
	u16 tmp;
	
	LCD_SetFrontColor(WHITE);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR); 
	tmp = gPageMainPara.hundred_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.fifty_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+68, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.twenty_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+138, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.ten_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+200, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.five_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+258, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);
	tmp = gPageMainPara.error_cnt%1000;
	LCD_ShowNum(page_basic_item[BASIC_ITEM_DENO].start_pos_x+328, page_basic_item[BASIC_ITEM_DENO].start_pos_y,tmp,4,16);	
}

//��ʾ��ǰ����
static void pageBasicItemShowCurCnt(void)
{
	LCD_SetFrontColor(LIGHTBLUE);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNumNull(page_basic_item[BASIC_ITEM_CUR_CNT].start_pos_x, page_basic_item[BASIC_ITEM_CUR_CNT].start_pos_y,gPageMainPara.cur_cnt%10000,5,128);
}

//��ʾ����
static void pageBasicItemShowCnt(void)
{
	LCD_SetFrontColor(LIGHTBLUE);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNum(page_basic_item[BASIC_ITEM_CNT].start_pos_x, page_basic_item[BASIC_ITEM_CNT].start_pos_y,gPageMainPara.total_cnt%10000,5,24);	
}

//��ʾ���
static void pageBasicItemShowSum(void)
{
	
	LCD_SetFrontColor(LIGHTBLUE);  //����ɫ
	LCD_SetBackColor(PAGE_MAIN_BACK_COLOR);
	LCD_ShowNum(page_basic_item[BASIC_ITEM_SUM].start_pos_x, page_basic_item[BASIC_ITEM_SUM].start_pos_y,gPageMainPara.sum%10000,5,24);	
}

//��ʾSD��״̬
static void pageBasicItemShowSDStatus(void)
{
	if (gPageMainPara.sd_flg)
	{
		show_bmp_in_flash(page_basic_item[BASIC_ITEM_SD].start_pos_x, page_basic_item[BASIC_ITEM_SD].start_pos_y,bmp_menuPageSDOn.width,bmp_menuPageSDOn.height,bmp_menuPageSDOn.addr);
	}
	else
	{
		show_bmp_in_flash(page_basic_item[BASIC_ITEM_SD].start_pos_x, page_basic_item[BASIC_ITEM_SD].start_pos_y,bmp_menuPageSDOff.width,bmp_menuPageSDOff.height,bmp_menuPageSDOff.addr);
	}
}

//��ʾ����״̬
static void pageBasicItemShowNetStatus(void)
{
	if (gPageMainPara.net_flg)
	{
		;
	}
	else
	{
		;
	}
}

//��ʾ���ֺ�
static void pageBasicItemShowSerialNum(void)
{
	LCD_ShowString(page_basic_item[BASIC_ITEM_SERIAL].start_pos_x, page_basic_item[BASIC_ITEM_SERIAL].start_pos_y, 144, 24, 24, gPageMainPara.serial);
}
#endif

