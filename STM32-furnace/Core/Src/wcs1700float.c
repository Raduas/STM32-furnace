/*
 * wcs1700.c
 *
 *  Created on: Jun 12, 2025
 *      Author: dolra
 */


#include <wcs1700float.h>
#include <base_funtions.h>


static ADC_HandleTypeDef *adc = NULL;
float calibrationConstant_mV = 0.0f;
static float calcArray[WCS1700_NUM_SAMPLES];

static float getAverage(float *array) {
    float sum = 0.0f;
    for (uint8_t i = 0; i < WCS1700_NUM_SAMPLES; i++) {
        sum += array[i];
    }
    return sum / WCS1700_NUM_SAMPLES;
}

static float readAdcMillivolts(void) {
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = WCS1700_ADC_CHANNEL;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    HAL_ADC_ConfigChannel(adc, &sConfig);

    HAL_ADC_Start(adc);
    HAL_ADC_PollForConversion(adc,20); // HAL_MAX_DELAY

    uint16_t raw = HAL_ADC_GetValue(adc);
    HAL_ADC_Stop(adc);

    return ((float)raw * WCS1700_SUPPLY_VOLTAGE_MV) / WCS1700_ADC_RESOLUTION;
}

void WCS1700float_Init(ADC_HandleTypeDef *adc_handle) {
    adc = adc_handle;
}

void WCS1700float_Calibrate(void) {
    for (uint8_t i = 0; i < WCS1700_NUM_SAMPLES; i++) {
        calcArray[i] = readAdcMillivolts();
        HAL_Delay(1);
    }
    calibrationConstant_mV = getAverage(calcArray);
}
void WCS1700float_ReCalibrate(void) {
	buckPWMStart();
	HAL_Delay(500);
    for (uint16_t i = 0; i < WCS1700_NUM_SAMPLES; i++) {
        calcArray[i] = readAdcMillivolts();
        HAL_Delay(1);
    }
    buckPWMStop();
    calibrationConstant_mV = getAverage(calcArray);
}
float WCS1700float_ReadCurrent_A(void) {
    for (uint8_t i = 0; i < WCS1700_NUM_SAMPLES; i++) {
        float mV = readAdcMillivolts();
        calcArray[i] =mV - calibrationConstant_mV;//calcArray[i] = (mV > calibrationConstant_mV) ? (mV - calibrationConstant_mV) : 0.0f;
    }
    float average_mV = getAverage(calcArray);
    return average_mV / WCS1700_SENSOR_RESOLUTION;  // výstup v Ampérech
}
void ReadCurrent_Flow(float *mV) {
	float measured_mV = readAdcMillivolts();
    *mV = (1.0f - f_KOEF_PROUD) * (*mV) + f_KOEF_PROUD * measured_mV;
}

float frommV2A(float *mV) {
	///(milivoltage, amps)
	// Odečteme offset (nulový proud), ochrana proti záporným hodnotám
	float delta_mV = (*mV > calibrationConstant_mV) ? (*mV - calibrationConstant_mV) : 0.0f;
    return  delta_mV / WCS1700_SENSOR_RESOLUTION; // Převod mV na A
}

/*float Fake_Amps(void) {
	//float mV = readAdcMillivolts();
    float duty = (float)__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1) / __HAL_TIM_GET_AUTORELOAD(&htim3);
    float f_Vout = 325.0f * duty; // simulované napětí buck konvertoru
    float R_load = 2.0f;          // simulovaná odporová zátěž v ohmech
    return f_Vout / R_load;       // Ohmův zákon
}*/

