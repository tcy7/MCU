#include "stm32f10x.h"                  // Device header
#include "Motor.h"

void Car_Init(){
	Motor_Init();
}

void Car_ForWard(){
	LeftMotor_Speed(60);
	RightMotor_Speed(60);
}
void Car_BackWard(){
	LeftMotor_Speed(-60);
	RightMotor_Speed(-50);
}
void Car_TurnLeft(){
	LeftMotor_Speed(0);
	RightMotor_Speed(50);
}
void Car_TurnRight(){
	LeftMotor_Speed(50);
	RightMotor_Speed(0);
}
void Car_Stop(){
	LeftMotor_Speed(0);
	RightMotor_Speed(0);
}
//顺时针转
void Car_Clockwise(){
	LeftMotor_Speed(50);
	RightMotor_Speed(-50);
}
//逆时针转
void Car_CounterClockwise(){
	LeftMotor_Speed(-50);
	RightMotor_Speed(50);
}

