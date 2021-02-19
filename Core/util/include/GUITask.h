#ifndef GUITASK_H
#define GUITASK_H

#include "util.h"

class GUITask
{
public:
    GUITask();
    ~GUITask();

    static GUITask* get_instance();

    TaskHandle_t get_task_handle();

private:
    TaskHandle_t _gui_task_handle;

    static GUITask* __instance;
};

#endif /* GUITASK_H */
