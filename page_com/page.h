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
#ifndef PAGE_H
#define PAGE_H

#ifndef PAGE_GLOBAL
#define PAGE_EXT				extern
#else
#define PAGE_EXT
#endif

//第一行Y位置
#define PAGE_BASIC_LINE1_POS_Y					3

//第二行Y位置
#define PAGE_BASIC_LINE2_POS_Y					( PAGE_BASIC_LINE1_POS_Y + 16 +5 )
#define PAGE_BASIC_LINE3_POS_Y					( PAGE_BASIC_LINE2_POS_Y + 16 +5 )

//
#define FUNC_START_POS_X								(170)

//灵敏度低中高位置
#define DZG_START_POS_X									(400-16*3 )
#define DZG_START_POS_Y									(PAGE_BASIC_LINE1_POS_Y)

//预置数显示位置
#define YZS_START_POS_X									(DZG_START_POS_X)
#define YZS_START_POS_Y									(PAGE_BASIC_LINE2_POS_Y)

//红外显示位置
#define HW_START_POS_X									(3)
#define HW_START_POS_Y									(71)

//图像显示位置
#define TX_START_POS_X									(HW_START_POS_X)
#define TX_START_POS_Y									(71+25)

//累加显示位置
#define LJ_START_POS_X									(HW_START_POS_X)
#define LJ_START_POS_Y									(71+25*2)


#endif //#ifndef PAGE_H


