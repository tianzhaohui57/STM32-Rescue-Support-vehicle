#ifndef _fatfs_sd_h
#define _fatfs_sd_h
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "delay.h"
#include "sys.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "ff.h"
#include "stm32_eval_sdio_sd.h"


#define M1NO1 GPIO_SetBits(GPIOD,GPIO_Pin_9);GPIO_ResetBits(GPIOD,GPIO_Pin_8);
#define M2NO1 GPIO_SetBits(GPIOD,GPIO_Pin_11);GPIO_ResetBits(GPIOD,GPIO_Pin_10);
#define M3NO1 GPIO_SetBits(GPIOD,GPIO_Pin_13);GPIO_ResetBits(GPIOD,GPIO_Pin_12);
#define M4NO1 GPIO_SetBits(GPIOD,GPIO_Pin_15);GPIO_ResetBits(GPIOD,GPIO_Pin_14);

#define M1NO2 GPIO_SetBits(GPIOD,GPIO_Pin_8);GPIO_ResetBits(GPIOD,GPIO_Pin_9);
#define M2NO2 GPIO_SetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOD,GPIO_Pin_11);
#define M3NO2 GPIO_SetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOD,GPIO_Pin_13);
#define M4NO2 GPIO_SetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_15);

#define M1OFF GPIO_ResetBits(GPIOD,GPIO_Pin_8);GPIO_ResetBits(GPIOD,GPIO_Pin_9);
#define M2OFF GPIO_ResetBits(GPIOD,GPIO_Pin_10);GPIO_ResetBits(GPIOD,GPIO_Pin_11);
#define M3OFF GPIO_ResetBits(GPIOD,GPIO_Pin_12);GPIO_ResetBits(GPIOD,GPIO_Pin_13);
#define M4OFF GPIO_ResetBits(GPIOD,GPIO_Pin_14);GPIO_ResetBits(GPIOD,GPIO_Pin_15);

#define M1CMDON GPIO_SetBits(GPIOB,GPIO_Pin_12);
#define M2CMDON GPIO_SetBits(GPIOB,GPIO_Pin_13);
#define M3CMDON GPIO_SetBits(GPIOB,GPIO_Pin_14);
#define M4CMDON GPIO_SetBits(GPIOB,GPIO_Pin_15);

#define M1CMDOFF GPIO_ResetBits(GPIOB,GPIO_Pin_12);
#define M2CMDOFF GPIO_ResetBits(GPIOB,GPIO_Pin_13);
#define M3CMDOFF GPIO_ResetBits(GPIOB,GPIO_Pin_14);
#define M4CMDOFF GPIO_ResetBits(GPIOB,GPIO_Pin_15);



#define BUFFER_SIZE  128
#define MAX_WAIT_CYCLES 10000
#define STM_SD_LOG 1
#define STM_LCD 1

typedef enum{
    ESP_OK=0,
    ESP_WIFI_OK,
    ESP_Error,
    ESP_TCPv6Error,
    ESP_CIPMUXError,
    ESP_Connect,
    ESP_No_Connection,
    ESP_DISK_ERR,
    ESP_ReceiveError,
    ESP_Noreply,
    ESP_IPV6Error,
    ESP_IPV6_OK,
    ESP_empty,
    ESP_Not,
    ESP_RES_OK
}ESP;

typedef enum{
    TIM_PWM_M=0,
    TIM4_PWM_M,
    TIM5_PWM_M,
    TIM6_PWM_M,
    TIM7_PWM_M
}TIM4567_PWM;

typedef struct
{
    unsigned int ID;
    unsigned int Data;
    int M1;
    int M2;
    int M3;
    int M4;
}M_ADC_t;

typedef struct
{
    unsigned int ID;
    unsigned int Data;
    char SSID[32];
    char password[32];
    char types[5];
    char ip[128];
    char port[5];
}WIFI_TCP_t;

typedef enum
{
    M=0,
    M1,
    M2,
    M3,
    M4
}M_ID;

int PWM_ADC1,PWM_ADC2,PWM_ADC3,PWM_ADC4,TIME1,TIME2,TIME3,TIME4;

FATFS fs;
FIL fnew;
FRESULT res_flash;
UINT fnum=0;
DWORD Number_clusters;
FATFS *qu;
DIR dir;
FRESULT res;
FILINFO fno;

u16 tx_Number=0;
uint8_t tx_buffer[BUFFER_SIZE];
uint8_t Read_data[BUFFER_SIZE];
ESP state=ESP_Not;


FRESULT Mount_device(const TCHAR *equipment);
void STM_LCD_init(void);
void STM_LOG(const char* __restrict,const char* __restrict,const char* __restrict,...)__attribute__((__nonnull__(1,2,3)));
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx,const char *str);
static void NVIC_Configuration(void);
static void USART_Initialization(void);
void TIM_PWM_Initialization(TIM4567_PWM TIMx);
static void GPIO_Initialization(void);
ESP ESP_AT(unsigned int tame, const char* AT);
void ESP_ERROR_LOG(ESP ERROR_LOG);
static void ESP_Default(void);
void controlMotor(M_ID motorNumber, int adcValue);
void WIFI_Connection(WIFI_TCP_t WIFITCP);




// 一些常用AT指令的定义
const char AT_AT[]="AT\r\n";
const char AT_ATE[]="ATE0\r\n";
const char AT_RST[]="AT+RESTORE\r\n";
const char AT_SYSSTORE[]="AT+SYSSTORE=0\r\n";
const char AT_CWMODE[]="AT+CWMODE=3\r\n";
const char AT_CWSAP[]="AT+CWSAP=\"ESP_TZH_S\",\"070330XYX\",5,3,3\r\n";
const char AT_CWDHCP[]="AT+CWDHCP=0,2\r\n";
const char AT_CIPAP[]="AT+CIPAP=\"192.168.2.1\"\r\n";
const char AT_CIPMUX[]="AT+CIPMUX=1\r\n";
const char AT_CIPSERVER[]="AT+CIPSERVER=1,3050\r\n";
const char AT_CIPSERVER_IPV6[]="AT+CIPSERVER=1,3050,\"TCPv6\"\r\n";
const char AT_CIPSTATE[]="AT+CIPSTATE?\r\n";
const char AT_CIPV6[]="AT+CIPV6=1\r\n";
const char AT_CIPSTA[]="AT+CIPSTA?\r\n";
const char AT_CIPSERVER_OFF[]="AT+CIPSERVER=0,1\r\n";
const char AT_CWJAP[]="AT+CWJAP=\"ESP_TZH_W\",\"070330XYX\"\r\n";
const char AT_CIPSTART[]="AT+CIPSTART=0,\"TCP\",\"192.168.1.1\",3050\r\n";
const char AT_CIPSEND_S[]="AT+CIPSEND=0,20\r\n";
const char AT_CWSTATE[]="AT+CWSTATE?\r\n";
const char Receiving_Terminal[]="[Receiving-Terminal]\r\n";
const char ESP_Reply_CWSTATE[]="+CWSTATE";
const char ESP_Reply_IPD[]="+IPD";
#endif

