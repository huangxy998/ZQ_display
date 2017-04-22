#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "flash.h"  


#include "../USER/main.h" 

#include "lcd_com.h"

#include "page_define.h"
#include "page.h"

page_para gPagePara;

const char* page_str[] =
{
	"Star",
	"STANDtime",
	"Version",
	"Main",
	"BLACKlist",
	"BLACKkey",
	"CIScheck",
	"CISset1",
	"SYSupdata",
	"ZBupdata",
	"NETset",
	"GZHMdisp",
	"SYSTEMset",
	"SENSORcheck",
	"GEARset1",
	"GEARset2",
	"DISPlight",
	"CLOCKdisp",
	"CLOCKset",
	"Speak",
	"Input",
	"Output",
	"Confirm",
	"Confirm1",
	"Error"
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//页面数据包
///////////////////////////////////////////////////////////////////////////////////////////////////
//字符串
static void parse_t_buff(u8 *buff)
{
	u8 i = 2, j = 0;
	u8 status = 0;
	u8 idx = 0;
	if((buff[1] >= '0') && ((buff[1] <= '9')))
	{
		while(buff[i] != 0)
		{
			switch(status)
			{
				case 0:
					if(buff[i] == '.')
					{
						switch(i-2)
						{
							case 1:
								idx = buff[i-1];
								status = 1;
								break;
							case 2:
								idx = (buff[i-2]<<8) | buff[i-1];
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if((buff[i] == '=') && (buff[i+1] == '"'))
					{
						i += 1;
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 32) && (j < 9))
					{
						gPagePara.t_string[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
			}
			i++;
		}
		gPagePara.t_string[idx][j] = 0;
	}
}
//数值字符
static void parse_n_buff(u8 *buff)
{
	u8 i = 2, j = 0;
	u8 status = 0;
	u8 idx = 0;
	if((buff[1] >= '0') && ((buff[1] <= '9')))
	{
		while(buff[i] != 0)
		{
			switch(status)
			{
				case 0:
					if(buff[i] == '.')
					{
						switch(i-2)
						{
							case 1:
								idx = buff[i-1];
								status = 1;
								break;
							case 2:
								idx = (buff[i-2]<<8) | buff[i-1];
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if(buff[i] == '=')
					{
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 32) && (j < 9))
					{
						gPagePara.n_val[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
			}
			i++;
		}
		gPagePara.n_val[idx][j] = 0;
	}
}
//进度条
static void parse_j_buff(u8 *buff)
{
	u8 i = 2, j = 0;
	u8 status = 0;
	u8 idx = 0;
	if((buff[1] >= '0') && ((buff[1] <= '9')))
	{
		while(buff[i] != 0)
		{
			switch(status)
			{
				case 0:
					if(buff[i] == '.')
					{
						switch(i-2)
						{
							case 1:
								idx = buff[i-1];
								status = 1;
								break;
							case 2:
								idx = (buff[i-2]<<8) | buff[i-1];
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if(buff[i] == '=')
					{
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 2) && (j < 3))
					{
						gPagePara.j_percent[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
				
			}
			i++;
		}
		gPagePara.j_percent[idx][j] = 0;
	}
}

//警告字符串
static void parse_g_buff(u8 *buff)
{
	u8 i = 2, j = 0;
	u8 status = 0;
	u8 idx = 0;
	if((buff[1] >= '0') && ((buff[1] <= '9')))
	{
		while(buff[i] != 0)
		{
			switch(status)
			{
				case 0:
					if(buff[i] == '.')
					{
						switch(i-2)
						{
							case 1:
								idx = buff[i-1];
								status = 1;
								break;
							case 2:
								idx = (buff[i-2]<<8) | buff[i-1];
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if((buff[i] == '=') && (buff[i+1] == '"'))
					{
						i += 1;
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 2) && (j < 49))
					{
						gPagePara.g_string[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
			}
			i++;
		}
		gPagePara.g_string[idx][j] = 0;
	}
}

//页面更新
static void parse_p_buff(char *buff)
{
	u8 i = 2, j = 0;
	
	while(buff[i] != 0)
	{
		if((buff[i] != ' ') && (buff[i-1] == ' '))
		{
			for(j = 0; j < sizeof(page_str)/sizeof(page_str[0]); j++)
			{
				if(strcmp(&buff[i], page_str[j]) == 0)
				{
					//在此更新页面序号
					gPageInfo.cur_page_idx = j;
					memset(&gPagePara, 0, sizeof(page_para));
					break;
				}
			}
		}
		i++;
	}
}

//带多种信息字符串
static void parse_x_buff(u8 *buff)
{
	u8 i = 1; 
	u8 j = 0;
	
	while(buff[i] != 0)
	{
		if((buff[i] != ' ') && (buff[i-1] == ' '))
		{
			if (j < 49)
			{
				gPagePara.x_str[0][j] = buff[i];
				j++;
			}
		}
		i++;
	}
	gPagePara.x_str[0][j] = 0;
}

//带多种信息填充矩形
static void parse_f_buff(u8 *buff)
{
	u8 i = 1; 
	u8 j = 0;
	
	while(buff[i] != 0)
	{
		if((buff[i] != ' ') && (buff[i-1] == ' '))
		{
			if (j < 29)
			{
				gPagePara.f_str[0][j] = buff[i];
				j++;
			}
		}
		i++;
	}
	gPagePara.f_str[0][j] = 0;
}

void uart_to_main_cmd_parse(void)
{	
	//类型
	switch( uart_to_main_cmd_parse_buff[0] )
	{
		case 'n':parse_n_buff(uart_to_main_cmd_parse_buff);
			break;
		case 't':parse_t_buff(uart_to_main_cmd_parse_buff); 
			break;
		case 'j':parse_j_buff(uart_to_main_cmd_parse_buff);
			break;
		case 'g':parse_g_buff(uart_to_main_cmd_parse_buff);
			break;
		case 'p':parse_p_buff((char*)uart_to_main_cmd_parse_buff);
			break;	
		case 'f':parse_f_buff(uart_to_main_cmd_parse_buff);
			break;
		case 'b':
			break;
		case 'x':parse_x_buff(uart_to_main_cmd_parse_buff);
			break;
		default:break;
		
	}
}
