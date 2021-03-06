#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"  
#include "rtc.h"
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "flash.h"  

#include "page_define.h" 
#include "page.h" 
#include "page_menu.h"
#include "page_version.h"
#include "page_blacklist.h"
#include "page_cisconfig.h"
#include "page_cistest.h"
#include "page_dialog.h"
#include "page_keyboard.h"
#include "page_netconfig.h"
#include "page_paraset.h"
#include "page_serial.h"
#include "page_systemset.h"
#include "page_timeset.h"
#include "page_start.h"
#include "page_mainpara.h"
#include "page_confirm.h"
#include "page_error.h"
#include "page_systemupdate.h"
#include "page_lcdlight.h"
#include "page_sound.h"


#include "lcd_com.h" 
#include "main.h"  
#include "timer.h"


//全局变量
volatile PAGE_INFO_T  gPageInfo;
CMD_PAGE_ID_INFO  gIDInfo;

u32 main_task_mask = 0;


int main(void)
{	
	u8 light = 0;
 	Stm32_Clock_Init(9);	//系统时钟设置 	
 	JTAG_Set(SWD_ENABLE);
	uart_init(72,115200);	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 
	KEY_Init();				//按键初始化	
	
	SPI_Flash_Init();  		//SPI FLASH 初始化 	
	RTC_Init();
	
	gIDInfo.cmdUpdate = 0;
	gIDInfo.cmdPage.start = 0x65;
	gIDInfo.cmdPage.pageID = PAGE_ID_STANDTIME;
	gIDInfo.cmdPage.touchStatus = 0x00;
	gIDInfo.cmdPage.cmdEnd[0] = 0xff;
	gIDInfo.cmdPage.cmdEnd[1] = 0xff;
	gIDInfo.cmdPage.cmdEnd[2] = 0xff;

	LCD_SetFrontColor(RED);//设置字体为红色 
	
	while(SPI_Flash_ReadID()!=W25Q32)							//检测不到W25Q32
	{
		LCD_ShowString(10,150,200,16,16,"25Q64 Check Failed!");
		LCD_ShowString(10,150,220,16,16,"Please Check!      ");
		delay_ms(500);
	}	

	TIM2_PWM_Init(100,7200);
	light = getLcdLightParam();
	if ((light < 1) || (light > 10))
		light = 8;
	TIM2_PWM_duty(10*light);
	
	LCD_Clear(WHITE);		
	tp_dev.init();			//触摸屏初始化

	//初始化显示页面参数
	gPageInfo.cur_page_idx = PAGE_ID_START;//点钞机初始化页面
	gPageInfo.page_init_finished = 0;     //页面未初始化
	gPageInfo.pre_page_idx = PAGE_ID_NUM;//保留上一次页面ID
	gPageInfo.total_pages  = PAGE_ID_NUM;

	gPageInfo.p_page[PAGE_ID_START] = &page_start;
	gPageInfo.p_page[PAGE_ID_STANDTIME] = &page_basic;
	gPageInfo.p_page[PAGE_ID_MAIN] = &page_menu;
	gPageInfo.p_page[PAGE_ID_SYSVERSION] = &page_version;
	gPageInfo.p_page[PAGE_ID_BLACKLIST] = &page_Blacklist;
	gPageInfo.p_page[PAGE_ID_BLACKKEY] = &page_KeyBoard;
	gPageInfo.p_page[PAGE_ID_CISCHEK] = &page_CISTest;
	gPageInfo.p_page[PAGE_ID_CISSET1] = &page_CISConfig;
	gPageInfo.p_page[PAGE_ID_SYSUPDATA] = &page_SystemUpdate;
	gPageInfo.p_page[PAGE_ID_ZBUPDATA] = &page_version;
	gPageInfo.p_page[PAGE_ID_NETSET] = &page_NetConfig;
	gPageInfo.p_page[PAGE_ID_GZHMDIS] = &page_Serial;
	gPageInfo.p_page[PAGE_ID_SYSEMSET] = &page_SystemSet;
	gPageInfo.p_page[PAGE_ID_SENSORCHECK] = &page_ParaSet;
	gPageInfo.p_page[PAGE_ID_GEARSET1] = &page_mainpara;
	gPageInfo.p_page[PAGE_ID_GEARSET2] = &page_dialog;
	gPageInfo.p_page[PAGE_ID_DISPLIGHT] = &page_SystemSet;
	gPageInfo.p_page[PAGE_ID_CLOCKDISP] = &page_TimeSet;
	gPageInfo.p_page[PAGE_ID_CLOCKSET] = &page_TimeSet;
	gPageInfo.p_page[PAGE_ID_SPEAK] = &page_Sound;
	gPageInfo.p_page[PAGE_ID_INPUT] = &page_TimeSet;
	gPageInfo.p_page[PAGE_ID_OUTPUT] = &page_dialog;
	gPageInfo.p_page[PAGE_ID_CONFIRM] = &page_confirm;
	gPageInfo.p_page[PAGE_ID_CONFIRM1] = &page_confirm;
	gPageInfo.p_page[PAGE_ID_ERRER] = &page_error;
	gPageInfo.p_page[PAGE_ID_LIGHT_PARA] = &page_Lcd;
	
		
	//加载页面，将页面结构体指针指向实际的页面数据结构
	LCD_SetBackColor(BLACK);
	while(1)
	{		
		//显示模块与主控通讯命令解析
		//if( main_task_mask & MAIN_TASK_MASK_UART_TO_MAIN_CMD_PARSE )
		//{
		//	main_task_mask = 0;
			uart_buff_cmd_parse();
		//}
		
		//获取触控状态
		gPageInfo.toucged_up = touch_up_check();
		gPageInfo.toucged_down = touch_pressed_down();
		
		//页面显示
		if(gPageInfo.cur_page_idx != gPageInfo.pre_page_idx)
		{
			gPageInfo.p_page[gPageInfo.cur_page_idx]->page_init(); //页面初始化
			gPageInfo.pre_page_idx = gPageInfo.cur_page_idx;
			delay_ms(2);
		}
		gPageInfo.p_page[gPageInfo.cur_page_idx]->page_update(); //页面更新		
		if(gIDInfo.cmdUpdate != 0)
		{
			gIDInfo.cmdUpdate = 0;
			uartSendbuffer((u8*)&gIDInfo.cmdPage, sizeof(CMD_PAGE_ID));
		}
	}	
}

/*
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



二，SPI FLASH 空间分配
    型号：			W25Q32
		总容量：		4Mbytes(0x400000)
		
		1, 0x00000000: Gb2312_16X16_hz.FON	(261'698)
		2, 0x0003FE42: basic_page						(192'008)	
		3, 0x0006EC4A: 
		
		
		0x003f0000: 触摸屏校准参数

#define GB2312_16X16_HZ_OFFSET					0x00000000
#define BASIC_PAGE_OFFSET								0x0003FE42

#define TOUCH_ADJUST_PARAM_OFFSET				0x003f0000

一，版本控制

V0
	23, 整理代码
	22, 完成从SPI FLASH读出中文字库并显示，
			完成从SPI FLASH快速读出BMP图片并显示
	21, 将Gb2312_16X16_hz.FON存入SPI FLASH
	20，//E:\hqdcj_display\display_pro\pic_font\Gb2312_16X16_hz.FON
			//PC2LCD2002取模方式设置：阴码+逐列式+顺向+C51格式
			//经验证以下两字：手动产生的的字模 与 从字库Gb2312_16X16_hz.FON找到的字模 完全一致
			//川(偏移：0x00E020) 张(偏移：0x26780)
			
	19, //触摸屏校准数据存放在SPI FLASH最高64K地址
			#define SAVE_ADDR_BASE (SPI_FLASH_SIZE-0x10000)
	18, 从SPI FLASH快速读出BMP图片显示
	17

	01，LCD点亮
	02, 显示字节
	3, 	优化注释//LCD_ShowChar();
	4,  128*64字体显示成功
	5,  显示正确
	
	7,  加入触摸屏相关代码
	8,  触摸屏初步工作OK
	
	9, 使用串口1与主控通讯
	10, 初步实现页面,页项方案
	11
	12,显示曲线正常
	13,触摸应用层获取触摸弹起位置
	14,触摸弹起事件初步测试OK
	15,
	16,测试Gb2312_16X16汉字字库寻址方法测试
	
*/



