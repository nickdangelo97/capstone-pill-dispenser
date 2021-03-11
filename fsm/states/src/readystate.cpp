#include "readystate.h"

#include "FreeRTOS.h"
#include "task.h"

#include "string.h"
#include "stdio.h"


ReadyState::ReadyState()
    : State()
{

}


ReadyState::~ReadyState()
{

}


void ReadyState::run(void *argument)
{
    //Do something here.

    //The functionality described below occurs during normal operation.

    //Check next scheduled time.
    //Check current time.
    //Compare next scheduled time with current time.
    //If they are the same, move to alarm state.
    //If scheduled time > current time, find difference, wait that long.
    //If scheduled time < current time:
            // if difference < x amount of time (perhaps a minute) move to alarm
            // else error.

    //If device has been in ready state > 2 mins without GUI interaction, put display into sleep mode.

}
