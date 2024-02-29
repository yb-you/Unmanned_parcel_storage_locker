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
//////////////////////////////////////////////////////////////////////////////////////////
#define LCD16X2_RCC_GPIO_CONTROL	RCC_APB2Periph_GPIOC
#define LCD16X2_GPIO_CONTROL			GPIOC
#define LCD16X2_GPIO_RS						GPIOC
#define LCD16X2_GPIO_RW						GPIOC
#define LCD16X2_GPIO_EN						GPIOC
// LCD data lines (must be on the same port)
#define LCD16X2_RCC_GPIO_DATA			RCC_APB2Periph_GPIOC
#define LCD16X2_GPIO_DATA					GPIOC
#define LCD16X2_GPIO_D4						GPIOC
#define LCD16X2_GPIO_D5						GPIOC
#define LCD16X2_GPIO_D6						GPIOC
#define LCD16X2_GPIO_D7						GPIOC
// Pin definition
#define LCD16X2_PIN_RS	GPIO_Pin_0
#define LCD16X2_PIN_RW	GPIO_Pin_1
#define LCD16X2_PIN_EN	GPIO_Pin_2
#define LCD16X2_PIN_D4	GPIO_Pin_4		// 4-bit mode LSB
#define LCD16X2_PIN_D5	GPIO_Pin_5
#define LCD16X2_PIN_D6	GPIO_Pin_6
#define LCD16X2_PIN_D7	GPIO_Pin_7		// 4-bit mode MSB

// Display size ------------------------------------------------------------ 
// Number of visible lines of the display (1 or 2)
#define LCD16X2_LINES					2
// Visible characters per line of the display
#define LCD16X2_DISP_LENGTH		16
// DDRAM address of first char of line 1
#define LCD16X2_START_LINE_1	0x00
// DDRAM address of first char of line 2
#define LCD16X2_START_LINE_2	0x40

// Delay value ------------------------------------------------------------- 
// Delay power on
#define LCD16X2_DELAY_POWER_ON   		16000
// Delay after initialize 8-bit
#define LCD16X2_DELAY_INIT      		5000
// Delay after initialize 8-bit repeated
#define LCD16X2_DELAY_INIT_REP    	64
// Delay after set 4-bit mode
#define LCD16X2_DELAY_INIT_4BIT   	64
// Delay until address counter updated after busy flag is cleared
#define LCD16X2_DELAY_BUSY_FLAG    	4
// Enable pulse width high level
#define LCD16X2_DELAY_ENABLE_PULSE	2

// Instructions bit location ----------------------------------------------- 
#define LCD16X2_CLEAR_DISPLAY					0x01
#define LCD16X2_CURSOR_HOME						0x02
#define LCD16X2_CHARACTER_ENTRY_MODE	0x04
#define LCD16X2_DISPLAY_CURSOR_ON_OFF	0x08
#define LCD16X2_DISPLAY_CURSOR_SHIFT 	0x10
#define LCD16X2_FUNCTION_SET					0x20
#define LCD16X2_SET_CGRAM_ADDRESS	 		0x40
#define LCD16X2_SET_DDRAM_ADDRESS	 		0x80
// Character entry mode instructions 
#define LCD16X2_INCREMENT							0x02	// Initialization setting
#define LCD16X2_DECREMENT							0x00
#define LCD16X2_DISPLAY_SHIFT_ON			0x01
#define LCD16X2_DISPLAY_SHIFT_OFF			0x00	// Initialization setting
// Display cursor on off instructions 
#define LCD16X2_DISPLAY_ON	 					0x04
#define LCD16X2_DISPLAY_OFF	 					0x00	// Initialization setting
#define LCD16X2_CURSOR_UNDERLINE_ON	 	0x02
#define LCD16X2_CURSOR_UNDERLINE_OFF	0x00	// Initialization setting
#define LCD16X2_CURSOR_BLINK_ON	 			0x01
#define LCD16X2_CURSOR_BLINK_OFF	 		0x00	// Initialization setting
// Display cursor shift instructions 
#define LCD16X2_DISPLAY_SHIFT					0x08
#define LCD16X2_CURSOR_MOVE						0x00
#define LCD16X2_RIGHT_SHIFT						0x04
#define LCD16X2_LEFT_SHIFT						0x00
// Function set instructions 
#define LCD16X2_8BIT_INTERFACE				0x10	// Initialization setting
#define LCD16X2_4BIT_INTERFACE				0x00
#define LCD16X2_2LINE_MODE						0x08
#define LCD16X2_1LINE_MODE						0x00	// Initialization setting
#define LCD16X2_5X10DOT_FORMAT				0x04
#define LCD16X2_5X7DOT_FORMAT					0x00	// Initialization setting
// Busy flag bit location 
#define LCD16X2_BUSY_FLAG							0x80

// LCD display and cursor attributes --------------------------------------- 
#define LCD16X2_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF	(LCD16X2_DISPLAY_OFF | \
	LCD16X2_CURSOR_UNDERLINE_OFF | LCD16X2_CURSOR_BLINK_OFF)
#define LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF		(LCD16X2_DISPLAY_ON | \
	LCD16X2_CURSOR_UNDERLINE_OFF | LCD16X2_CURSOR_BLINK_OFF)					
#define LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_ON		(LCD16X2_DISPLAY_ON | \
	LCD16X2_CURSOR_UNDERLINE_OFF | LCD16X2_CURSOR_BLINK_ON)
#define LCD16X2_DISPLAY_ON_CURSOR_ON_BLINK_OFF		(LCD16X2_DISPLAY_ON | \
	LCD16X2_CURSOR_UNDERLINE_ON | LCD16X2_CURSOR_BLINK_OFF)
#define LCD16X2_DISPLAY_ON_CURSOR_ON_BLINK_ON		(LCD16X2_DISPLAY_ON | \
	LCD16X2_CURSOR_UNDERLINE_ON | LCD16X2_CURSOR_BLINK_ON)

// Public function prototypes ---------------------------------------------- ///
///////////////////////////////////////////////////////////////////////////////
uint8_t custom_char[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F };

////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;


void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM_Configuration(void);
void EXTI_Configuration(void);
void USART1_Configuration(); //Printf�� ���
void USART3_Configuration();
//////////////////////////////door_lock.c////////////
void door_lock(int locking);
//////////////////////////////ketpad.c//////////////
void Keypad_password(void);
void Key_in_Room(uint8_t Key);
void password_in(uint8_t Key);
void new_password_in(uint8_t Key);
void new_password_in2(uint8_t Key);
void password_change(void);
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

//int a;
//int m=0;
//int position;
//int motor_speed=0;
uint8_t locking;                //����� ���� ����
uint8_t lock;
//int count_seg;
//bool motor_on=false;
//int usart3_start;
int main(void)
{
    //RCC �ʱ�ȭ

    
    DelayInit();	
	// LCD initialization
	
	// Create custom char
	lcd16x2_create_custom_char(0, custom_char);
	
    SystemInit();
    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();
    TIM_Configuration();
    EXTI_Configuration();
    USART1_Configuration();
    USART3_Configuration();
    locking=0;

    lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
    

    while(1)
        {
            delay_m();
           /* while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
                USART_SendData(USART3, 0);*/
            if(locking==0)                      //������� ���� ���
                {Keypad_password();}                            //Ű�е�� �� ȣ��, ��й�ȣ �Է�
            else if(locking==1)                 //������� ���� ���
                password_change();                              //Ű�е�� �� ��й�ȣ ����
            
            door_lock(locking);                 //����� ��� �Լ�
            

           
       }
}