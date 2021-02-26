#ifndef MYLIB_WS28XX
#define MYLIB_WS28XX

/****************************************
*Include
****************************************/
#include "tim.h"			//��ʱ�����
//�����Ҫ��ֲ,������� __show() �����Լ���Ӧ�����ݽṹ����

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

#define HSV_H_MAX 				360
#define HSV_H_MIN 				1

#define HSV_S_MAX 				1
#define HSV_S_MIN 				0.6				//0.6��֤����ʾ������ɫ����������ɫʧ�棩

#define HSV_V_MAX 				1
#define HSV_V_MIN 				0.005
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
	unsigned short int Pixel_size;
	
	
//��������index��RGB��ɫ
void (*SetPixelColor_RGB)(unsigned short int index,unsigned char r,unsigned char g,unsigned char b);
//��RGB���ݶ���������index��RGB��ɫ
void (*SetPixelColor_From_RGB_Buffer)( unsigned short int pixelIndex,unsigned char pRGB_Buffer[][3],unsigned short int DataCount);
//��������ΪRGB��ɫ
void (*SetALLColor_RGB)(unsigned char r,unsigned char g,unsigned char b);
//��ȡĳ��λ�õ�RGB
void (*GetPixelColor_RGB)(unsigned short int index,unsigned char *r,unsigned char *g,unsigned char *b);
	

	
// **************************************** HSV�ռ����� ****************************************
//��������index��HSV��ɫ																									--->>�ı�HSV
void (*SetPixelColor_HSV)(unsigned short int index,unsigned short int h,float s,float v);
	
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!���²�����ԭ����ɫ���������ı�
//����ĳ��λ�õ�HSVɫ�ࣨHue����1~~360��																		--->>Ҳ������ɫ(��ʱ��)
//SetPixelColor_HSV_Hע��ú��������һ��ʼ
void (*SetPixelColor_HSV_H)(unsigned short int pixelIndex,unsigned short int light);
//����ĳ��λ�õ�HSV���Ͷȣ�Saturation����0.6~~1��													--->>ɫ�ʴ�����
void (*SetPixelColor_HSV_S)(unsigned short int pixelIndex,float light);
//����ĳ��λ�õ�HSV���ȣ�Value����0.005~~1��																--->>Ҳ��������
void (*SetPixelColor_HSV_V)(unsigned short int pixelIndex,float light);

//��������HSVɫ�ࣨ1~~360��			       																			--->>Ҳ������ɫ(��ʱ��)
void (*SetALLColor_HSV_H)(unsigned short int setH);
//��������HSV���Ͷȣ�0.01~~1��																			   			--->>ɫ�ʴ�����
void (*SetALLColor_HSV_S)(float setS);
//������������/���ȣ�0.01~~1��																							--->>Ҳ��������
void (*SetALLColor_HSV_V)(float setV);
//��ʾ���������ݣ�
void (*show)(void);
}WS28xx_TypeStruct;

extern WS28xx_TypeStruct WS28xx;


void	WS28xx_TypeStructInit(void);


/*
*���ߺ���
*/
#define LIMIT(x,max,min) ((x<max )? ((x>min )? x:min):max)
#define MAX(a,b,c) (a>b?a:b>c?b:c)
#define MIN(a,b,c) (a<b?a:b<c?b:c)
void RGB2HSV(unsigned char r, unsigned char g, unsigned char b, float *h, float *s, float *v);
void HSV2RGB(float h, float s, float v, unsigned char *r, unsigned char *g, unsigned char *b);
#endif
