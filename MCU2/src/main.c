#include "stm32f10x.h"
//#include "SPI_define.h"     // SPI1, SPI2를 쉽게 사용할 수 있도록 정의한 부분
//#include "USART_define.h"

#include <stdio.h>
/*
    현 프로젝트는 USART3의 Tx, Rx를 이용한 자가통신 구현 프로젝트이다.
    USART3도 SPI와 마찬가지로 Serial 통신으로, Tx, Rx로 구현되어있다.
    다만 SPI와 다르게 Master/Slave 구조가 아니기 때문에 MISO, MOSI의 Pin이 존재하지 않고 Tx, Rx의 Pin만 존재한다.
     (이전 SPI통신은 SPIy(Master), SPIz(Slave)의 통신으로, USART로 치면 USART1, USART3 사이의 통신이였다. 하지만 현 프로젝트에서는 USART3 하나를 이용한 통신 방식으로 구현되었다.)
*/

// TIM
//////////////////////////////////////////////////////////
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;


void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM_Configuration(void);
void EXTI_Configuration(void);
void USART1_Configuration(); //Printf에 사용
void USART3_Configuration();
//////////////////////////////////segment.c//////////////
void GPIO_4digit_segment_0(void);
void GPIO_4digit_segment_1(void);
void GPIO_4digit_segment_2(void);
void GPIO_4digit_segment_3(void);
void GPIO_4digit_segment_4(void);
void GPIO_4digit_segment_5(void);
void GPIO_4digit_segment_6(void);
void GPIO_4digit_segment_7(void);
void GPIO_4digit_segment_8(void);
void GPIO_4digit_segment_9(void);
void GPIO_4digit_segment_DIG_1(void);
void GPIO_4digit_segment_DIG_2(void);
void GPIO_4digit_segment_DIG_3(void);
void GPIO_4digit_segment_DIG_4(void);
void SEG(int num);
///////////////////////////////////sensor.c//////////////////
void sensor(void);
//void SPIy_Master_Configuration(void);
//void SPIz_Slave_Configuration(void);

///////////////////////////////////////////////
// 각 채널의 Pulse 입력을 위한 변수. CCR1~4의 1~4는 PWM 출력 신호의 채널을 뜻함.
uint16_t CCR1_Val = 0;
uint16_t CCR2_Val = 0;
uint16_t CCR3_Val = 0;
uint16_t CCR4_Val = 0;

// 모터 스피드를 조절하기 위해 CCRx_Val에 대입할 변수
//int m_speed[9] = {0, 10,20,30,40,50,60,70,80,90,100};
/////////////////////////////////////////////////////
// USART 통신에 사용할 변수 데이터
uint8_t Send_data = 11;
uint8_t Receive_data = 0;
int position;

int motor_on;
int usart_seg1;
int usart_seg2;
int usart_seg3;
int usart_seg4;
int usart_num;

int usart_PS1;
int usart_PS2;
int usart_PS3;
int usart_PS4;
int usart_PS_num;
int count;
int main(void)
{
    //RCC 초기화
    SystemInit();
    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();
    TIM_Configuration();
    EXTI_Configuration();
    USART1_Configuration();
    USART3_Configuration();
    

    while(1)
        {
           sensor();                 //적외선센서 사용
            //while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);    // 3. RXNE는 RX Not Empty로, USART3 Rx의 Tmp 공간에 값이 들어왔는지 확인한다.      
            Receive_data = USART_ReceiveData(USART3);
            //printf("Receive_data=%d\n",Receive_data);
            printf("Received data is %d\n", Receive_data);
            if(Receive_data!=0)                                    //전송 받을경우
                {   usart_data(Receive_data);   Receive_data=0;}
        }
}