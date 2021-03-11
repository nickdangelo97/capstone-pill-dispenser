#include "statemachinemanager.h"

#include "util.h"

//will need to include headers for each state file created.
//ex. #include "teststate.h"

StateMachineManager* StateMachineManager::__instance = nullptr;

StateMachineManager::StateMachineManager()
{
    //Next two lines are what we did to get teststate working (for reference)
    // TestState *ts = new TestState();
    // Util::create_task(TestState::run_state, new RunArguments(ts, nullptr), "ReadyState", osPriorityBelowNormal1, 512);

    if(!__instance)
        __instance = this;
}


StateMachineManager::~StateMachineManager()
{

}


StateMachineManager* StateMachineManager::get_instance()
{
    if(!__instance)
        __instance = new StateMachineManager();

    return __instance;
}

