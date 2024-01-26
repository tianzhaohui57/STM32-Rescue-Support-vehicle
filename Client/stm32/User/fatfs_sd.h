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
uint8_t rx_buffer[BUFFER_SIZE];
uint8_t Read_data[BUFFER_SIZE];
ESP state=ESP_Not;




FRESULT Mount_device(const TCHAR *equipment);
void STM_LOG(const char* __restrict,const char* __restrict,const char* __restrict,...)__attribute__((__nonnull__(1,2,3)));
void Usart_SendString( USART_TypeDef * pUSARTx,const char *str);
FRESULT sta;

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

#endif

