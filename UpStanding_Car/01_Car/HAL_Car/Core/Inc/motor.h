#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"

void Load(int moto1,int moto2);			//-7200~7200
void Limit(int *motoA,int *motoB);

#endif 
