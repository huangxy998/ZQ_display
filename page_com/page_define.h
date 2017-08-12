 
#ifndef PAGE_DEFINE_H
#define PAGE_DEFINE_H

#ifndef PAGE_DEFINE_GLOBAL
#define PAGE_DEFINE_EXT				extern
#else
#define PAGE_DEFINE_EXT
#endif

enum
{
//	PAGE_ID_INIT,
	PAGE_ID_BASIC,
	PAGE_ID_MENU,
	PAGE_ID_VERSION,
	PAGE_ID_MAX
};

enum
{
	PAGE_ID_START,
	PAGE_ID_STANDTIME,
	PAGE_ID_SYSVERSION,
	PAGE_ID_MAIN,
	PAGE_ID_BLACKLIST,
	PAGE_ID_BLACKKEY,
	PAGE_ID_CISCHEK,
	PAGE_ID_CISSET1,
	PAGE_ID_SYSUPDATA,
	PAGE_ID_ZBUPDATA,
	PAGE_ID_NETSET,
	PAGE_ID_GZHMDIS,
	PAGE_ID_SYSEMSET,
	PAGE_ID_SENSORCHECK,
	PAGE_ID_GEARSET1,
	PAGE_ID_GEARSET2,
	PAGE_ID_DISPLIGHT,
	PAGE_ID_CLOCKDISP,
	PAGE_ID_CLOCKSET,
	PAGE_ID_SPEAK,
	PAGE_ID_INPUT,
	PAGE_ID_OUTPUT,
	PAGE_ID_CONFIRM,
	PAGE_ID_CONFIRM1,
	PAGE_ID_ERRER,

	PAGE_ID_NUM	
};

typedef enum
{
	PAGE_ITEM_TYPE_ZK,       //��ʾ������ʾ�ֿ��е��ַ�
	PAGE_ITEM_TYPE_NORMAL,   //��ʾ������ʾ�����ж�����ַ�
	PAGE_ITEM_TYPE_BMP,      //��ʾ������ʾbmpͼƬ
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

//ҳ�����ݽṹ����
//ҳ�����ݽṹ����
typedef	struct	PAGE_ITEM_S  
{
	u8 id;	//�ؼ����
	u8 touch_en;    //����ʹ�� 1,���� 0 �޴���
	
	u16 start_pos_x;//��ʼλ��X
	u16 start_pos_y;//��ʼλ��Y
	u16 width;//���	
	u16 height;//�߶�	
	
	u8 com_data[16];	
	void (*item_event)(void);                                    //��Ŀ������
}PAGE_ITEM_T;

typedef	struct	ITEM_IDX_S  
{
	u8 id;	     //�ؼ����
	u8 itemType; //�ؼ�����
	u8 itemIndx; //�������е����
}ITEM_IDX_T;



//ҳ�����ݽṹ����
typedef	struct	PAGE_S  
{
	u8  page_idx;												//ҳ�����
		
	u16 start_pos_x;											//��ʼλ��X
	u16 start_pos_y;											//��ʼλ��Y
	u16 width;												    //���
	u16 height;												    //�߶�	

	u8 page_item_num;											//ҳ����
			
	void	(*page_init)(void);							        //��ʼ������
	void 	(*page_update)(void);							    //��ʾ���º���
}PAGE_T;

//ҳ�����ݽṹ����
typedef	struct
{
	u8 cur_page_idx;															//��ǰҳ�����
	u8 pre_page_idx;                              //������һ��ҳ�����
	u8 total_pages;								  //ҳ����
	u8 need_update;

	u8 toucged_up;                                //����������̧���־
	u8 toucged_down;                              //�����������±�־(δ�ɿ�)
	
	u8 page_init_finished;                        //ҳ���ʼ����ɱ�־
	u8 page_need_update;                          //ҳ�����ݸ��±�־
	
	const PAGE_T*	p_page[PAGE_ID_NUM];		  //ҳ��ָ��
}PAGE_INFO_T;


extern volatile PAGE_INFO_T  gPageInfo;



#endif //#ifndef PAGE_DEFINE_H


