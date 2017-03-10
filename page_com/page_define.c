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


//页面数据结构定义
typedef	struct	PAGE_S  
{
	u8 type;															//类型
	u8 touch_en:								1;				//触摸使能
	u8 rvd:											7;
	
	
	u16 start_pos_x;											//开始位置X
	u16 start_pos_y;											//开始位置Y
	u16 end_pos_x;												//结束位置X	
	u16 end_pos_y;												//结束位置Y	

	u8 page_item_num;										//页项数
	PAGE_INEM_T*	p_page_item;						//页项指针
	
		
	void	(*page_init)(void);							//初始化函数
	void 	(*page_fun)(void);							//其它功能函数
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

//页项数据结构定义
typedef	struct	PAGE_ITEM_S  
{
	u8 type;															//类型
	u8 touch_en:								1;				//触摸使能
	u8 rvd:											7;				//保留
	
	u8* p_name;														//名称
	u8 name_len,													//长度(汉字个数)
	u8 name_val;													//值
	
	u16 start_pos_x;											//开始位置X
	u16 start_pos_y;											//开始位置Y
	u16 end_pos_x;												//结束位置X	
	u16 end_pos_y;												//结束位置Y	


	void		(*touch_event)(void);
	void		(*touch_up_event)(void);
}PAGE_ITEM_T;

*/



//智能
//混点
//分版
//清点
const u8 page_item_func_name[8] = 
{
	CM_48X48_ZHI40, CM_48X48_NENG20,
	CM_48X48_HUN30, CM_48X48_DIAN30,
	CM_48X48_FEN10, CM_48X48_BAN30,
	CM_48X48_QING10,CM_48X48_DIAN30	
};

//灵敏度
const u8 page_item_LMD_name[3] = 
{
	CM_16X16_LING20, CM_16X16_MING30,CM_16X16_DU40
};

//低中高
const u8 page_item_DZG_name[12] = 
{
	CM_16X16_SPACE, CM_16X16_SPACE,		CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_DI10,		CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_ZHONG10, CM_16X16_SPACE,
	CM_16X16_SPACE, CM_16X16_GAO10,		CM_16X16_SPACE
};

//预  置
const u8 page_item_YZ_name[3] = 
{
	CM_16X16_YU40, CM_16X16_SPACE,CM_16X16_ZHI40
};

//报警
const u8 page_item_BJ_name[2] = 
{
	CM_16X16_BAO40, CM_16X16_JING30
};


//红外
const u8 page_item_hongwai_name[2] = 
{
	CM_24X24_HONG20_H22, CM_24X24_WAI40_H22
};

//图像
const u8 page_item_tuxiang_name[2] = 
{
	CM_24X24_TU20_H22, CM_24X24_XIANG40_H22
};


//累加
const u8 page_item_leijia_name[2] = 
{
	CM_24X24_LEI30_H22, CM_24X24_JIA10_H22
};


const u16 page_item_color_default[2] = 
{
	RED, WHITE
};




///////////////////////////////////////////////////////////////////////////////////////////////////
//基本工作页面位置END
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
  //功能   
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8* name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		page_item_func_name, CM_TYPE_48X48, 2, &basic_page_data.function, &basic_page_data.function, page_item_color_function,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		FUNC_START_POS_X,	PAGE_BASIC_LINE1_POS_Y,	FUNC_START_POS_X+48*2,PAGE_BASIC_LINE1_POS_Y+48,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_function, NULL
	},
	
	
	  //灵敏度低中高
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8 name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		page_item_DZG_name, CM_TYPE_16X16, 3, &lmd_grade,  &temp_value_zero, page_item_color_default,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		DZG_START_POS_X,	DZG_START_POS_Y,	DZG_START_POS_X+16*3, DZG_START_POS_Y+16,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_LMD, NULL
	},

	  //预置数
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8 name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		NULL, 0, 0, &temp_value_zero, &temp_value_zero, page_item_color_default,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		YZS_START_POS_X,	YZS_START_POS_Y,	YZS_START_POS_X+16*3, YZS_START_POS_Y+16,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_YZS, NULL
	},	
	
  //红外   
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8* name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		page_item_hongwai_name, CM_TYPE_24X24, 2, &temp_value_zero, &temp_value_zero, page_item_color_HONGWAI,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		HW_START_POS_X,	HW_START_POS_Y,	HW_START_POS_X+24*2,HW_START_POS_Y+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	empty_touch_event, NULL
	},	
	
  //图像
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8* name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		page_item_tuxiang_name, CM_TYPE_24X24, 2, &temp_value_zero, &temp_value_zero, page_item_color_HONGWAI,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		HW_START_POS_X,	HW_START_POS_Y+25,	HW_START_POS_X+24*2,HW_START_POS_Y+25+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	empty_touch_event, NULL
	},	

  //累加
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;				//保留
		PAGE_ITEM_TYPE_FUNCTION,	TOUCH_ENABLE,	0,
		
		//const u8* p_name;											//名称
		//u8 CM_type;														//字模类型
		//u8 name_len;													//长度(汉字个数)
		//u8* name_val;													//值
		//u8* color_val;												//颜色索引值
		//const u16* p_color;										//背景色,前景色指针
		page_item_leijia_name, CM_TYPE_24X24, 2, &temp_value_zero, &LJ_on_off, page_item_color_LEIJIA,
		

		//u16 start_pos_x;											//开始位置X
		//u16 start_pos_y;											//开始位置Y
		//u16 end_pos_x;												//结束位置X	
		//u16 end_pos_y;												//结束位置Y	
		HW_START_POS_X,	HW_START_POS_Y+25*2,	HW_START_POS_X+24*2,HW_START_POS_Y+25*2+24,
		
		
		//void		(*touch_event)(void);
		//void		(*touch_up_event)(void);
	 	empty_touch_event,	touch_up_for_LJ, NULL
	},		
		
	
};

const	PAGE_T	page_array[PAGE_ID_MAX] = 
{
  
	//初始化页面
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;
		//u16 init_color;												//初始化底色		
		PAGE_TYPE_UNKNOW,	TOUCH_ENABLE,	0,	BLACK,

		//开始位置X, 开始位置Y, 结束位置X, 结束位置Y
		0,0,400, 240,
		
		//页项数
		1,
		//页项指针
		page_item_basic_array,
		
		//初始化函数
	 	NULL,
		//其它功能函数
		NULL
	},

	//基本工作页面
	{ 
		//u8 type;															//类型
		//u8 touch_en:								1;				//触摸使能
		//u8 rvd:											7;
		//u16 init_color;												//初始化底色		
		PAGE_TYPE_UNKNOW,	TOUCH_ENABLE,	0,	BLACK,

		//开始位置X, 开始位置Y, 结束位置X, 结束位置Y
		0,0,400, 240,
		
		//页项数
		6,
		//页项指针
		page_item_basic_array,
		
		//初始化函数
	 	NULL,
		//其它功能函数
		NULL
	},

	
};
