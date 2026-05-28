

#ifndef ADC_C_C
#define ADC_C_C

typedef  uint8_t bool;
extern ADC_HandleTypeDef adc_init;
extern GPIO_InitTypeDef gpio_strt;
void adc_start(bool mode);
void adc_off();
uint8_t adc_read(void);
void GPIO_Init(uint16_t pin, GPIO_TypeDef* port, uint32_t mode, uint32_t freq, uint32_t pull);
void ADC_IRQHandler(void);
#endif
