#include "timcont.h"


void TIM_1_2_CONT_Init(void)
{
	Cont_GPIO_Init();
	TIM1_Configuration();
	TIM2_Configuration(); 
}
void Cont_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//设置GPIO	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // Time base configuration
	TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
	TIM_SetCounter(TIM1, 0);
	TIM_Cmd(TIM1, ENABLE);
	
	
}

void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//配置TIMER2作为计数器
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); // Time base configuration
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
}
