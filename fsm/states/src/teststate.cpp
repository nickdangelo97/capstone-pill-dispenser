

//Too be deleted, here for reference only.

#include "teststate.h"

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f769i_discovery.h"

#include "string.h"
#include "stdio.h"

TestState::TestState()
    : State()
{

}


TestState::~TestState()
{

}


void TestState::run(void *argument)
{
    // BSP_LED_Init(LED2);

    
    char msg[10];


    BSP_LED_Init(LED1);
    BSP_LED_Init(LED2);

    for(;;) {
        osDelay(500);
        BSP_LED_Toggle(LED2);
        BSP_LED_Toggle(LED1);
    }

}
