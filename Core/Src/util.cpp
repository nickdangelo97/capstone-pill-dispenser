#include "util.h"

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t Util::create_task(osThreadFunc_t function, void *argument, const char *name, osPriority_t priority, uint32_t stack_size)
{
    osThreadAttr_t attributes = {};
    attributes.name = name;
    attributes.priority = priority;
    attributes.stack_size = stack_size;

    return (TaskHandle_t)osThreadNew(function, argument, &attributes);
}
