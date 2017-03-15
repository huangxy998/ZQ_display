/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "sys.h"

/** @defgroup FONTS_Exported_Types
  * @{
  */ 
typedef struct _tFont
{  
	const u16 *list;  
	const u8 *table;
	u8 BytesPerChar;
	u8 TableSize;
	u8 Width;
	u8 wWidth;
	u8 Height;  
} sFONT;


extern sFONT Font40x37;
extern sFONT Font32x29;
extern sFONT Font24x21;
extern sFONT Font24x19;
extern sFONT Font8x16;
extern sFONT Font16x24;
extern sFONT FontNUM;

/**
  * @}
  */ 

