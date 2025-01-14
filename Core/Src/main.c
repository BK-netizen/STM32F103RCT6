/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD/lcd.h"
#include "KEY/key.h"
#include "string.h"
#include "math.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define PI 3.1415926
#define SCREEN_WIDTH  240     
#define SCREEN_HEIGHT 320 
#define RXBUFFERSIZE  256     //�������ֽ���

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

char RxBuffer[RXBUFFERSIZE];   //��������

uint8_t aRxBuffer;			//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;		//���ջ������
uint8_t LED_Flag = 0;
uint16_t SinWaveTable[300] = {0};
uint16_t TriangleWaveTable[300] = {0};
uint8_t key = 0;
uint16_t N_POINTS = 600;    //һ������300���� 
uint32_t ARR = 0;           //�Զ���װ��ֵ
float VMaxRange = 3.3;
float currentFrequency = 1000.0f;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void SineWaveGen(uint32_t NPoints, float VMaxRange, uint16_t* SineWaveTable);
void TriangleWaveGen(uint32_t NPoints, float VMaxRange, uint16_t* TriangleWaveTable);
void display_sine_wave_on_lcd(void) ;
void display_triangle_wave_on_lcd(void) ;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_DMA_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  key_init();
  lcd_clear(WHITE);
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1); 
//  SineWaveGen(300,1.1, SinWaveTable);
//  TriangleWaveGen(300,1.1,TriangleWaveTable);
//  display_triangle_wave_on_lcd();
  HAL_TIM_Base_Start(&htim6);
//  HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)SinWaveTable,300,DAC_ALIGN_12B_R);
//	display_sine_wave_on_lcd();

//	for (uint32_t i = 0; i < 300; i++)
//  {
//        printf("TriangleWaveTable[%d] = %u\r\n", i, TriangleWaveTable[i]);  // ��ӡ���������Ͷ�Ӧ��ֵ
//  }
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
     key = key_scan(0);
//		if(key == 1)
//		{
//			if(VMaxRange < 3.3)
//			{
//					VMaxRange += 0.1;
//				    if (VMaxRange > 3.3) 
//					{
//						VMaxRange = 3.3;  // �������ֵΪ 3.3
//					}
//					lcd_clear(WHITE);					
//			}
//		}
//		if(key ==2)
//		{
//			if(VMaxRange > 0)
//			{
//					VMaxRange -= 0.1;
//					lcd_clear(WHITE);						
//			}
//		}
//		if(key ==3)
//		{
//		    if(currentFrequency < 10000.0f)  // Ƶ�����Ϊ10kHz
//		    {
//                    currentFrequency += 1000.0f;  // ����1kHz
//					N_POINTS *= 2;
//					lcd_clear(WHITE);
//			}		
//		
//		}
//		 ARR = (HAL_RCC_GetPCLK2Freq() / (currentFrequency * 300)) -1;
//		__HAL_TIM_SET_AUTORELOAD(&htim6, ARR);
		//printf("%d\r\n",ARR);
//		printf("%.2f\r\n",VMaxRange);

		//SineWaveGen(300, VMaxRange, SinWaveTable);
		//lcd_clear(WHITE);
		//display_sine_wave_on_lcd();
	  lcd_show_string(20,20,30,20,24,"F ",BLACK);
//	  lcd_show_num(45,20,currentFrequency/1000,2,24,BLACK);
	  lcd_show_string(85,20,30,20,24,"KHZ",BLACK);
	  lcd_show_string(20,45,30,20,24,"V ",BLACK);
//	  lcd_show_num(45,45,VMaxRange,2,24,BLACK);
//	  lcd_show_string(75,45,5,5,24,".",BLACK);
//	  lcd_show_num(80,45,(int)(VMaxRange * 10) % 10,2,24,BLACK);
	  lcd_show_string(110,45,30,20,24,"V",BLACK);
	  if(LED_Flag == 1)
	  {    
		    HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
			if(key == 1)
			{
				if(VMaxRange < 3.3)
				{
					VMaxRange += 0.1;
				    if (VMaxRange > 3.3) 
					{
						VMaxRange = 3.3;  // �������ֵΪ 3.3
					}
					lcd_clear(WHITE);					
				}	
			}
			if(key ==2)
			{
				if(VMaxRange > 0)
				{
					VMaxRange -= 0.1;
					lcd_clear(WHITE);						
				}
			}
			if(key ==3)
			{
				if(currentFrequency < 10000.0f)  // Ƶ�����Ϊ10kHz
				{
                    currentFrequency += 1000.0f;  // ����1kHz
					N_POINTS *= 2;
					lcd_clear(WHITE);
				}		
			
			}
			ARR = (HAL_RCC_GetPCLK2Freq() / (currentFrequency * 300)) -1;
			__HAL_TIM_SET_AUTORELOAD(&htim6, ARR);
			SineWaveGen(300, VMaxRange, SinWaveTable);
			HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)SinWaveTable,300,DAC_ALIGN_12B_R);
			//lcd_clear(WHITE);
		    lcd_show_num(45,20,currentFrequency/1000,2,24,BLACK);
			lcd_show_num(45,45,VMaxRange,2,24,BLACK);
			lcd_show_string(75,45,5,5,24,".",BLACK);
			lcd_show_num(80,45,(int)(VMaxRange * 10) % 10,2,24,BLACK);
			lcd_show_string(45,270,30,20,24,"Sin",BLACK);
			display_sine_wave_on_lcd();
	  }
	  else if(LED_Flag == 2)
	  {
		    
		  //HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
		  if(key == 1)
			{
				if(VMaxRange < 3.3)
				{
					VMaxRange += 0.1;
				    if (VMaxRange > 3.3) 
					{
						VMaxRange = 3.3;  // �������ֵΪ 3.3
					}
					lcd_clear(WHITE);					
				}	
			}
			if(key ==2)
			{
				if(VMaxRange > 0)
				{
					VMaxRange -= 0.1;
					lcd_clear(WHITE);						
				}
			}
			if(key ==3)
			{
				if(currentFrequency < 10000.0f)  // Ƶ�����Ϊ10kHz
				{
                    currentFrequency += 1000.0f;  // ����1kHz
					N_POINTS *= 2;
					lcd_clear(WHITE);
				}		
			
			}
		  ARR = (HAL_RCC_GetPCLK2Freq() / (currentFrequency * 300)) -1;
		  __HAL_TIM_SET_AUTORELOAD(&htim6, ARR);
		  TriangleWaveGen(300, VMaxRange, TriangleWaveTable);
		  HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
		  HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)TriangleWaveTable,300,DAC_ALIGN_12B_R);
		  lcd_show_num(45,20,currentFrequency/1000,2,24,BLACK);
		  lcd_show_num(45,45,VMaxRange,2,24,BLACK);
		  lcd_show_string(75,45,5,5,24,".",BLACK);
		  lcd_show_num(80,45,(int)(VMaxRange * 10) % 10,2,24,BLACK);
		  lcd_show_string(45,270,90,20,24,"Triangle",BLACK);
		  display_triangle_wave_on_lcd();
	  }


  }	
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//�������Ҳ�
void SineWaveGen(uint32_t NPoints, float VMaxRange, uint16_t* SineWaveTable)
{
    int i = 0;
    double radian = 0;  // ����
    double setup = 0;  // ����֮��ļ��
    double voltage = 0;  // �����ѹ

    setup = (2 * PI) / NPoints;  // ����֮��ļ��

    while (i < NPoints)
    {
        voltage = VMaxRange / 2.0 * (sin(radian) + 1.0);  // �����ѹ
        SineWaveTable[i] = (uint16_t)(voltage * 4096 / 3.3);  // ��ѹתΪDAC��ֵ
        radian += setup;  // ��һ����Ļ���
        i++;
    }
}

//�������ǲ�
void TriangleWaveGen(uint32_t NPoints, float VMaxRange, uint16_t* TriangleWaveTable)
{
    int i = 0;
//    double ramp_up = 0;    // ��������
//    double ramp_down = 0;  // �½�����
    double voltage = 0;    // �����ѹ

    // ���ǲ���һ�����ڣ����貨����0�����ֵ֮�����Ա仯�������ڷ�Ϊ�������½�
    int half_period = NPoints / 2;

    while (i < NPoints)
    {
        // ��������
        if (i < half_period) 
        {
            voltage = (VMaxRange / half_period) * i;  // ���������Դ�0��VMaxRange
        }
        // �½�����
        else
        {
            voltage = VMaxRange - ((VMaxRange / half_period) * (i - half_period));  // �½������Դ�VMaxRange��0
        }

        TriangleWaveTable[i] = (uint16_t)(voltage * 4096 / 3.3);  // ��ѹתΪDAC��ֵ
        i++;
    }
}

void delay_ms(uint32_t ms)
{
	uint32_t ms_uwTick = uwTick;
	while(ms_uwTick - uwTick <ms)
	{
	
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) // �ж����ĸ����ڴ�����
	{
		if(Uart1_Rx_Cnt >= 255)  //����ж�
		{
			Uart1_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer));
			HAL_UART_Transmit(&huart1, (uint8_t *)"�������", 10,0xFFFF); 	  
		}
		else
		{
			RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��
			if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
			{
				HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
				if (strncmp((char *)RxBuffer, "Z", 1) == 0)
        {
                    
					LED_Flag = 1;
					
                    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // ���� LED
        }
				if (strncmp((char *)RxBuffer, "S", 1) == 0)
        {
                    // ������յ� "task01"������ LED
					LED_Flag = 2;
                    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // ���� LED
        }
				//while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
				Uart1_Rx_Cnt = 0;
				memset(RxBuffer,0x00,sizeof(RxBuffer)); //�������
			}
		}
	}
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
}

//LCD ��ʾ���Ҳ�����
void display_sine_wave_on_lcd(void) 
{
    uint16_t i;
    int16_t y;
    int16_t amplitude = 120;  // �������ȣ����ⳬ����Ļ�߶ȷ�Χ
    int16_t offset_y = 120;  // ƫ������ʹ���Ҳ�����Ļ��ֱ������ʾ

    // ÿ��������300���㣬���������ܹ�600����
    // �������е����Ҳ����ݵ㲢��ʾ��LCD��
    for (i = 0; i < N_POINTS; i++) {
        // �����ݵ�ӳ�䵽��ʾ�������ڵ���Ļ���
        int16_t x = i * SCREEN_WIDTH / N_POINTS;  // ������ӳ�䣬x��0��SCREEN_WIDTH

        // ��DAC�������ֵӳ�䵽��Ļ�߶�
        y = (SinWaveTable[i % 300] * amplitude / 4096) + offset_y;  // ͨ��%300ȷ���ӵ�һ�������ظ�ʹ������

        // ��ֹ������Ļ��Χ
        if (y < 0) y = 0;
        if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;

        // ��LCD�ϻ������Ҳ���ÿ����
        lcd_draw_point(x, y, RED);  // ���Ƶ�
    }
}

//LCD��ʾ���ǲ�
void display_triangle_wave_on_lcd(void) 
{
    uint16_t i;
    int16_t x;  // ������
    int16_t y;  // ������
    int16_t amplitude = 120;  // �������ȣ����ⳬ����Ļ��ȷ�Χ
    int16_t offset_x = 120;   // ƫ������ʹ���ǲ�����Ļˮƽ������ʾ

    // �������е����ǲ����ݵ㲢��ʾ��LCD��
    for (i = 0; i < N_POINTS; i++) {
        // �����ݵ�ӳ�䵽��ʾ���Ĵ�ֱ���򣨷�ֵ����y��0��SCREEN_HEIGHT
        x = i * SCREEN_HEIGHT / N_POINTS;  // ӳ�䵽��Ļ�ĸ߶�

        // ��DAC�������ֵӳ�䵽��Ļ��ˮƽ���򣨷��ȣ�
        y = (TriangleWaveTable[i % 300] * amplitude / 4096) + offset_x;  // ͨ��%300ȷ���ӵ�һ�������ظ�ʹ������

        // ��ֹ������Ļ��Χ
        if (y < 0) x = 0;
        if (y >= SCREEN_WIDTH) y = SCREEN_WIDTH - 1;

        // ��LCD�ϻ������ǲ���ÿ����
        lcd_draw_point(x, y, RED);  // ���Ƶ�
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
