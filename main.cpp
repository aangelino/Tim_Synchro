#include "mbed.h"
#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim1;
long count=0;

static void MX_TIM1_Init(void);

int main(void)
{
  /* GPIO Ports Clock Enable /Enable the AHB1 peripheral clock. */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  MX_TIM1_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);    //Start TIM2 without interrupt

printf("\n\r srtart run \r\n");
  while (1)
  {

	  count = __HAL_TIM_GetCounter(&htim1);    //read TIM2 counter value
    printf("\n\r count=%d\n\r",count);
    wait(1);

  }


}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 15;
  if (HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    printf("_Error_Handler(__FILE__, __LINE__)");
    while(1){};
  }

}
