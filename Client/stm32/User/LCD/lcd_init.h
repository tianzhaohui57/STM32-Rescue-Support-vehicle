#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 3  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_RES_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_1)//RES
#define LCD_RES_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_1)

#define LCD_DC_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_2)//DC
#define LCD_DC_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_2)
 		     
#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_3)//CS
#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_3)

#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)//BLK
#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




