/*!
    \file  usbh_usr.c
    \brief user application layer for USBFS host-mode MSC class operation

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

#include <string.h>
#include "usbh_usr.h"
#include "drv_usb_hw.h"
#include "ff.h"
#include "usbh_msc_core.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bbb.h"

extern uint16_t LINE;
extern usb_core_driver usbh_msc_core;

FATFS fatfs;
FIL file;

uint8_t line_idx = 0;
uint8_t need_clear = 0;
uint8_t usbh_usr_application_state = USBH_USR_FS_INIT;
uint8_t WriteTextBuff[] = "GD32 Connectivity line Host Demo application using FAT_FS";

/*  points to the DEVICE_PROP structure of current device */
usbh_user_cb user_callback_funs =
{
    usbh_user_init,
    usbh_user_deinit,
    usbh_user_device_connected,
    usbh_user_device_reset,
    usbh_user_device_disconnected,
    usbh_user_over_current_detected,
    usbh_user_device_speed_detected,
    usbh_user_device_desc_available,
    usbh_user_device_address_assigned,
    usbh_user_configuration_descavailable,
    usbh_user_manufacturer_string,
    usbh_user_product_string,
    usbh_user_serialnum_string,
    usbh_user_enumeration_finish,
    usbh_user_userinput,
    usbh_usr_msc_application,
    usbh_user_device_not_supported,
    usbh_user_unrecovered_error
};

static uint8_t explore_disk     (char* path, uint8_t recu_level);
static void toggle_leds         (void);

/*!
    \brief      user operation for host-mode initialization
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_init(void)
{
    static uint8_t startup = 0U;

    if (0U == startup) {
        startup = 1U;

        /* configure the LED and KEY*/
        gd_eval_led_init(LED1);
        gd_eval_key_init(KEY_WAKEUP, KEY_MODE_GPIO);
    }
}

/*!
    \brief      user operation for device attached
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_device_connected(void)
{

}

/*!
    \brief      user operation when unrecoveredError happens
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_unrecovered_error (void)
{

}

/*!
    \brief      user operation for device disconnect event
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_device_disconnected (void)
{
    gd_eval_led_off(LED1);

}

/*!
    \brief      user operation for reset USB Device
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_device_reset(void)
{

}

/*!
    \brief      user operation for detectting device speed
    \param[in]  device_speed: device speed
    \param[out] none
    \retval     none
*/
void usbh_user_device_speed_detected(uint32_t device_speed)
{

}

/*!
    \brief      user operation when device descriptor is available
    \param[in]  device_desc: device descriptor
    \param[out] none
    \retval     none
*/
void usbh_user_device_desc_available(void *device_desc)
{

}

/*!
    \brief      usb device is successfully assigned the Address 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_device_address_assigned(void)
{
}

/*!
    \brief      user operation when configuration descriptor is available
    \param[in]  cfg_desc: pointer to configuration descriptor
    \param[in]  itf_desc: pointer to interface descriptor
    \param[in]  ep_desc: pointer to endpoint descriptor
    \param[out] none
    \retval     none
*/
void usbh_user_configuration_descavailable(usb_desc_config *cfg_desc,
                                          usb_desc_itf *itf_desc,
                                          usb_desc_ep *ep_desc)
{

}

/*!
    \brief      user operation when manufacturer string exists
    \param[in]  manufacturer_string: manufacturer string of usb device
    \param[out] none
    \retval     none
*/
void usbh_user_manufacturer_string(void *manufacturer_string)
{

}

/*!
    \brief      user operation when product string exists
    \param[in]  product_string: product string of usb device
    \param[out] none
    \retval     none
*/
void usbh_user_product_string(void *product_string)
{

}

/*!
    \brief      user operatin when serialNum string exists
    \param[in]  serial_num_string: serialNum string of usb device
    \param[out] none
    \retval     none
*/
void usbh_user_serialnum_string(void *serial_num_string)
{

}

/*!
    \brief      user response request is displayed to ask for application jump to class
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_enumeration_finish(void)
{

}

/*!
    \brief      user operation when device is not supported
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_device_not_supported(void)
{

}

/*!
    \brief      user action for application state entry
    \param[in]  none
    \param[out] none
    \retval     user response for user key
*/
usbh_user_status usbh_user_userinput(void)
{
    usbh_user_status usbh_usr_status = USBH_USER_NO_RESP;

    usb_mdelay(500);

    if (SET == gd_eval_key_state_get(KEY_WAKEUP)) {

        usbh_usr_status = USBH_USER_RESP_OK;
    }

    return usbh_usr_status;
}

/*!
    \brief      user operation for device overcurrent detection event
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_over_current_detected (void)
{

}

/*!
    \brief      demo application for mass storage
    \param[in]  pudev: pointer to device
    \param[in]  id: no use here
    \param[out] none
    \retval     status
*/
int usbh_usr_msc_application(void)
{
    FRESULT res;
    uint32_t bytesWritten, bytesToWrite;

    uint8_t TempStr[64], str_len = 0;

    switch(usbh_usr_application_state)
    {
        case USBH_USR_FS_INIT:
            /* initialises the file system*/
            if (FR_OK != f_mount(0, &fatfs)) {

                return(-1);
            }

            if (DISK_WRITE_PROTECTED == usbh_msc_param.msc_write_protect) {

            }

            usbh_usr_application_state = USBH_USR_FS_READLIST;
            break;

        case USBH_USR_FS_READLIST:

            while(SET == gd_eval_key_state_get(KEY_WAKEUP));
            while ((usbh_msc_core.host.connect_status)  && \
                (RESET == gd_eval_key_state_get (KEY_WAKEUP))) {
         
                usb_mdelay(50);

            }

            explore_disk("0:/", 1);
            line_idx = 0;
            usbh_usr_application_state = USBH_USR_FS_WRITEFILE;
            break;

        case USBH_USR_FS_WRITEFILE:
            usb_mdelay(100U);

            while(SET == gd_eval_key_state_get(KEY_WAKEUP));
            while ((usbh_msc_core.host.connect_status) && \
                    (RESET == gd_eval_key_state_get (KEY_WAKEUP))) {
 
                usb_mdelay(500);

            }

            if (DISK_WRITE_PROTECTED == usbh_msc_param.msc_write_protect) {
                usbh_usr_application_state = USBH_USR_FS_DEMOEND;
                break;
            }

            /* register work area for logical drives */
            f_mount(0, &fatfs);

            if (FR_OK == f_open(&file, "0:GD32.TXT", FA_CREATE_ALWAYS | FA_WRITE)) {
                /* write buffer to file */
                bytesToWrite = sizeof(WriteTextBuff); 
                res = f_write (&file, WriteTextBuff, bytesToWrite, (void *)&bytesWritten);
                /* EOF or error */
                if ((0U == bytesWritten) || (FR_OK != res)) {

                } else {

                }

                /* close file and filesystem */
                f_close(&file);
                f_mount(0, NULL); 
            } else {

            }

            usbh_usr_application_state = USBH_USR_FS_DEMOEND;

            break;

        case USBH_USR_FS_DEMOEND:
             gd_eval_led_on(LED1);

            break;

        default:
            break;
    }

    return(0);
}

/*!
    \brief      displays disk content
    \param[in]  path: pointer to root path
    \param[in]  recu_level: recursive level
    \param[out] none
    \retval     status
*/
static uint8_t explore_disk (char* path, uint8_t recu_level)
{
    FRESULT res;
    FILINFO fno;
    DIR dir;
    char *fn;

    res = f_opendir(&dir, path);

    if (res == FR_OK) {
        while (usbh_msc_core.host.connect_status) {
            res = f_readdir(&dir, &fno);
            if (FR_OK != res || 0U == fno.fname[0]) {
                break;
            }

            if ('.' == fno.fname[0]) {
                continue;
            }

            fn = fno.fname;

            if (AM_DIR == (fno.fattrib & AM_MASK)) {

            } else {

            }

            if ((AM_DIR == (fno.fattrib & AM_MASK)) && (1U == recu_level)) {
                explore_disk(fn, 2);
            }
        }
    }

    return res;
}

/*!
    \brief      toggle leds to shows user input state
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void toggle_leds(void)
{
    static uint32_t i;

    if (0x10000U == i++) {
        gd_eval_led_on(LED1);
        i = 0;
    }
}

/*!
    \brief      deinit user state and associated variables
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbh_user_deinit(void)
{
    usbh_usr_application_state = USBH_USR_FS_INIT;
}
