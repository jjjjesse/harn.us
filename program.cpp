#include <iostream>
#include <string>
#include <ctime>
#include <vector>
 
using namespace std;

struct project
{
    vector<subjects> subjects;
};

struct subject
{
    int final_mark;
    vector<time_record> time_records;
};

struct time_record
{
    time_t start_time;
    time_t end_time;
    int seconds;
    int minutes;
    int hours;
};

void clear_screen()
{
   cout << string( 100, '\n' );
}

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
    cout.precision(0);
    {
        cout << "Time elapsed: " << fixed << seconds << "\r";

    }
}

void print_time(time_t current_time)
{   
    struct tm *local_time;
    local_time = localtime( &current_time );
    local_time->tm_mon  = local_time->tm_mon + 1;
    local_time->tm_year   = local_time->tm_year + 1900;
    std::cout << "Timer started at: " << local_time->tm_hour << ":" << local_time->tm_min << std::endl;
    std::cout << "And the current date is: " << local_time->tm_mday << "/" << local_time->tm_mon << "/" << local_time->tm_year << std::endl;   
}

int main()
{
    clear_screen();
    time_t start_time, current_time;
    start_time = get_current_time();
    print_time(start_time);
    while(true)
    {
        current_time = get_current_time();
        ticker(start_time, current_time);
    }
    print_time(current_time);

    
    return 0;
}
