#include "splashkit.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>   
 
using namespace std;

enum menu_option
{
    START_STOP_TIMER,
    QUIT
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
    write("\r");
    write("Time elapsed: ");
    write(timer.hours);
    write(":");
    if (timer.minutes < 10)
    {    
        write(0);
        write(timer.minutes);  
    }
    else
    {
        write(timer.minutes);
    }
    write(":");
    if (timer.seconds < 10)
    {
         write(0);
         write(timer.seconds);
    }
    else
    {
        write(timer.seconds);
    }
}

void ticker(time_record timer)
{
    set_terminal_bold(true);
    double seconds;
    time_t current_time;
    current_time = get_current_time();
    seconds = std::difftime(current_time, timer.start_time);
    cout.precision(0);
    seconds_to_hours(seconds, timer);
    display_timer(timer);
    refresh_terminal();
    set_terminal_bold(false);
}

void print_time(time_t current_time)
{   
    struct tm *local_time;
    local_time = localtime( &current_time );
    local_time->tm_mon  = local_time->tm_mon + 1;
    local_time->tm_year   = local_time->tm_year + 1900;
    write("Timer started at: ");
    write(local_time->tm_hour);
    write(":");
    write(local_time->tm_min);
    write(" ");
    write(local_time->tm_mday);
    write("/");
    write(local_time->tm_mon);
    write("/");
    write_line(local_time->tm_year);   
}

void print_menu()
{

}

time_record new_timer()
{
    bool timer_running = true;
    time_record timer;
    timer.start_time = get_current_time();
    print_time(timer.start_time);
    while(timer_running == true)
    { 
        ticker(timer);
        if (key_typed(UP_KEY)) // NOT WORKING
        {
            timer.end_time = get_current_time();
            timer_running =false;
        }
        process_events();
    }
    write_line("Timer stopped.");
    return timer;
}

void setup_terminal()
{
    activate_advanced_terminal();
    set_terminal_colors(color_yellow(), color_dark_blue());
    set_terminal_echo_input(false);
    clear_terminal(); 
}

int main()
{
    setup_terminal();
    
    print_menu();
    new_timer();
    return 0;
}
