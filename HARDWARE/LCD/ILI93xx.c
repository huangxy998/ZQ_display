#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"
#include "delay.h"	 
#include "fonts.h"	


#include "flash.h"	

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32F103开发板
//2.4寸/2.8寸/3.5寸/4.3寸/7寸 TFT液晶驱动	  
//支持驱动IC型号包括:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963等		    
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/7/4
//版本：V3.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2修改说明
//支持了SPFD5408的驱动,另外把液晶ID直接打印成HEX格式.方便查看LCD驱动IC.
//V1.3
//加入了快速IO的支持
//修改了背光控制的极性（适用于V1.8及以后的开发板版本）
//对于1.8版本之前(不包括1.8)的液晶模块,请修改LCD_Init函数的LCD_LED=1;为LCD_LED=1;
//V1.4
//修改了LCD_ShowChar函数，使用画点功能画字符。
//加入了横竖屏显示的支持
//V1.5 20110730
//1,修改了B505液晶读颜色有误的bug.
//2,修改了快速IO及横竖屏的设置方式.
//V1.6 20111116
//1,加入对LGDP4535液晶的驱动支持
//V1.7 20120713
//1,增加LCD_RD_DATA函数
//2,增加对ILI9341的支持
//3,增加ILI9325的独立驱动代码
//4,增加LCD_Scan_Dir函数(慎重使用)	  
//6,另外修改了部分原来的函数,以适应9341的操作
//V1.8 20120905
//1,加入LCD重要参数设置结构体lcddev
//2,加入LCD_Display_Dir函数,支持在线横竖屏切换
//V1.9 20120911
//1,新增RM68042驱动（ID:6804），但是6804不支持横屏显示！！原因：改变扫描方式，
//导致6804坐标设置失效，试过很多方法都不行，暂时无解。
//V2.0 20120924
//在不硬件复位的情况下,ILI9341的ID读取会被误读成9300,修改LCD_Init,将无法识别
//的情况（读到ID为9300/非法ID）,强制指定驱动IC为ILI9341，执行9341的初始化。
//V2.1 20120930
//修正ILI9325读颜色的bug。
//V2.2 20121007
//修正LCD_Scan_Dir的bug。
//V2.3 20130120
//新增6804支持横屏显示
//V2.4 20131120
//1,新增NT35310（ID:5310）驱动器的支持
//2,新增LCD_Set_Window函数,用于设置窗口,对快速填充,比较有用,但是该函数在横屏时,不支持6804.
//V2.5 20140211
//1,新增NT35510（ID:5510）驱动器的支持
//V2.6 20140504
//1,新增ASCII 24*24字体的支持(更多字体用户可以自行添加)  
//2,修改部分函数参数,以支持MDK -O2优化
//3,针对9341/35310/35510,写时间设置为最快,尽可能的提高速度
//4,去掉了SSD1289的支持,因为1289实在是太慢了,读周期要1us...简直奇葩.不适合F4使用
//5,修正68042及C505等IC的读颜色函数的bug.
//V2.7 20140710
//1,修正LCD_Color_Fill函数的一个bug. 
//2,修正LCD_Scan_Dir函数的一个bug.
//V2.8 20140721
//1,解决MDK使用-O2优化时LCD_ReadPoint函数读点失效的问题.
//2,修正LCD_Scan_Dir横屏时设置的扫描方式显示不全的bug.
//V2.9 20141130
//1,新增对SSD1963 LCD的支持.
//2,新增LCD_SSD_BackLightSet函数
//3,取消ILI93XX的Rxx寄存器定义
//V3.0 20150423
//修改SSD1963 LCD屏的驱动参数.
//////////////////////////////////////////////////////////////////////////////////	 

static sFONT *LCD_Currentfonts;

//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;


//////////////////////////////////////////////////////////////////////////////////
//1，寄存器读写及芯片初始化
//////////////////////////////////////////////////////////////////////////////////
	 					    
//写寄存器函数
//data:寄存器值
void LCD_WR_REG(u16 data)
{ 
	LCD_RD_SET;
	LCD_RS_CLR;//写地址  
 	LCD_CS_CLR; 
	DATAOUT(data); 
	LCD_WR_CLR; 
	LCD_WR_SET; 
	LCD_RS_SET;
//	if (data != 0x22)
//		LCD_CS_SET;   
}
//写数据函数
//可以替代LCD_WR_DATAX宏,拿时间换空间.
//data:寄存器值
void LCD_WR_DATAX(u16 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}
/*写8位的数据*/
void LCD_WR_DATA8(u8 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}

//读LCD数据
//返回值:读到的值
u16 LCD_RD_DATA(void)
{										   
	u16 t;
 	GPIOB->CRL=0X88888888; //PB0-7  上拉输入
	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
	GPIOB->ODR=0X0000;     //全部输出0

	LCD_RS_SET;
	LCD_CS_CLR;
	//读取数据(读寄存器时,并不需要读2次)
	LCD_RD_CLR;
	if(lcddev.id==0X8989)delay_us(2);//FOR 8989,延时2us					   
	t=DATAIN;  
	LCD_RD_SET;
	LCD_CS_SET; 

	GPIOB->CRL=0X33333333; //PB0-7  上拉输出
	GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    //全部输出高
	return t;  
}

u16 LCD_RD_DATA16(void)
{										   
	u16 t;
 	GPIOB->CRL=0X88888888; //PB0-7  上拉输入
	GPIOB->CRH=0X88888888; //PB8-15 上拉输入
	GPIOB->ODR=0X0000;     //全部输出0

//	LCD_RS_SET;
//	LCD_CS_CLR;
	//读取数据(读寄存器时,并不需要读2次)
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

	GPIOB->CRL=0X33333333; //PB0-7  上拉输出
	GPIOB->CRH=0X33333333; //PB8-15 上拉输出
	GPIOB->ODR=0XFFFF;    //全部输出高
	return t;  
}


//写寄存器
//LCD_Reg:寄存器编号
//LCD_RegValue:要写入的值
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}   
//读寄存器
//LCD_Reg:寄存器编号
//返回值:读到的值
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
 	LCD_WR_REG(LCD_Reg);  //写入要读的寄存器号  
	return LCD_RD_DATA(); 
} 
//开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
} 
//LCD写GRAM
//RGB_Code:颜色值
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_WR_DATA(RGB_Code);//写十六位GRAM
}
//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}	


//初始化lcd
//该初始化函数可以初始化各种ALIENTEK出品的LCD液晶屏
//本函数占用较大flash,用户可以根据自己的实际情况,删掉未用到的LCD初始化代码.以节省空间.
void LCD_Init(void)
{ 
	u16 tmp16;
	
 	RCC->APB2ENR|=1<<3;//先使能外设PORTB时钟
 	RCC->APB2ENR|=1<<4;//先使能外设PORTC时钟

	RCC->APB2ENR|=1<<0;    //开启辅助时钟
	JTAG_Set(SWD_ENABLE);  //开启SWD
											 
	//PORTC6~10复用推挽输出 	
	GPIOC->CRH&=0XFFFFF000;
	GPIOC->CRH|=0X00000333; 
	GPIOC->CRL&=0X00FFFFFF;
	GPIOC->CRL|=0X33000000;  
	GPIOC->ODR|=0X07C0; 	 
	//PORTB 推挽输出 	
	GPIOB->CRH=0X33333333;
	GPIOB->CRL=0X33333333; 	 
	GPIOB->ODR=0XFFFF;

	delay_ms(50); // delay 50 ms 
	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
	lcddev.id = LCD_ReadReg(0x0000); 
	
	delay_ms(50); // delay 50 ms 
    LCD_WR_REG(0x001A); LCD_WR_DATA(0x0002); //BT	//0x001A电源控制寄存器	，低三位有效
	tmp16 = LCD_ReadReg(0x001A); 
		
	delay_ms(50); // delay 50 ms 
    LCD_WR_REG(0x001B); LCD_WR_DATA(0x0088); //VRH	//0x001b电源控制寄存器	 ，低五位有效
	tmp16 = LCD_ReadReg(0x001B);			

	lcddev.dir=1;	//横屏
 	printf(" LCD ID:%x\r\n",lcddev.id); //打印LCD ID  

	if( lcddev.id == 0x72 )
	{
		lcddev.width = LCD_HOR_SIZE;
		lcddev.height = LCD_VER_SIZE;
		lcddev.wramcmd = 0x22;
	
    	LCD_WR_REG(0x001A); LCD_WR_DATA(0x0002); //BT	//0x001A电源控制寄存器	，低三位有效
		tmp16 = LCD_ReadReg(0x001A); 
	
		LCD_WR_REG(0x001B); LCD_WR_DATA(0x0088); //VRH	//0x001b电源控制寄存器	 ，低五位有效
		
		//****VCOM offset**///
		LCD_WR_REG(0x0023); LCD_WR_DATA(0x0000); //SEL_VCM		 //电源
		LCD_WR_REG(0x0024); LCD_WR_DATA(0x005F); //VCM			 //电源
		LCD_WR_REG(0x0025); LCD_WR_DATA(0x0015); //VDV			 //电源
		LCD_WR_REG(0x002D); LCD_WR_DATA(0x0003); //NOW[2:0]=011
		
		/*****************电源设置*/
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
		
		/*********18位颜色与16位颜色选择*/
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
		
		/************设置GRAM显示区域即屏幕显示大小*/
		LCD_WR_REG(0x0002); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0003); LCD_WR_DATA(0x0000); //Column Start
		LCD_WR_REG(0x0004); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0005); LCD_WR_DATA(0x00EF); //Column End
		LCD_WR_REG(0x0006); LCD_WR_DATA(0x0000);
		LCD_WR_REG(0x0007); LCD_WR_DATA(0x0000); //Row Start
		LCD_WR_REG(0x0008); LCD_WR_DATA(0x0001);//0001
		LCD_WR_REG(0x0009); LCD_WR_DATA(0x008F); //Row End00AF
		
		/************显示设置*/
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x0038); //GON=1, DTE=1, D=10
		delay_ms(40);
		LCD_WR_REG(0x0028); LCD_WR_DATA(0x003F); //GON=1, DTE=1, D=11
		LCD_WR_REG(0x0022); //Start GRAM write

		/***************睡眠模式设置*/ 
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
//2，驱动层
//////////////////////////////////////////////////////////////////////////////////

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
__inline void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	if(lcddev.id==0x0072)
	{
		LCD_WriteReg(0x02, Ypos>>8);//起点x高八位
		LCD_WriteReg(0x03, Ypos);	//起点x低八位
		LCD_WriteReg(0x06, Xpos>>8);//起点y高八位
		LCD_WriteReg(0x07, Xpos);  	//起点y低八位						   				    
	} 

	LCD_WR_REG(0X22);			//准备写入ram
}

//画点
//x:0~LCD_W
//y:0~LCD_H
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//设置光标位置 
	LCD_WR_DATA(POINT_COLOR); 
} 	

//快速ALPHA BLENDING算法.
//src:源颜色
//dst:目标颜色
//alpha:透明程度(0~32)
//返回值:混合后的颜色.
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

//读点
//x:0~LCD_W
//y:0~LCD_H
//返回值:此点的颜色
u16 LCD_ReadPoint(u16 x,u16 y)
{
	u16 color;
	LCD_SetCursor(x,y);//设置光标位置 
	color = LCD_RD_DATA16();
//	color = LCD_RD_DATA();
	return color;
} 

//画透明矩形
//alpha为透明指数,取值范围0~32
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


//设定窗口区域写数据
//Xsta , Ysta:起点横坐标和纵坐标
//Xend , Yend:终点横坐标和纵坐标
void LCD_SetDomain(u16 Xsta, u16 Ysta,u16 Xend, u16 Yend)
{
	if(lcddev.id==0x0072)//HX8352
	{
		LCD_WriteReg(0x02, Ysta>>8);//起点x高八位但由于最大值为239，故高八位始终为0，可不写
		LCD_WriteReg(0x03, Ysta);	//起点x低八位
		LCD_WriteReg(0x04, Yend>>8);//终点x高八位
		LCD_WriteReg(0x05, Yend);	//终点x低八位
		LCD_WriteReg(0x06, Xsta>>8);//起点y高八位
		LCD_WriteReg(0x07, Xsta);  	//起点y低八位
		LCD_WriteReg(0x08, Xend>>8);//终点y高八位
		LCD_WriteReg(0x09, Xend);	//终点y低八位						   				    
	}

	LCD_WR_REG(0X22);			//准备写入ram
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

//清屏函数
//color:要清屏的填充色
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

//在指定区域内填充指定颜色
//区域大小:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:要填充的颜色
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
	
	//不读8字节的文件头
	add = bmp_start_add+8;
	
	for( i=0; i<width; i++ )
	{
		//读出一列数据，每个点占两个字节
		SPI_Flash_Read_bmp((u8*)(&bmp_file_buff),add,high*2);
			//SPI_Flash_Read((u8*)(&bmp_file_buff),add,high*2);
		bmp_file_buff[0] = 0;
		bmp_file_buff[1] = 0;
		add += high*2;
		
		p_dat = (u16*)bmp_file_buff;
		//从FLASH读出一列数据
		//显示一列
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
	
	//不读8字节的文件头
	add = bmp_start_add+8+(240*sx+sy)*2;
	
	for( i=0; i<width; i++ )
	{	
		//读出一列数据，每个点占两个字节
		SPI_Flash_Read_bmp((u8*)(&bmp_file_buff),add,high*2);
		add += 240*2;	
		bmp_file_buff[0] = bmp_file_buff[2];
		bmp_file_buff[1] = bmp_file_buff[3];
		p_dat = (u16*)bmp_file_buff;
		//从FLASH读出一列数据
		//显示一列
		for (j=sy;j<ey;j++)
		{
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}		
	}
	LCD_SetDomain(0,0,LCD_HOR_SIZE, LCD_VER_SIZE);
}

//void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash

/*
static u16 temp_buff[240*10];
void show_pic_from_flash(u16 sx,u16 sy,u16 ex,u16 ey,u32 start_address)
{
	unsigned int i,j;
	u16 lie_bytes_num;
	u16* p_dat;
	//BMP文件头点8个字节
	u32 offset = 8;
	
	LCD_SetDomain(sx,sy,ex, ey-1);
	
	//图片第列占用字节数
	lie_bytes_num = (ey - sy)<<1;
    
	for (i=sx;i<ex;i++)
  {
		//从FLASH读出一列数据
		SPI_Flash_Read((u8*)temp_buff,start_address+offset,lie_bytes_num);
		
		//显示
		p_dat = (u16*)temp_buff;
	  for (j=sy;j<ey;j++)
    {
			LCD_WR_DATA(*p_dat);
			p_dat++;
		}
		
		//偏移至下一列
		offset +=  lie_bytes_num;
	}	
}
*/



//显示曲线
//输入参数:
//		1, 座标原点:zero_point_x, zero_point_y;
//		2, 横坐标方向放大系数: X_MUL(用于将图片横坐标方向拉伸)
//		3, 纵坐标方向比例系统: XN/CN (用于将图片纵坐标方向缩小或放大)
//		4, 数据指针: p_dat,
//		5, 数据长度:	len
//		6, 颜色:color
void show_qx(u16 zero_point_x, u16 zero_point_y, u8 X_MUL, u8 XN, u8 CN, u8* p_dat, u16 len, u16 color)
{
	unsigned int i;
	u16 lie_bytes_num;
	//BMP文件头点8个字节
	u32 offset = 8;
	u16 temp16;
	
	
	//最多拉伸3倍
	if( X_MUL < 1 || X_MUL > 3 )
	{
			X_MUL = 1;
	}
	
	//由于显示屏高度不够, 仅按比例缩小
	if( XN > CN )
	{
		XN = CN;
	}
	
	//超出横坐标方向数据不显示
	if( zero_point_x+len*X_MUL > LCD_HOR_SIZE )
	{
		len = (LCD_HOR_SIZE-zero_point_x)/X_MUL;
	}
	
	//坐标转换
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


//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
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
//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}


//查找汉字内码在LCD_Currentfonts->list中的位置顺序
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

//根据汉字在LCD_Currentfonts->list中的顺序号查找到字符在显示代码数组LCD_Currentfonts->table中的位置
//仅限于内部调用
static u8 *GetDisplayCodeAddr(const u8 *base, u16 c)
{
	u16 idx;
	
	idx = SEARCH_word(LCD_Currentfonts->list, LCD_Currentfonts->TableSize, c);
	return (u8 *)&base[idx * LCD_Currentfonts->BytesPerChar];
}

//显示文字(仅限于内部调用)
void LCD_DrawChar(u16 Xpos, u16 Ypos, u16 CharIndex)
{
	u32 index = 0, i = 0;
	u16 temp;
	u8 *CharCode;
  
	CharCode = GetDisplayCodeAddr(LCD_Currentfonts->table,CharIndex);             //获取当前显示代码地址
	LCD_SetDomain(Xpos,Ypos,Xpos+LCD_Currentfonts->Width-1, Ypos+LCD_Currentfonts->Height-1); //设定显示地址
	for(index = 0; index < LCD_Currentfonts->BytesPerChar; index++)               //写入字节
	{
		temp = *CharCode;
		for(i = 0; i < 8; i++)
		{
			if(temp & 0x0001)
			{
				LCD_WR_DATA(POINT_COLOR); //为1则写入前景色
			}
			else
			{
				LCD_WR_DATA(BACK_COLOR); //为0则写入背景色
			}
			temp = temp>>1;                                             
		 }
		 CharCode++;                                                  //指向下一个显示字节
	}
}

//显示文字字符串
void LCD_DrawString(u16 Xpos, u16 Ypos, u8 *str)
{
	 unsigned char c1, c2;
	
	 while (*str) 
	 {
		 c1 = *str++;
		 if (c1 < 0x80)                    //ASCII字符只占用一个字节
			 LCD_DrawChar(Xpos, Ypos, c1); //显示当前ascii字符
		 else                            
		 {
			 c2 = *str++;                  //汉字则占用两个字节
			 LCD_DrawChar(Xpos, Ypos, (c1 << 8) | c2); //显示当前字符
		 }
		 Xpos += LCD_Currentfonts->wWidth; //指向下一个显示位置
	 } 	
}

/*********************************************
以十进制形式显示无符号长整型数
入口参数：(x，y) 是显示内容的右上角坐标；
			 num是欲显示的无符号长整型数
	       num的数值范围为：0~4,294,967,295(十进制)，
			 也就是说利用该函数，我们最多将一个10位十进制数显示在LCD屏上；
			 color:颜色,b_color:背景颜色。
出口参数: 无
说明：将一个无符号长整型数以十进制形式显示在TFT屏上。
注意：在使用该函数时，不论最终显示的数有几位，它都将在LCD屏幕上
      占10个字符的空间（显示的多位十进制数不足10位时，
		本函数会在有效显示数字前面补空格）。
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
			else/*往前写满ｗ位，也就是前面都写空格*/
			{
				if(xy)
					LCD_DrawChar(x,y,' ');
				else
					LCD_DrawChar(x,y,'0');
			}
			x=x-LCD_Currentfonts->Width;/*设置光标在文字插入后自动左移*/
		}
	}
}

//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
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

//显示数字,高位为0显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
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

//显示数字,高位为0,则用空格代替
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
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


//在指定位置显示一个字符
//x:0~LCD_W
//y:0~LCD_H
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)

//显示模式：从下到上，从左到右
//显示序列：先显示第一列，再显示第二列
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
	//字符点阵列数
	int lie_num;
	u8 lie_num_max;
	//字符点阵每列字节数
	u8 bytes_per_lie;
	int pos;
	
	if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return; 
	//设置窗口
 
	//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	if( char_high == 128 )
	{
		char_id=char_id-'0';
	}
	else
	{
		char_id=char_id-' ';
	}
	
	if(!mode) //非叠加方式
	{
		LCD_SetDomain(x,y,x+char_high-1,y+char_high-1); //设定GRAM区域地址 
		
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
		
		
		//字符点阵列数
		for( lie_num=0; lie_num < lie_num_max; lie_num++ )
		{
			//字符点阵每列字节数
			//for( pos=bytes_per_lie-1; pos>=0; pos-- )
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==12)temp=asc2_1206[char_id][lie_num*bytes_per_lie+pos]; 	 		//调用1206字体
				else if(char_high==16)temp=asc2_1608[char_id][lie_num*bytes_per_lie+pos];	//调用1608字体
				else if(char_high==24)temp=asc2_2412[char_id][lie_num*bytes_per_lie+pos];	//调用2412字体
				else if(char_high==128)temp=asc2_12864[char_id][lie_num*bytes_per_lie+pos];	//调用6432字体
				else return;																	//没有的字库				
			
				//1206字体每列两个字节，下面字节（第二个字节）低四位丢弃
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

		LCD_SetDomain(0,0,LCD_W,LCD_H);//恢复Gram全屏设置 
	}else//叠加方式(覆盖方式)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//调用1206字体，size为字体高度
		//	else temp=asc2_1608[num][pos]; //调用1608字体
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点
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
	//字符点阵列数
	int lie_num;
	u8 lie_num_max;
	//字符点阵每列字节数
	u8 bytes_per_lie;
	int pos;
	
//	x = LCD_HOR_SIZE-x;
	
	if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return; 
	//设置窗口
 

	
	if(!mode) //非叠加方式
	{
		LCD_SetDomain(x,y,x+(char_high-1),y+char_high-1); //设定GRAM区域地址 
		//	LCD_SetDomain(x-char_high+1,y,x,y+char_high-1); //设定GRAM区域地址 
		
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
		
		
		//字符点阵列数
		for( lie_num=0; lie_num <lie_num_max; lie_num++ )
		{
			//字符点阵每列字节数
//			for( pos=bytes_per_lie-1; pos>=0; pos-- )
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==16)temp=CM_16X16[char_id][lie_num*bytes_per_lie+pos];	//调用2412字体 
				else if(char_high==24)temp=CM_24X24[char_id][lie_num*bytes_per_lie+pos];	//调用2412字体
				else if(char_high==32)temp=CM_32X32[char_id][lie_num*bytes_per_lie+pos];	//调用2412字体
				else if(char_high==48)temp=CM_48X48[char_id][lie_num*bytes_per_lie+pos];	//调用2412字体
				else return;																	//没有的字库				
			
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

		LCD_SetDomain(0,0,LCD_W,LCD_H);//恢复Gram全屏设置 
	}else//叠加方式(覆盖方式)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//调用1206字体，size为字体高度
		//	else temp=asc2_1608[num][pos]; //调用1608字体
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点
		//		temp>>=1; 
		//	} 
		//} 
	}
	
	LCD_CS_SET;
}   

//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 total_width,u16 char_high,u8 char_width,u8 *p)
{         
	u8 x0;
	//当前X位置,显示最右边位置
	u16 curr_x_pos, rightest_x_pos;
	
	if(*p == 0)
		return;
	
	curr_x_pos = x;
	rightest_x_pos = x + total_width;
	
	//y = 240-y;
//	x = LCD_HOR_SIZE - x;
	x0 = x;
		
	
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(curr_x_pos>rightest_x_pos)
				{	
					//下一行从开始位置显示
					x=x0;
					
					if( y <= LCD_VER_SIZE )
					{
						//换下一行
						y += char_high;
					}
					else
					{
						//到达屏幕最下方
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
GB2312收录简化汉字及符号、字母、日文假名等共7445 个图形字符，其中汉字占6763 个。GB2312 规定“对任意一个图形字符都采用两个字节表示，每个字节均采用七位编码表示”，
习惯上称第一个字节为“高字节”，即所谓的区码。第二个字节为“低字节”，即所谓的位码。GB2312―80包含了大部分常用的一、二级汉字，和9区的符号。该字符集是几乎所有的中
文系统和国际化的软件都支持的中文字符集，这也是最基本的中文字符集。其编码范围是高位0xa1～0xfe，低位也是0xa1～0xfe；汉字从0xb0a1开始，结束于0xf7fe。GB2312将代码表
分为94个区，对应第一字节(0xa1～0xfe)；每个区94 个位(0xa1～0xfe)，对应第二字节。两个字节的值分别为区号值和位号值加32(20H)，因此也称为区位码。01～09区为符号、数字
区，16～87区为汉字区(0xb0～0xf7)，10～15区、88～94区是有待进一步标准化的空白区。GB2312将收录的汉字分成两级：第一级是常用汉字计3755个，置于16～55区，按汉语拼音字
母／笔形顺序排列：第二级汉字是次常用汉字计3008 个，置于56～87 区，按部首／笔画顺序排列。故而GB2312 最多能表示6763 个汉字。
*/

//E:\hqdcj_display\display_pro\pic_font\Gb2312_16X16_hz.FON
//PC2LCD2002取模方式设置：阴码+逐列式+顺向+C51格式
//经验证以下两字：手动产生的的字模 与 从字库Gb2312_16X16_hz.FON找到的字模 完全一致
/*

 川(偏移：0x00E020) 张(偏移：0x26780)

{0x00,0x01,0x00,0x02,0x00,0x0C,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00},"川",0

{0x40,0x00,0x47,0xC2,0x44,0x41,0x44,0x42,0x7C,0x7C,0x01,0x00,0x01,0x00,0xFF,0xFF},
{0x01,0x02,0x05,0x84,0x09,0x60,0x11,0x10,0x61,0x08,0x01,0x04,0x01,0x02,0x00,0x00},"张",1


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
	//字符点阵列数
	int lie_num;
	u8 lie_num_max;
	//字符点阵每列字节数
	u8 bytes_per_lie;
	int pos;
	u32 hz_offset;
	
	hz_offset = get_GB2312_offset(p) + GB2312_16X16_HZ_OFFSET;
	SPI_Flash_Read(hz_buff,hz_offset,32);
	
	if(!mode) //非叠加方式
	{
		LCD_SetDomain(x,y,x+char_high-1,y+char_high-1); //设定GRAM区域地址 
		
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
		
		
		//字符点阵列数
		for( lie_num=0; lie_num < lie_num_max; lie_num++ )
		{
			//字符点阵每列字节数
			for( pos=0; pos<bytes_per_lie; pos++ )
			{
				if(char_high==12)temp=hz_buff[lie_num*bytes_per_lie+pos]; 	 		//调用1206字体
				else if(char_high==16)temp=hz_buff[lie_num*bytes_per_lie+pos];	//调用1608字体
				else if(char_high==24)temp=hz_buff[lie_num*bytes_per_lie+pos];	//调用2412字体
				else if(char_high==128)temp=hz_buff[lie_num*bytes_per_lie+pos];	//调用6432字体
				else return;																	//没有的字库				
			

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

		LCD_SetDomain(0,0,LCD_W,LCD_H);//恢复Gram全屏设置 
	}else//叠加方式(覆盖方式)
	{ 
		//for(pos=0;pos<size;pos++) 
		//{ 
		//	if(size==12)temp=asc2_1206[char_id][pos];//调用1206字体，size为字体高度
		//	else temp=asc2_1608[num][pos]; //调用1608字体
		//	for(t=0;t<size/2;t++) 
		//	{ 
		//		if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点
		//		temp>>=1; 
		//	} 
		//} 
	}
	
	LCD_CS_SET;
}   

//LCD_ShowString_hz16x16(10,70,200,16,16,"川爸");	
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址	
static u32 hz_offset;
void LCD_ShowString_hz16x16(u16 x,u16 y,u16 total_width,u16 char_high,u8 char_width,const u8* p)
{         
	u8 x0;
	//当前X位置,显示最右边位置
	u16 curr_x_pos, rightest_x_pos;
	
	u8 tmp8;
	
	
	
	curr_x_pos = x;
	rightest_x_pos = x + total_width;
	
	//y = 240-y;
	//x = LCD_HOR_SIZE - x;
	x0 = x;
		
	
    while(*p!=0x00)//判断是不是非法字符!
    { 
        if(curr_x_pos>rightest_x_pos)
		{	
			//下一行从开始位置显示
			x=x0;
			
			if( y <= LCD_VER_SIZE )
			{
				//换下一行
				y += char_high;
			}
			else
			{
				//到达屏幕最下方
				return;
			}
		}
		
		//hz_offset = get_GB2312_offset((unsigned char *)"川");;
		//hz_offset = get_GB2312_offset(p);
		if(*p < 127)
		{
			LCD_ShowChar(x,y,*p,char_high,0);				
			//右移
    		x += ((char_width+1)>>1);				
			//指向下一个汉字
    		p+=1;				
			curr_x_pos += ((char_width+1)>>1);
		}
		else
		{
			LCD_ShowChar_hz16x16(x,y,p,char_high,0);				
			//右移
    		x += char_width;				
			//指向下一个汉字
    		p+=2;				
			curr_x_pos += char_width;
		}
    }  
}
  	
void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(24,20,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}
////////////////////////////////////////////////////////////////////////////////
//电容触摸屏专有部分
//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//画实心圆
//x0,y0:坐标
//r:半径
//color:颜色
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
//两个数之差的绝对值 
//x1,x2：需取差值的两个数
//返回值：|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//画一条粗线
//(x1,y1),(x2,y2):线条的起始坐标
//size：线条的粗细程度
//color：线条的颜色
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		gui_fill_circle(uRow,uCol,size,color);//画点 
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


