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

///////////////////////////////////////////////////////////////////////////////////////////////////
//ҳ�����ݰ�
///////////////////////////////////////////////////////////////////////////////////////////////////

void uart_to_main_cmd_parse(void)
{	
	//У��ͼ��
	
	
	//����
	switch( uart_to_main_cmd_parse_buff[4] )
	{
		//ҳ�����ݰ�
		case LC_PACKET_PAGE:
			
			break;
			
		default:break;
		
	}
}
