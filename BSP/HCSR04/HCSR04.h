//#ifndef __HCSR04_H__
//#define __HCSR04_H__
//#include "main.h"
//#include "stdio.h"

//float SR04_distant(void);

//#endif
#ifndef __HCSR04_H__
#define __HCSR04_H__

#include "main.h"
#include "tim.h"
#include "stdio.h"

#define TRIG_H  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)
#define TRIG_L  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)

void delay_us(uint32_t us);
float SR04_distant(void);

#endif

