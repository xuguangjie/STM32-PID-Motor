#include "pid.h"


float Eoutput = 0;  //输出值
float target;      //期望
float current;     //当前

void PIDInit (PID *pp,Error* err)
{
	Eoutput = 10000;
	target = 50;
	current = 0;
		pp->Kp = 1000;
		pp->Ki = 10;
		pp->Kd = 0; 
	
		err->E0 = 0;
		err->E1 = 0;
		err->E2 = 0;
	

	
}

float PID_increment(float current,float target,Error* err, PID *pid) 
{
	float Err0;
	float increment;
	Err0 = target-current;
	increment = pid->Kp*(Err0-err->E1) + pid->Ki*Err0 + pid->Kd*(Err0-2*err->E1+err->E2);
		
	err->E2 = err->E1; 
	err->E1 = Err0;
	return increment;
}