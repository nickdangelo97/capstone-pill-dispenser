#ifndef ALARMSTATE_H
#define ALARMSTATE_H

#include "state.h"

class AlarmState : public State
{
    
public:
    AlarmState();
    ~AlarmState();

protected:
    void run(void *argument) override;

};

#endif /* ALARMSTATE_H */
