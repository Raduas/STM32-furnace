/*
 * wcs1700.h
 *
 *  Created on: Jun 12, 2025
 *      Author: dolra
 */

#ifndef INC_WCS1700float_H_
#define INC_WCS1700float_H_

#include "stm32f4xx_hal.h"

#define WCS1700_ADC_CHANNEL        ADC_CHANNEL_1
#define WCS1700_NUM_SAMPLES        100
#define WCS1700_SUPPLY_VOLTAGE_MV  3300.0f
#define WCS1700_ADC_RESOLUTION     4095.0f
#define WCS1700_SENSOR_RESOLUTION  30.0f // mV per Ampere
#define f_KOEF_PROUD               0.3f  // Nová váha

extern float calibrationConstant_mV;

void WCS1700float_Init(ADC_HandleTypeDef *adc_handle);
void WCS1700float_Calibrate(void);
float WCS1700float_ReadCurrent_A(void);  // změna návratového typu na float v Ampérech
void ReadCurrent_Flow(float *mV);
float frommV2A(float *mV);
#endif /* INC_WCS1700_H_ */
