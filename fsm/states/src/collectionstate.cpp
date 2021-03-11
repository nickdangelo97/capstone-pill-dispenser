#include "collectionstate.h"

#include "FreeRTOS.h"
#include "task.h"


CollectionState::CollectionState()
    : State()
{

}


CollectionState::~CollectionState()
{

}


void CollectionState::run(void *argument)
{
    // Pseudo:
    // Transition to this state immediately after dispensing.
    // System cannot enter another state until this state resolves.
    // Check sensors in collection area to monitor when pouch has been removed.
    // Store timestamp when pouch is removed.
    // Create and record data entry for dispensing + collection event.
    // Proceed to adherence update state.
}
