# STM32-PID-Motor
使用STM32，通过PID增量式调节，来改变电机转速。
其中用到了几个定时器资源，TIM1,TIM3,TIM4 
TIM1、用作计数器功能
TIM4、用作周期（50ms）中断查询计数器数值。
TIM3、产生PWM方波

PID参数在TIM4中更新和计算。
