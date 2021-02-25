#ifndef MYLIB_WS28XX
#define MYLIB_WS28XX

/****************************************
*Include
****************************************/
#include "tim.h"			//定时器句柄
//如果需要移植官方库函数，更改这个 __show() 驱动即可

/****************************************
*Config
****************************************/
#define BIT_1                   61 			//1比较值为61-->850us
#define BIT_0                   28 			//0比较值为28-->400us

#define PIXEL_SIZE							6
#define WS28xx_PWM_hTIMER				htim3
#define WS28xx_PWM_Chaneel      TIM_CHANNEL_1		


/****************************************
*数据结构
****************************************/

//整个WS28xx_DataTypeStruct结构体将被以PWM方式发送
typedef struct
{
						//3个0等待PWM稳定
	unsigned char ColorStartData[3];
						//实际GRB数据(已经转换为PWM对应的值)
	unsigned char ColorRealData[24*PIXEL_SIZE*8];
						//结束位为0
	unsigned char ColorEndData;
}WS28xx_DataTypeStruct;

/****************************************
*对象化编程
****************************************/
typedef struct 
{
	//实际发送的数据
	WS28xx_DataTypeStruct WS28xx_Data;
	//灯数量
	unsigned short Pixel_size;
	
	
//单独设置index的RGB颜色
void (*SetPixelColor_RGB)(unsigned short index,unsigned char r,unsigned char g,unsigned char b);
//从RGB数据读出：设置index的RGB颜色
void (*SetPixelColor_From_RGB_Buffer)( unsigned short pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short DataCount);
//设置所有为RGB颜色
void (*SetALLColor_RGB)(unsigned short index,unsigned char r,unsigned char g,unsigned char b);
//获取某个位置的RGB
void (*GetPixelColor_RGB)(unsigned short index,unsigned char *r,unsigned char *g,unsigned char *b);
//设置某个位置的RGB亮度（0.005~~1）
void (*SetPixelColor_Light)(unsigned short pixelIndex,float light);
//设置所有RGB亮度（0.01~~1）
void (*SetALLColor_Light)(float light);
//显示（发出数据）
void (*show)(void);
}WS28xx_TypeStruct;

extern WS28xx_TypeStruct WS28xx;


void	WS28xx_TypeStructInit(void);
#endif
