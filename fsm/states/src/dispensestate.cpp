#include "dispensestate.h"

#include "FreeRTOS.h"
#include "task.h"

#include "string.h"
#include "stdio.h"


DispenseState::DispenseState()
    : State()
{

}


DispenseState::~DispenseState()
{

}


void DispenseState::run(void *argument)
{
    // Pseudo:
    // Make sure state.laststate is one that is allowed to call this (ex. alarmstate, manualdispensestate, misseddosestate)
    // Switch UI to dispense in progress screen.
    // IndexNextPackage();
    // Check if collection area is clear --> check collection area sensor
    // DispenseNextPackage();
    // Record time package was dispensed.
    // Confirm that package made it to dispensing area --> check collection area sensor
    // Move to next state --> adherence updates
}
