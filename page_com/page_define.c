#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   
#include "lcd.h"  
#include "key.h"  
#include "24cxx.h"  
#include "touch.h"  
#include "flash.h"  

#include "lcd_com_prot.h"
#include "lcd_com.h"

#include "page_define.h"
#include "char_model.h"

#include "page.h"


/*

enum
{
	PAGE_TYPE_UNKNOW
};

enum
{
	TOUCH_ENABLE,
	TOUCH_DISABLE
};


//ҳ�����ݽṹ����
typedef	struct	PAGE_S  
{
	u8 type;															//����
	u8 touch_en:								1;				//����ʹ��
	u8 rvd:											7;
	
	
	u16 start_pos_x;											//��ʼλ��X
	u16 start_pos_y;											//��ʼλ��Y
	u16 end_pos_x;												//����λ��X	
	u16 end_pos_y;												//����λ��Y	

	u8 page_item_num;										//ҳ����
	PAGE_INEM_T*	p_page_item;						//ҳ��ָ��
	
		
	void	(*page_init)(void);							//��ʼ������
	void 	(*page_fun)(void);							//�������ܺ���
}PAGE_T;



enum
{
	PAGE_ITEM_TYPE_UNKNOW
};

enum
{
	PAGE_TYPE_UNKNOW
};

enum
{
	TOUCH_ENABLE,
	TOUCH_DISABLE
};

//ҳ�����ݽṹ����
typedef	struct	PAGE_ITEM_S  
{
	u8 type;															//����
	u8 touch_en:								1;				//����ʹ��
	u8 rvd:											7;				//����
	
	u8* p_name;														//����
	u8 name_len,													//����(���ָ���)
	u8 name_val;													//ֵ
	
	u16 start_pos_x;											//��ʼλ��X
	u16 start_pos_y;											//��ʼλ��Y
	u16 end_pos_x;												//����λ��X	
	u16 end_pos_y;												//����λ��Y	


	void		(*touch_event)(void);
	void		(*touch_up_event)(void);
}PAGE_ITEM_T;

*/



//����
//���
//�ְ�
//���
const u8 page_item_func_name[8] = 
{
	CM_48X48_ZHI40, CM_48X48_NENG20,
	CM_48X48_HUN30, CM_48X48_DIAN30,
	CM_48X48_FEN10, CM_48X48_BAN30,
	CM_48X48_QING10,CM_48X48_DIAN30	
};

//������
const u8 page_item_LMD_name[3] = 
{
	CM_16X16_LING20, CM_16X16_MING30,CM_16X16_DU40
};

//���и�
const u8 page_item_DZG_name[12] = 
{
	CM_16X16_SPACE, CM_16X16_SPACE,		CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_DI10,		CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_ZHONG10, CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_GAO10,		CM_16X16_SPACE
};

//Ԥ  ��
const u8 page_item_YZ_name[3] = 
{
	CM_16X16_YU40, CM_16X16_SPACE,CM_16X16_ZHI40
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


const u16 page_item_color_default[2] = 
{
	RED, WHITE
};




///////////////////////////////////////////////////////////////////////////////////////////////////
//��������ҳ��λ��END
///////////////////////////////////////////////////////////////////////////////////////////////////
*/
const u16 page_item_color_function[8] = 
{
	GREEN, 	BLACK,
	RED,		BLACK,
	YELLOW,	BLACK,
	BLUE,		BLACK
	
};
const u16 page_item_color_HONGWAI[2] = 
{
	WHITE, BLACK
};

const u16 page_item_color_LEIJIA[4] = 
{
	WHITE, BLACK,
	RED, BLACK
};

const	PAGE_ITEM_T	page_item_basic_array[6] = 
{
  //����   
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8* name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		page_item_func_name, CM_TYPE_48X48, 2, &basic_page_data.function, &basic_page_data.function, page_item_color_function,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		FUNC_START_POS_X,	PAGE_BASIC_LINE1_POS_Y,	FUNC_START_POS_X+48*2,PAGE_BASIC_LINE1_POS_Y+48,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_function, NULL
	},
	
	
	  //�����ȵ��и�
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8 name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		page_item_DZG_name, CM_TYPE_16X16, 3, &lmd_grade,  &temp_value_zero, page_item_color_default,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		DZG_START_POS_X,	DZG_START_POS_Y,	DZG_START_POS_X+16*3, DZG_START_POS_Y+16,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_LMD, NULL
	},

	  //Ԥ����
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8 name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		NULL, 0, 0, &temp_value_zero, &temp_value_zero, page_item_color_default,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		YZS_START_POS_X,	YZS_START_POS_Y,	YZS_START_POS_X+16*3, YZS_START_POS_Y+16,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_YZS, NULL
	},	
	
  //����   
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8* name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		page_item_hongwai_name, CM_TYPE_24X24, 2, &temp_value_zero, &temp_value_zero, page_item_color_HONGWAI,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		HW_START_POS_X,	HW_START_POS_Y,	HW_START_POS_X+24*2,HW_START_POS_Y+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	empty_touch_event, NULL
	},	
	
  //ͼ��
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8* name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		page_item_tuxiang_name, CM_TYPE_24X24, 2, &temp_value_zero, &temp_value_zero, page_item_color_HONGWAI,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		HW_START_POS_X,	HW_START_POS_Y+25,	HW_START_POS_X+24*2,HW_START_POS_Y+25+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	empty_touch_event, NULL
	},	

  //�ۼ�
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;				//����
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//����
		//u8 CM_type;														//��ģ����
		//u8 name_len;													//����(���ָ���)
		//u8* name_val;													//ֵ
		//u8* color_val;												//��ɫ����ֵ
		//const u16* p_color;										//����ɫ,ǰ��ɫָ��
		page_item_leijia_name, CM_TYPE_24X24, 2, &temp_value_zero, &LJ_on_off, page_item_color_LEIJIA,
		

		//u16 start_pos_x;											//��ʼλ��X
		//u16 start_pos_y;											//��ʼλ��Y
		//u16 end_pos_x;												//����λ��X	
		//u16 end_pos_y;												//����λ��Y	
		HW_START_POS_X,	HW_START_POS_Y+25*2,	HW_START_POS_X+24*2,HW_START_POS_Y+25*2+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_LJ, NULL
	},		
		
	
};

const	PAGE_T	page_array[PAGE_ID_MAX] = 
{
  
	//��ʼ��ҳ��
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;
		//u16 init_color;												//��ʼ����ɫ		
		PAGE_TYPE_UNKNOW,	TOUCH_ENABLE,	0,	BLACK,

		//��ʼλ��X, ��ʼλ��Y, ����λ��X, ����λ��Y
		0,0,400, 240,
		
		//ҳ����
		1,
		//ҳ��ָ��
		page_item_basic_array,
		
		//��ʼ������
	 	NULL,
		//�������ܺ���
		NULL
	},

	//��������ҳ��
	{ 
		//u8 type;															//����
		//u8 touch_en:								1;				//����ʹ��
		//u8 rvd:											7;
		//u16 init_color;												//��ʼ����ɫ		
		PAGE_TYPE_UNKNOW,	TOUCH_ENABLE,	0,	BLACK,

		//��ʼλ��X, ��ʼλ��Y, ����λ��X, ����λ��Y
		0,0,400, 240,
		
		//ҳ����
		6,
		//ҳ��ָ��
		page_item_basic_array,
		
		//��ʼ������
	 	NULL,
		//�������ܺ���
		NULL
	},

	
};
