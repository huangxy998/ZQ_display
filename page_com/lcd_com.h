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
#ifndef LCD_COM_H
#define LCD_COM_H

#ifndef LCD_COM_GLOBAL
#define LCD_COM_EXT				extern
#else
#define LCD_COM_EXT
#endif

#define TOUCH_CMD_LEN      7

typedef struct
{
	u8 t_string[44][50];
	u8 t_bco[44][8];
	u8 n_val[32][10];
	u8 g_string[2][50];
	u8 j_percent[2][4];
	u8 x_str[4][50];
	u8 f_str[2][30];
	u8 b_str[28][10];
	u8 b_bc[28][10];
}page_para;

typedef struct
{
	unsigned char start;
	unsigned char pageID;
	unsigned char btnID;
	unsigned char touchStatus;
	unsigned char cmdEnd[3];
}CMD_PAGE_ID;

typedef struct
{
	unsigned char  cmdUpdate;
	CMD_PAGE_ID    cmdPage;
}CMD_PAGE_ID_INFO;

typedef struct
{
	u8 u_diskstate;
	u8 sd_state;
	u8 net_state;
}PARA_DEVICE_STATE;


extern CMD_PAGE_ID_INFO  gIDInfo;

extern page_para gPagePara;
extern void uart_buff_cmd_parse(void);


#endif //#ifndef LCD_COM_H


