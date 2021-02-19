#ifndef BOARD_H
#define BOARD_H


struct RTCTimeStamp
{
    RTCTimeStamp() {}
    RTCTimeStamp(int hour, 
                 int minute, 
                 int second,
                 int am,
                 int weekday,
                 int month,
                 int date,
                 int year)
    : hr(hour), 
      min(minute), 
      sec(second), 
      am(am == 0),
      weekday(weekday),
      month(month),
      date(date),
      year(year)
    {}

    int hr = 0;
    int min = 0;
    int sec = 0;
    bool am;

    int weekday = 0;
    int month = 0;
    int date = 0; /* day of month */
    int year = 0; /* last 2 digits */
};


class Board
{
public:
    static bool set_rtc_time(int hr, int min, int sec, bool am);
   
    static bool set_rtc_date(int weekday, int month, int date, int year);
   
    static RTCTimeStamp get_rtc_time();
};

#endif // BOARD_H
