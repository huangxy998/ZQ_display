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

typedef struct
{
	u8 ip[4];
	u8 mask[4];
	u8 gate[4];
	u8 server[4];
	u16 port;
	u8 mac[5];

}IP_INFO;


#define PAGE_NET_NL1		130
#define PAGE_NET_NL2		190
#define PAGE_NET_NL3		245
#define PAGE_NET_NL4		304

#define PAGE_NET_NH1		26
#define PAGE_NET_NH2		54
#define PAGE_NET_NH3		82
#define PAGE_NET_NW		    47
#define PAGE_NET_NH		    20

#define PAGE_NET_BL1		95
#define PAGE_NET_BL2		143
#define PAGE_NET_BL3		189
#define PAGE_NET_BL4		235
#define PAGE_NET_BL5		280
#define PAGE_NET_BL6		327
#define PAGE_NET_BH1		111
#define PAGE_NET_BH2		151
#define PAGE_NET_BW		    43
#define PAGE_NET_BH		    36

IP_INFO ipInfo;
u8      curDataIdx = 0;
u8      inputDataIdx = 0;
u8      inputDataErr = 0;

static void pageNetConfigInit(void);
static void pageNetConfigUpdate(void);
static void pageNetConfigItemUpdate(void);
static void pageNetTPUpdate(int item);
static u8 pageNetIPStr2Dec(u8 item, char* ipStr);




///////////////////////////////////////////////////////////
//页面子项目结构体
const PAGE_ITEM_T page_NetConfig_item[] =
{     
	             //b0控件
	{
		13,     //id
		1,      //支持触控
		
		320, 20,    //开始坐标
		65, 35 , //宽高
		
		{0x65,0x0a,0x0e,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	            //b1控件
	{
		14,     //id
		1,      //支持触控
		
		320,58,    //开始坐标
		65,35 , //宽高
		
		{0x65,0x0a,0x13,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	           //b2控件
	{
		15,     //id
		1,      //支持触控
		
		320,98,    //开始坐标
		65,35 , //宽高
		
		{0x65,0x0a,0x14,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b3控件
	{
		16,     //id
		1,      //支持触控
		
		22,160,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x15,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b4控件
	{
		17,     //id
		1,      //支持触控
		
		68,160,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x16,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b5控件
	{
		18,     //id
		1,      //支持触控
		
	 	118,160,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x17,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b6控件
	{
		19,     //id
		1,      //支持触控
		
	  	170,160,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x18,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b7控件
	{
		20,     //id
		1,      //支持触控
		
	  	218,160,    //开始坐标
		48,34 , //宽高
		
		{0x65,0x0a,0x19,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //b8控件
	{
	21,     //id
		1,      //支持触控
		
	 	274,160,    //开始坐标
		49,34 , //宽高
		
		{0x65,0x0a,0x1a,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	             //b9控件
	{
	22,     //id
		1,      //支持触控
		
	 	335,160,    //开始坐标
		49,34 , //宽高
		
		{0x65,0x0a,0x1b,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	            //b10控件
	{
		23,     //id
		1,      //支持触控
		
	 	22,200,    //开始坐标
		48,34 , //宽高
		
		{0x65,0x0a,0x1c,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b11控件
	{
		24,     //id
		1,      //支持触控
		
	 	68,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x1d,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b12控件
	{
		25,     //id
		1,      //支持触控
		
	  118,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x0f,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b13控件
	{
		26,     //id
		1,      //支持触控
		
	   170,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x10,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b14控件
	{
		27,     //id
		1,      //支持触控
		
	  218,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b15控件
	{
		28,     //id
		1,      //支持触控
		
	  274,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x12,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	//b16控件
	{
		25,     //id
		1,      //支持触控
		
	  335,200,    //开始坐标
		45,34 , //宽高
		
		{0x65,0x0a,0x0f,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b17控件
	{
		26,     //id
		1,      //支持触控
		
	   2,20,    //开始坐标
		94,20 , //宽高
		
		{0x65,0x0a,0x10,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	             //b18控件
	{
		27,     //id
		1,      //支持触控
		
	  2,43,    //开始坐标
		94,20 , //宽高
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //默认0
	},
	            //b19控件
	{
		28,     //id
		1,      //支持触控
		
	  2,65,    //开始坐标
		94,20 , //宽高
		
		{0x65,0x0a,0x12,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	//b20控件
	{
		27,     //id
		1,      //支持触控
		
	  2,86,    //开始坐标 
		94,20 , //宽高
		
		{0x65,0x0a,0x11,0x00,0xff,0xff,0xff},
		0       //默认0
	},

	//t0控件
	{
		27,     //id
		0,     
		
	  6,135,    //开始坐标
		194,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t1控件
	{
		27,     //id
		0,     
		
	  98,22,    //开始坐标
		206,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t2控件
	{
		27,     //id
		0,     
		
	  98,44,    //开始坐标
		206,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t3控件
	{
		27,     //id
		0,     
		
	  98,66,    //开始坐标
		206,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t4控件
	{
		27,     //id
		0,     
		
	  98,90,    //开始坐标
		206,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t5控件
	{
		27,     //id
		0,     
		
	  98,112,    //开始坐标
		206,20 , //宽高
		
		{0},
		0       //默认0
	},

	//t6控件
	{
		27,     //id
		0,     
		
	  200,134,    //开始坐标
		195,22 , //宽高
		
		{0},
		0       //默认0
	},
};

//页面结构体
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
	sprintf((char*)gPagePara.t_string[1], "%d.%d.%d.%d", ipInfo.ip[0], ipInfo.ip[1], ipInfo.ip[2], ipInfo.ip[3]);
	sprintf((char*)gPagePara.t_string[2], "%d.%d.%d.%d", ipInfo.mask[0], ipInfo.mask[1], ipInfo.mask[2], ipInfo.mask[3]);
	sprintf((char*)gPagePara.t_string[3], "%d.%d.%d.%d", ipInfo.gate[0], ipInfo.gate[1], ipInfo.gate[2], ipInfo.gate[3]);
	sprintf((char*)gPagePara.t_string[4], "%d.%d.%d.%d", ipInfo.server[0], ipInfo.server[1], ipInfo.server[2], ipInfo.server[3]);
	sprintf((char*)gPagePara.t_string[5], "%d:%d:%d:%d:%d", ipInfo.mac[0], ipInfo.mac[1], ipInfo.mac[2], ipInfo.mac[3], ipInfo.mac[4]);
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
			if((page_NetConfig_item[item].touch_en))  //检查触控
			{
			
				if( ( touch_up_pos.x >= page_NetConfig_item[item].start_pos_x ) && ( touch_up_pos.x < page_NetConfig_item[item].start_pos_x + page_NetConfig_item[item].width)  && \
					( touch_up_pos.y >= page_NetConfig_item[item].start_pos_y ) && ( touch_up_pos.y < page_NetConfig_item[item].start_pos_y + page_NetConfig_item[item].height) )
				{
					gPageInfo.need_update = 1;
					if (inputDataErr) //清除错误提示信息
					{
						inputDataErr = 0;
						gPagePara.t_string[6][0] = 0;//清显示字符
						LCD_Fill(page_NetConfig_item[21+6].start_pos_x, page_NetConfig_item[21+6].start_pos_y,
				     		page_NetConfig_item[21+6].start_pos_x+page_NetConfig_item[21+6].width-4,
				     		page_NetConfig_item[21+6].start_pos_y+16, BLACK);
					}
					pageNetTPUpdate(item);
					
//					gIDInfo.cmdUpdate = 1;
//					memcpy(&gIDInfo.cmdPage.start, &page_NetConfig_item[item].com_data[0], TOUCH_CMD_LEN);
					break;
				}
			}	
		}
	}
	if(gPageInfo.need_update == 1)
	{
		gPageInfo.need_update = 0;
		pageNetConfigItemUpdate();   //页面刷新
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
					page_NetConfig_item[item+21].start_pos_y, 100, 16, 16, gPagePara.t_string[item]);
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
		case 15:  //这些项属于字符输入，直接缓存即可
			gPagePara.t_string[0][inputDataIdx] = charbuf[item];
			if (inputDataIdx < 15) //最多输入15个字符，否则ip输入格式不对
			{
				inputDataIdx++;
				gPagePara.t_string[0][inputDataIdx] = 0; //添加字符串结束符
			}
			
			break;
		case 8 : //后退删除键
			if (inputDataIdx > 0)
			{
				inputDataIdx--;
				gPagePara.t_string[0][inputDataIdx] = 0; //清除当前字符
			}
			LCD_Fill(page_NetConfig_item[21].start_pos_x, page_NetConfig_item[21].start_pos_y,
			     page_NetConfig_item[21].start_pos_x+page_NetConfig_item[21].width-4,
			     page_NetConfig_item[21].start_pos_y+16, BLACK);
			break;
		case 16://确认键，将字符进行规则检查，符合要求则拷贝到相应的缓存
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
				memcpy(gPagePara.t_string[6], "输入的数据有误", sizeof("输入的数据有误"));
			}
			break;
		case 17://本地IP
		case 18://掩码
		case 19://网关
		case 20://服务器地址
			curDataIdx = item - 17;
		  	LCD_Fill(page_NetConfig_item[21].start_pos_x, page_NetConfig_item[21].start_pos_y,
			     page_NetConfig_item[21].start_pos_x+page_NetConfig_item[21].width-4,
			     page_NetConfig_item[21].start_pos_y+16, BLACK);
			inputDataIdx = 0;
		  	gPagePara.t_string[0][0] = 0;
			break;
		case 2:
			gPageInfo.cur_page_idx = PAGE_ID_MENU;
			memset(&gPagePara, 0, sizeof(page_para));
			break;
		default: break;	
	}
}

//数据正常返回1，否则返回0
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
			datatmp[dataidx] = curdata;  //取得一个合法数据
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
	datatmp[dataidx] = curdata;  //取得最后一个合法数据
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


