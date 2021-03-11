#ifndef DISPENSESTATE_H
#define DISPENSESTATE_H

#include "state.h"

class DispenseState : public State
{
    
public:
    DispenseState();
    ~DispenseState();

protected:
    void run(void *argument) override;

};

#endif /* DISPENSESTATE_H */
