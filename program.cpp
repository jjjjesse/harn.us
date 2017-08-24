#include <iostream>
#include <string>
#include <ctime>

using namespace std;


time_t get_current_time()
{
    time_t current_time;
    time( &current_time );
    return current_time;
}

void ticker(time_t start_time, time_t current_time)
{
    double seconds;
    seconds = std::difftime(current_time,start_time);
    cout.precision(3);
    {
        cout << fixed << seconds << "\r";

    }


}

void print_time(time_t current_time)
{   
    struct tm *local_time;
    local_time = localtime( &current_time );
    local_time->tm_mon  = local_time->tm_mon + 1;
    local_time->tm_year   = local_time->tm_year + 1900;
    std::cout << "Timer started at: " << local_time->tm_hour << ":" << local_time->tm_min << ":" << local_time->tm_sec << std::endl;
    std::cout << "And the current date is: " << local_time->tm_mday << "/" << local_time->tm_mon << "/" << local_time->tm_year << std::endl;   
}

int main()
{
    time_t start_time, current_time;
    start_time = get_current_time();
    while(true)
    {
        current_time = get_current_time();
        ticker(start_time, current_time);
    }
    print_time(current_time);

    
    return 0;
}
