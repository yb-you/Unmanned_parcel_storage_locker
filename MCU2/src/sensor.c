#include "stm32f10x.h"
#include <stdio.h>

int led1;
int led2;
int led3;
int led4;
void sensor(void)   //////////////////////////////////적외선 센서
{
    led1=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);
    led2=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
    led3=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
    led4=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
    delay_m();
    //printf("led1=%d\n led2=%d\n led3=%d\n led4=%d\n",led1,led2,led3,led4);
    if(!led1)
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
    else
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    if(!led2)
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
    else
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    if(!led3)
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
    else
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);
    if(!led4)
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
    else
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}