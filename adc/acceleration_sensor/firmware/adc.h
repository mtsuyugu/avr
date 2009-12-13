#ifndef ADC_H
#define ADC_H

#define NUM_ADPORT 3

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2
#define AXIS_MAX 2
#define NEXT_AXIS 0xff

extern uint8_t now_in_measure;
void adc_init();
void adc_start(uint8_t i);
void adc_stop(void);
uint16_t adc_get_raw_value();
uint16_t adc_get_value(uint8_t i);

#endif /* ADC_H */
