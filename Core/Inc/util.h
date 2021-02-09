#ifndef UTIL_H
#define UTIL_H

#include "FreeRTOS.h"
#include "task.h"


typedef void (*osThreadFunc_t) (void *argument);
enum osPriority_t : int;

class Util
{
public:
    static TaskHandle_t create_task(osThreadFunc_t function, void *argument, const char *name, osPriority_t priority,  uint32_t stack_size);
};


#endif /* UTIL_H */
