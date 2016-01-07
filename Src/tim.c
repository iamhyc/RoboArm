/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */

TimInputCapture Tim2Ch1 = {0, 0, 0, 0};
TimInputCapture Tim2Ch2 = {0, 0, 0, 0};
TimInputCapture Tim2Ch3 = {0, 0, 0, 0};
TimInputCapture Tim2Ch4 = {0, 0, 0, 0};
TimInputCapture Tim3Ch4 = {0, 0, 0, 0};


TIM_OC_InitTypeDef ConfigOCx = \
{
	.OCMode = TIM_OCMODE_PWM1,
	.Pulse = 0,
	.OCPolarity = TIM_OCPOLARITY_HIGH,
	.OCFastMode = TIM_OCFAST_DISABLE
};

TIM_IC_InitTypeDef ConfigICx = \
{
	.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING,
  .ICSelection = TIM_ICSELECTION_DIRECTTI,
  .ICPrescaler = TIM_ICPSC_DIV1,
  .ICFilter = 15
};

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  HAL_TIM_IC_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1);

  HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2);

  HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3);

  HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_4);

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_IC_InitTypeDef sConfigIC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  HAL_TIM_PWM_Init(&htim3);

  HAL_TIM_IC_Init(&htim3);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);	//直接启动输出PWM

  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 15;
  HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_4);

}
/* TIM4 init function */
void MX_TIM4_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 19999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim4);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __TIM2_CLK_ENABLE();
  
    /**TIM2 GPIO Configuration    
    PA0-WKUP     ------> TIM2_CH1
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    PA3     ------> TIM2_CH4 
    */
    GPIO_InitStruct.Pin = FIST_IN_Pin|DM_IN_Pin|YAW_IN_Pin|ROLL_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(htim_base->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __TIM3_CLK_ENABLE();
  
    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4 
    */
    GPIO_InitStruct.Pin = DM_OUT_Pin|L_Wheel_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = R_Wheel_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(R_Wheel_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = AutoSw_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(AutoSw_GPIO_Port, &GPIO_InitStruct);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_pwm->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* Peripheral clock enable */
    __TIM4_CLK_ENABLE();
  
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2 
    */
    GPIO_InitStruct.Pin = YAW_OUT_Pin|ROLL_OUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __TIM2_CLK_DISABLE();
  
    /**TIM2 GPIO Configuration    
    PA0-WKUP     ------> TIM2_CH1
    PA1     ------> TIM2_CH2
    PA2     ------> TIM2_CH3
    PA3     ------> TIM2_CH4 
    */
    HAL_GPIO_DeInit(GPIOA, FIST_IN_Pin|DM_IN_Pin|YAW_IN_Pin|ROLL_IN_Pin);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM2_IRQn);

  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __TIM3_CLK_DISABLE();
  
    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4 
    */
    HAL_GPIO_DeInit(GPIOA, DM_OUT_Pin|L_Wheel_Pin);

    HAL_GPIO_DeInit(GPIOB, R_Wheel_Pin|AutoSw_Pin);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM3_IRQn);

  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __TIM4_CLK_DISABLE();
  
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2 
    */
    HAL_GPIO_DeInit(GPIOB, YAW_OUT_Pin|ROLL_OUT_Pin);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM4_IRQn);

  }
  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */

void captureStart()
{
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);//AutoSw
}

void pwm_write(uint16_t timx, uint16_t Ch, float percent)
{
	TIM_HandleTypeDef htimx;
	uint32_t Channel;
	
	switch(timx){
		case 3:
			htimx = htim3;
		break;
		case 4:
			htimx = htim4;
		break;
	}
	switch(Ch){
		case 1:
			Channel = TIM_CHANNEL_1;
		break;
		case 2:
			Channel = TIM_CHANNEL_2;
		break;
		case 3:
			Channel = TIM_CHANNEL_3;
		break;
		case 4:
			Channel = TIM_CHANNEL_4;
		break;
	}
	HAL_TIM_PWM_Stop(&htimx, Channel);
	
	ConfigOCx.Pulse = (uint16_t)((htimx.Init.Period * percent + 1)/ 100) - 1;
	
	HAL_TIM_PWM_ConfigChannel(&htimx, &ConfigOCx, Channel);
	
	HAL_TIM_PWM_Start(&htimx, Channel);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  switch(htim->Channel){
    case HAL_TIM_ACTIVE_CHANNEL_1:
    {
      if(Tim2Ch1.State == 0)
      {
        Tim2Ch1.Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				{
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_1);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_1);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_1);
        Tim2Ch1.State = 1;
				}
      }
      else if(Tim2Ch1.State == 1)
      {
        Tim2Ch1.Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        Tim2Ch1.Frequency = (Tim2Ch1.Value2 > Tim2Ch1.Value1)?\
														(Tim2Ch1.Value2 - Tim2Ch1.Value1):\
                            ((0xFFFF - Tim2Ch1.Value1) + Tim2Ch1.Value2 + 1);
        Tim2Ch1.Frequency = HAL_RCC_GetPCLK1Freq() / Tim2Ch1.Frequency;
				{
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_1);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_1);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_1);
        Tim2Ch1.State = 0;
				}
      }
    }
    break;

    case HAL_TIM_ACTIVE_CHANNEL_2:
    {
      if(Tim2Ch2.State == 0)
      {
        Tim2Ch2.Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
				{
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_2);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_2);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_2);
        Tim2Ch2.State = 1;
				}
      }
      else if(Tim2Ch2.State == 1)
      {
        Tim2Ch2.Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        Tim2Ch2.Frequency = (Tim2Ch2.Value2 > Tim2Ch2.Value1)?\
														(Tim2Ch2.Value2 - Tim2Ch2.Value1):\
                            ((0xFFFF - Tim2Ch2.Value1) + Tim2Ch2.Value2 + 1);
        Tim2Ch2.Frequency = HAL_RCC_GetPCLK1Freq() / Tim2Ch2.Frequency;
        {
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_2);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_2);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_2);
        Tim2Ch2.State = 0;
				}
      }
    }
    break;

    case HAL_TIM_ACTIVE_CHANNEL_3:
    {
      if(Tim2Ch3.State == 0)
      {
        Tim2Ch3.Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
        {
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_3);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_3);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_3);
        Tim2Ch3.State = 1;
				}
      }
      else if(Tim2Ch3.State == 1)
      {
        Tim2Ch3.Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
        Tim2Ch3.Frequency = (Tim2Ch3.Value2 > Tim2Ch3.Value1)?\
														(Tim2Ch3.Value2 - Tim2Ch3.Value1):\
                            ((0xFFFF - Tim2Ch3.Value1) + Tim2Ch3.Value2 + 1);
        Tim2Ch3.Frequency = HAL_RCC_GetPCLK1Freq() / Tim2Ch3.Frequency;
        {
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_3);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_3);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_3);
        Tim2Ch3.State = 0;
				}
      }
    }
    break;

    case HAL_TIM_ACTIVE_CHANNEL_4:
    {
    if(htim->Instance == TIM2){
      if(Tim2Ch4.State == 0)
      {
        Tim2Ch4.Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        {
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_4);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_4);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_4);
        Tim2Ch4.State = 1;
				}
      }
      else if(Tim2Ch4.State == 1)
      {
        Tim2Ch4.Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        Tim2Ch4.Frequency = (Tim2Ch4.Value2 > Tim2Ch4.Value1)?\
														(Tim2Ch4.Value2 - Tim2Ch4.Value1):\
                            ((0xFFFF - Tim2Ch4.Value1) + Tim2Ch4.Value2 + 1);
        Tim2Ch4.Frequency = HAL_RCC_GetPCLK1Freq() / Tim2Ch4.Frequency;
        {
				HAL_TIM_IC_Stop(&htim2,TIM_CHANNEL_4);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
				HAL_TIM_IC_ConfigChannel(&htim2, &ConfigICx, TIM_CHANNEL_4);
				HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_4);
        Tim2Ch4.State = 0;
				}
      }
    }
		else if (htim->Instance == TIM3){
			if(Tim3Ch4.State == 0)
      {
        Tim3Ch4.Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        {
				HAL_TIM_IC_Stop(&htim3,TIM_CHANNEL_4);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
				HAL_TIM_IC_ConfigChannel(&htim3, &ConfigICx, TIM_CHANNEL_4);
				HAL_TIM_IC_Start(&htim3,TIM_CHANNEL_4);
        Tim3Ch4.State = 1;
				}
      }
      else if(Tim3Ch4.State == 1)
      {
        Tim3Ch4.Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        Tim3Ch4.Frequency = (Tim3Ch4.Value2 > Tim3Ch4.Value1)?\
														(Tim3Ch4.Value2 - Tim3Ch4.Value1):\
                            ((0xFFFF - Tim3Ch4.Value1) + Tim3Ch4.Value2 + 1);
        Tim3Ch4.Frequency = HAL_RCC_GetPCLK1Freq() / Tim3Ch4.Frequency;
        {
				HAL_TIM_IC_Stop(&htim3,TIM_CHANNEL_4);
				ConfigICx.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
				HAL_TIM_IC_ConfigChannel(&htim3, &ConfigICx, TIM_CHANNEL_4);
				HAL_TIM_IC_Start(&htim3,TIM_CHANNEL_4);
        Tim3Ch4.State = 0;
				}
      }
		}
    }
    break;
		default:
			break;
  }
    
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
