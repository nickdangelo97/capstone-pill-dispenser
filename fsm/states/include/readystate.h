#ifndef READYSTATE_H
#define READYSTATE_H

#include "state.h"

class ReadyState : public State
{
    
public:
    ReadyState();
    ~ReadyState();

protected:
    void run(void *argument) override;

};

#endif /* READYSTATE_H */
