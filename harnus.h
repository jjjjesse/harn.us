#include <ctime>






struct time_record
{
    time_t start_time;
    time_t end_time;
    int seconds;
    int minutes;
    int hours;
    bool stored;
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




time_t get_current_time();
void seconds_to_hours(double seconds, time_record &timer);
void display_timer(time_record timer);
void ticker(time_record timer);
void print_time(time_t current_time);
time_record new_timer(char &input);


void connect_database();
void create_table(char *sql);
void setup_tables();