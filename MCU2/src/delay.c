#include "stm32f10x.h"

/* for������ ������ ������ �Լ� */
static void delay_int_count(volatile unsigned int nTime)
{
    for(; nTime>0; nTime--);
}
void delay_m(void)
{
    delay_int_count(806596/*6*/);
}

void delay_Us(void)
{
    delay_int_count(800/*6*/);
}