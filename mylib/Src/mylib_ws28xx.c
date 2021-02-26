#include "../Inc/mylib_ws28xx.h"

WS28xx_TypeStruct WS28xx;
//如果需要移植官方库函数，更改这个 __show() 驱动即可
void __show()
{
	HAL_TIM_PWM_Start_DMA(&WS28xx_PWM_hTIMER,WS28xx_PWM_Chaneel,(uint32_t *)(&WS28xx.WS28xx_Data),sizeof(WS28xx.WS28xx_Data));
}

		
//设置index的颜色
void __SetPixelColor_RGB(unsigned short int index,unsigned char r,unsigned char g,unsigned char b)
{
	unsigned char j;
	if(index > WS28xx.Pixel_size)
		return;
	for(j = 0; j < 8; j++)
	{
		//G
		WS28xx.WS28xx_Data.ColorRealData [24 * index + j]     = (g & (0x80 >> j)) ? BIT_1 : BIT_0; //将高位先发
		//R
		WS28xx.WS28xx_Data.ColorRealData [24 * index + j + 8]     = (r & (0x80 >> j)) ? BIT_1 : BIT_0; //将高位先发
		//B
		WS28xx.WS28xx_Data.ColorRealData [24 * index + j + 16]     = (b & (0x80 >> j)) ? BIT_1 : BIT_0; //将高位先发
	}
}
//获取某个位置的RGB
void __GetPixelColor_RGB(unsigned short int index,unsigned char *r,unsigned char *g,unsigned char *b)
{
	unsigned char j;
	*r=0;
	*g=0;
	*b=0;
	if(index > WS28xx.Pixel_size)
		return;
	for(j = 0; j <8; j++)
	{
		//G
		(*g)|=((WS28xx.WS28xx_Data.ColorRealData [24 * index + j] >=BIT_1)?  0x80>>j:0);
		//R
		(*r)|=((WS28xx.WS28xx_Data.ColorRealData [24 * index + j + 8] >=BIT_1)? 0x80>>j:0);
		//B
		(*b)|=((WS28xx.WS28xx_Data.ColorRealData [24 * index + j + 16] >=BIT_1)? 0x80>>j:0);
	}
}
//读取RGB缓存数据，并且设置颜色例如下面数据
/*unsigned char RGB[x][3]={
{r1,g1,b2},
{r1,g1,b2},
{r1,g1,b2}};
*/
void __SetPixelColor_From_RGB_Buffer( unsigned short int pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short int DataCount)
{
	unsigned short int Index,j=0;
	for(Index=pixelIndex;Index < WS28xx.Pixel_size; Index++)
	{
			WS28xx.SetPixelColor_RGB(Index,pRGB_Buffer[j][0],pRGB_Buffer[j][1],pRGB_Buffer[j][2]);
			j++;
			if(j>DataCount)
				return;
	}
}

//设置所有颜色
void __SetALLColor_RGB(unsigned char r,unsigned char g,unsigned char b)
{
	unsigned short int Index;
	for(Index=0;Index < WS28xx.Pixel_size; Index++)
	{
		WS28xx.SetPixelColor_RGB(Index,r,g,b);
	}
}

void RGB2HSV(unsigned char r, unsigned char g, unsigned char b, float *h, float *s, float *v)
{
  float red, green ,blue;
  float cmax, cmin, delta;
  
  red = (float)r / 255;
  green = (float)g / 255;
  blue = (float)b / 255;
  
  cmax = MAX(red, green, blue);
  cmin = MIN(red, green, blue);
  delta = cmax - cmin;

  /* H */
  if(delta != 0)
  {
    if(cmax == red)
    {
			*h= green >= blue ? 60 * ((green - blue) / delta): 60 * ((green - blue) / delta) + 360;
    }
    else if(cmax == green)
    {
      *h = 60 * ((blue - red) / delta + 2);
    }
    else if(cmax == blue) 
    {
      *h = 60 * ((red - green) / delta + 4);
    }
  }else
  {
    *h = 0;
  }
  /* S */
	*s=cmax?delta / cmax:0;
  /* V */
  *v = cmax;
}
  
void HSV2RGB(float h, float s, float v, unsigned char *r, unsigned char *g, unsigned char *b)
{
    int hi = ((int)h / 60) % 6;
    float f = h * 1.0 / 60 - hi;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1- (1 - f) * s);
    switch (hi){
        case 0:
            *r = 255 * v;
            *g = 255 * t;
            *b = 255 * p;
            break;
        case 1:
            *r = 255 * q;
            *g = 255 * v;
            *b = 255 * p;
            break;
        case 2:
            *r = 255 * p;
            *g = 255 * v;
            *b = 255 * t;
            break;
        case 3:
            *r = 255 * p;
            *g = 255 * q;
            *b = 255 * v;
            break;
        case 4:
            *r = 255 * t;
            *g = 255 * p;
            *b = 255 * v;
            break;
        case 5:
            *r = 255 * v;
            *g = 255 * p;
            *b = 255 * q;
            break;
    }
}
//单独设置index的RGB颜色
void __SetPixelColor_HSV(unsigned short int pixelIndex,unsigned short int h,float s,float v)
{
	unsigned char r,g,b;
	h = LIMIT(h,HSV_H_MAX,HSV_H_MIN);
	s = LIMIT(s,HSV_S_MAX,HSV_S_MIN);
	v = LIMIT(v,HSV_V_MAX,HSV_V_MIN);
	HSV2RGB(h, s, v, &r, &g, &b);
	WS28xx.SetPixelColor_RGB(pixelIndex,r,g,b);
}
void __SetPixelColor_HSV_H(unsigned short int pixelIndex,unsigned short int setH)
{
	unsigned char r,g,b;
	float h,s,v;
	WS28xx.GetPixelColor_RGB(pixelIndex,&r,&g,&b);
	RGB2HSV(r,g,b, &h, &s, &v);
	h = LIMIT(setH,HSV_H_MAX,HSV_H_MIN);
	s = LIMIT(s,HSV_S_MAX,HSV_S_MIN);
	v = LIMIT(v,HSV_V_MAX,HSV_V_MIN);
	HSV2RGB(h, s, v, &r, &g, &b);
	WS28xx.SetPixelColor_RGB(pixelIndex,r,g,b);
}


void __SetPixelColor_HSV_S(unsigned short int pixelIndex,float setS)
{
	unsigned char r,g,b;
	float h,s,v;
	WS28xx.GetPixelColor_RGB(pixelIndex,&r,&g,&b);
	RGB2HSV(r,g,b, &h, &s, &v);
	h = LIMIT(h,HSV_H_MAX,HSV_H_MIN);
	s = LIMIT(setS,HSV_S_MAX,HSV_S_MIN);
	v = LIMIT(v,HSV_V_MAX,HSV_V_MIN);
	HSV2RGB(h, s, v, &r, &g, &b);
	WS28xx.SetPixelColor_RGB(pixelIndex,r,g,b);
}
void __SetPixelColor_HSV_V(unsigned short int pixelIndex,float setV)
{
	unsigned char r,g,b;
	float h,s,v;
	WS28xx.GetPixelColor_RGB(pixelIndex,&r,&g,&b);
	RGB2HSV(r,g,b, &h, &s, &v);
	h = LIMIT(h,HSV_H_MAX,HSV_H_MIN);
	s = LIMIT(s,HSV_S_MAX,HSV_S_MIN);
	v = LIMIT(setV,HSV_V_MAX,HSV_V_MIN);
	HSV2RGB(h, s, v, &r, &g, &b);
	WS28xx.SetPixelColor_RGB(pixelIndex,r,g,b);
}


void __SetALLColor_HSV_H(unsigned short int setH)
{
	unsigned short int Index;
	for(Index=0;Index < WS28xx.Pixel_size; Index++)
	{
		WS28xx.SetPixelColor_HSV_H(Index,setH);
	}
}
void __SetALLColor_HSV_S(float setS)
{
	unsigned short int Index;
	for(Index=0;Index < WS28xx.Pixel_size; Index++)
	{
		WS28xx.SetPixelColor_HSV_S(Index,setS);
	}
}
void __SetALLColor_HSV_V(float setV)
{
	unsigned short int Index;
	for(Index=0;Index < WS28xx.Pixel_size; Index++)
	{
		WS28xx.SetPixelColor_HSV_V(Index,setV);
	}
}

void	WS28xx_TypeStructInit()
{
	WS28xx.Pixel_size=PIXEL_SIZE;
	WS28xx.GetPixelColor_RGB=__GetPixelColor_RGB;
	WS28xx.SetPixelColor_From_RGB_Buffer=__SetPixelColor_From_RGB_Buffer;
	WS28xx.SetPixelColor_RGB=__SetPixelColor_RGB;
	WS28xx.SetALLColor_RGB=__SetALLColor_RGB;
	//HSV空间设置
	WS28xx.SetPixelColor_HSV=__SetPixelColor_HSV;
	WS28xx.SetPixelColor_HSV_H=__SetPixelColor_HSV_H;
	WS28xx.SetPixelColor_HSV_S=__SetPixelColor_HSV_S;
	WS28xx.SetPixelColor_HSV_V=__SetPixelColor_HSV_V;
	WS28xx.SetALLColor_HSV_H=__SetALLColor_HSV_H;
	WS28xx.SetALLColor_HSV_S=__SetALLColor_HSV_S;
	WS28xx.SetALLColor_HSV_V=__SetALLColor_HSV_V;
	WS28xx.show=__show;
}
