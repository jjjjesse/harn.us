#include <iostream>
#include <ctime>

struct timestamp
{
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
};

struct tm *local_time;

timestamp get_current_time()
{
    
    timestamp result;

    time_t current_time;
    time( &current_time );                   // Get the current time
    local_time = localtime( &current_time );  // Convert the current time to the local time

    result.day    = local_time->tm_mday;
    result.month  = local_time->tm_mon + 1;
    result.year   = local_time->tm_year + 1900;
    result.hour   = local_time->tm_hour;
    result.min    = local_time->tm_min;
    result.sec    = local_time->tm_sec;

    return result;
}

int main()
{
    timestamp current_time;
    current_time = get_current_time();

  //  std::cout << "This is currenttime: " << current_time << std::endl;
  //  std::cout << "This is localtime: " << local_time << std::endl;
    std::cout << "This program was exectued at: " << current_time.hour << ":" << current_time.min << ":" << current_time.sec << std::endl;
    std::cout << "And the current date is: " << current_time.day << "/" << current_time.month << "/" << current_time.year << std::endl;
    return 0;
}
