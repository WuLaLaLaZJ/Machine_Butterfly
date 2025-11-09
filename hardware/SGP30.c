#include "SGP30.h"
#include "MyI2C.h"


void SGP30_Init(void)
{
//	IIC_Init();
	SGP30_ad_write(0x26,0x12);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_ad_write(uint8_t a, uint8_t b)
{
  	IIC_Start();
  	IIC_Send_Byte(SGP30_write); //发送器件地址+写指令
	IIC_Wait_Ack();
  	IIC_Send_Byte(a);		//发送控制字节
	IIC_Wait_Ack();
	IIC_Send_Byte(b);
	IIC_Wait_Ack();
	IIC_Stop();
	HAL_Delay(100);
		
}

uint32_t SGP30_ad_read(void)
{
  	uint32_t dat;
	uint8_t crc;
  	IIC_Start();
  	IIC_Send_Byte(SGP30_read); //发送器件地址+写指令
	IIC_Wait_Ack();
  	dat = IIC_Read_Byte(1);
		dat <<= 8;
		dat += IIC_Read_Byte(1);
		crc = IIC_Read_Byte(1); //crc数据,舍去
	  	crc = crc;  //避免编译出现警告
		dat <<= 8;
		dat += IIC_Read_Byte(1);
		dat <<= 8;
		dat += IIC_Read_Byte(0);
  	IIC_Stop();
  	return(dat);
}
