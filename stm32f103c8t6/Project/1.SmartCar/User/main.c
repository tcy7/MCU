#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Car.h"
#include "Infraredtrack.h"


int main(void)
{
	Car_Init();
	Infrared_Init();
	        
	while (1){
		//9左1 8左2 5右2 4右1
		//红外模块返回值0为白线1为黑线
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
			  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
		    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&
		    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_ForWard();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1){
					Car_Stop();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_ForWard();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_TurnLeft();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_TurnLeft();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_TurnLeft();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1){
					Car_TurnRight();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1){
					Car_TurnRight();
		}else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1&&
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0){
					Car_TurnRight();
		}
	}
}
