/*!
    \file  main.c
    \brief ADC conversion triggered by timer

    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32vf103.h"
#include "gd32vf103v_eval.h"
#include "gd32vf103v_lcd_eval.h"
#include "systick.h"

#define BOARD_ADC_CHANNEL           ADC_CHANNEL_13
#define ADC_GPIO_PORT               GPIOC
#define ADC_GPIO_PIN                GPIO_PIN_3
#define X_START 2
#define Y_START 10
#define Y_DEALT 20

uint8_t gd_companyname_string[]={"GigaDevice Semiconductor Inc."} ;
uint8_t gd_mcu_string[]={" -- GD32VF103 Series MCU -- "} ;
uint8_t gd_evalboard_string[]={"       GD32V103V_EAVL      "} ;
uint8_t gd_demoname_string[]={"   ADC triggered by TIMER  "} ;
uint8_t gd_operation_tip_string[]={"  Please adjust the VR1 !  "} ;
uint16_t device_code;
char_format_struct char_format;
__IO uint16_t ad_value[220];

void test_display_init(void);
void diaplay_adc_value(void);
void flash_led(int times);
void rcu_config(void);
void gpio_config(void);
void dma_config(void);
void adc_config(void);
void timer_config(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* init test status led */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
    gd_eval_led_init(LED4);
    /* flash led for test */
    flash_led(3);

    /* system clocks configuration */
    rcu_config();
    /* GPIO configuration */
    gpio_config();
    /* DMA configuration */
    dma_config();
    /* ADC configuration */
    adc_config();
    /* RCU configuration */
    timer_config();

    /* configure the EXMC access mode */
    exmc_lcd_init();
    /* read the LCD Controller device code:(0x8989) */
    device_code = lcd_register_read(0x0000);
    /* initialize the LCD */
    lcd_init();
    /* clear the LCD screen */
    lcd_clear(LCD_COLOR_WHITE);
    /* LCD content initialize */
    test_display_init();

    while(1){
        /* TIMER1 counter enable */
        timer_enable(TIMER1);

        /* test on channel1 transfer complete flag */
        while( !dma_flag_get(DMA0,DMA_CH0, DMA_FLAG_FTF));
        /* clear channel1 transfer complete flag */
        dma_flag_clear(DMA0,DMA_CH0, DMA_FLAG_FTF);

        /* TIMER1 counter disable */
        timer_disable(TIMER1);

        diaplay_adc_value();
    }
}

/*!
    \brief      LCD content initialize
    \param[in]  none
    \param[out] none
    \retval     none
*/
void test_display_init( void )
{
    int i;

    /* configure char format */
    char_format.char_color = LCD_COLOR_BLUE;
    char_format.bk_color = LCD_COLOR_WHITE;
    char_format.direction = CHAR_DIRECTION_VERTICAL;
    char_format.font = CHAR_FONT_8_16;

    /* draw character on LCD screen */
    for(i = 0; i < sizeof(gd_companyname_string)-1; i++){
        lcd_char_display((X_START+8*i), Y_START+0*Y_DEALT, *(gd_companyname_string+i),char_format);
    }

    for(i = 0; i < sizeof(gd_mcu_string)-1; i++){
        lcd_char_display((X_START+8*i), Y_START+1*Y_DEALT, *(gd_mcu_string+i),char_format);
    }

    for(i = 0; i < sizeof(gd_evalboard_string)-1; i++){
        lcd_char_display((X_START+8*i), Y_START+2*Y_DEALT, *(gd_evalboard_string+i),char_format);
    }

    for(i = 0; i < sizeof(gd_demoname_string)-1; i++){
        lcd_char_display((X_START+8*i), Y_START+3*Y_DEALT, *(gd_demoname_string+i),char_format);
    }

    for(i = 0; i < sizeof(gd_operation_tip_string)-1; i++){
        lcd_char_display((X_START+8*i), Y_START+4*Y_DEALT, *(gd_operation_tip_string+i),char_format);
    }

    lcd_hline_draw(X_START+6,110,310,LCD_COLOR_BLUE,1);
    lcd_vline_draw(X_START+6,X_START+6+220,310,LCD_COLOR_BLUE,1);

    for(i = 0;i < 4;i ++){
        lcd_vline_draw(X_START+6-4,X_START+6,110+i*50,LCD_COLOR_BLUE,1);
    }

    for(i = 0;i < 4;i ++){
        lcd_vline_draw(X_START+6-4,X_START+6,110+25+i*50,LCD_COLOR_BLUE,1);
    }
}

/*!
    \brief      display ADC value
    \param[in]  none
    \param[out] none
    \retval     none
*/
void diaplay_adc_value(void)
{
    int ix,iy,i;
    int deta = 200 /4 * 3.3;

    for(ix = X_START + 6 + 1,i = 0;ix < X_START + 6 +220;ix++,i++){
        for(iy = 130;iy < 310-1;iy++){
            if(iy == (310 - ad_value[ i ] * deta / 0x0FFF)){
                /* set the pixel */
            	lcd_point_set(ix,iy,LCD_COLOR_BLUE);         //lcd_point_set
            }else{
                /* set the pixel */
            	lcd_point_set(ix,iy,LCD_COLOR_WHITE);
            }
        }
    }
}


/*!
    \brief      test status led
    \param[in]  times: the flash times of leds
    \param[out] none
    \retval     none
*/
void flash_led(int times)
{
    int i;

    for(i = 0;i < times;i ++){
        /* insert 200 ms delay */
        delay_1ms(200);

        /* turn on led */
        gd_eval_led_on(LED1);
        gd_eval_led_on(LED2);
        gd_eval_led_on(LED3);
        gd_eval_led_on(LED4);

        /* insert 200 ms delay */
        delay_1ms(200);

        /* turn off led */
        gd_eval_led_off(LED1);
        gd_eval_led_off(LED2);
        gd_eval_led_off(LED3);
        gd_eval_led_off(LED4);
    }
}

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
    /* enable GPIOA clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC0);
    /* enable DMA0 clock */
    rcu_periph_clock_enable(RCU_DMA0);
    /* enable timer1 clock */
    rcu_periph_clock_enable(RCU_TIMER1);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8);
}

/*!
    \brief      configure the GPIO peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_config(void)
{
    /* config the GPIO as analog mode */
    gpio_init(ADC_GPIO_PORT, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, ADC_GPIO_PIN);
}

/*!
    \brief      configure the DMA peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void)
{
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;

    /* ADC DMA_channel configuration */
    dma_deinit(DMA0, DMA_CH0);

    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr  = (uint32_t)(&ADC_RDATA(ADC0));
    dma_data_parameter.periph_inc   = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr  = (uint32_t)(ad_value);
    dma_data_parameter.memory_inc   = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;
    dma_data_parameter.direction    = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number       = 220;
    dma_data_parameter.priority     = DMA_PRIORITY_HIGH;
    dma_init(DMA0, DMA_CH0, &dma_data_parameter);
    dma_circulation_enable(DMA0, DMA_CH0);

    /* enable DMA channel */
    dma_channel_enable(DMA0, DMA_CH0);
}

/*!
    \brief      configure the ADC peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_config(void)
{
    /* reset ADC */
    adc_deinit(ADC0);
    /* ADC mode config */
    adc_mode_config(ADC_MODE_FREE);
    /* ADC contineous function enable */
    adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);
    /* ADC scan mode disable */
    adc_special_function_config(ADC0, ADC_SCAN_MODE, DISABLE);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    /* ADC channel length config */
    adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 1);

    /* ADC regular channel config */
    adc_regular_channel_config(ADC0, 0, BOARD_ADC_CHANNEL, ADC_SAMPLETIME_55POINT5);
    /* ADC trigger config */
    adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_T1_CH1);
    adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

    /* enable ADC interface */
    adc_enable(ADC0);
    delay_1ms(1);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC0);

    /* ADC DMA function enable */
    adc_dma_mode_enable(ADC0);
}

/*!
    \brief      TIMER configuration function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void timer_config(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    timer_deinit(TIMER1);

    /* TIMER1 configuration */
    timer_initpara.prescaler         = 5;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 199;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);

    /* CH1 configuration in PWM mode1 */
    timer_channel_output_struct_para_init(&timer_ocintpara);
    timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);

    timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 100);
    timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM1);
    timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
}

