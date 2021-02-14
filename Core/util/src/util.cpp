#include "util.h"


TaskHandle_t Util::create_task(osThreadFunc_t function, void *argument, const char *name, osPriority_t priority, uint32_t stack_size)
{
    osThreadAttr_t attributes = {};
    attributes.name = name;
    attributes.priority = priority;
    attributes.stack_size = stack_size;

    return (TaskHandle_t)osThreadNew(function, argument, &attributes);
}


int Util::seconds_since_midnight(int h, int m, int s, bool am)
{
    if(h == 12 && am)
        h = 0;
    
    if(h < 12 && !am)
        h += 12;

    return h*60*60 + m*60 + s;
}
