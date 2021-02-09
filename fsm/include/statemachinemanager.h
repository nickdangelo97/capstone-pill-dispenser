#ifndef STATEMACHINEMANAGER_H
#define STATEMACHINEMANAGER_H


class State;

class StateMachineManager
{
public:
    StateMachineManager();
    ~StateMachineManager();

    static StateMachineManager* get_instance();

private:
    static StateMachineManager* __instance;

    State *_state;
};


#endif /* STATEMACHINEMANAGER_H */
