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
#include "lcd_com_prot.h"


#include "page_define.h"
#include "page.h"

//u8 uart_to_main_cmd_parse_buff[UART_TO_MAIN_CMD_RCV_BUFF_LEN];     	//���ջ���,���USART_REC_LEN���ֽ�.



///////////////////////////////////////////////////////////////////////////////////////////////////
//ҳ�����ݰ�
///////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_PAGE_DATA_T basic_page_data;

u8 lmd_grade = 0;
u8 LJ_on_off = 0;

void page_base_parse(void)
{
	memcpy( (void*)&basic_page_data, &uart_to_main_cmd_parse_buff[8], sizeof(BASIC_PAGE_DATA_T) );
	
	
	//λ��ת���ɱ���
	//lmd_grade = basic_page_data.lmd_grade;
	
	//basic_page_data.function = 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//ҳ�����ݰ�END
///////////////////////////////////////////////////////////////////////////////////////////////////



void uart_to_main_cmd_parse(void)
{
	
	
	//1 У��ͼ��
	
	
	//����
	switch( uart_to_main_cmd_parse_buff[4] )
	{
		//ҳ�����ݰ�
		case LC_PACKET_PAGE:
			
			break;
			
		default:break;
		
	}
}
