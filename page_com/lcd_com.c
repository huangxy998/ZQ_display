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
	u8 bc = 0;
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
							case 0:
								idx = buff[i-1]-0x30;
								status = 1;
								break;
							case 1:
								idx = ((buff[i-2])-0x30)*10 + buff[i-1]-0x30;
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if( buff[i] == '=' )
					{
						if (buff[i+1] != '"')
						{
							bc = 1;
							memset((char*)&gPagePara.t_bco[0][0], 0, 352);
						}
						i += 1;
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 44) && (j < 49))
					{
						if (bc && (j < 7))
							gPagePara.t_bco[idx][j] = buff[i];
						else
							gPagePara.t_string[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
			}
			i++;
			if(buff[i] == '"')
				break;
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
							case 0:
								idx = buff[i-1]-0x30;
								status = 1;
								break;
							case 1:
								idx = ((buff[i-2])-0x30)*10 + buff[i-1]-0x30;
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
							case 0:
								idx = buff[i-1]-0x30;
								status = 1;
								break;
							case 1:
								idx = ((buff[i-2])-0x30)*10 + buff[i-1]-0x30;
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
							case 0:
								idx = buff[i-1]-0x30;
								status = 1;
								break;
							case 1:
								idx = ((buff[i-2])-0x30)*10 + buff[i-1]-0x30;
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
			if(buff[i] == '"')
				break;
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
			break;
		}
		i++;
	}
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

//带多种信息字符串
static void parse_x_buff(u8 *buff)
{
	u8 i = 1; 
	u8 j = 0;
	
	while(buff[i] != 0)
	{
		if((buff[i] != ' ') && (buff[i-1] == ' '))
		{
			break;
		}
		i++;
	}
	while(buff[i] != 0)
	{
		if(buff[i] == '"')
		{
			i++;
			break;
		}
		i++;
	}
	while(buff[i] != 0)
	{
		if (j < 29)
		{
			gPagePara.x_str[0][j] = buff[i];
			j++;
		}
		else
			break;
		i++;
		if(buff[i] == '"')
		{
			break;
		}
		
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
			break;
		}
		i++;
	}

	while(buff[i] != 0)
	{
		if(buff[i] >= 'A')
		{
			break;
		}
		i++;
	}

	while(buff[i] != 0)
	{
		if (j < 29)
		{
			gPagePara.f_str[0][j] = buff[i];
			j++;
		}
		else
			break;
		i++;
	}
	gPagePara.f_str[0][j] = 0;
}

//按钮信息
static void parse_b_buff(u8 *buff)
{
	u8 i = 2, j = 0;
	u8 status = 0;
	u8 idx = 0;
	u8 bc = 0; //背景色标志
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
							case 0:
								idx = buff[i-1]-0x30;
								status = 1;
								break;
							case 1:
								idx = ((buff[i-2])-0x30)*10 + buff[i-1]-0x30;
								status = 1;
								break;
							default: break;
						}
					}
					break;
				case 1:
					if(buff[i] == '=')
					{
						if(buff[i+1] == '"')
							i += 1;
						else
							bc = 1;
						status = 2;
						j = 0;
					}
					break;
				case 2:
					if ((idx < 28) && (j < 9))
					{	
						if(bc == 1)
							gPagePara.b_bc[idx][j] = buff[i];
						else
							gPagePara.b_str[idx][j] = buff[i];
						j++;
					}
					break;
				default:
					break;
			}
			i++;
			if(buff[i] == '"')
			{
				break;
			}
		}
		if(bc == 1)
			gPagePara.b_bc[idx][j] = 0;
		else
			gPagePara.b_str[idx][j] = 0;
	}
	else if(buff[1] == 't')
	{
		while(buff[i] != 0)
		{
			if(buff[i] != '=')
			{
				i++;
				continue;
			}
			if(buff[i-1] == 'l')
			{
				gPagePara.x_str[3][0] = buff[i+1];  //保存累加标志
			}
			break;
		}
	}
}

void uart_to_main_cmd_parse(u8 *uart_to_main_cmd_parse_buff)
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
		case 'b':parse_b_buff(uart_to_main_cmd_parse_buff);
			break;
		case 'x':parse_x_buff(uart_to_main_cmd_parse_buff);
			break;
		default:break;
		
	}
}

void uart_buff_cmd_parse(void)
{
	static u16 uart1_parse_cnt = 0;
	u16 idx = 0;
	u16 parselen = 0;
	u16 rcv_cnt_tmp = 0;

	rcv_cnt_tmp = uart1_rcv_cnt;

	if(rcv_cnt_tmp == uart1_parse_cnt)
	{
		return;
	}
	if(rcv_cnt_tmp > uart1_parse_cnt)
	{
		parselen = rcv_cnt_tmp - uart1_parse_cnt;
	}
	else
	{
		parselen = UART_TO_MAIN_CMD_RCV_BUFF_LEN - uart1_parse_cnt + rcv_cnt_tmp;
	}
	if(parselen > 8)
	{
		while(idx < parselen)
		{
			if(uart1_parse_cnt + idx < UART_TO_MAIN_CMD_RCV_BUFF_LEN)
			{
				uart_to_main_cmd_parse_buff[idx] = uart_to_main_cmd_rcv_buff[uart1_parse_cnt + idx];
			}
			else
			{
				uart_to_main_cmd_parse_buff[idx] = uart_to_main_cmd_rcv_buff[uart1_parse_cnt + idx - UART_TO_MAIN_CMD_RCV_BUFF_LEN];	
			}
			if(uart_to_main_cmd_parse_buff[0] == 0xff)
			{
				parselen--;
				uart1_parse_cnt++;
				uart1_parse_cnt %= UART_TO_MAIN_CMD_RCV_BUFF_LEN;
				continue;
			}
			if(uart_to_main_cmd_parse_buff[idx] == 0xff)
			{
				uart1_parse_cnt += idx;
				uart1_parse_cnt %= UART_TO_MAIN_CMD_RCV_BUFF_LEN;
				if(idx > 3)
				{
					uart_to_main_cmd_parse_buff[idx] = 0;
					uart_to_main_cmd_parse(uart_to_main_cmd_parse_buff);
					gPageInfo.need_update = 1;
				}
				parselen -=  idx + 1;
				idx = 0;	
			}
			else
			{
				idx++;
			}
		}
	}
}

