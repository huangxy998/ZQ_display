 
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
//页项数据结构定义
typedef	struct	PAGE_ITEM_S  
{
	u8 id;	//控件编号
	u8 touch_en;    //触摸使能 1,触控 0 无触控
	
	u16 start_pos_x;//开始位置X
	u16 start_pos_y;//开始位置Y
	u16 width;//宽度	
	u16 height;//高度	
	
	u8 com_data[16];	
	void (*item_event)(void);                                    //项目处理函数
}PAGE_ITEM_T;

typedef	struct	ITEM_IDX_S  
{
	u8 id;	     //控件编号
	u8 itemType; //控件类型
	u8 itemIndx; //在类型中的序号
}ITEM_IDX_T;



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
	u8 need_update;

	u8 toucged_up;                                //触摸屏按下抬起标志
	u8 toucged_down;                              //触摸屏被按下标志(未松开)
	
	u8 page_init_finished;                        //页面初始化完成标志
	u8 page_need_update;                          //页面数据更新标志
	
	const PAGE_T*	p_page[PAGE_ID_NUM];		  //页项指针
}PAGE_INFO_T;


extern volatile PAGE_INFO_T  gPageInfo;



#endif //#ifndef PAGE_DEFINE_H


