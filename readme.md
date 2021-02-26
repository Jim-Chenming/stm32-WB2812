添加测试函数：
void WS2812_test(void);

在头文件根据CubeMX配置修改
/****************************************
*Config
****************************************/
#define BIT_1                   61 			//1比较值为61-->850us
#define BIT_0                   28 			//0比较值为28-->400us

#define PIXEL_SIZE							6
#define WS28xx_PWM_hTIMER				htim3
#define WS28xx_PWM_Chaneel      TIM_CHANNEL_1	




****************************功能API:*******************************

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
void WS28xx.SetPixelColor_HSV_H(unsigned short int pixelIndex,unsigned short int light);
//设置某个位置的HSV饱和度（Saturation）（0.6~~1）													--->>色彩纯净度
void WS28xx.SetPixelColor_HSV_S(unsigned short int pixelIndex,float light);
//设置某个位置的HSV明度（Value）（0.005~~1）																--->>也就是亮度
void WS28xx.SetPixelColor_HSV_V(unsigned short int pixelIndex,float light);

//设置所有HSV色相（1~~360）			       																			--->>也就是颜色(逆时针)
void WS28xx.SetALLColor_HSV_H(unsigned short int setH);
//设置所有HSV饱和度（0.01~~1）																			   			--->>色彩纯净度
void WS28xx.SetALLColor_HSV_S(float setS);
//设置所有明度/亮度（0.01~~1）																							--->>也就是亮度
void WS28xx.SetALLColor_HSV_V(float setV);
//显示（发出数据）
void WS28xx.show(void);

****************************功能API:*******************************
