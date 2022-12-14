//
// Created by hhc on 2022/4/26.
//

#ifndef MAKEROBOT_MOTOR_H
#define MAKEROBOT_MOTOR_H

#include "tim.h"

typedef struct {
  int8_t x;
  int8_t y;
  int8_t z;
}carInfoType;

typedef struct {
  int16_t ENC;
  int16_t ADD;
  int16_t TGT;
  int16_t PWM;
  int16_t Velocity_KP;
  int16_t Velocity_KI;
  int16_t Bias;
  int16_t Last_bias;
}pidInfoType;

typedef struct {
  pidInfoType pidInfo;
  TIM_HandleTypeDef enc_htimx;
  TIM_HandleTypeDef pwm_htimx;
  uint16_t pwm_channel_x;
  GPIO_TypeDef *GPIOx_1;
  uint16_t GPIO_Pin_1;
  GPIO_TypeDef *GPIOx_2;
  uint16_t GPIO_Pin_2;
}motorInfoType;

void set_ENC(motorInfoType *motorInfo);
void set_ADD(motorInfoType *motorInfo);
void incremental_PI(motorInfoType *motorInfo);
void range_PWM(motorInfoType *motorInfo, int16_t amplitude);
void set_PWM(motorInfoType *motorInfo);
void init_motorInfo(motorInfoType *motorInfo, TIM_HandleTypeDef enc_htimx, TIM_HandleTypeDef pwm_htimx, uint16_t pwm_channel_x, GPIO_TypeDef *GPIOx_1, uint16_t GPIO_Pin_1, GPIO_TypeDef *GPIOx_2, uint16_t GPIO_Pin_2);
void Kinematic_Analysis_4(motorInfoType *motorInfoList, carInfoType *carInfo);
void start_motor(motorInfoType *motorInfoList, uint8_t len);
void motor_run(motorInfoType *motorInfoList, uint8_t len);

#endif //MAKEROBOT_MOTOR_H
