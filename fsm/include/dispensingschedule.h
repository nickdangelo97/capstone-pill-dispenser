#ifndef DISPENSINGSCHEDULE_H
#define DISPENSINGSCHEDULE_H

#include "board.h"
#include "list"


struct ScheduledDose{
    char time_of_day; //M - morning, L - lunch, S - supper, B - bedtime
    int min;
    int hr; //Using 24 hour-clock notation
    int day; // 1 - Sunday .... 7 - Saturday
    int seconds_since_midnight;
};


class DispensingSchedule
{
public:
    DispensingSchedule();
    ~DispensingSchedule();

    ScheduledDose get_next_dose(); //Returns next scheduled dose.
    
    static DispensingSchedule* get_instance();
    
private:
    static DispensingSchedule* __instance;

    std::list<ScheduledDose*> _schedule; //points to array of dose schedules.
    ScheduledDose* _next_dose;
};

#endif // DISPENSINGSCHEDULE_H
