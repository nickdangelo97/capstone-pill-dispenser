#include "board.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_rtc.h"

extern "C" RTC_HandleTypeDef hrtc;


bool Board::set_rtc_time(int hr, int min, int sec, bool am)
{
    RTC_TimeTypeDef new_time = {0};
    HAL_StatusTypeDef status;

    new_time.Hours = hr;
    new_time.Minutes = min;
    new_time.Seconds = sec;
    new_time.TimeFormat = am ? RTC_HOURFORMAT12_AM : RTC_HOURFORMAT12_PM;
    new_time.StoreOperation = RTC_STOREOPERATION_RESET;

    if (HAL_RTC_SetTime(&hrtc, &new_time, RTC_FORMAT_BIN) != HAL_OK)
        return false;

    return true;
}


bool Board::set_rtc_date(int weekday, int month, int date, int year)
{
    RTC_DateTypeDef new_date = {0};

    new_date.WeekDay = weekday;
    new_date.Month = month;
    new_date.Date = date;
    new_date.Year = year;

    if (HAL_RTC_SetDate(&hrtc, &new_date, RTC_FORMAT_BIN) != HAL_OK)
        return false;

    return true;
}       


RTCTimeStamp Board::get_rtc_time()
{
    RTC_TimeTypeDef get_time = {0};
    RTC_DateTypeDef get_date = {0};

    if(HAL_RTC_GetTime(&hrtc, &get_time, RTC_FORMAT_BIN) != HAL_OK || 
        HAL_RTC_GetDate(&hrtc, &get_date, RTC_FORMAT_BIN) != HAL_OK ) {
            //error
            return RTCTimeStamp();
        }

    return RTCTimeStamp(get_time.Hours,
                        get_time.Minutes, 
                        get_time.Seconds,
                        get_time.TimeFormat,
                        get_date.WeekDay,
                        get_date.Month,
                        get_date.Date,
                        get_date.Year);
}
