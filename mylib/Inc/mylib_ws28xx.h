#ifndef MYLIB_WS28XX
#define MYLIB_WS28XX

/****************************************
*Include
****************************************/
#include "tim.h"			//定时器句柄
//如果需要移植,更改这个 __show() 驱动以及对应的数据结构即可

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

#define HSV_H_MAX 				360
#define HSV_H_MIN 				1

#define HSV_S_MAX 				1
#define HSV_S_MIN 				0.6				//0.6保证能显示基本颜色（而不会变白色失真）

#define HSV_V_MAX 				1
#define HSV_V_MIN 				0.005
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
	unsigned short int Pixel_size;
	
	
//单独设置index的RGB颜色
void (*SetPixelColor_RGB)(unsigned short int index,unsigned char r,unsigned char g,unsigned char b);
//从RGB数据读出：设置index的RGB颜色
void (*SetPixelColor_From_RGB_Buffer)( unsigned short int pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short int DataCount);
//设置所有为RGB颜色
void (*SetALLColor_RGB)(unsigned char r,unsigned char g,unsigned char b);
//获取某个位置的RGB
void (*GetPixelColor_RGB)(unsigned short int index,unsigned char *r,unsigned char *g,unsigned char *b);
	

	
// **************************************** HSV空间设置 ****************************************
//单独设置index的HSV颜色																									--->>改变HSV
void (*SetPixelColor_HSV)(unsigned short int index,unsigned short int h,float s,float v);
	
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!以下操作在原来颜色基础上做改变
//设置某个位置的HSV色相（Hue）（1~~360）																		--->>也就是颜色(逆时针)
//SetPixelColor_HSV_H注意该函数，如果一开始
void (*SetPixelColor_HSV_H)(unsigned short int pixelIndex,unsigned short int light);
//设置某个位置的HSV饱和度（Saturation）（0.6~~1）													--->>色彩纯净度
void (*SetPixelColor_HSV_S)(unsigned short int pixelIndex,float light);
//设置某个位置的HSV明度（Value）（0.005~~1）																--->>也就是亮度
void (*SetPixelColor_HSV_V)(unsigned short int pixelIndex,float light);

//设置所有HSV色相（1~~360）			       																			--->>也就是颜色(逆时针)
void (*SetALLColor_HSV_H)(unsigned short int setH);
//设置所有HSV饱和度（0.01~~1）																			   			--->>色彩纯净度
void (*SetALLColor_HSV_S)(float setS);
//设置所有明度/亮度（0.01~~1）																							--->>也就是亮度
void (*SetALLColor_HSV_V)(float setV);
//显示（发出数据）
void (*show)(void);
}WS28xx_TypeStruct;

extern WS28xx_TypeStruct WS28xx;


void	WS28xx_TypeStructInit(void);


/*
*工具函数
*/
#define LIMIT(x,max,min) ((x<max )? ((x>min )? x:min):max)
#define MAX(a,b,c) (a>b?a:b>c?b:c)
#define MIN(a,b,c) (a<b?a:b<c?b:c)
void RGB2HSV(unsigned char r, unsigned char g, unsigned char b, float *h, float *s, float *v);
void HSV2RGB(float h, float s, float v, unsigned char *r, unsigned char *g, unsigned char *b);
#endif
