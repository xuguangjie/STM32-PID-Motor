#include "tim3.h"


void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,   ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);  //使能GPIO外设时钟使能
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);  //使能GPIO外设时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,   ENABLE);  //使能GPIO外设时钟使能  
                                                                 	
	TIM_DeInit(TIM3);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
/*	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); */
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);//完全重映射 

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/*CH1*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH预装载使能	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	/*CH2*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH预装载使能	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	/*CH3*/
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
//	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH预装载使能	
//	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
//	/*CH4*/
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH预装载使能	
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
   

	TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE 主输出使能	
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM1
}