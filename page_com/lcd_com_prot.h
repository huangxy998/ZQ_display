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
#ifndef LCD_COM_PROT_H
#define LCD_COM_PROT_H

#ifndef LCD_COM_PROT_GLOBAL
#define LCD_COM_PROT_EXT				extern
#else
#define LCD_COM_PROT_EXT
#endif



//#include "p24hxxxx.h"

#include "lcd_com_prot.h"

//包类型
typedef enum
{
	LC_PACKET_ZERO,
	LC_PACKET_CMD,
	LC_PACKET_PAGE,
	LC_PACKET_PARA_PAGE,
	LC_PACKET_DATA_BLOCK,
}LC_PACKET_T;

//命令包子类型
typedef enum
{
	CMD_ZERO,
	CMD_CONNECT,
	CMD_GET_KEY_VAL,
	CMD_TX_GZHM,
	CMD_TX_GZHM_REANALYSE,
	CMD_GET_LCD_STATE,
	CMD_DSP_ISP_STATE_TX,
	CMD_FILE_SIZE_READ,
	CMD_FILE_SIZE_WRITE,
	CMD_DATA_BLOCK_TX_FINISHED,
	CMD_MAIN_STATE_TX,
	CMD_VERSION_TX,
	CMD_GZHMJT_TX,
	CMD_CONTINUE,
	CMD_WB_BZ,
	CMD_GET_SET_PARAM,

	CMD_SUB_TYPE_NUM,

}LC_PACKET_CMD_T;


typedef enum
{
	PAGE_ZERO,
	PAGE_INIT,
	PAGE_BASIC,
	PAGE_CIS_DW,
	PAGE_DW_MM,
	PAGE_CIS_PAGE_PARAM1,
	PAGE_CIS_PAGE_PARAM2,
	PAGE_CIS_PAGE_PARAM3,
	PAGE_CIS_SOURSE_TEST,
	PAGE_SENSOR1_DATA,					//传感器校准显示页面
	PAGE_DW1_DATA,						//基本档位显示页面
	PAGE_CIS_AUTO_ADJUST,				//CIS自动校准首页
	PAGE_CIS_DW_AUTO_ADJUST,

}LC_PACKET_PAGE_T;


///////////////////////////////////////////////////////////////////////////////////////////////////
//页面数据包
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct BASIC_PAGE_DATA_S
{
	unsigned int curr_batch_cnt;				//当前把计数
	unsigned int last_batch_cnt;				//上把计数
	unsigned char  note_val;							//面值
	unsigned char  note_err;							//
	unsigned int preset_cnt;						//
	unsigned long ljje;									//累加金额
	unsigned long lj_cnt;								//累加计数
	unsigned char function;								//功能
	
	unsigned char lj_status:	3;					//累加状态
	unsigned char preset_status:1;				//预置状态
	unsigned char dime:			1;						
	unsigned char fl_status:	1;						
	unsigned char over_speed:	1;
	unsigned char study:		1;

	unsigned char lmd_grade:	3;					//灵敏度等级
	unsigned char lmd_tz:		1;
	unsigned char xckg_opened:	1;
	unsigned char tiao_can:		1;
	unsigned char rev_b:		2;
	
	
	
}BASIC_PAGE_DATA_T;

///////////////////////////////////////////////////////////////////////////////////////////////////
//页面数据包END
///////////////////////////////////////////////////////////////////////////////////////////////////


#endif //#ifndef LCD_COM_PROT_H


