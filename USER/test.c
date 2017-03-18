#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "flash.h"  

#include "page_define.h" 
#include "page.h" 
#include "page_menu.h"
#include "page_version.h"

#include "lcd_com.h" 
#include "main.h"  


//ȫ�ֱ���
PAGE_INFO_T  gPageInfo;
u32 main_task_mask = 0;


int main(void)
{	
		//u32 FLASH_SIZE;
	
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,115200);	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��	
	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 	
	

	LCD_Clear(BLACK);
	LCD_SetFrontColor(RED);//��������Ϊ��ɫ 
	
	while(SPI_Flash_ReadID()!=W25Q32)							//��ⲻ��W25Q32
	{
		LCD_ShowString(10,150,200,16,16,"25Q64 Check Failed!");
		LCD_ShowString(10,150,200,16,16,"Please Check!      ");
		delay_ms(500);
	}	
	LCD_ShowString(10,150,200,16,16,"25Q32 Check OK!");
	delay_ms(500);
	
	LCD_Clear(WHITE);		
	tp_dev.init();			//��������ʼ��
 	LCD_SetFrontColor(RED);//��������Ϊ��ɫ 
	
	LCD_ShowString_hz16x16(10,70,200,16,16,"��ǿ����");	
	delay_ms(3000);	
	
	LCD_ShowString(10,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(10,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(10,110,200,16,16,"2014/3/11");
	delay_ms(3000);	
	
	LCD_Clear(WHITE);	
	//��ʼ����ʾҳ�����
	gPageInfo.cur_page_idx = PAGE_ID_BASIC;//�㳮����ʼ��ҳ��
	gPageInfo.page_init_finished = 0;     //ҳ��δ��ʼ��
	gPageInfo.pre_page_idx = PAGE_ID_MAX;//������һ��ҳ��ID
	gPageInfo.total_pages  = PAGE_ID_MAX;
	
	gPageInfo.p_page[PAGE_ID_BASIC] = &page_basic;
	gPageInfo.p_page[PAGE_ID_MENU] = &page_menu;
	gPageInfo.p_page[PAGE_ID_VERSION] = &page_version;
		
	//����ҳ�棬��ҳ��ṹ��ָ��ָ��ʵ�ʵ�ҳ�����ݽṹ
	
	while(1)
	{		
		//��ʾģ��������ͨѶ�������
		if( main_task_mask & MAIN_TASK_MASK_UART_TO_MAIN_CMD_PARSE )
		{
			uart_to_main_cmd_parse();
		}
		
		//��ȡ����״̬
		gPageInfo.toucged_up = touch_up_check();
		gPageInfo.toucged_down = touch_pressed_down();
		
		//ҳ����ʾ
		if(gPageInfo.cur_page_idx != gPageInfo.pre_page_idx)
		{
			gPageInfo.pre_page_idx = gPageInfo.cur_page_idx;
			gPageInfo.p_page[gPageInfo.cur_page_idx]->page_init(); //ҳ���ʼ��
		}
		gPageInfo.p_page[gPageInfo.cur_page_idx]->page_update(); //ҳ�����		
	}	
}

/*
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



����SPI FLASH �ռ����
    �ͺţ�			W25Q32
		��������		4Mbytes(0x400000)
		
		1, 0x00000000: Gb2312_16X16_hz.FON	(261'698)
		2, 0x0003FE42: basic_page						(192'008)	
		3, 0x0006EC4A: 
		
		
		0x003f0000: ������У׼����

#define GB2312_16X16_HZ_OFFSET					0x00000000
#define BASIC_PAGE_OFFSET								0x0003FE42

#define TOUCH_ADJUST_PARAM_OFFSET				0x003f0000

һ���汾����

V0
	23, �������
	22, ��ɴ�SPI FLASH���������ֿⲢ��ʾ��
			��ɴ�SPI FLASH���ٶ���BMPͼƬ����ʾ
	21, ��Gb2312_16X16_hz.FON����SPI FLASH
	20��//E:\hqdcj_display\display_pro\pic_font\Gb2312_16X16_hz.FON
			//PC2LCD2002ȡģ��ʽ���ã�����+����ʽ+˳��+C51��ʽ
			//����֤�������֣��ֶ������ĵ���ģ �� ���ֿ�Gb2312_16X16_hz.FON�ҵ�����ģ ��ȫһ��
			//��(ƫ�ƣ�0x00E020) ��(ƫ�ƣ�0x26780)
			
	19, //������У׼���ݴ����SPI FLASH���64K��ַ
			#define SAVE_ADDR_BASE (SPI_FLASH_SIZE-0x10000)
	18, ��SPI FLASH���ٶ���BMPͼƬ��ʾ
	17

	01��LCD����
	02, ��ʾ�ֽ�
	3, 	�Ż�ע��//LCD_ShowChar();
	4,  128*64������ʾ�ɹ�
	5,  ��ʾ��ȷ
	
	7,  ���봥������ش���
	8,  ��������������OK
	
	9, ʹ�ô���1������ͨѶ
	10, ����ʵ��ҳ��,ҳ���
	11
	12,��ʾ��������
	13,����Ӧ�ò��ȡ��������λ��
	14,���������¼���������OK
	15,
	16,����Gb2312_16X16�����ֿ�Ѱַ��������
	
*/



