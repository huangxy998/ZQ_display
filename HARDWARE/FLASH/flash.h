#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//W25Q64 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/9 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//4M�ֽ�
#define SPI_FLASH_SIZE							0x400000

#define GB2312_16X16_HZ_OFFSET					0x00000000
#define BASIC_PAGE_OFFSET						0x0003FE42
#define MENU_PAGE_UP_OFFSET						0x0006EC4A
#define MENU_PAGE_DOWN_OFFSET					0x0009DA52
#define MENU_PAGE_PROGRESS_OFFSET				0x000CC85A
#define MENU_PAGE_PROGRESSFULL_OFFSET			0x000CDEEE
#define BASIC_PAGE_SD_ON_OFFSET					0x000CF582
#define BASIC_PAGE_SD_OFF_OFFSET				0x000CFC8A
#define BASIC_PAGE_ADD_ON_OFFSET				0x000D0392
#define BASIC_PAGE_ADD_OFF_OFFSET				0x000D0AFE

#define BASIC_PAGE_CIS_PARA_SET_OFFSET			0X000D126A
#define BASIC_PAGE_CIS_TEST_OFFSET				0X00100072
#define BASIC_PAGE_TIME_OFFSET					0X0012EE7A
#define BASIC_PAGE_CIS_LOCAL_IP_OFFSET			0X0015DC82
#define BASIC_PAGE_PARA_SET_OFFSET				0X0018CA8A
#define BASIC_PAGE_DIALOG_OFFSET				0X001BB892
#define BASIC_PAGE_SERAL_OFFSET					0X001CA07A
#define BASIC_PAGE_BLACK_LIST_OFFSET			0X001F8E82
#define BASIC_PAGE_KEYBOARD_OFFSET				0X00227C8A
#define BASIC_PAGE_SYSTEM_SET_OFFSET			0X00256A92

//END 0X0028589A



#define TOUCH_ADJUST_PARAM_OFFSET				0x003f0000

#define LOAD_BMP_PICTURE_HIGH_SPEED_MODE

//W25Xϵ��/Qϵ��оƬ�б�	   
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q64 ID  0XEF16	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16

extern u16 SPI_FLASH_TYPE;		//��������ʹ�õ�flashоƬ�ͺ�		   
#define	SPI_FLASH_CS PCout(5)  	//ѡ��FLASH	
				 
////////////////////////////////////////////////////////////////////////////
 
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void SPI_Flash_Init(void);
u16  SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
u8	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void SPI_FLASH_Write_SR(u8 sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Enable(void);  //дʹ�� 
void SPI_FLASH_Write_Disable(void);	//д����
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//��������
void SPI_Flash_Wait_Busy(void);           //�ȴ�����
void SPI_Flash_PowerDown(void);           //�������ģʽ
void SPI_Flash_WAKEUP(void);			  //����


void SPI_Flash_Read_bmp(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);

#endif
















