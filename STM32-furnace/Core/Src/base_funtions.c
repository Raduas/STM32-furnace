/*
 * base_funtions.c
 *
 *  Created on: Aug 23, 2025
 *      Author: dolra
 */
#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;

void allPWMStart(void) {
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_Base_Start_IT(&htim7);
	  HAL_TIM_Base_Start_IT(&htim8);
}

void allPWMStop(void){
	  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_Base_Stop_IT(&htim7);
	  HAL_TIM_Base_Stop_IT(&htim8);
}
void buckPWMStart(void){
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_Base_Start_IT(&htim7);
	  HAL_TIM_Base_Start_IT(&htim8);
}

void buckPWMStop(void){
	  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	  HAL_TIM_Base_Stop_IT(&htim7);
	  HAL_TIM_Base_Stop_IT(&htim8);
}
