#include "stm32f10x.h"

// 1Clock의 주기 = (prescaler + 1) / 72MHz
// 1Clock의 주파수 = 1 / 1Clock의 주기
// n초 : 1초 = x clock : 1 clock
// x clock = n * 1Clock의 주파수

TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure_PWM;
TIM_OCInitTypeDef           TIM_OCInitStructure_PWM;

void TIM_Configuration(void)
{
    // Time base configuration 
    // 입력은 72,000,000MHz이다. Prescaler(59999+1)로 나누면 1200이 된다. 즉, 1초에 1200번의 신호가 오는 1200Hz가 된다.
    // 이때 신호의 주기를 1200 신호로 잡아주면 1초에 1번 타이머 신호를 받게되게끔 구현이 가능하므로 주기를 1200으로 잡아준다.(1199 + 1)
    // 이를 두 개로 나눈 이유는 TIM_Prescaler가 16비트의 크기이기 때문에 65535 이상의 값을 넣을 수 없기에 Prescaler, Period의 개념으로 나누어 계산한다.
    TIM_TimeBaseStructure.TIM_Period = 1200;                      // 1(1.2): 약 0.001초
    TIM_TimeBaseStructure.TIM_Prescaler = 65535;                 // 0~59999 이므로 60000 (0xEA5F = 59999)

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // 현재 예제에서는 필요 없는 부분. tDTS를 구하기 위한 부분이다.
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // 다음에 지정하는 부분이 counter를 증가하는 방향으로 할지, 감소하는 방향으로 할지를 정하는 부분.
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;         // Advanced-control timer인 TIM1, TIM8이 아닌경우에는 필요가 없음.
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    TIM_TimeBaseStructure.TIM_Period = 40;                       // 40: 0.033초
    TIM_TimeBaseStructure.TIM_Prescaler = 59999;                  // 0~59999 이므로 60000

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // 현재 예제에서는 필요 없는 부분. tDTS를 구하기 위한 부분이다.
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   // 다음에 지정하는 부분이 counter를 증가하는 방향으로 할지, 감소하는 방향으로 할지를 정하는 부분.
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;         // Advanced-control timer인 TIM1, TIM8이 아닌경우에는 필요가 없음.
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
    // TIM2 enable counter 
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
  
    // 해당 코드는 현재 예제에서는 없어도 무관.
    TIM_PrescalerConfig(TIM2, 0xEA5F, TIM_PSCReloadMode_Immediate);
    TIM_PrescalerConfig(TIM3, 0xEA5F, TIM_PSCReloadMode_Immediate);

    // Clear TIM update pending flag
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

    // TIM IT enable 
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);










    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    // PWM //   // PWM //   // PWM //   // PWM //
    //서보모터는 PWM주기 20ms필요 -> 주파수=1/20ms=50Hz
    TIM_TimeBaseStructure_PWM.TIM_Period = 19999;       //1Mhz 입력에서 주기 20000으로 나누면 50Hz가 된다.
    TIM_TimeBaseStructure_PWM.TIM_Prescaler = 72;       //Prescaler가 72이면 1MHz가 된다.
    TIM_TimeBaseStructure_PWM.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure_PWM.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure_PWM);

   
    // PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure_PWM.TIM_OCMode = TIM_OCMode_PWM1;   //CCMR레지스터(Capture/compare mode register)
                                                            //TIMx_CCRM1, TIMx_CCRM2 두 종류가 있다.
                                                            //CCMR1이 채널1,2(CH1,CH2. 즉 OC1Init, OC2Init)담당. CCMR2가 채널3,4(CH3,CH4. 즉 OC3Init, OC4Init)담당이다.
                                                            //또한 OC는 Output Channel, IC는 Input Channel의 뜻으로, TIM_OCMode는 기본적으로 Output.

    TIM_OCInitStructure_PWM.TIM_OutputState = TIM_OutputState_Enable;	//CCER레지스터(Capture/compare enable register)
                                                                        //말 그대로 output을 enable해줌.

    TIM_OCInitStructure_PWM.TIM_Pulse = 1500;//CCR1_Val;		//CCR은 캡쳐/비교 레지스터
                                                            //Channel마다 다르게 설정한 CCRx_Val을 저장.(CCR저장)
                                                            //저장되는 값은 TIMx_CCRx에 저장.

    TIM_OCInitStructure_PWM.TIM_OCPolarity = TIM_OCPolarity_High;	//CCER레지스터(Captuer/compare enable register) 셋팅
    TIM_OC1Init(TIM4, &TIM_OCInitStructure_PWM);			        //TIM4를 위에 설정한 OC?와 연결
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);

    // TIM4 enable counter 
    TIM_Cmd(TIM4, ENABLE);
}
