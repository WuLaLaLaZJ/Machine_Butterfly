#include "main.h"  

#ifndef SHT4X_H
#define SHT4X_H

// SHT40操作
#define SHT40_ADDRESS 0x44 // SHT40的I2C地址
#define SHT40_COMMAND_MEASURE_HIGH_PRECISION 0xFD  //要发送的命令 0XFD

void Soft_IIC_Write_Command(uint8_t deviceAddr, uint8_t command);
void SHT40_Start_Measurement(void);
void SHT40_Read_Measurement(uint8_t* data, uint8_t length);

#endif // SOFTIIC_H
