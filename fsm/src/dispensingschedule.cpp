#include "dispensingschedule.h"
#include "util.h"
#include "list"


//THIS FUNCTION IS JUST FOR TESTING --> until we have schedule in memory
std::list<ScheduledDose*> CreateSchedule(int size){
    char dayAbbr[4] = {'M', 'L', 'S', 'B'};
    int mins[4] = {0,0,0,0};
    int hrs[4] = {9,12,17,21};
    int midnightsecarr[4] = {Util::seconds_since_midnight(hrs[0], mins[0],0,1), Util::seconds_since_midnight(hrs[1], mins[1],0,1),
        Util::seconds_since_midnight(hrs[2], mins[2],0,1),Util::seconds_since_midnight(hrs[3], mins[3],0,1)};
    
    std::list<ScheduledDose*> mylist;

    for(int i=0;i<size;i++){
       ScheduledDose* thisdose = new ScheduledDose;
       thisdose->time_of_day = dayAbbr[size%4];
       thisdose->min = mins[size%4];
       thisdose->hr = hrs[size%4];
       thisdose->day = (i+1)%4; //This will overflow at end of the month
       thisdose->seconds_since_midnight = midnightsecarr[size%4];
       mylist.push_back(thisdose);
    };
    return mylist;
}


DispensingSchedule::DispensingSchedule(){
     _schedule = CreateSchedule(4);//need to get the uploaded schedule here (from memory eventually)
    _next_dose = _schedule.front(); //resets to first dose everytime, again will need to come from memory
};


DispensingSchedule::~DispensingSchedule(){

};


ScheduledDose DispensingSchedule::get_next_dose(){
    return *_next_dose;
};
