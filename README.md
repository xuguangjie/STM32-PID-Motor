# STM32-PID-Motor
使用STM32，通过PID增量式调节，来改变电机转速。
其中用到了几个定时器资源，TIM1,TIM3,TIM4 
TIM1、用作计数器功能
TIM4、用作周期（50ms）中断查询计数器数值。
TIM3、产生PWM方波

PID参数在TIM4中更新和计算。


12V直流减速电机。
PWM给35000 ，满量程   所以在50ms的定时器周期，计数器最高捕获到150 CNt 。
通过串口1，可以改变期望值。
所以就是0-150的转速  对应着 0-100% 

通过串口给单片机发送 50  则电机会运行到50cnt速度。
