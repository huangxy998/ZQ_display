#ifndef PAGE_KEYBOARD_H
#define PAGE_KEYBOARD_H

#include "sys.h"

typedef struct
{
	u8 strUpdate;
	u8 buffLen;
	u8 buff[32];
}KEYBOARD_INFO;

extern const PAGE_T  page_KeyBoard;
extern KEYBOARD_INFO keyBoardInfo;

#endif

