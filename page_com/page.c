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
#include "char_model.h"
#include "page.h"
#include "touch.h"
#include "lcd_com.h"

void pageBasicInit(void);
void pageBasicUpdate(void);


//ҳ������Ŀ�ṹ��
const PAGE_ITEM_T page_basic_item[] =
{
	{},
	{},
}

//ҳ��ṹ��
const PAGE_S page_basic = 
{
		
	PAGE_ID_INIT,	
	0,	0,
	LCD_HOR_SIZE, LCD_VER_SIZE,
	sizeof(page_basic_item)/sizeof(PAGE_ITEM_T),
	
 	pageBasicInit,	
 	pageBasicUpdate
}


//���� ��� �ְ� ���
const u8 page_item_func_name[4][2] = 
{
	{CM_48X48_ZHI40, CM_48X48_NENG20},
	{CM_48X48_HUN30, CM_48X48_DIAN30},
	{CM_48X48_FEN10, CM_48X48_BAN30},
	{CM_48X48_QING10,CM_48X48_DIAN30}	
};

//������
const u8 page_item_LMD_name[3] = 
{
	CM_16X16_LING20, CM_16X16_MING30,CM_16X16_DU40
};

//���и�
const u8 page_item_DZG_name[4][3] = 
{
	{CM_16X16_SPACE, CM_16X16_SPACE,	CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_DI10,		CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_ZHONG10,  CM_16X16_SPACE},
	{CM_16X16_SPACE, CM_16X16_GAO10,	CM_16X16_SPACE}
};

//Ԥ  ��
const u8 page_item_YZ_name[3] = 
{
	CM_16X16_YU40, CM_16X16_SPACE, CM_16X16_ZHI40
};

//����
const u8 page_item_BJ_name[2] = 
{
	CM_16X16_BAO40, CM_16X16_JING30
};

//����
const u8 page_item_hongwai_name[2] = 
{
	CM_24X24_HONG20_H22, CM_24X24_WAI40_H22
};

//ͼ��
const u8 page_item_tuxiang_name[2] = 
{
	CM_24X24_TU20_H22, CM_24X24_XIANG40_H22
};

//�ۼ�
const u8 page_item_leijia_name[2] = 
{
	CM_24X24_LEI30_H22, CM_24X24_JIA10_H22
};



void pageBasicInit(void)
{

}

void pageBasicUpdate(void)
{

}








