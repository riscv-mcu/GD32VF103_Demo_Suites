/*!
    \file  main.c
    \brief RCU clock output
    
    \version 2019-6-5, V1.0.0, demo for GD32VF103
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
#include <stdio.h>

typedef enum
{
    CKOUT0_SYSTEMCLOCK_CKOUT = 0,
    CKOUT0_IRC8M_CKOUT = 1,
    CKOUT0_HXTAL_CKOUT = 2,
}clock_output_enum;

void all_led_init(void);
void all_led_off(void);
void clock_output_select(uint8_t seq);
void clock_output_config(void);

extern volatile uint8_t g_button_press_flag;

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    uint8_t func_seq = 0;

    /* initialize the USART */
    gd_eval_com_init(EVAL_COM0);

    printf("\r\n /=========== Gigadevice Clock output Demo ===========/ \r\n");
    printf("press key B to select clock output source \r\n");

    /* initialize the LEDs */
    all_led_init();
    /* initialize the clock output */
    clock_output_config();
    /* initialize the tamper key */
    gd_eval_key_init(KEY_B, KEY_MODE_EXTI);

    while (1){
        if(1 == g_button_press_flag){
            /* if the button is pressed */
            g_button_press_flag = 0;
            /* control the led */
            all_led_off();
            gd_eval_led_on((led_typedef_enum)func_seq);
            /* select the clock output mode */
            clock_output_select(func_seq);

            func_seq++;
            func_seq %= 3;
        }
    }
}

/*!
    \brief      initialize the LEDs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void all_led_init(void)
{
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
}

/*!
    \brief      all LEDs turn off
    \param[in]  none
    \param[out] none
    \retval     none
*/
void all_led_off(void)
{
    gd_eval_led_off(LED1);
    gd_eval_led_off(LED2);
    gd_eval_led_off(LED3);
}

/*!
    \brief      configure clock output function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void clock_output_config(void)
{
    /* peripheral clock enable */
    rcu_periph_clock_enable(RCU_GPIOA);

    rcu_osci_on(RCU_IRC8M);
    if(ERROR == rcu_osci_stab_wait(RCU_IRC8M)){
        printf("RCU_IRC8M rcu_osci_stab_wait timeout! \r\n");
        while(1);
    }

    /* configure clock output pin */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

/*!
    \brief      select type of clock output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void clock_output_select(uint8_t seq)
{
    switch(seq){
        case CKOUT0_SYSTEMCLOCK_CKOUT:
            rcu_ckout0_config(RCU_CKOUT0SRC_CKSYS);
            printf("CK_OUT0: system clock \r\n");
            break;
        case CKOUT0_IRC8M_CKOUT:
            rcu_ckout0_config(RCU_CKOUT0SRC_IRC8M);
            printf("CK_OUT0: IRC8M \r\n");
            break;
        case CKOUT0_HXTAL_CKOUT:
            rcu_ckout0_config(RCU_CKOUT0SRC_HXTAL);
            printf("CK_OUT0: HXTAL \r\n");
            break;

        default:
            printf("clock output select parameter error! \r\n");
            while(1);
    }
}
