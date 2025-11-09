#include "main.h"   
#include "MyI2C.h"

#define CPU_FREQUENCY_MHZ    64		// STM32时钟主频 MHz
void delay_us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}

static void SDA_OUT(void){
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_OUTPUT_OD;
    SOFT_IIC_GPIO_STRUCT.Pin = SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

static void SDA_IN(void)
{
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_INPUT;
    SOFT_IIC_GPIO_STRUCT.Pin = SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

void IIC_Delay(void) {
	delay_us(5);
}

void IIC_Start(void) {
    SDA_OUT();
    SDA_HIGH();
    SCL_HIGH();
    IIC_Delay();
    SDA_LOW();
    IIC_Delay();
    SCL_LOW();
}

void IIC_Stop(void) {
    SDA_OUT();
    SCL_LOW();
    SDA_LOW();
    IIC_Delay();
    SCL_HIGH();
    IIC_Delay();
    SDA_HIGH();
    IIC_Delay();
}

void IIC_Send_Byte(uint8_t byte) {
    SDA_OUT();
		SCL_LOW();
    for (uint8_t i = 0; i < 8; i++) {
        if ((byte<<i) & 0x80) {
            SDA_HIGH();
        } else {
            SDA_LOW();
        }
				IIC_Delay();
        SCL_HIGH();
        IIC_Delay();
        SCL_LOW();
        IIC_Delay();
    }
}

uint8_t IIC_Read_Byte(uint8_t ack) {
    uint8_t byte = 0;
    SDA_IN();
    for (uint8_t i = 0; i < 8; i++) {
        SCL_LOW();
        IIC_Delay();
        SCL_HIGH();
        byte <<= 1;
        if (READ_SDA()) {
            byte |= 0x01;
        }
        IIC_Delay();
    }
    return byte;
}

uint8_t IIC_Wait_Ack(void)
{
    uint8_t wait;
    SDA_IN();
		IIC_Delay();
		SCL_HIGH();
		IIC_Delay();
    while (READ_SDA())
    {
        wait++;
        if (wait > 200)
        {
            IIC_Stop();
            return 1;
        }
    }
    SCL_LOW();
    return 0;
}

void IIC_Ack(void) {
    SCL_LOW();
    SDA_OUT();
    SDA_LOW();
    IIC_Delay();
    SCL_HIGH();
    IIC_Delay();
    SCL_LOW();
}

void IIC_NAck(void) {
    SCL_LOW();
    SDA_OUT();
    SDA_HIGH();
    IIC_Delay();
    SCL_HIGH();
    IIC_Delay();
    SCL_LOW();
}
