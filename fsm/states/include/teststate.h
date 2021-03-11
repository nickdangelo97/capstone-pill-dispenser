
// This state is here for reference only. Will be deleted.

#ifndef TESTSTATE_H
#define TESTSTATE_H


#include "state.h"


class TestState : public State
{
    
public:
    TestState();
    ~TestState();

protected:
    void run(void *argument) override;

};

#endif /* TESTSTATE_H */
