#include "stm32f10x.h"
#include <stdio.h>

TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;
extern __IO uint16_t CCR1_Val;

extern uint8_t Send_data;
extern uint8_t Receive_data;
extern uint8_t lock;
void door_lock(int locking)
{
    if(locking==0)//////////////////잠금
        {
            delay_m();
            CCR1_Val=1000;                  //서보모터 작동
            //printf("CCR1_Val : %d\n", CCR1_Val);
            TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
            TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
            GPIO_SetBits(GPIOB, GPIO_Pin_8);            //빨간색 LED켬
            GPIO_ResetBits(GPIOB, GPIO_Pin_9);          //초록색 LED끔
        }
    else if(locking==1)///////////////열림
        {
            delay_m();
            CCR1_Val=2000;                  //서보모터 작동
            //printf("CCR1_Val : %d\n", CCR1_Val);
            TIM_OCInitStructure_PWM.TIM_Pulse = CCR1_Val;
            TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);
            GPIO_SetBits(GPIOB, GPIO_Pin_9);            //초록색 LED켬
            GPIO_ResetBits(GPIOB, GPIO_Pin_8 );         //빨간색 LED끔
        }
    

}