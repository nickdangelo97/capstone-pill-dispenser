#ifndef UTIL_H
#define UTIL_H

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"


class Util
{
public:
    static TaskHandle_t create_task(osThreadFunc_t function, void *argument, const char *name, osPriority_t priority,  uint32_t stack_size);

    static int seconds_since_midnight(int h, int m, int s, bool am);
};


#endif /* UTIL_H */
