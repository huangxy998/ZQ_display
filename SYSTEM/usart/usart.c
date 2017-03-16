#include <string.h>
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

#include "../USER/main.h"


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ�����ʺ�STM32F10xϵ�У�		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/1/1
//�汾��V1.7
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
//V1.6�޸�˵�� 20150109
//uart_init����ȥ���˿���PE�ж�
//V1.7�޸�˵�� 20150322
//�޸�OS_CRITICAL_METHOD���ж�Ϊ��SYSTEM_SUPPORT_OS
////////////////////////////////////////////////////////////////////////////////// 	  
 
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART1->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////

#if EN_USART1_RX   //���ʹ���˽���

u8 uart_to_main_com_sm;
#define DC_SYNC_BYTE					0xAABBCCDD
#define DC_SYNC_BYTE1					0xAA
#define DC_SYNC_BYTE2					0xBB
#define DC_SYNC_BYTE3					0xCC
#define DC_SYNC_BYTE4					0xDD

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 uart_to_main_cmd_rcv_buff[UART_TO_MAIN_CMD_RCV_BUFF_LEN];     		//���ջ���,���USART_REC_LEN���ֽ�.
u8 uart_to_main_cmd_parse_buff[UART_TO_MAIN_CMD_RCV_BUFF_LEN];     	//���ջ���,���USART_REC_LEN���ֽ�.

u16 uart1_rcv_cnt = 0;       //����״̬���	 
u16 total_len = 0;

void USART1_IRQHandler(void)
{
	u8 rcv_byte;	
	static u32 sync_byte = 0x00;
	
	
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	
if(USART1->SR&(1<<5))	//���յ�����
	{	 
		rcv_byte=USART1->DR; 
			
		//��ͬ��
		if( uart1_rcv_cnt >= 4 )
		{
			//���뻺����
			uart_to_main_cmd_rcv_buff[uart1_rcv_cnt] = rcv_byte;
			uart1_rcv_cnt++;
			
			//��ǰ���ܳ���
			if( uart1_rcv_cnt == 7 )
			{
				total_len = (uart_to_main_cmd_rcv_buff[7]<<8) + uart_to_main_cmd_rcv_buff[6] + 10;
			}
			
			//�������	
			if( uart1_rcv_cnt >= total_len )
			{
				memcpy ( uart_to_main_cmd_parse_buff, uart_to_main_cmd_rcv_buff, total_len );
					
				uart1_rcv_cnt = 0;
				total_len = 0;
				sync_byte = 0x00;
				
				
				main_task_mask |= MAIN_TASK_MASK_UART_TO_MAIN_CMD_PARSE;
					
			}
		}
		//δͬ��
		else
		{
			sync_byte = (sync_byte<<8) + rcv_byte;
			if( sync_byte == DC_SYNC_BYTE )
			{
				uart_to_main_cmd_rcv_buff[0] = DC_SYNC_BYTE1;
				uart_to_main_cmd_rcv_buff[1] = DC_SYNC_BYTE2;	
				uart_to_main_cmd_rcv_buff[2] = DC_SYNC_BYTE3;
				uart_to_main_cmd_rcv_buff[3] = DC_SYNC_BYTE4;	
				
				uart1_rcv_cnt = 4;
				total_len = UART_TO_MAIN_CMD_RCV_BUFF_LEN;
			}
		}
	}
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
	
} 
#endif										 
//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������ 
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬���� 
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART1_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
#endif
}
