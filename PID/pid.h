#ifndef __PID_H
#define __PID_H
#include <string.h>
#include <stdio.h>

extern float Eoutput ;   //输出值
extern float target;      //期望
extern float current;     //当前


typedef struct PID PID;
typedef struct Error Error;
struct PID
{
 float Kp;
 float Ki;
 float Kd;
};
struct Error
{
 float E0;  
 float E1;
 float E2;
};


void PIDInit (PID *pp,Error* err);
float PID_increment(float current,float target,Error* err, PID *pid) ;

#endif

