#ifndef PAGE_H
#define PAGE_H

#ifndef PAGE_GLOBAL
#define PAGE_EXT				extern
#else
#define PAGE_EXT
#endif

//��һ��Yλ��
#define PAGE_BASIC_LINE1_POS_Y					3

//�ڶ���Yλ��
#define PAGE_BASIC_LINE2_POS_Y					( PAGE_BASIC_LINE1_POS_Y + 16 +5 )
#define PAGE_BASIC_LINE3_POS_Y					( PAGE_BASIC_LINE2_POS_Y + 16 +5 )

//
#define FUNC_START_POS_X								(170)

//�����ȵ��и�λ��
#define DZG_START_POS_X									(400-16*3 )
#define DZG_START_POS_Y									(PAGE_BASIC_LINE1_POS_Y)

//Ԥ������ʾλ��
#define YZS_START_POS_X									(DZG_START_POS_X)
#define YZS_START_POS_Y									(PAGE_BASIC_LINE2_POS_Y)

//������ʾλ��
#define HW_START_POS_X									(3)
#define HW_START_POS_Y									(71)

//ͼ����ʾλ��
#define TX_START_POS_X									(HW_START_POS_X)
#define TX_START_POS_Y									(71+25)

//�ۼ���ʾλ��
#define LJ_START_POS_X									(HW_START_POS_X)
#define LJ_START_POS_Y									(71+25*2)

typedef struct 
{
	u8  mode;
	u8  sensity;
	u8  pre_set;
	u8  add_flg;
	u8  net_flg;
	u8  sd_flg;
	u8  serial[12];
	
	u16 cur_cnt;
	u16 total_cnt;
	u16 sum;
	
	u8  hundred_cnt;
	u8  fifty_cnt;
	u8  twenty_cnt;
	u8  ten_cnt;
	u8  five_cnt;
	u8  error_cnt;
}PAGE_MAIN_PARA_T;
extern PAGE_MAIN_PARA_T gPageMainPara;

#endif //#ifndef PAGE_H


