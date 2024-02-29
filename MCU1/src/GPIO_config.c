#include "stm32f10x.h"
/*
    GPIO 설정에 관련된 코드들을 함수화하여 나타낸 c파일
*/
void GPIO_Configuration(void)
{
    ///////////////////////////KEYPAD///////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_KEYPAD_COL;			                //KEYPAD_COL(Output)
    GPIO_InitStructure_KEYPAD_COL.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;       
    GPIO_InitStructure_KEYPAD_COL.GPIO_Speed = GPIO_Speed_50MHz;	                    //최대 스피드 선택
    GPIO_InitStructure_KEYPAD_COL.GPIO_Mode  = GPIO_Mode_Out_PP;	                    //Output 모드 선택   
    GPIO_Init(GPIOC, &GPIO_InitStructure_KEYPAD_COL);			                // GPIO_InitStructure_KEYPAD_COL 구조체의 셋팅 내용을 GPIOC로 입력   

    GPIO_InitTypeDef GPIO_InitStructure_KEYPAD_ROW;			                //KEYPAD_ROW(Input)
    GPIO_InitStructure_KEYPAD_ROW.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
    GPIO_InitStructure_KEYPAD_ROW.GPIO_Mode  = GPIO_Mode_IN_FLOATING;          //Input 모드 선택.   
    GPIO_Init(GPIOA, &GPIO_InitStructure_KEYPAD_ROW);			                // GPIO_InitStructure_KEYPAD_ROW 구조체의 셋팅 내용을 GPIOA로 입력
    


    /////////////////////////lcd//////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_lcd;
    GPIO_InitStructure_lcd.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure_lcd.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure_lcd.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure_lcd);
    


    //////////////////////////LED///////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_LED;   
    GPIO_InitStructure_LED.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure_LED.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_LED);
    
    
    
    /////////////////////////PWM//////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_PWM;                             
    GPIO_InitStructure_PWM.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;            //buzzer,servo
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_AF_PP;		            // AFIO설정
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_PWM);			                // B포트설정



    ////////////////////////USART1///////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_USART1;   
    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure_USART1.GPIO_Pin   = GPIO_Pin_9;               //GPIO_USART_Tx_Pin;//GPIO_Pin_9
    GPIO_InitStructure_USART1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure_USART1.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure_USART1);                       //GPIO_USART = GPIOA
    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure_USART1.GPIO_Pin  = GPIO_Pin_10;                  //GPIO_USART_Rx_Pin;//GPIO_Pin_10
    GPIO_InitStructure_USART1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure_USART1);
  


    //////////////////////USART3///////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_USART3;   
    // Configure USARTx_Tx as alternate function push-pull 
    GPIO_InitStructure_USART3.GPIO_Pin   = GPIO_Pin_10;               //GPIO_USART_Tx_Pin;//GPIO_Pin_10
    GPIO_InitStructure_USART3.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure_USART3.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);                       //GPIO_USART = GPIOA
    // Configure USARTx_Rx as input floating 
    GPIO_InitStructure_USART3.GPIO_Pin  = GPIO_Pin_11;                  //GPIO_USART_Rx_Pin;//GPIO_Pin_11
    GPIO_InitStructure_USART3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);
  
  
  
    ////////////////////KEY/////////////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_KEY;
    GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
    GPIO_Init(GPIOA, &GPIO_InitStructure_KEY);  
    
       
    
}