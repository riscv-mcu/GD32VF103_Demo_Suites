/*!
    \file  main.c
    \brief EXMC LCD demo
    
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
#include "gd32vf103v_lcd_eval.h"
#include "touch_panel.h"
#include "picture.h"
#include "systick.h"
#include <stdio.h>

uint16_t a1=20;
uint16_t a2=120;
uint16_t a3=220;
uint16_t b1=10;
uint16_t b2=100;
uint16_t b3=200;
uint16_t device_code;
uint8_t error_string[]="Please press the button!";
extern uint16_t touch_ad_x,touch_ad_y;
char_format_struct char_format;

/* turn on the LED according the pressed button */
void turn_on_led(uint8_t button_id);
/* get the touch area */
void get_touch_area(uint16_t x,uint16_t y,uint16_t *num_array);
/* find the position of max value in array */
uint8_t find_max(uint16_t* num_array);
/* change the picture of LED */
void change_picture(uint8_t button_id);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    uint16_t i;
    uint16_t num[4]={0,0,0,0}; /* store the touch point number on four buttons */
    uint8_t count=0;
    uint8_t led_string[4][4]={"LED1","LED2","LED3","LED4"};
    uint8_t button_id=0;
    
    /* initialize LEDs */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
    gd_eval_led_init(LED4);
    
    /* configure the EXMC access mode */
    exmc_lcd_init();

    /* configure the GPIO of SPI touch panel */
    touch_panel_gpio_configure();

    delay_1ms(50);  

    /* read the LCD controller device code:(0x8989) */
    device_code = lcd_register_read(0x0000);

    /* initialize the LCD */
    lcd_init();

    /* clear the LCD screen */
    lcd_clear(LCD_COLOR_WHITE);

    /* draw the picture of Gigadevice logo */
    /* if you don't want to draw the picture, you should modify the macro on
       the line 422th of picture.c file and comment the next line */
    lcd_picture_draw(40,200,40+160-1,200+87-1,(uint16_t *)(picture + BMP_HEADSIZE));

    /* draw a rectangle */
    lcd_rectangle_draw(10,10,230,310,LCD_COLOR_BLUE);

    /* configure char format */
    char_format.char_color = LCD_COLOR_BLUE;
    char_format.bk_color = LCD_COLOR_WHITE;
    char_format.direction = CHAR_DIRECTION_VERTICAL;
    char_format.font = CHAR_FONT_8_16;
    
    /* draw character on LCD screen */
    for (i = 0; i < 4; i++){
        lcd_char_display((a1+35+8*i), b1+20, *(led_string[0]+i), char_format);
        lcd_char_display((a2+35+8*i), b1+20, *(led_string[1]+i), char_format);
        lcd_char_display((a1+35+8*i), b2+20, *(led_string[2]+i), char_format);
        lcd_char_display((a2+35+8*i), b2+20, *(led_string[3]+i), char_format);
    }
    
    /* draw picture of button on LCD screen */
    lcd_picture_draw(a1+30,b1+40,a1+30+40-1,b1+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a2+30,b1+40,a2+30+40-1,b1+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a1+30,b2+40,a1+30+40-1,b2+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a2+30,b2+40,a2+30+40-1,b2+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));

    while(1){
        /* get the position of touch on LCD screen */
        if(SUCCESS == touch_scan()){
            count++;
            get_touch_area(touch_coordinate_x_get(touch_ad_x),(LCD_Y - touch_coordinate_y_get(touch_ad_y)),num);
        }
        /*  generate response to the touch(turn on LED and change picture )*/
        if(count==20){
            button_id = find_max(num);
            turn_on_led(button_id);
            change_picture(button_id);
            num[0]=num[1]=num[2]=num[3]=0;
            count=0;
        }
    }
}


/*!
    \brief      find the position of max value in array
    \param[in]  none
    \param[out] none
    \retval     the position of max value in num_array array
*/
uint8_t find_max(uint16_t* num_array)
{
    int id;
    id=0;
    if(num_array[id]<num_array[1]){
        id=1;
    }
    if(num_array[id]<num_array[2]){
        id=2;
    }
    if(num_array[id]<num_array[3]){
        id=3;
    }
    if(num_array[id]==0){
        id=4;
    }
    return id;
}

/*!
    \brief      get the touch area
    \param[in]  x: the row-coordinate
    \param[in]  y: the column-coordinate
    \param[out] num_array: touch area array pointer
    \retval     none
*/
void get_touch_area(uint16_t x,uint16_t y,uint16_t *num_array)
{
      if((x<a1+70)&&(x>a1+30)&&(y>b1+30)&&(y<b1+70)){
          num_array[0]++;
      }else if((x<a2+70)&&(x>a2+30)&&(y>b1+30)&&(y<b1+70)){
          num_array[1]++;
      }else if((x<a1+70)&&(x>a1+30)&&(y>b2+30)&&(y<b2+70)){
          num_array[2]++;
      }else if((x<a2+70)&&(x>a2+30)&&(y>b2+30)&&(y<b2+70)){
          num_array[3]++;
      }
}

/*!
    \brief      change the picture of LED
    \param[in]  button_id: the id of button you just pressed
    \param[out] none
    \retval     none
*/
void change_picture(uint8_t button_id)
{
    uint8_t len_s;
    uint8_t *str;
    uint16_t i;
    
    /* draw picture on LCD screen */
    lcd_picture_draw(a1+30,b1+40,a1+30+40-1,b1+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a2+30,b1+40,a2+30+40-1,b1+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a1+30,b2+40,a1+30+40-1,b2+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    lcd_picture_draw(a2+30,b2+40,a2+30+40-1,b2+40+40-1,(uint16_t *)(image_off + BMP_HEADSIZE));
    /* draw character on LCD screen */
    len_s=sizeof(error_string)-1;
    str = error_string;
    
    char_format.char_color = LCD_COLOR_WHITE;
    for (i = 0; i < len_s; i++){
        lcd_char_display((30+8*i), 190, *str++, char_format);
    }
    
    switch(button_id){
        case 0:
            lcd_picture_draw(a1+30,b1+40,a1+30+40-1,b1+40+40-1,(uint16_t *)(image_on + BMP_HEADSIZE));
            break;
        case 1:
            lcd_picture_draw(a2+30,b1+40,a2+30+40-1,b1+40+40-1,(uint16_t *)(image_on + BMP_HEADSIZE));
            break;
        case 2:
            lcd_picture_draw(a1+30,b2+40,a1+30+40-1,b2+40+40-1,(uint16_t *)(image_on + BMP_HEADSIZE));
            break;
        case 3:
            lcd_picture_draw(a2+30,b2+40,a2+30+40-1,b2+40+40-1,(uint16_t *)(image_on + BMP_HEADSIZE));
            break;
        default:
            str = error_string;
            char_format.char_color = LCD_COLOR_RED;
            for (i = 0; i < len_s; i++){
                lcd_char_display((30+8*i), 190, *str++, char_format);
            }
            break;
    }
}

/*!
    \brief      turn on the LED according the pressed button
    \param[in]  button_id: the id of button you just pressed
    \param[out] none
    \retval     none
*/
void turn_on_led(uint8_t button_id)
{
    /* firstly,turn off all the LEDs */
    gd_eval_led_off(LED1);
    gd_eval_led_off(LED2);
    gd_eval_led_off(LED3);
    gd_eval_led_off(LED4);
    
    switch(button_id){
        case 0:
            gd_eval_led_on(LED1);  /*!< turn on LED2 only */
            break;
        case 1:
            gd_eval_led_on(LED2);  /*!< turn on LED3 only */
            break;
        case 2:
            gd_eval_led_on(LED3);  /*!< turn on LED4 only */
            break;
        case 3:
            gd_eval_led_on(LED4);  /*!< turn on LED5 only */
            break;
        default:
            /* turn on all the LEDs */
            gd_eval_led_on(LED1);
            gd_eval_led_on(LED2);
            gd_eval_led_on(LED3);
            gd_eval_led_on(LED4);
            break;
    }
}
