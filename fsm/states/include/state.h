#ifndef STATE_H
#define STATE_H

#include "util.h"

class State;

struct RunArguments
{
    RunArguments(State *_s, void *_args)
        : state(_s), argument(_args)
    {
    }

    State *state;
    void *argument;
};

class State
{
    friend class StateMachineManager;
public:
    State()
    {}

    ~State() {}

protected:
    static void run_state(void *argument)  {
        RunArguments *args = (RunArguments *)(argument);

        if (!args) {
            //error
            return;
        }

        args->state->run(argument);

        for (;;);
    };

private:
    virtual void run(void *argument);
};




#endif /* STATE_H */
