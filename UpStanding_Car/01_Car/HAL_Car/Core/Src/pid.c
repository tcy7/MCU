#include "pid.h"
#include "encoder.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "motor.h"

//传感器数据变量
int Encoder_Left,Encoder_Right;
float pitch,roll,yaw;//姿态角
short gyrox,gyroy,gyroz;//原始数据角速度
short	aacx,aacy,aacz;//原始数据角加速度

//闭环控制中间变量
int Velocity_out,Vertical_out,Turn_out,
	Target_Speed,Target_turn,MOTO1,MOTO2;
float Med_Angle=3;

//调参
/*temp输出给电机7200~-7200，角度值几十度算Kp，gyrox角速度值最快到两三千算Kd*/
float Vertical_Kp,Vertical_Kd;		//Kp:0~1000、Kd:0~10
/*temp输出给角度环0~60，两个编码器相加满速约160算Kp,对于速度环根据工程经验一般Kp=200Ki*/
float Velocity_Kp,Velocity_Ki;		//Kp:0~1,Ki:
float Turn_Kp,Turn_Kd;
uint8_t stop;


extern TIM_HandleTypeDef htim2,htim4;


//角度环（直立环）PD控制（内环）保证小车不倒
//输入：期望角度、真实角度、陀螺仪角速度（位置求导）
int Vertical(float Med,float Angle,float gyro_Y)
{
	int temp;
	temp=Vertical_Kp*(Angle-Med)+Vertical_Kd*gyro_Y;//真实值减去期望值
	return temp;
}

//速度环PI控制（中环）控制小车前进后退速度输出目标倾角交给角度环
//输入：期望速度、左编码器、右编码器（速度通过编码器值反应），I项对速度误差求和
int Velocity(int Target,int encoder_L,int encoder_R)
{
	static int Err_LowOut,Err_S;
	static float a=0.7; //滤波系数
	int Err,temp;
	
	//计算偏差值
	Err=(encoder_L+encoder_R)-Target;
	//低通滤波（不完全微分），外环是通过编码器得到速度值信号可能存在毛刺，
	//其他通过MPU6050获得的数据不需要添加低通滤波是因为模块已经处理了信号
	Err_LowOut=(1-a)*Err+a*Err_LowOut;
	//积分
	Err_S+=Err_LowOut;
	//积分限幅(-20000~20000)
	Err_S=Err_S>20000?20000:(Err_S<(-20000)?(-20000):Err_S);
	if(stop==1)Err_S=0,stop=0;
	//速度环计算
	temp=Velocity_Kp*Err_LowOut+Velocity_Ki*Err_S;
	return temp;
}

//转向环PD控制（外环）输出左右轮差速叠加到电机控制上
//输入：角速度、角度值
int Turn(float gyro_Z,int Target_turn)
{
	int temp;
	temp=Turn_Kp*Target_turn+Turn_Kd*gyro_Z;
	return temp;
}

void Control(void) //每10ms调用一次
{
	int PWM_out;
	//读取编码器和陀螺仪的数据
	Encoder_Left=Read_Speed(&htim2);
	Encoder_Right=-Read_Speed(&htim4);
	mpu_dmp_get_data(&pitch,&roll,&yaw);
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
	MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
	
	//将数据写入PID控制器，计算出左右电机的转速值
	Velocity_out=Velocity(Target_Speed,Encoder_Left,Encoder_Right);
	Vertical_out=Vertical(Velocity_out+Med_Angle,roll,gyrox);
	Turn_out=Turn(gyroz,Target_turn);
	
	PWM_out=Vertical_out;
	MOTO1=PWM_out-Turn_out;
	MOTO2=PWM_out+Turn_out;
	
	Limit(&MOTO1,&MOTO2);
	Load(MOTO1,MOTO2);
}
