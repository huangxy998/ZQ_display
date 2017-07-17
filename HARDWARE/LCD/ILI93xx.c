#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"
#include "delay.h"	 
#include "fonts.h"	


#include "flash.h"	

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32F103������
//2.4��/2.8��/3.5��/4.3��/7�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963��		    
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/7/4
//�汾��V3.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2�޸�˵��
//֧����SPFD5408������,�����Һ��IDֱ�Ӵ�ӡ��HEX��ʽ.����鿴LCD����IC.
//V1.3
//�����˿���IO��֧��
//�޸��˱�����Ƶļ��ԣ�������V1.8���Ժ�Ŀ�����汾��
//����1.8�汾֮ǰ(������1.8)��Һ��ģ��,���޸�LCD_Init������LCD_LED=1;ΪLCD_LED=1;
//V1.4
//�޸���LCD_ShowChar������ʹ�û��㹦�ܻ��ַ���
//�����˺�������ʾ��֧��
//V1.5 20110730
//1,�޸���B505Һ������ɫ�����bug.
//2,�޸��˿���IO�������������÷�ʽ.
//V1.6 20111116
//1,�����LGDP4535Һ��������֧��
//V1.7 20120713
//1,����LCD_RD_DATA����
//2,���Ӷ�ILI9341��֧��
//3,����ILI9325�Ķ�����������
//4,����LCD_Scan_Dir����(����ʹ��)	  
//6,�����޸��˲���ԭ���ĺ���,����Ӧ9341�Ĳ���
//V1.8 20120905
//1,����LCD��Ҫ�������ýṹ��lcddev
//2,����LCD_Display_Dir����,֧�����ߺ������л�
//V1.9 20120911
//1,����RM68042������ID:6804��������6804��֧�ֺ�����ʾ����ԭ�򣺸ı�ɨ�跽ʽ��
//����6804��������ʧЧ���Թ��ܶ෽�������У���ʱ�޽⡣
//V2.0 20120924
//�ڲ�Ӳ����λ�������,ILI9341��ID��ȡ�ᱻ�����9300,�޸�LCD_Init,���޷�ʶ��
//�����������IDΪ9300/�Ƿ�ID��,ǿ��ָ������ICΪILI9341��ִ��9341�ĳ�ʼ����
//V2.1 20120930
//����ILI9325����ɫ��bug��
//V2.2 20121007
//����LCD_Scan_Dir��bug��
//V2.3 20130120
//����6804֧�ֺ�����ʾ
//V2.4 20131120
//1,����NT35310��ID:5310����������֧��
//2,����LCD_Set_Window����,�������ô���,�Կ������,�Ƚ�����,���Ǹú����ں���ʱ,��֧��6804.
//V2.5 20140211
//1,����NT35510��ID:5510����������֧��
//V2.6 20140504
//1,����ASCII 24*24�����֧��(���������û������������)  
//2,�޸Ĳ��ֺ�������,��֧��MDK -O2�Ż�
//3,���9341/35310/35510,дʱ������Ϊ���,�����ܵ�����ٶ�
//4,ȥ����SSD1289��֧��,��Ϊ1289ʵ����̫����,������Ҫ1us...��ֱ����.���ʺ�F4ʹ��
//5,����68042��C505��IC�Ķ���ɫ������bug.
//V2.7 20140710
//1,����LCD_Color_Fill������һ��bug. 
//2,����LCD_Scan_Dir������һ��bug.
//V2.8 20140721
//1,���MDKʹ��-O2�Ż�ʱLCD_ReadPoint��������ʧЧ������.
//2,����LCD_Scan_Dir����ʱ���õ�ɨ�跽ʽ��ʾ��ȫ��bug.
//V2.9 20141130
//1,������SSD1963 LCD��֧��.
//2,����LCD_SSD_BackLightSet����
//3,ȡ��ILI93XX��Rxx�Ĵ�������
//V3.0 20150423
//�޸�SSD1963 LCD������������.
//////////////////////////////////////////////////////////////////////////////////	 

static sFONT *LCD_Currentfonts;

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR=0x0000;	//������ɫ
u16 BACK_COLOR=0xFFFF;  //����ɫ 

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;


//////////////////////////////////////////////////////////////////////////////////
//1���Ĵ�����д��оƬ��ʼ��
//////////////////////////////////////////////////////////////////////////////////
	 					    
//д�Ĵ�������
//data:�Ĵ���ֵ
void LCD_WR_REG(u16 data)
{ 
	LCD_RD_SET;
	LCD_RS_CLR;//д��ַ  
 	LCD_CS_CLR; 
	DATAOUT(data); 
	LCD_WR_CLR; 
	LCD_WR_SET; 
	LCD_RS_SET;
//	if (data != 0x22)
//		LCD_CS_SET;   
}
//д���ݺ���
//�������LCD_WR_DATAX��,��ʱ�任�ռ�.
//data:�Ĵ���ֵ
void LCD_WR_DATAX(u16 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}
/*д8λ������*/
void LCD_WR_DATA8(u8 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}

//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{										   
	u16 t;
 	GPIOB->CRL=0X88888888; //PB0-7  ��������
	GPIOB->CRH=0X88888888; //PB8-15 ��������
	GPIOB->ODR=0X0000;     //ȫ�����0

	LCD_RS_SET;
	LCD_CS_CLR;
	//��ȡ����(���Ĵ���ʱ,������Ҫ��2��)
	LCD_RD_CLR;
	if(lcddev.id==0X8989)delay_us(2);//FOR 8989,��ʱ2us					   
	t=DATAIN;  
	LCD_RD_SET;
	LCD_CS_SET; 

	GPIOB->CRL=0X33333333; //PB0-7  �������
	GPIOB->CRH=0X33333333; //PB8-15 �������
	GPIOB->ODR=0XFFFF;    //ȫ�������
	return t;  
}

u16 LCD_RD_DATA16(void)
{										   
	u16 t;
 	GPIOB->CRL=0X88888888; //PB0-7  ��������
	GPIOB->CRH=0X88888888; //PB8-15 ��������
	GPIOB->ODR=0X0000;     //ȫ�����0

//	LCD_RS_SET;
//	LCD_CS_CLR;
	//��ȡ����(���Ĵ���ʱ,������Ҫ��2��)
	LCD_RD_CLR;	
  LCD_RD_CLR;	
	t=DATAIN;  
	LCD_RD_SET;
	LCD_RD_SET;
	LCD_RD_CLR;
  LCD_RD_CLR;	
	t=DATAIN;  
	LCD_RD_SET;
	LCD_CS_SET; 

	GPIOB->CRL=0X33333333; //PB0-7  �������
	GPIOB->CRH=0X33333333; //PB8-15 �������
	GPIOB->ODR=0XFFFF;    //ȫ�������
	return t;  
}


//д�Ĵ���
//LCD_Reg:�Ĵ������
//LCD_RegValue:Ҫд���ֵ
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}   
//���Ĵ���
//LCD_Reg:�Ĵ������
//����ֵ:������ֵ
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
 	LCD_WR_REG(LCD_Reg);  //д��Ҫ���ļĴ�����  
	return LCD_RD_DATA(); 
} 
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
} 
//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_WR_DATA(RGB_Code);//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}	


//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ALIENTEK��Ʒ��LCDҺ����
//������ռ�ýϴ�flash,�û����Ը����Լ���ʵ�����,ɾ��δ�õ���LCD��ʼ������.�Խ�ʡ�ռ�.
void LCD_Init(void)
{ 
	u16 tmp16;
	
 	RCC->APB2ENR|=1<<3;//��ʹ������PORTBʱ��
 	RCC->APB2ENR|=1<<4;//��ʹ������PORTCʱ��

	RCC->APB2ENR|=1<<0;    //��������ʱ��
	JTAG_Set(SWD_ENABLE);  //����SWD
											 
	//PORTC6~10����������� 	
	GPIOC->CRH&=0XFFFFF000;
	GPIOC->CRH|=0X00000333; 
	GPIOC->CRL&=0X00FFFFFF;
	GPIOC->CRL|=0X33000000;  
	GPIOC->ODR|=0X07C0; 	 
	//PORTB ������� 	
	GPIOB->CRH=0X33333333;
	GPIOB->CRL=0X33333333; 	 
	GPIOB->ODR=0XFFFF;

	delay_ms(50); // delay 50 ms 
	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
	lcddev.id = LCD_ReadReg(0x0000); 
	
	delay_ms(50); // delay 50 ms 
    LCD_WR_REG(0x001A); LCD_WR_DATA(0x0002); //BT	//0x001A��Դ���ƼĴ���	������λ��Ч
	tmp16 = LCD_ReadReg(0x001A); 
		
	delay_ms(50); // delay 50 ms 
    LCD_WR_REG(0x001B); LCD_WR_DATA(0x0088); //VRH	//0x001b��Դ���ƼĴ���	 ������λ��Ч
	tmp16 = LCD_ReadReg(0x001B);			

	lcddev.dir=1;	//����
 	printf(" LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID  

	if( lcddev.id == 0x72 )
	{
		lcddev.width = LCD_HOR_SIZE;
		lcddev.height = LCD_VER_SIZE;
		lcddev.wramcmd = 0x22;
	
    	LCD_WR_REG(0x001A); LCD_WR_DATA(0x0002); //BT	//0x001A��Դ���ƼĴ���	������λ��Ч
		tmp16 = LCD_ReadReg(0x001A); 
	
		LCD_WR_REG(0x001B); LCD_WR_DATA(0x0088); //VRH	//0x001b��Դ���ƼĴ���	 ������λ��Ч
		
		//****VCOM offset**///
		LCD_WR_REG(0x0023); LCD_WR_DATA(0x0000); //SEL_VCM		 //��Դ
		LCD_WR_REG(0x0024); LCD_WR_DATA(0x005F); //VCM			 //��Դ
		LCD_WR_REG(0x0025); LCD_WR_DATA(0x0015); //VDV			 //��Դ
		LCD_WR_REG(0x002D); LCD_WR_DATA(0x0003); //NOW[2:0]=011
		
		/*****************��Դ����*/
		LCD_WR_REG(0x0018); LCD_WR_DATA(0x0004); //Frame rate 72Hz
		LCD_WR_REG(0x0019); LCD_WR_DATA(0x0001); //OSC_EN='1', start Osc
		LCD_WR_REG(0x0001); LCD_WR_DATA(0x0002); //INVON = 1
		
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0088); //STB=0
		delay_ms(5);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0080); //DK=0
		delay_ms(5);
		delay_ms(0x001F); LCD_WR_DATA(0x0090); //PON=1
		delay_ms(5);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x00D0); //VCOMG=1
		delay_ms(5);
		
		/*********18λ��ɫ��16λ��ɫѡ��*/
		LCD_WR_REG(0x0017); LCD_WR_DATA(0x0005); //default 0x06 262k color // 0x05 65k color
			
		//SET PANEL
		LCD_WR_REG(0x0036); LCD_WR_DATA(0x0017); //REV_P, SM_P, GS_P, BGR_P, SS_P
		/*LCD_WR_REG(0x0029); LCD_WR_DATA(0x0031); //400 lines
		LCD_WR_REG(0x0071); LCD_WR_DATA(0x001A); //RTN*/
		
		//Gamma 2.2 Setting
		LCD_WR_REG(0x0040); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0041); LCD_WR_DATA(0x0045);
		LCD_WR_REG(0x0042); LCD_WR_DATA(0x0045);
		LCD_WR_REG(0x0043); LCD_WR_DATA(0x0004);
		LCD_WR_REG(0x0044); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0045); LCD_WR_DATA(0x0008);
		LCD_WR_REG(0x0046); LCD_WR_DATA(0x0023);
		LCD_WR_REG(0x0047); LCD_WR_DATA(0x0023);
		LCD_WR_REG(0x0048); LCD_WR_DATA(0x0077);
		LCD_WR_REG(0x0049); LCD_WR_DATA(0x0040);

		LCD_WR_REG(0x004A); LCD_WR_DATA(0x0004);
		LCD_WR_REG(0x004B); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x004C); LCD_WR_DATA(0x0088);
		LCD_WR_REG(0x004D); LCD_WR_DATA(0x0088);
		LCD_WR_REG(0x004E); LCD_WR_DATA(0x0088);
		
		/************����GRAM��ʾ������Ļ��ʾ��С*/
		LCD_WR_REG(0x0002); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0003); LCD_WR_DATA(0x0000); //Column Start
		LCD_WR_REG(0x0004); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0005); LCD_WR_DATA(0x00EF); //Column End
		LCD_WR_REG(0x0006); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0007); LCD_WR_DATA(0x0000); //Row Start
		LCD_WR_REG(0x0008); LCD_WR_DATA(0x0001);//0001
		LCD_WR_REG(0x0009); LCD_WR_DATA(0x008F); //Row End00AF
		
		/************��ʾ����*/
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x0038); //GON=1, DTE=1, D=10
		delay_ms(40);
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x003F); //GON=1, DTE=1, D=11
		LCD_WR_REG(0x0022); //Start GRAM write

		/***************˯��ģʽ����*/ 
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x0038); //GON=??DTE=??D[1:0]=?0?
		delay_ms(40);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0089); // GAS=1, VOMG=0, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=1
		delay_ms(40);
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x0020); //GON=??DTE=??D[1:0]=?0?
		delay_ms(40);
		LCD_WR_REG(0x0019); LCD_WR_DATA(0x0000); //OSC_EN=??
		delay_ms(5);
		
		// Exit Sleep mode Setting
		LCD_WR_REG(0x0019); LCD_WR_DATA(0x0001); //OSC_EN='1', start Osc
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0088); //STB=0
		delay_ms(5);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0080); //DK=0
		delay_ms(5);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x0090); //PON=1
		delay_ms(5);
		LCD_WR_REG(0x001F); LCD_WR_DATA(0x00D0); //VCOMG=1
		delay_ms(5);
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x0038); //GON=1, DTE=1, D=10
		delay_ms(40);
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x003F); //GON=1, DTE=1, D=11
		
		//LCD_WriteReg(0x16,(1<<5)|(0<<6));//MY=0,MX=1,MV=1,BGR=0	
		
		//LCD_WR_REG(0x0016); LCD_WR_DATA(0x00a0); //GON=??DTE=??D[1:0]=?0?
		//delay_ms(40);
		
	}
		
}  		  
  


//////////////////////////////////////////////////////////////////////////////////
//2��������
//////////////////////////////////////////////////////////////////////////////////

//���ù��λ��
//Xpos:������
//Ypos:������
__inline void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	if(lcddev.id==0x0072)
	{
		LCD_WriteReg(0x02, Ypos>>8);//���x�߰�λ
		LCD_WriteReg(0x03, Ypos);	//���x�Ͱ�λ
		LCD_WriteReg(0x06, Xpos>>8);//���y�߰�λ
		LCD_WriteReg(0x07, Xpos);  	//���y�Ͱ�λ						   				    
	} 

	LCD_WR_REG(0X22);			//׼��д��ram
}

//����
//x:0~LCD_W
//y:0~LCD_H
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
	LCD_WR_DATA(POINT_COLOR); 
} 	

//����ALPHA BLENDING�㷨.
//src:Դ��ɫ
//dst:Ŀ����ɫ
//alpha:͸���̶�(0~32)
//����ֵ:��Ϻ����ɫ.
u16 gui_alpha_blend565(u16 src,u16 dst,u8 alpha)
{
	u32 src2;
	u32 dst2;	 
	//Convert to 32bit |-----GGGGGG-----RRRRR------BBBBB|
	src2=((src<<16)|src)&0x07E0F81F;
	dst2=((dst<<16)|dst)&0x07E0F81F;   
	//Perform blending R:G:B with alpha in range 0..32
	//Note that the reason that alpha may not exceed 32 is that there are only
	//5bits of space between each R:G:B value, any higher value will overflow
	//into the next component and deliver ugly result.
	dst2=((((dst2-src2)*alpha)>>5)+src2)&0x07E0F81F;
	return (dst2>>16)|dst2;  
} 

//����
//x:0~LCD_W
//y:0~LCD_H
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
	u16 color;
	LCD_SetCursor(x,y);//���ù��λ�� 
	color = LCD_RD_DATA16();
//	color = LCD_RD_DATA();
	return color;
} 

//��͸������
//alphaΪ͸��ָ��,ȡֵ��Χ0~32
u16 color;
void LCDDrawRectAlphaBlend(u16 x,u16 y,u16 width,u16 height,u8 alpha)
{
    u16 i = 0,j = 0;
		
	  u16 colortmp = POINT_COLOR;
		for(i = x;i < x+width;i++)
		{
			for(j = y;j < y+height;j++)
			{			
				color = LCD_ReadPoint(i,j);
				color = gui_alpha_blend565(color,LIGHTBLUE,alpha);
				POINT_COLOR = color;
				LCD_DrawPoint(i,j);
			}
		}
		POINT_COLOR = colortmp;
}

void LCD_SetFrontColor(u16 color)
{
	POINT_COLOR = color;
}

void LCD_SetBackColor(u16 color)
{
	BACK_COLOR = color;
}

/**
  * @brief  Sets the Text Font.
  * @param  fonts: specifies the font to be used.
  * @retval None
  */
void LCD_SetFont(sFONT *fonts)
{
  LCD_Currentfonts = fonts;
}

/**
  * @brief  Gets the Text Font.
  * @param  None.
  * @retval the used font.
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}


//�趨��������д����
//Xsta , Ysta:���������������
//Xend , Yend:�յ�������������
void LCD_SetDomain(u16 Xsta, u16 Ysta,u16 Xend, u16 Yend)
{
	if(lcddev.id==0x0072)//HX8352
	{
		LCD_WriteReg(0x02, Ysta>>8);//���x�߰�λ���������ֵΪ239���ʸ߰�λʼ��Ϊ0���ɲ�д
		LCD_WriteReg(0x03, Ysta);	//���x�Ͱ�λ
		LCD_WriteReg(0x04, Yend>>8);//�յ�x�߰�λ
		LCD_WriteReg(0x05, Yend);	//�յ�x�Ͱ�λ
		LCD_WriteReg(0x06, Xsta>>8);//���y�߰�λ
		LCD_WriteReg(0x07, Xsta);  	//���y�Ͱ�λ
		LCD_WriteReg(0x08, Xend>>8);//�յ�y�߰�λ
		LCD_WriteReg(0x09, Xend);	//�յ�y�Ͱ�λ						   				    
	}

	LCD_WR_REG(0X22);			//׼��д��ram
} 


void ClearScreen(u16 bColor)
{
	unsigned int i,j;
  
	//Set GRAM Area	
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
    
	for (i=0;i<LCD_HOR_SIZE;i++)
 	{
    	for (j=0;j<LCD_VER_SIZE;j++)
        {
			LCD_WR_DATA(bColor);
		}
    }
}

//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	unsigned int i,j;
  
	//Set GRAM Area
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
    
	for (i=0;i<LCD_HOR_SIZE;i++)
	{
		for (j=0;j<LCD_VER_SIZE;j++)
		{
			LCD_WR_DATA(color);
		}
	}
} 

//��ָ�����������ָ����ɫ
//�����С:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	unsigned int i,j;
	
	LCD_SetDomain(sx,sy,ex, ey);
    
	for (i=sx;i<=ex;i++)
	{
		for (j=sy;j<=ey;j++)
		{
			LCD_WR_DATA(color);
		}
	}
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
}


void show_pic(u16 sx,u16 sy,u16 ex,u16 ey,u16* p_dat)
{
	unsigned int i,j;
	
	LCD_SetDomain(sx,sy,ex, ey-1);
    
	for (i=sx;i<ex;i++)
	{
		for (j=sy;j<ey;j++)
		{
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}
	}
//	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
}

//show_pic(0,0, 103,81, (u16*)(&gImage_pic_qq_image[8]) );

static u16 bmp_file_buff[LCD_VER_SIZE+16];

void show_bmp_in_flash( u16 sx,u16 sy,u16 width, u16 high, u32 bmp_start_add )
{
	unsigned int i,j;
	u16 ex,ey;
	u32 add;
	u16* p_dat;
	
	ex = sx + width;
	if( ex > LCD_HOR_SIZE )
	{
		ex = LCD_HOR_SIZE;
	}
	ey = sy + high;
	if( ey > LCD_VER_SIZE )
	{
		ex = LCD_VER_SIZE;
	}
	
	LCD_SetDomain(sx,sy,ex-1, ey-1);
	
	//����8�ֽڵ��ļ�ͷ
	add = bmp_start_add+8;
	
	for( i=0; i<width; i++ )
	{
		//����һ�����ݣ�ÿ����ռ�����ֽ�
		SPI_Flash_Read_bmp((u8*)(&bmp_file_buff),add,high*2);
			//SPI_Flash_Read((u8*)(&bmp_file_buff),add,high*2);
		bmp_file_buff[0] = 0;
		bmp_file_buff[1] = 0;
		add += high*2;
		
		p_dat = (u16*)bmp_file_buff;
		//��FLASH����һ������
		//��ʾһ��
		for (j=sy;j<ey;j++)
		{
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}		
	}
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
}

void show_pressed_icon_in_flash( u16 sx,u16 sy,u16 width, u16 high, u32 bmp_start_add )
{
	unsigned int i,j;
	u16 ex,ey;
	u32 add;
	u16* p_dat;
	
	ex = sx + width;
	if( ex > LCD_HOR_SIZE )
	{
		ex = LCD_HOR_SIZE;
	}
	ey = sy + high;
	if( ey > LCD_VER_SIZE )
	{
		ex = LCD_VER_SIZE;
	}
	
	LCD_SetDomain(sx,sy,ex-1, ey-1);
	
	//����8�ֽڵ��ļ�ͷ
	add = bmp_start_add+8+(240*sx+sy)*2;
	
	for( i=0; i<width; i++ )
	{	
		//����һ�����ݣ�ÿ����ռ�����ֽ�
		SPI_Flash_Read_bmp((u8*)(&bmp_file_buff),add,high*2);
		add += 240*2;	
		bmp_file_buff[0] = bmp_file_buff[2];
		bmp_file_buff[1] = bmp_file_buff[3];
		p_dat = (u16*)bmp_file_buff;
		//��FLASH����һ������
		//��ʾһ��
		for (j=sy;j<ey;j++)
		{
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}		
	}
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
}

//void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash

/*
static u16 temp_buff[240*10];
void show_pic_from_flash(u16 sx,u16 sy,u16 ex,u16 ey,u32 start_address)
{
	unsigned int i,j;
	u16 lie_bytes_num;
	u16* p_dat;
	//BMP�ļ�ͷ��8���ֽ�
	u32 offset = 8;
	
	LCD_SetDomain(sx,sy,ex, ey-1);
	
	//ͼƬ����ռ���ֽ���
	lie_bytes_num = (ey - sy)<<1;
    
	for (i=sx;i<ex;i++)
  {
		//��FLASH����һ������
		SPI_Flash_Read((u8*)temp_buff,start_address+offset,lie_bytes_num);
		
		//��ʾ
		p_dat = (u16*)temp_buff;
	  for (j=sy;j<ey;j++)
    {
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}
		
		//ƫ������һ��
		offset +=  lie_bytes_num;
	}	
}
*/



//��ʾ����
//�������:
//		1, ����ԭ��:zero_point_x, zero_point_y;
//		2, �����귽��Ŵ�ϵ��: X_MUL(���ڽ�ͼƬ�����귽������)
//		3, �����귽�����ϵͳ: XN/CN (���ڽ�ͼƬ�����귽����С��Ŵ�)
//		4, ����ָ��: p_dat,
//		5, ���ݳ���:	len
//		6, ��ɫ:color
void show_qx(u16 zero_point_x, u16 zero_point_y, u8 X_MUL, u8 XN, u8 CN, u8* p_dat, u16 len, u16 color)
{
	unsigned int i;
	u16 lie_bytes_num;
	//BMP�ļ�ͷ��8���ֽ�
	u32 offset = 8;
	u16 temp16;
	
	
	//�������3��
	if( X_MUL < 1 || X_MUL > 3 )
	{
			X_MUL = 1;
	}
	
	//������ʾ���߶Ȳ���, ����������С
	if( XN > CN )
	{
		XN = CN;
	}
	
	//���������귽�����ݲ���ʾ
	if( zero_point_x+len*X_MUL > LCD_HOR_SIZE )
	{
		len = (LCD_HOR_SIZE-zero_point_x)/X_MUL;
	}
	
	//����ת��
	//<--------
	//        |  
	//        |
	//        V	
	//TO
	//^  
	//|
	//|
	//-------->	
	//zero_point_x = LCD_HOR_SIZE - zero_point_x;
	//zero_point_y = LCD_VER_SIZE-zero_point_y;	
	
	
	POINT_COLOR = color;
	for( i=0; i<len; i++ )
	{
		temp16 = *p_dat* XN / CN;
		temp16 &= 0xff;
		
		LCD_DrawPoint(zero_point_x,zero_point_y-temp16 );
		p_dat++;
		
		zero_point_x += X_MUL;
		
		delay_ms(20);
	}
	

}


//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}


//���Һ���������LCD_Currentfonts->list�е�λ��˳��
static u8 SEARCH_word(const u16 *base, u8 cnt, u16 key)
{
	u8 low, high, mid;
	
	low = 0; 
	high = cnt - 1;
	
	while (low <= high) 
	{
		mid = (low + high) / 2;
		if (base[mid] == key)
			return mid;
		if (base[mid] > key)
			high = mid - 1;
		else 
			low = mid + 1;
	}
	
	return 0;
}

//���ݺ�����LCD_Currentfonts->list�е�˳��Ų��ҵ��ַ�����ʾ��������LCD_Currentfonts->table�е�λ��
//�������ڲ�����
static u8 *GetDisplayCodeAddr(const u8 *base, u16 c)
{
	u16 idx;
	
	idx = SEARCH_word(LCD_Currentfonts->list, LCD_Currentfonts->TableSize, c);
	return (u8 *)&base[idx * LCD_Currentfonts->BytesPerChar];
}

//��ʾ����(�������ڲ�����)
void LCD_DrawChar(u16 Xpos, u16 Ypos, u16 CharIndex)
{
	u32 index = 0, i = 0;
	u16 temp;
	u8 *CharCode;
  
	CharCode = GetDisplayCodeAddr(LCD_Currentfonts->table,CharIndex);             //��ȡ��ǰ��ʾ�����ַ
	LCD_SetDomain(Xpos,Ypos,Xpos+LCD_Currentfonts->Width-1, Ypos+LCD_Currentfonts->Height-1); //�趨��ʾ��ַ
	for(index = 0; index < LCD_Currentfonts->BytesPerChar; index++)               //д���ֽ�
	{
		temp = *CharCode;
		for(i = 0; i < 8; i++)
		{
			if(temp & 0x0001)
			{
				LCD_WR_DATA(POINT_COLOR); //Ϊ1��д��ǰ��ɫ
			}
			else
			{
				LCD_WR_DATA(BACK_COLOR); //Ϊ0��д�뱳��ɫ
			}
			temp = temp>>1;                                             
		 }
		 CharCode++;                                                  //ָ����һ����ʾ�ֽ�
	}
}

//��ʾ�����ַ���
void LCD_DrawString(u16 Xpos, u16 Ypos, u8 *str)
{
	 unsigned char c1, c2;
	
	 while (*str) 
	 {
		 c1 = *str++;
		 if (c1 < 0x80)                    //ASCII�ַ�ֻռ��һ���ֽ�
			 LCD_DrawChar(Xpos, Ypos, c1); //��ʾ��ǰascii�ַ�
		 else                            
		 {
			 c2 = *str++;                  //������ռ�������ֽ�
			 LCD_DrawChar(Xpos, Ypos, (c1 << 8) | c2); //��ʾ��ǰ�ַ�
		 }
		 Xpos += LCD_Currentfonts->wWidth; //ָ����һ����ʾλ��
	 } 	
}

/*********************************************
��ʮ������ʽ��ʾ�޷��ų�������
��ڲ�����(x��y) ����ʾ���ݵ����Ͻ����ꣻ
			 num������ʾ���޷��ų�������
	       num����ֵ��ΧΪ��0~4,294,967,295(ʮ����)��
			 Ҳ����˵���øú�����������ཫһ��10λʮ��������ʾ��LCD���ϣ�
			 color:��ɫ,b_color:������ɫ��
���ڲ���: ��
˵������һ���޷��ų���������ʮ������ʽ��ʾ��TFT���ϡ�
ע�⣺��ʹ�øú���ʱ������������ʾ�����м�λ����������LCD��Ļ��
      ռ10���ַ��Ŀռ䣨��ʾ�Ķ�λʮ����������10λʱ��
		������������Ч��ʾ����ǰ�油�ո񣩡�
**********************************************/
void LCD_wrul(u16 x, u16 y, u8 w, u32 num, u8 xy)
{
	unsigned long temp; 
	u8 i;
	if(num == 0)
	{
		LCD_DrawChar(x,y,'0');
		for(i = 1; i < w; i++)
		{
			x=x-LCD_Currentfonts->Width;
			if(xy)
				LCD_DrawChar(x,y,' ');
			else
				LCD_DrawChar(x,y,'0');
		}
	}
	else
	{
		for(i = 0; i < w; i++)
		{
			if(num != 0)
			{
				temp = num/10;
				LCD_DrawChar( x, y, (num-temp*10)+'0');
				num=temp;
			}
			else/*��ǰд����λ��Ҳ����ǰ�涼д�ո�*/
			{
				if(xy)
					LCD_DrawChar(x,y,' ');
				else
					LCD_DrawChar(x,y,'0');
			}
			x=x-LCD_Currentfonts->Width;/*���ù�������ֲ�����Զ�����*/
		}
	}
}

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
//				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x,y,temp+'0',size,0); 
		x += size/2;
	}
} 

//��ʾ����,��λΪ0��ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
	 	LCD_ShowChar(x,y,temp+'0',size,0); 
		x += size/2;
	}
} 

//��ʾ����,��λΪ0,���ÿո����
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNumNull(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x,y,'0',size,0);
				x += size/2;
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x,y,temp+'0',size,0); 
		x += size/2;
	}
} 


//��ָ��λ����ʾһ���ַ�
//x:0~LCD_W
//y:0~LCD_H
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)

//��ʾģʽ�����µ��ϣ�������
//��ʾ���У�����ʾ��һ�У�����ʾ�ڶ���
//^^^^^^
//||||||
//||||||
//......
//......
//||||||
//||||||
//||||||


#define LCD_W LCD_HOR_SIZE
#define LCD_H LCD_VER_SIZE
#define MAX_CHAR_POSX LCD_W-1
#define MAX_CHAR_POSY LCD_H-11

void LCD_ShowChar(u16 x,u16 y,u8 char_id,u8 char_high,u8 mode) 
{ 
	u8 temp; 
	u8 t;
	//�ַ���������
	int lie_num;
	u8 lie_num_max;
	//�ַ�����ÿ���ֽ���
	u8 bytes_per_lie;
	int pos;
	
	if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return; 
	//���ô���
 
	//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	if( char_high == 128 )
	{
		char_id=char_id-'0';
	}
	else
	{
		char_id=char_id-' ';
	}
	
	if(!mode) //�ǵ��ӷ�ʽ
	{
		LCD_SetDomain(x,y,x+char_high-1,y+char_high-1); //�趨GRAM�����ַ 
		
		switch(char_high)
		{
			case 12:
				bytes_per_lie = 2;
				lie_num_max = 6;
				break;
			case 16:
				bytes_per_lie = 2;
				lie_num_max = 8;
			break;
			case 24:
				bytes_per_lie = 3;
				lie_num_max = 12;
			break;
			case 128:
				bytes_per_lie = 16;
				lie_num_max = 64;
			break;			
			default: return;
				
		}
		
		
		//�ַ���������
		for( lie_num=0; lie_num < lie_num_max; lie_num++ )
		{
			//�ַ�����ÿ���ֽ���
			//for( pos=bytes_per_lie-1; pos>=0; pos-- )
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==12)temp=asc2_1206[char_id][lie_num*bytes_per_lie+pos]; 	 		//����1206����
				else if(char_high==16)temp=asc2_1608[char_id][lie_num*bytes_per_lie+pos];	//����1608����
				else if(char_high==24)temp=asc2_2412[char_id][lie_num*bytes_per_lie+pos];	//����2412����
				else if(char_high==128)temp=asc2_12864[char_id][lie_num*bytes_per_lie+pos];	//����6432����
				else return;																	//û�е��ֿ�				
			
				//1206����ÿ�������ֽڣ������ֽڣ��ڶ����ֽڣ�����λ����
				if( ( char_high==12 ) && (pos == 0) )
				{
					if(temp&0x08) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x04) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}	
					if(temp&0x02) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x01) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}						
				}
				else
				{
					if(temp&0x80) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x40) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}	
					if(temp&0x20) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x10) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}		
					if(temp&0x08) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x04) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}	
					if(temp&0x02) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x01) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}						
				}
			}
		}

		LCD_SetDomain(0,0,LCD_W,LCD_H);//�ָ�Gramȫ������ 
	}else//���ӷ�ʽ(���Ƿ�ʽ)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//����1206���壬sizeΪ����߶�
		//	else temp=asc2_1608[num][pos]; //����1608����
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����
		//		temp>>=1; 
		//	} 
		//} 
	}
	
	LCD_CS_SET;
}   

#include "../page_com/char_model.h"
void LCD_ShowHZ(u16 x,u16 y,u16 char_id,u8 char_high,u8 mode) 
{ 
	u8 temp; 
	u8 t;
	//�ַ���������
	int lie_num;
	u8 lie_num_max;
	//�ַ�����ÿ���ֽ���
	u8 bytes_per_lie;
	int pos;
	
//	x = LCD_HOR_SIZE-x;
	
	if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return; 
	//���ô���
 

	
	if(!mode) //�ǵ��ӷ�ʽ
	{
		LCD_SetDomain(x,y,x+(char_high-1),y+char_high-1); //�趨GRAM�����ַ 
		//	LCD_SetDomain(x-char_high+1,y,x,y+char_high-1); //�趨GRAM�����ַ 
		
		switch(char_high)
		{
			case 16:
				bytes_per_lie = 2;
				lie_num_max = 16;
			break;			
			case 24:
				bytes_per_lie = 3;
				lie_num_max = 24;
			break;			
			case 32:
				bytes_per_lie = 4;
				lie_num_max = 32;
			break;		
			case 48:
				bytes_per_lie = 6;
				lie_num_max = 48;
				break;
			default: return;
				
		}
		
		
		//�ַ���������
		for( lie_num=0; lie_num <lie_num_max; lie_num++ )
		{
			//�ַ�����ÿ���ֽ���
//			for( pos=bytes_per_lie-1; pos>=0; pos-- )
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==16)temp=CM_16X16[char_id][lie_num*bytes_per_lie+pos];	//����2412���� 
				else if(char_high==24)temp=CM_24X24[char_id][lie_num*bytes_per_lie+pos];	//����2412����
				else if(char_high==32)temp=CM_32X32[char_id][lie_num*bytes_per_lie+pos];	//����2412����
				else if(char_high==48)temp=CM_48X48[char_id][lie_num*bytes_per_lie+pos];	//����2412����
				else return;																	//û�е��ֿ�				
			
				{
					/*
					for(t=0;t<8;t++) 
					{ 
						if(temp&0x01) {LCD_WR_DATA(POINT_COLOR);}
						else	{LCD_WR_DATA(BACK_COLOR);}
						temp>>=1; 
					}
					*/
					if(temp&0x80) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x40) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x20) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x10) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x08) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x04) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x02) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
					if(temp&0x01) {LCD_WR_DATA(POINT_COLOR);}
					else	{LCD_WR_DATA(BACK_COLOR);}
				}
			}
		}

		LCD_SetDomain(0,0,LCD_W,LCD_H);//�ָ�Gramȫ������ 
	}else//���ӷ�ʽ(���Ƿ�ʽ)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//����1206���壬sizeΪ����߶�
		//	else temp=asc2_1608[num][pos]; //����1608����
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����
		//		temp>>=1; 
		//	} 
		//} 
	}
	
	LCD_CS_SET;
}   

//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 total_width,u16 char_high,u8 char_width,u8 *p)
{         
	u8 x0;
	//��ǰXλ��,��ʾ���ұ�λ��
	u16 curr_x_pos, rightest_x_pos;
	
	if(*p == 0)
		return;
	
	curr_x_pos = x;
	rightest_x_pos = x + total_width;
	
	//y = 240-y;
//	x = LCD_HOR_SIZE - x;
	x0 = x;
		
	
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(curr_x_pos>rightest_x_pos)
				{	
					//��һ�дӿ�ʼλ����ʾ
					x=x0;
					
					if( y <= LCD_VER_SIZE )
					{
						//����һ��
						y += char_high;
					}
					else
					{
						//������Ļ���·�
						return;
					}
				}
				
				LCD_ShowChar(x,y,*p,char_high,0);
				
        x += char_width/2;
        p++;
				
				curr_x_pos += char_width/2;
    }  
}


/*
GB2312��¼�򻯺��ּ����š���ĸ�����ļ����ȹ�7445 ��ͼ���ַ������к���ռ6763 ����GB2312 �涨��������һ��ͼ���ַ������������ֽڱ�ʾ��ÿ���ֽھ�������λ�����ʾ����
ϰ���ϳƵ�һ���ֽ�Ϊ�����ֽڡ�������ν�����롣�ڶ����ֽ�Ϊ�����ֽڡ�������ν��λ�롣GB2312�D80�����˴󲿷ֳ��õ�һ���������֣���9���ķ��š����ַ����Ǽ������е���
��ϵͳ�͹��ʻ��������֧�ֵ������ַ�������Ҳ��������������ַ���������뷶Χ�Ǹ�λ0xa1��0xfe����λҲ��0xa1��0xfe�����ִ�0xb0a1��ʼ��������0xf7fe��GB2312�������
��Ϊ94��������Ӧ��һ�ֽ�(0xa1��0xfe)��ÿ����94 ��λ(0xa1��0xfe)����Ӧ�ڶ��ֽڡ������ֽڵ�ֵ�ֱ�Ϊ����ֵ��λ��ֵ��32(20H)�����Ҳ��Ϊ��λ�롣01��09��Ϊ���š�����
����16��87��Ϊ������(0xb0��0xf7)��10��15����88��94�����д���һ����׼���Ŀհ�����GB2312����¼�ĺ��ֳַ���������һ���ǳ��ú��ּ�3755��������16��55����������ƴ����
ĸ������˳�����У��ڶ��������Ǵγ��ú��ּ�3008 ��������56��87 ���������ף��ʻ�˳�����С��ʶ�GB2312 ����ܱ�ʾ6763 �����֡�
*/

//E:\hqdcj_display\display_pro\pic_font\Gb2312_16X16_hz.FON
//PC2LCD2002ȡģ��ʽ���ã�����+����ʽ+˳��+C51��ʽ
//����֤�������֣��ֶ������ĵ���ģ �� ���ֿ�Gb2312_16X16_hz.FON�ҵ�����ģ ��ȫһ��
/*

 ��(ƫ�ƣ�0x00E020) ��(ƫ�ƣ�0x26780)

{0x00,0x01,0x00,0x02,0x00,0x0C,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00},"��",0

{0x40,0x00,0x47,0xC2,0x44,0x41,0x44,0x42,0x7C,0x7C,0x01,0x00,0x01,0x00,0xFF,0xFF},
{0x01,0x02,0x05,0x84,0x09,0x60,0x11,0x10,0x61,0x08,0x01,0x04,0x01,0x02,0x00,0x00},"��",1


*/

u32 get_GB2312_offset(const u8* c)
{ 
	u32 tmp32;
	u8 h_byte,l_byte;
	
  h_byte = *c;    
  l_byte = *(c+1); 

  tmp32 = ( (h_byte-0xa1)*94 + (l_byte-0xa1) )*32;
	
	return tmp32;
	
}

static u8 hz_buff[256];
void LCD_ShowChar_hz16x16(u16 x,u16 y,const u8* p,u8 char_high,u8 mode) 
{ 
	u8 temp; 
	u8 t;
	//�ַ���������
	int lie_num;
	u8 lie_num_max;
	//�ַ�����ÿ���ֽ���
	u8 bytes_per_lie;
	int pos;
	u32 hz_offset;
	
	hz_offset = get_GB2312_offset(p) + GB2312_16X16_HZ_OFFSET;
	SPI_Flash_Read(hz_buff,hz_offset,32);
	
	if(!mode) //�ǵ��ӷ�ʽ
	{
		LCD_SetDomain(x,y,x+char_high-1,y+char_high-1); //�趨GRAM�����ַ 
		
		switch(char_high)
		{
			case 12:
				bytes_per_lie = 2;
				lie_num_max = 6;
				break;
			case 16:
				bytes_per_lie = 2;
				lie_num_max = 16;
			break;
			case 24:
				bytes_per_lie = 3;
				lie_num_max = 12;
			break;
			case 128:
				bytes_per_lie = 16;
				lie_num_max = 64;
			break;			
			default: return;
				
		}
		
		
		//�ַ���������
		for( lie_num=0; lie_num < lie_num_max; lie_num++ )
		{
			//�ַ�����ÿ���ֽ���
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==12)temp=hz_buff[lie_num*bytes_per_lie+pos]; 	 		//����1206����
				else if(char_high==16)temp=hz_buff[lie_num*bytes_per_lie+pos];	//����1608����
				else if(char_high==24)temp=hz_buff[lie_num*bytes_per_lie+pos];	//����2412����
				else if(char_high==128)temp=hz_buff[lie_num*bytes_per_lie+pos];	//����6432����
				else return;																	//û�е��ֿ�				
			

				{
					if(temp&0x80) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x40) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}	
					if(temp&0x20) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x10) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}		
					if(temp&0x08) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x04) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}	
					if(temp&0x02) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}
					if(temp&0x01) 
					{	
						LCD_WR_DATA(POINT_COLOR);
					}
					else		
					{
						LCD_WR_DATA(BACK_COLOR);
					}						
				}
			}
		}

		LCD_SetDomain(0,0,LCD_W,LCD_H);//�ָ�Gramȫ������ 
	}else//���ӷ�ʽ(���Ƿ�ʽ)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//����1206���壬sizeΪ����߶�
		//	else temp=asc2_1608[num][pos]; //����1608����
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����
		//		temp>>=1; 
		//	} 
		//} 
	}
	
	LCD_CS_SET;
}   

//LCD_ShowString_hz16x16(10,70,200,16,16,"����");	
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ	
static u32 hz_offset;
void LCD_ShowString_hz16x16(u16 x,u16 y,u16 total_width,u16 char_high,u8 char_width,const u8* p)
{         
	u8 x0;
	//��ǰXλ��,��ʾ���ұ�λ��
	u16 curr_x_pos, rightest_x_pos;
	
	u8 tmp8;
	
	
	
	curr_x_pos = x;
	rightest_x_pos = x + total_width;
	
	//y = 240-y;
	//x = LCD_HOR_SIZE - x;
	x0 = x;
		
	
    while(*p!=0x00)//�ж��ǲ��ǷǷ��ַ�!
    { 
        if(curr_x_pos>rightest_x_pos)
		{	
			//��һ�дӿ�ʼλ����ʾ
			x=x0;
			
			if( y <= LCD_VER_SIZE )
			{
				//����һ��
				y += char_high;
			}
			else
			{
				//������Ļ���·�
				return;
			}
		}
		
		//hz_offset = get_GB2312_offset((unsigned char *)"��");;
		//hz_offset = get_GB2312_offset(p);
		if(*p < 127)
		{
			LCD_ShowChar(x,y,*p,char_high,0);				
			//����
    		x += ((char_width+1)>>1);				
			//ָ����һ������
    		p+=1;				
			curr_x_pos += ((char_width+1)>>1);
		}
		else
		{
			LCD_ShowChar_hz16x16(x,y,p,char_high,0);				
			//����
    		x += char_width;				
			//ָ����һ������
    		p+=2;				
			curr_x_pos += char_width;
		}
    }  
}
  	
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//����   
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
	LCD_ShowString(24,20,200,16,16,"RST");//��ʾ��������
  	POINT_COLOR=RED;//���û�����ɫ 
}
////////////////////////////////////////////////////////////////////////////////
//���ݴ�����ר�в���
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//��ʵ��Բ
//x0,y0:����
//r:�뾶
//color:��ɫ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
//������֮��ľ���ֵ 
//x1,x2����ȡ��ֵ��������
//����ֵ��|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//��һ������
//(x1,y1),(x2,y2):��������ʼ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


