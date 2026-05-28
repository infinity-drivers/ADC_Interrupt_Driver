#include "stm32f4xx_hal.h"
#include "adc_converter.h"
#include <stdbool.h>


uint32_t value=0, counter, count, btn, pin1;

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

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();


		GPIO_Init(GPIO_PIN_12, GPIOA, GPIO_MODE_IT_RISING, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP);

		GPIO_Init(GPIO_PIN_5, GPIOC, GPIO_MODE_IT_RISING, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP);

		NVIC_SetPriority(EXTI15_10_IRQn, 4 );
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		NVIC_SetPriority(EXTI9_5_IRQn, 3);
		NVIC_EnableIRQ(EXTI9_5_IRQn);

	//adc_start(0);

	while(1){
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		//HAL_Delay(1000);

		counter= pin1;
	}

}

void SysTick_Handler(void){
	HAL_IncTick();
}

void EXTI9_5_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);;
}

void EXTI15_10_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);;
}



void HAL_GPIO_EXTI_Callback(uint16_t pin){
	pin1=(uint32_t) pin;

	static uint32_t last_press_time=0;

	if(pin==GPIO_PIN_5){
		uint32_t now = HAL_GetTick();

			        if((now - last_press_time) > 20)
			        {

			            last_press_time = now;
			            btn=2;
			            adc_start(0);
			        }

	}
	else if(pin==GPIO_PIN_12){

		uint32_t now = HAL_GetTick();

		 if((now - last_press_time) > 20)
		{

		  last_press_time = now;
		  btn=0;
		  adc_off();
		  resetAll();

		}


	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc_init){
	//adc_start(0);
	value=adc_read()+30;
	count=value/372;


			resetAll();
			HAL_GPIO_WritePin(ports[count], pins[count], 1);


	//HAL_ADC_Start_IT(&adc_init);



}
void resetAll(){

	for(uint32_t i=0; i<12; i++){


		HAL_GPIO_WritePin(ports[i], pins[i], 0);
	}

}
