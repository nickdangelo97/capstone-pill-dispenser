#include "GUITask.h"

#include "cmsis_os2.h"
#include "app_touchgfx.h"


GUITask* GUITask::__instance = nullptr;
GUITask::GUITask()
{
    _gui_task_handle = Util::create_task(TouchGFX_Task, NULL, "TouchGFXTask", (osPriority_t)osPriorityNormal, 4096 * 4);
    
    if(!_gui_task_handle) {
        //error
    }

    if(!__instance)
        __instance = this;
}


GUITask::~GUITask()
{

}


GUITask* GUITask::get_instance()
{
    if(!__instance)
        __instance = new GUITask();

    return __instance;
}


TaskHandle_t GUITask::get_task_handle()
{
    return _gui_task_handle;
}
