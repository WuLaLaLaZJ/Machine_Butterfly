#include "sht4x.h"
#include "main.h"
#include "MyI2C.h"

//SHT41,温湿度传感器模块

void Soft_IIC_Write_Command(uint8_t deviceAddr, uint8_t command) {
    IIC_Start();
    IIC_Send_Byte(deviceAddr << 1); // 发送设备地址和写位
    IIC_Wait_Ack();
    IIC_Send_Byte(command); // 发送命令
    IIC_Wait_Ack();
    IIC_Stop();
}

void SHT40_Start_Measurement(void) {
    Soft_IIC_Write_Command(SHT40_ADDRESS, SHT40_COMMAND_MEASURE_HIGH_PRECISION);
    HAL_Delay(10); // 根据数据手册说明，延时10ms
}

void SHT40_Read_Measurement(uint8_t* data, uint8_t length) {
    IIC_Start();
    IIC_Send_Byte((SHT40_ADDRESS << 1) | 0x01); // 发送设备地址和读位
    IIC_Wait_Ack();
    for (uint8_t i = 0; i < length-1; i++) {
      *data = IIC_Read_Byte(i < (length - 1)); // 读取数据并发送应答信号
			data++;
			IIC_Ack();
    }
		*data = IIC_Read_Byte(0);
		IIC_NAck();
    IIC_Stop();
}

