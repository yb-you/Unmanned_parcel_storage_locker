#include "stm32f10x.h"
//#include "SPI_define.h"     // SPI1, SPI2�� ���� ����� �� �ֵ��� ������ �κ�
//#include "USART_define.h"

#include <stdio.h>
/*
    �� ������Ʈ�� USART3�� Tx, Rx�� �̿��� �ڰ���� ���� ������Ʈ�̴�.
    USART3�� SPI�� ���������� Serial �������, Tx, Rx�� �����Ǿ��ִ�.
    �ٸ� SPI�� �ٸ��� Master/Slave ������ �ƴϱ� ������ MISO, MOSI�� Pin�� �������� �ʰ� Tx, Rx�� Pin�� �����Ѵ�.
     (���� SPI����� SPIy(Master), SPIz(Slave)�� �������, USART�� ġ�� USART1, USART3 ������ ����̿���. ������ �� ������Ʈ������ USART3 �ϳ��� �̿��� ��� ������� �����Ǿ���.)
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
void USART1_Configuration(); //Printf�� ���
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
// �� ä���� Pulse �Է��� ���� ����. CCR1~4�� 1~4�� PWM ��� ��ȣ�� ä���� ����.
uint16_t CCR1_Val = 0;
uint16_t CCR2_Val = 0;
uint16_t CCR3_Val = 0;
uint16_t CCR4_Val = 0;

// ���� ���ǵ带 �����ϱ� ���� CCRx_Val�� ������ ����
//int m_speed[9] = {0, 10,20,30,40,50,60,70,80,90,100};
/////////////////////////////////////////////////////
// USART ��ſ� ����� ���� ������
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
    //RCC �ʱ�ȭ
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
           sensor();                 //���ܼ����� ���
            //while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);    // 3. RXNE�� RX Not Empty��, USART3 Rx�� Tmp ������ ���� ���Դ��� Ȯ���Ѵ�.      
            Receive_data = USART_ReceiveData(USART3);
            //printf("Receive_data=%d\n",Receive_data);
            printf("Received data is %d\n", Receive_data);
            if(Receive_data!=0)                                    //���� �������
                {   usart_data(Receive_data);   Receive_data=0;}
        }
}