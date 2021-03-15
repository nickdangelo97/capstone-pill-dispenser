/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.16.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/**
 * @file touchgfx/hal/BoardConfiguration.hpp
 *
 * Declares initialization functions for the hardware as well as for TouchGFX.
 */
#ifndef BOARDCONFIGURATION_HPP
#define BOARDCONFIGURATION_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"


#define VSYNC_FREQ2_Pin GPIO_PIN_13
#define VSYNC_FREQ2_GPIO_Port GPIOJ
#define DSI_RESET_Pin GPIO_PIN_15
#define DSI_RESET_GPIO_Port GPIOJ
#define RENDER_TIME_Pin GPIO_PIN_7
#define RENDER_TIME_GPIO_Port GPIOC
#define VSYNC_FREQ_Pin GPIO_PIN_6
#define VSYNC_FREQ_GPIO_Port GPIOC
#define RENDER_TIME2_Pin GPIO_PIN_5
#define RENDER_TIME2_GPIO_Port GPIOJ
#define FRAMERATE_Pin GPIO_PIN_1
#define FRAMERATE_GPIO_Port GPIOJ


#define STEPPER_PAIR_1_PIN_1_Pin GPIO_PIN_6
#define STEPPER_PAIR_1_PIN_1_GPIO_Port GPIOF
#define STEPPER_PAIR_1_PIN_2_Pin GPIO_PIN_0
#define STEPPER_PAIR_1_PIN_2_GPIO_Port GPIOJ
#define STEPPER_PAIR_1_PIN_3_Pin GPIO_PIN_8
#define STEPPER_PAIR_1_PIN_3_GPIO_Port GPIOC
#define STEPPER_PAIR_1_PIN_4_Pin GPIO_PIN_7
#define STEPPER_PAIR_1_PIN_4_GPIO_Port GPIOF


#define STEPPER_PAIR_2_PIN_1_Pin GPIO_PIN_3
#define STEPPER_PAIR_2_PIN_1_GPIO_Port GPIOJ
#define STEPPER_PAIR_2_PIN_2_Pin GPIO_PIN_4
#define STEPPER_PAIR_2_PIN_2_GPIO_Port GPIOJ
#define STEPPER_PAIR_2_PIN_3_Pin GPIO_PIN_6
#define STEPPER_PAIR_2_PIN_3_GPIO_Port GPIOH
#define STEPPER_PAIR_2_PIN_4_Pin GPIO_PIN_11
#define STEPPER_PAIR_2_PIN_4_GPIO_Port GPIOA


#define CUTTER_1_Pin GPIO_PIN_6
#define CUTTER_1_GPIO_Port GPIOA
#define CUTTER_2_Pin GPIO_PIN_4
#define CUTTER_2_GPIO_Port GPIOA
#define CUTTER_3_Pin GPIO_PIN_2
#define CUTTER_3_GPIO_Port GPIOC
#define CUTTER_4_Pin GPIO_PIN_10
#define CUTTER_4_GPIO_Port GPIOF


/**
 * Function to perform generic hardware initialization of the board. This function prototype is
 * only provided as a convention.
 */
void hw_init();

/**
 * Function to perform touchgfx initialization. This function prototype is only provided as a
 * convention.
 */
void touchgfx_init();


void MX_I2C4_Init(void);
uint8_t QSPI_WriteEnable(QSPI_HandleTypeDef* hqspi);


#ifdef __cplusplus
}
#endif



#endif // BOARDCONFIGURATION_HPP
