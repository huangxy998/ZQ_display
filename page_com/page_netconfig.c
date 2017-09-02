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

#include "char_model.h"
#include "page.h"
#include "touch.h"
#include "lcd_com.h"

typedef struct
{
	u8 ip[4];
	u8 mask[4];
	u8 gate[4];
	u8 server[4];
	u16 port;
	u8 mac[5];

}IP_INFO;

#ifdef LCD_SIZE_480X320
	#define PAGE_NET_BNL1		386
	#define PAGE_NET_BNH1		30
	#define PAGE_NET_BNH2		82
	#define PAGE_NET_BNH3		132
	#define PAGE_NET_BNW		78
	#define PAGE_NET_BNH		38

	#define PAGE_NET_TL1		12
	#define PAGE_NET_TL2		266
	#define PAGE_NET_TH1		180
	#define PAGE_NET_TNW		200
	#define PAGE_NET_TH		  28

	#define PAGE_NET_NL1		122
	#define PAGE_NET_NH1		28
	#define PAGE_NET_NH2		58
	#define PAGE_NET_NH3		88
	#define PAGE_NET_NH4		118
	#define PAGE_NET_NH5		148
	#define PAGE_NET_NW		  248
	#define PAGE_NET_NH		  26

	#define PAGE_NET_BTL1		2
	#define PAGE_NET_BTH1		PAGE_NET_NH1
	#define PAGE_NET_BTH2		PAGE_NET_NH2
	#define PAGE_NET_BTH3		PAGE_NET_NH3
	#define PAGE_NET_BTH4		PAGE_NET_NH4
	#define PAGE_NET_BTW		248
	#define PAGE_NET_BTH		26

	#define PAGE_NET_BL1		25
	#define PAGE_NET_BL2		84
	#define PAGE_NET_BL3		143
	#define PAGE_NET_BL4		202
	#define PAGE_NET_BL5		260
	#define PAGE_NET_BL6		328
	#define PAGE_NET_BL7		404
	#define PAGE_NET_BH1		216
	#define PAGE_NET_BH2		270
	#define PAGE_NET_BW		  54
	#define PAGE_NET_BH		  40
#else
	#define PAGE_NET_BNL1		320
	#define PAGE_NET_BNH1		20
	#define PAGE_NET_BNH2		58
	#define PAGE_NET_BNH3		98
	#define PAGE_NET_BNW		65
	#define PAGE_NET_BNH		35

	#define PAGE_NET_TL1		6
	#define PAGE_NET_TL2		200
	#define PAGE_NET_TH1		135
	#define PAGE_NET_TNW		195
	#define PAGE_NET_TH		  22

	#define PAGE_NET_NL1		98
	#define PAGE_NET_NH1		22
	#define PAGE_NET_NH2		44
	#define PAGE_NET_NH3		66
	#define PAGE_NET_NH4		90
	#define PAGE_NET_NH5		112
	#define PAGE_NET_NW		  206
	#define PAGE_NET_NH		  20

	#define PAGE_NET_BTL1		2
	#define PAGE_NET_BTH1		20
	#define PAGE_NET_BTH2		43
	#define PAGE_NET_BTH3		65
	#define PAGE_NET_BTH4		86
	#define PAGE_NET_BTW		94
	#define PAGE_NET_BTH		20

	#define PAGE_NET_BL1		22
	#define PAGE_NET_BL2		68
	#define PAGE_NET_BL3		118
	#define PAGE_NET_BL4		170
	#define PAGE_NET_BL5		218
	#define PAGE_NET_BL6		274
	#define PAGE_NET_BL7		335
	#define PAGE_NET_BH1		160
	#define PAGE_NET_BH2		200
	#define PAGE_NET_BW		  45
	#define PAGE_NET_BH		  34
#endif
IP_INFO ipInfo;
u8      curDataIdx = 0;
u8      inputDataIdx = 0;
u8      inputDataErr = 0;

static void pageNetConfigInit(void);
static void pageNetConfigUpdate(void);
static void pageNetConfigItemUpdate(void);
static void pageNetTPUpdate(int item);
static u8 pageNetIPStr2Dec(u8 item, char* ipStr);
static u8 pageNetMakeReplyFrame(u8 item, u8* buff);




///////////////////////////////////////////////////////////
//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_NetConfig_item[] =
{     
	             //b0�ؼ�
	{
		13,     //id
		1,      //֧�ִ���
		
		PAGE_NET_BNL1, PAGE_NET_BNH1,    //��ʼ����
		PAGE_NET_BNW, PAGE_NET_BNH , //���
		
		{0x65,0x0a,0x0e,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //b1�ؼ�
	{
		14,     //id
		1,      //֧�ִ���
		
		PAGE_NET_BNL1,PAGE_NET_BNH2,    //��ʼ����
		PAGE_NET_BNW,PAGE_NET_BNH , //���
		
		{0x65,0x0a,0x13,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	           //b2�ؼ�
	{
		15,     //id
		1,      //֧�ִ���
		
		PAGE_NET_BNL1,PAGE_NET_BNH3,    //��ʼ����
		PAGE_NET_BNW,PAGE_NET_BNH , //���
		
		{0x65,0x0a,0x14,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b3�ؼ�
	{
		16,     //id
		1,      //֧�ִ���
		
		PAGE_NET_BL1,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x15,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b4�ؼ�
	{
		17,     //id
		1,      //֧�ִ���
		
		PAGE_NET_BL2,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x16,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b5�ؼ�
	{
		18,     //id
		1,      //֧�ִ���
		
	 	PAGE_NET_BL3,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x17,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b6�ؼ�
	{
		19,     //id
		1,      //֧�ִ���
		
	  	PAGE_NET_BL4,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x18,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b7�ؼ�
	{
		20,     //id
		1,      //֧�ִ���
		
	  	PAGE_NET_BL5,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x19,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //b8�ؼ�
	{
	21,     //id
		1,      //֧�ִ���
		
	 	PAGE_NET_BL6,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x1a,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	             //b9�ؼ�
	{
	22,     //id
		1,      //֧�ִ���
		
	 	PAGE_NET_BL7,PAGE_NET_BH1,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x1b,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	            //b10�ؼ�
	{
		23,     //id
		1,      //֧�ִ���
		
	 	PAGE_NET_BL1,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x1c,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b11�ؼ�
	{
		24,     //id
		1,      //֧�ִ���
		
	 	PAGE_NET_BL2,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x1d,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b12�ؼ�
	{
		25,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BL3,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x0f,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b13�ؼ�
	{
		26,     //id
		1,      //֧�ִ���
		
	   PAGE_NET_BL4,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x10,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b14�ؼ�
	{
		27,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BL5,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b15�ؼ�
	{
		28,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BL6,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x12,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	//b16�ؼ�
	{
		25,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BL7,PAGE_NET_BH2,    //��ʼ����
		PAGE_NET_BW,PAGE_NET_BH , //���
		
		{0x65,0x0a,0x0f,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b17�ؼ�
	{
		26,     //id
		1,      //֧�ִ���
		
	   PAGE_NET_BTL1,PAGE_NET_BTH1,    //��ʼ����
		PAGE_NET_BTW,PAGE_NET_BTH , //���
		
		{0x65,0x0a,0x10,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	             //b18�ؼ�
	{
		27,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BTL1,PAGE_NET_BTH2,    //��ʼ����
		PAGE_NET_BTW,PAGE_NET_BTH , //���
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},
	            //b19�ؼ�
	{
		28,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BTL1,PAGE_NET_BTH3,    //��ʼ����
		PAGE_NET_BTW,PAGE_NET_BTH , //���
		
		{0x65,0x0a,0x12,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	//b20�ؼ�
	{
		27,     //id
		1,      //֧�ִ���
		
	  PAGE_NET_BTL1,PAGE_NET_BTH4,    //��ʼ���� 
		PAGE_NET_BTW,PAGE_NET_BTH , //���
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //Ĭ��0
	},

	//t0�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_TL1,PAGE_NET_TH1,    //��ʼ����
		PAGE_NET_TNW,PAGE_NET_TH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t1�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_NL1,PAGE_NET_NH1,    //��ʼ����
		PAGE_NET_NW,PAGE_NET_NH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t2�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_NL1,PAGE_NET_NH2,    //��ʼ����
		PAGE_NET_NW,PAGE_NET_NH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t3�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_NL1,PAGE_NET_NH3,    //��ʼ����
		PAGE_NET_NW,PAGE_NET_NH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t4�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_NL1,PAGE_NET_NH4,    //��ʼ����
		PAGE_NET_NW,PAGE_NET_NH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t5�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_NL1,PAGE_NET_NH5,    //��ʼ����
		PAGE_NET_NW,PAGE_NET_NH , //���
		
		{0},
		0       //Ĭ��0
	},

	//t6�ؼ�
	{
		27,     //id
		0,     
		
		PAGE_NET_TL2,PAGE_NET_TH1,    //��ʼ����
		PAGE_NET_TNW,PAGE_NET_TH , //���
		
		{0},
		0       //Ĭ��0
	},
};

//ҳ��ṹ��
const PAGE_T page_NetConfig =
{ 
	PAGE_ID_VERSION,
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_NetConfig_item)/sizeof(PAGE_ITEM_T),
	
 	pageNetConfigInit,	
 	pageNetConfigUpdate
};

const _bmp_info bmp_NetConfig_Page =
{
	BASIC_PAGE_LOCAL_IP_OFFSET,
	LCD_HOR_SIZE,
	LCD_VER_SIZE
};

static void pageNetConfigInit(void)
{
	show_bmp_in_flash(0,0,bmp_NetConfig_Page.width,bmp_NetConfig_Page.height,bmp_NetConfig_Page.addr);
#if 0
	sprintf((char*)gPagePara.t_string[1], "%d.%d.%d.%d", ipInfo.ip[0], ipInfo.ip[1], ipInfo.ip[2], ipInfo.ip[3]);
	sprintf((char*)gPagePara.t_string[2], "%d.%d.%d.%d", ipInfo.mask[0], ipInfo.mask[1], ipInfo.mask[2], ipInfo.mask[3]);
	sprintf((char*)gPagePara.t_string[3], "%d.%d.%d.%d", ipInfo.gate[0], ipInfo.gate[1], ipInfo.gate[2], ipInfo.gate[3]);
	sprintf((char*)gPagePara.t_string[4], "%d.%d.%d.%d", ipInfo.server[0], ipInfo.server[1], ipInfo.server[2], ipInfo.server[3]);
	sprintf((char*)gPagePara.t_string[5], "%d:%d:%d:%d:%d", ipInfo.mac[0], ipInfo.mac[1], ipInfo.mac[2], ipInfo.mac[3], ipInfo.mac[4]);
#endif	
	curDataIdx = 0;
	inputDataIdx = 0;
	gPageInfo.need_update = 1;
}

static void pageNetConfigUpdate(void)
{
	u8 item;
	if(gPageInfo.toucged_up)
	{
		for(item = 0; item < page_NetConfig.page_item_num; item++)
		{
			if((page_NetConfig_item[item].touch_en))  //��鴥��
			{
			
				if( ( touch_up_pos.x >= page_NetConfig_item[item].start_pos_x ) && ( touch_up_pos.x < page_NetConfig_item[item].start_pos_x + page_NetConfig_item[item].width)  && \
					( touch_up_pos.y >= page_NetConfig_item[item].start_pos_y ) && ( touch_up_pos.y < page_NetConfig_item[item].start_pos_y + page_NetConfig_item[item].height) )
				{
					gPageInfo.need_update = 1;
					if (inputDataErr) //���������ʾ��Ϣ
					{
						inputDataErr = 0;
						gPagePara.t_string[6][0] = 0;//����ʾ�ַ�
						LCD_Fill(page_NetConfig_item[21+6].start_pos_x, page_NetConfig_item[21+6].start_pos_y,
				     		page_NetConfig_item[21+6].start_pos_x+page_NetConfig_item[21+6].width-4,
				     		page_NetConfig_item[21+6].start_pos_y+16, BLACK);
					}
					pageNetTPUpdate(item);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageNetConfigItemUpdate();   //ҳ��ˢ��
	}
	
}

static void pageNetConfigItemUpdate(void)
{
	int item;

	for(item = 0; item < 7; item++)
	{
		if ( item == curDataIdx+1 )
		{
			LCD_SetFrontColor(BLACK);
			LCD_SetBackColor(WHITE);
		}
		else
		{
			LCD_SetFrontColor(WHITE);
			LCD_SetBackColor(BLACK);
		}
		LCD_ShowString_hz16x16(page_NetConfig_item[item+21].start_pos_x, 
					page_NetConfig_item[item+21].start_pos_y, 160, 16, 16, gPagePara.t_string[item]);
	}
	LCD_SetFrontColor(WHITE);
	LCD_SetBackColor(BLACK);
}

const char charbuf[] = {0, 0,   0, '1', '2', '3', '4', '5',
	                    0, 0, '6', '7', '8', '9', '0', '.'};

static void pageNetTPUpdate(int item)
{
	switch(item)
	{
		case 3 :  
		case 4 :
		case 5 :
		case 6 :
		case 7 :		
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:  //��Щ�������ַ����룬ֱ�ӻ��漴��
			gPagePara.t_string[0][inputDataIdx] = charbuf[item];
			if (inputDataIdx < 15) //�������15���ַ�������ip�����ʽ����
			{
				inputDataIdx++;
				gPagePara.t_string[0][inputDataIdx] = 0; //����ַ���������
			}
			
			break;
		case 8 : //����ɾ����
			if (inputDataIdx > 0)
			{
				inputDataIdx--;
				gPagePara.t_string[0][inputDataIdx] = 0; //�����ǰ�ַ�
			}
			LCD_Fill(page_NetConfig_item[21].start_pos_x, page_NetConfig_item[21].start_pos_y,
			     page_NetConfig_item[21].start_pos_x+page_NetConfig_item[21].width-4,
			     page_NetConfig_item[21].start_pos_y+16, BLACK);
			break;
		case 16://ȷ�ϼ������ַ����й����飬����Ҫ���򿽱�����Ӧ�Ļ���
			if (pageNetIPStr2Dec(curDataIdx, (char*)gPagePara.t_string[0]))
			{
				memcpy(&gPagePara.t_string[curDataIdx+1][0], &gPagePara.t_string[0][0], inputDataIdx+1);
				LCD_Fill(page_NetConfig_item[21+curDataIdx+1].start_pos_x, page_NetConfig_item[21+curDataIdx+1].start_pos_y,
				     page_NetConfig_item[21+curDataIdx+1].start_pos_x+page_NetConfig_item[21+curDataIdx+1].width-4,
				     page_NetConfig_item[21+curDataIdx+1].start_pos_y+16, BLACK);
			}
			else
			{
				inputDataErr = 1;
				memcpy(gPagePara.t_string[6], "�������������", sizeof("�������������"));
			}
			break;
		case 17://����IP
		case 18://����
		case 19://����
		case 20://��������ַ
			curDataIdx = item - 17;
			LCD_Fill(page_NetConfig_item[21].start_pos_x, page_NetConfig_item[21].start_pos_y,
				 page_NetConfig_item[21].start_pos_x+page_NetConfig_item[21].width-4,
				 page_NetConfig_item[21].start_pos_y+16, BLACK);
			inputDataIdx = 0;
			gPagePara.t_string[0][0] = 0;
			break;
		case 2://����
		#if 1  //������
			gPageInfo.cur_page_idx = PAGE_ID_MENU;
			memset(&gPagePara, 0, sizeof(page_para));
		#endif
			//����ִ��
		case 0://�Զ�
			gIDInfo.cmdUpdate = 1;
			memcpy(&gIDInfo.cmdPage.start, &page_NetConfig_item[item].com_data[0], TOUCH_CMD_LEN);
			break;
		case 1://����
			{
				u8 sendbuff[28];
				u8 sendlen;
				u8 type = 1;
				while(type < 5)
				{
					sendlen = pageNetMakeReplyFrame(type, sendbuff);
					uartSendbuffer(sendbuff, sendlen);
					type++;
					delay_us(4);       //��ʱ4usȷ��֡��֮֡����һ�����
				}
			}
			break;
		default: break;	
	}
}

//������������1�����򷵻�0
static u8 pageNetIPStr2Dec(u8 item, char* ipStr)
{
	u8 datatmp[5];
	u8 idx = 0 ;
	u8 dataidx = 0 ;
	u8 datalen = 0;
	int curdata = 0 ;
	u8 *dataptr = 0;

	if (ipStr[0] == 0)
		return 0;
	
	while(ipStr[idx] != 0)
	{
		if(ipStr[idx] == '.')
		{
			if ((datalen == 0) || (datalen > 3) || (curdata > 255))
				return 0;
			datalen = 0;
			datatmp[dataidx] = curdata;  //ȡ��һ���Ϸ�����
			dataidx++;
			if(dataidx > 3) 
				return 0;
			curdata = 0;
			idx++;
			continue;
		}
		curdata = 10*curdata + ipStr[idx] - '0';
		datalen++;
		idx++;
	}
	if ((datalen == 0) || (datalen > 3) || (curdata > 255))
		return 0;
	datalen = 0;
	datatmp[dataidx] = curdata;  //ȡ�����һ���Ϸ�����
	if (dataidx != 3)
		return 0;
	switch(item)
	{
		case 0: dataptr = &ipInfo.ip[0];
			break;
		case 1: dataptr = &ipInfo.mask[0];
			break;
		case 2: dataptr = &ipInfo.gate[0];
			break;
		case 3: dataptr = &ipInfo.server[0];
			break;
		default: break;
	}
	if (dataptr != 0)
	{
		memcpy(dataptr, datatmp, 4);
	}
	else
		return 0;
	return 1;
	
}

//��ظ�IP��ַ֡,����ĵ�֡���������buff�У�����item��ֵ����Ϊ1~5����������֡����
static u8 pageNetMakeReplyFrame(u8 item, u8* buff)
{
	u8 i = 0;
	u8 k = 0;
	
	buff[i] = 0x90;   //֡ͷ
	i++;
	buff[i] = 0x0a;   //ҳ��ID
	i++;
	buff[i] = item;   //������
	i++;
	buff[i] = '"';
	i++;
	while(gPagePara.t_string[item][k] != 0)  //�����ַ���
	{
		buff[i] = gPagePara.t_string[item][k];
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

