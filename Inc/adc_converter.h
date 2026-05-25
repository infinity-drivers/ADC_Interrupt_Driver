

#ifndef ADC_C_C
#define ADC_C_C

typedef  uint8_t bool;
extern ADC_HandleTypeDef adc_init;
void adc_start(bool mode);
uint8_t adc_read(void);
void ADC_Handle_IRQ(void);
#endif
