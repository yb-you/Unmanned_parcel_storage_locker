#include "stm32f10x.h"
/*
    NVIC 설정에 관련된 코드들을 함수화하여 나타낸 c파일
    해당 명령어는 stm32f10x_nvic.c, stm32f10x_nvic.h가 아닌
             misc.c, misc.h에 나타나 있다.
*/

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);

  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);


    NVIC_InitTypeDef NVIC_InitStructure_KEY;
    /* Set the Vector Table base location at 0x08000000 */ 
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the EXTI0 Interrupt */
    NVIC_InitStructure_KEY.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure_KEY.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure_KEY.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure_KEY.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure_KEY);
    
     NVIC_InitStructure_KEY.NVIC_IRQChannel = EXTI1_IRQn;
     NVIC_InitStructure_KEY.NVIC_IRQChannelPreemptionPriority = 0;
     NVIC_InitStructure_KEY.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure_KEY.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure_KEY);
}