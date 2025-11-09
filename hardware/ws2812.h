#include "main.h"
#include "tim.h"

/*
ws2812：通过PWM波通信，其一个数据帧是一个完整周期的PWM波，通信速率为800 Kbit/s，即72MHz/90
1码：   由2/3左右的高电平 和 1/3左右的低电平组成
0码：   由1/3左右的高电平 和 2/3左右的低电平组成
复位码： 50us以上低电平
每个WS2812需要用24bit的数据来控制，当n个ws2812进行级联的时候，第一个灯会将第一个24bit的数据拦截，将后面的数据进行转发。
*/

#define WS_H           60   // 1 码相对计数值
#define WS_L           29   // 0 码相对计数值
#define WS_REST        40   // 复位信号脉冲数量
#define LED_NUM        24   // WS2812灯个数
#define DATA_LEN       24   // WS2812数据长度，单个需要24个字节
#define WS2812_RST_NUM 50   // 官方复位时间为50us（40个周期），保险起见使用50个周期
 
void WS2812_Init(void);
void WS2812_Set(uint16_t num,uint8_t R,uint8_t G,uint8_t B);