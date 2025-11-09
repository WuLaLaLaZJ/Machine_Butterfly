#ifndef __SGP30_H__
#define __SGP30_H__

#include "main.h"

#define Device_Address 0x59
#define SGP30_read     0xb2         //0x59 << 1 | 0  
#define SGP30_write    0xb3         //0x59 << 1 | 1

void SGP30_Init(void);				  
void SGP30_ad_write(uint8_t a, uint8_t b);
uint32_t SGP30_ad_read(void);



#endif
