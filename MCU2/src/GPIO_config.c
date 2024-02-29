#include "stm32f10x.h"
//#include "SPI_define.h"
/*
    GPIO 설정에 관련된 코드들을 함수화하여 나타낸 c파일
*/
void GPIO_Configuration(void)
{
    /////////////////////////seg/////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_seg;
    GPIO_InitStructure_seg.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_7;
    GPIO_InitStructure_seg.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure_seg.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure_seg);
    
    GPIO_InitStructure_seg.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6;
    GPIO_InitStructure_seg.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure_seg.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure_seg);

    //////////////////////////LED///////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_LED;   
    GPIO_InitStructure_LED.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure_LED.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure_LED);
    
    
    
    /////////////////////////PWM//////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_PWM;                             //DC motor PWM
    GPIO_InitStructure_PWM.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_AF_PP;		            // AFIO설정
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_PWM);			                // B포트설정
 
    GPIO_InitStructure_PWM.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_Out_PP;		            // AFIO설정
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_PWM);			                // B포트설정
    
    
    ////////////////////KEY/////////////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_KEY;
    GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
    GPIO_Init(GPIOA, &GPIO_InitStructure_KEY);

    
    ////////////////////Sensor/////////////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure_Sensor;
    GPIO_InitStructure_Sensor.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure_Sensor.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
    GPIO_Init(GPIOB, &GPIO_InitStructure_Sensor);
    

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
    GPIO_InitStructure_USART3.GPIO_Pin   = GPIO_Pin_10;               //GPIO_USART_Tx_Pin;//GPIO_Pin_9
    GPIO_InitStructure_USART3.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure_USART3.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);                       //GPIO_USART = GPIOA
    // Configure USARTx_Rx as input floating 
    GPIO_InitStructure_USART3.GPIO_Pin  = GPIO_Pin_11;                  //GPIO_USART_Rx_Pin;//GPIO_Pin_10
    GPIO_InitStructure_USART3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);
    
  
  
 
    
    
    
    // LED //   // LED //   // LED //   // LED //
    // LED //   // LED //   // LED //   // LED //
    // LED //   // LED //   // LED //   // LED //
    // LED //   // LED //   // LED //   // LED //
    // LED //   // LED //   // LED //   // LED //



    // 구조체 선언
   /* GPIO_InitTypeDef GPIO_InitStructure_LED;
    

    GPIO_InitStructure_LED.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;// | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure_LED.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_LED.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure_LED);
    */
    



    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
/*
    GPIO_InitTypeDef GPIO_InitStructure_PWM;

    GPIO_InitStructure_PWM.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	// PB6, PB7 -> motor PWM
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_AF_PP;		// AFIO설정
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_PWM);			// B포트설정

    // enable 10,11, direction 12,13
    GPIO_InitStructure_PWM.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
    GPIO_InitStructure_PWM.GPIO_Mode = GPIO_Mode_Out_PP;					//얘는 GPIO
    GPIO_InitStructure_PWM.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_PWM);

*/    
    
    
    
    
    
    // USART1 //   // USART1 //   // USART1 //   // USART1 //
    // USART1 //   // USART1 //   // USART1 //   // USART1 //
    // USART1 //   // USART1 //   // USART1 //   // USART1 //
    // USART1 //   // USART1 //   // USART1 //   // USART1 //
    // USART1 //   // USART1 //   // USART1 //   // USART1 //
    
    
/*    GPIO_InitTypeDef GPIO_InitStructure_USART1;
    
    /* Configure USARTx_Tx as alternate function push-pull */
/*    GPIO_InitStructure_USART1.GPIO_Pin   = GPIO_Pin_9;//GPIO_USART_Tx_Pin;      //GPIO_Pin_9
    GPIO_InitStructure_USART1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure_USART1.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure_USART1);             //GPIO_USART = GPIOA

    /* Configure USARTx_Rx as input floating */
 /*   GPIO_InitStructure_USART1.GPIO_Pin  = GPIO_Pin_10;//GPIO_USART_Rx_Pin;       //GPIO_Pin_10
    GPIO_InitStructure_USART1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure_USART1);
   
    
    
    
    
    // USART3 //   // USART3 //   // USART3 //   // USART3 //
    // USART3 //   // USART3 //   // USART3 //   // USART3 //
    // USART3 //   // USART3 //   // USART3 //   // USART3 //
    // USART3 //   // USART3 //   // USART3 //   // USART3 //
    // USART3 //   // USART3 //   // USART3 //   // USART3 //
    
    
    GPIO_InitTypeDef GPIO_InitStructure_USART3;
    
    // Configure USARTx_Tx as alternate function push-pull 
 /*   GPIO_InitStructure_USART3.GPIO_Pin   = GPIO_Pin_10;//GPIO_USART_Tx_Pin;      //GPIO_Pin_9
    GPIO_InitStructure_USART3.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure_USART3.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);             //GPIO_USART = GPIOA

    // Configure USARTx_Rx as input floating 
    GPIO_InitStructure_USART3.GPIO_Pin  = GPIO_Pin_11;//GPIO_USART_Rx_Pin;       //GPIO_Pin_10
    GPIO_InitStructure_USART3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure_USART3);
 */   
    
    
    
    
    
    
    // KEY //   // KEY //   // KEY //   // KEY //
    // KEY //   // KEY //   // KEY //   // KEY //
    // KEY //   // KEY //   // KEY //   // KEY //
    // KEY //   // KEY //   // KEY //   // KEY //
    // KEY //   // KEY //   // KEY //   // KEY //

/*    GPIO_InitTypeDef GPIO_InitStructure_KEY;

    GPIO_InitStructure_KEY.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7;
    GPIO_InitStructure_KEY.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
    GPIO_Init(GPIOA, &GPIO_InitStructure_KEY);			
*/


    
    // SPI //   // SPI //   // SPI //   // SPI //
    // SPI //   // SPI //   // SPI //   // SPI //
    // SPI //   // SPI //   // SPI //   // SPI //
    // SPI //   // SPI //   // SPI //   // SPI //
    // SPI //   // SPI //   // SPI //   // SPI //
    
/*    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure SPIy pins: SCK, MISO and MOSI */	//SCK는 PA5, MISO는 PA6, MOSI는 PA7
/*    GPIO_InitStructure.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MISO | SPIy_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//SPIy_PIN_SCK = GPIO_Pin_5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//AFIO
    GPIO_Init(SPIy_GPIO, &GPIO_InitStructure);		//SPIy_GPIO = PORTA

    /* Configure SPIz pins: SCK, MISO and MOSI */	//SCK는 PB13, MISO는 PB14, MOSI는 PB15
/*    GPIO_InitStructure.GPIO_Pin = SPIz_PIN_SCK | SPIz_PIN_MISO | SPIz_PIN_MOSI;
    GPIO_Init(SPIz_GPIO, &GPIO_InitStructure);		//SPIz_GPIO = PORTB
							//얘도 위에설정한 AFIO 사용됨.
*/
    ////////////////////KEYPAD////////////////////////

    
    
    
    
}