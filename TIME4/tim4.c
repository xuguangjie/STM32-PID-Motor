#include "tim4.h"
#include "usart1.h"
#include "pid.h"
#include "tim3.h"
#include "reportqt.h"


extern float target;
extern PID pid;
extern Error err;
void TIM4_Init(u16 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4时钟
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //开启定时器中
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;        //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);    

	TIM_Cmd(TIM4,ENABLE); //使能定时器    
}


void TIM4_IRQHandler(void)
{
	float i,count2;
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		count2 = (float)TIM2->CNT;
		i = PID_increment(count2,target,&err,&pid) ;
		Eoutput += i; 
		TIM_SetCompare1(TIM3,(int)Eoutput);	
		if(Eoutput<0) 
			Eoutput =0 ;
		else if(Eoutput>35000)
		{
			Eoutput = 35000;
		}
		// reportTemp_(count2) ;  

		
		
		printf("Eoutput:%.1f  cn2: %.1f \r\n",Eoutput,count2); 
		
		TIM2->CNT = 0; 
	} 
TIM_ClearITPendingBit(TIM4,TIM_IT_Update);    
}