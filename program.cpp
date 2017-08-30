#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <math.h>   
 
using namespace std;

enum menu
{

};


struct time_record
{
    time_t start_time;
    time_t end_time;
    int seconds;
    int minutes;
    int hours;
};

struct subject
{
    int final_mark;
    vector<time_record> time_records;
};

struct project
{
    vector<subject> subjects;
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

void seconds_to_hours(double seconds, time_record &timer)
{
    double temp_minutes; // 188
    timer.seconds = fmod(seconds, 60);   //8
    temp_minutes = (seconds - timer.seconds)/60; //180
    timer.minutes = fmod(temp_minutes, 60); //0
    timer.hours = (temp_minutes - timer.minutes)/60;
}


void display_timer(time_record timer)
{
    cout << "Time elapsed: ";
    cout << timer.hours << ":";
    if (timer.minutes < 10)
    {    
        cout << 0 << timer.minutes;  
    }
    else
    {
        cout << timer.minutes;
    }
    cout << ":";
    if (timer.seconds < 10)
    {
         cout << 0 << timer.seconds;
    }
    else
    {
        cout << timer.seconds;
    }
    cout << "\r" << flush;
}

void ticker(time_record timer)
{
    double seconds;
    time_t current_time;
    current_time = get_current_time();
    seconds = std::difftime(current_time, timer.start_time);
    cout.precision(0);
    seconds_to_hours(seconds, timer);
    display_timer(timer);
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
    time_record timer;
    timer.start_time = get_current_time();
    print_time(timer.start_time);
    while(true)
    {
        ticker(timer);
    }

    
    return 0;
}
