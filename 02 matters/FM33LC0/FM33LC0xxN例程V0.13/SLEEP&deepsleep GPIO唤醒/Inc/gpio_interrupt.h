/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : gpio_interrupt.h
  * @brief          : Header for gpio_interrupt.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 FMSH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by FM under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_INTERRUPT_H
#define __GPIO_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fm33lc0xx_ll_rcc.h"
#include "fm33lc0xx_ll_lptim.h"
#include "fm33lc0xx_ll_lpuart.h"
#include "fm33lc0xx_ll_gpio.h"
#include "fm33lc0xx_ll_uart.h"
#include "fm33lc0xx_ll_vref.h"
#include "fm33lc0xx_ll_iwdt.h"
#include "fm33lc0xx_ll_wwdt.h"
#include "fm33lc0xx_ll_pmu.h"
#include "fm33lc0xx_ll_flash.h"
#include "fm33lc0xx_ll_svd.h"
#include "fm33lc0xx_ll_aes.h"
#include "fm33lc0xx_ll_rmu.h"
#include "fm33lc0xx_ll_rng.h"
#include "fm33lc0xx_ll_opa.h"
#include "fm33lc0xx_ll_comp.h"
#include "fm33lc0xx_ll_hdiv.h"
#include "fm33lc0xx_ll_i2c.h"
#include "fm33lc0xx_ll_spi.h"
#include "fm33lc0xx_ll_u7816.h"
#include "fm33lc0xx_ll_bstim.h"
#include "fm33lc0xx_ll_gptim.h"
#include "fm33lc0xx_ll_atim.h"
#include "fm33lc0xx_ll_crc.h"
#include "fm33lc0xx_ll_dma.h"
#include "fm33lc0xx_ll_rtc.h"
#include "fm33lc0xx_ll_lcd.h"
#include "mf_config.h"


#if defined(USE_FULL_ASSERT)
#include "fm33_assert.h"
#endif /* USE_FULL_ASSERT */



#define LINE_9_GPIO    GPIOC
#define LINE_9_PIN     LL_GPIO_PIN_6


void GPIO_interrupt_init(void);// 外部引脚中断初始化



#ifdef __cplusplus
}
#endif

#endif /* __GPIO_INTERRUPT_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
