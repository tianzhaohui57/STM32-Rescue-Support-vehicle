#include "fatfs_sd.h"

//NVIC初始化
/**
 * @brief 配置中断优先级
 * 
 * 此函数配置了SDIO、USART1等中断的优先级。
 */
static void NVIC_Configuration(void) {
    NVIC_InitTypeDef NVIC_InitStructure;

    // 设置优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    // 配置SDIO中断
    NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Init(&NVIC_InitStructure);  

    // 配置USART1接收中断
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 配置其他定时器中断，如TIM3,TIM4,TIM5,TIM6,TIM7等
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
 * @brief 初始化USART1
 * 
 * 此函数初始化USART1，并使能USART1的DMA接收和接收中断。
 */
void USART_Initialization(void) {
    USART_InitTypeDef USARTinit;

    // 使能USART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // 配置USART1
    USARTinit.USART_BaudRate = 115200;
    USARTinit.USART_WordLength = USART_WordLength_8b;
    USARTinit.USART_StopBits = USART_StopBits_1;
    USARTinit.USART_Parity = USART_Parity_No;
    USARTinit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USARTinit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Cmd(USART1, ENABLE);
    USART_Init(USART1, &USARTinit);

    // 使能 USART1 的 DMA 接收
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    // 使能USART1接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

/**
 * @brief 配置PWM定时器
 * 
 * @param TIMx 要配置的PWM定时器
 */
void TIM_PWM_Initialization(TIM4567_PWM TIMx) {
    TIM_TimeBaseInitTypeDef TIMinit;

    // 使能TIM4、TIM5、TIM6、TIM7时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7, ENABLE);

    // 配置TIM基本参数
    TIMinit.TIM_Prescaler = 35;
    TIMinit.TIM_Period = 999;
    TIMinit.TIM_CounterMode = TIM_CounterMode_Up;
    TIMinit.TIM_ClockDivision = 1;

    switch (TIMx) {
        case TIM_PWM_M:
            // 配置TIM4、TIM5、TIM6、TIM7
            TIM_Cmd(TIM4, ENABLE);
            TIM_TimeBaseInit(TIM4, &TIMinit);
            TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

            TIM_Cmd(TIM5, ENABLE);
            TIM_TimeBaseInit(TIM5, &TIMinit);
            TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

            TIM_Cmd(TIM6, ENABLE);
            TIM_TimeBaseInit(TIM6, &TIMinit);
            TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

            TIM_Cmd(TIM7, ENABLE);
            TIM_TimeBaseInit(TIM7, &TIMinit);
            TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
            break;

        case TIM4_PWM_M:
            // 配置TIM4
            TIM_Cmd(TIM4, ENABLE);
            TIM_TimeBaseInit(TIM4, &TIMinit);
            TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
            break;
        case TIM5_PWM_M:
            // 配置TIM5
            TIM_Cmd(TIM5, ENABLE);
            TIM_TimeBaseInit(TIM5, &TIMinit);
            TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
            break;
        case TIM6_PWM_M:
            // 配置TIM6
            TIM_Cmd(TIM6, ENABLE);
            TIM_TimeBaseInit(TIM6, &TIMinit);
            TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
            break;
        case TIM7_PWM_M:
            // 配置TIM7
            TIM_Cmd(TIM7, ENABLE);
            TIM_TimeBaseInit(TIM7, &TIMinit);
            TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
            break;
    }
}

/**
 * @brief 初始化GPIO
 * 
 * 此函数初始化了GPIOB、GPIOE和GPIOA的一些引脚作为输出或复用推挽输出。
 */
void GPIO_Initialization(void) {
    GPIO_InitTypeDef GPIO_init;

    // 使能GPIOB、GPIOE、GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOA, ENABLE);

    // 配置GPIOB输出
    GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_init);

    // 配置GPIOE输出
    GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_init.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_init);

    // 配置GPIOA TX引脚为复用推挽输出
    GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_init.GPIO_Pin = GPIO_Pin_9;
    GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_init);

    // 配置GPIOA RX引脚为浮空输入
    GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_init.GPIO_Pin = GPIO_Pin_10;
    GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_init);
}

/**
 * @brief 将日志信息记录到文件或通过串口发送
 *
 * @param log_category 日志类别
 * @param log_process 日志处理过程描述
 * @param log_detail 日志详细信息的格式化字符串
 * @param ... 可变参数列表，用于填充 log_detail 中的格式化字符串
 */
void STM_LOG(const char* log_category, const char* log_process, const char* log_detail, ...) {
    char LOG[64],OUT_LOG[128];  // 存储格式化后的日志字符串
    va_list args;  // 用于处理可变参数列表
    va_start(args, log_detail);  // 初始化可变参数列表

    // 使用 vsnprintf 处理可变参数，将格式化后的日志字符串存储到 LOG 缓冲区中
    vsnprintf(LOG, sizeof(LOG), log_detail, args);

    va_end(args);  // 清理可变参数列表
    sprintf(OUT_LOG,"%s:(%s)%s\r\n\0",log_category,log_process,LOG);
    #if STM_SD_LOG
        // 如果定义了 STM_SD_LOG，则将日志写入SD卡文件
        UINT i;
        sta=f_opendir(&dir, "0:");
        sta=f_open(&fnew, "log.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
        sta=f_lseek(&fnew, f_size(&fnew));
        sta=f_write(&fnew, OUT_LOG, sizeof(OUT_LOG), &i);
        sta=f_close(&fnew);
    #else
        // 如果未定义 STM_SD_LOG，则通过串口发送日志信息
        Usart_SendString(USART1, OUT_LOG);
    #endif
}

/**
 * @brief 发送单个字节到 USART
 *
 * @param pUSARTx USART 对应的指针，如 USART1、USART2 等
 * @param ch 要发送的字节
 */
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch) {
    USART_SendData(pUSARTx, ch);
    
    // 等待直到发送缓冲区为空
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/**
 * @brief 发送字符串到 USART
 *
 * @param pUSARTx USART 对应的指针，如 USART1、USART2 等
 * @param str 要发送的字符串
 */
void Usart_SendString(USART_TypeDef *pUSARTx, const char *str) {
    unsigned int k = 0;
    
    // 逐字符发送字符串，直到遇到字符串结束符 '\0'
    do {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');
    
    // 等待直到所有字符都被发送完毕
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}


/**
 * @brief 向 ESP8266 发送 AT 指令并等待响应
 *
 * @param tame 发送 AT 指令后等待的时间（毫秒）
 * @param AT 要发送的 AT 指令字符串
 * @return ESP 模块的状态，可能的值为 ESP_OK、ESP_Error、ESP_ReceiveError 或 ESP_Noreply
 */
ESP ESP_AT(unsigned int tame, const char* AT) {
    unsigned int Error = 0, ReceiveError = 0, Noreply = 0;

    while (1) {
        // 发送 AT 指令到 ESP8266
        Usart_SendString(USART1, AT);

        // 等待一段时间，以便 ESP8266 处理指令
        delay_ms(tame);

        // 根据 ESP 模块的状态进行相应的处理
        switch (state) {
            case ESP_OK:
                state = ESP_Not;
                return ESP_OK;

            case ESP_Error:
                state = ESP_Not;
                Error++;

                // 如果错误计数达到上限（10次），返回 ESP_Error
                if (Error == 10)
                    return ESP_Error;
                break;

            case ESP_ReceiveError:
                state = ESP_Not;
                ReceiveError++;

                // 如果接收错误计数达到上限（10次），返回 ESP_ReceiveError
                if (ReceiveError == 10)
                    return ESP_ReceiveError;
                break;

            default:
                Noreply++;

                // 如果没有响应计数达到上限（30次），返回 ESP_Noreply
                if (Noreply == 30)
                    return ESP_Noreply;
                break;
        }
    }
}

    
/**
 * @brief 处理 ESP 模块的错误状态并进行相应的日志记录
 * 
 * @param ERROR_LOG ESP 模块的错误状态
 */
void ESP_ERROR_LOG(ESP ERROR_LOG) {
    #define ESP_LOG_PREFIX "ESP"
    switch (ERROR_LOG) {
        case ESP_OK:
            #if STM_LCD 
            LCD_ShowString(5+8*12,5,"OK   ",RED,BLACK,16,0);
            #endif
            break;
        case ESP_WIFI_OK:
            // 成功连接到 WiFi
            STM_LOG("I", ESP_LOG_PREFIX, "Successfully connected to WiFi");
            #if STM_LCD 
            LCD_ShowString(5+8*12,21,"OK   ",RED,BLACK,16,0);
            #endif
            break;
        case ESP_Error:
            // ESP 模块错误
            STM_LOG("E", ESP_LOG_PREFIX, "Module error");
            #if STM_LCD 
            LCD_ShowString(5+8*12,5,"ERROR",RED,BLACK,16,0);
            #endif
            break;
        case ESP_TCPv6Error:
            // 未获取到或不存在 TCPv6 连接
            STM_LOG("E", ESP_LOG_PREFIX, "TCPv6 not obtained or does not exist");
            #if STM_LCD 
            LCD_ShowString(5+8*12,37,"ERROR",RED,BLACK,16,0);
            #endif
            break;
        case ESP_CIPMUXError:
            // 启动多连接失败
            STM_LOG("E", ESP_LOG_PREFIX, "Failed to start multiple connections");
            break;
        case ESP_Connect:
            // 连接成功建立
            STM_LOG("I", ESP_LOG_PREFIX, "Connection successfully established");
            break;
        case ESP_No_Connection:
            // 未建立连接
            STM_LOG("W", ESP_LOG_PREFIX, "No connection established");
            #if STM_LCD 
            LCD_ShowString(5+8*12,21,"ERROR",RED,BLACK,16,0);
            LCD_ShowString(5+8*12,32,"ERROR",RED,BLACK,16,0);
            #endif
            break;
        case ESP_DISK_ERR:
        case ESP_ReceiveError:
        case ESP_Noreply:
        case ESP_empty:
            // ESP 磁盘/接收/无响应/空状态错误
            STM_LOG("E", ESP_LOG_PREFIX, "Error: %d", ERROR_LOG);
            #if STM_LCD 
            LCD_ShowString(5+8*12,5,"ERROR",RED,BLACK,16,0);
            #endif
            break;
        case ESP_IPV6Error:
            // 未获取到或不存在 IPV6 连接
            STM_LOG("E", ESP_LOG_PREFIX, "IPv6 not obtained or does not exist");
            #if STM_LCD 
            LCD_ShowString(5+8*12,37,"ERROR",RED,BLACK,16,0);
            #endif
            break;
        case ESP_IPV6_OK:
            // 成功获取 IPV6 连接
            STM_LOG("I", ESP_LOG_PREFIX, "IPv6 obtained");
            #if STM_LCD 
            LCD_ShowString(5+8*12,37,"OK   ",RED,BLACK,16,0);
            #endif
            break;
        default:
            // 未知状态
            STM_LOG("W", ESP_LOG_PREFIX, "Unknown state: %d", ERROR_LOG);
             #if STM_LCD 
            LCD_ShowString(5+8*12,5,"?    ",RED,BLACK,16,0);
            #endif
            break;
    }
}


#if STM_LCD

void STM_LCD_init(void)
{
    LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
    LCD_RoundedRectangle(0,0,160,64,2,GBLUE);
    LCD_RoundedRectangle(0,62,160,64,2,GBLUE);
    LCD_ShowString(5,5,"ESP Status:",RED,BLACK,16,0);
    LCD_ShowString(5,21,"WiFi Status:",RED,BLACK,16,0);
    LCD_ShowString(5,37,"IPV6 Status:",RED,BLACK,16,0);
    LCD_ShowString(15,70,"M1:",RED,BLACK,16,0);
    LCD_ShowString(15,100,"M2:",RED,BLACK,16,0);
    LCD_ShowString(90,70,"M3:",RED,BLACK,16,0);
    LCD_ShowString(90,100,"M4:",RED,BLACK,16,0);
    return;
}
#endif


#if STM_SD_LOG

/**
 * @brief 挂载设备（如SD卡）
 * 
 * @param equipment 设备的路径
 * @return FRESULT 文件系统的状态码
 */
FRESULT Mount_device(const TCHAR *equipment) {
    FRESULT SD_state;

    // 尝试挂载文件系统
    SD_state = f_mount(&fs, equipment, 1);

    switch (SD_state) {
        case FR_NO_FILESYSTEM:
            // 如果没有文件系统，尝试创建文件系统
            return f_mkfs(equipment, 0, 0);
        default:
            return SD_state;
    }
}
#endif

void ESP_Default(void){
    ESP_ERROR_LOG(ESP_AT(100,AT_AT));
    ESP_ERROR_LOG(ESP_AT(100,AT_ATE));
    ESP_ERROR_LOG(ESP_AT(100,AT_SYSSTORE));
    ESP_ERROR_LOG(ESP_AT(100,AT_CWMODE));
    ESP_ERROR_LOG(ESP_AT(500,AT_CWSAP));

}


int main(void)
{
	NVIC_Configuration();
	GPIO_Initialization();
	USART_Initialization();
    #if STM_SD_LOG
        Mount_device("0:");
    #endif
    #if STM_LCD
        STM_LCD_init();
    #endif
    ESP_Default(); 
	while(1);
}


/**
 * @brief USART1 接收中断处理函数
 * 
 * 此函数在USART1接收中断发生时被调用，用于处理接收到的数据并进行调试输出。
 * 在调试期间，通过串口发送调试信息以便观察和分析系统行为。
 * 
 * 注意：该函数中的 Usart_SendString 调用是专门用于调试输出。
 */
void USART1_IRQHandler(void) {
    // 检查是否接收缓冲区非空
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != SET) {
        return;  // 如果接收缓冲区为空，则退出
    }

    // 读取接收到的字节到缓冲区
    tx_buffer[tx_Number] = USART_ReceiveData(USART1);

    switch (tx_buffer[0]) {
        case 'O':
            // 发送 "ok" 到 USART1（调试输出）
            //Usart_SendString(USART1, "ok");
            tx_buffer[0] = 0x00;
            state = ESP_OK;
            tx_Number = 0;
            return;

        case 'E':
            // 发送 "ERROR" 到 USART1（调试输出）
            state = ESP_Error;
            //Usart_SendString(USART1, "ERROR");
            tx_buffer[0] = 0x00;
            tx_Number = 0;
            return;

        case '+':
            // 如果没接收到换行符 '\n'
            if (tx_buffer[tx_Number] != '\n') {
                tx_Number++;
                return;
            }
            tx_Number = 0;
            // 复制数据到 Read_data，并清空 tx_buffer
            strcpy((char *)Read_data, (char *)tx_buffer);
            memset(tx_buffer, 0, tx_Number);
            // 发送 Read_data 到 USART1
            Usart_SendString(USART1, (char *)Read_data);
            return;
        case '1':
        case '2':
        case '3':
        case '4':
            // 如果接收到 '0', '1', '2', '3', 或 '4'
            state = ESP_OK;
            // 执行 ESP_AT 函数，并在串口发送调试信息
            ESP_AT(10, AT_CIPSTATE);
            tx_buffer[0] = 0X00;
            return;
        default:
            // 重置 tx_Number 为 0，准备处理下一条数据
            tx_Number = 0;
            break;
    }
}
