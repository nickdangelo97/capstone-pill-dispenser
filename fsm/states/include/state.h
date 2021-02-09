#ifndef STATE_H
#define STATE_H

#include "util.h"


class State
{
public:
    State(const char* name, osPriority_t priority, uint32_t stack_size)
    {}

    ~State() {}

protected:
    virtual void run(void *argument);
};



#endif /* STATE_H */
