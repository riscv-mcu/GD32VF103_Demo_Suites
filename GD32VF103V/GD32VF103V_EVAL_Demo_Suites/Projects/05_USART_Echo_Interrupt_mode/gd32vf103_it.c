/*!
    \file  gd32f10x_it.c
    \brief interrupt service routines

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

#include "gd32vf103_it.h"
#include "systick.h"

#define tx_buffer_size   (countof(tx_buffer))
#define countof(a) (sizeof(a)/sizeof(*(a)))
extern uint8_t   tx_buffer[];
extern uint8_t   rx_buffer[] ;
extern uint32_t  nbr_data_to_read, nbr_data_to_send;
extern uint16_t  tx_counter, rx_counter;

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)){
        /* read one byte from the receive data register */
        rx_buffer[rx_counter++] = (uint8_t)usart_data_receive(USART0);

        if(rx_counter >= nbr_data_to_read)
        {
            /* disable the USART0 receive interrupt */
            usart_interrupt_disable(USART0, USART_INT_RBNE);
        }
    }
       
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE)){
        /* write one byte to the transmit data register */
        usart_data_transmit(USART0, tx_buffer[tx_counter++]);

        if(tx_counter >= nbr_data_to_send)
        {
            /* disable the USART0 transmit interrupt */
            usart_interrupt_disable(USART0, USART_INT_TBE);
        }
    }
}
