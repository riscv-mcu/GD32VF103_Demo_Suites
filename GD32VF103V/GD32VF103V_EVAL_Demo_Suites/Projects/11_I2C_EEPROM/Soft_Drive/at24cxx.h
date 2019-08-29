/*!
    \file  at24cxx.h
    \brief the header file of AT24Cxx
    
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

#ifndef AT24CXX_H
#define AT24CXX_H

#include "gd32vf103.h"

#define EEP_FIRST_PAGE         0x00

#define I2C_OK                 0
#define I2C_FAIL               1

/* I2C read and write functions */
uint8_t i2c_24c02_test(void);
/* initialize EEPROM address */
void i2c_eeprom_init(void);
/* write one byte to the EEPROM */
void eeprom_byte_write(uint8_t* p_buffer, uint8_t write_address);
/* write more than one byte to the EEPROM */
void eeprom_page_write(uint8_t* p_buffer, uint8_t write_address, uint8_t number_of_byte);
/* write buffer of data to the EEPROM */
void eeprom_buffer_write(uint8_t* p_buffer, uint8_t write_address, uint16_t number_of_byte);
/* read data from the EEPROM */
void eeprom_buffer_read(uint8_t* p_buffer, uint8_t read_address, uint16_t number_of_byte);
/* wait for EEPROM standby state */
void eeprom_wait_standby_state(void);

#endif  /* AT24CXX_H */
