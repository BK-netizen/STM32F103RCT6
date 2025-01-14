#include "HCSR04.h"

extern uint8_t  g_tim_sta;
extern uint32_t g_tim_val;
uint32_t temp = 0;
float distant = 0.0;
uint8_t   measure_Cnt = 0;

//void delay_us(uint32_t us)//主频180M
//{
//    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
//    while (delay--)
//    {
//        ;
//    }
//}

float SR04_distant(void)
{
	switch(measure_Cnt)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
			measure_Cnt++;
			break;
		case 1:
			if(g_tim_sta & 0x80)
			{
				temp = g_tim_sta & 0x3F;
				temp *= 0xFFFFFFFF;
				temp += g_tim_val;
				//printf("高电平时间为%d us\r\n",temp);
				distant = (temp * 0.034)/2;  //cm
				printf("测距为%.2f cm\r\n",distant);
				g_tim_sta = 0;
				measure_Cnt = 0;
				break;
			}
	}
	return distant;
}	
