#include "alarmstate.h"

#include "FreeRTOS.h"
#include "task.h"

#include "string.h"
#include "stdio.h"


AlarmState::AlarmState()
    : State()
{

}


AlarmState::~AlarmState()
{

}


void AlarmState::run(void *argument)
{
    // Check that this state was initiated by ready (or other?) state --> if not error.
    
    // Turn on the alarm and signal GUI to change to alarm screen.
    // When distification received by the UI turn off alarm and move to dispense state.
    // If duration in alarm state exceeds x amount of time (perhaps 20 mins to start), turn off alarm
    // and move to missed dose state.
        // missed dose state still to be defined, will include UI screen with instructions on what to do next
        // also, in missed dose state we can "ping" with the alarm every 5-10 minutes until cleared.
}
