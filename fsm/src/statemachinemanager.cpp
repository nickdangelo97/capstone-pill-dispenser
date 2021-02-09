#include "statemachinemanager.h"


StateMachineManager* StateMachineManager::__instance = nullptr;

StateMachineManager::StateMachineManager()
{

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

