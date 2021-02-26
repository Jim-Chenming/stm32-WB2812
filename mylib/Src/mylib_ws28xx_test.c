#include "../Inc/mylib_ws28xx_test.h"

void read_RGB_Buffer()
{
	uint8_t rgb[][3]={
	{0xFF,0,0},
	{0,0xFF,0},
	{0,0,0xFF},
	{0,0,0xFF},
	{0,0xFF,0},
	{0xFF,0,0},
	};
	uint8_t r,g,b;
	WS28xx.SetPixelColor_From_RGB_Buffer(0,rgb,6);
	WS28xx.show();
	HAL_Delay(500);
	WS28xx.GetPixelColor_RGB(1,&r,&g,&b);
	WS28xx.SetPixelColor_RGB(3,r,g,b);
	WS28xx.show();
	HAL_Delay(500);
}
void HSV_test()
{
	uint16_t h=0,index=0;
	float v=0,s=0;
	
	WS28xx.SetALLColor_HSV_V(0.4);
	for(h=0;h<360;h+=20)
	{
		WS28xx.SetPixelColor_HSV_H(index++%WS28xx.Pixel_size,h);
		WS28xx.show();
		HAL_Delay(300);
	}
	
	for(s=0.6;s<1;s+=0.05)
	{
		WS28xx.SetALLColor_HSV_S(s);
		WS28xx.show();
		HAL_Delay(200);
	}
	for(v=0;v<1;v+=0.05)
	{
		WS28xx.SetALLColor_HSV_V(v);
		WS28xx.show();
		HAL_Delay(200);
	}
}

void WS2812_test()
{
	read_RGB_Buffer();
	HSV_test();
}
