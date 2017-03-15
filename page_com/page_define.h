/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        timer.h
 * Dependencies:    
 * Processor:
 * Compiler:
 * Linker:  
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * This is a simple timer function used to provide quant for state mashines
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			04/28/03	...	
 * 
 *****************************************************************************/
#ifndef PAGE_DEFINE_H
#define PAGE_DEFINE_H

#ifndef PAGE_DEFINE_GLOBAL
#define PAGE_DEFINE_EXT				extern
#else
#define PAGE_DEFINE_EXT
#endif

enum
{
	PAGE_ID_INIT,
	PAGE_ID_BASIC,
	PAGE_ID_MENU,
	PAGE_ID_MAX
};

typedef enum
{
	PAGE_ITEM_TYPE_ZK,       //显示区域显示字库中的字符
	PAGE_ITEM_TYPE_NORMAL,   //显示区域显示代码中定义的字符
	PAGE_ITEM_TYPE_BMP,      //显示区域显示bmp图片
}_DISP_TYPE;

enum
{
	PAGE_ITEM_TYPE_UNKNOW,
	PAGE_ITEM_TYPE_FUNCTION,
	PAGE_ITEM_TYPE_TOUCH_AREA
};

enum
{
	PAGE_TYPE_UNKNOW
};

enum
{
	TOUCH_DISABLE,
	TOUCH_ENABLE
	
};

//页项数据结构定义
typedef	struct	PAGE_ITEM_S  
{
	u8 type;													//类型
	u8 touch_en;                                 				//触摸使能
	
	u16 start_pos_x;											//开始位置X
	u16 start_pos_y;											//开始位置Y
	u16 width;												    //宽度	
	u16 height;												    //高度	

	u8	(*item_event)(void);                                    //项目处理函数
}PAGE_ITEM_T;

//页面数据结构定义
typedef	struct	PAGE_S  
{
	u8  page_idx;												//页面序号
		
	u16 start_pos_x;											//开始位置X
	u16 start_pos_y;											//开始位置Y
	u16 width;												    //宽度
	u16 height;												    //高度	

	u8 page_item_num;											//页项数
			
	void	(*page_init)(void);							        //初始化函数
	void 	(*page_update)(void);							    //显示更新函数
}PAGE_T;

//页面数据结构定义
typedef	struct
{
	u8 cur_page_idx;															//当前页面序号
	u8 pre_page_idx;                              //保存上一次页面序号
	u8 total_pages;								  //页项数

	u8 toucged_up;                                //触摸屏按下抬起标志
	u8 toucged_down;                              //触摸屏被按下标志(未松开)
	
	u8 page_init_finished;                        //页面初始化完成标志
	u8 page_need_update;                          //页面数据更新标志
	
	const PAGE_T*	p_page[PAGE_ID_MAX];		  //页项指针
}PAGE_INFO_T;


extern PAGE_INFO_T  gPageInfo;



#endif //#ifndef PAGE_DEFINE_H


