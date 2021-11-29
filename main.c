#include "led.h"
#include "delay.h"
#include "bitband.h"
#include "pwm.h"
#include "usart1.h" 
#include "timcont.h" 
#include "tim3.h"
#include "tim4.h"
#include "pid.h"

PID pid;
Error err;



int main(void)
{
	u16 count1= 0;
	u16 count2= 0;	
	int i = 0,q,len,t;
		int led0pwmval=1500;    
	int r1,r2,r3,r4,r5;
	u8 dir=1;	
	led_init();
	delay_init();
	uart_init(115200);
	TIM_1_2_CONT_Init();  
	TIM4_Init(500,7199);
	TIM3_PWM_Init(35999,0);
	//400-2500
	TIM_SetCompare2(TIM3,0);

	PIDInit ( &pid ,&err);  
//	printf("     Main  init   \r\n");	
	while(1)
	{
		LED = !LED; 

		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;
		//	printf("消息长度len:%d  \r\n",len);
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);
			} 
			r1 =(int)USART_RX_BUF[0]-'0';  
			r2=	(int)USART_RX_BUF[1]-'0';
			r3=	(int)USART_RX_BUF[2]-'0';
			r4=	(int)USART_RX_BUF[3]-'0';
			r5=	(int)USART_RX_BUF[4]-'0';
			if(len==3)
			{
					led0pwmval = r1*100+r2*10+r3*1;
					if(led0pwmval>=70)
					{
						led0pwmval = 70;
					}
					target = (float)led0pwmval;
			}
			else if(len ==2)
			{
					led0pwmval = r1*10+r2;
					if(led0pwmval>=70)
					{
						led0pwmval = 70;
					}
					target = (float)led0pwmval;
			}
			
			//else if(len ==5)
			//{
					//led0pwmval = r1*10000+r2*1000+r3*100+r4*10+r5;
			//}
			//TIM_SetCompare1(TIM3,led0pwmval);	   
			//printf("\r\nled0pwmval:%d\r\n",led0pwmval);
			
			USART_RX_STA=0;
		}
	}
}







