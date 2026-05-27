#include "stm32f4xx_hal.h"
#include "adc_converter.h"
#include <stdbool.h>


uint32_t value=0, counter, count;

uint16_t pins[12]={	GPIO_PIN_6, GPIO_PIN_10, GPIO_PIN_5, GPIO_PIN_10,
					GPIO_PIN_9, GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_7,
					GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_9, GPIO_PIN_8};

GPIO_TypeDef* ports[12]={	GPIOC, GPIOA, GPIOB, GPIOB,
							GPIOA, GPIOC, GPIOB, GPIOA,
							GPIOA, GPIOA, GPIOB, GPIOB	};

/*bool sets[12][12]={

		{1,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,1},

};*/

int main(){


	HAL_Init();
	adc_start(0);

	while(1){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		//HAL_Delay(1000);

		counter=count;
	}

}

void SysTick_Handler(void){
	HAL_IncTick();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc_init){
	adc_start(0);
	value=adc_read()+30;
	count=value/372;


			resetAll(count);
			HAL_GPIO_WritePin(ports[count], pins[count], 1);


	//HAL_ADC_Start_IT(&adc_init);



}
void resetAll(uint32_t skip){

	for(uint32_t i=0; i<12; i++){
		if(i==skip) continue;

		HAL_GPIO_WritePin(ports[i], pins[i], 0);
	}

}
