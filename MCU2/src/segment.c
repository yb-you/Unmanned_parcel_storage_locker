#include "stm32f10x.h"

/* 4digit segment의 자릿수에 대한 핀 번호 정의 */
#define SEG_dig_4        	GPIO_Pin_8
#define SEG_dig_3        	GPIO_Pin_7
#define SEG_dig_2        	GPIO_Pin_1
#define SEG_dig_1        	GPIO_Pin_0

/* 4digit segment의 숫자값(0~9)에 대한 핀 번호 정의 */
#define a                  GPIO_Pin_0
#define b                  GPIO_Pin_1
#define c                  GPIO_Pin_2
#define d                  GPIO_Pin_3
#define e                  GPIO_Pin_4
#define f                  GPIO_Pin_5
#define g                  GPIO_Pin_6


////////////////////////////* 4digit segment의 출력 숫자 값을 정의한 함수 *///////////////////////
void GPIO_4digit_segment_0(void)
{
    // 0 출력
    GPIO_ResetBits(GPIOC, a| b| c| d| e| f);
    GPIO_SetBits(GPIOC, g);
}

void GPIO_4digit_segment_1(void)
{
    // 1 출력
    GPIO_ResetBits(GPIOC, b| c);
    GPIO_SetBits(GPIOC, a| d| e| f| g);
}

void GPIO_4digit_segment_2(void)
{
    // 2 출력
    GPIO_ResetBits(GPIOC, a| b| d| e| g);
    GPIO_SetBits(GPIOC, c| f);
}
void GPIO_4digit_segment_3(void)
{
    // 3 출력
    GPIO_ResetBits(GPIOC, a| b| c| d| g);
    GPIO_SetBits(GPIOC, e| f);
}
void GPIO_4digit_segment_4(void)
{
    // 4 출력
    GPIO_ResetBits(GPIOC, b| c| f| g);
    GPIO_SetBits(GPIOC, a| d| e);
}
void GPIO_4digit_segment_5(void)
{
    GPIO_ResetBits(GPIOC, a| c| d| f|g);
    GPIO_SetBits(GPIOC, b|e );
}
void GPIO_4digit_segment_6(void)
{
    GPIO_ResetBits(GPIOC, a| c| d|e| f| g);     //6
    GPIO_SetBits(GPIOC,b);
}
void GPIO_4digit_segment_7(void)
{
    GPIO_ResetBits(GPIOC,a| b| c| f);     //7
    GPIO_SetBits(GPIOC,d| e|g);
}
void GPIO_4digit_segment_8(void)
{
    GPIO_ResetBits(GPIOC,a| b| c| d| e|f| g);     //8
}
void GPIO_4digit_segment_9(void)
{
    GPIO_ResetBits(GPIOC, a| b| c| d| f| g);     //9
    GPIO_SetBits(GPIOC,e);
}
void GPIO_4digit_segment_100(void)               // -모양 출력
{
    GPIO_ResetBits(GPIOC, g);     
    GPIO_SetBits(GPIOC,e|a| b| c| d| f);
}
void SEG(int num)
{
    switch(num)
    {
        case 1:
            GPIO_4digit_segment_0(); break;
        case 2:
            GPIO_4digit_segment_1();break;
        case 3:
            GPIO_4digit_segment_2();break;
        case 4:
            GPIO_4digit_segment_3();break;
        case 5:
            GPIO_4digit_segment_4();break;
        case 6:
            GPIO_4digit_segment_5();break;
        case 7:
            GPIO_4digit_segment_6();break;
        case 8:
            GPIO_4digit_segment_7();break;
        case 9:
            GPIO_4digit_segment_8();break;
        case 10:
            GPIO_4digit_segment_9();break;
        case 100:
            GPIO_4digit_segment_100();break;
    }
        
}
////////////////////////////////////* 4digit의 자릿수를 정의하는 함수 */////////////////////////////////
void GPIO_4digit_segment_DIG_1(void)
{
    GPIO_ResetBits(GPIOB, SEG_dig_2 | SEG_dig_3 | SEG_dig_4);       // 끄기
    GPIO_SetBits(GPIOB, SEG_dig_1);                                 // 켜기
}

void GPIO_4digit_segment_DIG_2(void)
{
    GPIO_ResetBits(GPIOB, SEG_dig_1 | SEG_dig_3 | SEG_dig_4);       
    GPIO_SetBits(GPIOB, SEG_dig_2);                                 
}

void GPIO_4digit_segment_DIG_3(void)
{
    GPIO_ResetBits(GPIOB, SEG_dig_1 | SEG_dig_2 | SEG_dig_4);       
    GPIO_SetBits(GPIOB, SEG_dig_3);                                 
}

void GPIO_4digit_segment_DIG_4(void)
{
    GPIO_ResetBits(GPIOB, SEG_dig_1 | SEG_dig_2 | SEG_dig_3);       
    GPIO_SetBits(GPIOB, SEG_dig_4);                                 
}
void GPIO_4digit_segment_DIG_off(void)
{
    GPIO_ResetBits(GPIOB, SEG_dig_1 | SEG_dig_2 | SEG_dig_3|SEG_dig_4);       // 모두 끄기
}