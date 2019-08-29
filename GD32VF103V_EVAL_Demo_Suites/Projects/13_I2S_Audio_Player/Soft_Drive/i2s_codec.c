/*!
    \file  i2s_codec.c
    \brief I2S codec driver
    
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

#include <stdio.h>
#include "wave_data.h"
#include "i2s_codec.h"

wave_file_struct wave_struct;
uint16_t i2saudiofreq = 0;
__IO uint8_t headertab_index = 0;
uint32_t datastartaddr = 0;
__IO uint32_t audiodataindex = 0; 

/*!
    \brief      read uint data according to endianness
    \param[in]  nbrofbytes: number of read bytes
    \param[in]  bytesformat: littleendian or bigendian
    \param[out] none
    \retval     the uint data
*/
uint32_t read_unit(uint8_t nbrofbytes, endianness_enum bytesformat)
{
    uint32_t index = 0;
    uint32_t temp = 0;
    if(littleendian == bytesformat){
        for(index = 0; index < nbrofbytes; index++)
            temp |= AUDIOFILEADDRESS[headertab_index++] << (index * 8);
    }else{
        for(index = nbrofbytes; index != 0; index--)
            temp |= AUDIOFILEADDRESS[headertab_index++] << ((index-1) * 8);
    }
    return temp;
}

/*!
    \brief      wave audio file parsing function
    \param[in]  none
    \param[out] none
    \retval     errorcode_enum
*/
errorcode_enum codec_wave_parsing(void)
{
    uint32_t temp = 0;
    uint32_t extraformatbytes = 0; 
    /* initialize the headertab index variable */
    headertab_index = 0;
    /* read chunkid, must be 'riff' */
    if(CHUNKID != read_unit(4, bigendian))
        return(UNVALID_RIFF_ID);
    /* read the file length */
    wave_struct.riffchunksize = read_unit(4, littleendian);
    /* read the file format, must be 'wave' */
    if(FILEFORMAT != read_unit(4, bigendian))
        return(UNVALID_WAVE_FORMAT);
    /* read the format chunk, must be 'fmt' */
    if(FORMATID != read_unit(4, bigendian))
        return(UNVALID_FORMATCHUNK_ID);
    /* read the size of the 'fmt' data, must be 0x10 */
    if(FORMATCHUNKSIZE != read_unit(4, littleendian))
        extraformatbytes = 1;
    /* read the audio format, must be 0x01 (pcm) */
    wave_struct.formattag = read_unit(2, littleendian);
    if(WAVE_FORMAT_PCM != wave_struct.formattag)
        return(UNSUPPORETD_FORMATTAG);    
    /* read the number of channels: 0x02->stereo 0x01->mono */
    wave_struct.numchannels = read_unit(2, littleendian);
    /* read the sample rate */
    wave_struct.samplerate = read_unit(4, littleendian);
    /* update the i2s_audiofreq value according to the .wav file sample rate */
    if((wave_struct.samplerate < 8000) || (wave_struct.samplerate > 192000))
        return(UNSUPPORETD_SAMPLE_RATE);
    else
        i2saudiofreq = wave_struct.samplerate;  
    /* read the byte rate */
    wave_struct.byterate = read_unit(4, littleendian);
    /* read the block alignment */
    wave_struct.blockalign = read_unit(2, littleendian);
    /* read the number of bits per sample */
    wave_struct.bitspersample = read_unit(2, littleendian);
    if(BITS_PER_SAMPLE_16 != wave_struct.bitspersample)
        return(UNSUPPORETD_BITS_PER_SAMPLE);
    /* if there are extra format bytes, these bytes will be defined in "fact chunk" */
    if(1 == extraformatbytes){
        /* read th extra format bytes, must be 0x00 */
        if(0x00 != read_unit(2, littleendian))
            return(UNSUPPORETD_EXTRAFORMATBYTES);
        /* read the fact chunk, must be 'fact' */
        if(FACTID != read_unit(4, bigendian))
            return(UNVALID_FACTCHUNK_ID);
        /* read fact chunk data size */
        temp = read_unit(4, littleendian);
        /* set the index to start reading just after the header end */
        headertab_index += temp;
    }
    /* read the data chunk, must be 'data' */
    if(DATAID != read_unit(4, bigendian))
        return(UNVALID_DATACHUNK_ID);
    /* read the number of sample data */
    wave_struct.datasize = read_unit(4, littleendian);
    /* set the data pointer at the beginning of the effective audio data */
    datastartaddr += headertab_index;
    
    return(VALID_WAVE_FILE);
}

/*!
    \brief      I2S configuration function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2s_config()
{
    /* enable the GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOB); 
    rcu_periph_clock_enable(RCU_GPIOC);
    /* enable I2S1 clock */
    rcu_periph_clock_enable(RCU_SPI1);

    /* I2S1_WS(PB12), I2S1_CK(PB13), I2S1_SD(PB15) GPIO pin configuration */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15);
    /* I2S1_MCK(PC6) GPIO pin configuration */
    gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

    spi_i2s_deinit(SPI1);

    /* I2S1 peripheral configuration */
    i2s_psc_config(SPI1, i2saudiofreq, I2S_FRAMEFORMAT_DT16B_CH16B, I2S_MCLKOUTPUT);
    i2s_init(SPI1, I2S_MODE_MASTERTX, I2S_STANDARD, I2S_CKPL_HIGH);
    /* enable the I2S1 peripheral */
    i2s_enable(SPI1); 
}

/*!
    \brief      I2S data send
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2s_audio_data_send(void)
{
    /* send the data read from the memory */
    spi_i2s_data_transmit(SPI1, read_half_word(audiodataindex+datastartaddr));
    /* increment the index */
    audiodataindex += (uint32_t)wave_struct.numchannels ;
}

/*!
    \brief      I2S audio play
    \param[in]  none
    \param[out] none
    \retval     errorcode_enum
*/
errorcode_enum i2s_audio_play(void)
{
    errorcode_enum errorcode = UNVALID_RIFF_ID; 
    /* read the audio file to extract the audio frequency */
    errorcode = codec_wave_parsing();
    if(VALID_WAVE_FILE == errorcode){
        i2s_config(); 
        /* enable the I2S1 TBE interrupt */ 
        spi_i2s_interrupt_enable(SPI1, SPI_I2S_INT_TBE);
    }
    return errorcode;
}            

/*!
    \brief      read half word
    \param[in]  offset : audio data index
    \param[out] none
    \retval     audio data
*/
uint16_t read_half_word(uint32_t offset)
{   
    static  uint32_t monovar = 0, tmpvar = 0;
    if((AUDIOFILEADDRESS + offset) >= AUDIOFILEADDRESSEND)
        audiodataindex = 0;
    /* test if the left channel is to be sent */
    if(0 == monovar){
        tmpvar = (*(__IO uint16_t *)(AUDIOFILEADDRESS + offset));
        /* increment the mono variable only if the file is in mono format */
        if(CHANNEL_MONO == wave_struct.numchannels)
            /* increment the monovar variable */
            monovar++;
        /* return the read value */
        return tmpvar;
    /* right channel to be sent in mono format */
    }else{
        /* reset the monovar variable */
        monovar = 0;
        /* return the previous read data in mono format */
        return tmpvar;
    }
}
