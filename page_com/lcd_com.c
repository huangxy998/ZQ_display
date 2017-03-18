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
//页面数据包
///////////////////////////////////////////////////////////////////////////////////////////////////

void uart_to_main_cmd_parse(void)
{	
	//校验和检查
	
	
	//类型
	switch( uart_to_main_cmd_parse_buff[4] )
	{
		//页面数据包
		case LC_PACKET_PAGE:
			
			break;
			
		default:break;
		
	}
}
