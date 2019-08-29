/*!
    \file  i2s_codec.h
    \brief the header file of I2S codec driver
    
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

#ifndef I2S_CODEC_H
#define I2S_CODEC_H

/* .WAV file format :

  Endian      Offset      Length      Contents
  big         0           4 bytes     'RIFF'              0x52494646
  little      4           4 bytes     <file length - 8>
  big         8           4 bytes     'WAVE'              0x57415645

  Next, the fmt chunk describes the sample format:

  big         12          4 bytes     'fmt '              0x666D7420
  little      16          4 bytes     0x00000010          length of the fmt data (16 bytes)
  little      20          2 bytes     0x0001              format tag: 1 = PCM
  little      22          2 bytes     <channels>          channels: 1 = mono, 2 = stereo
  little      24          4 bytes     <sample rate>       samples per second: e.g., 22050
  little      28          4 bytes     <bytes/second>      sample rate * block align
  little      32          2 bytes     <block align>       channels * bits/sample / 8
  little      34          2 bytes     <bits/sample>       8 or 16

  Finally, the data chunk contains the sample data:

  big         36          4 bytes     'data'              0x64617461
  little      40          4 bytes     <length of the data block>
  little      44          *           <sample data>

*/

#include "gd32vf103.h"

/* extern audio file */
extern const char wavetestdata[];

#define COUNTOF(a)          (sizeof(a) / sizeof(*(a)))

/* constants definitions */
/* audio parsing constants */
#define CHUNKID             0x52494646  /* correspond to the letters 'RIFF' */
#define FILEFORMAT          0x57415645  /* correspond to the letters 'WAVE' */
#define FORMATID            0x666D7420  /* correspond to the letters 'fmt ' */
#define DATAID              0x64617461  /* correspond to the letters 'data' */
#define FACTID              0x66616374  /* correspond to the letters 'fact' */
#define WAVE_FORMAT_PCM     0x01        /* pcm format */
#define FORMATCHUNKSIZE     0x10        /* format chunk size */
#define CHANNEL_MONO        0x01        /* mono channel */
#define CHANNEL_STEREO      0x02        /* stereo channel */
#define BITS_PER_SAMPLE_8   8           /* 8 bits per sample */
#define BITS_PER_SAMPLE_16  16          /* 16 bits per sample */
/* audio start address and end address constants */
#define AUDIOFILEADDRESS       (uint32_t)wavetestdata                                /* audio start address */
#define AUDIOFILEADDRESSEND    (uint32_t)(wavetestdata + (COUNTOF(wavetestdata)))    /* audio end address */
/* I2S configuration parameters */
#define I2S_STANDARD                  I2S_STD_MSB         /* I2S MSB standard */
#define I2S_MCLKOUTPUT                I2S_MCKOUT_ENABLE   /* mck output enable */

/* audio file information structure */
typedef struct
{
    uint32_t riffchunksize;             /* riff chunk size */
    uint16_t formattag;                 /* format tag */
    uint16_t numchannels;               /* number of channel */
    uint32_t samplerate;                /* audio sample rate */
    uint32_t byterate;                  /* byte rate */
    uint16_t blockalign;                /* block align */
    uint16_t bitspersample;             /* bits per sample */
    uint32_t datasize;                  /* audio data size */
}wave_file_struct;

/* error identification enum */
typedef enum
{
    VALID_WAVE_FILE = 0,                /* valid wave file */
    UNVALID_RIFF_ID,                    /* unvalid riff id */
    UNVALID_WAVE_FORMAT,                /* unvalid wave format */
    UNVALID_FORMATCHUNK_ID,             /* unvalid format chunk id */
    UNSUPPORETD_FORMATTAG,              /* unsupporetd format tag */
    UNSUPPORETD_NUMBER_OF_CHANNEL,      /* unsupporetd number of channel */
    UNSUPPORETD_SAMPLE_RATE,            /* unsupporetd sample rate */
    UNSUPPORETD_BITS_PER_SAMPLE,        /* unsupporetd bits per sample */
    UNVALID_DATACHUNK_ID,               /* unvalid data chunk id */
    UNSUPPORETD_EXTRAFORMATBYTES,       /* unsupporetd extra format bytes */
    UNVALID_FACTCHUNK_ID                /* unvalid fact chunk id */
}errorcode_enum;

/* endianness enum */
typedef enum
{
    littleendian,                       /* little endian */
    bigendian                           /* big endian */
}endianness_enum;

/* function declarations */

/* read uint data according to endianness */
uint32_t read_unit(uint8_t nbrofbytes, endianness_enum bytesformat);
/* wave audio file parsing function */
errorcode_enum codec_wave_parsing(void);
/* configure I2S GPIO and parameters */
void i2s_config(void);
/* send audio data */
void i2s_audio_data_send(void);
/* start audio paly */
errorcode_enum i2s_audio_play(void);
/* read half word */
uint16_t read_half_word(uint32_t offset);

#endif /* I2S_CODEC_H */
