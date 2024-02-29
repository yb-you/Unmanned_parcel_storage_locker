#include "stm32f10x.h"

void RCC_Configuration(void) {
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//TIM2를 ENABLE,, TIM1만 APB2(~72MHz)이고 나머진 APB1(~36MHz)이다.
}							//만일 TIM2,3,4모두 ENABLE하려면
							//RCC_APB1...(RCC_APB1Periph_TIM2 | .. _TIM3 | .. _TIM4, ENALBE); 로 하면 됨.

void NVIC_Configuration(void){

//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//이건 아래 TIM들이 우선순위 넣을 때 사용한다.
								//아래는 우선순위가 0 하나이므로 안써도 되나
								//우선순위가 2종류면 ..Group_1, 4종류면 ...Group_2, ... Group_4까지 있다.)

NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;			//TIM2를 쓰므로 TIM2로 설정.
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//우선순위 0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//서브우선순위 0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//TIM2의 채널을 ENABLE시킴
NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){	//(안써도됨)이건 실습에있었음. 인터럽트 플래그 클리어
						//이걸쓰면 팬딩부분 TIM_IT_Update를 TIM_IT_CC1로 바꿔야함.

TIM_ClearITpendingBit(TIM2, TIM_IT_Update);	//ClearITpendingBit는 pending bit를 clear하기위해 사용.
						//TIM_IT_Update는 UIF(Update Interrupt Flag)를 1로 바꾸어주는 역할.
GPIO_SetBits(GPIOA, GPIO_Pin_4);		//명령어임, 이건 그냥 외부 LED 키는것.
}
}

void TIM_Configuration(void)
{

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;			//아래 사용될 구조체 부르는것 같음

TIM_TimeBaseStructure.TIM_Period = 0x4AF;			//타이머의 카운터가 0x4AF(1199)가 된 다음에 다시 0으로 돌아감.
								//타이머의 주기 설정임. (0, 1, 2, 3, ..., 1198, 1199, 0, 1, 2, ...)
								//주기 설정(기존 주기를 0x4AF주기당 1주기로 묶는것 (아래에서 72MHz(1초에 72M주기)를 1200Hz로(1초에 1200주기). 이제 1200주기를 1주기로 묶어 1주기에 1초되도록 셋팅.)
								//설정한 주기를 (TIMx_ARR에 저장; Auto-reload register). Counter의 값이 자동으로 재설정될 때 이 값으로 셋팅.
								//1초를 카운트하려면 이 값은 1200이여야한다.
								//그러나0x4AF는 1199이다. 이유는 0이 될 때부터 카운트를 시작하므로, 0~1199는 1200으로,

TIM_TimeBaseStructure.TIM_Prescaler = 0xEA5F;			//프리스케일러 설정(TIMx_PSC에 저장, 총16bit라서 72,000로 묶질 못함.(최대 약 65,000))
								//기존 72MHz(1초에 72M주기)를 60,000(0xEA5F + 0x1)씩 묶어 1200Hz(1초에 1200주기)로 바꾸는 것.
								//기본(CK_INT)72Mhz --> CK_PSC로 가져감(=CK_PSC도 72Mhz)
								//TIMx_PSC의 값(1199 = 0xEA5F)에 +1한 결과(1200)를 CK_PSC(72Mhz)에서 나누면 그 값이 CK_CNT에 공급됨(1초)
								//나눈 결과가 1200이 된다.
								//요약; 기존 CK_INT(72Mhz)를 CK_PSC로 가져옴 따라서 CK_PSC는 72MHz
								//요약2; CK_PSC(72Mhz)를 입력된 PSC값(0XEA5F+0x1 = 60,000)로 나누면
								//요약3; 즉, 72MHz(CK_PSC)를 60,000씩 묶으니 1200Hz(=CK_CNT)가 나온것.

TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//=0x0	//CKD : Clock division, digital filter등에 상요되는 sampling 클럭에 사용되는 tDTS를 구하기 위한 부분
								//CK_INT(72Mhz)기준으로 구하게 됨.
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//=0	//카운트를 +로 셀지, -로 셀지 결정
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;		//이건 TIM1, TIM8에서만 씀. 아무거나넣어도됨
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);			//위 설정을 TIM2에 적용
}