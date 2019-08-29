/*!
    \file  main.c
    \brief use the I2C bus to write and read EEPROM
    
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
#include "systick.h"
#include <stdio.h>
#include "i2c.h"
#include "at24cxx.h"

uint8_t count=0;

void led_turn_on(uint8_t led_number);
void led_config(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* configure LEDs */
    led_config();
    
    /* configure USART */
    gd_eval_com_init(EVAL_COM0);

    printf("I2C-24C02 configured....\n\r");
    
    /* configure GPIO */
    gpio_config();
    
    /* configure I2C */
    i2c_config();
    
    /* initialize EEPROM */
    i2c_eeprom_init();

    printf("The I2C0 is hardware interface \n\r");
    printf("The speed is %d\n", I2C0_SPEED);
    
    if(I2C_OK == i2c_24c02_test()){
        while(1){
           /* turn off all LEDs */
           gd_eval_led_off(LED1);
           gd_eval_led_off(LED2);
           gd_eval_led_off(LED3);
           gd_eval_led_off(LED4);
           /* turn on a LED */
           led_turn_on(count%4);
           count++;
           if(count >= 4){
               count = 0;
           }
           delay_1ms(500);
        }
    }
    /* turn on all LEDs */
    gd_eval_led_on(LED1);
    gd_eval_led_on(LED2);
    gd_eval_led_on(LED3);
    gd_eval_led_on(LED4);
    
    while(1);
}

/*!
    \brief      configure the LEDs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_config(void)
{
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
    gd_eval_led_init(LED4);

    /* turn off LED1,LED2,LED3,LED4 */
    gd_eval_led_off(LED1);
    gd_eval_led_off(LED2);
    gd_eval_led_off(LED3);
    gd_eval_led_off(LED4);
}

/*!
    \brief      trun on a LED
    \param[in]  led_number
    \param[out] none
    \retval     none
*/
void led_turn_on(uint8_t led_number)
{
    switch(led_number){
    case 0:
      gd_eval_led_on(LED1); 
      break;
    case 1:
      gd_eval_led_on(LED2);  
      break;
    case 2:
      gd_eval_led_on(LED3);
      break;
    case 3:
      gd_eval_led_on(LED4);
      break; 
    default:
      gd_eval_led_on(LED1);
      gd_eval_led_on(LED2);
      gd_eval_led_on(LED3);
      gd_eval_led_on(LED4);
      break;
    }
}

