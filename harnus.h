#include "splashkit.h"

#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

using namespace std;

struct time_record
{
    time_t start_time;
    time_t end_time;
    int seconds;
    int minutes;
    int hours;
    int subject_id;
};


/*
struct subject
{
    int final_mark;
    vector<time_record> time_records;
};

struct project
{
    vector<subject> subjects;
};
*/


//FROM TIMER.CPP
time_t get_current_time();
void seconds_to_hours(double seconds, time_record &timer);
void display_timer(time_record timer);
void ticker(time_record timer);
void print_time(time_t current_time);
time_record new_timer(char &input);

//FROM DATABASE.CPP
sqlite3* connect_database();
void create_table(char *sql);
void setup_tables();
vector<vector<string>> select_data(const char *sql);
vector<vector<string>> get_projects();
void add_project_sql(string project_name);
