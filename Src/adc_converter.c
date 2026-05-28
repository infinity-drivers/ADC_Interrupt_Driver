#include "stm32f4xx_hal.h"
//#include <stdbool.h>

GPIO_InitTypeDef gpio_strt;
ADC_HandleTypeDef adc_init;

typedef  uint8_t  bool;

void adc_on(bool mode);


uint32_t adc_read(void){
	  //HAL_ADC_PollForConversion(&adc_init, 1);
	return HAL_ADC_GetValue(&adc_init);

}

void adc_start(bool mode){
	adc_on(mode);
	HAL_ADC_Start_IT(&adc_init);

}

void adc_on(bool mode){

	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_Init(GPIO_PIN_0, GPIOA, GPIO_MODE_ANALOG, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_6, GPIOC, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_10, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_5, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_10, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_9, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_7, GPIOC, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_6, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_7, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_6, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_5, GPIOA, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_9, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
	GPIO_Init(GPIO_PIN_8, GPIOB, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);


	//GPIO_Init(GPIO_PIN_1, GPIOA, GPIO_MODE_ANALOG);


	ADC_ChannelConfTypeDef chconf={0};


	adc_init.Instance=ADC1;
	adc_init.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV2;
	adc_init.Init.Resolution=ADC_RESOLUTION_12B;

	if(mode==0){
		adc_init.Init.ContinuousConvMode=ENABLE;
	}
	else{
		adc_init.Init.ContinuousConvMode=DISABLE;
	}

	adc_init.Init.DiscontinuousConvMode=DISABLE;
	adc_init.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;
	adc_init.Init.ExternalTrigConv=ADC_SOFTWARE_START;
	adc_init.Init.DataAlign=ADC_DATAALIGN_RIGHT;
	adc_init.Init.NbrOfConversion=1;
	adc_init.Init.DMAContinuousRequests=DISABLE;
	adc_init.Init.EOCSelection=ADC_EOC_SINGLE_CONV;

	HAL_ADC_Init(&adc_init);

	chconf.Channel=ADC_CHANNEL_0;
	chconf.Rank=1;
	chconf.SamplingTime=ADC_SAMPLETIME_480CYCLES;

	HAL_ADC_ConfigChannel(&adc_init, &chconf);

	chconf.Channel=ADC_CHANNEL_1;
		chconf.Rank=2;
		chconf.SamplingTime=ADC_SAMPLETIME_480CYCLES;

		HAL_ADC_ConfigChannel(&adc_init, &chconf);

	NVIC_SetPriority(ADC_IRQn, 2);
	NVIC_EnableIRQ(ADC_IRQn);

}

void adc_off(){
	HAL_ADC_Stop_IT(&adc_init);
	HAL_ADC_DeInit(&adc_init);
}

void ADC_IRQHandler(void){

	HAL_ADC_IRQHandler(&adc_init);



}


void GPIO_Init(uint16_t pin, GPIO_TypeDef* port, uint32_t mode, uint32_t freq, uint32_t pull){

	gpio_strt.Mode=mode;
	gpio_strt.Pin=pin;
	gpio_strt.Pull=pull;
	gpio_strt.Speed=freq;
	HAL_GPIO_Init(port,  &gpio_strt);
}


/*void adc_s_init(void){

	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();



	gpio_strt.Mode=GPIO_MODE_ANALOG;
	gpio_strt.Pin=GPIO_PIN_0;
	gpio_strt.Pull=GPIO_NOPULL;
	gpio_strt.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_strt);

	ADC_ChannelConfTypeDef chconf={0};


	adc_init.Instance=ADC1;
	adc_init.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV2;
	adc_init.Init.Resolution=ADC_RESOLUTION_12B;
	adc_init.Init.ContinuousConvMode=DISABLE;
	adc_init.Init.DiscontinuousConvMode=DISABLE;
	adc_init.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;
	adc_init.Init.ExternalTrigConv=ADC_SOFTWARE_START;
	adc_init.Init.DataAlign=ADC_DATAALIGN_RIGHT;
	adc_init.Init.NbrOfConversion=1;
	adc_init.Init.DMAContinuousRequests=DISABLE;
	adc_init.Init.EOCSelection=ADC_EOC_SINGLE_CONV;

	HAL_ADC_Init(&adc_init);

	chconf.Channel=ADC_CHANNEL_0;
	chconf.Rank=1;
	chconf.SamplingTime=ADC_SAMPLETIME_480CYCLES;

	HAL_ADC_ConfigChannel(&adc_init, &chconf);

}*/
