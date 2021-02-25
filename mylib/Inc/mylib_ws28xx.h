#ifndef MYLIB_WS28XX
#define MYLIB_WS28XX

/****************************************
*Include
****************************************/
#include "tim.h"			//��ʱ�����
//�����Ҫ��ֲ�ٷ��⺯����������� __show() ��������

/****************************************
*Config
****************************************/
#define BIT_1                   61 			//1�Ƚ�ֵΪ61-->850us
#define BIT_0                   28 			//0�Ƚ�ֵΪ28-->400us

#define PIXEL_SIZE							6
#define WS28xx_PWM_hTIMER				htim3
#define WS28xx_PWM_Chaneel      TIM_CHANNEL_1		


/****************************************
*���ݽṹ
****************************************/

//����WS28xx_DataTypeStruct�ṹ�彫����PWM��ʽ����
typedef struct
{
						//3��0�ȴ�PWM�ȶ�
	unsigned char ColorStartData[3];
						//ʵ��GRB����(�Ѿ�ת��ΪPWM��Ӧ��ֵ)
	unsigned char ColorRealData[24*PIXEL_SIZE*8];
						//����λΪ0
	unsigned char ColorEndData;
}WS28xx_DataTypeStruct;

/****************************************
*���󻯱��
****************************************/
typedef struct 
{
	//ʵ�ʷ��͵�����
	WS28xx_DataTypeStruct WS28xx_Data;
	//������
	unsigned short Pixel_size;
	
	
//��������index��RGB��ɫ
void (*SetPixelColor_RGB)(unsigned short index,unsigned char r,unsigned char g,unsigned char b);
//��RGB���ݶ���������index��RGB��ɫ
void (*SetPixelColor_From_RGB_Buffer)( unsigned short pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short DataCount);
//��������ΪRGB��ɫ
void (*SetALLColor_RGB)(unsigned short index,unsigned char r,unsigned char g,unsigned char b);
//��ȡĳ��λ�õ�RGB
void (*GetPixelColor_RGB)(unsigned short index,unsigned char *r,unsigned char *g,unsigned char *b);
//����ĳ��λ�õ�RGB���ȣ�0.005~~1��
void (*SetPixelColor_Light)(unsigned short pixelIndex,float light);
//��������RGB���ȣ�0.01~~1��
void (*SetALLColor_Light)(float light);
//��ʾ���������ݣ�
void (*show)(void);
}WS28xx_TypeStruct;

extern WS28xx_TypeStruct WS28xx;


void	WS28xx_TypeStructInit(void);
#endif
