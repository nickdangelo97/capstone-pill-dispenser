/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * @attention
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

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "../ft6x06/ft6x06.h"
#include <stm32f7xx_hal.h>

extern "C"
{
    /** @brief With FT6206 : maximum 2 touches detected simultaneously
      */
#define TS_MAX_NB_TOUCH                 ((uint32_t) FT6206_MAX_DETECTABLE_TOUCH)

#define TS_SWAP_NONE                    ((uint8_t) 0x01)
#define TS_SWAP_X                       ((uint8_t) 0x02)
#define TS_SWAP_Y                       ((uint8_t) 0x04)
#define TS_SWAP_XY                      ((uint8_t) 0x08)

    /**
      * @brief TouchScreen FT6206 Slave I2C address 1
      */
#define TS_I2C_ADDRESS                   ((uint16_t)0x54)

    /**
      * @brief TouchScreen FT6336G Slave I2C address 2
      */
#define TS_I2C_ADDRESS_A02               ((uint16_t)0x70)

    /** @defgroup STM32F769I_DISCOVERY_TS_Exported_Types  TS Exported Types
      * @{
      */
    /**
    *  @brief TS_StateTypeDef
    *  Define TS State structure
    */
    typedef struct
    {
        uint8_t  touchDetected;                /*!< Total number of active touches detected at last scan */
        uint16_t touchX[TS_MAX_NB_TOUCH];      /*!< Touch X[0], X[1] coordinates on 12 bits */
        uint16_t touchY[TS_MAX_NB_TOUCH];      /*!< Touch Y[0], Y[1] coordinates on 12 bits */
    } TS_StateTypeDef;

    /**
     *  @brief TS_StatusTypeDef
     *  Define BSP_TS_xxx() functions possible return value,
     *  when status is returned by those functions.
     */
    typedef enum
    {
        TS_OK                = 0x00, /*!< Touch Ok */
        TS_ERROR             = 0x01, /*!< Touch Error */
        TS_TIMEOUT           = 0x02, /*!< Touch Timeout */
        TS_DEVICE_NOT_FOUND  = 0x03  /*!< Touchscreen device not found */
    } TS_StatusTypeDef;

    extern I2C_HandleTypeDef hi2c4;
    extern void MX_I2C4_Init(void);

    static uint8_t  ts_orientation;
    static uint8_t  I2C_Address = 0;

    /* TouchScreen (TS) IO functions */
    void     TS_IO_Init(void);
    void     TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
    uint8_t  TS_IO_Read(uint8_t Addr, uint8_t Reg);
    uint16_t TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t* Buffer, uint16_t Length);
    void     TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t* Buffer, uint16_t Length);
    void     TS_IO_Delay(uint32_t Delay);

    uint8_t BSP_TS_Init(uint16_t ts_SizeX, uint16_t ts_SizeY);
    uint8_t BSP_TS_GetState(TS_StateTypeDef* TS_State);
}

static bool bsp_ts_initialized = false;

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    if (BSP_TS_Init(800, 480) == TS_OK)
    {
        bsp_ts_initialized = true;
    }

    assert(bsp_ts_initialized);
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
    if (bsp_ts_initialized)
    {
        TS_StateTypeDef state;
        BSP_TS_GetState(&state);
        if (state.touchDetected)
        {
            x = state.touchX[0];
            y = state.touchY[0];
            return true;
        }
    }
    return false;
}

extern "C"
{
    /******************************** LINK TS (TouchScreen) ***********************/
    /**
      * @brief  Manages error callback by re-initializing I2C.
      * @param  i2c_handler : I2C handler
      * @param  Addr: I2C Address
      * @retval None
      */
    static void I2Cx_Error(I2C_HandleTypeDef* i2c_handler, uint8_t Addr)
    {
        /* De-initialize the I2C communication bus */
        HAL_I2C_DeInit(i2c_handler);

        /* Re-Initialize the I2C communication bus */
        MX_I2C4_Init();
    }

    /**
      * @brief  Reads multiple data.
      * @param  i2c_handler : I2C handler
      * @param  Addr: I2C address
      * @param  Reg: Reg address
      * @param  MemAddress: memory address
      * @param  Buffer: Pointer to data buffer
      * @param  Length: Length of the data
      * @retval HAL status
      */
    static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef* i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t* Buffer, uint16_t Length)
    {
        HAL_StatusTypeDef status = HAL_OK;

        status = HAL_I2C_Mem_Read(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

        /* Check the communication status */
        if (status != HAL_OK)
        {
            /* I2C error occured */
            I2Cx_Error(i2c_handler, Addr);
        }
        return status;
    }

    /**
      * @brief  Writes a value in a register of the device through BUS in using DMA mode.
      * @param  i2c_handler : I2C handler
      * @param  Addr: Device address on BUS Bus.
      * @param  Reg: The target register address to write
      * @param  MemAddress: memory address
      * @param  Buffer: The target register value to be written
      * @param  Length: buffer size to be written
      * @retval HAL status
      */
    static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef* i2c_handler, uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t* Buffer, uint16_t Length)
    {
        HAL_StatusTypeDef status = HAL_OK;

        status = HAL_I2C_Mem_Write(i2c_handler, Addr, (uint16_t)Reg, MemAddress, Buffer, Length, 1000);

        /* Check the communication status */
        if (status != HAL_OK)
        {
            /* Re-Initiaize the I2C Bus */
            I2Cx_Error(i2c_handler, Addr);
        }
        return status;
    }

    /**
      * @brief  Initializes Touchscreen low level.
      * @retval None
      */
    __weak void TS_IO_Init(void)
    {
        // I2Cx_Init(&hi2c4);
    }

    /**
      * @brief  Writes a single data.
      * @param  Addr: I2C address
      * @param  Reg: Reg address
      * @param  Value: Data to be written
      * @retval None
      */
    __weak void TS_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
    {
        I2Cx_WriteMultiple(&hi2c4, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&Value, 1);
    }

    /**
      * @brief  Reads a single data.
      * @param  Addr: I2C address
      * @param  Reg: Reg address
      * @retval Data to be read
      */
    __weak uint8_t TS_IO_Read(uint8_t Addr, uint8_t Reg)
    {
        uint8_t read_value = 0;

        I2Cx_ReadMultiple(&hi2c4, Addr, Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&read_value, 1);

        return read_value;
    }

    /**
      * @brief  Reads multiple data with I2C communication
      *         channel from TouchScreen.
      * @param  Addr: I2C address
      * @param  Reg: Register address
      * @param  Buffer: Pointer to data buffer
      * @param  Length: Length of the data
      * @retval Number of read data
      */
    __weak uint16_t TS_IO_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t* Buffer, uint16_t Length)
    {
        return I2Cx_ReadMultiple(&hi2c4, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
    }

    /**
      * @brief  Writes multiple data with I2C communication
      *         channel from MCU to TouchScreen.
      * @param  Addr: I2C address
      * @param  Reg: Register address
      * @param  Buffer: Pointer to data buffer
      * @param  Length: Length of the data
      * @retval None
      */
    __weak void TS_IO_WriteMultiple(uint8_t Addr, uint8_t Reg, uint8_t* Buffer, uint16_t Length)
    {
        I2Cx_WriteMultiple(&hi2c4, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
    }

    /**
      * @brief  Delay function used in TouchScreen low level driver.
      * @param  Delay: Delay in ms
      * @retval None
      */
    __weak void TS_IO_Delay(uint32_t Delay)
    {
        HAL_Delay(Delay);
    }

    /**
      * @brief  Initializes and configures the touch screen functionalities and
      *         configures all necessary hardware resources (GPIOs, I2C, clocks..).
      * @param  ts_SizeX : Maximum X size of the TS area on LCD
      * @param  ts_SizeY : Maximum Y size of the TS area on LCD
      * @retval TS_OK if all initializations are OK. Other value if error.
      */
    __weak uint8_t BSP_TS_Init(uint16_t ts_SizeX, uint16_t ts_SizeY)
    {
        uint8_t ts_status = TS_OK;
        uint8_t ts_id1, ts_id2 = 0;
        /* Note : I2C_Address is un-initialized here, but is not used at all in init function */
        /* but the prototype of Init() is like that in template and should be respected       */

        /* Initialize the communication channel to sensor (I2C) if necessary */
        /* that is initialization is done only once after a power up         */
        ft6x06_ts_drv.Init(I2C_Address);

        ts_id1 = ft6x06_ts_drv.ReadID(TS_I2C_ADDRESS);
        if (ts_id1 != FT6206_ID_VALUE)
        {
            ts_id2 = ft6x06_ts_drv.ReadID(TS_I2C_ADDRESS_A02);
            I2C_Address    = TS_I2C_ADDRESS_A02;
        }
        else
        {
            I2C_Address    = TS_I2C_ADDRESS;
        }

        /* Scan FT6xx6 TouchScreen IC controller ID register by I2C Read       */
        /* Verify this is a FT6206 or FT6336G, otherwise this is an error case */
        if ((ts_id1 == FT6206_ID_VALUE) || (ts_id2 == FT6206_ID_VALUE))
        {
            /* Get LCD chosen orientation */
            if (ts_SizeX < ts_SizeY)
            {
                ts_orientation = TS_SWAP_NONE;
            }
            else
            {
                ts_orientation = TS_SWAP_XY | TS_SWAP_Y;
            }

            if (ts_status == TS_OK)
            {
                /* Software reset the TouchScreen */
                ft6x06_ts_drv.Reset(I2C_Address);

                /* Calibrate, Configure and Start the TouchScreen driver */
                ft6x06_ts_drv.Start(I2C_Address);

            } /* of if(ts_status == TS_OK) */
        }
        else
        {
            ts_status = TS_DEVICE_NOT_FOUND;
        }

        return (ts_status);
    }
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TS_State: Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
__weak uint8_t BSP_TS_GetState(TS_StateTypeDef* TS_State)
{
    static uint32_t _x[TS_MAX_NB_TOUCH] = {0, 0};
    static uint32_t _y[TS_MAX_NB_TOUCH] = {0, 0};
    uint8_t ts_status = TS_OK;
    uint16_t tmp;
    uint16_t Raw_x[TS_MAX_NB_TOUCH];
    uint16_t Raw_y[TS_MAX_NB_TOUCH];
    uint16_t xDiff;
    uint16_t yDiff;
    uint32_t index;

    /* Check and update the number of touches active detected */
    TS_State->touchDetected = ft6x06_ts_drv.DetectTouch(I2C_Address);
    if (TS_State->touchDetected)
    {
        for (index = 0; index < TS_State->touchDetected; index++)
        {
            /* Get each touch coordinates */
            ft6x06_ts_drv.GetXY(I2C_Address, &(Raw_x[index]), &(Raw_y[index]));

            if (ts_orientation & TS_SWAP_XY)
            {
                tmp = Raw_x[index];
                Raw_x[index] = Raw_y[index];
                Raw_y[index] = tmp;
            }

            if (ts_orientation & TS_SWAP_X)
            {
                Raw_x[index] = FT_6206_MAX_WIDTH - 1 - Raw_x[index];
            }

            if (ts_orientation & TS_SWAP_Y)
            {
                Raw_y[index] = FT_6206_MAX_HEIGHT - 1 - Raw_y[index];
            }

            xDiff = Raw_x[index] > _x[index] ? (Raw_x[index] - _x[index]) : (_x[index] - Raw_x[index]);
            yDiff = Raw_y[index] > _y[index] ? (Raw_y[index] - _y[index]) : (_y[index] - Raw_y[index]);

            if ((xDiff + yDiff) > 5)
            {
                _x[index] = Raw_x[index];
                _y[index] = Raw_y[index];
            }


            TS_State->touchX[index] = _x[index];
            TS_State->touchY[index] = _y[index];
        } /* of for(index=0; index < TS_State->touchDetected; index++) */
    } /* end of if(TS_State->touchDetected != 0) */

    return (ts_status);
}
/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/