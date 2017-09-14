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
#ifndef CHAR_MODEL_H
#define CHAR_MODEL_H

#ifndef CHAR_MODEL_GLOBAL
#define CHAR_MODEL_EXT				extern
#else
#define CHAR_MODEL_EXT
#endif


enum
{
	CM_TYPE_16X16,
	CM_TYPE_24X24,
	CM_TYPE_32X32,
	CM_TYPE_48X48,
	
};

enum
{
	CM_16X16_BAO40,//"��"
	CM_16X16_DI10,//"��"
	CM_16X16_DU40,//"��",
	CM_16X16_GAO10,//��"
	CM_16X16_JING30,//"��"
	CM_16X16_LING20,//"��"
	CM_16X16_MING30,//"��"
	CM_16X16_SPACE,//" "
	CM_16X16_YU40,//"Ԥ"
	CM_16X16_ZHI40,//"��"
	CM_16X16_ZHONG10,//"��"

	
};


enum
{
	CM_24X24_HONG20_H22,//"��"
	CM_24X24_JIA10_H22,//"��"
	CM_24X24_LEI30_H22,//"��"
	CM_24X24_TU20_H22,//"ͼ"
	CM_24X24_XIANG40_H22,//"��"
	CM_24X24_WAI40_H22,//��"
};

enum
{
	CM_32X32_BAN30,//"��",
	CM_32X32_DIAN30,//"��"
	CM_32X32_FEN10,//"��"
	CM_32X32_HUN30,//"��
	CM_32X32_NENG20,//"��"
	CM_32X32_QING10,//"��"
	CM_32X32_ZHI40,//"��"
	
};

enum
{
	CM_48X48_BAN30,//"��",
	CM_48X48_DIAN30,//"��"
	CM_48X48_FEN10,//"��"
	CM_48X48_HUN30,//"��
	CM_48X48_NENG20,//"��"
	CM_48X48_QING10,//"��"
	CM_48X48_ZHI40,//"��"
	CM_48X48_JI10, //"��"
	CM_48X48_SHU30, //"��"
};

extern const  u8 CM_16X16[][32];
extern const  u8 CM_24X24[][72];
extern const  u8 CM_32X32[][128];
extern const  u8 CM_48X48[][288];


#endif //#ifndef CHAR_MODEL_H


