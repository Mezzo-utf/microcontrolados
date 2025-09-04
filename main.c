/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "button.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */

uint8_t button_release(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t active_high)
{
  static uint8_t last_state = 1;  // Último estado do botão
  uint8_t current_state;

  // Lê o estado atual do pino
  current_state = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

  // Se o botão for ativo em nível alto, inverte a lógica
  if (!active_high)
    current_state = !current_state;

  // Detecta transição de pressionado para solto
  if (current_state == 1 && last_state == 0)
  {
    HAL_Delay(20);  // Delay LED_KIT_Pinde debounce (20ms)

    // Confirma se ainda está solto após o delay
    if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == (active_high ? GPIO_PIN_SET : GPIO_PIN_RESET))
    {
      last_state = 1;
      return 1; // Botão foi solto
    }
  }

  // Atualiza estado anterior se estiver pressionado
  if (current_state == 0)
    last_state = 0;

  return 0; // Nenhuma transição detectada
}

int main(void)
{

  /* USER CODE BEGIN 1 */
  uint32_t i;
  uint8_t leds = 0;
  uint8_t last_led = 0;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  while (1) {
  for (i = 0; i < 5; i++) {

    if (button_release(GPIOB, GPIO_PIN_12, 0)) {
    //if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET){ // botão pressionado

      HAL_GPIO_WritePin(GPIOA, leds, 0);

      if (leds == 0) {
        leds = (1 << 3);
      } else if (leds == GPIO_PIN_7) {
        leds = 0;
      } else {
        leds = leds << 1;
      }

      HAL_GPIO_WritePin(GPIOA, leds, 1);
    }

    HAL_Delay(200);
  }
}

  
  
  /* while (1)
  {
    for (i=0; i<13;i++){
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8); // alterna o estado do LED
    HAL_GPIO_WritePin(LED_KIT_GPIO_Port, LED_KIT_Pin, 0);
    HAL_Delay(25);
    HAL_GPIO_WritePin(LED_KIT_GPIO_Port, LED_KIT_Pin, 1);
    HAL_Delay(50);
    HAL_Delay(800);
    if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
    {
      // Desliga o LED anterior
      if (last_led != 0)
      HAL_GPIO_WritePin(GPIOA, last_led, GPIO_PIN_RESET);
  
  if (leds == 0) {
      leds = GPIO_PIN_3;
      HAL_Delay(100);
  }
  else if (leds == GPIO_PIN_3) {
      leds = GPIO_PIN_4;
      HAL_Delay(100);
  }
  else if (leds == GPIO_PIN_4) {
      leds = GPIO_PIN_5;
      HAL_Delay(100);
  }
  else if (leds == GPIO_PIN_5) {
      leds = GPIO_PIN_6;
      HAL_Delay(100);
  }
  else if (leds == GPIO_PIN_6) {
      leds = GPIO_PIN_7;
      HAL_Delay(100);
  }
  else if (leds == GPIO_PIN_7) {
      leds = GPIO_PIN_3; // volta para o início
      HAL_Delay(100);
  }
  

      HAL_GPIO_WritePin(GPIOA, leds, GPIO_PIN_SET);
      last_led = leds;

      HAL_Delay(200);
    } */
  }
    /*
    if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1))
    {
      HAL_GPIO_WritePin(GPIOA, leds, 1);
      if (leds == 0)
      {
        leds = GPIO_PIN_12;
      }
      else if (leds == GPIO_PIN_12)
      {
        leds = GPIO_PIN_11;
      }
      else if (leds == GPIO_PIN_11)
      {
        leds = GPIO_PIN_10;
      }
      else if (leds == GPIO_PIN_10)
      {
        leds = GPIO_PIN_9;
      }
      else if (leds == GPIO_PIN_9)
      {
        leds = GPIO_PIN_8;
      }
      else if (leds == GPIO_PIN_8)
      {
        leds = 0;
      }

      HAL_GPIO_WritePin(GPIOA, leds, 1);
    }
  }

  */

    /* USER CODE BEGIN 3 */
  
  /* USER ODE END 3 */


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_KIT_GPIO_Port, LED_KIT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_KIT_Pin */
  GPIO_InitStruct.Pin = LED_KIT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_KIT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin
                           LED5_Pin */
  GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BOTAO1_Pin BOTAO2_Pin */
  GPIO_InitStruct.Pin = BOTAO1_Pin | BOTAO2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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

#ifdef USE_FULL_ASSERT
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
