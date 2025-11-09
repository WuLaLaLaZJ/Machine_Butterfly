#ifndef __MYI2C_H
#define __MYI2C_H

#include "main.h"

// IIC引脚操作

#define SDA_PIN  GPIO_PIN_8   //SDA-> PB8
#define SCL_PIN  GPIO_PIN_9   //SCL-> PB9
#define SDA_PORT GPIOB
#define SCL_PORT GPIOB

#define READ_SDA() HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN)

#define SDA_HIGH() HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_SET)
#define SDA_LOW()  HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_RESET)
#define SCL_HIGH() HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_SET)
#define SCL_LOW()  HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_RESET)

// IIC基本操作
void IIC_Delay(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t byte);
uint8_t IIC_Read_Byte(uint8_t ack);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
static void SDA_OUT(void);
static void SDA_IN(void);

#endif
